<script lang="ts">
	import { Opt } from '$lib/types';
	import { onMount } from 'svelte';
	import { fade } from 'svelte/transition';
	import { AnimatedFloat } from '$lib/Utils/AnimatedFloat';
	import { TextureRect } from '$lib/Utils/TextureRect';
	import GLCanvas from '$lib/GLCanvas.svelte';
	import {
		amiga,
		aspectHeight,
		aspectWidth,
		canvasHeight,
		canvasWidth,
		config,
		gamepadManager,
		layout,
		poweredOn,
		wasm
	} from '$lib/stores';

	// Component references
	let glCanvas: GLCanvas = $state()!;

	// Texture cutout
	let x1 = $state(0);
	let y1 = $state(0);
	let x2 = $state(0);
	let y2 = $state(0);
	let tx1 = $state(0);
	let ty1 = $state(0);
	let tx2 = $state(0);
	let ty2 = $state(0);

	interface Props {
		// Visible texture area
		textureRect?: any;
	}

	let { textureRect = new TextureRect() }: Props = $props();

	// Size of the emulator canvas
	let recw = new AnimatedFloat(0);
	let rech = new AnimatedFloat(0);

	// Triggers for redrawing the emulator canvas
	let w = $state(0);
	let h = $state(0);

	// Indicates if the emulator canvas is animating
	let animating = false;

	onMount(() => {
		console.log('Emulator::onMount()');
		textureRect.zoomIn();
	});

	export function updateRect(layout: string) {
		if (layout == 'full') {
			recw.set($canvasWidth);
			rech.set($canvasHeight);
		} else if (layout == 'aspect') {
			recw.set($aspectWidth);
			rech.set($aspectHeight);
		} else if (layout == 'fit') {
			const x1 = textureRect.x1.current * textureRect.texW;
			const y1 = textureRect.y1.current * textureRect.texH;
			const x2 = textureRect.x2.current * textureRect.texW;
			const y2 = textureRect.y2.current * textureRect.texH;
			recw.set(x2 - x1 + 2);
			rech.set(2 * (y2 - y1 + 2));
		}
	}

	export function doAnimationFrame(animationFrame: number, now: DOMHighResTimeStamp) {
		// Read pending messages
		const entries = [];
		$amiga.lockMsgQueue();
		while (1) {
			let msg = $amiga.readMessage();
			if (msg.type == $wasm.Msg.NONE) break;
			entries.push(msg);
		}
		$amiga.unlockMsgQueue();

		// Process messages
		for (const msg of entries) {
			$wasm.processMsg(msg);
		}

		if ($poweredOn) {
			update(now);
			glCanvas?.render();
		}
	}

	function update(now: DOMHighResTimeStamp) {
		let textureAnimates = textureRect.animates();
		let canvasAnimates = recw.animates() || rech.animates();
		animating = textureAnimates || canvasAnimates;

		// Poll gamepads
		$gamepadManager.pollState();

		// Perform animations
		if (textureAnimates) {
			textureRect.move();
			tx1 = textureRect.x1.current;
			ty1 = textureRect.y1.current;
			tx2 = textureRect.x2.current;
			ty2 = textureRect.y2.current;
			x1 = textureRect.x1.current * textureRect.texW;
			y1 = textureRect.y1.current * textureRect.texH;
			x2 = textureRect.x2.current * textureRect.texW;
			y2 = textureRect.y2.current * textureRect.texH;

			// In 1:1 mode, use the new texture size as the emulator canvas size to get a smooth effect
			if ($layout == 'fit') {
				w = recw.current = recw.target = x2 - x1 + 2;
				h = rech.current = rech.target = 2 * (y2 - y1 + 2);
			}
			if (glCanvas) glCanvas.needsDisplay = true;
		}
		if (canvasAnimates) {
			recw.move();
			rech.move();
			w = recw.current;
			h = rech.current;
			if (glCanvas) glCanvas.needsDisplay = true;
		}

		glCanvas?.update();
	}
	let canvasBorder = $derived(
		$config?.getBool(Opt.CANVAS_BORDER) ? 'border-2 border-primary border-opacity-100' : ''
	);

	$effect(() => {
		const l = $layout;

		if (l === 'full') {
			recw.set($canvasWidth);
			rech.set($canvasHeight);
		} else if (l === 'aspect') {
			recw.set($aspectWidth);
			rech.set($aspectHeight);
		} else if (l === 'fit') {
			const x1 = textureRect.x1.current * textureRect.texW;
			const y1 = textureRect.y1.current * textureRect.texH;
			const x2 = textureRect.x2.current * textureRect.texW;
			const y2 = textureRect.y2.current * textureRect.texH;
			recw.set(x2 - x1 + 2);
			rech.set(2 * (y2 - y1 + 2));
		}
	});

	export { textureRect };
</script>

{#if $poweredOn}
	<div class="relative flex h-full grow flex-col justify-center" transition:fade>
		<div class="flex h-full items-center justify-center">
			<div class={canvasBorder} style="height:{h}px; width:{w}px">
				<GLCanvas bind:this={glCanvas} {x1} {x2} {y1} {y2} {tx1} {tx2} {ty1} {ty2} />
			</div>
		</div>
	</div>
{/if}
