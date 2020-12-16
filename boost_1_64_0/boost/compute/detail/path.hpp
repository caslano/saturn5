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
wIKF7BQVpyoXi9GJYJH+YCkKCE9j9+jAekxtdC0iBKeLlViOPiTO0De0o/JM5WIZelCxmN2gDeuR2kM5qJuuHsyZoc2I7Uk39jiO7EVcHBfzTIe98FDEIGqL9sXbz/ypwl7JZ5Grtc7BTe3dPGzvO3ShZP/spfZKm76dsrwPOQ3LlNfluj7nc9vY7ziMef7B/s/ovJPe5nvvbHfysgdK0t56C+y3FlfO0oJ9CzBzAV2gy1pxzuca9KN0gmNoQQZzUI8KtLkv8fU483i+jAgDiJ9Ejj4r0WK/8oV/MgdCLzYgUTD/QxpZdM4yP0JgPl2H2fYuz2AVurEedWPs5YzyDvqjfyXMD/29mxikzOXub9H2DIIp9v1EX2ivQ9Tah3BmhT0Pn7HHD3rY17xu+0S5Z7o+zEefcgLyGXKu0h4P9ZiNxeix73nk3aIi1iNOLqE19lp1zca0XWKe+yMLrFfWPDrI2Ju7DQN3KNPeEbWO91pbbH6OrB0P6GTIfQl/F1H+2h5B/6YT9D7p82Xf7VMYw1JtLjofoU0/skhjjmsbsdb5Jp/t9sjLuHc52tHqeCcalNFqT/rAGmJent8T0Y89vTdYp1hoD/Dl9dZnZ5qb+uyxb3eNd6mmYc3JfqO353dMGT328h7EUqTtE57znlW7v1tm6KfvhSM9z0GeNa7v9n0INQj0u51c5rl22kxyIuNZ9uirRwxDB9C7evvdv8bfA9tYG/e5DGnMwnTn630WMYdt1freSK4Zcp2v/gH9ycm7m/yWt94zArVk22LeXOoha3vNrd9N3Zfpt3tC+8BOd77PdUV7k081B1x8nja4JqKfhmnabS//ig3slm33sd/Afu5L6Gqea+r20Fcya3ddiDXqT/i+fKa+kV2BnJvtdz9rYzLi34uxBsGv4kFBnpz7x/ggzEwSzydZ56cve8nlb5WfPqo/r1QHyVnjg+jo6iDd45k28Sl6MR6k3giD1HWTg+hsx/8jtmxeFdis3/9xnWxMrApKz4VBw8Qp9kyNB9k7Y0HyqvFB8Jp7PSeSukcM++WEoNxuLrR0tH37HZ+pnCNj9kHRpuvd51nyrPfjSu3a53jCvlupG+JB8pdxv02NDxocy8Wm2BNlUlA8UUz5T4X5umfXHC+IJ/mbJgfB9eOD1KvVQYHP57YO7YE43r4KrrEfXMKxhs98j8U9xzIhyNjbNHEhO07yE/tmFR73Hm6+yh7M/keH/5cY3Epef/rf/6xnA+TUpGx7uaX976/iY3w/Ria3xYOy+0ozyHDhZP+bjkx/O946Nfk+M8G7oJOCrP2GshuJ2zuyt5umBPnz9P2HoT3CJweJ8njyrwoSV9DvJZOC8koySCvnHuVcT9Y787HL7B02sVpOMMXvFurco1rbPQfzFPmvmxAkTiO/l+NB5gb9tydlcAffaLC37NXVQbltUpDemwwH7KNERtkdyLbatdqe+Iy/02fe35Ey0/SXc01iblVQ9O597i8TPGM02rtbriXjwLsAOfEm2zLZ7wmTg5RjSfIIbx5lbwuyuSgeFDv051BtvEuZ5BB+SI9sovya+XJMeeovqyd38eQgq7zS82zqaWP3nPFB1j6+4TC722tCUJo9yd4n4o3nqhNJ/a9VNv2W/VacGGJnZXugNU0I8qdU+W05HpTWiV9D7h1rb9tBtnm4/+nxUty+CRvpDz2w52A7OjiB7LQ7fZ922B8p+OsE+33bz22Xajl/dZD1mZsTD/J0ldCu7Ffjg/R1rr+Rb1zKfsfq0wvs8kV+9hd216cNz44PkkeGQUGZeX2OrlDXXP2ZUR2k/A+S7KaTg8ye1X5rHePdbLpqI4tdtfE9MfFOtvIme3heuYP2Nb4=
*/