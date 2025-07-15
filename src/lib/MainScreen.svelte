<script lang="ts">
	import { Layer } from '$lib/types';
	import { amiga, dragItem, dragType, initialized, layer, wasm } from '$lib/stores';

	let {
		children
	}: {
		children?: import('svelte').Snippet;
	} = $props();

	function handleDragEnter(event: DragEvent) {
		event.preventDefault();
		if (!event.dataTransfer) {
			return;
		}
	}

	function handleDragOver(event: DragEvent) {
		event.preventDefault();
	}

	function handleDragLeave(event: DragEvent) {}

	async function handleDragDrop(event: DragEvent) {
		event.preventDefault();

		// Only proceed if we've received any data
		if (!event.dataTransfer || !event.dataTransfer.items) return;

		// Only proceed if the user has dragged in a single item
		if (event.dataTransfer.items.length !== 1) return;
		let item = event.dataTransfer.items[0];

		// Only proceed if the user has dragged in a file
		if (item.kind !== 'file') return;
		const file = item.getAsFile();
		if (!file) return;

		// Get the file data
		let blob = await file.arrayBuffer();
		let uint8View = new Uint8Array(blob);

		// Check the file type
		switch ($amiga.getFileType(blob)) {
			case $wasm.FILETYPE_ROM:
				await handleDraggedRom(uint8View);
				return;
			case $wasm.FILETYPE_ADF:
			case $wasm.FILETYPE_EADF:
			case $wasm.FILETYPE_DMS:
			case $wasm.FILETYPE_EXE:
				handleDraggedDisk(uint8View);
				return;
			case $wasm.FILETYPE_HDF:
				handleDraggedHardDrive(uint8View);
				return;
			default:
				console.warn('Unsupported file format');
				return;
		}
	}

	async function handleDraggedRom(blob: Uint8Array) {
		$wasm.addRom(blob);
	}

	function handleDraggedDisk(blob: Uint8Array) {
		$dragItem = blob;
		$dragType = 'floppy';
		$layer = Layer.dropzone;
	}

	function handleDraggedHardDrive(blob: Uint8Array) {
		$dragItem = blob;
		$dragType = 'harddrive';
		$layer = Layer.dropzone;
	}
</script>

<div
	class="flex h-screen w-screen flex-grow flex-col overflow-clip"
	role="region"
	ondragenter={handleDragEnter}
	ondragleave={handleDragLeave}
	ondragover={handleDragOver}
	ondrop={handleDragDrop}
>
	{#if $initialized}
		{@render children?.()}
	{/if}
</div>
