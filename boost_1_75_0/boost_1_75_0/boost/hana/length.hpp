/*!
@file
Defines `boost::hana::length`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_LENGTH_HPP
#define BOOST_HANA_LENGTH_HPP

#include <boost/hana/fwd/length.hpp>

#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/unpack.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr auto length_t::operator()(Xs const& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using Length = BOOST_HANA_DISPATCH_IF(length_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Foldable<S>::value,
        "hana::length(xs) requires 'xs' to be Foldable");
    #endif

        return Length::apply(xs);
    }
    //! @endcond

    namespace detail {
        struct argn {
            template <typename ...Xs>
            constexpr hana::size_t<sizeof...(Xs)> operator()(Xs const& ...) const
            { return {}; }
        };
    }

    template <typename T, bool condition>
    struct length_impl<T, when<condition>> : default_ {
        template <typename Xs>
        static constexpr auto apply(Xs const& xs) {
            return hana::unpack(xs, detail::argn{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_LENGTH_HPP

/* length.hpp
v8hONfnw2U1FKydq733SaLwWpPZaw0fn5u4Yrm5TOmB238BXA4zWLVsNhervd3Z6den13KbmwKZLH7/Vc0LjYXFbD73xVUzqVJw5qD4rLv3dt8LxyBw27uZ65+7z7zTZdPbKl7YGhoShwUXNLv1WsH1B1LDDe18Oylhz5VTQ16tee+t9vk8lfMiRG7dvzmw/dVdB7ZEW//KoHeNC7sQFNPyx9aiyP4Nv3j6oWRnasmzCqc3PRRsn+5j/UC0d3qrEueIFxi5/sGmgc+b0l5ppDuYP2PD8xeeWBcTGJObVfev83wte6vBl4xt53YOiNyz5MWLaxzv2+Y78eVje2Tc6Fk6eOyEJJEj/19dPj77VYN2I0oYfuVjOR53Vh4/tOj25QLOydeInBy9al54Li2j2SdK+IxMWN752ev6A8OQrmjV/WIoSO339Xm2UMlWPjDWBx0bWfWt/J+3w555uPX7b7eechdejux4eXBaxrEbA3kE1Py27vufwNxkVf17+INrnp/VT1B3sHW1Hp/2x8dq7NZrWCs9+cmLyuBWHekVcSS4oaND2Vq/hXw1vvK3jotPfB8/4fuHxoifjH3s3pM1gdf91C48e+nPW+YMXk56tyMtYPs74wfMDG3WYEDMZutOI1kFDmptHvJt9Y/Xz7X764q83Pr720+Xmt7bk9HLN3NBvUNeN5Qsurm0ZoL99Imn8/T71xw/PbbLpfPi+
*/