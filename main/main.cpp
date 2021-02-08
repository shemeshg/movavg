#include "libmovavg.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/program_options.hpp>
namespace po = boost::program_options;



std::vector<std::string> split(std::string s, std::string delimiter)
{
    std::vector<std::string> v;

    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos)
    {
        token = s.substr(0, pos);
        v.push_back(token);        
        s.erase(0, pos + delimiter.length());
    }
    v.push_back(s);
    return v;
}

void loopLine(std::istream &f, const size_t mva_len, const std::string colDelim, const size_t colPos, bool showErr)
{
    
    
    std::string line;

    Moving_Average<double, double> ma;
    ma.setSizeOf(mva_len);

    while (getline(f, line))
    {
        try
        {
            ma(std::stod(split(line,",").at(colPos) ));
            std::cout << line << colDelim << ma << '\n';
        }
        catch (const std::exception &e)
        {
            if (showErr) {
                std::cout << e.what() << std::endl;
            } else {
                std::cout << line << colDelim << ma << '\n';
            }
            
        }
    }
    if (f.bad())
        perror("error while reading file");
}



int main(int ac, char* av[])
{

    try {

        po::options_description desc("Allowed options");
        desc.add_options()
            ("help,h", "produce help message")
            ("showErr,e", "show errors")
            ("len,l", po::value<size_t>(), "set moving avg len, default 7")
            ("coldelim,d", po::value<std::string>(), "set column delimiter, default ',' ")
            ("colnum,n", po::value<size_t>(), "set column number, default 0")
        ;

        po::variables_map vm;        
        po::store(po::parse_command_line(ac, av, desc), vm);
        po::notify(vm);    

        if (vm.count("help")) {
            std::cout << desc << "\n";
            return 0;
        }

        bool showErr = false;
        if (vm.count("showErr")) {
            showErr = true;
        }

        size_t len = 7;if (vm.count("len")) {len = vm["len"].as<size_t>();} 
        std::string coldelim = ",";if (vm.count("coldelim")) {coldelim = vm["coldelim"].as<std::string>();} 
        size_t colnum = 0;if (vm.count("colnum")) {colnum = vm["colnum"].as<size_t>();} 

        loopLine(std::cin, len,coldelim,colnum, showErr);
    }
    catch(std::exception& e) {
        std::cerr << "error: " << e.what() << "\n";
        return 1;
    }
    catch(...) {
        std::cerr << "Exception of unknown type!\n";
    }

    
    

    return 0;
}
