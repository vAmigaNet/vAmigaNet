<script lang="ts">
	import { Layer } from '$lib/types';
	import { fade } from 'svelte/transition';
	import { liveQuery } from 'dexie';
	import { db, type RomEntry } from '$lib/Db/db';
	import { browser } from '$app/environment';
	import FaPlus from 'svelte-icons/fa/FaPlus.svelte';
	import FaTrash from 'svelte-icons/fa/FaTrash.svelte';
	import IoMdClose from 'svelte-icons/io/IoMdClose.svelte';
	import { amiga, initialized, layer, memory, proxy, wasm } from '$lib/stores';
	import FileDialog from '$lib/Utils/FileDialog.svelte';

	// Connect to Dexie DB
	let roms: RomEntry[] = $state([]);
	let myQuery = liveQuery(() => (browser ? db.roms.orderBy('title').toArray() : []));
	myQuery.subscribe((value) => {
		roms = value;
	});

	interface Props {
		show?: boolean;
	}

	let { show = $bindable(true) }: Props = $props();

	async function addRomToDatabase(rom: Uint8Array, ext: Uint8Array | null = null, extStart = 0) {
		let info = $memory.analyzeRom(rom, rom.length);
		if (info.crc32) {
			try {
				const t = info.title;

				const id = await db.roms.add({
					crc32: info.crc32,
					title: info.title,
					version: info.version,
					released: info.released,
					model: info.model,
					isAros: info.isAros,
					isDiag: info.isDiag,
					isCommodore: info.isCommodore,
					isHyperion: info.isHyperion,
					isPatched: info.isPatched,
					isUnknown: info.isUnknown,
					rom: rom,
					ext: ext,
					extStart: extStart
				});
				console.log(`${t} successfully added with id ${id}`);
			} catch (error) {
				console.log(`Failed to add Kickstart`);
			}
		}
	}

	async function installDefaultRoms() {
		try {
			// Add AROS
			let response = await fetch('roms/aros-svn55696-rom.bin');
			let blob = await response.arrayBuffer();
			let arosRom = new Uint8Array(blob);
			response = await fetch('roms/aros-svn55696-ext.bin');
			blob = await response.arrayBuffer();
			let arosExt = new Uint8Array(blob);

			await addRomToDatabase(arosRom, arosExt);

			// Add DiagROM
			response = await fetch('roms/diagrom-121.bin');
			blob = await response.arrayBuffer();
			let diagRom = new Uint8Array(blob);

			await addRomToDatabase(diagRom);
		} catch (exc) {
			console.error('Cannot install default Roms');
		}
	}

	function version(rom: RomEntry) {
		if (rom.isUnknown) {
			return 'CRC ' + rom.crc32.toString();
		} else {
			return rom.version;
		}
	}

	$effect(() => {
		if ($initialized) {
			installDefaultRoms();
		}
	});

	function imageUrl(rom: RomEntry) {
		return rom.isHyperion
			? 'rom-hyperion.png'
			: rom.isAros
				? 'rom-aros.png'
				: rom.isDiag
					? 'rom-diag.png'
					: rom.isCommodore
						? 'rom-commodore.png'
						: 'rom-unknown.png';
	}

	function close() {
		console.log('close');
		show = false;
		$layer = Layer.none;
	}

	async function deleteAction(e: MouseEvent, id: number) {
		console.log('deleteAction: ', id);
		try {
			await db.roms.delete(id);
			console.log(`{id} successfully deleted`);
		} catch (error) {
			console.log(`Failed to delete Kickstart`, error);
		}
	}

	async function installAction(e: MouseEvent, crc: number) {
		console.log('installAction: ', crc);
		$amiga.powerOff();
		await $wasm.installRom(crc);
		$amiga.hardReset();
		$amiga.run();
	}

	const debug = ''; // 'border-2';
	let activeTab = $state(0);

	let fdialog: FileDialog | undefined = $state();

	function addRomAction() {
		console.log('addRomAction');
		fdialog.open().then(
			function (value) {
				console.log('open file dialog', value);
				$proxy.addRom(value);
			},
			function (error) {
				console.log('error', error);
			}
		);
	}
