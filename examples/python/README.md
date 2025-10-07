# Example Projects PYTHON using the API or HIDAPI
Samples for using the IO-Warrior with Python with the IowKit API or LibUSB/HIDAPI.


### Using IowKit API
For running these Pyhton examples you have to copy the iowkit.dll into the "includes" directory based on your Python version (x84 or x64).  
The iowkit.dll can ba found in "dll" directory in the main path.

### Using LibUSB / HIDAPI
You can use [libusb **hidapi**](https://github.com/libusb/hidapi/releases/tag/hidapi-0.15.0) to connect to the IO-Warrior.
To install the *hidapi* package, use **pip**:

```
pip install hidapi
```
The hidapi.dll and hidapi.lib can also be downloaded from Github (link above).  
After installation, copy hidapi.dll and hidapi.lib into your local Python installation directory, for example:

```
C:\Users\<Username>\AppData\Local\Programs\Python\Python312\Lib\site-packages\hidapi-*
```
to 
```
C:\Users\<Username>\AppData\Local\Programs\Python\Python312
```
