import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.StandardCopyOption;

public class FileCopier {
    public static void main(String[] args) {
        String parentFolderPath = "D:\\FileCopier\\parent"; // Replace with the actual parent folder path
        String childFolderPath = "D:\\FileCopier\\child"; // Replace with the actual child folder path

        long startTime = System.currentTimeMillis(); // Start the timer

        copyMissingFiles(parentFolderPath, childFolderPath);

        long endTime = System.currentTimeMillis(); // Stop the timer
        long duration = endTime - startTime;

        System.out.println("Missing files copied successfully!");
        System.out.println("Time taken: " + duration + " milliseconds.");
    }

    private static void copyMissingFiles(String parentFolderPath, String childFolderPath) {
        File parentFolder = new File(parentFolderPath);
        File childFolder = new File(childFolderPath);
        if (parentFolder.exists() && parentFolder.isDirectory() && childFolder.exists() && childFolder.isDirectory()) {
            File[] filesInParent = parentFolder.listFiles();
            if (filesInParent != null) {
                for (File file : filesInParent) {
                    if (file.isFile()) {
                        File destFile = new File(childFolder, file.getName());
                        if (!destFile.exists()) {
                            try {
                                Files.copy(file.toPath(), destFile.toPath(), StandardCopyOption.REPLACE_EXISTING);
                            } catch (IOException e) {
                                e.printStackTrace();
                            }
                        }
                    }
                }
            }
        }
    }
}
