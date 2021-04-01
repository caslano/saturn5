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
YbwHN5/uqMpzB7KetDLWLP2VNiOY1JGyRm2l6SuD6GrRDfjBSrViTA+L9XHBi31KutEKqnEZgyXhY0Hhk+S3HxFCbsLzIPro6ya8oh4DMR1fYFlYFGDnp0zou9OtIGp8WiJLNu5u5fuvLXHxV45qlarQhXUOE7wi4zmL0345/1Sg5c1HvKIBM5dB1bVmYgXEubbYPmVYAZkX4M5FupfdyAfH7yUPZ2Yovj6AhfiK/q3BLNVvHSZlYRbQY+WX1RP9k8t9O2aefyblURJShGlXBs7+IUMCB9fCAare65k1dsSf0KpGMfrQ4aXB4/gn0ate/vi5tJ6HNWmLdP6dr8bVHLNToaZCUiQKnAXoP1NaexBePg0dBoAcWhluOkMJFqrvwS4jP6QA3gG3UZgAQriWOh3+8rpVOnIGugUWV7cdVffK7TqPpANEZoIQAIzBErg7OQVkixf8rgBftgn7nTBa+Spn8ZqzfOeq3s+w/rgGPgyikrNiMZzgkUEIP4hQcZVd2t/RSjC1mNxQK+YA2BcY+yqR+VxlH6Y+C5QYN1+liSe1snV1pEope8M5Eg==
*/