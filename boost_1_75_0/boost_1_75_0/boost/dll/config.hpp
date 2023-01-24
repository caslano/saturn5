// Copyright 2018-2019 Antony Polukhin.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

/// \file boost/dll/config.hpp
/// \brief Imports filesystem, error_code, errc, system_error, make_error_code from Boost or C++17 into `boost::dll::fs` namespace.

#ifndef BOOST_DLL_DETAIL_CONFIG_HPP
#define BOOST_DLL_DETAIL_CONFIG_HPP

#include <boost/config.hpp>
#ifdef BOOST_HAS_PRAGMA_ONCE
#   pragma once
#endif

#ifdef BOOST_DLL_DOXYGEN
/// Define this macro to make Boost.DLL use C++17's std::filesystem::path, std::system_error and std::error_code.
#define BOOST_DLL_USE_STD_FS BOOST_DLL_USE_STD_FS

/// This namespace contains aliases to the Boost or C++17 classes. Aliases are configured using BOOST_DLL_USE_STD_FS macro.
namespace boost { namespace dll { namespace fs {

/// Alias to `std::filesystem::path` if \forcedmacrolink{BOOST_DLL_USE_STD_FS} is defined by user.
/// Alias to `boost::filesystem::path` otherwise.
using path = std::conditional_t<BOOST_DLL_USE_STD_FS, std::filesystem::path, boost::filesystem::path>;

/// Alias to `std::error_code` if \forcedmacrolink{BOOST_DLL_USE_STD_FS} is defined by user.
/// boost::system::error_code otherwise.
using error_code = std::conditional_t<BOOST_DLL_USE_STD_FS, std::error_code, boost::system::error_code>;

/// Alias to `std::system_error` if \forcedmacrolink{BOOST_DLL_USE_STD_FS} is defined by user.
/// Alias to `boost::system::system_error` otherwise.
using system_error = std::conditional_t<BOOST_DLL_USE_STD_FS, std::system_error, boost::system::system_error>;

}}}

#endif

#ifdef BOOST_DLL_USE_STD_FS
#include <filesystem>
#include <system_error>

namespace boost { namespace dll { namespace fs {

using namespace std::filesystem;

using std::error_code;
using std::system_error;
using std::make_error_code;
using std::errc;
using std::system_category;

}}}

#else // BOOST_DLL_USE_STD_FS

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/system/error_code.hpp>

namespace boost { namespace dll { namespace fs {

using namespace boost::filesystem;

using boost::system::error_code;
using boost::system::system_error;
using boost::system::errc::make_error_code;
namespace errc = boost::system::errc;
using boost::system::system_category;

}}}

#endif // BOOST_DLL_USE_STD_FS

#endif // BOOST_DLL_DETAIL_PUSH_OPTIONS_HPP


/* config.hpp
M5frPu+j4/H7UNb4/R48HOFXa+n0S3762T2BcWYgV/24XS9XzQczi8EgFepqaTtyE5pMcD+yb2hrRL9RHbXoeVXqk+/UsDKgTcN1bQoU9GYPbSroJVbUd2lSZ7qI7WG1fmvVLGJBbWLfbDuPTeyfm1thE7sJJrhtujvAJlZzs9EmtvLmf2MTu9ltsIl1tjZnE8uYhp/7l7uF7Kzu6Pxb1d4lNMXZ430IBNf7dJXemzCePAKLA4BjuO9gH/IdzB9S3xMxFABmw9tVXZvx3CRQqkfZu9kiOoIzAfc/Tu7cKO9Set+t+txHCtfIgVo/4mGuZiNQiPB/jC7d292UuA/tOl+Gc8CCGFqHPtsT7CYGkZ0PtGBNBwFaoOIV6HEm3q/U2qD6ZubNb+KM+fbbTYavKUwEH75L+fCl1fdoFQSFpYMBggKGbpSkDZ0yXdibVayWs1u0+X0erJbLpf9/YbUs02O1LBhiwGqJiDZgtaRNBqyWn+6ymdRYDbKnwRCc2SzsaY2BI5BRC1Y2yZdZ67f1HWLo/vbA7qPwclrX/cyDLl9GraHz10LnoxEgHpjHg1g6+BhM18ZgYpAyaD4jEJNZg+0mDPupZ7vuCTUUeFHDZtrt/3TjgReeNJw+7CrNnna8IHsVjCB07/rBNICZjTB+29uTMw5KQziOE+BeTcDDTBBdCiRaeWQ62di+ut1AY2BdPFuhX5tG/JW1Gc3j
*/