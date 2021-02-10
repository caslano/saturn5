//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_IMPL_ERROR_HPP
#define BOOST_BEAST_IMPL_ERROR_HPP

#include <type_traits>

namespace boost {
namespace system {
template<>
struct is_error_code_enum<::boost::beast::error>
{
    static bool const value = true;
};
template<>
struct is_error_condition_enum<::boost::beast::condition>
{
    static bool const value = true;
};
} // system
} // boost

namespace boost {
namespace beast {

BOOST_BEAST_DECL
error_code
make_error_code(error e);

BOOST_BEAST_DECL
error_condition
make_error_condition(condition c);

} // beast
} // boost

#endif

/* error.hpp
W28EAAB1CgAAKgAJAGN1cmwtbWFzdGVyL2RvY3MvZXhhbXBsZXMvaHJlZl9leHRyYWN0b3IuY1VUBQABtkgkYK1VbW/aSBD+7l8xx6kqpi4OUaWeCo0OAbmioxDxcrmIRNZir/G2ttfaXUNyTf/7zdi8X3rJhxrB7s7OM8/Ms+PFrf28x4IaPPt4xdfDB8cCcaXkF+6bp7097xHKD6JucXyOxIU95NGz4XnII1QLiLdhadHc854juqXc6Mcl5K1HU7QgjJAdmT0osYwMVDs2nJ81zuEtDudnDnRZKngME8PTBVdLB1pBYfk9Yvf3dc0vHOAGWFzfhJpGQoOWoVkzxQHnsfB5qnkATEPAta/EAhciBRNxCEXMoTO6uukP/3BgHQk/oiAPMgcdyTwOIGIrDor7XKzKGBlTBmSIcAweCG0wYG6ETOvIzcFwlWiKQfQs1hLYiomYLZCIGYiMyfQH1/VzFWP2biB97frb8uuRSXaV3GASCXsAmRkwEnLNHSBPBxIZiJBGFASNWb6IhY6cfTZIlQauVKB5HFMsxAmuy7Q5TDbyOOQGGWYsDA1appqo1pFMjhxRR4oS5ipFItQBnQKJMjuQpwFXhXNR+ZZio2kh8A+PZp9vADLFZKDSnkB/UoEF00I7cN2ffhrN
*/