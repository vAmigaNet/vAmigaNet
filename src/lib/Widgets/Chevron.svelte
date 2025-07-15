<script lang="ts">
	import FaChevronDown from 'svelte-icons/fa/FaChevronDown.svelte';
	let {
		children
	}: {
		children?: import('svelte').Snippet;
	} = $props();
</script>

<div class="flex w-full items-center justify-between">
	<div class="flex grow justify-center">
		{@render children?.()}
	</div>
	<div class="w-4 h-4">
		<FaChevronDown />
	</div>
</div>
