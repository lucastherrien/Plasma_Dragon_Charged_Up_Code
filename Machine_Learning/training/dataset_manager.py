import os
import shutil
import tkinter as tk
from PIL import Image, ImageTk
from pillow_heif import register_heif_opener

register_heif_opener()

# Function to move the image to the specified folder
def move_image(image_path, folder_path):
    filename = os.path.basename(image_path)
    destination = os.path.join(folder_path, filename)
    shutil.move(image_path, destination)
    print(f"Moved {filename} to {folder_path}")

# Function to display the image and create buttons
def display_image(image_path, folder1_path, folder2_path):
    # Create the main window
    window = tk.Tk()
    window.title("Image Sorting")

    # Load and display the image
    image = Image.open(image_path)
    image = image.resize((300, 300))  # Adjust the size as needed
    photo = ImageTk.PhotoImage(image)
    label = tk.Label(window, image=photo)
    label.pack()

    # Function to handle button clicks
    def button_click(folder_path):
        move_image(image_path, folder_path)
        window.destroy()

    # Create two buttons
    button1 = tk.Button(window, text="Cube", command=lambda: button_click(folder1_path))
    button1.pack(side=tk.LEFT, padx=10)

    button2 = tk.Button(window, text="Non-cube", command=lambda: button_click(folder2_path))
    button2.pack(side=tk.RIGHT, padx=10)

    # Run the main event loop
    window.mainloop()

# Function to iterate over images in the folder
def process_images(image_folder, folder1_path, folder2_path):
    # Iterate over each image in the folder
    for filename in os.listdir(image_folder):
        if filename.endswith(".jpg") or filename.endswith(".png"):  # Adjust the extensions as needed
            image_path = os.path.join(image_folder, filename)
            display_image(image_path, folder1_path, folder2_path)

# Usage example
image_folder = "C:\\Users\\lucas\\Documents\\MiniFRC9Images\\Unsorted"
folder1_path = "C:\\Users\\lucas\\Documents\\MiniFRC9Images\\Cube"
folder2_path = "C:\\Users\\lucas\\Documents\\MiniFRC9Images\\Non-Cube"

process_images(image_folder, folder1_path, folder2_path)