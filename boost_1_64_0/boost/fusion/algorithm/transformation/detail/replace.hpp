/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REPLACE_08182005_0841)
#define FUSION_REPLACE_08182005_0841

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <bool is_convertible>
    struct replacer_helper;

    template <>
    struct replacer_helper<false>
    {
        template <typename U, typename T>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static U&
        call(U& x, T const&, T const&)
        {
            return x;
        }
    };

    template <>
    struct replacer_helper<true>
    {
        template <typename U, typename T>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static U
        call(U& x, T const& old_value, T const& new_value)
        {
            return (x == old_value) ? new_value : x;
        }
    };

    template <typename T>
    struct replacer
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        replacer(T const& in_old_value, T const& in_new_value)
            : old_value(in_old_value), new_value(in_new_value) {}

        template<typename Sig>
        struct result;

        template <typename U1, typename U2>
        struct result<replacer<U1>(U2)>
        {
            typedef typename remove_reference<U2>::type value;
            typedef typename
                mpl::if_<is_convertible<T, value>, value, value const&>::type
            type;
        };

        template <typename U>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename result<replacer(U)>::type
        operator()(U const& x) const
        {
            return replacer_helper<is_convertible<T, U>::value>::
                call(x, old_value, new_value);
        }

        T old_value;
        T new_value;
    };
}}}

#endif


/* replace.hpp
0M8PNNtzGvbUmu1p9nPda08/jz0qLX0fcMLCninYU2e2p0We933Fpp5ikz49vV1bBpntOh27TpjtapF3Aa9dXcQufXr694QYm7VdEbNNdrXYe8JAg23GNPX163AA++LM9jX7PcK/zAhT6fl/U84cbH7HSNX6A0ubCu1OV1Gz+gLZA0BLx/9dR+yYLGML7ldLrS8w2/GdvOt4v13bdXTbR+L+5eQYYt47eSb21Vvat9KRv6qiWbahjjBPOvpy+nqIuQ7N1p7NZ5jsaPZ7mLeP6u2uQ5KW4T3l2qFme9K0Z7bZnhZ5P/PW6+5ik0rPYNeYaLNdc7Erz2xXi7y7ee0a7LZLn56/XU9Z2JWOXdVmu1rkvc5r11CxS5+evl5lDTPUb+kHaiztclaWsx21vYntL8qv/Ulahn7pWAB76i3tcZVXVgTvAxC4L/Ckoy8Xx3DrPtuWZrKj2e/CUX59tkrLv/1b2JOhtTezPc1+R/ba003skbT8+8URAd6dTfZUlmpvz8G8S1q9Pyv/B9Gnzp8XfTVGfTJVGMqYsxqLCzQWKOuG8mLM65Uytb5ljqwbUh4B2mBgCOuF1PyStAXRd0Qi90K6is7t2LrDrI+PBhZHORyN6tSnnz7S8y+jRcdwZCfp15rTd5Y5m54nb7uvd4dpyaysLC0I8yvbOgtbrsGWExa2VFYUNckOafMyvu10lRvKY+Yo8/1dpL2nzdXboHd/Cn4tWkKy9Vq0g6PM93ixVqesdKrb3Lhefb76jzbnayk6qq10hLjGbkmKdd3dN9p8P5dxba2lTu2WBq9TlaVhDszqno4ZY17rdxZ2nLCyI8R1fktSGl/n57XjgTHm8ignH3Hz9HYo96ni0sLgyyPOojxO725dHjGx5rpwNvlwWtkRYh3HDsu6UGOhMxedNZY6qeNB1L8o0bnMnc8CXJ7xqjbo7THWrDcfvXVWekOs964A7XnfWPN9LkBnWLqVTrrVZpSxt18t7a7vVw31f5x1vUu1sifEdhhKvXtgnLkdriN+tZUdIbZDV3Lj7dD7nImIM/e31/KcOeJnR2jPU2/au+PMZX0dadf7pR36s/RfFs/SGwz3XL+uu3e82Y7d2GGbr7cjtOcoNpjK+Oeqz/Uvh4Oi/x7RfzuSjb15Hv2ywYH7uI+CEmfj72leH5szxZ9LfNHk9wqdL41x/l/u+XhPYqtRngAXQbv27pxhtMft71jgPStnS9uG9z1wtpV9D9C/o62/f9/utma/hZq2Zj/6g21958WIb56Uud6Hw8rfRfrANtxv93XubCi/iUz4VS8tnI8+gjU/rDu5L10oi02a/QvceTeUnYuE5b1Y+Y463QaIL4aEufz8tT4l/Pj3sJY90Jr1rdFa+PJVe45G3LLkgw2f5Xy5eWD204HWsrfcWRita9y/nzXuT3XQwp98Mfsvhxz9jn97dc3MN4be/4/Aa9//6b6+9o/LBu/Ju/3kzac81ybq8wOP0KanauGVV1+R+sBX3S4Ie/DfP7115dLrmrYmPjVM1k3BUqTGsPd6uexFXwEnQxdMhZWwGK6Dkg5rlQKns1rSWSPpOCSdEkmnVJdObQPp5Es6KySdAkmnUNKxSzqZYbL+BlZIOp3gTEnnTElnqaSTLeksg/PgcrgAngVLYY4u3TpJ9zyLdOdJuulwDJwPx8MMOAMugE64EFbCRSpdWZsC7RbpDpU12NGwLxwG+8PhcAIcAefAGJgHR+rSPSHpLrRIN1nSTYED4QQ4BE6ECXASPANOhulwijobRNaSwMuRGsPZIKdKulFwLOwFk2FvOAn2hWmwH7TD/nADHACr4SC4Gdp0+YiItc6H8YyAgXC65GOG5GOm5GO25OM=
*/