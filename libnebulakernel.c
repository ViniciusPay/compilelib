#include <jni.h>
#include <string.h>
#include <stdlib.h>

static const unsigned char xor_key = 0x5A;

// Coloque aqui o link original, sem criptografia
static const char plain_link[] = "https://api-launcher-sv1.wuaze.com/";

JNIEXPORT jstring JNICALL
Java_com_launcher_gold_NebulaKernel_fetch(JNIEnv *env, jclass clazz) {
    int len = strlen(plain_link);
    unsigned char *encrypted = (unsigned char*) malloc(len + 1);
    if (!encrypted) return NULL;

    // Criptografa o link
    for (int i = 0; i < len; i++) {
        encrypted[i] = plain_link[i] ^ xor_key;
    }
    encrypted[len] = '\0';

    // Descriptografa pra entregar o texto limpo
    char *decrypted = (char*) malloc(len + 1);
    if (!decrypted) {
        free(encrypted);
        return NULL;
    }
    for (int i = 0; i < len; i++) {
        decrypted[i] = encrypted[i] ^ xor_key;
    }
    decrypted[len] = '\0';

    free(encrypted);

    jstring result = (*env)->NewStringUTF(env, decrypted);
    free(decrypted);
    return result;
}
