/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ADAPT_DEREF_TRAITS_05062005_0900)
#define FUSION_ADAPT_DEREF_TRAITS_05062005_0900

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref.hpp>

namespace boost { namespace fusion { namespace detail
{
    struct adapt_deref_traits
    {
        template <typename Iterator>
        struct apply
        {
            typedef typename
                result_of::deref<typename Iterator::first_type>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& i)
            {
                return *i.first;
            }
        };
    };
}}}

#endif



/* adapt_deref_traits.hpp
ZDGn1xra02GZBPaclj02w8SSk9xQMcvXD2bSNmx0PHQz64aOQ7rIjdP04IF1AIL6V2d/LOPJmgcrDRnPR3jWoYe5JOWSVxHb+9uWWZflQ5OVpAf6vWCSNAavV02UZcMVIEs5015OQuWMuRXYKYxOLCOOUc6acnjqd28PV3Cankvf8usQkSaEnfN2+2KpAaiFYoSeyqbicB1BmLMwo4E6U7dW7SXZqKsk6hLVR4fBudWeqIkSHW84LL8U4hkfWzTP4KUeH72A5/psrH4O4lU9hYctdeSRzw5osno0U/Gdn3ijEh2xIK72MKErVXwvjcesyIPBg2cLFh2h75w3WswnkUeHitgUU1YXWVwDyxH3crAij58ZtyaHELwKcQLNuzFSaOH8JLxI7bzM98CqnLpQrPgTuqqnXWHq1FeMtYE1RNkxYxfz8I7Flxme1gZtdwxAx3jQEsOlILdxYQwEYSu0MDT9gMvgzsaJgQ08P5tilBDTeymh2MC1DlmZ5sU2jjlPT37JQHKS4vwi0HcK4OpBaGBpgT4rYaLWgcldxmocTJFgpSWYt9ls9VDx6wCKz9ET3zIFabRQtLvLhM6lEiMoNgL8qzSVmO0IGkHxlQADaV0JsKGdtoGhttktAotkSxa/CDHPmGos1P4aeOEs
*/