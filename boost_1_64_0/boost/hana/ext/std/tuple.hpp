/*!
@file
Adapts `std::tuple` for use with Hana.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXT_STD_TUPLE_HPP
#define BOOST_HANA_EXT_STD_TUPLE_HPP

#include <boost/hana/bool.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/fwd/at.hpp>
#include <boost/hana/fwd/core/make.hpp>
#include <boost/hana/fwd/core/tag_of.hpp>
#include <boost/hana/fwd/drop_front.hpp>
#include <boost/hana/fwd/empty.hpp>
#include <boost/hana/fwd/flatten.hpp>
#include <boost/hana/fwd/front.hpp>
#include <boost/hana/fwd/is_empty.hpp>
#include <boost/hana/fwd/length.hpp>
#include <boost/hana/fwd/lift.hpp>
#include <boost/hana/integral_constant.hpp>

#include <cstddef>
#include <tuple>
#include <type_traits>
#include <utility>


#ifdef BOOST_HANA_DOXYGEN_INVOKED
namespace std {
    //! @ingroup group-ext-std
    //! Adapter for `std::tuple`s.
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! A `std::tuple` is a model of the `Sequence` concept, and all the
    //! concepts it refines. That makes it essentially the same as a Hana
    //! tuple, although the complexity of some operations might differ from
    //! that of Hana's tuple.
    //!
    //! @include example/ext/std/tuple.cpp
    template <typename ...T>
    struct tuple { };
}
#endif


BOOST_HANA_NAMESPACE_BEGIN
    namespace ext { namespace std { struct tuple_tag; }}

    template <typename ...Xs>
    struct tag_of<std::tuple<Xs...>> {
        using type = ext::std::tuple_tag;
    };

    //////////////////////////////////////////////////////////////////////////
    // make
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct make_impl<ext::std::tuple_tag> {
        template <typename ...Xs>
        static constexpr decltype(auto) apply(Xs&& ...xs) {
            return std::make_tuple(static_cast<Xs&&>(xs)...);
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Applicative
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct lift_impl<ext::std::tuple_tag> {
        template <typename X>
        static constexpr auto apply(X&& x) {
            return std::tuple<typename detail::decay<X>::type>{
                                                static_cast<X&&>(x)};
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Monad
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct flatten_impl<ext::std::tuple_tag> {
        template <typename Xs, std::size_t ...i>
        static constexpr decltype(auto)
        flatten_helper(Xs&& xs, std::index_sequence<i...>) {
            return std::tuple_cat(std::get<i>(static_cast<Xs&&>(xs))...);
        }

        template <typename Xs>
        static constexpr decltype(auto) apply(Xs&& xs) {
            using Raw = typename std::remove_reference<Xs>::type;
            constexpr std::size_t Length = std::tuple_size<Raw>::value;
            return flatten_helper(static_cast<Xs&&>(xs),
                                  std::make_index_sequence<Length>{});
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // MonadPlus
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct empty_impl<ext::std::tuple_tag> {
        static constexpr auto apply()
        { return std::tuple<>{}; }
    };

    //////////////////////////////////////////////////////////////////////////
    // Iterable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct front_impl<ext::std::tuple_tag> {
        template <typename Xs>
        static constexpr decltype(auto) apply(Xs&& xs) {
            return std::get<0>(static_cast<Xs&&>(xs));
        }
    };

    template <>
    struct drop_front_impl<ext::std::tuple_tag> {
        template <std::size_t n, typename Xs, std::size_t ...i>
        static constexpr auto drop_front_helper(Xs&& xs, std::index_sequence<i...>) {
            return std::make_tuple(
                hana::at_c<n + i>(static_cast<Xs&&>(xs))...
            );
        }

        template <typename Xs, typename N>
        static constexpr auto apply(Xs&& xs, N const&) {
            using Raw = typename std::remove_reference<Xs>::type;
            constexpr std::size_t n = N::value;
            constexpr auto len = std::tuple_size<Raw>::value;
            return drop_front_helper<n>(static_cast<Xs&&>(xs),
                    std::make_index_sequence<(n < len ? len - n : 0)>{});
        }
    };

    template <>
    struct is_empty_impl<ext::std::tuple_tag> {
        template <typename ...Xs>
        static constexpr auto apply(std::tuple<Xs...> const&)
        { return hana::bool_c<sizeof...(Xs) == 0>; }
    };

    template <>
    struct at_impl<ext::std::tuple_tag> {
        template <typename Xs, typename N>
        static constexpr decltype(auto) apply(Xs&& xs, N const&) {
            constexpr std::size_t index = N::value;
            return std::get<index>(static_cast<Xs&&>(xs));
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Foldable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct length_impl<ext::std::tuple_tag> {
        template <typename ...Xs>
        static constexpr auto apply(std::tuple<Xs...> const&) {
            return hana::size_c<sizeof...(Xs)>;
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Sequence
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct Sequence<ext::std::tuple_tag> {
        static constexpr bool value = true;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXT_STD_TUPLE_HPP

/* tuple.hpp
fRzVnqgcT7/LbifmowfHN+2DiwC1uj/mM/81apPjE74PVtEDJGkZcscF9eXgwYOi/yQ/aLXZ13jafMRdarXRtBkRstG2LCUbjfcf2H8u8L7w0asNTvIWLC+OW+3yIsxhx8xUYRL3AIXxpnK6HyREY/RMtsR+8glCI6aRe9vTLyvJHvhmf/2WhZ3e/KSyoXfhFgherwdenuZCv6xSkFFMFLirYE+3g+7sGnO0ZkzyujdOO4LjtBT150qd1ogJ30cn1grKefJMdgyvPaoH8dy5erQzM5UeUYgesq1XKDiAbMOuWk26gGIsih9nAPfDk03++zm18QMjCLWayN3cFeTHmavFfpFi/roq4MSd8/da7fsesidCa9rZHo2K77LCXzdXDF6F2rF7Es3hc1HXKaeYPcxza+PDVPhMwwNjfFhK+8a6hKwZbnwF7p1Z3LCa3qaXZwWZd83Aa6BkL7IstVoc9r75vh0Lx0QkT4rne3usrCKUl4yp/o6IRl7Vjvp0gYVLyiXJwX0inGhdls/7Why/nOx4cRHw/JaxpiU5AD70vqJ9r3itpfPeaBSKSAYGgN8MGdg3D7EV0RcPBiwLGKauhY0D9gLATiPYQwC7HrDVBCvhP+5UMkWwS6WNFxDsMYB9A2vHA6jdxwPWtgC8IbqnALYPsHUEuwywVwK2kmDPAezLHuwFgB2zMA57EWDHHQVZU7DaZB4zMBeQ+Yc5madx2QGmpbqHIfHZdEtrRySpWKfiZ81eudrSWWkO1rG51asj3BbOth6RDleu1NQn0FXtE3A19Ql0wT6tJTqJlUxkp1SvMpjymsr5pKsDNB6vu9BWPpffKIykxlxbb1wdpvP7o2iKgXpsbAj1+DSaf1zHcMpoESlr76Vf7XCBMqIhTKmozNtXM64u1tfuzq7tenN51qSE+d98JcryG1WSFw5Kx993gsavx+sb8PRF1Ld3r2Yc6vTL8Bfx+4FROdKJVJbuBsIVQG2mdPK+oTbbj6tWcxnwqFpdna1WBpcm6su2Al6t7FB/V0t7s8jmcq9suTCNUB/w9I1eeV3Qx5mbkQzO3o8RfYtZSQwJ6vXx3cUw/oOx8u5yJQ+P8nH8UuqbyjP2x+xDqwUuz7MwDz8iOPkgW9dHI7huxflehwDHLUMt6eHtqRay4T4OuAahbu5Pf9cmO24nEy3gsX4PdbYl6D4FOsDBe6KrMj8/rWjD8xPw8Pz87GrG1VG/zbdQGwyHWjQY79sBT9SxqaU1SAs49mnILhajONbvPdt7h/oGd+7s01W4ur+6mnDUvxsBz0xmylNpfVMg2nRv+o3jYgzeS7oJtMrPxUMULc2tbj5+HfCtAzA0ivGzqN+M9B+9nxjhvk040UGhdlqb2zrqAnDwwumf7wA+hWSGwtik8hr14s1tfQ94YwtPwQrPTPD8+T5w/NaQ/479DxP4+D2IP17Nbxm5cj9NlPPeQFR9Ujo83jHb51/aPkuqN8dfgCvPFtNjWI/2IS9+P/H8VrWeD18y0GkuQE0/pOTi1Ldb3J5U74jN20TgBVu3FSdbzwBdZTKfn4Z8s/2uGevZ7/DXpc5CBTGcab05z28JJtqM702ca8urCEcRZ7tn9ilPgOv4i8w5ff9MeifsNXg5tO79TfCc1+Ln3Mxrsv2EQpNGSA7mA8/99OXgKOCx1xA/70Z9uGeTsRPk7Cfug5EMS2rjONWG0ETmBmitTJwEfCdiR5O4RiiqiNeohcD3dnWn/ApYNpaAZri7u0vR+PNqGXDQjRYVwVdoeGsCvhrwrT0WbNs4TfUzNTwCTKL905tkDRAOMm4d4fycqXs1+XYfChP+LB+vGi8csHJ0jo/HvIFAVdjnO4/4yzY=
*/