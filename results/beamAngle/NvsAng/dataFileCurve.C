void dataFileCurve()
{
	TCanvas *c1 = new TCanvas("c1", "Incident Particles vs Angular Beam Spread", 800, 600);
	
	std::vector<const char*> fileNames = {"DDOn.txt", "IDOn.txt", "IDDDOn.txt",  "allDetsOn.txt"};
	std::vector<TGraph*> graphs;

	for (size_t i = 0; i < fileNames.size(); ++i) {
		std::ifstream inFile(fileNames[i]);

		// Check if the file is open
		if (!inFile.is_open()) {
			std::cerr << "Error opening file: " << fileNames[i] << std::endl;
			continue;
		}

		// Vectors to store the x and y values from the file
		std::vector<double> x, y;
		double xVal, yVal;

		// Read data from the file (assume two columns: x and y)
		while (inFile >> xVal >> yVal) {
			x.push_back(xVal);
			y.push_back(yVal);
		}

		// Create a TGraph from the x and y data
		TGraph *graph = new TGraph(x.size(), &x[0], &y[0]);
		graphs.push_back(graph);

		// Set graph properties (color, line style)
		graph->SetLineColor(i + 1);  // Different color for each graph
		graph->SetLineWidth(2);      // Line width
		graph->SetMarkerStyle(kFullCircle);
		graph->SetMarkerSize(1);
		graph->SetTitle("Incident Particles vs Angular Beam Spread");
		graph->GetXaxis()->SetTitle("Beam Spread (degrees)");
		graph->GetYaxis()->SetTitle("Incident Particles (N)");
		

		// Draw the graph
		if (i == 0) {
			graph->Draw("AL");  // First graph with axis and line
		} else {
			graph->Draw("L SAME");  // Subsequent graphs on the same canvas
		}
		
		graph->GetXaxis()->SetLimits(1.9, 4.1);  // Set x-axis range
		graph->GetYaxis()->SetRangeUser(0, 105000);  // Set y-axis range

		// Close the file after reading
		inFile.close();
	}

	TLegend *legend = new TLegend(0.9, 0.75, 1, 0.9);
	legend->AddEntry(graphs[0], "DD ", "l");
	legend->AddEntry(graphs[1], "ID ", "l");
	legend->AddEntry(graphs[2], "DD+ID", "l");
	legend->AddEntry(graphs[3], "All", "l");
	legend->Draw();
	
	c1->Update();
	
	c1->SaveAs("Incident Particles vs Angular Beam Spread.png");
}
