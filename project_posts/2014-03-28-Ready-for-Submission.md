This is some document for competition Judging Panel

I hope it is useful for someone who try this.



## Final artworks files
As a risk management, I uploaded two versions for the final submission. One is for installation with sensor unit, the other is standalone desktop version.

 - [Installation with laser sensor](https://github.com/fladdict/devart-template/tree/master/project_code/openframeworks/TheGiantMap) May not work without sensor unit. 
 - [Desktop Demo](https://github.com/fladdict/devart-template/tree/master/project_code/openframeworks/TheGiantMap_without_sensor) Stable and good for desktop judging environment. [Excutable Demo](https://dl.dropboxusercontent.com/u/262233/the_giant_map_executable_desktop_standalone.zip).


## Work and Build Environment
 - Program is made with Macbook pro 2013.
 - Openframeworks 0.8.
 - XCode 5.0 or later
 - All libraries are included into project (I wish).
 - For unknown reason you need to build project twice to make it stable.
  - Build project with setting Build Phases' Copy Files Destination as Frameworks.
  - Build project again with setting Build Phases' Copy Files Destination as Executables.

## Issues to Know

 - App is made with Openframeworks 0.8, to complie it place the folder inside openframeworks app folder.
 - My friend reported that shader doesn't work with Macbook Air. (I think shader version issue), it works on Macbook Pro 2013.
 
 
##Shortcut for debug and tuning.
 
  - Tab: Shows setting panel
  - 0-9: Location shortcut.
  - C: Screen capture.
  - S: Save Settings
  - L: Load Settings
  - R: Remove all particles
  - W: Wireframe debug mode
  - +: Zoom In
  - -: Zoom Out


## Future TODO after competition
 
 - Push embedded params and strings to external settings file.
 - More sound effect management.
 - GUI for Laser Unit position configulation for installation.
 - Auto restart and setup script for installation.
 - VNC or other remote desktop setup for installation risk management.
 - Setup document for installation stuff for risk management.
