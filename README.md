**AR Pharmacist - Utilities**

*We recommend that you open this README and document yourself about the steps you need to take to run this project.*

---

## Downloading everything you need

1. Download the following dependencies at the ***"Development Libraries"*** section:
    -   [SDL2.0](https://www.libsdl.org/download-2.0.php) 
    -   [SDL2_image](https://www.libsdl.org/projects/SDL_image)
    -   [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf)
2. Unzip all the libraries into the directories SDL, SDL2_Image and SDL2_TTF found in the External_Dependencies directory.
3. Open a new **Visual Studio Empty Project in C++** build it and put all the files from this project into the right place.

---

## Getting ready to run the generator project

Next, you’ll configure your project.

1. Go to **Project -> <Project_Name> Properties**
2. After the window opens you need to follow these steps:
    -   Set **Configuration** to *All Configurations* (Only if you need the project dependencies to match with the Debug configuration and Release too).
    -   Set **Platform** to *All Platforms* (Only if you need the project dependencies to match with the x64 configuration and x86 configuration too).
    -   Then go to **Configuration Properties -> VC++ Directories** section and do the following:
        -   Select **Edit** on the *Include Directories* field and add the following:
            -   $(SolutionDir)\External_Dependencies\SDL\SDL2-2.0.10\include
            -   $(SolutionDir)\\External_Dependencies\SDL2_Image\SDL2_image-2.0.5\include
            -   $(SolutionDir)\External_Dependencies\SDL2_TTF\SDL2_ttf-2.0.15\include
        -   Select **Edit** on the *Library Directories* field and add the following (at the end of each lib you must **choose the platform you're working with *(x86/x64)***):
            -   $(SolutionDir)\External_Dependencies\SDL\SDL2-2.0.10\lib\ 
            -   $(SolutionDir)\External_Dependencies\SDL2_Image\SDL2_image-2.0.5\lib\
            -   $(SolutionDir)\External_Dependencies\SDL2_TTF\SDL2_ttf-2.0.15\lib\
    -   After all previous steps have been completed, you need to include in the **Linker -> Input -> Additional Dependencies** the following (just write them after you click *Edit*):
        -   SDL2.lib
        -   SDL2main.lib
        -   SDL2_image.lib
        -   SDL2_ttf.lib
3. After making your changes, click the button *OK* OR *Apply*.
4. Now you're good to go.

Now, before we go to the next step, build your project.

5. Add all .dll files into your build folder (You can find the .dll in the lib folder from each folder in External_Dependencies).

---

## Some rules before running the project

Use these steps rules if you want your project to be build correctly. These rules are kinda essential if you want a project without errors.

1. Before downloading any font style, make sure the format is .ttf, .otf or .fon
2. Create a directory with a suggestive name of the font in the <Project_Name>\<Project_Name>\Fonts directory. 
3. Unzip the downloaded font into that directory.
4. This is the format of the input: | File_Name + Lowercase extension | (Ex: Arial.ttf).
5. You can find that file in the Resources directory (Same path as in step 2).
6. All the generated data is saved in the Dataset directory in .bmp format.