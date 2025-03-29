import os
import numpy as np
from stl import mesh

def calculate_volume(stl_file):
    model = mesh.Mesh.from_file(stl_file)
    volume = 0.0
    for i in range(len(model.vectors)):
        v1, v2, v3 = model.vectors[i]
        volume += np.dot(v1, np.cross(v2, v3))
    return abs(volume) / 6.0

def average_stl_volume(directory):
    stl_files = [f for f in os.listdir(directory) if f.endswith('.stl')]
    if not stl_files:
        print("No STL files found in the directory.")
        return

    total_volume = 0.0
    for stl_file in stl_files:
        volume = calculate_volume(os.path.join(directory, stl_file))
        print(f"{stl_file}: {volume:.2f} cubic units")
        total_volume += volume

    average_volume = total_volume / len(stl_files)
    print(f"\nAverage Volume: {average_volume:.2f} cubic units")

if __name__ == "__main__":
    folder_path = input("Enter the folder path containing STL files: ")
    average_stl_volume(folder_path)
