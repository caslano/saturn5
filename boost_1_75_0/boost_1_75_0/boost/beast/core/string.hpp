//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_STRING_HPP
#define BOOST_BEAST_STRING_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/string_type.hpp>

namespace boost {
namespace beast {

/** Returns `true` if two strings are equal, using a case-insensitive comparison.

    The case-comparison operation is defined only for low-ASCII characters.

    @param lhs The string on the left side of the equality

    @param rhs The string on the right side of the equality
*/
BOOST_BEAST_DECL
bool
iequals(
    beast::string_view lhs,
    beast::string_view rhs);

/** A case-insensitive less predicate for strings.

    The case-comparison operation is defined only for low-ASCII characters.
*/
struct iless
{
    BOOST_BEAST_DECL
    bool
    operator()(
        string_view lhs,
        string_view rhs) const;
};

/** A case-insensitive equality predicate for strings.

    The case-comparison operation is defined only for low-ASCII characters.
*/
struct iequal
{
    bool
    operator()(
        string_view lhs,
        string_view rhs) const
    {
        return iequals(lhs, rhs);
    }
};

} // beast
} // boost

#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/core/impl/string.ipp>
#endif

#endif

/* string.hpp
2VG1RkbIdpfFVD9BMngpNeFX7mChOnVX60Er3+nGK6WYDVnX8um1/CxC9O0yzMGeyK3r21wma6Ec8AzmZ6Q7IQO7S73vGQfWEeSXw1YoG4oXc1gmR/6MKrNUvTkPOON8/ZjxUpzU9WN08JXGp8Ey/XwT/3W5/Gpdv/tp+302b9Ie6ND0cJRhxTSnsyunDhGn9vHb95ObDdaYHxuUtLLJ8tIDPtask8hFj0/ndDFFtHp13Wi/f10lZqEF4PGu/+70bjsA5Tistc8fPV/GWePpeuAXE3Rl+OEB3MdZbNwVXgwf65TmeU3CfSgmO+wpIY5p+tnEyvvzyfAvs8p1B+JCDoxwcDLK/2tWGfCftoXZeP5yFjNyNmN2t7I917ZRINHA7awLQkhsvMuZF5K2RRy40d7QBqasp55XmuXUVi99F2s0owUmkaZAXF+neqNfBuc+gy3fCuxG0KurE5E8XUqYCllLGq3SPytqfE/jiLyOpcYFWwI8LsYYpwq+yAMjCy2cmh8zvSffJwQfzzoOna5744zsf+yb4UoBpwRcvBkxx7O+Un5PooPvQSnw9QaBGL+SecvA6FqRyv19w1UfWYnk2g9rrPmVmAAzsHi5T8hZP2X6vtAkCKwA/HDHZKJzjq43BYTQMGn6Rm9EC1a/eYJ6DnLcg4Gd1LnZG7hFQ7mxSC2qpD5chKsfNL8HSLYzYseQnkwQXsXHBE8p8Lmb
*/