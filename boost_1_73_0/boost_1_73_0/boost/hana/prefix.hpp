/*!
@file
Defines `boost::hana::prefix`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_PREFIX_HPP
#define BOOST_HANA_PREFIX_HPP

#include <boost/hana/fwd/prefix.hpp>

#include <boost/hana/append.hpp>
#include <boost/hana/chain.hpp>
#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/functional/partial.hpp>
#include <boost/hana/lift.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pref>
    constexpr auto prefix_t::operator()(Xs&& xs, Pref&& pref) const {
        using M = typename hana::tag_of<Xs>::type;
        using Prefix = BOOST_HANA_DISPATCH_IF(prefix_impl<M>,
            hana::MonadPlus<M>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::MonadPlus<M>::value,
        "hana::prefix(xs, pref) requires 'xs' to be a MonadPlus");
    #endif

        return Prefix::apply(static_cast<Xs&&>(xs), static_cast<Pref&&>(pref));
    }
    //! @endcond

    template <typename M, bool condition>
    struct prefix_impl<M, when<condition>> : default_ {
        template <typename Xs, typename Z>
        static constexpr decltype(auto) apply(Xs&& xs, Z&& z) {
            return hana::chain(static_cast<Xs&&>(xs),
                hana::partial(hana::append, hana::lift<M>(static_cast<Z&&>(z))));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_PREFIX_HPP

/* prefix.hpp
Uw55XbRAo4Bt+96JZjPFdSagBKH1u7V9F6mtfB+3Q2zORVM6Klno9+H/1jVwu/vEqS2i6ANubfr8aPphXwRqumy4Dy/CqGb3Wm1vEhXUMDOYfTJ1RNPh36npGcPdRjHKZxQ0i5pz/p5XF/FT182WZJOyjR+qZInVwynJeZYhXjJ642ItSX2mDeCfMSV5f2Jlc6ckj8hETe6ARB8sfdw7DcQXjCcKdaqwSSolvbKathrzwnthyMhyr9CUQswABSdoDml54s0q+5KQZXZ/FYHEFYnTLUmhMp/PaEJL0aeFwL32Fn3/SO7jtPM19oB0V1lCVOoCcwClhmbbN2wIE2BYiOL8oSEGbMqZ0YVjK25fuZMbKq5iFSPMVK/AZZRWWOYWXJUF058VYdjr36Ip3eiwe9IFGeT0SxsuwNmmcau3f33N7tiQC9fYraa26fJH80zj41dQorNYwkDC5aaHRA6YqQ2JCJ7G+oh0zuf4vtM7zXxkRnJwza7WabzxqNlUrxHQN4jcb5TOAAWuIko1devdt0APJAlql9VIH1aFLHsUuebqfB4kgmgdT/3k0QadnKw4/wTL6L/Qem/bCi1ToeXRvslBwj3tXgARwrdT7QqzTb2CM8xBq02zwFHu0cltlsl//7X210ocRh8AkPBm
*/