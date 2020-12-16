/*!
@file
Defines `boost::hana::prepend`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_PREPEND_HPP
#define BOOST_HANA_PREPEND_HPP

#include <boost/hana/fwd/prepend.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concat.hpp>
#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/lift.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename X>
    constexpr auto prepend_t::operator()(Xs&& xs, X&& x) const {
        using M = typename hana::tag_of<Xs>::type;
        using Prepend = BOOST_HANA_DISPATCH_IF(prepend_impl<M>,
            hana::MonadPlus<M>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::MonadPlus<M>::value,
        "hana::prepend(xs, x) requires 'xs' to be a MonadPlus");
    #endif

        return Prepend::apply(static_cast<Xs&&>(xs), static_cast<X&&>(x));
    }
    //! @endcond

    template <typename M, bool condition>
    struct prepend_impl<M, when<condition>> : default_ {
        template <typename Xs, typename X>
        static constexpr auto apply(Xs&& xs, X&& x) {
            return hana::concat(hana::lift<M>(static_cast<X&&>(x)),
                                static_cast<Xs&&>(xs));
        }
    };

    template <typename S>
    struct prepend_impl<S, when<Sequence<S>::value>> {
        template <typename Xs, typename X, std::size_t ...i>
        static constexpr auto prepend_helper(Xs&& xs, X&& x, std::index_sequence<i...>) {
            return hana::make<S>(
                static_cast<X&&>(x), hana::at_c<i>(static_cast<Xs&&>(xs))...
            );
        }

        template <typename Xs, typename X>
        static constexpr auto apply(Xs&& xs, X&& x) {
            constexpr std::size_t N = decltype(hana::length(xs))::value;
            return prepend_helper(static_cast<Xs&&>(xs), static_cast<X&&>(x),
                                  std::make_index_sequence<N>{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_PREPEND_HPP

/* prepend.hpp
+Evg598l6Ttd/5+0j2P13PSftY2VO8bLhbENHq8OW4XG/1wqR3gvfhZHPndK8z2IkJOrnFCBhlEf87QcgREh6zDWVVEZ12b3vgzpAfMs5q9yHlE7g/z4Xe5N+evbYOAgm9IBZ9/wAbOyG5sHD5qXjfVux7Ihatqac6XC/hPXxj7lb8VAL9TvMxOt7YsRbc1fkZYm3KTHLZQBlxD/BtFxHhLreXJa7kEP35jm7zPmc4i0TxMuUiz7vKTsQ/5p2RfO+R6jwlD6rLnAEnQf+MXvEtm5LJqqraXYgN3xqcm4/Pjiu8vvk/tkIVvjLi7e0WhndxTN8LOd209fmtPlRpRtK3GMVmJ83o9mkLcBjB1VP7PkvgC9w3BeJ0pd4CJeSLHlj0NPfXxB13EyqV+Kttd6gGKW6odI5D2sUh+E6xN+CqeHAF+rysUx7sRp5jeLz5MIpwHfHiA7ri0XiLxeNOM1FJVp60bNeaV+7YwZ4/VezktVojSttX1fJQFamCdPiOURw1v4dpGvezJG+Lgms1paKTYTP+4j7eTJd+cPKY++g9qzNdmMR9o1Zu9NGOWcj8xFXRUQq2t7ZFvmfgZi4vOAhA9kv8rJYEMe+Tzw9Nb2xlkYcVvop8361UEx2hR1K2S41C7IVcGcfRbj6NWcjxV9D4HSY8f30L3ds59bUh+bvye+ldPfrhxUMdSZjdYLVJ+kN19evhW2021l+4hsO5FQbByUT+IoGK37vOyPtEdgXYz33QuvMfpb1w7JWlW1QEFf7HQs96pX8nuxMs6ruqz8822K9ZqU07jgZ7nUQsVyFGeKt/t43ecObsXd0KnkFMvjF7zsbcq6zgptgnch/tPO779/SMa8MrKplB3EsTPecfuck0TD4pS887bc99XkWdnqzHCa9K6w9MelGc5E2eRQXAfbAyfrYZaS5UFqtM/m+7U5H1mLOhu0kYmZjA7ajmhqc3wYVRiFYP7Xb31Ocs/qC2mHri2wRcWHRtIb0h47JH1ohM1a1bRGCedpcPL2556zNtGOQKEzvPAZfWnqolCNPpLeY77O3t04fScGMxgp217QIx1bWXF/p3fgpO5M5AoLU+dWBI2Q35O9+V26370+oesEjsN2aMw/G3C+MZAu65N/TOZLYVpnORHny23jfNnq4/0u+c7Od73tB9UN/zYe2wOBfASGNP/+NHv7sZnpytohisW9RSdasnR/W4vf4Np/mtvx2CaH8pj8ZEZbNEjCRE7f7wSntWKwObbHofObwjHuUMMcXeidmNP2opUltNw1+lGdlZT6jrioqd45V2VZYxC0nMgPjubD+76XtkG32lrdin9GffjAqE/mtNIKUzTS5pX2Tn909IPBnvtf0fof8QM7MbZPO8gxH78qOELYERDrwXGuJnWggaXO+la2wQ8TU/y/qsJlJDrjb/N6OqH6Rta5NMJJpkl4MHau/YLTtGLoOwu6wdOMUXVTnefSn7n82rVlVmfaSVAbm5DZaW+iNl2clz+3kVhhpurDt0nlzLsS1hanue1gW9WqzvgvsoD3dXVe9jhUhlpVZR9GNuyTdZRfedm8ELrvVdmaynX2Nk7N6xXYvGkLPo2no8wmEl459tyu7KA8jj0LFigeQYJ4zGXjhEfmYuy0hdVZ5BFEpQUWpJPj9LdxdntVV5fCzQ76O7fz2U5oVNPpTA65v0bQ3/kc2Uto8rzBiVo4koH+Jm8lZ2Zjk1dtX0pnS+sfykZTWhdXYCQ7iN/yWcm3hABbOE99kbnvMvdNfkFSVkKp1etqfClbbBh0GLEvL0/mrzXSPWOCjDDuwlwkWz+U53ZkGhrM8Hr4YNzrtue2e29N5q5Ez3UFKfyIVjEMiaRNdTs=
*/