/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   ends_with.hpp
 * \author Andrey Semashev
 * \date   30.03.2008
 *
 * This header contains a predicate for checking if the provided string ends with a substring.
 */

#ifndef BOOST_LOG_UTILITY_FUNCTIONAL_ENDS_WITH_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FUNCTIONAL_ENDS_WITH_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

//! The \c ends_with functor
struct ends_with_fun
{
    typedef bool result_type;

    template< typename T, typename U >
    bool operator() (T const& left, U const& right) const
    {
        typedef typename T::const_reverse_iterator left_iterator;
        typedef typename U::const_reverse_iterator right_iterator;

        left_iterator left_it = left.rbegin(), left_end = left.rend();
        right_iterator right_it = right.rbegin(), right_end = right.rend();
        for (; left_it != left_end && right_it != right_end; ++left_it, ++right_it)
        {
            if (*left_it != *right_it)
                break;
        }
        return right_it == right_end;
    }
};

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_FUNCTIONAL_ENDS_WITH_HPP_INCLUDED_

/* ends_with.hpp
zFFUM43DlHEmeFy0NtEnprgSHhKFDY39G34EXQGLFKrXLAxd+VSGAaQfDPSHuaCWwp4ZWj8W2kMqFdkcUcc6jcx8tGpvEgVio+F8qX1MwTSoMEQtEAJZMuQeZe2j+wHTS2A6FwqyXo8ClAcb6wxpdA4H++p3XBNzEZUjQf8obFHrAejQGJzgG9wSjRWgkdw+R/OJ92cUDtkbeskbEimUFbVT/2P9+fKCjdYEqw+fga7VNo82cM+zQVsbHfJJPNn+k13Th8pJquJYjRrrlm+WEOl/w5Y7j0DJ/omaG/DKsDppmQ0y9Dt200RGheCLUMHuu2Unva0gJYVsxeQlrJtAeB0STfTrMp2i+mcg/KmSZiTlsBXoY4thMyqyhamwFIrzCoafnFhsqE4IzwUA2PMsQ1VLW5zqr9iAAcpHiZ1ZP6LxlIzwkEWHlBV0Yg9nX8EoTF5lx9UJC7sd0wCpPBrWLv7C6KvWF+gQ5cPCXNh33ka+hmZjjoOpqiW17ZMRgBvSVlm/vJkxpT/yKXh/XekgYuY8bGLSrPD7v1Gc1bCvxr7moMsu7xCgK3+JCA==
*/