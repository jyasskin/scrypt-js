scrypt-js
=========

Emscripten sources for scrypt in Javascript

These are the subset of scrypt-1.1.6 (http://www.tarsnap.com/scrypt.html) needed
to run the crypto_scrypt() function.  config.h was generated using `emconfigure
./configure`.

Emscripten doesn't enable SSE support, so only crypto_scrypt-nosse.c is included.

Emscripten's output has two major problems:

* I haven't found a way to emit only the computation functions without
  a lot of wrapper code. This makes the output significantly larger
  than it needs to be.
* Emscripten, and possibly asm.js, insists on establishing the heap
  size at load time. However, scrypt uses a variable amount of
  heap--up to more than a gigabyte for N==2^20.  I've set the heap
  size to 2^28, which wastes space for many uses and isn't enough for
  some of the largest.

However, in Chrome 29 and Firefox 22, it appears to run approximately
as fast as native code, which is impressive.
