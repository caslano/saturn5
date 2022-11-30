/*!
@file
Defines `boost::hana::to` and related utilities.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CORE_TO_HPP
#define BOOST_HANA_CORE_TO_HPP

#include <boost/hana/fwd/core/to.hpp>

#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/common.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/detail/wrong.hpp>
#include <boost/hana/unpack.hpp>
#include <boost/hana/value.hpp>

#include <type_traits>
#include <utility>


namespace boost { namespace hana {
    //////////////////////////////////////////////////////////////////////////
    // to
    //////////////////////////////////////////////////////////////////////////
    //! @cond
    template <typename To, typename From, typename>
    struct to_impl : to_impl<To, From, when<true>> { };
    //! @endcond

    namespace convert_detail {
        struct no_conversion { };

        template <typename To, typename From, typename = void>
        struct maybe_static_cast : no_conversion {
            template <typename X>
            static constexpr auto apply(X const&) {
                static_assert(detail::wrong<to_impl<To, From>, X>{},
                "no conversion is available between the provided types");
            }
        };

        template <typename To, typename From>
        struct maybe_static_cast<To, From, decltype((void)
            static_cast<To>(std::declval<From>())
        )> {
            template <typename X>
            static constexpr To apply(X&& x)
            { return static_cast<To>(static_cast<X&&>(x)); }
        };
    } // end namespace convert_detail

    template <typename To, typename From, bool condition>
    struct to_impl<To, From, when<condition>>
        : convert_detail::maybe_static_cast<To, From>
    { };

    template <typename To>
    struct to_impl<To, To> : embedding<> {
        template <typename X>
        static constexpr X apply(X&& x)
        { return static_cast<X&&>(x); }
    };

    //! @cond
    template <typename To>
    template <typename X>
    constexpr decltype(auto) to_t<To>::operator()(X&& x) const {
        using From = typename hana::tag_of<X>::type;
        return to_impl<To, From>::apply(static_cast<X&&>(x));
    }
    //! @endcond

#define BOOST_HANA_DEFINE_EMBEDDING_IMPL(TO, FROM)                          \
    template <>                                                             \
    struct to_impl<TO, FROM> : embedding<>                                  \
    { static constexpr TO apply(FROM x) { return x; } }                     \
/**/
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(long double, double);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(long double, float);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(double     , float);

    BOOST_HANA_DEFINE_EMBEDDING_IMPL(signed long long, signed long);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(signed long long, signed int);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(signed long long, signed short);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(signed long long, signed char);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(signed long     , signed int);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(signed long     , signed short);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(signed long     , signed char);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(signed int      , signed short);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(signed int      , signed char);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(signed short    , signed char);

    BOOST_HANA_DEFINE_EMBEDDING_IMPL(unsigned long long, unsigned long);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(unsigned long long, unsigned int);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(unsigned long long, unsigned short);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(unsigned long long, unsigned char);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(unsigned long     , unsigned int);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(unsigned long     , unsigned short);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(unsigned long     , unsigned char);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(unsigned int      , unsigned short);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(unsigned int      , unsigned char);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(unsigned short    , unsigned char);
#undef BOOST_HANA_DEFINE_EMBEDDING_IMPL

    namespace detail {
        template <typename T>
        struct copy_char_signedness {
            using type = typename std::conditional<std::is_signed<char>::value,
                std::make_signed<T>, std::make_unsigned<T>
            >::type::type;
        };
    }

    // If `char` is signed, we define an embedding from `char` to any signed
    // integral type. Otherwise, we define one from `char` to any unsigned
    // integral type.
#define BOOST_HANA_DEFINE_CHAR_EMBEDDING_IMPL(TO)                           \
    template <>                                                             \
    struct to_impl<detail::copy_char_signedness<TO>::type, char>            \
        : embedding<>                                                       \
    {                                                                       \
        static constexpr detail::copy_char_signedness<TO>::type             \
        apply(char x)                                                       \
        { return x; }                                                       \
    }                                                                       \
/**/
    BOOST_HANA_DEFINE_CHAR_EMBEDDING_IMPL(long long);
    BOOST_HANA_DEFINE_CHAR_EMBEDDING_IMPL(long);
    BOOST_HANA_DEFINE_CHAR_EMBEDDING_IMPL(int);
    BOOST_HANA_DEFINE_CHAR_EMBEDDING_IMPL(short);
#undef BOOST_HANA_DEFINE_CHAR_EMBEDDING_IMPL

    template <typename T>
    struct to_impl<T*, decltype(nullptr)> : embedding<> {
        static constexpr T* apply(decltype(nullptr)) { return nullptr; }
    };

    //////////////////////////////////////////////////////////////////////////
    // is_convertible
    //////////////////////////////////////////////////////////////////////////
    template <typename From, typename To, typename>
    struct is_convertible : std::true_type { };

    template <typename From, typename To>
    struct is_convertible<From, To, decltype((void)
        static_cast<convert_detail::no_conversion>(*(to_impl<To, From>*)0)
    )> : std::false_type { };

    //////////////////////////////////////////////////////////////////////////
    // is_embedded
    //////////////////////////////////////////////////////////////////////////
    template <typename From, typename To, typename>
    struct is_embedded : std::false_type { };

    template <typename From, typename To>
    struct is_embedded<From, To, decltype((void)
        static_cast<embedding<true>>(*(to_impl<To, From>*)0)
    )> : std::true_type { };

    //////////////////////////////////////////////////////////////////////////
    // Conversion for Constants
    //////////////////////////////////////////////////////////////////////////
    template <typename To, typename From>
    struct to_impl<To, From, when<
        hana::Constant<From>::value &&
        is_convertible<typename From::value_type, To>::value
    >> : embedding<is_embedded<typename From::value_type, To>::value> {
        template <typename X>
        static constexpr decltype(auto) apply(X const&)
        { return hana::to<To>(hana::value<X>()); }
    };

    //////////////////////////////////////////////////////////////////////////
    // Foldable -> Sequence
    //////////////////////////////////////////////////////////////////////////
    template <typename S, typename F>
    struct to_impl<S, F, when<
        hana::Sequence<S>::value &&
        hana::Foldable<F>::value
    >> : embedding<Sequence<F>::value> {
        template <typename Xs>
        static constexpr decltype(auto) apply(Xs&& xs)
        { return hana::unpack(static_cast<Xs&&>(xs), hana::make<S>); }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_CORE_TO_HPP

/* to.hpp
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
*/