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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_LAZY_HPP

/* lazy.hpp
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
*/