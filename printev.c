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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <err.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/input.h>

int main(int argc, char *argv[]) {
  int fd;
  struct input_event ev;
  if (argc != 2) { printf("Usage: %s <evdev>\ne.g. /dev/input/event5\n", argv[0]); return EXIT_FAILURE; }
  if ((fd = open(argv[1], O_RDONLY)) == -1) { err(2, "open %s", argv[1]); }
  while (1) {
    read(fd, &ev, sizeof ev);
    if (ev.type == EV_KEY) { printf("code: 0x%x, value: 0x%x\n", ev.code, ev.value); }
	  fflush(stdout);
  }
	return EXIT_SUCCESS;
}