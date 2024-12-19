import javax.crypto.Cipher;
import javax.crypto.spec.SecretKeySpec;
import java.nio.file.Files;
import java.nio.file.Paths;

public class SimpleFileEncryption {

    public static void main(String[] args) throws Exception {
        String inputFile = "input.txt";
        String encryptedFile = "encrypted.enc";
        String decryptedFile = "decrypted.txt";

        byte[] key = "1234567812345678".getBytes(); // Clave de 16 bytes
        encryptFile(inputFile, encryptedFile, key);
        decryptFile(encryptedFile, decryptedFile, key);
    }

    public static void encryptFile(String inputPath, String outputPath, byte[] key) throws Exception {
        byte[] data = Files.readAllBytes(Paths.get(inputPath));
        Cipher cipher = Cipher.getInstance("AES");
        SecretKeySpec secretKey = new SecretKeySpec(key, "AES");
        cipher.init(Cipher.ENCRYPT_MODE, secretKey);
        byte[] encryptedData = cipher.doFinal(data);
        Files.write(Paths.get(outputPath), encryptedData);
    }

    public static void decryptFile(String inputPath, String outputPath, byte[] key) throws Exception {
        byte[] encryptedData = Files.readAllBytes(Paths.get(inputPath));
        Cipher cipher = Cipher.getInstance("AES");
        SecretKeySpec secretKey = new SecretKeySpec(key, "AES");
        cipher.init(Cipher.DECRYPT_MODE, secretKey);
        byte[] decryptedData = cipher.doFinal(encryptedData);
        Files.write(Paths.get(outputPath), decryptedData);
    }
}
