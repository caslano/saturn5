/*!
@file
Defines operators for Searchables.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_OPERATORS_SEARCHABLE_HPP
#define BOOST_HANA_DETAIL_OPERATORS_SEARCHABLE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/fwd/at_key.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Derived>
    struct searchable_operators {
        template <typename Key>
        constexpr decltype(auto) operator[](Key&& key) & {
            return hana::at_key(static_cast<Derived&>(*this),
                                static_cast<Key&&>(key));
        }

        template <typename Key>
        constexpr decltype(auto) operator[](Key&& key) && {
            return hana::at_key(static_cast<Derived&&>(*this),
                                static_cast<Key&&>(key));
        }

        template <typename Key>
        constexpr decltype(auto) operator[](Key&& key) const& {
            return hana::at_key(static_cast<Derived const&>(*this),
                                static_cast<Key&&>(key));
        }
    };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_OPERATORS_SEARCHABLE_HPP

/* searchable.hpp
q/zL6VCViWjle/w+mdQ19Bv2Df95jDV/m+BXeALVsOYwWt7F/tV16nSGXWd3p7/rbMGf3X7POXBD3wucceqFl1581XO+n9GT/3Xtfv68nXhveo6XOm6wXQGn/7znnPjTG+cvfvqPhRuGACWE3/j9f10tXD/YnkaLN9uiNxfXfuIk0Ty9dWPPge+BP/XCxJs5buLMvGQa+5fwww+d9Npz5n7gOcPTs1+OTt71nNtrf3qNQO6ilZNcR6tg5ly7nzwn9qae/4lhLN04daI5VAfgMz9JAeAq9aNwG9r2nNSLFwnCwObdIIkc9xP00b2EhtzUuU7TZbL/+PF0FQeAgMezaJo8nsqRb1+ni0CO5BfoxMK9c6Jl6qSRs0q8noMle84imvlz/As4hYfL1WXgJ9e9rDfQVDh7HMVO4gUBwoJ6vpdwtz1nLNDTw2LOEnrsp/gnicIEm7q9jhZGQcAjQpmv4hAaAjxAoVkEaO45q3DmxVSYRi6bEDglBJdOTdbfmROF0BlnYzB2jsYbzqWb+EnP+fno4v3pxwvn58H5+eDk4hfn9NAZnPyCwH48OjkA6vGhsdjxPi9jL4HGY8dfLAPfm4k2v97n8YMHj2kU42gVTwXlzKFBNwgc/3RMqFy4U/g29mB2vYvYDZNlFKdb
*/