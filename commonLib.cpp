//
// Created by DucDung Nguyen on 05/04/2017.
//

#include "commonLib.h"

// Load data from the input file
// return: true if loading process is success
bool loadData(char* fName, DataIterator_t& data) {
	ifstream inFile(fName);
	if (inFile) {
		string line;
		int id = 0;
		while (getline(inFile, line)) {
			/// On Windows, lines on file ends with \r\n. So you have to remove \r
			if (line[line.length() - 1] == '\r')
				line.erase(line.length() - 1);
			if (line.length() > 0) {
				if (id > 2) {
					istringstream iss(line);
					Point2D_t temp;
					iss >> temp.x >> temp.y;
					data.data.push_back(temp);
				}
			}
			id++;
		}
	}
	else {
		cout << "The file is not found!";
	}
	return true;
}

// Load parameters from the input file
// return: true if loading process is success
bool loadParams(char* fName, ProbParam_t& param) {
    ifstream inFile(fName);
    if (inFile) {
        string line;
		int id = 0;
        while (getline(inFile , line)) {
            /// On Windows, lines on file ends with \r\n. So you have to remove \r
            if (line[line.length() - 1] == '\r')
                line.erase(line.length() - 1);
            if (line.length() > 0) {
				if (id > 2) {
					istringstream iss(line);
					string temp;
					if (id == 3)
						iss >> temp >> param.nIterations;
					if (id == 4)
						iss >> temp >> param.learningRate;
					if (id == 5)
						iss >> temp >> param.startPoint.x;
					if (id == 6)
						iss >> temp >> param.startPoint.y;
					if (id == 7)
						iss >> temp >> param.nFolds;
					if (id == 8)
						iss >> temp >> param.eval;
				}
            }
			id++;
        }
        inFile.close();
    }
    else {
        cout << "The file is not found!";
    }
	return true;
}
