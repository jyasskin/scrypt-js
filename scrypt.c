#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/crypto/crypto_scrypt.h"

void usage() {
  printf("Usage: test passwd salt N r p outlen\n"
         "  N, r, p, and outlen must be integers.\n"
         "  r * p < 2^30; outlen <= (2^32 - 1) * 32\n"
         "  Will print hex-encoded bytes of output.\n"
         "  See http://www.tarsnap.com/scrypt/scrypt.pdf for specification.\n");
  exit(1);
}

unsigned long long parse(const char* in) {
  char* endptr = NULL;
  errno = 0;
  unsigned long long result = strtoull(in, &endptr, 10);
  if (errno != 0)
    usage();
  if (*endptr != '\0')
    usage();
  return result;
}

int main(int argc, char** argv) {
  if (argc != 7)
    usage();

  char* passwd = argv[1];
  char* salt = argv[2];
  char* N_str = argv[3];
  char* r_str = argv[4];
  char* p_str = argv[5];
  char* outlen_str = argv[6];

  unsigned long long N = parse(N_str);
  unsigned long long r = parse(r_str);
  unsigned long long p = parse(p_str);
  unsigned long long outlen = parse(outlen_str);

  uint8_t* result = malloc(outlen);
  if (result == NULL) {
    printf("malloc(%zu) failed.\n", (size_t)outlen);
    exit(1);
  }
  if (0 != crypto_scrypt((const uint8_t*)passwd, strlen(passwd),
                         (const uint8_t*)salt, strlen(salt),
                         N, r, p, result, outlen)) {
    printf("Failed\n");
    free(result);
    exit(1);
  }

  for (size_t i = 0; i < outlen; ++i)
    printf("%02x ", result[i]);
  printf("\n");

  free(result);
}
