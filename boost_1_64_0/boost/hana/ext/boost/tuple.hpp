/*!
@file
Adapts `boost::tuple` for use with Hana.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXT_BOOST_TUPLE_HPP
#define BOOST_HANA_EXT_BOOST_TUPLE_HPP

#include <boost/hana/bool.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/fwd/at.hpp>
#include <boost/hana/fwd/core/make.hpp>
#include <boost/hana/fwd/core/tag_of.hpp>
#include <boost/hana/fwd/drop_front.hpp>
#include <boost/hana/fwd/is_empty.hpp>
#include <boost/hana/fwd/length.hpp>
#include <boost/hana/integral_constant.hpp>

#include <boost/tuple/tuple.hpp>

#include <cstddef>
#include <utility>


#ifdef BOOST_HANA_DOXYGEN_INVOKED
namespace boost {
    //! @ingroup group-ext-boost
    //! Adapter for `boost::tuple`s.
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! A `boost::tuple` is a model of the `Sequence` concept, and all the
    //! concepts it refines. That makes it essentially the same as a Hana
    //! tuple, although the complexity of some operations might differ from
    //! that of Hana's tuple.
    //!
    //! @include example/ext/boost/tuple.cpp
    template <typename ...T>
    struct tuple { };
}
#endif


BOOST_HANA_NAMESPACE_BEGIN
    namespace ext { namespace boost { struct tuple_tag; }}

    template <typename ...Xs>
    struct tag_of<boost::tuple<Xs...>> {
        using type = ext::boost::tuple_tag;
    };

    template <typename H, typename T>
    struct tag_of<boost::tuples::cons<H, T>> {
        using type = ext::boost::tuple_tag;
    };

    template <>
    struct tag_of<boost::tuples::null_type> {
        using type = ext::boost::tuple_tag;
    };

    //////////////////////////////////////////////////////////////////////////
    // Iterable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct at_impl<ext::boost::tuple_tag> {
        template <typename Xs, typename N>
        static constexpr decltype(auto) apply(Xs&& xs, N const&) {
            constexpr std::size_t n = N::value;
            return static_cast<Xs&&>(xs).template get<n>();
        }
    };

    template <>
    struct drop_front_impl<ext::boost::tuple_tag> {
        template <std::size_t n, typename Xs, std::size_t ...i>
        static constexpr auto drop_front_helper(Xs&& xs, std::index_sequence<i...>) {
            return hana::make<ext::boost::tuple_tag>(
                hana::at_c<n + i>(static_cast<Xs&&>(xs))...
            );
        }

        template <typename Xs, typename N>
        static constexpr auto apply(Xs&& xs, N const&) {
            constexpr std::size_t n = N::value;
            constexpr std::size_t len = decltype(hana::length(xs))::value;
            return drop_front_helper<n>(static_cast<Xs&&>(xs),
                    std::make_index_sequence<(n < len ? len - n : 0)>{});
        }
    };

    template <>
    struct is_empty_impl<ext::boost::tuple_tag> {
        static constexpr auto apply(boost::tuples::null_type const&)
        { return hana::true_c; }

        template <typename H, typename T>
        static constexpr auto apply(boost::tuples::cons<H, T> const&)
        { return hana::false_c; }
    };

    //////////////////////////////////////////////////////////////////////////
    // Foldable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct length_impl<ext::boost::tuple_tag> {
        template <typename Xs>
        static constexpr auto apply(Xs const&) {
            return hana::size_c<boost::tuples::length<Xs>::value>;
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Sequence
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct Sequence<ext::boost::tuple_tag> {
        static constexpr bool value = true;
    };

    template <>
    struct make_impl<ext::boost::tuple_tag> {
        template <typename ...Xs>
        static constexpr auto apply(Xs&& ...xs) {
            return boost::tuples::tuple<
                typename detail::decay<Xs>::type...
            >{static_cast<Xs&&>(xs)...};
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXT_BOOST_TUPLE_HPP

/* tuple.hpp
SSGGZl+2wkWiyEcmX0kuDf1akIIM0ctcznoibkV2a/Fpr/I3+tpjFXpUy9nHEPKk8IxK8pRdF5FT4n7C0C74DBFr/oheXou/d5IrmAGPK0O/WxL7Yxdzv0EP4rG1bXA09vqGS5kTuPg783Hhn5ttQLeK8eGryWWCg3WH4c1g79wuxJVPgJvI+Bw56thu6FFPfA2+eTa2fRmYWzYY/9wJdWbv37SBVeD2h3uINR6Fi87Dj9+I3TwOb8XGi9GtQfvR2ynIoQ+6uAGZE5tHJ3C+3QBXg5u8dRH5iV3ka4lp0k3cnbwJuRBTJ8KX1jJv8RlvC/o3ljzFi4vgPD+hz2n4t0eJFfDHr12Fb2iHXkxGbvjEHi8ZZ/KxUXDINcT2b4CPy8ito9vvhJF7r+JMub+Je+TIFX/pbEV+Og9/fkLTPxd5PdzyozYadZwrgM0F8J5a8fnnKnKr8LXJjDn0SZ4FA0PEWSt8eWQfEcOCyexXPT5jOfHNUHJNozXyg/3RKThaMvgYyvqfXkW+FH/fpRlnNgvBa/zB4xvEHqFPL5MPfiEIXAD/wPnd5N5q2Pv7uAt4soRcPGtIicXfPgLubofnP0zMOZt65n4tck5A53FBWtVQE3fZyfeeAGP+Ce/CzoLZ+433gjvvi3nBQ1YZeeBzcLqwb7GNW9F78GTWS/C5jSbtmtH4kaXEQSSSRpLD7FeAjpNzypwJj8dOV44k9w0+7MBHz8tmv5D3cbC8N7kma7qBBVsccK9T8Fpy663cjO/kXsVUdHgzeuZBf58DJ2wGPk7/FlmQF570KXgNv/xoGTLwkNOG7ySbsUPa9fwJjomeRtDHTBfnB+h66w7iDjl36ptz/2KmgYWtPkW+B/G9t4MzrLstuc5CdCcdnXNfj34+KD4LCLdBrwSmhVJ+CZw8D514lD2aUch54xTGng3fRi/ziRsiC5lbPfzHCe88SywLdg6tB6sfp7wz3JH8xLwU2obBC53glwn/BrZ81tekf0eBGSwsfQe/sRLcJg9jxa+8+RwxD9x4tZ0zxUxsHJxKuJFYhn8v6sBZygqNXDJr3Y1+Mv61rfERj+Cj0LuRSciFnG1L8bnFWejF9/gX1jXkdrhGFXtzFzg5DJzjnv16fm47je3uoO0l+EZySZaB5OrBpdXgZcxa+CXn2Gbi2DFByOoGgX+aloPPa4AvlnQEJ63kOUVuaxf72hreC/ct45zkVCR5AfjKiEnsJfcMBm2FR8DFjt6JbaFTPebDP8Hqy8ibZQwkdkIf7m9NzLEAHQFDFhxAN77ELjujPzy35nLyJ9j/gIPo9Bh8FL5l2U4w6zi8fRo6Kz6nh3+/5zY41kDsGAztgh1kl5L3HY6M0GXH5fgHZP3+UvL+rPkgOt0PfRkAPg25Bb+RgN6PMe7lHC5njLs0LX4Q+eSHkTu68J4HHCD+uC2OOnzMnWHYNXHkEvT/iqvg1VcSC70Ilo8j1/Ain0dgPfdPgZeDCz3wj79EEwvgl8234B9X6TqJ3pEPxx/vGQLOpxBLoNdvfUu/bxLfwwvO9mTt2GZ/1n3jVO6aNee8BZlfkmfYx/3MJx7esqcLObZoxqXs4Mf4Ifzwp/R9/1Fi9Vr40Vvk7dij6OPE9+hP/4Xc8WxObIuuXAI/+RbcXEus+sI9YP9ScDHE6H/+Gfjzvcj1acapYC5wwqO/Mn/0PB0dt46Cl9O2d0/xHfLwY9YdncjePwYvgLcmjSBuYG5fMpd6dPpFbLtFuPheYzgDOrkRP7SjGJ5iwd7ArhU9ie8ykCMxWBL+/rsfsclW+D/0phQ9aANnPpsCH0Wv5uKnHkEn+rDWfdfDTafxTC68/hvk/hWxNfPpcAdzww8=
*/