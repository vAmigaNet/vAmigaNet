<script lang="ts">
    import { onMount } from 'svelte';
    import { InputDevice } from '$lib/types';
    import { joystick1, joystick2, port1, port2, wasm } from '$lib/stores';

    interface Props {
        gamepads?: { [index: number]: Gamepad };
    }

    let { gamepads = $bindable({}) }: Props = $props();

    onMount(() => {

        window.addEventListener(
            "gamepadconnected",
            (e) => { gamepads[e.gamepad.index] = e.gamepad; },
            false
        );
        window.addEventListener(
            "gamepaddisconnected",
            (e) => { delete gamepads[e.gamepad.index]; },
            false
        );
    });

    let tmp = 0;

    function joystickPort() {
        if ($port1 == InputDevice.gamepad1 || $port1 == InputDevice.gamepad2) {
            return $joystick1;
        }
        if ($port2 == InputDevice.gamepad1 || $port2 == InputDevice.gamepad2) {
            return $joystick2;
        }
        return null;
    }

    export function pollState()
    {
        const gps = navigator.getGamepads();
        if (gps.length == 0) return;
        const gp = gps[0];
        if (!gp) return;

        const b1 = gp.buttons[0].pressed;
        const ax = gp.axes[0].valueOf();
        const ay = gp.axes[1].valueOf();

        if (b1) {
            joystickPort()?.trigger($wasm.PRESS_FIRE);
        } else {
            joystickPort()?.trigger($wasm.RELEASE_FIRE);
        }
        if (ax < -0.5) {
            joystickPort()?.trigger($wasm.PULL_LEFT);
        } else if (ax > 0.5) {
            joystickPort()?.trigger($wasm.PULL_RIGHT);
        } else {
            joystickPort()?.trigger($wasm.RELEASE_X);
        }
        if (ay < -0.5) {
            joystickPort()?.trigger($wasm.PULL_UP);
        } else if (ay > 0.5) {
            joystickPort()?.trigger($wasm.PULL_DOWN);
        } else {
            joystickPort()?.trigger($wasm.RELEASE_Y);
        }
    }

</script>
