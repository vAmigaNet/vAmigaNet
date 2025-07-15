<script lang="ts">
	import { darkTheme } from '$lib/stores';

	let {
		item = { id: '', icon: '' },
		alt = 'Icon',
		toggle = false,
		active = false,
		select = () => {}
	}: {
		item?: any;
		alt?: string;
		toggle?: boolean;
		active?: boolean;
		select: (sender: string, state: boolean) => void;
	} = $props();

	let state = false;

	function click(e: Event) {
		console.log('click', e);
		e.preventDefault();
		state = toggle ? !state : true;
		console.log('toggle = ', toggle);
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
