import os
import shutil
import time

def copy_missing_files(parent_folder_path, child_folder_path):
    if not os.path.exists(parent_folder_path) or not os.path.isdir(parent_folder_path) or \
       not os.path.exists(child_folder_path) or not os.path.isdir(child_folder_path):
        print("Invalid folder paths. Please provide valid paths.")
        return

    start_time = time.time()  # Start the timer

    for file_name in os.listdir(parent_folder_path):
        source_file = os.path.join(parent_folder_path, file_name)
        dest_file = os.path.join(child_folder_path, file_name)

        if os.path.isfile(source_file) and not os.path.exists(dest_file):
            shutil.copy(source_file, dest_file)

    end_time = time.time()  # Stop the timer
    duration = end_time - start_time

    print("Missing files copied successfully!")
    print(f"Time taken: {duration:.2f} seconds.")

if __name__ == "__main__":
    parent_folder_path = "D:/FileCopier/parent"  # Replace with the actual parent folder path
    child_folder_path = "D:/FileCopier/child"    # Replace with the actual child folder path

    copy_missing_files(parent_folder_path, child_folder_path)
