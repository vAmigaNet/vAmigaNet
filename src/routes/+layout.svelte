<script lang="ts">
	import '../app.css';
	import { browser } from '$app/environment';
	import { onMount } from 'svelte';
	import { wasm, loadWasm, wasmLoaded } from '$lib/stores';
	import vAmigaFactory from '$lib/vAmiga.js';

	let module: any;

	onMount(() => {
		if (!browser) return;

		console.log('+layout: onMount()');

		(async () => {
			console.log('Loading vAmiga WASM module...');
			module = await vAmigaFactory();
			console.log('vAmiga WASM module loaded:', module);
			console.log('HEAP32:', module.HEAP32);
		})();

		/*
		// Provide a Module object for Emscripten to use
		(window as any).Module = {
			onRuntimeInitialized() {
				wasm.set((window as any).Module);
				console.log('WASM loaded');
				// $loadWasm = true;
				$wasmLoaded = true;
							console.log('HEAP: ', $wasm.HEAPF32);

			}
		};

		// Dynamically insert the Emscripten glue script
		const script = document.createElement('script');
		script.src = '/vAmiga.js'; // served from /static
		script.async = true;
		script.onload = () => {
			console.log('Emscripten glue script loaded');
			console.log('HEAP: ', $wasm);
		};
		document.body.appendChild(script);
		*/
	});

	let { children } = $props();
</script>

{@render children()}
