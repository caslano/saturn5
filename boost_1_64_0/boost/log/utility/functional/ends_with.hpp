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
CDwspwDeF7HF5BzjexbBG3j7gw5+mgVM65aZQ/cRS3Ioji/V5J76zip2EZ9JYxeDM41jFzE5FFuc5+UEnpb6F1vEknLpv2FxMZfaJGwj1xvk9apGF2Yy1+dSOz+KvCDx/KtOZtQ31ejCNDaUS7FFAvLqit+/4jIVkPm+JJn5eBf2rt7HOyFvluAHjR5x+fiAgVr0wrQ9t+fRtezOPNqeO7jcBiDX24k0JFOs8RX2vWMC1qibp53hEube89l0/VQvTzsbJc6Tj+hs+pYaYHWmtnkexRsd86h/Z21ytX//I5LpneGr2RRz1MmjmOP9bDrvhmC+0YKdzmxy2WlgMw11mI+Xs+laYslsaqdh5a6xaMANbSwyxB1v51DcUZlD9zm+yDO+f/FdnhZHFfdJuQ5BoEOVxb8dM5t+wyN4Nu13ymaX3QdscI5Ckmk84yzqrwrj0HM5/N+2aCML36PLo/GM+M0uuwzy5XbxM63DzHxql4x8apcrXG4o2Pt9zS6G+ONELo1pvDrb+A7Gllzafz6ZbYw/uj7qaseB5dUIxKxeNw38zZZvcA6Yy1RA5gLJ9DsCz7I6CXeXZlMMsgfzySIGme1atzbl8d7HXHUZ9FcNhVjGAwcX0PVRbIHBd7247GCQfU4yvY9xMZ/ex2iO/f+2XfgmQwGd3yvx3VxyH+N6Fut/+u/u5PP7GEliv9iia4NCuJFhYc9PUYaf+I2LfHofo0wvc3z1jQwzLFI3m66l9+dTLPJNFv13fo7n07j7FV3Zg885/3XMAIfquMsUj7xWoH2LGfi6M5AFGh4RfCZyq05+OY92eKmKxR7hnwvo2uBWgcG/16CXHe9EJZIpLjk4m8Y8TjGesAdUQHHJitkUl5wooLhkJcsnxP+3ufrq4CGSaczj0QKKTZ4oMLj/vc01Vg45wqMe/qZt6VlE9wHqFhnc/+ZyZZC7wHrt9k4htc9HhQb3v7frZPaujnqYydxUSNfGuwspDi3jMhWQ2dJ87VZWSPHJwkKKTy5td7Xn0Ef53NPAHO8V0brfRJ4qfs9oh2vuGZqszT2GsY+82ezf/9R/g2C2+/gFPCynGFp5sjD3ZBWxeLrbGYdDXAcZdGhs3f7zimj7ryyi7V9/p6v9h/pIpnGPGbPpfY1xs/l9DU/hvkYqljNZ0D1LV86wpXCyymLd+VYxPVv1+2KDf/+Cy5RB5lBrH99aTO28p5iuk4J36WTKzrHbr47pPetiik9ykBcoyEzXyRz6e1VWJXM/74nvNxT8fFQxXWOd3uXy8+Ex2u0N0zY9MIdilINz6Lgx6HEmtwHIDbXGKL8U0njIH4uNz1h9UkjXWM3mGGOU8sd1NrhsjVE6zKF+HjmH+nlAhc7/XjLHKN8WUozScA7FKF8VUozSaA4d39MrXHYa0atmjPJICV0zlpdQO13nchuAXA+IjFhglKvYH8uF8eiVIjoe3UL9i8n3p+wlxvc5ona77DT8BGB5i/EouISuG1uX0P53QC+zwhqnXCqidzrOFBmfu7o9h97pkJ5w7ZeMbFJ9q8P0O+ZzaXx8MfK8xPPMXGYo2OVP1hjlXDGNkXxSYnzual8x7T/flhifu7rEdZBBh4PWGMVnLvW3esBzxygxe1z9Z8TD5hjlVDGNk3xaQjFKZTHFKJ+X0L31ij2uukR7qHUV2F03/Xdy59G1Uco8ik2i97qwycgPzLHJB3Pp/Y7wQva9W/33wOfROMmrc43jJD8U0DjJubnGcZIdXE8Z9NwIncvCjn+ZS/f9vwae+7/t3WifTubM6lseZtjk7kK6nj45l2ITT4Ox8I251JYlurKjP6mOlJjhkg/nGcdJ3pyn3fEQcMlFvey9+lNYFt8=
*/