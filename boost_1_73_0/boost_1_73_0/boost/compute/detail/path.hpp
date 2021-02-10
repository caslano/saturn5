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
Dj60L5xOexM3BAB65k5q3ch7lR37uuu0eufPkr4OJdqPKFgsO+5KtQJM2W66Lcexij4C90fxLfEmYUxAkPo5mqAiYoBwceK+QTvrOGd/rFUQgJ6AakfRfr+t6l1F5uq6M3RGrtt5tg0RWFhguMAaRu2NgL/NLiKaAhIuA6UPJAm36YljGkRjHoyUCgDN6gdbAHFr2V+dXN1h52pNH3q0SSGkdaNPZ5sEhSbpiwCxnx+bc6wKx3Al5olgIeJVaferrd9/3mBldlfRNxkE/JVifbpK9JibTibygXUwXpbDpqCFUZMwngf4J/O6wfNaQgj8lR66zDgCGqtZU42rTEPcRNzK1snqLt316ZtPukVPBILat7JWzfKWRSuvBF0JSDVv5ACcBBtctDASHZ/YW+vOPKmSFpYtwoBiTncudwdlxN36cTy77mZIg9Yt8VNE6Gl5qbzMbVLaeopDsrfbBSKsxiMNHW+Nwq6gdS6nhM42QyfsGXRi/QQ6WTXdgb1fYbxhx21eDy9H7qC/iQ2xfBtLWV2GK4NZdkddtFass/LKsbUqyP5eJThGLf59RO2hvRnEQXF+yLME09qtSJRd1VAGbapTpTuP5SSsi/b6yA/JixFDz2W/FIc8dDkCv01KIJuqvw7ZTLRGdk2n9FmV
*/