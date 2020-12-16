/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_PP_LIST_TIE_07192005_0109)
#define FUSION_PP_LIST_TIE_07192005_0109

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/fusion/container/list/list.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/generation/detail/preprocessed/list_tie.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/list_tie" FUSION_MAX_LIST_SIZE_STR".hpp")
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
        struct list_tie;
    }

// $$$ shouldn't we remove_reference first to allow references? $$$
#define BOOST_FUSION_REF(z, n, data) BOOST_PP_CAT(T, n)&

#define BOOST_PP_FILENAME_1 <boost/fusion/container/generation/detail/pp_list_tie.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_LIST_SIZE)
#include BOOST_PP_ITERATE()

#undef BOOST_FUSION_REF

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
        struct list_tie< BOOST_PP_ENUM_PARAMS(N, T) BOOST_PP_REPEAT_FROM_TO(BOOST_PP_DEC(N), FUSION_MAX_LIST_SIZE, TEXT, void_) >
        #undef TEXT
        {
            typedef list<BOOST_PP_ENUM(N, BOOST_FUSION_REF, _)> type;
        };
    }

    template <BOOST_PP_ENUM_PARAMS(N, typename T)>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<BOOST_PP_ENUM(N, BOOST_FUSION_REF, _)>
    list_tie(BOOST_PP_ENUM_BINARY_PARAMS(N, T, & arg))
    {
        return list<BOOST_PP_ENUM(N, BOOST_FUSION_REF, _)>(
            BOOST_PP_ENUM_PARAMS(N, arg));
    }

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* pp_list_tie.hpp
xMU4C1diLq7HPCxHM+7DfHwOC/BjtOCXOBd/wiJsQ6XmYWdciAPwFkzARTgHl2EpluARXI5f4l34Da7EK9mmVRiMpdgZV2MsrsHJuBYLcR1uwvW4De/Fo7gRT+B9+CZuxi/wfrwikHbEtvgHHIkPYjJuwSJ8CG/BbbgIt+MWfATL8XF8Gv+I72IFnsHd+A0+ia3YJ3uwN+7FSbgPF+BTWIz78V48gLvwIB7EZ/B9fBY/xkNYpy73lrAhvoAt8DDegC9hHzyCA/FlHIPHcRa+gqvxBK7Ht/EhfAeP4bv4PlbheXwPf8T3Ubn/9QHWxTPYCD/EKPwYe+FZHIxfYzaew1vxW7wfv8Mt+D2W4w/4CJ7HHfgjHsN/4Kt4Af+C/8J3MaA241ixFnasz5/YFQNxGNbBUVgPU7A+zsUgXIRX4BJsgPfilbgJG+JWbISP41W4B6/GZ/BafAVD8D1sjkqggBbYAEPxWmyJLbANhmFbHIntMBE74CzsiHOwE67Dzng/dsGHsSs+iTfgixiBr2MkvoNR+Dn2wC+wJ/6A0Xgd54Ne2AF74w0Yg92xD8ZhP0zA/piIA/EmHITTMRZn4VBcgXH4KA7DJ3E4/hlH4CsYj3/Fkfg3HIXnZMye9GGhb4vtPDXd9v1mXYplfOVijMJl2BdLcCjeiYl4F+bjCpyHd2MJluIOXI27cC0ewHX4PK7HT/FerMbfY10qcx82xs1owgcwHctwOm7BBbgV1+JDuAkfxodxGz6O5fgabse38FGsxsfwO6zAq9jmJ7AJ7sQw3IWdcTcm4JM4DvfizfgU5uHTuAT34/14EI/gM/gGVuLb+Cx+h8/hj/gCNqaND2MsvoSj8Agm4VH8Hb6Ms/AErsZXcT2+gQ/im3gE/4Jv41v4KZ7Ez/EUKp1fT2MjfAfDsQqj8D3shR9hAn6M4/BTnIZfYQFW41L8Gu/Cc1iK3+BG/A4fxe/xMP6AJ/A8vok/4vf4D2xUl/MGRuFP2Av/hYlYK5Dtx9qYgXVxA9bHzRiET+MVWIkN8CO8Ej/Hq7BNPY5lDMfGGIHX42AMwRRshmnYHJdgC1yKLXEbtsU92A6PYnv8EDvhFxiOP2AX/Ad2tf8+CpQ+PdLXR/k8Zaj6gv5ZxgMfwn74PI7AF9CEL+JkPIxZ+BLm4hGcj0fxdnwZV+Fx3Imv4FP4NzyMp/Esvo3fYBUGUan3sCl+gEn4IWbjR3gbfozL8FN8AD/D3fg5voxn8SP8Ar/EL/FatvErbIpfYyh+g9H4LY7B73A6fo+5+APeg+fxXvwRN+IFfAJ/wqP4T3wZA2pxHsPa+A0G4nmsh6G0bX3sh0E4BBtgBl6J2dgILXgdrsLGuBOvx73YFI9jCJ7GZvgZNsfAOhwf2ABDsTW2xPbYChOxNSZhGOZgG8zFtng/tsMt2AEfwY64BzvhIeyMJzAc38SueBa74dcYiSEc31EYhT1wLPbEZIzGifgb/B32xgKMwUXYF1dhP7wXB+LDOAhPYix+hYOxFsftEGyFQzEc43AgDsOROBxH4wjMwFH4OxyNi3AMrsBEXIPjcDOOx22YhNsx2RmHQ/pG2fpMpWjicOQqn2s0YzhaMAoLcQLOwak4D7NxPq7ABbgGb8WHcRH+CYvxZVyM7+Jt+B7ejnUpcwk2wGXYApdjP1yBQ3ElzsC7cSauweW4Fh/DdfhHvBcP4gY8hhvxdfw9/oD3YS22dRMG4v3YCMuwKz6I3XEL2uIrSF8o+XeKJr7CgDp8HnEQRmAs9sDB2A+H4DksJZkln88kn6txieSjjK8OxbEYiSaMwXE4FZMwAyfgfJyId+Ak3I4p+BhOwcN4I76CU/EdvAk/wN/ih5g=
*/