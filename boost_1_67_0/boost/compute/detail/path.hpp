//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_PATH_HPP
#define BOOST_COMPUTE_DETAIL_PATH_HPP

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/compute/detail/getenv.hpp>

namespace boost {
namespace compute {
namespace detail {

// Path delimiter symbol for the current OS.
static const std::string& path_delim()
{
    static const std::string delim =
        boost::filesystem::path("/").make_preferred().string();
    return delim;
}

// Path to appdata folder.
inline const std::string& appdata_path()
{
    #ifdef _WIN32
    static const std::string appdata = detail::getenv("APPDATA")
        + path_delim() + "boost_compute";
    #else
    static const std::string appdata = detail::getenv("HOME")
        + path_delim() + ".boost_compute";
    #endif
    return appdata;
}

// Path to cached binaries.
inline std::string program_binary_path(const std::string &hash, bool create = false)
{
    std::string dir = detail::appdata_path() + path_delim()
                    + hash.substr(0, 2) + path_delim()
                    + hash.substr(2);

    if(create && !boost::filesystem::exists(dir)){
        boost::filesystem::create_directories(dir);
    }

    return dir + path_delim();
}

// Path to parameter caches.
inline std::string parameter_cache_path(bool create = false)
{
    const static std::string dir = appdata_path() + path_delim() + "tune";

    if(create && !boost::filesystem::exists(dir)){
        boost::filesystem::create_directories(dir);
    }

    return dir + path_delim();
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_PATH_HPP

/* path.hpp
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
*/