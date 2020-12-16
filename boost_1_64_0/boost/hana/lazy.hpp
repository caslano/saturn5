/*!
@file
Defines `boost::hana::lazy`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_LAZY_HPP
#define BOOST_HANA_LAZY_HPP

#include <boost/hana/fwd/lazy.hpp>

#include <boost/hana/basic_tuple.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/detail/operators/adl.hpp>
#include <boost/hana/detail/operators/monad.hpp>
#include <boost/hana/functional/apply.hpp>
#include <boost/hana/functional/compose.hpp>
#include <boost/hana/functional/on.hpp>
#include <boost/hana/fwd/ap.hpp>
#include <boost/hana/fwd/duplicate.hpp>
#include <boost/hana/fwd/eval.hpp>
#include <boost/hana/fwd/extend.hpp>
#include <boost/hana/fwd/extract.hpp>
#include <boost/hana/fwd/flatten.hpp>
#include <boost/hana/fwd/lift.hpp>
#include <boost/hana/fwd/transform.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //////////////////////////////////////////////////////////////////////////
    // lazy
    //////////////////////////////////////////////////////////////////////////
    template <typename Indices, typename F, typename ...Args>
    struct lazy_apply_t;

    namespace detail { struct lazy_secret { }; }

    template <std::size_t ...n, typename F, typename ...Args>
    struct lazy_apply_t<std::index_sequence<n...>, F, Args...>
        : detail::operators::adl<>
    {
        template <typename ...T>
        constexpr lazy_apply_t(detail::lazy_secret, T&& ...t)
            : storage_{static_cast<T&&>(t)...}
        { }

        basic_tuple<F, Args...> storage_;
        using hana_tag = lazy_tag;
    };

    template <typename X>
    struct lazy_value_t : detail::operators::adl<> {
        template <typename Y>
        constexpr lazy_value_t(detail::lazy_secret, Y&& y)
            : storage_{static_cast<Y&&>(y)}
        { }

        basic_tuple<X> storage_;
        using hana_tag = lazy_tag;

        // If this is called, we assume that `X` is in fact a function.
        template <typename ...Args>
        constexpr lazy_apply_t<
            std::make_index_sequence<sizeof...(Args)>,
            X, typename detail::decay<Args>::type...
        > operator()(Args&& ...args) const& {
            return {detail::lazy_secret{},
                    hana::at_c<0>(storage_), static_cast<Args&&>(args)...};
        }

        template <typename ...Args>
        constexpr lazy_apply_t<
            std::make_index_sequence<sizeof...(Args)>,
            X, typename detail::decay<Args>::type...
        > operator()(Args&& ...args) && {
            return {detail::lazy_secret{},
                static_cast<X&&>(hana::at_c<0>(storage_)),
                static_cast<Args&&>(args)...
            };
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // make<lazy_tag>
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct make_impl<lazy_tag> {
        template <typename X>
        static constexpr lazy_value_t<typename detail::decay<X>::type> apply(X&& x) {
            return {detail::lazy_secret{}, static_cast<X&&>(x)};
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Operators
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <>
        struct monad_operators<lazy_tag> { static constexpr bool value = true; };
    }

    //////////////////////////////////////////////////////////////////////////
    // eval for lazy_tag
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct eval_impl<lazy_tag> {
        // lazy_apply_t
        template <std::size_t ...n, typename F, typename ...Args>
        static constexpr decltype(auto)
        apply(lazy_apply_t<std::index_sequence<n...>, F, Args...> const& expr) {
            return hana::at_c<0>(expr.storage_)(
                hana::at_c<n+1>(expr.storage_)...
            );
        }

        template <std::size_t ...n, typename F, typename ...Args>
        static constexpr decltype(auto)
        apply(lazy_apply_t<std::index_sequence<n...>, F, Args...>& expr) {
            return hana::at_c<0>(expr.storage_)(
                hana::at_c<n+1>(expr.storage_)...
            );
        }

        template <std::size_t ...n, typename F, typename ...Args>
        static constexpr decltype(auto)
        apply(lazy_apply_t<std::index_sequence<n...>, F, Args...>&& expr) {
            return static_cast<F&&>(hana::at_c<0>(expr.storage_))(
                static_cast<Args&&>(hana::at_c<n+1>(expr.storage_))...
            );
        }

        // lazy_value_t
        template <typename X>
        static constexpr X const& apply(lazy_value_t<X> const& expr)
        { return hana::at_c<0>(expr.storage_); }

        template <typename X>
        static constexpr X& apply(lazy_value_t<X>& expr)
        { return hana::at_c<0>(expr.storage_); }

        template <typename X>
        static constexpr X apply(lazy_value_t<X>&& expr)
        { return static_cast<X&&>(hana::at_c<0>(expr.storage_)); }
    };

    //////////////////////////////////////////////////////////////////////////
    // Functor
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct transform_impl<lazy_tag> {
        template <typename Expr, typename F>
        static constexpr auto apply(Expr&& expr, F&& f) {
            return hana::make_lazy(hana::compose(static_cast<F&&>(f), hana::eval))(
                static_cast<Expr&&>(expr)
            );
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Applicative
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct lift_impl<lazy_tag> {
        template <typename X>
        static constexpr lazy_value_t<typename detail::decay<X>::type>
        apply(X&& x) {
            return {detail::lazy_secret{}, static_cast<X&&>(x)};
        }
    };

    template <>
    struct ap_impl<lazy_tag> {
        template <typename F, typename X>
        static constexpr decltype(auto) apply(F&& f, X&& x) {
            return hana::make_lazy(hana::on(hana::apply, hana::eval))(
                static_cast<F&&>(f), static_cast<X&&>(x)
            );
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Monad
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct flatten_impl<lazy_tag> {
        template <typename Expr>
        static constexpr decltype(auto) apply(Expr&& expr) {
            return hana::make_lazy(hana::compose(hana::eval, hana::eval))(
                static_cast<Expr&&>(expr)
            );
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Comonad
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct extract_impl<lazy_tag> {
        template <typename Expr>
        static constexpr decltype(auto) apply(Expr&& expr)
        { return hana::eval(static_cast<Expr&&>(expr)); }
    };

    template <>
    struct duplicate_impl<lazy_tag> {
        template <typename Expr>
        static constexpr decltype(auto) apply(Expr&& expr)
        { return hana::make_lazy(static_cast<Expr&&>(expr)); }
    };

    template <>
    struct extend_impl<lazy_tag> {
        template <typename Expr, typename F>
        static constexpr decltype(auto) apply(Expr&& expr, F&& f) {
            return hana::make_lazy(static_cast<F&&>(f))(static_cast<Expr&&>(expr));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_LAZY_HPP

/* lazy.hpp
Fid3/DCLUqvoKVDA6tj2p5p2n4sNcxAFMTCjHWhOfNyeLeIipDBhrC+ijSv4K1Hobq10/h/hy+A+D/J23Lxz3RvcBzkcP/wrlNd+IIpIhX8TZVfaPeIHkXUecFPswz8GmUGsy/xCjhNgnANj73TDzjVucD/g65z7lyjwZ/k3wOJTGXSab1eS3yI/q0Cv/kY44yIoZ3OA0ne0QX4vj85Tgfp+VfkdLiD6rnBfTX6HA4nBXl1+c+027mvQd8Kiv++S3+fiED86DPc15XfPftBcg+Na8ltlz83FBcd9bfkdhw9BnPmCf/T9Ouo7goXispjj+K9LPODfrqf6z3BfX7WvQMsZ7G7qD69/g6aPVB9l9G3On43trGnbjWq8Pv5QSVO2R5aBTa5PvremPTeWZbbnzc8enZtX3/FTfZ/1RZSQ/n5TRcfOYpvxcm/dLn92Hj9Zf28mvsvjXfzsgCf0/eY1vO7rLWre5nac6bq3rPmHW30LR2fjBuet8H1cP29d08IAUSFrx21I7r2j2dE59n2f+K64wr7fVn4XOni+hETqdt5Ofp8HjWacbl/PCXsuatpyh1oe5uaO+rNUpHHfsW7/UQec5by6E6vD+3XnevygOPzZahbHVUxG7kJyPe/PaTx3Fd/UMRHDf7ea7rw9Oy8q6O93r3lfePjK4e9Rj1HkuykKm+/3bL5HJYRGtfNezfd6IBmuezdlccXav78esxKzRMMekN+kQOJzg2OixpHNtmT1oPpOsqpwT8rvtaDemr5N0fxxZ310lsSEtfOQwoUR5t8Pa1mMPXzW+Kb5WMqBXigzryk/wsZUFzO895HlMCuhEvjcv28trx5vw/1onMK48Pn3+xMPxexTcnMVrAPIINJ7THcLzu2tfPHM2sb2BmQMZVeTZfMV2JBlDjazC5CqcjaefxAU2DHwy8NYAu4agLtSBxddKFQQUwvqGWxbwPHv/GyZoS22k6EtGBuCv/Jl4XP7BPpaeMdjbz7SNK562TrenFstzNthQ+Mal4WXHVgIcH1krgOZR51rtvsRl2O7cYhgr3wZWEwftN/OEBm/cKzMjuZ+PdbXlvXccnbhmD8rVgf0NRG/TYjyXTe4E8oHj5IKRa6UWM83+ie3N5fFeKH8nnV5lbpzh3mZqDtZlx2NQRzTP+TlN0H5IZSLk2z0A+0RrfU6t8P3+9f1VHBr1a59c1YXoj0PTtYgQg5RNuxQWXE0yzqQHXx7YI1Tfob/DNSyNlpJe96k7RKQOHEWQLJfD2I8EStEU1rjeHhdHlf2ygpONwfB4sba+tkGSrSny3BUJdw8D8JE8HwZ8EioJNw65y/mGlpO4wBANg49wPGIZKIl+XxdlLU6JL8/Hd+JNu5pVPhct//ZNU1ik1AS87M+6+X1AHN70EVY02O7C0NJ/yWMRhZJjREcLVyJ7+U7jSf1QMC8aiyMyfc3EoxYWCHHWN5MHG+ty2WMRyyXTL8ZXZLJKxo5oJlijst72LhgRsTBg2Bozdp5m9/vB9wcrsUKS0NGJuJsbuFEZco1RWgo2p9ktOcfVDWDTWP92bqcBZHk/nxUem35+hLjwxy4lIEV+KfqqqT19ZF+EjUav2+ivDp6HGyu2/a9cfCE74Yo/wHrb4fm2U/xrRZgGCHUx18y/mVlmR6tqPU0b39Xl8+dgP6LPZP3f9mp/1xvkKwzoADCKdtzI5RnJaSmQq9onP7e4OTsljz4J8qoIbL+VW4gxi1eKbdmF+FNk226Fr4RX0jJQKc7JFhsTG4AODZnoBYYCMHsBQyT8bH655aAGRlbxsMb0tw72nQU3/h4Lriq73cCrkosl5lvFxiIcLY8WlHf74WyuJCGshy3g/idy2Y=
*/