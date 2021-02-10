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
xFn5Dx3UDxlfNJYdrun6megaCc8KEuSS4buiezToLL6ygqu+qYF9Jjx0DA8WIYebYi9NXfMUzl9uL2hh7JWhSAFnZ5Nuo8t+TZeiPnauLeqzrv4I9THIR6tvtzDkR2vRQigRf4Eai5ci2EktSdwfVpXxdbqL5UauVJmxlti8P/GVCpxo/m8CKLRu0VkZf//fKO2xuvpjTVXKqapaTMw++nhKhe52UMcFmH8hhV9sOZX2nkveCJYuRffDzv8AUEsDBAoAAAAIAC1nSlJot/I63wUAAJUQAAAoAAkAY3VybC1tYXN0ZXIvZG9jcy9leGFtcGxlcy9mdHAtd2lsZGNhcmQuY1VUBQABtkgkYM1XbU/jRhD+nl8xl+oqJ/KRcG2l3vGihiRARC5BIRShUlkbe4235+xa3jWBu+O/d2ZtxwFC4KSrVCNiZz0zzzOz87JpNX/cVYMmvHh59t/DC+9W4zRV/3DfrJf2vG+Q/6HWFd5fAmlBpfLNa8DLKt/AsSpegbJLz573EtAVcaOPFmleefSIK6hGml2V3KXiOjLgdBuw/eHD7/AO3rfft13oMSl4DGeGyxlPr13YDezKHxG7vd3SfN8FboDFW4WpaSQ0aBWaBUs54HMsfC41D4BpCLj2UzHDL0KCiTiEIubQ
*/