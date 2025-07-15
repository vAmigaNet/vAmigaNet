<script lang="ts">
	let {
		bg = '',
		children
	}: {
		bg?: string;
		children?: import('svelte').Snippet;
	} = $props();
</script>

<div class="flex h-8">
	<div class="flex h-full w-16 items-center justify-center {bg}">
		{@render children?.()}
	</div>
	<div class="h-full w-1 bg-black"></div>
</div>
