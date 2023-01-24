/*!
@file
Defines `boost::hana::fill`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FILL_HPP
#define BOOST_HANA_FILL_HPP

#include <boost/hana/fwd/fill.hpp>

#include <boost/hana/concept/functor.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/functional/always.hpp>
#include <boost/hana/transform.hpp>
#include <boost/hana/unpack.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Value>
    constexpr auto fill_t::operator()(Xs&& xs, Value&& value) const {
        using S = typename hana::tag_of<Xs>::type;
        using Fill = BOOST_HANA_DISPATCH_IF(fill_impl<S>,
            hana::Functor<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Functor<S>::value,
        "hana::fill(xs, value) requires 'xs' to be a Functor");
    #endif

        return Fill::apply(static_cast<Xs&&>(xs),
                           static_cast<Value&&>(value));
    }
    //! @endcond

    template <typename Fun, bool condition>
    struct fill_impl<Fun, when<condition>> : default_ {
        template <typename Xs, typename Value>
        static constexpr auto apply(Xs&& xs, Value&& v) {
            return hana::transform(static_cast<Xs&&>(xs),
                                   hana::always(static_cast<Value&&>(v))
            );
        }
    };

    template <typename S>
    struct fill_impl<S, when<Sequence<S>::value>> {
        //! @cond
        template <typename V>
        struct filler {
            V const& v;
            template <typename ...Xs>
            constexpr auto operator()(Xs const& ...xs) const {
                return hana::make<S>(((void)xs, v)...);
            }
        };
        //! @endcond

        template <typename Xs, typename V>
        static constexpr auto apply(Xs const& xs, V const& v) {
            return hana::unpack(xs, filler<V>{v});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FILL_HPP

/* fill.hpp
o8BpWzqwxSyXL/ud0E9vQu1ELS3Ru9qTb0FB4cnHKyYd/FyflrzDzKNyJZFYaK8Mn3sn+0xYcFHOcm+knTmKhnQxZSJ8UeqUxr6DL874keCT83ZXK8woyCnQhjEMpSsFmRTGwPdeiLj+w9SRh37+X4SIktTLq05eZcyDf+CiD8uvl+v21r7RT/68cWLeqzmEsybHFgD5DOilU7pQpHoJwDL9H7LU+gd8AFv5RhKH/Zo3Iv2afufu+X7HZ81zxmTdz+/pedDTNWZ2gPd5DT5zvhD/4++14nIxswV3ff7uXP0tzYZi82FODWcnwrsz1iXOA07R3/NRnAcUxPA+075/1vtNP6NtJbpz12CkQLWrrii9Q3ernKqWE6m/5lkTVmsppB/35FbTiL9GbtcgnGLqZe+w8rHj+9ty3Jwspg1CnQVfYx16fX4d1EQZnBpKCTrRiXoi9VOjJkjEIFIXLaD54t5Aaf7HOYIsS8Sz1aHlYVJz6VSnL/ecmtstvhiqHq5QkKrqTpuPyj7e22Tzm53Hz9wNzUPdtewOP19X6MgxS8rhzucnO98W7YTtGnhhLXyXumv6qn3OiwH933f5sa5NrKX2rm2sY37ztvgNeTqHwxNPaiv7R3qJBKQNFPzJPw1i6oJJ9qO3UMT41bkdSwk2kOotA2f59RDzx7DQduN687MXssbEDO8TQvLm4V5Zz5HyP1gIheVWoC4SexDR
*/