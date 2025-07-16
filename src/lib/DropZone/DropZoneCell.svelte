<script lang="ts">
	import { invert } from '$lib/stores';
	import FaTimes from 'svelte-icons/fa/FaTimes.svelte';
	import { audio } from '$lib/stores';
	import Proxy from '$lib/Proxy.svelte';

	interface Props {
		id: number;
		name: string;
		enabled?: boolean;
		selected?: boolean;
		icon1?: string;
		icon2?: string;
		opacity?: string;
		select: (value: string) => void;
	}
	let {
		id,
		name,
		enabled = false,
		selected = false,
		icon1 = 'icons/disk.png',
		icon2 = 'icons/disk.png',
		opacity = 'opacity-50',
		select = () => {}
	}: Props = $props();

	let opac = $derived(selected ? 'opacity-100' : 'opacity-50');
	let bopac = $derived(enabled ? 'opacity-100' : 'opacity-50');

	function mouseEnter(event: MouseEvent) {
		event.preventDefault();
		if (enabled) selected = true;
	}

	function mouseLeave(event: MouseEvent) {
		event.preventDefault();
		selected = false;
	}

	async function mouseClick(event: MouseEvent) {
		event.preventDefault();
		await $audio.setup();
		select(name);
	}
</script>

<div class="bg-primary/90 rounded-xl p-4">
	<div class="flex flex-col items-center">
		<div
			class="border-primary-content h-32 w-32 rounded-xl border-2 p-5 {bopac}"
			onmouseenter={mouseEnter}
			onmouseleave={mouseLeave}
			onmousedown={mouseClick}
			role="button"
			tabindex="0"
		>
			{#if !enabled}
				<div class="text-primary-content h-full w-full opacity-50"><FaTimes /></div>
			{:else if selected}
				<img class="{$invert} {opac}" src={icon1} alt="Icon" />
			{:else if icon2 !== ''}
				<img class="{$invert} {opac}" src={icon2} alt="Icon" />
			{/if}
		</div>
		<div class="font-azaret text-primary-content text-xl">{name}</div>
	</div>
</div>
