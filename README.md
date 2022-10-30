# **Mandelbrotset** 
This program calculates the Mandelbrot set on the GPU in a specific fragment shader. To keep the project short and simple I used SFML for all the window management and other stuff.  
![low iteration amount](https://user-images.githubusercontent.com/79220215/198892900-eb640231-19c5-43ea-9c6c-704b530d9a9a.png) 
![close up view](https://user-images.githubusercontent.com/79220215/198892917-c6773681-01e9-42c6-9449-d2f38dc19566.png) 
# **How to build?** 
If you don't want to build it on your own, you can download the latest release for windows on github. 
If you want to have the newest version available, you must probably build it on your own. <br /> 
### What do you need? 
You should have a c++ compiler, git and cmake on your computer to follow the steps below. 
Run these commands in the terminal: <br /> 
first download the source code 
`git clone https://github.com/itsLeatch/Mandelbrotset.git --recursive` <br /> 
Create a directory build and go into it 
`mkdir build` 
`cd build` <br /> 
Now run cmake on the directory above 
`cmake ..` <br />
finaly compile everything with 
`cmake --build .` <br /> 
The binary should be in the bin folder one directory above. 
# **How to use it?** 
- use Key Q to lower the iterations 
- use Key E to increase the iterations 
- hold the left mouse button and move to look around 
# **Known issues** 
- low zoom levels because of the limited amount of uniform interpolations 
- judder movement when zooming in, because of the limited accuracy of double values 
- bad performance 
