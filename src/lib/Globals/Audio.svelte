<script lang="ts">
    import { amiga, audioPort, wasm } from '$lib/stores';

    let audioContext: AudioContext;
    let insertSound: AudioBuffer;
    let ejectSound: AudioBuffer;
    let stepSound: AudioBuffer;
    let clickSound: AudioBuffer;

    let playCnt = 0;

    export async function setup()
    {
        if (audioContext) {
            return;
        }
        console.log('Setting up audio...');

        audioContext = new AudioContext();
        audioContext.onstatechange = () => console.log('Audio Context: state = ' + audioContext.state);
        let gainNode = audioContext.createGain();
        gainNode.gain.value = 1.0;
        gainNode.connect(audioContext.destination);

        console.log('Audio context: ', audioContext.state);
        $audioPort.setSampleRate(audioContext.sampleRate);
        await audioContext.audioWorklet.addModule('js/audio-processor.js');

        console.log('Audio Worklet module loaded');
        const audioNode = new AudioWorkletNode(audioContext, 'audio-processor', {
            outputChannelCount: [2],
            processorOptions: {
                pointers: [$audioPort.leftChannelBuffer(), $audioPort.rightChannelBuffer()],
                buffer: $wasm.HEAPF32.buffer,
                length: 2048
            }
        });
        console.log('Audio Worklet Node created');
        audioNode.port.onmessage = (e) => {
            $audioPort.updateAudio(e.data);
        };
        // audioNode.connect(audioContext.destination);
        audioNode.connect(gainNode);
        if (audioContext.state === 'suspended') {
            await audioContext.resume();
        }

        await loadSounds();
    }

    async function loadSounds()
    {
        console.log('Loading sounds...');
        if (!insertSound) insertSound = await loadSound('sounds/insert.mp3');
        if (!ejectSound) ejectSound = await loadSound('sounds/eject.mp3');
        if (!stepSound) stepSound = await loadSound('sounds/step.mp3');
        if (!clickSound) clickSound = await loadSound('sounds/stephd.mp3');
    }

    export function playInsertSound(volume: number, pan: number)
    {
        playAudioBuffer(insertSound, volume, pan);
    }

    export function playEjectSound(volume: number, pan: number)
    {
        playAudioBuffer(ejectSound, volume, pan);
    }

    export function playStepSound(volume: number, pan: number)
    {
        playAudioBuffer(stepSound, volume, pan);
    }

    export function playClickSound(volume: number, pan: number)
    {
        playAudioBuffer(clickSound, volume, pan);
    }

    async function playAudioBuffer(buffer: AudioBuffer | null, volume: number, pan: number)
    {
        if (buffer == null || playCnt >= 3) return;

        // TODO: Take care of pan
        const gain_node = audioContext.createGain();
        gain_node.gain.value = 0.004 * volume;
        gain_node.connect(audioContext.destination);

        const source = audioContext.createBufferSource();
        source.buffer = buffer;
        source.addEventListener('ended', () => {
            playCnt--;
        });
        source.connect(gain_node);
        source.start();

        playCnt++;
    }

    async function loadSound(url: string)
    {
        // console.log('load_sound: url = ' + url);
        let response = await fetch(url);
        let buffer = await response.arrayBuffer();
        return await audioContext.decodeAudioData(buffer);
    }
</script>
