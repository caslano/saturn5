/*!
@file
Defines `boost::hana::optional`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_OPTIONAL_HPP
#define BOOST_HANA_OPTIONAL_HPP

#include <boost/hana/fwd/optional.hpp>

#include <boost/hana/bool.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/detail/operators/adl.hpp>
#include <boost/hana/detail/operators/comparable.hpp>
#include <boost/hana/detail/operators/monad.hpp>
#include <boost/hana/detail/operators/orderable.hpp>
#include <boost/hana/detail/wrong.hpp>
#include <boost/hana/functional/partial.hpp>
#include <boost/hana/fwd/any_of.hpp>
#include <boost/hana/fwd/ap.hpp>
#include <boost/hana/fwd/concat.hpp>
#include <boost/hana/fwd/core/make.hpp>
#include <boost/hana/fwd/empty.hpp>
#include <boost/hana/fwd/equal.hpp>
#include <boost/hana/fwd/find_if.hpp>
#include <boost/hana/fwd/flatten.hpp>
#include <boost/hana/fwd/less.hpp>
#include <boost/hana/fwd/lift.hpp>
#include <boost/hana/fwd/transform.hpp>
#include <boost/hana/fwd/type.hpp>
#include <boost/hana/fwd/unpack.hpp>

#include <cstddef> // std::nullptr_t
#include <type_traits>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //////////////////////////////////////////////////////////////////////////
    // optional<>
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <typename T, typename = typename hana::tag_of<T>::type>
        struct nested_type { };

        template <typename T>
        struct nested_type<T, type_tag> { using type = typename T::type; };
    }

    template <typename T>
    struct optional<T> : detail::operators::adl<>, detail::nested_type<T> {
        // 5.3.1, Constructors
        constexpr optional() = default;
        constexpr optional(optional const&) = default;
        constexpr optional(optional&&) = default;

        constexpr optional(T const& t)
            : value_(t)
        { }

        constexpr optional(T&& t)
            : value_(static_cast<T&&>(t))
        { }

        // 5.3.3, Assignment
        constexpr optional& operator=(optional const&) = default;
        constexpr optional& operator=(optional&&) = default;

        // 5.3.5, Observers
        constexpr T const* operator->() const { return &value_; }
        constexpr T* operator->() { return &value_; }

        constexpr T&        value() & { return value_; }
        constexpr T const&  value() const& { return value_; }
        constexpr T&&       value() && { return static_cast<T&&>(value_); }
        constexpr T const&& value() const&& { return static_cast<T const&&>(value_); }

        constexpr T&        operator*() & { return value_; }
        constexpr T const&  operator*() const& { return value_; }
        constexpr T&&       operator*() && { return static_cast<T&&>(value_); }
        constexpr T const&& operator*() const&& { return static_cast<T const&&>(value_); }

        template <typename U> constexpr T&        value_or(U&&) & { return value_; }
        template <typename U> constexpr T const&  value_or(U&&) const& { return value_; }
        template <typename U> constexpr T&&       value_or(U&&) && { return static_cast<T&&>(value_); }
        template <typename U> constexpr T const&& value_or(U&&) const&& { return static_cast<T const&&>(value_); }

        // We leave this public because it simplifies the implementation, but
        // this should be considered private by users.
        T value_;
    };

    //! @cond
    template <typename ...dummy>
    constexpr auto optional<>::value() const {
        static_assert(detail::wrong<dummy...>{},
        "hana::optional::value() requires a non-empty optional");
    }

    template <typename ...dummy>
    constexpr auto optional<>::operator*() const {
        static_assert(detail::wrong<dummy...>{},
        "hana::optional::operator* requires a non-empty optional");
    }

    template <typename U>
    constexpr U&& optional<>::value_or(U&& u) const {
        return static_cast<U&&>(u);
    }

    template <typename T>
    constexpr auto make_just_t::operator()(T&& t) const {
        return hana::optional<typename detail::decay<T>::type>(static_cast<T&&>(t));
    }
    //! @endcond

    template <typename ...T>
    struct tag_of<optional<T...>> {
        using type = optional_tag;
    };

    //////////////////////////////////////////////////////////////////////////
    // make<optional_tag>
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct make_impl<optional_tag> {
        template <typename X>
        static constexpr auto apply(X&& x)
        { return hana::just(static_cast<X&&>(x)); }

        static constexpr auto apply()
        { return hana::nothing; }
    };

    //////////////////////////////////////////////////////////////////////////
    // Operators
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <>
        struct comparable_operators<optional_tag> {
            static constexpr bool value = true;
        };
        template <>
        struct orderable_operators<optional_tag> {
            static constexpr bool value = true;
        };
        template <>
        struct monad_operators<optional_tag> {
            static constexpr bool value = true;
        };
    }

    //////////////////////////////////////////////////////////////////////////
    // is_just and is_nothing
    //////////////////////////////////////////////////////////////////////////
    //! @cond
    template <typename ...T>
    constexpr auto is_just_t::operator()(optional<T...> const&) const
    { return hana::bool_c<sizeof...(T) != 0>; }

    template <typename ...T>
    constexpr auto is_nothing_t::operator()(optional<T...> const&) const
    { return hana::bool_c<sizeof...(T) == 0>; }
    //! @endcond

    //////////////////////////////////////////////////////////////////////////
    // sfinae
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        struct sfinae_impl {
            template <typename F, typename ...X, typename = decltype(
                std::declval<F>()(std::declval<X>()...)
            )>
            constexpr decltype(auto) operator()(int, F&& f, X&& ...x) const {
                using Return = decltype(static_cast<F&&>(f)(static_cast<X&&>(x)...));
                static_assert(!std::is_same<Return, void>::value,
                "hana::sfinae(f)(args...) requires f(args...) to be non-void");

                return hana::just(static_cast<F&&>(f)(static_cast<X&&>(x)...));
            }

            template <typename F, typename ...X>
            constexpr auto operator()(long, F&&, X&& ...) const
            { return hana::nothing; }
        };
    }

    //! @cond
    template <typename F>
    constexpr decltype(auto) sfinae_t::operator()(F&& f) const {
        return hana::partial(detail::sfinae_impl{}, int{},
                             static_cast<F&&>(f));
    }
    //! @endcond

    //////////////////////////////////////////////////////////////////////////
    // Comparable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct equal_impl<optional_tag, optional_tag> {
        template <typename T, typename U>
        static constexpr auto apply(hana::optional<T> const& t, hana::optional<U> const& u)
        { return hana::equal(t.value_, u.value_); }

        static constexpr hana::true_ apply(hana::optional<> const&, hana::optional<> const&)
        { return {}; }

        template <typename T, typename U>
        static constexpr hana::false_ apply(T const&, U const&)
        { return {}; }
    };

    //////////////////////////////////////////////////////////////////////////
    // Orderable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct less_impl<optional_tag, optional_tag> {
        template <typename T>
        static constexpr hana::true_ apply(hana::optional<> const&, hana::optional<T> const&)
        { return {}; }

        static constexpr hana::false_ apply(hana::optional<> const&, hana::optional<> const&)
        { return {}; }

        template <typename T>
        static constexpr hana::false_ apply(hana::optional<T> const&, hana::optional<> const&)
        { return {}; }

        template <typename T, typename U>
        static constexpr auto apply(hana::optional<T> const& x, hana::optional<U> const& y)
        { return hana::less(x.value_, y.value_); }
    };

    //////////////////////////////////////////////////////////////////////////
    // Functor
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct transform_impl<optional_tag> {
        template <typename F>
        static constexpr auto apply(optional<> const&, F&&)
        { return hana::nothing; }

        template <typename T, typename F>
        static constexpr auto apply(optional<T> const& opt, F&& f)
        { return hana::just(static_cast<F&&>(f)(opt.value_)); }

        template <typename T, typename F>
        static constexpr auto apply(optional<T>& opt, F&& f)
        { return hana::just(static_cast<F&&>(f)(opt.value_)); }

        template <typename T, typename F>
        static constexpr auto apply(optional<T>&& opt, F&& f)
        { return hana::just(static_cast<F&&>(f)(static_cast<T&&>(opt.value_))); }
    };

    //////////////////////////////////////////////////////////////////////////
    // Applicative
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct lift_impl<optional_tag> {
        template <typename X>
        static constexpr auto apply(X&& x)
        { return hana::just(static_cast<X&&>(x)); }
    };

    template <>
    struct ap_impl<optional_tag> {
        template <typename F, typename X>
        static constexpr auto ap_helper(F&&, X&&, ...)
        { return hana::nothing; }

        template <typename F, typename X>
        static constexpr auto ap_helper(F&& f, X&& x, hana::true_, hana::true_)
        { return hana::just(static_cast<F&&>(f).value_(static_cast<X&&>(x).value_)); }

        template <typename F, typename X>
        static constexpr auto apply(F&& f, X&& x) {
            return ap_impl::ap_helper(static_cast<F&&>(f), static_cast<X&&>(x),
                                      hana::is_just(f), hana::is_just(x));
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Monad
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct flatten_impl<optional_tag> {
        static constexpr auto apply(optional<> const&)
        { return hana::nothing; }

        static constexpr auto apply(optional<optional<>> const&)
        { return hana::nothing; }

        template <typename T>
        static constexpr auto apply(optional<optional<T>> const& opt)
        { return hana::just(opt.value_.value_); }

        template <typename T>
        static constexpr auto apply(optional<optional<T>>&& opt)
        { return hana::just(static_cast<T&&>(opt.value_.value_)); }
    };

    //////////////////////////////////////////////////////////////////////////
    // MonadPlus
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct concat_impl<optional_tag> {
        template <typename Y>
        static constexpr auto apply(hana::optional<>&, Y&& y)
        { return static_cast<Y&&>(y); }

        template <typename Y>
        static constexpr auto apply(hana::optional<>&&, Y&& y)
        { return static_cast<Y&&>(y); }

        template <typename Y>
        static constexpr auto apply(hana::optional<> const&, Y&& y)
        { return static_cast<Y&&>(y); }

        template <typename X, typename Y>
        static constexpr auto apply(X&& x, Y&&)
        { return static_cast<X&&>(x); }
    };

    template <>
    struct empty_impl<optional_tag> {
        static constexpr auto apply()
        { return hana::nothing; }
    };

    //////////////////////////////////////////////////////////////////////////
    // Foldable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct unpack_impl<optional_tag> {
        template <typename T, typename F>
        static constexpr decltype(auto) apply(optional<T>&& opt, F&& f)
        { return static_cast<F&&>(f)(static_cast<T&&>(opt.value_)); }

        template <typename T, typename F>
        static constexpr decltype(auto) apply(optional<T> const& opt, F&& f)
        { return static_cast<F&&>(f)(opt.value_); }

        template <typename T, typename F>
        static constexpr decltype(auto) apply(optional<T>& opt, F&& f)
        { return static_cast<F&&>(f)(opt.value_); }

        template <typename F>
        static constexpr decltype(auto) apply(optional<> const&, F&& f)
        { return static_cast<F&&>(f)(); }
    };

    //////////////////////////////////////////////////////////////////////////
    // Searchable
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <bool>
        struct optional_find_if {
            template <typename T>
            static constexpr auto apply(T const&)
            { return hana::nothing; }
        };

        template <>
        struct optional_find_if<true> {
            template <typename T>
            static constexpr auto apply(T&& t)
            { return hana::just(static_cast<T&&>(t)); }
        };
    }

    template <>
    struct find_if_impl<optional_tag> {
        template <typename T, typename Pred>
        static constexpr auto apply(hana::optional<T> const& opt, Pred&& pred) {
            constexpr bool found = decltype(static_cast<Pred&&>(pred)(opt.value_))::value;
            return detail::optional_find_if<found>::apply(opt.value_);
        }

        template <typename T, typename Pred>
        static constexpr auto apply(hana::optional<T>& opt, Pred&& pred) {
            constexpr bool found = decltype(static_cast<Pred&&>(pred)(opt.value_))::value;
            return detail::optional_find_if<found>::apply(opt.value_);
        }

        template <typename T, typename Pred>
        static constexpr auto apply(hana::optional<T>&& opt, Pred&& pred) {
            constexpr bool found = decltype(
                static_cast<Pred&&>(pred)(static_cast<T&&>(opt.value_))
            )::value;
            return detail::optional_find_if<found>::apply(static_cast<T&&>(opt.value_));
        }

        template <typename Pred>
        static constexpr auto apply(hana::optional<> const&, Pred&&)
        { return hana::nothing; }
    };

    template <>
    struct any_of_impl<optional_tag> {
        template <typename T, typename Pred>
        static constexpr auto apply(hana::optional<T> const& opt, Pred&& pred)
        { return static_cast<Pred&&>(pred)(opt.value_); }

        template <typename Pred>
        static constexpr hana::false_ apply(hana::optional<> const&, Pred&&)
        { return {}; }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_OPTIONAL_HPP

/* optional.hpp
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
*/