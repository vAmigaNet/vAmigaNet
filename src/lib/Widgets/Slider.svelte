<script lang="ts">
	import { createEventDispatcher } from 'svelte';
	import type { ActionEvent } from '$lib/types';

	let {
		tag = 0,
		value = 0,
		locked = false,
		min = 0,
		max = 0,
		open = true,
        select = () => {},
		children
	}: {
		tag?: number;
		value?: number;
		locked?: boolean;
		min?: number;
		max?: number;
		open?: boolean;
        select: (value: number) => void;
		children?: import('svelte').Snippet;
	} = $props();

	const dispatch = createEventDispatcher<{ select: ActionEvent }>();

	function sliderAction(e: Event) {
		e.preventDefault();
		value = Number((e.target as HTMLInputElement).value);
        console.log('tag', tag, 'value', value);
        select(value);
	}
</script>

<div class="dropdown dropdown-bottom">
	<!-- Make DropDown work in Safari using the label / tabindex trick (see DaisyUI doc) -->
	<!-- svelte-ignore a11y_no_noninteractive_tabindex -->
	<!-- svelte-ignore a11y_label_has_associated_control -->
     <button type="button" tabindex="0" onclick={(e) => (open = true)} class={locked ? 'pointer-events-none' : ''}>
		{@render children?.()}
	</button>
    <!--
	<label tabindex="0" onclick={(e) => (open = true)} class={locked ? 'pointer-events-none' : ''}>
		{@render children?.()}
	</label>
    -->
	<!-- svelte-ignore a11y_no_noninteractive_tabindex -->
	{#if open}
		<ul tabindex="0" class="dropdown-content menu bg-base-100 text-base-content mt-1 w-full">
			<input
				type="range"
				oninput={(e) => sliderAction(e)}
				{min}
				{max}
				{value}
				class="range range-accent h-12 rounded-none px-4"
			/>
		</ul>
	{/if}
</div>
