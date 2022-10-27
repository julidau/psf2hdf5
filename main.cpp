#include <iostream>
#include <string>

#include <highfive/H5File.hpp>
#include <psf.h>

std::vector<std::string> split(std::string const&input, std::string const& sep) {
    std::vector<std::string> result;
    std::string current = "";

    for (auto c : input) {
        if (sep.find(c) != std::string::npos) {
            result.push_back(current);
            current.clear();
            continue;
        }

        current += c;
    }

    result.push_back(current);
    return result;
}

int main(int argc, char ** argv) {
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " [input file] [output file]" << std::endl;
        return 0;
    }

    std::string inputname(argv[1]), outputname(argv[2]);

    std::cout << "convert " << inputname << " -> " << outputname << std::endl;

    // create output file

    // Create a new file using the default property lists.
    std::cout << "generating file " << outputname << std::endl;

    auto file =  HighFive::File(outputname, H5F_ACC_TRUNC);

    std::cout << "load input file " << inputname << std::endl;
    auto input = PSFDataSet(inputname);

    auto timevalues = input.get_sweep_values();
    HighFive::DataSet timedataset;
    if (std::vector<double> *time64v = dynamic_cast<std::vector<double>*>(timevalues)) {
        timedataset = file.createDataSet("time", *time64v);
    }
    auto signalgroup = file.createGroup("signals");

    for (auto signal : input.get_signal_names()) {

        // differentiate between signal value or vector
        if (input.is_swept()) {
            // this is a vector
            auto signalvalues = input.get_signal_vector(signal);
            
            // create groups for signal hieracharchy
            auto signalhier = split(signal, ".");
        
            std::string path;
            for (auto hier: signalhier) {
                path += hier + "/";
            }
            path.pop_back();

            // find out what type of array we have here 
            if (std::vector<double> *f64v = dynamic_cast<std::vector<double> *>(signalvalues))  {
                auto dataset = signalgroup.createDataSet(path, *f64v);
            } else {
                std::cout << signal << ": data is not double :(" << std::endl;
            }
        }
        
        std::cout << "  *" << signal << "written" << std::endl;
    } 

    return 0;
}