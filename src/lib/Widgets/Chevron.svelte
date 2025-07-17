<script lang="ts">
	import FaChevronDown from 'svelte-icons/fa/FaChevronDown.svelte';
	interface Props {
		children?: import('svelte').Snippet;
	}
	let { children }: Props = $props();
</script>

<div class="flex w-full items-center justify-between">
	<div class="flex grow justify-center">
		{@render children?.()}
	</div>
	<div class="h-4 w-4">
		<FaChevronDown />
	</div>
</div>
