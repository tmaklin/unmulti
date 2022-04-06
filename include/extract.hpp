#ifndef UNMULTI_EXTRACT_HPP
#define UNMULTI_EXTRACT_HPP

#include <vector>
#include <cstdint>
#include <string>
#include <utility>

#include "cxxio.hpp"

namespace unmulti {
    std::vector<std::pair<uint32_t, std::string>>Extract(const std::string &outdir, const std::vector<std::string> &outnames, const bool compress, cxxio::In &in);
}

#endif
