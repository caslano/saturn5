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