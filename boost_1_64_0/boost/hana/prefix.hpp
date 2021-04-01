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
ln9FB7At135OPIWPKHuBWIWujAh4OaKjFOqS3X7YnWGTp23T9p0K7wvceoYxFfsoYBRM0nOiZMigglJ10J2Q7DVt66hn5Lw3+CbNBTDCkiDEpJO3WbE6eUYh5JUYpj/+ywqymuP1QMjH7ecDoaTHuxnfiCMKPpevtBMpWmeeiOHbG9LuEomdpKo/lY3mYYnFCjhpx6XA57Z/T8zUPhwS1krp54+wpqX+kQJtT8vCOOHEyHqBGktuN9xeIUfVkziihKpwFqR1O5+Rmw6oM+pD9xaV6bcqI4WFEqnW+dmBo/2oA1rS4oZpGWVZy3zqMX4i7y5dB57Z2GQwwSYOkwgA6czYVMCgns33DcB/XcQnrKPrJ5mHfgiOqtIF16sX5ApMFtPc2I2wDfs8FIETBt1uB1WZ64A4mLd2mF5EMgaT+2H/+CFXNfwyct+RHxDpfwB222tUrfFblJ61nJDcRiHSIgnYYsS7HU73KmOCn36iNOJpXpwyYoyrfGAwtwAXuqQPA+u4m/8LTe4xGFKayjJvK4D/uY6L5M1ldoQ9/Zea1xh0hL9DhxTYMXpAtw==
*/