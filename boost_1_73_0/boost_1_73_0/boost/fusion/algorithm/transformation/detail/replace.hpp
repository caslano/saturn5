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
D7EvHa8eZ+NIj0wfnOweFKfsXGt4KI0Gvt+edDuXHTeNfVvY4MIiPQEbFNwFunFUAA33vGixMb44JHHY5A5lZraibfQW/pdC12Bwl+9TwpZYlO0mS0Sl2wTCv0XzAEnR4kTTtn3s0P5xY59EIYH9CpSuG8ffLVInSVkkS/ATtM5q6lywembBptRPpHL5c5b1Ev6v1e9/6lSxoQ3r7uYofcsvn+Tj74xFCV/VquR9zStKuyjGeMAAhOrwQ71NGx0bxtqzHfjXLKO1+BZSV6BiJfQAalkxY+VmYCRnmsDx1hNYwvNZWUSys0CdLn5bOowBFwYrvSwa6V2k/SYN/wBPIOAae+TokKHRqLvvrHpgd0yNkO2tavvSS8qEE2klOfvqrjgdsx2o5Ozpk/9NJRKp6Cu9oth9BC1SvvP/lCDgsHvhxOfXWWCyVft6qzgxls6RW8IdcpsKxHiT7aGoNdCSg0JsLXKDerNslepUdGlywq8ErnGP2WrAacPN4j6eiejmRiWT76dEImukNJcxWRCZ8SgrEUTicMl0QNRtNTluogdVB/GlIhTBQ7AKF3SzlFBsoROSu7kUAY5TGvQFLKwmu1hIVaCF2WPYtZR6QUYB/o9FRUJJlV3HmHWYWJbwIGnz7KhEv0QDamQHpGvC
*/