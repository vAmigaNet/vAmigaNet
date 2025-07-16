<script lang="ts">
    import { onMount } from 'svelte';
    import { MenuItem, Opt, RenderMode } from '$lib/types';
    import { fade } from 'svelte/transition';
    import ConfigSection from './ConfigSection.svelte';
    import ConfigItem from '$lib/Settings/ConfigItem.svelte';
    import { config, wasm } from '$lib/stores';

    onMount(() => {
        update();
    });

    function update()
    {
    }

    function renderModeAction(value: number)
    {
        $config.set(Opt.RENDER_MODE, value);
        update();
    }

    function paletteAction(value: number)
    {
        $config.set(Opt.PALETTE, value);
        update();
    }

    function brightnessAction(value: number)
    {
        $config.set(Opt.BRIGHTNESS, value);
        update();
    }

    function contrastAction(value: number)
    {
        $config.set(Opt.CONTRAST, value);
        update();
    }

    function saturationAction(value: number)
    {
        $config.set(Opt.SATURATION, value);
        update();
    }

    function flickerAction(value: number)
    {
        $config.set(Opt.FLICKER_WEIGHT, value);
        update();
    }
</script>

<div in:fade>
    <ConfigSection name="WebGL">
        <ConfigItem
                name="Render Mode"
                items={[
				new MenuItem('Smooth', RenderMode.smooth),
				new MenuItem('Pixelated', RenderMode.pixelated)
			]}
                selectedTag={$config.getNum(Opt.RENDER_MODE)}
                select={renderModeAction}
        />
    </ConfigSection>
    <ConfigSection name="Colors">
        <ConfigItem
                name="Palette"
                items={[
				new MenuItem('Color', $wasm.PALETTE_COLOR),
				new MenuItem('Black and White', $wasm.PALETTE_BLACK_WHITE),
				new MenuItem('Paper White', $wasm.PALETTE_PAPER_WHITE),
				new MenuItem('Green', $wasm.PALETTE_GREEN),
				new MenuItem('Amber', $wasm.PALETTE_AMBER),
				new MenuItem('Sepia', $wasm.PALETTE_SEPIA)
			]}
                selectedTag={$config.getNum(Opt.PALETTE)}
                select={paletteAction}
        />
        <ConfigItem
                name="Brightness"
                min={0}
                max={100}
                tag={$wasm.OPT_BRIGHTNESS}
                selectedTag={$config.getNum(Opt.BRIGHTNESS)}
                select={brightnessAction}
        />
        <ConfigItem
                name="Contrast"
                min={0}
                max={100}
                tag={$wasm.OPT_CONTRAST}
                selectedTag={$config.getNum(Opt.CONTRAST)}
                select={contrastAction}
        />
        <ConfigItem
                name="Saturation"
                min={0}
                max={100}
                tag={$wasm.OPT_SATURATION}
                selectedTag={$config.getNum(Opt.SATURATION)}
                select={saturationAction}
        />
    </ConfigSection>
    <ConfigSection name="Interlace">
        <ConfigItem
                name="Flicker Weight"
                min={0}
                max={100}
                tag={1000}
                selectedTag={$config.getNum(Opt.FLICKER_WEIGHT)}
                select={flickerAction}
        />
    </ConfigSection>
</div>
