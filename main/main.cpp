#include "libmovavg.h"
#include "cxxopts.hpp"
#include <iostream>
#include <fstream>
#include <vector>

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

void loopLine(std::istream &f, const size_t mva_len, const std::string colDelim, const size_t colPos, bool showErr, const std::string nullstr)
{

    std::string line;

    Moving_Average<double, double> ma;
    ma.setSizeOf(mva_len);

    while (getline(f, line))
    {
        try
        {
            ma(std::stod(split(line, ",").at(colPos)));
            if (ma.isNull())
            {
                std::cout << line << colDelim << nullstr << '\n';
            }
            else
            {
                std::cout << line << colDelim << ma << '\n';
            }
        }
        catch (const std::exception &e)
        {
            if (showErr)
            {
                std::cout << e.what() << std::endl;
            }
            else
            {
                if (ma.isNull())
                {
                    std::cout << line << colDelim << nullstr << '\n';
                }
                else
                {
                    std::cout << line << colDelim << ma << '\n';
                }
            }
        }
    }
    if (f.bad())
        perror("error while reading file");
}

int main(int argc, char **argv)
{

    try
    {

        cxxopts::Options options("movavg", "moving average cpp utility");
 
        options.add_options()
        ("e,showErr", "show errors",cxxopts::value<bool>()->default_value("false"))
        ("l,len", "set moving avg len, 0 for none moving", cxxopts::value<int>()->default_value("7"))
        ("d,coldelim", "set column delimiter", cxxopts::value<std::string>()->default_value(","))
        ("n,colnum", "set column number", cxxopts::value<int>()->default_value("0"))
        ("nullstr", "set null string", cxxopts::value<std::string>()->default_value("null"))
        ("h,help", "Print usage")
        ;
        auto result = options.parse(argc, argv);

        if (result.count("help"))
        {
            std::cout << options.help() << std::endl;
            return 0;
        }

        bool showErr = result["showErr"].as<bool>();

        size_t len = result["len"].as<int>();

        std::string coldelim = result["coldelim"].as<std::string>();

        size_t colnum = result["colnum"].as<int>();

        std::string nullstr = result["nullstr"].as<std::string>();
        ;

        loopLine(std::cin, len, coldelim, colnum, showErr, nullstr);
    }
    catch (std::exception &e)
    {
        std::cerr << "error: " << e.what() << "\n";
        return 1;
    }
    catch (...)
    {
        std::cerr << "Exception of unknown type!\n";
    }

    return 0;
}
