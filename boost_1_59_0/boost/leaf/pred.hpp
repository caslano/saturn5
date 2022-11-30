#ifndef BOOST_LEAF_PRED_HPP_INCLUDED
#define BOOST_LEAF_PRED_HPP_INCLUDED

// Copyright 2018-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/leaf/config.hpp>
#include <boost/leaf/handle_errors.hpp>

#if __cplusplus >= 201703L
#   define BOOST_LEAF_MATCH_ARGS(et,v1,v) auto v1, auto... v
#else
#   define BOOST_LEAF_MATCH_ARGS(et,v1,v) typename leaf_detail::et::type v1, typename leaf_detail::et::type... v
#endif
#define BOOST_LEAF_ESC(...) __VA_ARGS__

namespace boost { namespace leaf {

namespace leaf_detail
{
#if __cplusplus >= 201703L
    template <class MatchType, class T>
    BOOST_LEAF_CONSTEXPR BOOST_LEAF_ALWAYS_INLINE bool cmp_value_pack( MatchType const & e, bool (*P)(T) noexcept ) noexcept
    {
        BOOST_LEAF_ASSERT(P != 0);
        return P(e);
    }

    template <class MatchType, class T>
    BOOST_LEAF_CONSTEXPR BOOST_LEAF_ALWAYS_INLINE bool cmp_value_pack( MatchType const & e, bool (*P)(T) )
    {
        BOOST_LEAF_ASSERT(P != 0);
        return P(e);
    }
#endif

    template <class MatchType, class V>
    BOOST_LEAF_CONSTEXPR BOOST_LEAF_ALWAYS_INLINE bool cmp_value_pack( MatchType const & e, V v )
    {
        return e == v;
    }

    template <class MatchType, class VCar, class... VCdr>
    BOOST_LEAF_CONSTEXPR BOOST_LEAF_ALWAYS_INLINE bool cmp_value_pack( MatchType const & e, VCar car, VCdr ... cdr )
    {
        return cmp_value_pack(e, car) || cmp_value_pack(e, cdr...);
    }
}

////////////////////////////////////////

#if BOOST_LEAF_CFG_STD_SYSTEM_ERROR
template <class E, class Enum = E>
struct condition
{
    static_assert(std::is_error_condition_enum<Enum>::value || std::is_error_code_enum<Enum>::value, "leaf::condition<E, Enum> requires Enum to be registered either with std::is_error_condition_enum or std::is_error_code_enum.");
};

template <class Enum>
struct condition<Enum, Enum>
{
    static_assert(std::is_error_condition_enum<Enum>::value || std::is_error_code_enum<Enum>::value, "leaf::condition<Enum> requires Enum to be registered either with std::is_error_condition_enum or std::is_error_code_enum.");
};

#if __cplusplus >= 201703L
template <class ErrorCodeEnum>
BOOST_LEAF_CONSTEXPR inline bool category( std::error_code const & ec )
{
    static_assert(std::is_error_code_enum<ErrorCodeEnum>::value, "leaf::category requires an error code enum");
    return &ec.category() == &std::error_code(ErrorCodeEnum{}).category();
}
#endif
#endif

////////////////////////////////////////

namespace leaf_detail
{
    template <class T>
    struct match_enum_type
    {
        using type = T;
    };

#if BOOST_LEAF_CFG_STD_SYSTEM_ERROR
    template <class Enum>
    struct match_enum_type<condition<Enum, Enum>>
    {
        using type = Enum;
    };

    template <class E, class Enum>
    struct match_enum_type<condition<E, Enum>>
    {
        static_assert(sizeof(Enum) == 0, "leaf::condition<E, Enum> should be used with leaf::match_value<>, not with leaf::match<>");
    };
#endif
}

template <class E, BOOST_LEAF_MATCH_ARGS(match_enum_type<E>, V1, V)>
struct match
{
    using error_type = E;
    E matched;

    template <class T>
    BOOST_LEAF_CONSTEXPR static bool evaluate(T && x)
    {
        return leaf_detail::cmp_value_pack(std::forward<T>(x), V1, V...);
    }
};

#if BOOST_LEAF_CFG_STD_SYSTEM_ERROR
template <class Enum, BOOST_LEAF_MATCH_ARGS(BOOST_LEAF_ESC(match_enum_type<condition<Enum, Enum>>), V1, V)>
struct match<condition<Enum, Enum>, V1, V...>
{
    using error_type = std::error_code;
    std::error_code const & matched;

