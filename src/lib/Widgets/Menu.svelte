<script lang="ts">
	import type { Snippet } from 'svelte';
	import { MenuItem, MenuSeparator } from '$lib/types';
	import Checkmark from './Checkmark.svelte';

	let {
		tag = 0,
		items = [],
		isEnabled = true,
		dropdownStyle = '',
		listStyle = '',
		select = () => {},
		children
	}: {
		tag: number;
		items?: MenuItem[];
		isEnabled?: boolean;
		dropdownStyle?: string;
		listStyle?: string;
		select: (value: number) => void;
		children?: Snippet;
	} = $props();

	const selectedItems = $derived(items.filter((item) => item.isSelected));

	const action = (e: MouseEvent, value: number) => {
		e.preventDefault();

		// Force the dropdown to close
		if (document.activeElement) (document.activeElement as HTMLElement).blur();
		console.log(`Menu action: ${tag} - ${value}`);
		select(value);
	};

	function style(i: number) {
		return items[i].isEnabled ? '' : 'opacity-20';
	}
</script>

<div class="dropdown {dropdownStyle}">
	<!-- <div tabindex="0" role="button" class="btn m-1">Click</div> -->
	<!-- svelte-ignore a11y_no_noninteractive_tabindex -->
	<label tabindex="0" class={isEnabled ? '' : 'pointer-events-none'}>
		{@render children?.()}
	</label>
	<!-- svelte-ignore a11y_no_noninteractive_tabindex -->
	<!-- svelte-ignore a11y_label_has_associated_control -->
	<ul tabindex="0" class="dropdown-content menu bg-base-100 rounded-box z-1 w-52 p-2 shadow-sm">
		{#key items}
			{#each items as item, i}
				{#if item instanceof MenuSeparator}
					<li class="divider"></li>
				{:else if !item.isHidden}
					<li id={tag.toString()}>
						<button
							disabled={!item.isEnabled}
							class={item.isEnabled ? '' : 'hover:bg-base-100 opacity-40'}
							onclick={(e) => action(e, item.tag)}
						>
							<Checkmark enabled={selectedItems.length !== 0} visible={item.isSelected} />
							{item.title}</button
						>
					</li>
				{/if}
			{/each}
		{/key}
	</ul>
</div>
