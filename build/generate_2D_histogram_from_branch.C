void generate_2D_histogram_from_branch(const char *dirname="/home/guy/software/geant4/geant4-v11.2.2-gdml-mt-install/projects/diamondDetector/build/", const char *ext=".root") {
	
	//setting up the file output names  
   	char pngFile[256]; // Adjust the size if needed
	char pngFile2[256];

	//used to get the file names with .root extension in current working directory
	const int MAX_FILES = 1000;
	TString* filenames[MAX_FILES];
	int file_count = 0;
	
	TSystemDirectory dir(dirname, dirname);
	TList *files = dir.GetListOfFiles();
	if (files) {
		TSystemFile *file;
		TString fname;
		TIter next(files);
		while ((file=(TSystemFile*)next())) {
			fname = file->GetName();
			if (!file->IsDirectory() && fname.EndsWith(ext)) {
				//cout << fname.Data() << endl;
				filenames[file_count] = new TString(fname);  //allocate and copy
                    		file_count++;	
			} 
		}
	}
	
	int strLength;
	char detStat[256];
	Long64_t nEntries;
	double testArr[1024];
	
	// Set up variables to hold branch values
	double branch1_value, branch2_value;

	for(int i = 0; i < file_count; i++){
	
		TFile *file = TFile::Open(filenames[i]->Data(), "READ");

		// Checking file and tree contents
		if (!file || file->IsZombie()) {
			std::cerr << "Error opening file!" << std::endl;
			return;
		}
		TTree *tree = (TTree*)file->Get("Position");
		if (!tree) {
			std::cerr << "TTree not found!" << std::endl;
			file->Close();
			return;
		}
		
		//finding and printing the total number of entries per tree here
		nEntries = tree->GetEntries();
		//std::cout << "Entry Number: " << nEntries << std::endl;
		
		//remove the .root suffix in the file name
		strcpy(detStat, filenames[i]->Data());
		//std::cout << detStat << std::endl;
		strLength = strlen(detStat);
		strLength = strLength - 5;
		detStat[strLength] = '\0';
		strcpy(pngFile, detStat);
		strcpy(pngFile2, detStat);
		std::cout << pngFile2 << std::endl;
		
		// Create a 2D histogram (1000x1000 bins, with ranges for both axes)
		TH2F *hist2d = new TH2F("hist2d", detStat, 50, -5, 5, 50, -5, 5);

		// Set branch addresses, replace with respective branch names
		tree->SetBranchAddress("X", &branch1_value);  
		tree->SetBranchAddress("Y", &branch2_value);  

		// Loop over the entries in the tree and fill the histogram
		for (Long64_t i = 0; i < nEntries; i++) {
			tree->GetEntry(i);
			hist2d->Fill(branch1_value, branch2_value);  // Fill the histogram 
		}

		// Create a canvas and draw histogram
		TCanvas *canvas = new TCanvas("canvas", "18Ne Observations over X and Y", 800, 600);
		hist2d->SetStats(0);
		hist2d->Draw("COLZ");

		TLegend *legend = new TLegend(0.6, 0.9, 1.0, 1.0);
		legend->AddEntry(hist2d, Form("Events: %.2lld", nEntries), "");
		legend->Draw();

		//the following is used to create the 1D angular distribution
		double yCounter; //used to count the number of events observed in the specified size gap on the crystal surface
		double xCounter; //used to breakup the crystal surface into determined segments
		int arrCounter = 0;

		int nPoints = 1000;
		double x_vals[nPoints], y_vals[nPoints];

		double xMin = -5.1, xMax = 5.1;
		double xPrec = (xMax - xMin) / nPoints;

		xCounter = xMin;

		while (xCounter < xMax){
			yCounter = 0; //resets the y count after each entry

			//loop used to count the number of y entries observed between x and x+xPrec
			for (Long64_t i = 0; i < nEntries; i++) {
				tree->GetEntry(i);
				if(branch1_value >= xCounter && branch1_value < xCounter + 0.1){
					yCounter++;
				}
			}
			//fills the observed events in y into testArr
			testArr[arrCounter] = yCounter;
			
			//creates seperate arrays for the plot
			x_vals[arrCounter] = xCounter;
			y_vals[arrCounter] = testArr[arrCounter];

			//iterates the while loop and xPrec
			xCounter = xCounter + xPrec;
			arrCounter++;
		}

		TGraph *graph = new TGraph(nPoints, x_vals, y_vals);
		graph->SetTitle(detStat);
		graph->GetXaxis()->SetTitle("Crystal surface X (mm)");
    	graph->GetYaxis()->SetTitle("Observations (N)");
		graph->SetMarkerStyle(20);   
		graph->SetMarkerSize(0.5);   
		graph->SetMarkerColor(kBlue);
		graph->SetLineWidth(3); 

		TCanvas *canvas2 = new TCanvas("canvas2", "Observations against Angular Distribution on X", 1000, 600);
    	graph->Draw("AP");

		strcat(pngFile, "2D.png");
		canvas->SaveAs(pngFile);
		delete canvas;

		strcat(pngFile2, "1D.png");
		canvas2->SaveAs(pngFile2);
		delete canvas2;

		file->Close();
	}
	
	// Print the filenames stored in the array and free memory used
	//std::cout << "Stored Filenames:" << std::endl;
	//for (int i = 0; i < file_count; i++) {
	//	delete filenames[i];
	//}
}

