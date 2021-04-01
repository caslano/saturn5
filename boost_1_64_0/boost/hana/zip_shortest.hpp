/*!
@file
Defines `boost::hana::zip_shortest`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ZIP_SHORTEST_HPP
#define BOOST_HANA_ZIP_SHORTEST_HPP

#include <boost/hana/fwd/zip_shortest.hpp>

#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/fast_and.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/zip_shortest_with.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename ...Ys>
    constexpr auto zip_shortest_t::operator()(Xs&& xs, Ys&& ...ys) const {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(detail::fast_and<
            hana::Sequence<Xs>::value, hana::Sequence<Ys>::value...
        >::value,
        "hana::zip_shortest(xs, ys...) requires 'xs' and 'ys...' to be Sequences");
    #endif

        return zip_shortest_impl<typename hana::tag_of<Xs>::type>::apply(
            static_cast<Xs&&>(xs),
            static_cast<Ys&&>(ys)...
        );
    }
    //! @endcond

    template <typename S, bool condition>
    struct zip_shortest_impl<S, when<condition>> : default_ {
        template <typename ...Xs>
        static constexpr decltype(auto) apply(Xs&& ...xs) {
            return hana::zip_shortest_with(hana::make_tuple,
                                           static_cast<Xs&&>(xs)...);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ZIP_SHORTEST_HPP

/* zip_shortest.hpp
q4y0Aq68baZSMg7ldsRF7rZuvH5+jg0FQaA24XsmXpWUcPH8+SCBblfiIuTgePe2A+YOBjzJOgV+z1O/l4M+eBC4onNf6idg8o2rkewAgqpH64hyn+RUA5wsuK1F2JGE4WD/tMeSRuwiE6ltoHLs1Kfil0x2BTVniSA+LtmjoxWZ/h+X5E5eGbFaSmmQTj4QYooQ1Y1+N1bJntvym4P0pTfrLTwbLOOLDXSlSjdRA63I24xwiQFVTVx/i3S+GtkQozXMFRT8HkqmdMUCSzRgAqN4+HkX4Xe6eFeKDXp4pPkKAnDhbw352VqoilMcUbvCNHkNaNKBCQX3rLL2lqf4y/TUaAcnujuzFpG5SHgDGJJonAj9PGLPPHCMuBGL34edYmtduaya5Ad3sA3NPqdDAnl8SH1QWRW8rwjYedBW8lCrTbKtGmtB0D9CJzGgXIaW0Oi7ZztongAg4wT9DTPIbCPMcLlWvocLF5Z/iqUtKK8fezh/YQZlLH1XnBm/2f4JlggWaycRGHxFn0eH6gL2DZsEd9UKvWKCFh/SAidbYL17Z5FwF452iYk29Q==
*/