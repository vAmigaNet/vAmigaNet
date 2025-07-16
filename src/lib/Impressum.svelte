<script lang="ts">
	import { fade } from 'svelte/transition';

	function close() {
		console.log('close');
		show = false;
	}

	interface Props {
		show?: boolean;
	}

	let { show = $bindable(false) }: Props = $props();
</script>

<div class="" transition:fade>
	<div class="font-josefin flex h-[500px] flex-col">
		<!-- Header -->
		<div class="w-full text-center text-3xl font-semibold text-white">Impressum</div>
		<hr class="my-4 h-px border-0 bg-gray-200 dark:bg-gray-700" />

		<!-- Main -->
		<div class="grow overflow-auto border-blue-500 px-4">
			<div>
				<article in:fade class="prose mx-1">
					<h2>Kontakt</h2>
					<address>
						Prof. Dr. Dirk W. Hoffmann<br />
						Hochschule Karlsruhe<br />
						Moltkestraße 30<br />
						D - 76133 Karlsruhe<br />
						Germany
					</address>
					<h2>Datenschutz</h2>
					<p>
						Durch die Nutzung unserer Website erklären Sie sich mit der Erhebung, Verarbeitung und
						Nutzung von Daten gemäß der nachfolgenden Beschreibung einverstanden. Unsere Website
						kann grundsätzlich ohne Registrierung besucht werden. Dabei werden Daten wie
						beispielsweise aufgerufene Seiten bzw. Namen der abgerufenen Datei, Datum und Uhrzeit zu
						statistischen Zwecken auf dem Server gespeichert, ohne dass diese Daten unmittelbar auf
						Ihre Person bezogen werden. Personenbezogene Daten, insbesondere Name, Adresse oder
						E-Mail-Adresse werden soweit möglich auf freiwilliger Basis erhoben. Ohne Ihre
						Einwilligung erfolgt keine Weitergabe der Daten an Dritte.
					</p>
					<h2>Hosting</h2>
					<p>
						Diese Webseite wird gehostet auf Servern der Github Inc., 88 Colin P Kelly Jr. Street,
						San Francisco, CA 94107, USA. GitHub kann beim Aufruf dieser Webseiten technische
						Informationen inklusive ihrer IP Adresse aufzeichnen. Weitere Informationen zum Umgang
						mit Nutzerdaten finden Sie in der
						<a href="https://help.github.com/articles/github-privacy-policy"
							>Datenschutzerklärung von GitHub</a
						>.
					</p>
				</article>
			</div>
		</div>

		<!-- Footer -->
		<hr class="my-4 h-px border-0 bg-gray-200 dark:bg-gray-700" />
		<div class="flex w-full justify-center">
			<button class="btn btn-primary" onclick={close}>Close</button>
		</div>
	</div>
</div>
