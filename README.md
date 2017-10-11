# Edu-hoc project

Edu-hoc project is an educational platform for ad-hoc networking with a focus on wireless sensor networks and security of these. It aims to provide easy to use environment for anyone interested, but with minimal experience in the area of an ad-hoc network, since these tend to have rather a specific approach to problems like routing, encryption etc. 

The project will supply various working examples of code for individual nodes, exercises for practising various security primitives and on the server side capability to easily manage upload to every node in the network. 

## Technical details

Edu-hoc consists of example apps and various scenarios, these can be found in src (scr/scenarios) folder. 

For mass deployment on the network is used JeeTool, which can be found in the corresponding repository (linked as git submodule) and also BareArduinoProject, which enables use of make and other convenient things (also Linked as Git submodule)

Project is currently using Arduino-compatible hardware for physical realisation of network, and ease of use is ensured with use of Bare-Arduino-Project for installation instructions and other issues regarding this part of project please refer to: https://github.com/ladislas/Bare-Arduino-Project  

JeeLib advanced setup guide can be found at: http://tools.jeelabs.org/rfm12b.html

## Licencing

The project is developed at the [Centre for Research on Cryptography and Security, Masaryk University, Brno, Czech Republic](http://crcs.cz). It's licensed under MIT licence, see the file in the repository root. The project uses some third party code as documented in the following list:
* **Bare-Arduino-Project** developed by Ladislas de Toldi under MIT license, details to this project can be found in corresponding git submodule.  
* **RF12 library** developed by JeeLabs under MIT licence, details for this library can be found here [JeeLabs RF12](http://jeelabs.net/projects/jeelib/wiki)
