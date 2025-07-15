<script lang="ts">
	import { darkTheme } from '$lib/stores';

	let {
		src = '',
		children
	}: {
		src?: string;
		children?: import('svelte').Snippet;
	} = $props();

	function click() {
		e.preventDefault();
	}
</script>

<button type="button" onclick={() => click()}>
	<img
		class="border-0 p-1.5 w-8 h-8 object-scale-down {$darkTheme ? 'invert' : ''} opacity-70"
		{src}
		alt="Status bar icon"
	/>
</button>
{@render children?.()}

