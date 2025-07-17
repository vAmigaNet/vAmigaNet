<script lang="ts">
	import type { ActionEvent } from '$lib/types';
	import { onMount } from 'svelte';
	import { wasm, amiga, cpu, agnus } from '$lib/stores';
	import { darkTheme } from '$lib/stores';
	import Menu from '$lib/Widgets/Menu.svelte';
	import SelectMenu from '$lib/Widgets/SelectMenu.svelte';
	import { MenuItem } from '$lib/types';

	interface Props {
		acceleration?: number;
		mhz?: number;
		emuFps?: number;
		gpuFps?: number;
		latchedTimestamp?: number;
		latchedCycle?: number;
		latchedEmuFrame?: number;
		latchedGpuFrame?: number;
	}
	let {
		acceleration = $bindable(1.0),
		mhz = $bindable(0.0),
		emuFps = $bindable(0.0),
		gpuFps = $bindable(0.0),
		latchedTimestamp = $bindable(0.0),
		latchedCycle = $bindable(0.0),
		latchedEmuFrame = $bindable(0.0),
		latchedGpuFrame = $bindable(0.0)
	}: Props = $props();

	let mode = $state(0);
	let value = $state('');

	let items: MenuItem[] = $state([
		new MenuItem('Amiga Frequency', 0),
		new MenuItem('Amiga Refresh Rate', 1),
		new MenuItem('Host CPU Load', 2),
		new MenuItem('Host GPU Refresh Rate', 3),
		new MenuItem('Audio Buffer Fill Level', 4)
	]);

	onMount(() => {
		latchedTimestamp = Date.now();
		items[0].isSelected = true;
	});

	export function update(animationFrame: number, now: DOMHighResTimeStamp) {
		if (animationFrame % 10 != 0) return;

		let timestamp = Date.now();
		let elapsedTime = (timestamp - latchedTimestamp) / 1000;

		let cycle = $cpu.getClock();
		let emuFrame = $agnus.frameCount();
		let gpuFrame = animationFrame;

		// Measure clock frequency
		if (cycle >= latchedCycle) {
			const elapsedCycles = (cycle - latchedCycle) / 1000000;
			const alpha = 0.5;
			mhz = alpha * (elapsedCycles / elapsedTime) + (1 - alpha) * mhz;
		}

		// Measure emulator frames per second
		if (animationFrame % 25 == 0 && emuFrame >= latchedEmuFrame) {
			const elapsedFrames = emuFrame - latchedEmuFrame;
			const alpha = 0.9;
			emuFps = alpha * (elapsedFrames / elapsedTime) + (1 - alpha) * emuFps;
		}

		if (animationFrame % 25 == 0 && gpuFrame >= latchedGpuFrame) {
			// Measure GPU frames per second
			const elapsedFrames = gpuFrame - latchedGpuFrame;
			const alpha = 0.9;
			gpuFps = alpha * (elapsedFrames / elapsedTime) + (1 - alpha) * gpuFps;
		}

		if (animationFrame % 25 == 0) {
			redraw();
		}

		// Keep values
		latchedTimestamp = timestamp;
		latchedCycle = cycle;
		latchedEmuFrame = emuFrame;
		latchedGpuFrame = gpuFrame;
	}

	function redraw() {
		switch (mode) {
			case 0:
				acceleration = $amiga.getConfig($wasm.OPT_CPU_OVERCLOCKING);
				if (acceleration == 0) acceleration = 1;
				value = (mhz * acceleration).toFixed(2) + ' MHz';
				break;
			case 1:
				value = emuFps.toFixed(0) + ' Hz';
				break;
			case 2:
				value = $amiga.cpuLoad() + '%';
				break;
			case 3:
				value = gpuFps.toFixed(0) + ' Hz';
				break;
			case 4:
				value = $amiga.audioFillLevel() + '%';
				break;
			default:
				value = '---';
				break;
		}
	}

	function select(value: number) {
		mode = value;
		items.forEach(function (item) {
			item.isSelected = item.tag == mode;
		});

		// Force component to refresh
		items = items;
		redraw();
	}
</script>

<div class="flex h-8">
	<div class="h-full w-1 bg-black"></div>
	{#key mode}
	<SelectMenu
		{items}
		selectedTag={mode}
		{select}
		dropdownStyle="dropdown-end"
		listStyle="menu menu-compact rounded text-sm w-64"
	>
		<div class="text-primary-content flex h-full w-20 items-center justify-center text-xs">
			{value}
		</div>
	</SelectMenu>
	{/key}
</div>
