/**
  @param passwd TypedArray
  @param salt TypedArray
  @param N integer
  @param r integer
  @param p integer
  @param outlen integer
  @return TypedArray of length outlen
*/
window['crypto_scrypt'] = function(passwd, salt, N, r, p, outlen) {
    r = r|0;
    p = p|0;
    outlen = outlen|0;
    var stack = Runtime.stackSave();
    try {
        var passwd_mem = Runtime.stackAlloc(passwd.length);
        writeArrayToMemory(passwd, passwd_mem);
        var salt_mem = Runtime.stackAlloc(salt.length);
        writeArrayToMemory(salt, salt_mem);
        var out_mem = Runtime.stackAlloc(outlen);
        var two_pow_32 = Math.pow(2, 32);
        var N_hi = Math.min(two_pow_32-1, Math.floor(N / two_pow_32));
        N_lo = N|0;
        var err = _crypto_scrypt(passwd_mem, passwd.length, salt_mem, salt.length,
                                 N_lo, N_hi, r, p,
                                 out_mem, outlen);
        if (err != 0) {
            throw new Error("crypto_scrypt(..., ..., " + N + ", " + r + ", " +
                            p + ", " + outlen + ") failed.");
        }
        var result = new Uint8Array(outlen);
        result.set(new Uint8Array(buffer, out_mem, outlen));
        return result;
    } finally {
        Runtime.stackRestore(stack);
    }
}
