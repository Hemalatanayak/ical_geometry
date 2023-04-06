 //---NOTE
//This is a MINI_ICAL Geometry setup consisting of 11 iron layers and 10 glass layers.
//The dimension of Iron layer is 2m*2m*5.6cm .
//The dimension of Glass layer is given by 2m*2m* 6mm.
//The inter layer gap is 4.5 cm .So the gap between an iron and glass layer is 2.25cm.
//Iron layer has been placed at the top.
 // \author Hemalata Nayak
void mini_ical_geometry(bool vis = true)
{
   // gStyle->SetCanvasPreferGL(true);
   TGeoManager *geom = new TGeoManager("mini_ical_geometry", "mini_ical_geometry");

//    //--- define some materials
   TGeoMaterial *matAir = new TGeoMaterial("Air", 1,1,0.001205);
   TGeoMaterial *matIron = new TGeoMaterial("Iron", 55.85,26,7.87);
   TGeoMaterial *matGlass = new TGeoMaterial("Glass", 28.09,14,2.5);

//    //--- define media
   TGeoMedium *Air = new TGeoMedium("Air",1, matAir);
   TGeoMedium *Iron = new TGeoMedium("Iron",2, matIron);
   TGeoMedium *Glass = new TGeoMedium("Glass",3, matGlass);
//   // All Units in cm
   Double_t Field = 1.5 ;// tesla
   // TGeoUniformMagField *magField = new TGeoUniformMagField(0,Field,0);


   //--- make the top World volume //---All units are in cm
   Double_t worldx = 125.;
   Double_t worldy = 125.;
   Double_t worldz = 60;
   TGeoVolume *top = geom->MakeBox("TOP", Air , worldx, worldy, worldz);
   geom->SetTopVolume(top);
   geom->SetVisibility(top, kTRUE);

   // half-thickness of objects in the geometry
   Double_t rpcDim = 100; // cm
   Double_t ironThickness = 2.8; //cm
   Double_t glassThickness = 0.00005; // cm (proxy for RPC, only used for position and time sensing)
   
   Double_t inter_layer_gap = 4.5;//cm
   int nlayers = 11;

   //Creating Iron layers

   TGeoVolume *IRON = geom->MakeBox("IRON", Iron, rpcDim, rpcDim, ironThickness);
   IRON->SetLineColor(kBlue);
   IRON->SetTransparency(0.9);
   // TGeoUniformMagField *magField = new	TGeoUniformMagField(0.,-2.0,0.);
   // IRON->SetField(magField);
   // top->AddNode(IRON,1, new TGeoTranslation(0, 0, 2.8));
  
   for(int i=0;i<nlayers;i++){
   Double_t layerPosition=(((2*ironThickness)+inter_layer_gap+(2*glassThickness))*i);
   top->AddNode(IRON,i+1, new TGeoTranslation(0, 0,-50+layerPosition ));
   }


   
   //Creating Glass layers
   TGeoVolume *GLASS = geom->MakeBox("GLASS", Glass, rpcDim, rpcDim, glassThickness);
   GLASS->SetLineColor(kRed);
   GLASS->SetTransparency(0.9);
   // top->AddNode(GLASS,1, new TGeoTranslation(0, 0, -2.1));
   for(int i=0;i<(nlayers-1);i++){
   Double_t glasslayerPosition=(((2*ironThickness)+inter_layer_gap+(2*glassThickness))*i)+(ironThickness+(inter_layer_gap/2));
    top->AddNode(GLASS,i+1, new TGeoTranslation(0, 0,-50+glasslayerPosition ));
   }

//    TGeoVolume *botGlass = geom->MakeBox("BOTGLASS", Vacuum, rpcDim, rpcDim, glassThickness);
//    top->AddNode(botGlass,1, new TGeoTranslation(0, 0, -gasGap-2));
//    botGlass->SetTransparency(0.9);
//    botGlass->SetLineColor(kRed);
   

   geom->CloseGeometry();
   geom->Export("mini_ical_geometry.root");
   geom->Export("mini_ical_geometry.gdml");
   // disable sections to save only part of geometry

   //--- draw the ROOT box.
   // by default the picture will appear in the standard ROOT TPad.
   //if you have activated the following line in system.rootrc,
   //it will appear in the GL viewer
   //#Viewer3D.DefaultDrawOption:   ogl

   geom->SetVisLevel(4);
   if (vis) top->Draw("ogle");
}