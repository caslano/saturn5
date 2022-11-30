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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_OPTIONAL_HPP

/* optional.hpp
+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
*/