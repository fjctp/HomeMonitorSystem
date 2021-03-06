#ifndef OPTIONSPARSER_HPP
#define OPTIONSPARSER_HPP

#include <string>
#include <yaml-cpp/yaml.h>
#include <boost/program_options.hpp>

#include "Settings.hpp"

namespace po = boost::program_options;

struct Options {
  std::string path2yaml;
  std::string path2log;
};

// OptionsParser Class
class OptionsParser
{
public:
  OptionsParser();
  ~OptionsParser();

  Options parse(int argc, char* argv[]);

protected:
  void setup();
  void show_help_message();

  po::options_description desc;
  po::variables_map vm;
};


#endif // !OPTIONSPARSER_HPP
