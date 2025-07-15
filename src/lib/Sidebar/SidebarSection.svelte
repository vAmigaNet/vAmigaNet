<script lang="ts">
	import SidebarButton from '$lib/Sidebar/SidebarButton.svelte';
	import { fade } from 'svelte/transition';

	let {
		expanded = false,
		item = { id: '', icon: '' },
		subitems = [{ id: '', icon: '' }],
		select = () => {}
	}: {
		expanded?: boolean;
		item?: any;
		subitems?: any;
		select: (sender: string, state: boolean) => void;
	} = $props();
</script>

<div class="flex border-0">
	<div>
		<div class="border-0">
			<SidebarButton {select} active={expanded} {item} />
		</div>
	</div>
	{#if expanded}
		<div transition:fade={{ duration: 200 }}>
			<div class="mx-1 flex space-x-1">
				{#each subitems as item}
					<SidebarButton {select} {item} />
				{/each}
			</div>
		</div>
	{/if}
</div>
