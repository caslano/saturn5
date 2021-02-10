/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_VALUE_AT_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_VALUE_AT_IMPL_01062013_1700

namespace boost { namespace fusion {
    
    struct std_array_tag;

    namespace extension
    {
        template<typename T>
        struct value_at_impl;

        template <>
        struct value_at_impl<std_array_tag>
        {
            template <typename Sequence, typename N>
            struct apply 
            {
                typedef typename Sequence::value_type type;
            };
        };
    }
}}

#endif

/* value_at_impl.hpp
AeiP0oFhKBpLDWgSvg29U7Mx+CqqoDc4NHQrpNzSwC+JW2/EysqpaAWXTxzluSCokdV5Uy50khieFWKTkHBBXfMJmVboHO22LhMZDdSDLqq9/kzBxMD/0ua22sIHs9URrHGJHmgKcUSHvStcyYHIDo/zdR4JUNyQP8du3bMLSPka3W32lus83zKQDeMZnuRGcVA4oY/m4EaV9Qb9Pgl44MoseSDDHKz9aMwmZFOwQZcOgwvpTBpRzHEOlAoduSPNrj/sjS4wxQj/SBlanUAg9p2vGqfLu3rNIYaed6YwJUC+VWg0GPEDNfc9iEYD51IEJHAP1Hhb+gBHjmB32hsMBA0wjFuI9LyA1cEexhDC0K6kz9LgYthAvx2MNiWyKZT2/TQbsMKwBpgUj13SxEMfBGj4eIszJ2jDBBBWslGNFnQC8LhSbhlTDrlsThFZNZ9dnr2kE0ly9GSbFqwkJ8/pN1RHa/i29pEHkA1P5Vu0KLUvmCJsg6EkOJhphQgTocuZxa74dOIsIwWboxsm0cLtqjxcExsWngdM4AR3e6CFa+y+hYfCoGKdk4mTx7E+QDHAsNobDXv9yXCqunuAekljZHNl10BqhppAyMbEFWjN1oQM1TzOsLmlzOXBzi1r5nnCkbHC1dhP6nLjPNjw
*/