</script>

<FileDialog bind:this={fdialog}></FileDialog>

<div class="{debug} flex h-full flex-col border-green-500">
	<div class="mx-2 flex items-center space-x-2">
		<div class="{debug} tabs tabs-box flex grow">
			<button class="tab" class:tab-active={activeTab === 0} onclick={() => (activeTab = 0)}
				>Installed Roms
			</button>
			<button class="tab" class:tab-active={activeTab === 1} onclick={() => (activeTab = 1)}
				>Legal Information
			</button>
			<div class="flex grow items-center justify-end">
				<button class="btn btn-sm btn-primary flex w-8 p-0" onclick={close}>
					<IoMdClose />
				</button>
			</div>
		</div>
	</div>
	<div class="mt-4 flex overflow-auto {debug} text-base-content p-1">
		{#if activeTab === 0}
			<table in:fade class="table-compact table-zebra table w-full">
				<tbody class={debug}>
					{#if roms}
						{#each roms as rom}
							<tr class="h-8 {debug} border-0 border-purple-400">
								<td class="">
									<div class="flex h-[5.5rem] space-x-4">
										<div class="{debug} h-full w-[4.5rem]">
											<img
												class="h-full w-full"
												src={'icons/' + imageUrl(rom)}
												alt="Rom Chip Icon"
											/>
										</div>
										<div class="{debug} flex h-full grow flex-col overflow-hidden">
											<div class="font-bold">{rom.title}</div>
											<div class="opacity-60">{version(rom)}</div>
											<div class="opacity-60">{rom.model}</div>
										</div>
										<div class="{debug} flex h-full items-center">
											<button
												class="btn btn-primary btn-outline btn-sm"
												onclick={(e) => installAction(e, rom.crc32)}
												>Install
											</button>
										</div>
										<div class="{debug} flex h-full items-center">
											<button
												class="btn btn-primary btn-outline btn-sm w-8 p-1.5"
												onclick={(e) => deleteAction(e, rom.crc32)}
											>
												<FaTrash />
											</button>
										</div>
									</div>
								</td>
							</tr>
						{/each}
					{/if}
					<tr class="h-8 {debug} border-0 border-purple-400">
						<td class="">
							<div class="flex h-[5.5rem] space-x-4">
								<div
									class="{debug} text-base-content font-josefin flex h-full grow flex-col justify-center overflow-hidden border-0 text-center text-base"
								>
									<p>Use drag-and-drop or press the 'Plus' button</p>
									<p>to add additional ROMs.</p>
								</div>
								<div class="{debug} flex h-full items-center">
									<button
										class="btn btn-primary btn-outline btn-sm w-8 p-1.5"
										onclick={() => addRomAction()}
									>
										<FaPlus />
									</button>
								</div>
							</div>
						</td>
					</tr>
				</tbody>
			</table>
		{:else}
			<article in:fade class="prose mx-1 {debug}">
				<h3>Kickstart</h3>
				<p>
					To run the emulator, a Kickstart ROM is required. The original Amiga ROMs are the
					intellectual property of Cloanto™ and cannot be freely distributed. If you own a legal
					Kickstart ROM, you can add the ROM image to vAmiga.net via drag and drop. Once a supported
					image is detected, it becomes available in the ROM database. The ROMs are stored in the
					browser's memory and will remain available in future sessions.
				</p>

				<h3>Encrypted ROMs</h3>
				<p>
					If you have purchased an older version of Amiga Forever™, you may possess encrypted ROM
					files. These are accompanied by a <code>.key</code> file required to decrypt the ROM. Encrypted
					ROMs are not yet supported by the emulator. They must be decrypted manually before they can
					be used in vAmiga.net.
				</p>

				<h3>AROS</h3>
				<p>
					If you don’t have access to an original Kickstart ROM, you may use the Amiga Research
					Operating System ROM (AROS) instead. AROS is an open-source Kickstart replacement and can
					be freely redistributed. However, not all Amiga programs are compatible with AROS, so we
					strongly recommend using vAmiga.net with original ROMs whenever possible.
				</p>
			</article>
		{/if}
	</div>
</div>
