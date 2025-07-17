<script lang="ts">
	interface Props {
		enabled: boolean;
		visible: boolean;
	}

	let { enabled, visible }: Props = $props();
</script>

{#if enabled}
	{#if visible}
		<!-- <div class="w-4">{@html visible ? '&#10003' : ''}</div> -->
		<div class="w-4">&#10003</div>
	{:else}
		<div class="w-4"></div>
	{/if}
{/if}
