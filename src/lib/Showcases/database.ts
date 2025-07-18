import type { DataBaseItem } from '$lib/types';
import { WarpMode } from '$lib/types';
import { CRC32 } from '$lib/constants';

export const demos: DataBaseItem[] = [
	{
		url: 'batmanrises',
		title: 'Batman Rises',
		subtitle: 'The Batman Group',
		description:
			'Batman Rises is a demo released in December 2022 at the Posadas Party Autumn Edition. It quickly gained public attention and is widely regarded as one of the finest demos ever created for the Commodore Amiga.',
		adf: ['BatmanRises1.adf', 'BatmanRises2.adf'],
		memory: [1024, 512, 0],
		roms: [CRC32.Aros],
		warp: WarpMode.never
	},
	{
		url: 'stateart',
		title: 'State of the Art',
		subtitle: 'Spaceballs',
		description:
			'This demo was released in December 1992 and took 1st place in the Amiga Demo Competition at The Party 1992.',
		adf: ['StateArt.adf'],
		memory: [512, 512, 0],
		roms: [CRC32.Aros],
		warp: WarpMode.never
	},
	{
		url: 'rinkadink',
		title: 'Rink a Dink - Redux',
		subtitle: 'Lemon',
		description:
			'This demo was released by Lemon at Revision 2013 and has gained widespread popularity over time. We have used it extensively since the early days of vAmiga to test and validate the emulator.',
		adf: ['RinkADink.adf'],
		memory: [512, 512, 0],
		roms: [CRC32.Aros],
		warp: WarpMode.never
	},
	{
		url: 'desertdreams',
		title: 'Desert Dreams',
		subtitle: 'Kefrens',
		description:
			'This demo was released in April 1993 and won 1st place in the Amiga Demo Competition at The Gathering 1993.',
		adf: ['DesertDream1.adf', 'DesertDream2.adf'],
		memory: [1024, 512, 0],
		roms: [CRC32.Aros],
		warp: WarpMode.never
	},
	{
		url: 'inebriation',
		title: 'Absolute Inebriation',
		subtitle: 'Virtual Dreams & Fairlight',
		description:
			'This demo was released in December 1992 as the debut production of Virtual Dreams, a Finnish-based Amiga demo group. The group later rose to prominence during their time as the demo division of Fairlight.',
		adf: ['AbsoluteInebriation1.adf'],
		memory: [512, 512, 0],
		roms: [CRC32.Aros],
		warp: WarpMode.never
	},
	{
		url: 'eon',
		title: 'Eon',
		subtitle: 'The Black Lotus',
		description:
			'This demo is widely regarded as one of the finest ever created for the Commodore Amiga. It showcases the machine’s full potential through masterful use of its hardware capabilities.',
		adf: ['Eon1.adf'],
		memory: [512, 512, 0],
		roms: [CRC32.Kick12, CRC32.Kick13],
		warp: WarpMode.never
	},
	{
		url: '3ddemo',
		title: '3D Demo II',
		subtitle: 'Anarchy',
		description:
			'This demo was released in December 1992 and placed 2nd in the Amiga Demo Competition at The Party 1992.',
		adf: ['3Ddemo2.adf'],
		memory: [1024, 512, 0],
		roms: [CRC32.Kick12, CRC32.Kick13],
		warp: WarpMode.never
	},
	{
		url: 'hamazing',
		title: 'HAMazing',
		subtitle: 'Desire',
		description:
			'This demo won the 16-bit demo competition at SIGGRAPH Asia 2023 and was nominated for Outstanding Technical Achievement at The Meteoriks 2024. It showcases the impressive HAM (Hold-And-Modify) graphics capabilities of the Amiga.',
		adf: ['Hamazing.adf'],
		memory: [1024, 512, 0],
		roms: [CRC32.Kick12, CRC32.Kick13],
		warp: WarpMode.never
	},
{
		url: 'sushiboyz',
		title: 'Sushi Boyz',
		subtitle: 'Ghostown',
		description:
			'This demo was released in April 2015 and won 1st place in the Amiga Demo Competition at Revision 2015.',
		adf: ['Sushiboyz.adf'],
		memory: [1024, 512, 0],
		roms: [CRC32.Kick12, CRC32.Kick13],
		warp: WarpMode.never
	},
	{
		url: 'kyrios',
		title: 'Mental Scrollover',
		subtitle: 'Kyrios',
		description:
			'This demo was released in August 1990. I’ve used it many times to test vAmiga and have grown fond of it over time.',
		adf: ['Kyrios.adf'],
		memory: [1024, 512, 0],
		roms: [CRC32.Kick12, CRC32.Kick13],
		warp: WarpMode.never
	}
];

