<script lang="ts">
	interface Props {
		enabled: boolean;
		visible: boolean;
	}

	let { enabled, visible }: Props = $props();
</script>

{#if enabled}
	<div class="w-4">{@html visible ? '&#10003' : ''}</div>
{/if}
