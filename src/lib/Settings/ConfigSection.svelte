<script lang="ts">
	let {
		name = '',
		children
	}: {
		name?: string;
		children?: import('svelte').Snippet;
	} = $props();
</script>

<div class="px-0 py-0.5">
	<div class="w-full flex">
		<div class="text-xl text-base-content">{name}</div>
	</div>
	 children}{@render children?.()}
</div>
