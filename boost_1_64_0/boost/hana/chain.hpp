/*!
@file
Defines `boost::hana::chain`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CHAIN_HPP
#define BOOST_HANA_CHAIN_HPP

#include <boost/hana/fwd/chain.hpp>

#include <boost/hana/concept/monad.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/flatten.hpp>
#include <boost/hana/transform.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename F>
    constexpr decltype(auto) chain_t::operator()(Xs&& xs, F&& f) const {
        using M = typename hana::tag_of<Xs>::type;
        using Chain = BOOST_HANA_DISPATCH_IF(chain_impl<M>,
            hana::Monad<M>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Monad<M>::value,
        "hana::chain(xs, f) requires 'xs' to be a Monad");
    #endif

        return Chain::apply(static_cast<Xs&&>(xs), static_cast<F&&>(f));
    }
    //! @endcond

    template <typename M, bool condition>
    struct chain_impl<M, when<condition>> : default_ {
        template <typename Xs, typename F>
        static constexpr auto apply(Xs&& xs, F&& f) {
            return hana::flatten(hana::transform(static_cast<Xs&&>(xs),
                                                 static_cast<F&&>(f)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CHAIN_HPP

/* chain.hpp
o08qCvmcoMRJiQHsmB0ZstH0/rJN7cVpVDkwAamuj5vunlToJAAuraEQOF4FsOFPj2dQa5ZvMu1qKSdaGH2zOQSmxsZ9Boo+ZCKoKr4yVv5xc+234qn1HZhEc/BGWCgorJxLmBi9oXIKs6XLyPbNSrgG15tb+wNlqozZ2d8YMZRI2kMe/InWVIpfcZODAw/PxXqs8Nu5OU6KfJFLR+7UnPhsmHIwcjPr8pzaszi8nPq6AB/mQ4OmNT/ZEUoex8nMnHc6fm3+HdutEGj1ui+SqtCXD2WjePAxhPDtNKpJ76Yb9jugNl5698akN4RfSob0i3WoM+Cz+FjfKxcydu55RtDDmpPC6bN2ztEUaLdMlt0AnaQY9j4vhT8ZAAK185SEGtYp75jht65xn+CzP78Q30NIYmhN2393haX/4vEeDy3pkR3dnNhWP4pA/VBNw+pULuuPz270KAYS3KkYbDIhQoS8c7vB8fc95PBweXljCGoUB2jM8XIIlw3UyBIWelm4jmUXX9Y95zWjIM8ZU5YuLlOvHOZWt09gIPoyP/4MTjJn2fR3rRBIM1fJ+Q==
*/