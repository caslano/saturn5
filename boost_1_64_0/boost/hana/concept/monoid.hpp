/*!
@file
Defines `boost::hana::Monoid`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_MONOID_HPP
#define BOOST_HANA_CONCEPT_MONOID_HPP

#include <boost/hana/fwd/concept/monoid.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/plus.hpp>
#include <boost/hana/zero.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename M>
    struct Monoid
        : hana::integral_constant<bool,
            !is_default<zero_impl<typename tag_of<M>::type>>::value &&
            !is_default<plus_impl<typename tag_of<M>::type,
                                  typename tag_of<M>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_MONOID_HPP

/* monoid.hpp
2P1lkOw4+qQvZZ5vZLHKOxIqVJ2KfzfZvQCBxXooyTjwlsdBjTcx4QsiKiCFrkMtf3T5Cb5wTeFuOC+/A2k/fO/5ijSNaolVRVr91vLtQsjVngTElfWl26Yf7RH1pXKdk0CsjUpbYNwJbqtEc1l8T1H3PDEBU6jRfgShHqQp/+jEWjsAY7SURjNgznX2+lCpbDdF31M8KuYyU7a5cEaEbBqlGVFpAIbmKWsJoyTE6NSVBMz3RbImG2RrzfIZDsMcuE0KC+esFaADhEAJoR2BRkK4z9ZGhT88Zh62eKSs1cVjmd1DnsKb5t7ASkNrF7q7DdQP8xJtB4qXGH2Bh5VDQTNQ4sF0nGL7AiIPrQ7ad9RE9pa5vRiNJs7wpVEBeevfAqQAiaZzkIQT78PebNsbeWJUI2O4uNu2nsVAbamuQRzZ203P26VazfVnxoiuUkai8d6ime1VnOelUTy8CR/8sH1ZH246mkDotv0W4OANDFHXsPrQzXGUb3c+mmIJuMZntVbmmBf7bL2H+opW7l7MvZOkWDdXv/jZuCBgrYEv5JpwkHA6Ummvz0MR0Q==
*/