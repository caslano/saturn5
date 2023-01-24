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
liuvRahkHmIfgIecNhncl1mUKQ/fSaeM+PrvFdhcKlj6XVc9465DfQVnldU+R7JKeS38NpSo3KW7/CAYLW3CfPMYW+pmEL2NvFCbezbFVvEDOf9JqqhNHjyJGzJR3isQY2MifcfP5D33CmHRugbvRYcc9K/J5KpLw8SVpknD2RydGURdbFz4otV7+bcI3WgNehE+bu9xqg2LdUWTu434+QEFcValpKIjRxcWocH9yAdbxBu2CK6WoslWH76LKHJ227ir6IpajVV0BXwPL61kX//4zPJ9hWgCHMmqaHWJl0RDUuO8RXq1TA3StjqNxK9dYhokguxV/FrqLulcLHOjrHSRfVAqgobJlHh2xHvp2jh7hOxQwy9Fr+WnyripJh/4y/iiWzWTjRVtGiZOJcMRgldJ46aaK3pZlDR+foTs2c7dFTKOfCIEXS5SKrciC633IvNw6VqZSOetlY4n6Qd9uJmd66q2MTb6nPZIYt5wnzBsWNHEgpvK4xZqSiKeVJv5K/mVIWMyuzuasOt9M1jBjddyi0UMER7xK65LfiN9TDP3qIIPgwWpa9Xlaasxm8st/oZyi39YgqI1zEStedlNVb3S1uoV594gbwwj7ltsOkTBXG2uls/yfkP1ZsUNN95LBRxHw0TTxxfK7zDJF85YmRTVXSL2GJgWyuaQMjup54+0J8RG5gkM//291FsYQsOEAd/f5SsypxVJirZG
*/