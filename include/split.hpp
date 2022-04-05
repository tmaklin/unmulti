#ifndef UNMULTI_SPLIT_HPP
#define UNMULTI_SPLIT_HPP

#include <vector>
#include <cstdint>
#include <string>
#include <utility>

#include "cxxio.hpp"

namespace unmulti {
    std::vector<std::pair<uint32_t, std::string>> Split(const std::string &outdir, const bool compress, cxxio::In &in);
    void FileToSeq(const std::string &outdir, const std::string &outfile, const std::vector<std::pair<uint32_t, std::string>> &seq_names);
}

#endif
