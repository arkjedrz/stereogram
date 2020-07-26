#include <CLI/CLI.hpp>
#include <string>
#include "file_helpers.h"
#include "generator.h"
#include "sirds_generator.h"

int main(int argc, char** argv) {
  CLI::App app{"Single Image Random Dot Stereograms generator."};

  int dpi = 72;
  std::string depth_map_filepath;
  std::string output_filepath;
  app.add_option("--dpi", dpi, "Output image DPI.", true);
  app.add_option("-d, --depth", depth_map_filepath,
                 "Path to a depth file. Only first channel will be used.")
      ->required();
  app.add_option("-o, --output", output_filepath,
                 "Generated autostereogram path.")
      ->required();

  CLI11_PARSE(app, argc, argv);

  using namespace stereogram;
  if (!FileExists(depth_map_filepath)) {
    std::cout << "Depth map file not found.";
    exit(-1);
  }

  cv::Mat depth_map = LoadDepthMap(depth_map_filepath);

  std::unique_ptr<Generator> generator =
      std::make_unique<SirdsGenerator>(depth_map, dpi);
  cv::Mat autostereogram = generator->Generate();

  cv::imwrite(output_filepath, autostereogram);

  return 0;
}
