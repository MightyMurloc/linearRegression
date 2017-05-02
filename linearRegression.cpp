//
// Created by DucDung Nguyen on 05/04/2017.
//

#include "linearRegression.h"

bool linearRegression(DataIterator_t& dataIter, ProbParam_t& param,
                      LinearRegressionModel_t& model) {
	model.a = param.startPoint.x, model.b = param.startPoint.y;
	float alpha = param.learningRate;
	for (int i = 0; i < param.nIterations; ++i) {
		float deriv_a = 0, deriv_b = 0;
		for (int j = 0; j < dataIter.data.size(); ++j) {
			float x = dataIter.data[j].x, y = dataIter.data[j].y;
			deriv_a += x*(model.a*x + model.b - y);
			deriv_b += model.a*x + model.b - y;
		}

		float length = sqrt(pow(deriv_a, 2) + pow(deriv_b, 2));
		model.a -= alpha*(deriv_a/length);
		model.b -= alpha*(deriv_b/length);
	}
    return true;
}

bool modelEvaluationLR(DataIterator_t& dataIter, LinearRegressionModel_t& model) {
	float mean = 0, sigma = 0;
	vector<float> e;
	model.Ermsd = 0;

	for (int i = 0; i < dataIter.data.size(); ++i) {
		float x = dataIter.data[i].x, y = dataIter.data[i].y;
		float temp = model.a * x + model.b - y;
		mean += temp;
		e.push_back(temp);
	}
	mean /= dataIter.data.size();
	
	for (int i = 0; i < dataIter.data.size(); ++i) {
		model.Ermsd += pow(e[i], 2);
	}
	model.Ermsd /= dataIter.data.size();
	model.Ermsd = sqrt(model.Ermsd);

	for (int i = 0; i < dataIter.data.size(); ++i) {
		sigma += pow(e[i] - mean, 2);
	}
	sigma /= dataIter.data.size();
	sigma = sqrtf(sigma);

	float v_min = mean - 3 * sigma, v_max = mean + 3 * sigma;
	float interval[10];
	for (int i = 0; i < 10; ++i) {
		float temp = v_min + (i + 1)*((v_max - v_min) / 10);
		interval[i] = temp;
	}
	for (int i = 0; i < 10; ++i) {
		model.errHistogram[i] = 0;
	}
	for (int i = 0; i < dataIter.data.size(); ++i) {
		if (e[i] < v_min || e[i] > v_max) continue;
		if (e[i] < interval[0])
			model.errHistogram[0] += 1;
		else if (e[i] >= interval[8])
			model.errHistogram[9] += 1;
		else {
			for (int j = 0; j < 8; j++) {
				if (e[i] >= interval[j] && e[i] < interval[j + 1]) {
					model.errHistogram[j + 1] += 1;
					break;
				}
			}
		}
	}
	
	int length = 0;
	for (int i = 0; i < 10; ++i) {
		length += model.errHistogram[i];
	}
	for (int i = 0; i < 10; ++i) {
		model.errHistogram[i] /= length;
	}

    return true;
}

bool kFoldTraining(DataIterator_t& dataIter, ProbParam_t& param,
                   LinearRegressionModel_t& model) {
	cout << "---------------------------------------------------------------------------------\n"
			"Output of the validation\n"
			"---------------------------------------------------------------------------------\n";
	dataIter.curBlock = 0;

	while (dataIter.curBlock < param.nFolds) {
		DataIterator_t testData, trainData;
		int size = dataIter.data.size() / param.nFolds;
		if (dataIter.curBlock != param.nFolds - 1) {
			dataIter.batchSize = size;
		}
		else
			dataIter.batchSize = dataIter.data.size() - (param.nFolds - 1)*size;

		int pos = dataIter.curBlock*size;
		for (int i = 0; i < dataIter.batchSize; ++i) {
			Point2D_t temp = dataIter.data[pos];
			testData.data.push_back(temp);
			pos++;
		}

		for (int i = 0; i < dataIter.curBlock*size; ++i) {
			Point2D_t temp = dataIter.data[i];
			trainData.data.push_back(temp);
		}
		pos = (dataIter.curBlock + 1)*testData.data.size();
		for (int i = pos; i < dataIter.data.size(); ++i) {
			Point2D_t temp = dataIter.data[pos];
			trainData.data.push_back(temp);
			pos++;
		}

		linearRegression(trainData, param, model);
		cout << right << setw(7) << model.a << " " << right << setw(7) << model.b << " ";
		
		modelEvaluationLR(testData, model);
		cout << right << setw(7) << model.Ermsd << " ";
		
		for (int i = 0; i < 10; ++i)
			cout << right << setw(7) << model.errHistogram[i] << " ";
		cout << endl;

		dataIter.curBlock++;
	}
    return true;
}