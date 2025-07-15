// See https://svelte.dev/docs/kit/types#app.d.ts
// for information about these interfaces
declare global {
	namespace App {
		// interface Error {}
		// interface Locals {}
		// interface PageData {}
		// interface PageState {}
		// interface Platform {}
	}
}

declare module 'svelte-icons/*' {
	import { SvelteComponentTyped } from 'svelte';
	export default class GiPadlock extends SvelteComponentTyped<any, any, any> {}
}
