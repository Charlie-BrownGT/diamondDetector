// Macro to modify title, axis names, and legend of a histogram in a ROOT file
void modify_histogram() {
    // Open the ROOT file
    TFile *file = TFile::Open("DDresults.root", "UPDATE");
    
    // Check if the file was opened successfully
    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }
    
    // Get the histogram from the file
    TH1F *hist = (TH1F*)file->Get("Position"); // Replace "histogram_name" with the actual name of your histogram

    // Check if the histogram exists
    if (!hist) {
        std::cerr << "Histogram not found!" << std::endl;
        file->Close();
        return;
    }

    // Set new axis titles
    hist->GetXaxis()->SetTitle("New X-axis Title");
    hist->GetYaxis()->SetTitle("New Y-axis Title");

    // Set new plot title
    hist->SetTitle("New Plot Title");

    // Create a legend
    TLegend *legend = new TLegend(0.6, 0.7, 0.9, 0.9); // Coordinates for the legend (x1, y1, x2, y2)
    legend->AddEntry(hist, "Legend Entry", "l"); // "l" for line; could use "p" for points, etc.

    // Create a canvas to draw the histogram
    TCanvas *canvas = new TCanvas("canvas", "Canvas Title", 800, 600);

    // Draw the histogram
    hist->Draw();

    // Draw the legend
    legend->Draw();

    // Save the canvas as a PNG image
    canvas->SaveAs("modified_histogram.png");

    // Close the file
    file->Close();
}

