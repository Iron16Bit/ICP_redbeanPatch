/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:2;tab-width:8;coding:utf-8 -*-│
│ vi: set et ft=c ts=2 sts=2 sw=2 fenc=utf-8                               :vi │
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2023 Justine Alexandra Roberts Tunney                              │
│                                                                              │
│ Permission to use, copy, modify, and/or distribute this software for         │
│ any purpose with or without fee is hereby granted, provided that the         │
│ above copyright notice and this permission notice appear in all copies.      │
│                                                                              │
│ THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL                │
│ WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED                │
│ WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE             │
│ AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL         │
│ DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR        │
│ PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER               │
│ TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR             │
│ PERFORMANCE OF THIS SOFTWARE.                                                │
╚─────────────────────────────────────────────────────────────────────────────*/
#include "libc/calls/calls.h"
#include "libc/fmt/conv.h"
#include "libc/runtime/runtime.h"
#include "libc/str/str.h"

void GenBuf(char buf[8], int x) {
  int i;
  bzero(buf, 8);
  for (i = 0; i < 7; ++i) {
    buf[i] = x & 127;  // nt doesn't respect invalid unicode?
    x >>= 1;
  }
}

int main(int argc, char *argv[]) {
  char buf[8];
  if (argc != 4) {
    tinyprint(2, "error: argc != 4\n", NULL);
    return 20;
  }
  GenBuf(buf, atoi(argv[2]));
  if (strcmp(buf, argv[3])) {
    tinyprint(2, "error: buf check failed\n", NULL);
    return 10;
  }
  const char *prog = "./execve_test_prog2";
  if (!fork()) {
    execl(prog, prog, NULL);
    _Exit(127);
  }
  int ws;
  if (wait(&ws) == -1)
    return 30;
  if (ws)
    return 31;
  return 0;
}
