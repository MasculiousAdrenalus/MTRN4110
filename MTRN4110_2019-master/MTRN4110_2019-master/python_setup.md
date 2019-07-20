For the vision part of mtrn4110 this year, we ask you to develop your algorithms in python 3 with opencv. This tutorial 
lists the necessary steps of installing python through anaconda, setting up conda virtual environment and installing required packages. 
We expect this tutorial to take about half an hour. Please tag all questions related to python setup with 'python setup' on moodle.

# Step 1: Installing [Anaconda](https://www.anaconda.com/distribution/#linux)
For vision part,  we recommend using the free Anaconda Python distribution, which provides an easy way for you to handle 
package dependencies. Please be sure to download the Python 3 version, which currently installs Python 3.7.

## Ubuntu:

```
wget https://repo.anaconda.com/archive/Anaconda3-2019.03-Linux-x86_64.sh
chmod +x Anaconda3-2019.03-Linux-x86_64.sh
sudo ./Anaconda3-2019.03-Linux-x86_64.sh
export PATH=/home/$NAME/anaconda3/bin:$PATH^C
```
## Windows:

Download .exe [file](https://repo.anaconda.com/archive/Anaconda3-2019.03-Windows-x86_64.exe) and install it.

Recommend to do: check 'Add Anaconda to my PATH environment variable' and also 'Register Anaconda with my .....'
If you are not doing this one, you will need to google how to add environment variable.

## MAC :

Download .pkg [file](https://repo.anaconda.com/archive/Anaconda3-2019.03-MacOSX-x86_64.pkg) and install it.

Recommend to do: check 'Add Anaconda to my PATH environment variable' and also 'Register Anaconda with my .....'
If you are not doing this one, you will need to google how to add environment variable.


# Step 2: Anaconda Virtual Environment
Once you have Anaconda installed, it makes sense to create a virtual environment for the course. 
If you choose not to use a virtual environment, it is up to you to make sure that all dependencies 
for the code are installed globally on your machine. 

## Ubuntu/Mac:

To set up a virtual environment, run (in a terminal)
```
conda create -n mtrn4110 python=3.6 (can be any version, depends on what version of python will 
                                     compile with your code or github repo)

```
to create an environment called mtrn4110.

Then, to activate and enter the environment, run
```
source activate mtrn4110
```
To exit, you can simply close the window, or run

```
source deactivate
```

## Windows:

To set up a virtual environment, run (in a cmd)
```
conda create -n mtrn4110 python=3.6 (can be any version, depends on what version of python will 
                                     compile with your code or github repo)

```
to create an environment called mtrn4110.

Then, to activate and enter the environment, run
```
conda activate mtrn4110
```
To exit, you can simply close the window, or run

```
conda deactivate
```

# Step 3: Installing Dependencies
First activate the virtual envinroment 'mtrn4110', and check whether you are using the correct 'pip' by running

## Ubuntu/MAC:
```
#run in terminal
which pip
```
which will give you '.../anaconda3/envs/mtrn4110/.../pip'

## Windows:
```
#run in cmd
pip --version
```
which will give you 'pip 19.0.3 from .....\AppData\Local\Continuum\anaconda3\lib\site-packages\pip (python 3.7)'

To install required dependecies, download the MTRN4110_2019 folder from github, 'cd' to the folder and run

```
pip install -r requirements.txt
```
# Step 4: Test Opencv

start python by typing 'python' in terminal(Ubuntu/MAC)/cmd(Windows), run
```
import cv2
print(cv2.__version__)
```
which gives you '3.4.3'

# Step 5: Jupyter Notebook

git clone the [repo](https://github.com/drliaowu/MTRN4110_2019) and change dir to the repo folder and run in terminal(Ubuntu/Mac)/cmd(Windows)
```
jupyter notebook
```
click the 'opencv_tutorial.ipynb' and run each section.

# Step 6: Run a python script
In terminal(Ubuntu/Mac)/cmd(Windows), change directory to the location of your python script, run
```
python [script_name].py
```

