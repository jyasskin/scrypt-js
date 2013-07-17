# Put Emscripten's emcc in your path.
EMCC := emcc

CPPFLAGS := -I. -Ilib -Ilib/util -D HAVE_CONFIG_H
EMFLAGS := -s ERROR_ON_UNDEFINED_SYMBOLS=1 -s 'EXPORTED_FUNCTIONS=["_crypto_scrypt"]' -s INVOKE_RUN=0 -s CLOSURE_ANNOTATIONS=1

SCRYPT_SOURCE := lib/crypto/crypto_scrypt-nosse.c lib/crypto/sha256.c
SCRYPT_HEADERS := config.h scrypt_platform.h lib/crypto/sha256.h lib/util/sysendian.h lib/crypto/crypto_scrypt.h

scrypt.js: $(SCRYPT_SOURCE) $(SCRYPT_HEADERS) Makefile
	$(EMCC) -O2 $(CPPFLAGS) $(EMFLAGS) $(SCRYPT_SOURCE) -o $@