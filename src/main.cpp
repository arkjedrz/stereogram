#include <CLI/CLI.hpp>
#include <string>
#include "sirds_generator.h"
#include "file_aux.h"

int main(int argc, char** argv) {
    using namespace stereogram;
    CLI::App app{"Single Image Random Dot Stereograms generator."};

    int dpi = 72;
    app.add_option("--dpi", dpi, "Output image DPI.", true);
    std::string depth_map_filepath;
    app.add_option("-d, --depth", depth_map_filepath, "Path to a depth file.")->required();
    std::string output_filepath;
    app.add_option("-o, --output", output_filepath, "Output file.")->required();

    CLI11_PARSE(app, argc, argv);

    cv::Mat depth_map = load_depth_map(depth_map_filepath);
    cv::Mat sirds_image = generate_sirds(depth_map, dpi);
    cv::imwrite(output_filepath, sirds_image);

    return 0;
}
