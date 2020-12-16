// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file detail/concept_tags.hpp
/// \brief Bimap tags and concepts

#ifndef BOOST_BIMAP_DETAIL_CONCEPT_TAGS_HPP
#define BOOST_BIMAP_DETAIL_CONCEPT_TAGS_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/mpl/identity.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/bool.hpp>

namespace boost {
namespace bimaps {
namespace detail {

/// \brief Tag of {SetType}_of definition classes
/**
The {SetType}_of classes are derived from this class so it is easy to construct
metafunctions. For example now is easy to create a is_set_type_of metafunction.
                                                                                **/

struct set_type_of_tag          {};

/// \brief Tag of {SetType}_of_relation defition classes

struct set_type_of_relation_tag {};

/// \brief Tag of {Side}_based identifiers

struct side_based_tag : set_type_of_relation_tag {};

} // namespace detail


/** \struct boost::bimaps::left_based
    \brief Tag to indicate that the main view will be based on the left side.

This is convenient because the multi-index core will be more efficient.
If possible use this options or the right based one.

See also right_based.
                                                                            **/

/** \struct boost::bimaps::right_based
    \brief Tag to indicate that the main view will be based on the right side.

This is convenient because the multi-index core will be more efficient.
If possible use this options or the right based one.

See also left_based.
                                                                            **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

struct left_based : ::boost::bimaps::detail::side_based_tag
{
    // I run into troubles if I do not define bind for side based tags.
    // Maybe a more coherent way of binding the relation can be developped.
    template< class Relation > struct bind_to { typedef void type; };

    typedef mpl::bool_<true>  left_mutable_key;
    typedef mpl::bool_<true> right_mutable_key;
};

struct right_based : ::boost::bimaps::detail::side_based_tag
{
    // I run into troubles if I do not define bind for side based tags.
    // Maybe a more coherent way of binding the relation can be developped.
    template< class Relation > struct bind_to { typedef void type; };

    typedef mpl::bool_<true>  left_mutable_key;
    typedef mpl::bool_<true> right_mutable_key;
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

typedef mpl::_ _relation;

} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_DETAIL_CONCEPT_TAGS_HPP


/* concept_tags.hpp
elFWpyLXIJuQ3cjHSFsPZYhkI+chVyJ3IvuQz5EOUc2twcgkRHa2dMxja9WFyao7w0x4XlQP+k3HIFcj9yEvIB8irbE9mIqMRwqRK5A7kFeRz5CYqNbWIOQMpB31J8rfThvQRttZbQDXK++5kG3cC32/kydMHJRqyS/X9ksb6vcbHvDL8Pv9+T7bb7Df74WAX7rfb0PAL83vtzLgN9DvtyjgZ6dlqO038ES/X1zAb5Df7+MNtp/Ztx1+e2y/DOOusd1DXK9XakeyYeOrz+pLlh91VnpZti1t6lTIdZvTaLaHZG/zDngM7W3lplrtLQ8rgGHanPQ5qz1VXzca9yrP6RzrWuR1ZAD18EeI1rLxt0P2kt1es89STzaJmsvM5H0wxaM+e/sYifa1LG2z193MER9mHCsLrZ5qp48a/as9Y71XQOT3SG8PWojsjCnO/o77bMC+YAx83oQn175eKs0JNWpDLmlyi6+H0Y+R26/fKqz+uUY/OWz4xlrhlKkj/F8Kj6f9NfWe3wSnNPz7RGjdy4KUeVDdy7H9zHkgDUNjdpjyo5ySLeNOrAl254a414e4j9hu97URHtHaCDXQQ73N3BJUbwsKMdBE8mrV2y6m3kqf2bI/pIyusqKxbbfJvm+sN2Gd/XYy+U2sgWdL7dvDitWz20zjXuPJ438s+/Ty78Mpc9pjnW70bvUUyNZljh1XF9fvUTHwRRPe3P4+deyDZr0Bux7dZ8I7Klxu1UPWyjFjQTHwaMVqfalrTPhITz+rVe3xonp+/bHROQNb6E1rP4upnZ9rdG7Cqm+U0emFBjm0n5XPRKePSevNViuVI+H28/gIE7bYtnd3Os8XCxAv87zPGbAE6UEhzNB9I6see3c3Pxhs767Mpf5C2crUult65u0lP52zoGeTzHaW2Yr0jJuPvEe8qcHPuCXzSipqP9/qejHK6E7RukamDmr/2NrXGL0nnGnC+9v2wf7egPun6zOu0x4oGTBji/WMu9gbLz9WPhCUF3CeKYgw133pJ9l1e6NxF1op/A9nX+5eozObK7zWurLjSQyti3b7eNuEx8rtsV4w7rYax2zqBmOZfXbitsDhDbC1Wte1jXS72tdMlk37ObpfngO95bZtc1C5ma/ZlFy4cpN+T6uLyu0t4z5oncD/85C7raEqU6z33m/qDK3w5FplqvJTfMfa75FvGPdIT1/uofmI23WlE/zAxH2c3Dz1mnJtX+s8xKsudjL6SeadtSXivw/+3Pj3sOvBb4x7Ameoqc67Px9jTD5c86Z3eEvv8F0U97lGZyv7RFmjOcZi9zhrtZ94XaP2mbKI86RyHosR2dS38xrrtEeYp3qnfFxp4nc/F6dZ0821+Vfe92xkq+pfE+Rhfq9HPPx+BG5QWB/55fuIX8PG3Id9BgytqxorsPsrjBVwt78WGUPwVccQXBPj9e/xy1dWrdxf9PFHZxW9f9a+BVxwVphybre7zbKiXm8O/+jR9Afj5o4vDj+2wN0+4P/+mAN3u37h7R4yRoGrgPr0YJrs0XS0aF+IJTt2XWELmAZbwpGwFRwPW8PJsC08C7aDc2AHWAY7wsUwDlbDTnAZ7AxXwi7wadgV7oTdoIc0HAubwV6wFewOY2EP2BUmQ42xUB+X6Stj5+AxFqPxag/HwA5wLEyAp8IUOA4OhllwLDwNIsZ9htyyZ6i+IvO7lj3DibJHlgN7wkkwGRbDE+BkjfGYAk+EU+HJJs2+8pwGx8Gz4OkwF54Jz4bnwHPgLDgDzoc/hBUwDy6F+fAyOBPeDmfB9bAA1sAiuAUWKz8JUeqvUJ+QNz+Z/G4TpfuxyqlU+ZmrcloFM2RvLAvOh1PhAjgNlsNzFD4=
*/