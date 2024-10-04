void generate_2D_histogram_from_branch(const char *dirname="/home/guy/software/geant4/geant4-v11.2.2-gdml-mt-install/projects/diamondDetector/results/beamAngle/", const char *ext=".root") {

	//setting up the file output names  
   	char pngFile[256]; // Adjust the size if needed
	
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
	
	// Open the ROOT file
	
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
		
		char detStat[256];
		strcpy(detStat, filenames[i]->Data());
		std::cout << detStat << std::endl;
		
		strcpy(pngFile, detStat);
		
		// Create a 2D histogram (1000x1000 bins, with ranges for both axes)
		TH2F *hist2d = new TH2F("Legend", detStat, 1000, -50, 50, 1000, -50, 50);

		// Set up variables to hold branch values
		double branch1_value, branch2_value;

		// Set branch addresses, replace with respective branch names
		tree->SetBranchAddress("X", &branch1_value);  
		tree->SetBranchAddress("Y", &branch2_value);  

		// Loop over the entries in the tree and fill the histogram
		double nentries = tree->GetEntries();

		for (double i = 0; i < nentries; i++) {
			tree->GetEntry(i);
			hist2d->Fill(branch1_value, branch2_value);  // Fill the histogram 
		}

		// Create a canvas and draw histogram
		TCanvas *canvas = new TCanvas("canvas", "21Na Observations over X and Y", 800, 600);
		hist2d->Draw("COLZ");
		
		strcat(pngFile, ".png");
		
		canvas->SaveAs(pngFile);
		file->Close();
	}
	
	// Print the filenames stored in the array and free memory used
	std::cout << "Stored Filenames:" << std::endl;
	for (int i = 0; i < file_count; i++) {
		//std::cout << filenames[i]->Data() << std::endl;
		delete filenames[i];
	}
}

