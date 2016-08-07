#ifndef SETTINGS_PARSER_HPP_HPP
#define SETTINGS_PARSER_HPP

#include <string>
#include <yaml-cpp/yaml.h>
#include <boost/program_options.hpp>

#include "Settings.hpp"

namespace po = boost::program_options;

// SettingsParser Class
class SettingsParser
{
public:
  SettingsParser();
  ~SettingsParser();

  void parse(int argc, char* argv[]);
  Setting get();

protected:
  void setup();
  std::string parse_cmd(int argc, char* argv[]);
  void parse_yaml(std::string yaml_path);
  void show_help_message();

  po::options_description desc;
  po::variables_map vm;

  Setting s;
};


#endif // !SETTINGS_PARSER_HPP
