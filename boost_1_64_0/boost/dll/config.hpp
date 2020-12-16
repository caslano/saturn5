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
7Rf6fq7ntmnu6hs344Rb4lXX2PJtQGVGm7m18UEPfd9Cp226vO15dUscnXdNJlG7cr8yqqxATf9pIUIpoTWQZsbuj8QYUDj3liKBmQjb6kevi7L+uEne1EWvt6+j2Zje9m+iKooKAzz2XeFuRNB0zqlTce2t3GOr1srdlrH6lmqkLHfa59JAXTrozy/DC9D6zHwJFeb9JALTmi0apj8DJu7hVMR5ZC7jDDH+8rao8ddupxh/23DkpeHI8+P3c9+wjDy6TqM4nsfQvrfFGMor9nNS11dE0h3F2Zy0c7ZIukoN25tms4J7GLQ5SvzXM6zgeitV4qWvsII7knOumaOP0t7bHUbprTvEKL1hx0mO0irnfzar8Xr8PRiv77wrxmvFezWPV4v/3PDq/evEvvqmar5Pwe9hyAMxPp/aZFsu8wUjvgm8XJ7NC9kHXxULWVooxXZ1gU3Tgzyqe8ZeCF+S8MsT0P8iBiAh/Gw8IsyzIkwmhLMJ4aFKaLcbAExtzA6XJs4AoVggUIy2ovhkJZlqRUxJjmWeqTvgDq9yk19/QnilQDjOivBxQug5eTt0rfRT0R/ut2z9wec/Fj3K/THHPP/ximi+o9R8L56A5stb4tAfhfjlBMhiLbDZVQJhnhXhNEIojfMDEGzbNu4P0VKyBe8mLA0EltFWLH0FluCNobtkGmKy9Qpbat7IR5z5Vpzfr/i1eyWc/rm9xNY/HJTflc/98xYTnSaILj9Izen5BZrzgxcd+id4HL7cCqJfCw326jjuHxPh18sFwmmEcDWCnbPV7J8pZv9MJiz3CiyjrViWCSzBP1riBuIL9wrf8JVii07r3JtTTs08WvP8avGnHF6zP6XFf3Zc7fxnp0wJld/+XujpUJak5UJMiKjAcxqmh0VfYYNCV7tSyluN/zZi0/WFXX9Rk86Sn4AZHn6e98/A/N6ZHsVNCUvr0U5PCajDnAzv0xrId3Yti70FMe3aVLPfkPo5LrW7EWXWkDoZfEbYLw8p+4VvIBA4WRL4anSNrnSO43O48P9aLwpVmwnaBtyUH6FSmYvhM/E5xW0RW9VutaLgOxpvqiev4PiHW3mdx5rhwKAMeS83jht8JB9GepD+Gyvc5p3qhZgxwAVjf0g9+y2sLPuG8BrnTunfPkpdzNUh336HygCBH1LA14+Xr0AjFdigINqY3UB6PlLwE/hMrk4t0oruI/wTRiknxsmw3il3K5TsTGhSTIZW5Jf6FKxEiCCO4joi2im1SwPZjEtUMjkmYkSxpcKkncN3skwvFYqbiI41mmTX4ZEcZKSIZdc/XoL9loECGd2650XNkUr0Gh1RZ6U3wis3HLmZ+MptvB6pgJ7LO4D6SDtRxP8/IP+X0JGjX/lqzVPys0UdXI+2EP26WTUMdE04h+MWTXXjQg00bKj6Hd9D1S8AiwKp4znG1ZGyC3u5OVygn+CRjSVT/OyxzOaQvbHkJR91Uht6xi56mdbltJ+iLn1JLf/EJQFEUD/7143SrIrSQ4UT8Ake89aX85cWqxeHIBJRIHGmyrl2bGyhZ8JbSS4KUO2lJVlzoAfdj8UWZGtyW4G/uX1FGWSJ7B7w5qZS9r9voKUIfWUO5Oq9ghocQyL7BT3labho0W9wZG6M/RoPvQwCpEaf6ab7SvZ/lOXsS8n73lSTzKVIbdNnFH/4jE5u4WreQk0p/ShAS8LLbpLmT5HPX0OEG/2XMKcUreiv17DC5cOtgzSz5ycJ04xzL2Cw3bSiFSTmnnlYOdMv2h4WBVXqT0TQHZhQtLrZ3CsLzKCUQvEntdIrighrvIqZMobRo0xLJa9lZfIng3M3vIcLo6vAPib8MfpCszo6E9Mh4TqfVyE=
*/