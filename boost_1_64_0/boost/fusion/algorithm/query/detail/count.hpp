/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_COUNT_09162005_0158)
#define FUSION_COUNT_09162005_0158

#include <boost/fusion/support/config.hpp>
#include <boost/config.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/fusion/support/detail/access.hpp>

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning (disable: 4512) // assignment operator could not be generated.
#endif

namespace boost { namespace fusion { namespace detail
{ 
    template <bool is_convertible>
    struct compare_convertible;

    // T1 is convertible to T2 or vice versa
    template <>
    struct compare_convertible<true>
    {
        template <typename T1, typename T2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(T1 const& x, T2 const& y)
        {
            return x == y;
        }
    };

    // T1 is NOT convertible to T2 NOR vice versa
    template <>
    struct compare_convertible<false>
    {
        template <typename T1, typename T2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(T1 const&, T2 const&)
        {
            return false;
        }
    };

    template <typename T1>
    struct count_compare
    {
        typedef typename detail::call_param<T1>::type param;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        count_compare(param in_x)
            : x(in_x) {}

        template <typename T2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        bool
        operator()(T2 const& y) const
        {
            return
                compare_convertible<
                    mpl::or_<
                        is_convertible<T1, T2>
                      , is_convertible<T2, T1> 
                    >::value
                >::call(x, y);
        }

        param x;
    };
}}}

#if defined (BOOST_MSVC)
#  pragma warning(pop)
#endif

#endif


/* count.hpp
SbPpR/uOmbj58dFg5/JILQ340b5jJm5+1A6x11XVEdOP9h0zcfOj01C7H6ofph/tO2aCH45jJtcODb0uvY36YfrRfmMm5v4iNh8Szg71oaNRN9YEfGi/MRM3H7Y6+JBq1AvTh/YbM2Gei+OYScqwUB9OMuqE6UP7jZmYPti/fzj4cJ1RH0wf2mfM5PvdnMdMUtJC7V9j1IW1AfvtM2Zit3/EaLPbsBbOea1a9GvknNfCRb+GLdo1cp/V2jbntWrRr3n7T1vb9pZvDduJR5L/vm5RyYWvnDr4Ou8NV3Rtv3j4SZOM37O+c+DwwIt3/X7E96fde9V3Hi5q2xq59DjNIYcXI/W2eKelGi5bA8sgojipmuMNVzjoDVLc0cFwGRwKTXvSy3bQ26b48TfDOfBW6I+jrHnRmi9db4ujfJn0NsGp8HI4G34RngdrYQW8Aq6HV8Lt8Msw4NdhpT/awa8C5WcVHAE9yk9GnOYew53S6wjTpHeeym8xHAKXwLvgMlNf84TBTQ76ubK7HPaHK2AdvNBankvcy7NO5XKDyvNGS35Tl7rrXS29r0rvWoterfQ2OOjNVH5nwSo4x/RT81NhqYPePOVzPiyCCy16jdIrctBLlV5fmAcpI9UXzQeFOxzqyzrlrxxOg144F14Ml8JKWAmr4EZYA++Al1jjBH/evb5MkV9T4QhLvO4sJFN6l0jvJDg5EK9bfnlgOiyGGXA1nAxL5FcpDNSfZqV3X0j9gboew1X/RsAGONKsf5q3CG910B+jfIxV/RsHvwEnQH/8fs07hNuRelv8/hTpd4cZsAecDHvCb8KzzOuseYRwgkN59lXc5X5wDOwPzfoRRq+z9LpIr6v1+l3grjdMemnSGw7Ndi+MXpL0kqWXYt3vIYze56WXK73l1nYpjN4M6c2U3izrfgwr3fUWSG+h9BZZ9OrC6E2Q3kTpTbLoNa90vx92qh406H64x9ouXOiut116t0nvdmt9udDdz3fk52/l57vW+hJG7xHpfU96j1rry0XuevdKb5f0dlvrSxi9O6RXL707rfUljF7nE1Svoa9eQ7O+hNF7TfZel703rPUlz13vBNmLl72O0KwvYfR+IXsHZe+X1vqS537d39N1P6Tr/r61vuS76/1Uej+T3gFrfQmj91fpfSi9v0HzOoTROyi9X0rvRWjmL9+9XD6W3j/gGPiJqYcUuOu9LL1XpPcaNJ/LBe5+3iC9r8vPG63vD2H0rpLeV6S3BZr3wyp3vcel90PpPQHNehZG70HpPSS9h635C6N3mfQ2Se8L1vyF0fNK72LpVZp6+kYORjm936peD4bD4RDrfRRGr5v0EqV3OjTzF6Tnvn/NcOMcaOYvjF5P6fWS3lnW9qwoRC90nwPpXWTNXxi9LOnNld48a/7C6C2W3hLpLbXmL4zeVOmdK71Ma/487td9t677fbru91vrZxi9O6V3l/S+ZXnfrJVersP75gfy8wgcBP8KR8AP4Sj4NzgLfgQXwb9D3/c6S//ncJj0n1L6Tyv9Hyv9nyj9/Ur/GaX/U6X/M2i2j8Xu5fye0j+kcv6j9TkVRu8x6T0uvSes7X8YvQek1yi971j7Lavd9XZI79vSu9uavzB6J+v51gkOh6dAM39h9F6SvZdl7xVr/sLo/VN6n0rvX9b8lbjrPSe956XXZM1fiXu9Pax6+4HqLTot+XPVw470mqT3c+vzzVWP/EiPE9AD1vyVuus1S+9N2XvL+vwudS+XjiqXE1UuJ1nrZxi9d2Tvt3A4/J01f2H8/Ib0vik/t0Ezf2vc9a6R3rXSu86avzB6T0nvR9LbZ71+YfS+J7090nvUmr8werXSu0J6X7Lmb627Xo0=
*/