/*
 * Copyright 09/20/2026 https://github.com/su8/0verlaunch
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

/* Commands to run */
command mute[] = {(char *const)"amixer", (char *const)"set", (char *const)"Master", (char *const)"toggle", NULL};
command voldn[] = {(char *const)"amixer", (char *const)"set", (char *const)"Master", char *const)"1%-", NULL};
command volup[] = {(char *const)"amixer", (char *const)"set", (char *const)"Master", (char *const)"1%+", NULL};

/*
 * Rules
 * The possible values are:
 *  0:  Key release
 *  1:  Key press
 *  2:  Key hold
 * Normally, you'll get 1 followed by 0. If you hold the key past some
 * threshold,you'll get 1, then lots of 2s for as long as the key is depressed,
 * then 0.
 * Play around with printev to see exactly how it works, and to find out the
 * right codes.
 * For a simple hit, use 0.
 * To keep executing a command while a button is being held, 1 followed by 2
 * works well - see how voldn and volup work. 2s are only fired after a delay.
 */
struct event events[] = {
	/*code, value, command*/
	{0x71, 0, mute},
	{0x72, 1, voldn},
	{0x72, 2, voldn},
	{0x73, 1, volup},
	{0x73, 2, volup},
};

/*
 * Since holding a key creates lots of processes, it can result in a heavy load
 * on weaker systems. We'll usleep(DELAY) before forking to alleviate this.
 * Use 0 to disable the delay completely.
 */
#define DELAY 5