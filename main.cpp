#include <iostream>
#include "eSNN.h"
#include <windows.h>


using namespace std;

//Read all data files in a given directory
void ReadDirectory(const std::string &name, vector<string> &v) {
    std::string pattern(name);
    pattern.append("\\*");
    WIN32_FIND_DATA data;
    HANDLE hFind;
    if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
        do {
            v.push_back(data.cFileName);
        } while (FindNextFile(hFind, &data) != 0);
        FindClose(hFind);
    }
}

int main() {


    string path = "F:\\Artykuly\\Online Air Pollution Prediction with eSNN\\Software\\OeSNN"
                  "\\Datasets\\Warsaw\\";
    string resultsPath = "F:\\Artykuly\\Online Air Pollution Prediction with eSNN\\Software\\OeSNN"
                         "\\Results\\Warsaw\\";


    vector<string> files;

    ReadDirectory(path, files); //load all datafiles from a directory


    double NOsize_b = 200, NOsize_e = 200, NOsize_s = 50; //parameters for grid search (xxx_b - intial, xxx_e - ending, xxx_s - step)
    double Wsize_b = 1, Wsize_e = 1, Wsize_s = 1;
    double NIsize_b = 40, NIsize_e = 300, NIsize_s = 20;
    double sim_b = 0.05, sim_e = 0.05, sim_s = 0.5;
    double mod_b = 0.9, mod_e = 0.9, mod_s = 0.1;

    Ninit = 200, Nsize = 1096;

    for (int i = 2; i <= 2; i++) {

        cout << "#####################################################################" << endl;
        cout << files[i] << endl;

        for (double Wsize_c = Wsize_b; Wsize_c <= Wsize_e; Wsize_c += Wsize_s) {
            for (double NOsize_c = NOsize_b; NOsize_c <= NOsize_e; NOsize_c += NOsize_s) {
                for (double NIsize_c = NIsize_b; NIsize_c <= NIsize_e; NIsize_c += NIsize_s) {
                    for (double NIsize_c = NIsize_b; NIsize_c <= NIsize_e; NIsize_c += NIsize_s) {
                        for (double sim_c = sim_b; sim_c <= sim_e; sim_c += sim_s) {
                            for (double mod_c = mod_b; mod_c <= mod_e; mod_c += mod_s) {


                                Wsize = Wsize_c, NOsize = NOsize_c, NIsize = NIsize_c, simTr = sim_c, mod = mod_c,
                                Nn = 1, H = 12;

                                cout << endl << "WSize " << Wsize << " NOsize " << NOsize << " NIsize " << NIsize
                                     << " simTr " << simTr << " mod " << mod
                                     << endl;

                                LoadData(path + "\\" + files[i]); //load dataset

                                PredictOeSNN(); //predict with OeSNN

                                //SaveResults(resultsFilePath);
                                //SaveMetrics(metricsFilePath, precision, recall, fMeasure, 0);

                                CalculateRMSE();

                                SaveResults(resultsPath + files[i]);

                                ClearStructures();

                            }
                        }
                    }
                }
            }
        }
        //Wsize = 12, NOsize = 250, NIsize = 10, simTr = 0.15, mod = 0.95, n = 2, m = 5, H = 144, K = 5;

    }


    return 0;

}