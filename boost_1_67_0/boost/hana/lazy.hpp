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
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
*/