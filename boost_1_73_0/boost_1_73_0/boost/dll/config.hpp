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
iVxwLaxusKrWLpahXjZVciUsFpzpLigMQIRHa+TvorhCykcuz++IoUvQ0t1G6BYbanJCaWOlSJvycZH1vekHrw4vsnHEB3y5bSQ+M7wpYI4tqL2X9QqBI5XiG2REyWNR8loA6rCR6Rq5Qs5VXSV1LqrA6A7Lu0t6Fo3tTHNwGxUJdu8YbiIuosprKnS+2SqCVxXswJ3a+A4UXO3Qp9rWKH1XqLksgn0OzyKu+qYuywItZ1VUW1IZB6jDJdCT7WqCBnusAIIIEXISclln9Rz5rDhDrkReS1crasPFAbZGwdd97pzGs/jgNQO+jVfQu42jCx87C6YWOXfIUkqfZVx3hWnCF+7sRQZYRcAKsoq1byK+n7kzjQgAXckMDvDzgDSuqObSynyzz4Joy6vAy0oCW9/ttVwD/aZOhbIF6cH1ufd5/jE+dTHWIBmU6uJmAUuc0AVYZKxwvZabFPzVhe83VYXV2g0bFmfQbyjWmwjOKBYgckdlgAb1nL6Ozs58zgLNsYeOCoqhJC00s8hZH+wVNuIVx/OZa5Xwx88eFD/gSYDARz2rQje/i9ha5TlxEYWRsKTWGHqQupUbW7xjiECToI7n1h/yGhoO9ebd0dngdDjDdTjsdWeOP43erToLbhIa/eWlrDj4N8tDx1eL
*/