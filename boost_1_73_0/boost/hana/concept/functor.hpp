/*!
@file
Defines `boost::hana::Functor`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_FUNCTOR_HPP
#define BOOST_HANA_CONCEPT_FUNCTOR_HPP

#include <boost/hana/fwd/concept/functor.hpp>

#include <boost/hana/adjust_if.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/transform.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename F>
    struct Functor
        : hana::integral_constant<bool,
            !is_default<transform_impl<typename tag_of<F>::type>>::value ||
            !is_default<adjust_if_impl<typename tag_of<F>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_FUNCTOR_HPP

/* functor.hpp
e4GBiVthW1o97P79gYOwH/2NByhdokKW+aA+LbpEUc6Pnn+xNQ59iSf6x6p/vPmJi+9Nk17OdzYMU+6dLPfjWq6TENwqgZvqcvzQlZIU81LUZpjF9oas4N0ixwcZQlRX9eQ0VDw/0fN9lgS5xn7Cb9hCeBHPWTMFEK5G2A5RgXgqioT6tQhrSwoNxO7KC02IqF9E5bN+VnCJIgDwDKmxOHGMDkzW9pDW5swch3ZsRDtIiFU/
*/