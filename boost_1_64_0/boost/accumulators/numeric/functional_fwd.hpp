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
U/ZTPtt+ymfbT/ls+ymfbT/ls+2nfLb9lM+2n/LZ9lO+Q7Gf6v5+YMBID8COKmBc5AoYE7KMCR7j+mxjtteYNihgzM41LsrDCSB3T9JiOOtIxnPW83cDfzfim/4b4Gyhr2b6amJ//mzAJ3QjAWcdBDGtZjvg/ZygB5ytgWUO9GQIjCBR4gHoP40GjDc7yFbNaIQkqvydW0ldojydHUZLzd8tn11Gc81blo9pNNW8aae5C68NarYnZYEiuDgTxzLNwU7PMi1dgzmdVt/h/Sd7VwIfZXXEs9kAAYWNCBoONVXUYFCjixoEdL+wCxvZhSAEooYSC2hUwAi7GOUQDKlZP5ZDQbGVilVbb61ajUg1IUCiKAIq4lEFte2LqYpX5FC2/5l537ebBBBbetg2v9/me+e8c+bNmzdvXvW2ZG+Hak/ldWmonLfSQK62lQb0q9DmTpVGG6RbXb3NadTsOsrbod4w0b42lUY7dnSsNFIRX1u9rY1Rs7urt8NGb2VeWzTCWzmiPV51qDRgOQlddVilcRgna2vU7DnS22ErBSZXGh3p26HS6GTWoY6VxhH4UuU6e1xPr0uuromlezrsrNnT2Vznrbzo8Jqd7SoxOdDLrkqjK5KsRb1q9h7t6bCj8iKXuRZtOJIrd7S5luuWbgBM9baUmu+6ejooT+U1R6FvPJVXdKvZmVJpdCed6DSE+HmXbrJ5ebDdNTsPrzR6oNVc3b1dvB12mKu5usfQt0PN7s6VI47zVl7Ts9I49j/57h+/KZ3IThaz/Zt3mZ00oS/0Bd2VMRsi2NTtBJY6c/swkmY7cwVH+zpzBUVznLkaQ525AxhBPc5cwU+vM1fQ0+/M1djpzA0AOc3czKzkiJFp5vbJygX29wHgLAKcDcBZBLgvAGcR4Bwzd0BWLjB/AABnEWAPAGcRYC8AZxFgv5kbyMrFSrcpYgTYPjBsPeSrsvdhHTs6JBP6FPgFM9XlCICjLBgdDF2lMflqNAJw9zPfWU0MMVyj2DUArkJntdecXASfB74i8s0qhs8LXzH5JvaFzw/fBPhASPrAG4C3BF5QE4rNh3cSQxwFVym7CuEKec1wDvuKTF9+li8Tut2mb1SWrw90uk1fYZYvG7rcMJJu4OgB5Ak+rHN1tPEDoVsX8cEc+Dfm5AkQP5pXj/I5ru5jmNcOwP7PvAECy3Eenzluks8c4/WZw0t95hBUckzIMIcHkLrQiAzpYtZl1eKbThQlazVcPYn2ZFXDBd2wrBp8exmwuW44h+QDerYRgdtcg61in6D5F/j6Ek8Bb1+4c6Ipp+EzIJrSHx8PmPDuwJ2AF/yU1wuXH6FehIKiome9xISSgAUoNcqLf1QhP7TUkTwHzgDqWUYS0OH5cM00nPVwovcW0tmS4XwRvkL45pGPkxXBV8m+9fAVwzcfPvZMgGcReV6FpwSeJeTZAM8keJZRJvaVwncnfF7Uq8hAasygkJF1Zy+CZGSN6lXmy/L2munLms8nXL6sJb3m0RcpuOSsVfJee9ZTvZZwuFiy9yGcwBoRQNKW7asoPGKFE+QIQY5oyBENOaIhRzTkiIYcEciQDRfbDMu/81bnv+9v3/ZO174p2+Fobplc7FehdwjlxzD+gxbkq/EcEMyHh2nAvqyaNpyHRD+o/GZG986P1yIgd1I/fZsLzQThgQWR0ZnqjxKQT5QIAfnqZQkogxYDwuT1w30azWv49duxg7AKy/ddEul7Kds/3NJkvV96ir70wofcXwjRxGXPeQr1QA3xWEK+uhYeONBPqOH1n8ViZlvqSyfqR+bYQRX85vvm4BTn4D6RQX1ww945OBWPeJqD+zoHHx4Z1Bd37Z2D0yKDcszBA5w=
*/