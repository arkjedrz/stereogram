#include <CLI/CLI.hpp>
#include <string>
#include "file_helpers.h"
#include "sirds_generator.h"

int main(int argc, char** argv) {
  CLI::App app{"Single Image Random Dot Stereograms generator."};

  int dpi = 72;
  std::string depth_map_filepath;
  std::string output_filepath;
  app.add_option("--dpi", dpi, "Output image DPI.", true);
  app.add_option("-d, --depth", depth_map_filepath, "Path to a depth file.")
      ->required();
  app.add_option("-o, --output", output_filepath, "Output file.")->required();

  CLI11_PARSE(app, argc, argv);

  if (!stereogram::FileExists(depth_map_filepath)) {
    std::cout << "Depth map file not found.";
    exit(-1);
  }

  cv::Mat depth_map = stereogram::LoadDepthMap(depth_map_filepath);

  stereogram::SirdsGenerator generator{depth_map, dpi};
  cv::Mat sirds_image = generator.Generate();

  cv::imwrite(output_filepath, sirds_image);

  return 0;
}
