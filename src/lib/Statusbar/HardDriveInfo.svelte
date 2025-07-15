<script lang="ts">
	import { run } from 'svelte/legacy';

	import { MenuItem } from '$lib/types';
	import { darkTheme, invert, poweredOn } from '$lib/stores';
	import BarBox from './BarBox.svelte';
	import Menu from '$lib/Widgets/Menu.svelte';

	interface Props {
		tag?: number;
		cyl?: number;
		reading?: boolean;
		writing?: boolean;
		unsaved?: boolean;
		select?: (value: number, tag: number) => void;
	}
	let {
		tag = 0,
		cyl = 0,
		reading = false,
		writing = false,
		unsaved = false,
		select = () => {}
	}: Props = $props();

	const gray = '';
	const green = 'bg-gradient-to-b from-green-700 to-green-500';
	const red = 'bg-gradient-to-b from-red-700 to-red-500';

	let items = $state([new MenuItem('Attach', 0)]);

	function update(power: boolean) {
		items[0].isEnabled = !power;
		items[0] = items[0];
	}

	const driveIcon = 'icons/hard-drive.png';
	const src = $derived(driveIcon);
	const bg = $derived(reading ? green : writing ? red : gray);
	const opc = $derived(unsaved ? 'opacity-40' : 'opacity-70');
	const textcol = $derived($darkTheme ? 'text-gray-300' : 'text-black');

	run(() => {
		update($poweredOn);
	});
</script>

<Menu
	{items}
	{tag}
	listStyle="menu menu-compact rounded p-0 text-sm w-32"
	select={(value: number) => {
		select(value, tag);
	}}
>
	<BarBox {bg}>
		<img
			class="h-full border-0 object-scale-down py-1.5 pr-1 {$invert} {opc}"
			{src}
			alt="Floppy icon"
		/>
		<div class="w-6 items-center border-0 pl-1 text-left text-sm leading-none {textcol}">
			{cyl}
		</div>
	</BarBox>
</Menu>
