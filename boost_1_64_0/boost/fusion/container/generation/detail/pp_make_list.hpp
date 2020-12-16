/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_PP_MAKE_LIST_07192005_1239)
#define FUSION_PP_MAKE_LIST_07192005_1239

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/fusion/container/list/list.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/generation/detail/preprocessed/make_list.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/make_list" FUSION_MAX_LIST_SIZE_STR".hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace boost { namespace fusion
{
    struct void_;

    namespace result_of
    {
        template <
            BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
                FUSION_MAX_LIST_SIZE, typename T, void_)
          , typename Extra = void_
        >
        struct make_list;

        template <>
        struct make_list<>
        {
            typedef list<> type;
        };
    }

    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<>
    make_list()
    {
        return list<>();
    }

#define BOOST_FUSION_AS_FUSION_ELEMENT(z, n, data)                               \
    typename detail::as_fusion_element<BOOST_PP_CAT(T, n)>::type

#define BOOST_PP_FILENAME_1 <boost/fusion/container/generation/detail/pp_make_list.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_LIST_SIZE)
#include BOOST_PP_ITERATE()

#undef BOOST_FUSION_AS_FUSION_ELEMENT

}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif
#else // defined(BOOST_PP_IS_ITERATING)
///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////

#define N BOOST_PP_ITERATION()

    namespace result_of
    {
        template <BOOST_PP_ENUM_PARAMS(N, typename T)>
        #define TEXT(z, n, text) , text
        struct make_list< BOOST_PP_ENUM_PARAMS(N, T) BOOST_PP_REPEAT_FROM_TO(BOOST_PP_DEC(N), FUSION_MAX_LIST_SIZE, TEXT, void_) >
        #undef TEXT
        {
            typedef list<BOOST_PP_ENUM(N, BOOST_FUSION_AS_FUSION_ELEMENT, _)> type;
        };
    }

    template <BOOST_PP_ENUM_PARAMS(N, typename T)>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<BOOST_PP_ENUM(N, BOOST_FUSION_AS_FUSION_ELEMENT, _)>
    make_list(BOOST_PP_ENUM_BINARY_PARAMS(N, T, const& arg))
    {
        return list<BOOST_PP_ENUM(N, BOOST_FUSION_AS_FUSION_ELEMENT, _)>(
            BOOST_PP_ENUM_PARAMS(N, arg));
    }

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* pp_make_list.hpp
QDKpiLSVdJj0CSloPHGISPEkC2ktaR/pDKkhN3xjSFNJJaQdpBOks6TG3NyKJCWQzKS1pP2kM6SGE3gfKYW0kFRGOkaqJoVyMyyOlD3RH8vIv/gX/+Jf/It/8S/+xb/4F//iX/6fll8o/p8yfvayxP8b1ZFno5r5/xfKPc65pNciA1iB+4WqOHKRMnzXOhCZHFPJOivA+3G86rHHV9nGQsoYeItLjINvpT7FpFDSAtIb1KdMU58oqY8Mnb+oejjixQTb47xpYqLwmn08Z1iA2xyVjjYskee+WdKGaaS/UOfYEa51lirLtKy26UZ9mePWWXftfJ4ZeTmZrjE/ukmfsHVSp1LSSTKpNKhTwSz2Z0a62Zu5YvVibck4eYm5ZM1IE9OrIGt2gGsckENSxwJlXenL8FfeUByvjUsilbuE462zYz+bHfvzSlVd1cfgpjoSZ4NKtEAT/o16BY90ibMxyzwzS1U178ZjdxylGY+tM+9lNmrHuJsdrzFVtHP/S9vmTsuxONtbHd9QPW6zfV39uTsrR/0yc3d+i8W1Lt+YLf0xScZjxfTHnBmO/dIfs2U4xsh4rNXddZXXrzrRsGR6u/cGfvN09JPXzxqZffnGeBmNYaqyjpG6pmXWxq7Dbv/g5JmD55Z3COMhpO2Zs5zj5dyfXcv1mXO6jH2Zhr/BDJyMWXgTzsC5mIOOvg+SX7Hkp+77MEuereZhRzRjBM7GHliA2ViI+TgH52ARLsB5KH2f5LxKXaQcdd+nSVLvFOyKk7E7TsHeeCMOx6mYhr9V5Vsp+a7TybeJ5NsMw7E5jsEWOA5bSn1bYym2ceQr5zMs0Mm3vfQJ6SztEo4x2AX7Y1dMxG6Yi2yLzNEo5yM5T5GvyxyNPQNk7Bm2x97YC2NwCvbBdOwn+fbHRTgAl+JAfBgHYTkOxj/hENyPcXgch+EJHIHvYzx+jSPxRxyNjahbAl6NidgETdgXx2EcjsdETEITJqufhY4ynEOEv3l/bVzgeY6Q9jvleaRmfhD13CA8c5TnjS7zgcj8HzXO/SHPBnld9TwwIJbySfGk8xHu83kcIqmf450kyVwd8ozO9nxuLcbtrHl+jqkkvfk4OpMy5flZ/FDX52WZO43n2FDPrVGkrEfSex6mfgYmz77Uz720z7rUc2bIfBnGz64SbM+sfJ4PI5LknPfC+Sypimc2wZN4tkPKJK0gVZDemOR/luNf/It/8X35pa7/C3KjLvn6v21Aw2v28WOmylSX3+RuMXvSC4u4LmCd3fzYiRynuw4XcqkWS4BtvXmsV6Vab1ji0NShYxOThyUmO1bswnqV/EAyj5f1JD4OK08cljDWNMyZpbV+WeRZnOSS5/jJJmd+baV+1ap14kaOGJaU7Fq3GH4klCU711ECXtgKzrFkzXJdr1q73sRh40cOn+xYs7msFztBWc/cOzNrenrhTIvyn6z/7R1+mKUp/81xaT3NMm0mvxulvYNUbUQj8x7ZzonO19Xb92xL6iT/zRFPKM6xinM/TtKsM965IztKuwen6K7jyCxC6hI22bneyKSkCaw3ODEuNYmWGJyg3key30tV62t3pXKfqVHHALnWZ1251g+ywW9giQnYT66ptTtIrj3B4Hra1rax5FFp3Xcz8zLSZ/JG13sMQXX0yw2WcnV2uNflBk8wLrdIyg2XexvtSUsjaWMpV33QEvHGq/tA9njHb9qu711iQp812M7YPm7lUVfv29asaVt1mfHyk6k1qRGpOWkZFUzT2UZCIHncPnX77avr3n7LybtU8lafGDzHHnJtv7d02q9bPf32M/VxL8+XY6QyyfgYWVHPvf3upIIn9LaRBvTmGFHdx2Ij3NtwhdI=
*/