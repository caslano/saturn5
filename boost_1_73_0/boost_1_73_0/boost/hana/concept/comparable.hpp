/*!
@file
Defines `boost::hana::Comparable`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_COMPARABLE_HPP
#define BOOST_HANA_CONCEPT_COMPARABLE_HPP

#include <boost/hana/fwd/concept/comparable.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/equal.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename T>
    struct Comparable
        : hana::integral_constant<bool,
            !is_default<equal_impl<typename tag_of<T>::type,
                                   typename tag_of<T>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_COMPARABLE_HPP

/* comparable.hpp
Qf9HnwP/c9o2Veg1A57qbrT5G3yGLWZ/rm14/KfQC/Fz/hPIBr0B/CzG
*/