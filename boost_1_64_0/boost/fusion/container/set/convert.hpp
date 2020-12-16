/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_09232005_1341)
#define FUSION_CONVERT_09232005_1341

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/set/detail/as_set.hpp>
#include <boost/fusion/container/set/detail/convert_impl.hpp>
#include <boost/fusion/container/set/set.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct as_set
        {
            typedef typename detail::as_set<result_of::size<Sequence>::value> gen;
            typedef typename gen::
                template apply<typename result_of::begin<Sequence>::type>::type
            type;
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_set<Sequence>::type
    as_set(Sequence& seq)
    {
        typedef typename result_of::as_set<Sequence>::gen gen;
        return gen::call(fusion::begin(seq));
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_set<Sequence const>::type
    as_set(Sequence const& seq)
    {
        typedef typename result_of::as_set<Sequence const>::gen gen;
        return gen::call(fusion::begin(seq));
    }
}}

#endif

/* convert.hpp
yl5lr7JX2avsVfb6z78qkqb9ueP/TVfuV7CPAHh9YwC2sFSv3b6V/eRbeYvEEEcJ3I4rN0XY8mwhz84RynmdpOSUBEZm0OZhcmUswQXeFrVPaXUZGzxQ+mh3xNOtKeZrGcssPCJOulkqsyl1n1r7PcCZuTn8v4GujzCfyZgm0rfWcd9D7mRbCdK3Vr3vOTmRT9X7Kz5vrXw2JHxAiWfvZycnyjyd/Yn5TClL+tU+/g11Uq6jtJb7MuU989TfNyNt0luuvweTzpDH+m1tzT3Ucq+y0tPWjf6u/2itv0d5gJTJtRDbqxWpmsT/DXl3m5XJjWfaheLO+DCa8tV77c/aPrMmTjfcr+0j49w9rcRHeor0g7JuuIpJ6eJ+nbF8a49FmZNtWTbis3P2z1L4MHuqpi/udxK3csuul/TZ/d7+WTbR2Dvz8vKStj/v/Js1K/U2bjLgb7IO/dP5N1bEtNREQ1sUViy5fH5kmqJzLtqC5cIoDNfUFg30bSFz0sdjlXH24mXZxJF+ba00iot4slOnZFznsvlJ2kiZk5csm5+dn8XReDQ48cvyuaT5G//o4veuLIVK35BbSL+TP89V/NyOmJoy65rid7Tnb/Z4ZE4WtQ6XtZ/bItVvDzZKrDnS1rZrLspYRWaxcqNUae8fj8QthvGCfCR26WOu20YEV5Hrd7IONiKVJ468703iyL6x24gGtjhtm2J9P305rE+VtplKqkhMG0xjujHbiH+1VD6zzUjdRvxh+0zdRKhtWdEeN5sI8so2oprtM3UToW4fasjnms2Dun2oK39zbh707VDkUXLZVKYd/M+btcON2T7Y20FmZIinQMbx6yvLpQ/Jg3giTeO5MduHm+1txIyc3y1v+UzdPGi2D82df+Mfffy9ZAy9DrJ9aE+qpqxXpvHfmO1DK1s8MiPN9qGt5nMlUuOYq2skVg87tmvQNxFrsS7WEeyzjRo1tBRtrLkHhxmZz/u8bt7KBlL292RnsDTfd+02LuemkvffVqccyz/15bgzf2lr3fg1unFMq6vX/cjL/LCGL5/rymSDKmWW5p4u5f6ewB/U8XTVe2OP2MauSc6YIve6Oce00d+X+vsFplVia61fDusk1nbSPm1JNYm16AdtrNnXtByknTS/Bfp2mlDDOT5XQxmfy9OXdFFftpTp1phHxjF9InRxyHfVuH2VtupvL5+/2d/feVHfdhf5/4by7t+bY37PlOt7hczvvXJ9b06Yh/J5r5/92kT/NPfOLQPHNfq2ylIuJD/eUvn80ecf3PPOW7demlNnZ732Hj8Pc30vkvk9XO7fW/RkReXzHK8lPy4Y+eC4O9rFrPfsUvW063uOzO+lcnUvmOt7ynJs81n0xNoTX+7391+wf9TM1OWPf+vqHjH3n01qfs+a+/eUmd/z5epeM9f3XsVPVz4/uj7s16Pvp9aO6/XJ6y/m1KOjmf3ZmHLMK8fC+YZnYy6UZ0UuwnaGZ0VOxHxMwrswE5fiPZp7YVbgK7gS92ABHsS78TNchV/gPfg9rsZf8F55Fub92BbXYEd8QO2TK8elcryab+iTu1mu/T4p8T+Fwfi0Or0cY2Ir4/TSp7Ma1sc62ABbYkOUPgNyPMg8SfmGPgPUIa8e/ore+Bt2xMvYFf+FA/B3HI5/YJz0QZyigDOxPOZhBbwbK+IDWAmfwsoo9eGYzHV9qkl9bpL6VJf61JDpYy1yDAXxMr0HDpXpfctRH2yD3uiHHbEtdsV2OADb43DsgHHYUe0jLMc42E/mL9fq1T76tTAEG2IP9MOe6I+98BbsjWofCZlfDinf0EdinbT/Q+iPD2MwbsBe+AiG46M4Gh/DqbgR03GTeq+MHGfIPm4=
*/