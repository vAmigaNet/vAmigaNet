<script lang="ts">
	import '../app.css';
	import { browser } from '$app/environment';
	import { onMount } from 'svelte';
	import { proxy, wasmLoaded } from '$lib/stores';

	onMount(() => {
		if (!browser) return;

		console.log('+layout: onMount()');

		// Provide a Module object for Emscripten to use
		(window as any).Module = {
			onRuntimeInitialized() {
				console.log('WASM loaded');
				proxy.set((window as any).Module);
				$wasmLoaded = true;
			}
		};

		// Dynamically insert the Emscripten glue script
		const script = document.createElement('script');
		script.src = '/vAmiga.js'; // served from /static
		script.async = true;
		document.body.appendChild(script);
	});

	let { children } = $props();
</script>

{@render children()}
