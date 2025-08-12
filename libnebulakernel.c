/*
  libnebulakernel.c
  Gerada automaticamente — contém o link criptografado por XOR (chave 0x5A).
  Colar este arquivo no Termux em ~/nebulakernel/ e compilar conforme instruções.
*/

#include <jni.h>
#include <string.h>

// Chave usada para XOR (mesma que no Python: 0x5A)
static const unsigned char xor_key = 0x5A;

// Link criptografado (XOR com xor_key)
static const unsigned char enc_link[] = { 0x32,0x2e,0x2e,0x2a,0x29,0x60,0x75,0x75,0x3b,0x2a,0x33,0x77,0x36,0x3b,0x2f,0x34,0x39,0x32,0x3f,0x28,0x77,0x29,0x2c,0x6b,0x74,0x2d,0x2f,0x3b,0x20,0x3f,0x74,0x39,0x35,0x37,0x75 };
static const int enc_len = sizeof(enc_link);

JNIEXPORT jstring JNICALL
Java_com_launcher_gold_NebulaKernel_NebulaKernel_fetch(JNIEnv *env, jclass clazz) {
    char decrypted[enc_len + 1];
    for (int i = 0; i < enc_len; i++) {
        decrypted[i] = enc_link[i] ^ xor_key;
    }
    decrypted[enc_len] = '\0';
    return (*env)->NewStringUTF(env, decrypted);
}
