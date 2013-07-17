scrypt-js
=========

Emscripten sources for scrypt in Javascript

These are the subset of scrypt-1.1.6 (http://www.tarsnap.com/scrypt.html) needed
to run the crypto_scrypt() function.  config.h was generated using `emconfigure
./configure`.

Emscripten doesn't enable SSE support, so only crypto_scrypt-nosse.c is included.