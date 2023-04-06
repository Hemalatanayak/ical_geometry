//---NOTE
//This is a ICAL Geometry setup consisting of 151 iron layers and 150 glass layers.
//The dimension of Iron layer is 16m*16m*5.6cm .
//The dimension of Glass layer is given by 16m*16m* 0.001cm.
//The inter layer gap is 4cm .So the gap between an iron and glass layer is 2cm.
//Iron layer has been placed at the top.
 // \author Hemalata Nayak
#include "TGeoManager.h"
#include "TGeoMaterial.h" 
#include "TGeoMedium.h"
#include "TGeoVolume.h" 
#include "TGeoBBox.h" 
#include "TGeoCompositeShape.h" 
#include "TGeoBoolNode.h" 
#include "TGeoPhysicalNode.h" 
#include "TGeoMatrix.h"
// #include "TGeoMagneticField.h"


void ical_geometry(bool vis = true)
{
   
   TGeoManager *geom = new TGeoManager("ical_geometry", "ical_geometry");

//    //--- define some materials
   TGeoMaterial *matAir = new TGeoMaterial("Air", 1,1,0.001205);
   TGeoMaterial *matIron = new TGeoMaterial("Iron", 55.85,26,7.87);
   TGeoMaterial *matGlass = new TGeoMaterial("Glass", 28.09,14,2.5);

//    //--- define media
   TGeoMedium *Air = new TGeoMedium("Air",1, matAir);
   TGeoMedium *Iron = new TGeoMedium("Iron",2, matIron);
   TGeoMedium *Glass = new TGeoMedium("Glass",3, matGlass);
//   // All Units in cm
 
   //--- make the top World volume //---All units are in cm
   Double_t worldx = 810.;
   Double_t worldy = 810.;
   Double_t worldz = 730.;
   TGeoVolume *top = geom->MakeBox("TOP", Air , worldx, worldy, worldz);
   geom->SetTopVolume(top);
   // geom->SetVisibility(kFALSE);

   // half-thickness of objects in the geometry
   Double_t rpcDim = 800; // cm
   Double_t ironThickness = 2.8; //cm
   Double_t glassThickness = 0.00005; // cm (proxy for RPC, only used for position and time sensing)
   
   Double_t inter_layer_gap = 4;//cm
   int nlayers = 151;

   //---Creating Iron layers

   TGeoVolume *IRON = geom->MakeBox("IRON", Iron, rpcDim, rpcDim, ironThickness);
   IRON->SetLineColor(kBlue);
   IRON->SetTransparency(0.9);
   // top->AddNode(IRON,1, new TGeoTranslation(0, 0, 2.8));
 
   for(int i=0;i<nlayers;i++){
   Double_t layerPosition=(((ironThickness*2)+inter_layer_gap+(glassThickness*2))*i);
   top->AddNode(IRON,i+1, new TGeoTranslation(0, 0,-715+layerPosition ));
   }


   
   //---Creating Glass layers

   TGeoVolume *GLASS = geom->MakeBox("GLASS", Glass, rpcDim, rpcDim, glassThickness);
   GLASS->SetLineColor(kRed);
   GLASS->SetTransparency(0.9);
   // top->AddNode(GLASS,1, new TGeoTranslation(0, 0, -2.1));
   
   for(int i=0;i<(nlayers-1);i++){
   Double_t glasslayerPosition=(((ironThickness*2)+inter_layer_gap+(glassThickness*2))*i)+(ironThickness+(inter_layer_gap/2));
    top->AddNode(GLASS,i+1, new TGeoTranslation(0, 0,-715+glasslayerPosition ));
   }



   geom->CloseGeometry();
   geom->Export("ical_geometry.root");
   geom->Export("ical_geometry.gdml");
   // disable sections to save only part of geometry

   //--- draw the ROOT box.
   // by default the picture will appear in the standard ROOT TPad.
   //if you have activated the following line in system.rootrc,
   //it will appear in the GL viewer
   //#Viewer3D.DefaultDrawOption:   ogl

   geom->SetVisLevel(4);
   if (vis) top->Draw("ogle");
}