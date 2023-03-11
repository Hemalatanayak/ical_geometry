# Codes for generating simplified geometries of the ICAL and mICAl detector of the India-based Neutrino Observtory

##  ICAL Geometry
ICAL stands for Iron calorimeter proposed by INO to study interactions of the neutrino and antineutrinos. 
The original ICAL geometry setup consists of 3 modules with each module having 151 iron layers of dimension 16 m x 16 m x 5.6 cm and 2 m x 2 m Resistive Plate Chambers (RPCs) sandwiched between the two iron plates. All the modules are magnetized with a maximum field of 1.5 T. 

In this ROOT-based code, a simplified geometry of the ICAL is created for use in fast simulation studies and benchmarking. The main simplifications are:

* The RPCs are replaced by thin glass plates with no strips or gas volumes. 
* Instead of many single 2 m x 2 m RPCs in a given layer, a single 16 m x 16 m glass plate is placed.
* No coils are placed in the geometry
* The magnetic field description is not given

The dimension of the elements in the simplified geometry is as follows:
*   Iron plate:     16 m x 16 m x 5.6 cm
*   Glass plate:    16 m x 16 m x 0.001 cm
*   Gap between iron plates: 4 cm
*   Distance between RPC and iron plate boundary (both top and bottom): 2 cm
*   Number of layers: 151

|-------------------------- IRON PLATE 16 m x 16 m x 5.6 cm ---------------------------------------|

|---------------------------2 cm AIR GAP ---------------------------------------------------------------------|


|-------------------------- GLASS PLATE 16 m x 16 m x 0.001 cm ---------------------------------|

|---------------------------2 cm AIR GAP ---------------------------------------------------------------------|


|-------------------------- IRON PLATE 16 m x 16 m x 5.6 cm ---------------------------------------|

Repeat above structure to get 151 iron plates and 150 glass plates.



## mICAL Geometry
mICAL detector is a prototype version of the ICAL detector with only 11 layers and a smaller dimension. The dimensions for iron plates is 2 m x 2 m x 5.6 cm and  2 m x 2 m x 0.001 cm for the glass plates. The gap between two iron plates is set at 4.5 cm.

## Usage Instructions
- Required: ROOT version 6
- on the command line type  **root ical_geometry.C** to get the ical_geometry.gdml and ical_geometry.root files
- To get the mICAL geometry, repeat the same with **mini_ical_geometry.C**
- To view the geometry, one can open the root files on the root terminal:
    - on the linux command type: root
    - Once the root terminal is opened type: TBrowser th
    - On the browser, click on the ROOT file to view the geometry.
## Last update: 12 March 2023