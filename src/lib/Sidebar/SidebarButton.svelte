<script lang="ts">
	import { darkTheme } from '$lib/stores';

	interface Props {
		item?: { id: string; icon: string };
		alt?: string;
		toggle?: boolean;
		active?: boolean;
		select: (sender: string, state: boolean) => void;
	}
	let {
		item = { id: '', icon: '' },
		alt = 'Icon',
		toggle = false,
		active = false,
		select = () => {}
	}: Props = $props();

	let state = false;

	function click(e: Event) {
		e.preventDefault();
		state = toggle ? !state : true;
		select((e.target as HTMLElement).id, state);
	}
</script>

<button
	type="button"
	class="btn btn-lg btn-primary btn-square p-1.5 {active ? 'btn-active' : ''}"
	onclick={click}
>
	<img class={$darkTheme ? 'invert' : ''} id={item.id} src={item.icon} {alt} />
</button>
