<script lang="ts">
	let {
		icon,
		description,
		onclick = () => {}
	}: {
		icon: import('svelte').Snippet;
		description: import('svelte').Snippet;
		onclick?: () => void;
	} = $props();
</script>

<div class="my-4 flex w-28 flex-col items-center justify-center border-0">
	<button
		class="flex h-16 w-16 flex-col items-center justify-center text-gray-300"
		{onclick}
	>
		{@render icon()}
	</button>
	<div class="font-josefin flex border-none text-xl text-gray-300">
		{@render description()}
	</div>
</div>
