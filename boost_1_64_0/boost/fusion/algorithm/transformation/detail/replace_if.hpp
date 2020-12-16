/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REPLACE_IF_08182005_0946)
#define FUSION_REPLACE_IF_08182005_0946

#include <boost/fusion/support/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <bool is_convertible>
    struct replacer_if_helper;

    template <>
    struct replacer_if_helper<false>
    {
        template <typename U, typename F, typename T>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static U&
        call(U& x, F&, T const&)
        {
            return x;
        }
    };

    template <>
    struct replacer_if_helper<true>
    {
        template <typename U, typename F, typename T>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static U
        call(U& x, F& f, T const& new_value)
        {
            return f(x) ? new_value : x;
        }
    };

    template <typename F, typename T>
    struct replacer_if
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        replacer_if(F in_f, T const& in_new_value)
            : f(in_f), new_value(in_new_value) {}

        template<typename Params>
        struct result;

        template <typename F1, typename T1, typename U>
        struct result<replacer_if<F1, T1>(U)>
        {
            typedef typename remove_reference<U>::type value;
            typedef typename
                mpl::if_<is_convertible<T, value>, value, value const&>::type
            type;
        };

        template <typename U>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename result<replacer_if(U)>::type
        operator()(U const& x) const
        {
            return replacer_if_helper<is_convertible<T, U>::value>::
                call(x, f, new_value);
        }

        F f;
        T new_value;
    };
}}}

#endif


/* replace_if.hpp
DF0+qiXdtRb52C17+O+BfeFe2B/eAJPgTTAF3gxnwRp4BrwVLoG3QQfcD6V+y9oP7qFF/a6SswbWw17wPNgPng+j4QaVDtJAOhdKOtWSzkWSzsWSziX6Mwwkna5IjeEsgkslnctgF7hFF69a4iVbxDsq+l6E8fAliZeN1I31b9+dYbrEu4LrusJtcCS8SuJvl/LcAZfBq2EhvAYWw2uhZy8DWe8AMyV9v70MxK43YAJ8E06Ex+AU+BacB9+W9I4gdZKejf+rMZxJM6Wtp3xT4Sg4DcbD6XACnAHT4UyYC2fBy+BsuBemwbvgHHgvnAsfhfPgqzAdvgXnwz/DDNgeOxbAU2Am7AoXwh5wEewDF8N+MAt62o+sR4BLLdrPGqnnDjgalsJY6JRyKYfzoQsugpW6elAr6YZb1IP0dp76Mx92hRnwH7A3Eeok3t+kXG2eM4vcfx9IvT0ObfAjmAg/htnwr7AAfgJL4GfwIvg53Aq/gDvgl/Au+BX8GfwnfAx+DZ+B38Bj8N9QM+Zb2AmGSfm1gUNgBzgGdoRZsBMshZ3hBngSvBSeDPfAU+BdsAv8GewKn4Hh8DkYAY/CSPg+7A4/hKfK/ToRJusD4D4pH63eviflGiX1rjccDPvC0XAAzIaD4Apogw44GFbAoXAjjIY74TD4IBwOD8MRsA7GwDfgSPgOHANPwo5YOBSOhfFwHDwNxsEMGA9XwATogOPhRpgIL4LJUk4pcC+cAG+GE6G7/baRdQCyPqAGGa61X6kXBVzXH9rhOFgEU2AxnAZXw/lwDcyBDrgelsBqWAovh2WS/3JYCyvg89AF34aV8C9wHfwMngu/hedJOWyEkfACOAxeCGfCargAXgIvgJvgbngpvBVeBvfBLfBJuBU+DS+H78Er4GdwG/wGXgv7UAa7YD94PbTBPTAR7oWnwxtgOrwRZsKbpDwfDpO1AHCU1KMe/PedUo86SvvqBGNhFzgVdoXLYThcAyPgeTAS3gq7w0fgqfAV2AMegz3hBzAKHoe94Yewj/QXfeHncADU+rGBMAraoA0OgcPgULk+DzkySfdeZDgT60vZ1/srOAz+6z/snQtcVfUdwC+CSj6BTFFJMcUnKigSminmI0hUNCoqGw9BIRGvPBTNFSt1tizJqNmbylLTijYra2xh09KyjTZzrLlFZuWma7ReVtr2Pff+7v+ee+65D4hqj3s+/fp6D+d3fr//87x+53fgSHgaxsMzcBb8Gl4B/wWvhkHsn32rb7Y1IskXyPwo9RQpMd7aMlj3rZkhcDgcDUfARBgLk+FImAJHwTlwtNRjHCyA8bAEjoU3wXHwXpgIX4RJ8BU4Hh6AE2ATvADis2USjIDJsDecAgfCi+BwOBXOhtPhPDjDWT7i7D2XL1XKN1PKN0vKN1vKN0fKly7lmyvlmyflu1TKlyHlu1zKlynlu1LKd5WU72op33wp3zVSvmwpX66Ub4GUL0/Kly/lWyTlK5DybbZIHD58Q/pJGNwg5XtLvh33tvSTJpgK34Hz4VFYBN+FpfA9WA4/gGvgcbgB/hVugidgDTwJn4N/h/XwH/BV2AwPwo+hjEOJtadOTMZhrZy/PgP7wGdhf00PpsAX4Bz4C5gB6+A6+CtYDV+Emo16+BrcA9+EL8G34a/hO3AvPAH3Qc2ZV+C5cD8cAQ/AifBVeClkX3Kclxh82N3kOP+OnCcehd3gu/rzRC96L7Sz6/0CdoN1UH0jy4teuJxXRMBu8Gzo0Kv3otdB9DqKXqhOr8mL3nvi5/vi5wdOPxl8nvWixN65Yq+fzl60F71msfeR2Punzl6yF70Lxd4ksTcZqvYTvTEmehezXU+YAkfCVKjawYs=
*/