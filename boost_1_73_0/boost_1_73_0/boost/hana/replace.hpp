/*!
@file
Defines `boost::hana::replace`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REPLACE_HPP
#define BOOST_HANA_REPLACE_HPP

#include <boost/hana/fwd/replace.hpp>

#include <boost/hana/concept/functor.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/replace_if.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename OldVal, typename NewVal>
    constexpr auto replace_t::operator()(Xs&& xs, OldVal&& oldval, NewVal&& newval) const {
        using S = typename hana::tag_of<Xs>::type;
        using Replace = BOOST_HANA_DISPATCH_IF(replace_impl<S>,
            hana::Functor<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Functor<S>::value,
        "hana::replace(xs, oldval, newval) requires 'xs' to be a Functor");
    #endif

        return Replace::apply(static_cast<Xs&&>(xs),
                              static_cast<OldVal&&>(oldval),
                              static_cast<NewVal&&>(newval));
    }
    //! @endcond

    template <typename Fun, bool condition>
    struct replace_impl<Fun, when<condition>> : default_ {
        template <typename Xs, typename OldVal, typename NewVal>
        static constexpr decltype(auto)
        apply(Xs&& xs, OldVal&& oldval, NewVal&& newval) {
            return hana::replace_if(
                static_cast<Xs&&>(xs),
                hana::equal.to(static_cast<OldVal&&>(oldval)),
                static_cast<NewVal&&>(newval)
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_REPLACE_HPP

/* replace.hpp
jzN1AH6g3P+Aheax1goei1bQyCkgjNNgpggXO2WmwalgNdjX/KAwguxXFsoA2b+gtOepNWrhthT9OrgxUx0RLEmMQXpf1+gQbDSdo4MDUBb22ueNLfgQCgsgGATxV+E/+Xt8tjXFltutk9FsPRkyu/FblpVrKm3iO2I+p/HSgcAvrqYI0TVeDQZygTw7Da8oOuz+MnjTldLbo6NwD9ccPZB2JOyeyX2DApOtCcaD/tkw1edGfhKqB3TZf9OXC5fWFfDPnmr49oyJciLWXds6IZcn42xtatVPEn+srEQBmUFJB0Knv7hcjMuCcjWLZHbWU4Z4L3LsYtTUk875+cvOyRud24U8S9mBfEoJYZWELPeyyM7OEuU6UYdJ4gjE56Bkw28ZMWQrG9V3PE3TI9pUlskVn+5QtBt4QPFI8Ae8Ma5EAuRDrbC87fz7YCiCK1fBzahYRC1wWQoIsXD3+NB9O+Zb7Nl9W8E67ym147IaJ+c9vGf7unt+PihWPOEMu9f+YhFtrP+2Mxp3h+6b7vtKIJhvZBOIs16/N3rdPa0EwJdCgYGVQhl1h4CzqoHI5ZQNA5H6ZI4tGYQAYGFwI4TqcQiMzeMYdv/jsjsa8yZHhuFuEdIQMzkD/WGhjUjdCEXwagBRMovtilwgz6NP
*/