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
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <errno.h>
#include <err.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/input.h>

typedef char *const command;

struct event {
	uint16_t code;
	int32_t value;
	command *cmd;
};

#include "config.h"

const size_t nevents = sizeof(events) / sizeof(events[0]);

int main(int argc, char *argv[]) {
  struct input_event ev;
  size_t x;
  if (argc != 2) { printf("Usage: %s <evdev>\ne.g. /dev/input/event5\n", argv[0]); return EXIT_FAILURE; }
  int fd = open(argv[1], O_RDONLY | O_NONBLOCK);
  if (fd == -1) { perror("open"); return EXIT_FAILURE; }
  while (1) {
    read(fd, &ev, sizeof(ev));
    for (x = 0; x < nevents; x++) {
      if (ev.code == events[x].code && ev.value == events[x].value && ev.type == EV_KEY &&
          #if DELAY
          !usleep(DELAY) &&
          #endif
          !fork()) {
        close(fd);
        execvp(events[x].cmd[0], events[x].cmd);
        err(1, "execvp");
      }
    }
    fflush(stdout);
  }
  return EXIT_SUCCESS;
}
