<script lang="ts">
	import '../app.css';
	import { browser } from '$app/environment';
	import { onMount } from 'svelte';
	import { wasm } from '$lib/stores';
	import vAmigaFactory from '$lib/vAmiga.js';

	onMount(() => {
		console.log('+layout::onMount()');

		if (!browser) return;

		(async () => {
			console.log('Loading WASM module...');
			$wasm = await vAmigaFactory();
		})();
	});

	let { children } = $props();
</script>

{@render children?.()}
