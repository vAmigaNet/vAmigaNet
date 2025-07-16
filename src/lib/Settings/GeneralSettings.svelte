<script lang="ts">
    import { MenuItem, Opt, Theme } from "$lib/types";
    import { fade } from 'svelte/transition';
    import ConfigSection from '$lib/Settings/ConfigSection.svelte';
    import ConfigItem from '$lib/Settings/ConfigItem.svelte';
    import { config } from '$lib/stores';

    function saveAction()
    {
        $config.saveGeneralSettings();
    }

    function resetAction()
    {
        $config.restoreGeneralDefaults();
    }

</script>

<div in:fade>
    <ConfigSection name="Warp mode">
        <ConfigItem
                items={[
				new MenuItem('During Disk Accesses', 0),
				new MenuItem('Never', 1),
				new MenuItem('Always', 2)
			]}
                name="Enable warp mode"
                select={(value) => $config.setNum(Opt.WARP_MODE, value)}
                selectedTag={$config.getNum(Opt.WARP_MODE)}
        />
    </ConfigSection>
    <ConfigSection name="Appearance">
        <ConfigItem
                items={[
                    new MenuItem('Default', Theme.default),
				    new MenuItem('Light', Theme.light),
				    new MenuItem('Dark', Theme.dark),
				new MenuItem('Coffee', Theme.coffee),
				new MenuItem('Cupcake', Theme.cupcake),
				new MenuItem('Forest', Theme.forest),
				new MenuItem('Aqua', Theme.aqua),
				new MenuItem('Garden', Theme.garden),
				new MenuItem('Pastel', Theme.pastel)
			]}
                name="Color theme"
                select={(value) => $config.setNum(Opt.THEME, value)}
                selectedTag={$config.getNum(Opt.THEME)}
        />
        <ConfigItem
                items={[
                    new MenuItem('Yes', 1),
                    new MenuItem('No', 0)
                    ]}
                name="Draw Canvas Border"
                select={(value) => $config.setNum(Opt.CANVAS_BORDER, value)}
                selectedTag={$config.getNum(Opt.CANVAS_BORDER)}
        />
    </ConfigSection>
    <ConfigSection name="Peripherals">
        <ConfigItem
                items={[
                    new MenuItem('Yes', 1),
                    new MenuItem('No', 0)
                    ]}
                name="Release Mouse by Shaking"
                select={(value) => $config.setNum(Opt.SHAKING, value)}
                selectedTag={$config.getNum(Opt.SHAKING)}
        />
    </ConfigSection>
</div>