    BOOST_LEAF_CONSTEXPR static bool evaluate(std::error_code const & e) noexcept
    {
        return leaf_detail::cmp_value_pack(e, V1, V...);
    }
};
#endif

template <class E, BOOST_LEAF_MATCH_ARGS(match_enum_type<E>, V1, V)>
struct is_predicate<match<E, V1, V...>>: std::true_type
{
};

////////////////////////////////////////

namespace leaf_detail
{
    template <class E>
    struct match_value_enum_type
    {
        using type = typename std::remove_reference<decltype(std::declval<E>().value)>::type;
    };

#if BOOST_LEAF_CFG_STD_SYSTEM_ERROR
    template <class E, class Enum>
    struct match_value_enum_type<condition<E, Enum>>
    {
        using type = Enum;
    };

    template <class Enum>
    struct match_value_enum_type<condition<Enum, Enum>>
    {
        static_assert(sizeof(Enum)==0, "leaf::condition<Enum> should be used with leaf::match<>, not with leaf::match_value<>");
    };
#endif
}

template <class E, BOOST_LEAF_MATCH_ARGS(match_value_enum_type<E>, V1, V)>
struct match_value
{
    using error_type = E;
    E const & matched;

    BOOST_LEAF_CONSTEXPR static bool evaluate(E const & e) noexcept
    {
        return leaf_detail::cmp_value_pack(e.value, V1, V...);
    }
};

#if BOOST_LEAF_CFG_STD_SYSTEM_ERROR
template <class E, class Enum, BOOST_LEAF_MATCH_ARGS(BOOST_LEAF_ESC(match_value_enum_type<condition<E, Enum>>), V1, V)>
struct match_value<condition<E, Enum>, V1, V...>
{
    using error_type = E;
    E const & matched;

    BOOST_LEAF_CONSTEXPR static bool evaluate(E const & e)
    {
        return leaf_detail::cmp_value_pack(e.value, V1, V...);
    }
};
#endif

template <class E, BOOST_LEAF_MATCH_ARGS(match_value_enum_type<E>, V1, V)>
struct is_predicate<match_value<E, V1, V...>>: std::true_type
{
};

////////////////////////////////////////

#if __cplusplus >= 201703L
template <auto, auto, auto...>
struct match_member;

template <class T, class E, T E::* P, auto V1, auto... V>
struct match_member<P, V1, V...>
{
    using error_type = E;
    E const & matched;

    BOOST_LEAF_CONSTEXPR static bool evaluate(E const & e) noexcept
    {
        return leaf_detail::cmp_value_pack(e.*P, V1, V...);
    }
};

template <auto P, auto V1, auto... V>
struct is_predicate<match_member<P, V1, V...>>: std::true_type
{
};
#endif

////////////////////////////////////////

template <class P>
struct if_not
{
    using error_type = typename P::error_type;;
    decltype(std::declval<P>().matched) matched;

    template <class E>
    BOOST_LEAF_CONSTEXPR static bool evaluate(E && e) noexcept
    {
        return !P::evaluate(std::forward<E>(e));
    }
};

template <class P>
struct is_predicate<if_not<P>>: std::true_type
{
};

////////////////////////////////////////


#ifndef BOOST_LEAF_NO_EXCEPTIONS

namespace leaf_detail
{
    template <class Ex>
    BOOST_LEAF_CONSTEXPR inline bool check_exception_pack( std::exception const & ex, Ex const * ) noexcept
    {
        return dynamic_cast<Ex const *>(&ex)!=0;
    }

    template <class Ex, class... ExRest>
    BOOST_LEAF_CONSTEXPR inline bool check_exception_pack( std::exception const & ex, Ex const *, ExRest const * ... ex_rest ) noexcept
    {
        return dynamic_cast<Ex const *>(&ex)!=0 || check_exception_pack(ex, ex_rest...);
    }

    BOOST_LEAF_CONSTEXPR inline bool check_exception_pack( std::exception const & ) noexcept
    {
        return true;
    }
}

template <class... Ex>
struct catch_
{
    using error_type = void;
    std::exception const & matched;

    BOOST_LEAF_CONSTEXPR static bool evaluate(std::exception const & ex) noexcept
    {
        return leaf_detail::check_exception_pack(ex, static_cast<Ex const *>(0)...);
    }
};

template <class Ex>
struct catch_<Ex>
{
    using error_type = void;
    Ex const & matched;

    BOOST_LEAF_CONSTEXPR static Ex const * evaluate(std::exception const & ex) noexcept
    {
        return dynamic_cast<Ex const *>(&ex);
    }

    explicit catch_( std::exception const & ex ):
        matched(*dynamic_cast<Ex const *>(&ex))
    {
    }
};

template <class... Ex>
struct is_predicate<catch_<Ex...>>: std::true_type
{
};

#endif

} }

#endif

/* pred.hpp
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
*/