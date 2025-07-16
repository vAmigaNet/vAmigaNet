<script lang="ts">
	import FaLock from 'svelte-icons/fa/FaLock.svelte';

	interface Props {
		title?: string;
		src?: string;
		active?: boolean;
		locked?: boolean;
	}
	let { title = '???', src = '', active = false, locked = false }: Props = $props();

	let textcol = $derived(active ? 'text-white' : 'text-gray-400');
	let border = $derived(active ? 'border-white border-2' : 'border-gray-700 border-2');
	let brightness = $derived(active ? 'brightness-125' : '');
	let opacity = $derived(active ? 'opacity-100' : 'opacity-100');

	export { title, src, active, locked };
</script>

<div class="">
	<div class="relative p-1">
		<img class="rounded border-solid {border} {brightness} {opacity}" {src} alt={title} />
		{#if locked}
			<div class="absolute top-0 left-0 flex h-full w-full items-center justify-center">
				<div class="h-12 w-12 text-gray-200 opacity-70"><FaLock /></div>
			</div>
		{/if}
	</div>
	<div class="p-1">
		<div class="font-josefin justify-center text-xl">
			<div class="flex justify-center {textcol}">{title}</div>
		</div>
	</div>
</div>