export const games: DataBaseItem[] = [
	{
		url: 'traprunner',
		title: 'Trap Runner',
		subtitle: 'Night Owl Design',
		description:
			'Trap Runner is a classic platform game with a few clever twists. Navigate mind traps, dodge obstacles, and battle monsters as you collect items to boost your score, gain extra lives, or complete special missions. The game runs on any OCS/ECS Amiga with at least 1MB of RAM, starting from Kickstart 1.2.',
		adf: ['TrapRunner.adf'],
		memory: [512, 512, 8192],
		roms: [CRC32.Aros],
		warp: WarpMode.never
	},
	{
		url: 'celtic',
		title: 'Celtic Heart',
		subtitle: 'Night Owl Design',
		description:
			'This game was developed in early 2019, largely built on the Trap Runner engine. Set in a medieval world, you play as the Celtic knight Eric on a quest to save the kingdom from an evil force.',
		adf: ['CelticHeart.adf'],
		memory: [512, 512, 8192],
		roms: [CRC32.Aros],
		warp: WarpMode.never
	},
	{
		url: 'paccer',
		title: 'Paccer',
		subtitle: 'Dirk W. Hoffmann',
		description:
			'This game is a Pac-Man clone originally released on Fish Disk 223. I developed it myself many years ago on my Amiga 500 using the Aztec C compiler and DPaint. Unfortunately, I lost the source code when my parents cleaned out their attic, but fortunately, the game has survived and is still available on the Internet.',
		adf: ['Paccer.adf'],
		memory: [512, 512, 0],
		roms: [CRC32.Kick12, CRC32.Kick13],
		warp: WarpMode.never
	},
	{
		url: 'china',
		title: 'China Challenge II',
		subtitle: 'Dirk W. Hoffmann',
		description:
			'This game is a Mahjong clone that I developed myself many years ago. The original version was released on Fish Disk 312, and this slightly improved sequel was later published on Fish Disk 444.',
		adf: ['ChinaChallengeII.adf'],
		memory: [512, 512, 0],
		roms: [CRC32.Kick12, CRC32.Kick13],
		warp: WarpMode.never
	},
	{
		url: 'defender',
		title: 'Defender of the Crown',
		subtitle: 'Cinemaware',
		description:
			"Defender of the Crown is a strategy game designed by Kellyn Beck and was Cinemaware’s very first release. Originally launched for the Commodore Amiga in 1986, it set a new benchmark for graphic quality in home computer games.",
		adf: ['DefenderOfTheCrown1.adf', 'DefenderOfTheCrown2.adf'],
		memory: [512, 512, 0],
		roms: [CRC32.Kick12, CRC32.Kick13],
		warp: WarpMode.never
	}
];

export const tools: DataBaseItem[] = [
	{
		url: 'sysinfo',
		title: 'Sysinfo 4.4',
		subtitle: 'Nic Wilson, Tobias Geijersson',
		description:
			'Sysinfo is a shareware program written entirely in Assembly for Motorola 68k-equipped Amiga computers to benchmark system performance. It displays the version of system software in ROM, the hardware present, and the current operating mode of the hardware.',
		adf: ['SysInfo.adf'],
		memory: [1024, 512, 0],
		roms: [CRC32.Kick12, CRC32.Kick13],
		warp: WarpMode.never
	},
	{
		url: 'testkit',
		title: 'Amiga Test Kit',
		subtitle: 'Keir Fraser',
		description:
			'The Amiga Test Kit is a software-based tool designed to test and diagnose various components of a Commodore Amiga.',
		adf: ['AmigaTestKit.adf'],
		memory: [512, 512, 0],
		roms: [CRC32.Kick12, CRC32.Kick13],
		warp: WarpMode.never
	},
	{
		url: 'diagrom',
		title: 'Amiga DiagROM',
		subtitle: 'John Hertell',
		description:
			'The Amiga Diagnostic ROM is a hardware-based testing solution for Amiga computers. Installed as a replacement for the Kickstart ROM on the motherboard, it boots the system into a diagnostic menu upon power-up. The ROM provides a range of test routines to check various hardware components.',
		adf: [],
		memory: [512, 512, 0],
		roms: [CRC32.DiagROM],
		warp: WarpMode.never
	}
];
