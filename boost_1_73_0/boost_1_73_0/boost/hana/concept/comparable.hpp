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
NFmC2b40JHJ5GXA6cCnwfOCVQMzT1FXA+UA0SeIm4NVAyLRqB94DXA78PvAaIOvi60aRnueY6jzNQN2O9pSj7XouZyR6BBsX3aWKPq6bv7wz1P9kzjuFC7bcCUq05zT8607Rns0NDfMGPL3wt1wa1RkUV6YdFNc/Gs35JyCNlW8bDfpnIMP8Fci8vmvE9UxXs2eG7exCaGscrT/N6Z8qV+ip8jBWsGjSWFeuR4BK05olbPXeqFLNfqcoEQwW9ck=
*/