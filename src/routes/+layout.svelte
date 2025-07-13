<script lang="ts">
	import '../app.css';
	import { browser } from '$app/environment';
	import { onMount } from 'svelte';
	import { audio, config, gamepadManager, proxy } from '$lib/stores';
	import Audio from '$lib/Globals/Audio.svelte';
	import Config from '$lib/Globals/Config.svelte';
	import GamepadManager from '$lib/Globals/GamepadManager.svelte';
	import Guru from '$lib/Guru.svelte';
	import Proxy from '$lib/Proxy.svelte';
	// import { Module } from '../../static/vAmiga2.js';

	let loadWasm = false;

	/*
	onMount(() => {
		console.log('+layout: onMount()');

		// Bind to emscripten
		window.Module = $proxy;

		// Let the script read vAmiga.js
		console.log('loadWasm = true');
		loadWasm = true;
	});
	*/

	onMount(() => {
		if (!browser) return;

		console.log('+layout: onMount()');
		// Provide a Module object for Emscripten to use
		(window as any).Module = {
			onRuntimeInitialized() {
				console.log('WASM loaded');
				proxy.set((window as any).Module);
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

<!--
<svelte:head>
	<Audio bind:this={$audio} />
	<Config bind:this={$config} />
	<GamepadManager bind:this={$gamepadManager} />
	<Proxy bind:this={$proxy} />

	{#if loadWasm}
		<script>
			console.log('Loading vAmiga.js');
		</script>
		I am here
		<script src="vAmiga.js"></script>
	{/if}
</svelte:head>
<Guru />
<div class="relative">
	<slot />
</div>
-->