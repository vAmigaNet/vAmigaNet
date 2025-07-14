<script lang="ts">
	import '../app.css';
	import { browser } from '$app/environment';
	import { onMount } from 'svelte';
	import { wasm } from '$lib/stores';
	import vAmigaFactory from '$lib/vAmiga.js';

	onMount(() => {
		if (!browser) return;

		console.log('+layout: onMount()');

		(async () => {
			console.log('Loading vAmiga WASM module...');
			$wasm = await vAmigaFactory();
			console.log('vAmiga WASM module loaded:', $wasm);
			console.log('HEAP32:', $wasm.HEAP32);
			// $wasmLoaded = true;
		})();
	});

	let { children } = $props();
</script>

{@render children()}
