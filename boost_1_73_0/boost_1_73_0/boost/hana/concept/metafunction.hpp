/*!
@file
Defines `boost::hana::Metafunction`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_METAFUNCTION_HPP
#define BOOST_HANA_CONCEPT_METAFUNCTION_HPP

#include <boost/hana/fwd/concept/metafunction.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    namespace detail {
        template <typename F, typename Tag = typename tag_of<F>::type>
        struct metafunction_dispatch
            : hana::integral_constant<bool,
                Metafunction<Tag>::value
            >
        { };

        template <typename F>
        struct metafunction_dispatch<F, F>
            : hana::integral_constant<bool, false>
        { };
    }

    template <typename F>
    struct Metafunction
        : detail::metafunction_dispatch<F>
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_METAFUNCTION_HPP

/* metafunction.hpp
bmmncdUv85wajW6p0spW4UahyGwuzZYqFYFRl8pojs2l0SKJ6DrYbX+0SbwXP/wocrJf/B3nt2j+ATaVP4fFtv8AUEsDBAoAAAAIAC1nSlIF68rUKgIAANAEAAAdAAkAY3VybC1tYXN0ZXIvbGliL3Z0bHMvcnVzdGxzLmhVVAUAAbZIJGCtU1tP2zAUfu+vOCovgLIE8bihaVVhazdUUC9ClZAsNznBnhw78rEpSP3xO04DbBJTX3DV2vU538Wfk+L048YATuHgEN1X8OC5Q9x69xvL8H63EDvYfxh1z/MhkQLeIDtxAochOzjuIKJXuUhrIQ4J3Sdv6adIyHuRlrzDsIQcu/bZ6wcV4Hh8Audn52cZ/JSl28DE1XUj7aeRrTxuKYOLBx1U3HxTfUHuC3npmq8921JpAnJ12EqPwGujS7SEFUiCCqn0esN/tIWgEGptEMY3t+vp7EcGW6VLlUieXQRSLpoKlHxE8FiiftxztNIHcDXDmbzSFJgwBu1sztoIAX1DiSPJS0MO5KPURm5YSAZQIbT0uSjK6E1OWFSupKJ8SSBXoTF5f5I1m2jkM7g2QHAQCTNInRk0rtJ1mtE/8GYbN0aTyt7csJStCueB0JjExTiNtLeNsOjjyVIbtOxYhzSRs5Sktso1
*/