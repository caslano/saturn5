///////////////////////////////////////////////////////////////////////////////
/// \file functional_fwd.hpp
///
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_NUMERIC_FUNCTIONAL_FWD_HPP_EAN_08_12_2005
#define BOOST_NUMERIC_FUNCTIONAL_FWD_HPP_EAN_08_12_2005

#include <boost/mpl/if.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace numeric
{
    // For using directives -- this namespace may be re-opened elsewhere
    namespace operators
    {}

    namespace op
    {
        using mpl::_;
        using mpl::_1;
        using mpl::_2;
    }

    namespace functional
    {
        using namespace operators;

        template<typename T>
        struct tag
        {
            typedef void type;
        };

        template<typename T>
        struct tag<T const>
          : tag<T>
        {};

        template<typename T>
        struct tag<T volatile>
          : tag<T>
        {};

        template<typename T>
        struct tag<T const volatile>
          : tag<T>
        {};

        template<typename T>
        struct static_;

        template<typename A0, typename A1>
        struct are_integral;
    }

    /// INTERNAL ONLY
    ///
#define BOOST_NUMERIC_FUNCTIONAL_DECLARE_UNARY_OP(Name, Op)                                     \
    namespace functional                                                                        \
    {                                                                                           \
        template<typename Arg, typename EnableIf = void>                                        \
        struct Name ## _base;                                                                   \
        template<typename Arg, typename ArgTag = typename tag<Arg>::type>                       \
        struct Name;                                                                            \
    }                                                                                           \
    namespace op                                                                                \
    {                                                                                           \
        struct Name;                                                                            \
    }                                                                                           \
    namespace                                                                                   \
    {                                                                                           \
        extern op::Name const &Name;                                                            \
    }

    /// INTERNAL ONLY
    ///
#define BOOST_NUMERIC_FUNCTIONAL_DECLARE_BINARY_OP(Name)                                        \
    namespace functional                                                                        \
    {                                                                                           \
        template<typename Left, typename Right, typename EnableIf = void>                       \
        struct result_of_ ## Name;                                                              \
        template<typename Left, typename Right, typename EnableIf = void>                       \
        struct Name ## _base;                                                                   \
        template<                                                                               \
            typename Left                                                                       \
          , typename Right                                                                      \
          , typename LeftTag = typename tag<Left>::type                                         \
          , typename RightTag = typename tag<Right>::type                                       \
        >                                                                                       \
        struct Name;                                                                            \
    }                                                                                           \
    namespace op                                                                                \
    {                                                                                           \
        struct Name;                                                                            \
    }                                                                                           \
    namespace                                                                                   \
    {                                                                                           \
        extern op::Name const &Name;                                                            \
    }

    BOOST_NUMERIC_FUNCTIONAL_DECLARE_BINARY_OP(plus)
    BOOST_NUMERIC_FUNCTIONAL_DECLARE_BINARY_OP(minus)
    BOOST_NUMERIC_FUNCTIONAL_DECLARE_BINARY_OP(multiplies)
    BOOST_NUMERIC_FUNCTIONAL_DECLARE_BINARY_OP(divides)
    BOOST_NUMERIC_FUNCTIONAL_DECLARE_BINARY_OP(modulus)
    BOOST_NUMERIC_FUNCTIONAL_DECLARE_BINARY_OP(greater)
    BOOST_NUMERIC_FUNCTIONAL_DECLARE_BINARY_OP(greater_equal)
    BOOST_NUMERIC_FUNCTIONAL_DECLARE_BINARY_OP(less)
    BOOST_NUMERIC_FUNCTIONAL_DECLARE_BINARY_OP(less_equal)
    BOOST_NUMERIC_FUNCTIONAL_DECLARE_BINARY_OP(equal_to)
    BOOST_NUMERIC_FUNCTIONAL_DECLARE_BINARY_OP(not_equal_to)

    BOOST_NUMERIC_FUNCTIONAL_DECLARE_BINARY_OP(assign)
    BOOST_NUMERIC_FUNCTIONAL_DECLARE_BINARY_OP(plus_assign)
    BOOST_NUMERIC_FUNCTIONAL_DECLARE_BINARY_OP(minus_assign)
    BOOST_NUMERIC_FUNCTIONAL_DECLARE_BINARY_OP(multiplies_assign)
    BOOST_NUMERIC_FUNCTIONAL_DECLARE_BINARY_OP(divides_assign)
    BOOST_NUMERIC_FUNCTIONAL_DECLARE_BINARY_OP(modulus_assign)

    BOOST_NUMERIC_FUNCTIONAL_DECLARE_UNARY_OP(unary_plus, +)
    BOOST_NUMERIC_FUNCTIONAL_DECLARE_UNARY_OP(unary_minus, -)
    BOOST_NUMERIC_FUNCTIONAL_DECLARE_UNARY_OP(complement, ~)
    BOOST_NUMERIC_FUNCTIONAL_DECLARE_UNARY_OP(logical_not, !)

#undef BOOST_NUMERIC_FUNCTIONAL_DECLARE_UNARY_OP
#undef BOOST_NUMERIC_FUNCTIONAL_DECLARE_BINARY_OP


    namespace functional
    {
        template<typename To, typename From, typename EnableIf = void>
        struct promote_base;
        template<typename Left, typename Right, typename EnableIf = void>
        struct min_assign_base;
        template<typename Left, typename Right, typename EnableIf = void>
        struct max_assign_base;
        template<typename Left, typename Right, typename EnableIf = void>
        struct fdiv_base;
        template<typename Arg, typename EnableIf = void>
        struct as_min_base;
        template<typename Arg, typename EnableIf = void>
        struct as_max_base;
        template<typename Arg, typename EnableIf = void>
        struct as_zero_base;
        template<typename Arg, typename EnableIf = void>
        struct as_one_base;

        template<typename To, typename From, typename ToTag = typename tag<To>::type, typename FromTag = typename tag<From>::type>
        struct promote;
        template<typename Left, typename Right, typename LeftTag = typename tag<Left>::type, typename RightTag = typename tag<Right>::type>
        struct min_assign;
        template<typename Left, typename Right, typename LeftTag = typename tag<Left>::type, typename RightTag = typename tag<Right>::type>
        struct max_assign;
        template<typename Left, typename Right, typename LeftTag = typename tag<Left>::type, typename RightTag = typename tag<Right>::type>
        struct fdiv;
        template<typename Arg, typename Tag = typename tag<Arg>::type>
        struct as_min;
        template<typename Arg, typename Tag = typename tag<Arg>::type>
        struct as_max;
        template<typename Arg, typename Tag = typename tag<Arg>::type>
        struct as_zero;
        template<typename Arg, typename Tag = typename tag<Arg>::type>
        struct as_one;
    }

    namespace op
    {
        template<typename To>
        struct promote;
        struct min_assign;
        struct max_assign;
        struct fdiv;
        struct as_min;
        struct as_max;
        struct as_zero;
        struct as_one;
    }

    namespace
    {
        extern op::min_assign const &min_assign;
        extern op::max_assign const &max_assign;
        extern op::fdiv const &fdiv;
        extern op::as_min const &as_min;
        extern op::as_max const &as_max;
        extern op::as_zero const &as_zero;
        extern op::as_one const &as_one;
    }

    template<typename To, typename From>
    typename lazy_disable_if<is_const<From>, mpl::if_<is_same<To, From>, To &, To> >::type
    promote(From &from);

    template<typename To, typename From>
    typename mpl::if_<is_same<To const, From const>, To const &, To const>::type
    promote(From const &from);

    template<typename T>
    struct default_;

    template<typename T>
    struct one;

    template<typename T>
    struct zero;

    template<typename T>
    struct one_or_default;

    template<typename T>
    struct zero_or_default;

}} // namespace boost::numeric

#endif

/* functional_fwd.hpp
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
*/