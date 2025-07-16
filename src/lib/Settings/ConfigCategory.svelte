<script lang="ts">
    interface Props {
        name?: string;
        active?: string;
        style?: string;
        onclick?: () => void;
    }

    let { name = '', active = '', style = 'text-3xl', onclick }: Props = $props();
</script>

<button {onclick} class="btn btn-ghost p-0 font-thin {active === name ? 'btn-active' : ''} {style}">
    {name}
</button>
