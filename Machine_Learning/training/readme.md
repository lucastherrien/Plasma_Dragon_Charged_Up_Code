Steps to train cube model:
1. Clone the repo
2. Download the dataset from https://drive.google.com/drive/folders/1hrCZ8V6udx6lLqymtly-iNwmJtFiwKax
(click where it says Plasma_Dragon_Cube_dataset and select download on the drop down menu)
3. Extract all on the downloaded zip file, go in the extracted folder, copy the folder labeled Plasma_Dragon_Cube_dataset.
4. Paste that folder into this folder
5. Open the dataset maker notebook, follow the instructions provided there.
6. Open the train notebook, run all the cells in order and make sure to change all the filepaths that need to be changed
7. (Optional, Pico4ML hardware required for utilization beyond this point) Convert the tensorflow .h5 model to a tflite file with the following command
edit bashed on your environment
```bash
C:/Users/lucas/AppData/Local/Programs/Python/Python39/python.exe c:/Users/lucas/Documents/GitHub/mliot-hw2-lucastherrien/tf_lite_converter.py best_model.h5
```
8. See embedded section (WIP) for use on Pico4ML
