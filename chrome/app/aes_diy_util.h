#ifndef CHROME_APP_AES_DIY_UITL_H_
#define CHROME_APP_AES_DIY_UITL_H_

#include "base/base64.h"
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/rand.h>


void decrypt_aes_cbc(const uint8_t* encrypted_text,
                     int encrypted_text_len,
                     const uint8_t* key,
                     uint8_t* iv,
                     uint8_t* decrypted_text) {
  AES_KEY aes_key;
  AES_set_decrypt_key(key, 128, &aes_key);
  AES_cbc_encrypt(encrypted_text, decrypted_text, encrypted_text_len, &aes_key,
                  iv, AES_DECRYPT);
}

std::string diyDecrypted(const std::string& encrypted_text,const std::string& aesKey) {
    absl::optional<std::vector<uint8_t>> decodedData = base::Base64Decode(encrypted_text);
    if (!decodedData.has_value()) {
        return "";
    }
    std::vector<uint8_t>  data=decodedData.value();
    std::vector<uint8_t> iv(data.begin(), data.begin() + 16);
    std::vector<uint8_t> uencrypted_text(data.begin() + 16, data.end());
    const uint8_t* key = reinterpret_cast<const uint8_t*>(aesKey.data());

 
    
    std::vector<uint8_t> decrypted_text(uencrypted_text.size());

    decrypt_aes_cbc(uencrypted_text.data(), uencrypted_text.size(), key, iv.data(), decrypted_text.data());
    std::string decrypted_string(reinterpret_cast<char*>(decrypted_text.data()), uencrypted_text.size());


    return decrypted_string;
}

std::vector<uint8_t> pKCS5Padding(const std::vector<uint8_t>& ciphertext, int blockSize) {
    int padding = blockSize - ciphertext.size() % blockSize;
    std::vector<uint8_t> padText(padding, static_cast<uint8_t>(padding));
    std::vector<uint8_t> paddedCiphertext = ciphertext;
    paddedCiphertext.insert(paddedCiphertext.end(), padText.begin(), padText.end());
    return paddedCiphertext;
}

std::string diyEncrypt(const std::string& text, const std::string& aesKey) {
  
        const uint8_t* key = reinterpret_cast<const uint8_t*>(aesKey.data());

        // Generate a random IV (Initialization Vector)
        uint8_t iv[AES_BLOCK_SIZE];
        RAND_bytes(iv, AES_BLOCK_SIZE);

        // Convert the input text to uint8_t vector
        std::vector<uint8_t> plaintext = pKCS5Padding(std::vector<uint8_t>(text.begin(), text.end()), AES_BLOCK_SIZE);
        
        int plaintext_len = plaintext.size();

        std::vector<uint8_t> ciphertext(plaintext_len + AES_BLOCK_SIZE);

        // Copy the IV to the beginning of the ciphertext
        std::copy(iv, iv + AES_BLOCK_SIZE, ciphertext.begin());

        // Create AES context with PKCS5Padding
        AES_KEY aes_key;
        AES_set_encrypt_key(key, 128, &aes_key);

        // Encrypt the plaintext using AES in CBC mode with PKCS5Padding
        AES_cbc_encrypt(plaintext.data(), &ciphertext[AES_BLOCK_SIZE],
                        plaintext_len,
                        &aes_key, iv, AES_ENCRYPT);

        // Convert the ciphertext to a base64-encoded string
        std::string reStr = base::Base64Encode(ciphertext);
        return reStr;
    
}
#endif  // CHROME_APP_AES_DIY_UITL_H_