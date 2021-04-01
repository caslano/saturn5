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
N0bn2EmJmroNozny/QrcxTLhI81LYXXlHvstBfLJFXHCG5wq7ltFO4KAIkkAL8KF3+OeIZe+mfvxiPXB0Y/xfxragB5flsYi0YDNxsHVBCC9QSxBJCl9KIj/gvbwJ+n6AY82HUlXl2mKtxMxifEpszmW9Gik6US/zLcXFKHJfN23yJl0YVlFF9EzQd5mZmu+yJgpWFoAj81V8ohRJ47wENI10cS2aYFVP0mDHfaUxe4dvUZRn7HIQa9uBrRsbbj6C4GrpIsLgHpxV1vtvgPoWV7Dz0sFQnOB19wmwPa2IKyMerlNoVJyHOrSy6HF2UHMeJj1++N7R2WvpI/LzVScL37/bwgHuxW1pORrncLaEOjX8eMBVPESYA1xHIyGTRnx8R/KMMFHqykC36wycOMtgzn0jTY0Zybc1gvW7jgT6NnZR1aITPJ/jN7exNF+U+cc7rvJFOLT+vSg7VCPDHucJOaCTP1iH0g27MK2RsO3NLwZgsB++TaPkzyl9sm6IS0jXC7Lpz6yE7XEBu56Di4AP1GYiZkxeevCEJq7d/Fq4FER24a4/rXF5cMrEQ==
*/