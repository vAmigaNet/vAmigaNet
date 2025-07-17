<script lang="ts">
	import type { Snippet } from 'svelte';
	import { MenuItem } from '$lib/types';
	import Menu from '$lib/Widgets/Menu.svelte';
	import Checkmark from './Checkmark.svelte';

	interface Props {
		tag?: number;
		items?: MenuItem[];
		isEnabled?: boolean;
		checkmarks?: boolean;
		dropdownStyle?: string;
		listStyle?: string;
		selectedTag?: number;
		select: (value: number) => void;
		children?: Snippet;
	}
	let {
		tag = 0,
		items = [],
		isEnabled = true,
		checkmarks = true,
		dropdownStyle = '',
		listStyle = '',
		selectedTag = 0,
		select = () => {},
		children
	}: Props = $props();

	let checkmark = $derived(selectedTag == tag ? '&#10003' : '');

	let checkmarkedItems = $derived.by(() => {
		let result = items;
		let selected = selectedTag;
		for (const item of result) {
			item.isSelected = item.tag == selected;
		}
		return result;
	});
</script>

{#key items}
<Menu {tag} items={checkmarkedItems} {isEnabled} {checkmarks} {dropdownStyle} {listStyle} {select}>
	{@render children?.()}
</Menu>
{/key}
