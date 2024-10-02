// Macro to generate histograms from branches in a ROOT file
void generate_histogram_from_branch() {
    // Open the ROOT file
    TFile *file = TFile::Open("DDresults.root", "READ");

    // Check if file was successfully opened
    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    // Get the TTree from the file (replace "tree_name" with your actual tree name)
    TTree *tree = (TTree*)file->Get("Position");
    if (!tree) {
        std::cerr << "TTree not found!" << std::endl;
        file->Close();
        return;
    }

    // Option 1: Simple method - Use TTree::Draw to draw and generate a histogram directly
    // This command will automatically create and draw a histogram from the specified branch.
    //tree->Draw("X");  // Replace "branch_name" with the actual branch name

    // Option 2: More control - Create a custom histogram manually
    // Define the histogram (specify name, title, bins, and range)
    TH1F *hist = new TH1F("hist", "Histogram Title;X-axis Title;Y-axis Title", 100, -5, 5);

    // Fill the histogram by looping over the entries in the tree and retrieving the branch data
    double branch_value;
    tree->SetBranchAddress("X", &branch_value);  // Replace "branch_name" with the actual branch name

    // Loop over the entries in the tree
    double nentries = tree->GetEntries();
    for (double i = 0; i < nentries; i++) {
        tree->GetEntry(i);
        hist->Fill(branch_value);
    }

    // Create a canvas to draw the histogram
    TCanvas *canvas = new TCanvas("canvas", "Canvas Title", 800, 600);
    
    // Draw the histogram
    hist->Draw();

    // Save the canvas as an image (PNG format)
    canvas->SaveAs("branch_histogram.png");

    // Close the file
    file->Close();
}

