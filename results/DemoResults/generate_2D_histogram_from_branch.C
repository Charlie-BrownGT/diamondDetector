void generate_2D_histogram_from_branch() {

    // Open the ROOT file
    TFile *file = TFile::Open("DDresults.root", "READ");

    // Check if the file was successfully opened
    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    // Get the TTree from the file (replace "Position" with the name of your tree)
    TTree *tree = (TTree*)file->Get("Position");
    if (!tree) {
        std::cerr << "TTree not found!" << std::endl;
        file->Close();
        return;
    }

    // Create a 2D histogram (300x300 bins, with ranges for both axes)
    TH2F *hist2d = new TH2F("Legend", "Diamond Detector Events Detected;X-axis (mm);Y-axis (mm)", 300, -5, 5, 300, -5, 5);

    // Set up variables to hold branch values
    double branch1_value, branch2_value;

    // Set branch addresses
    tree->SetBranchAddress("X", &branch1_value);  // Replace with branch name
    tree->SetBranchAddress("Y", &branch2_value);  // Replace with branch name

    // Loop over the entries in the tree and fill the histogram
    double nentries = tree->GetEntries();
    
    for (double i = 0; i < nentries; i++) {
        tree->GetEntry(i);
        hist2d->Fill(branch1_value, branch2_value);  // Fill the 2D histogram with the branch values
    }

    // Create a canvas
    TCanvas *canvas = new TCanvas("canvas", "Canvas Title", 800, 600);
    
    // Draw the 2D histogram
    hist2d->Draw("COLZ");  // "COLZ" adds color to represent bin content

    canvas->SaveAs("DD_2D_position.png");

    file->Close();
}

