
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/preprocessor/expr_if.hpp>
#include <boost/preprocessor/inc.hpp>
#include <boost/preprocessor/cat.hpp>

#if !defined(AUX778076_COUNT_ARGS_PARAM_NAME)
#   define AUX778076_COUNT_ARGS_PARAM_NAME T
#endif

#if !defined(AUX778076_COUNT_ARGS_TEMPLATE_PARAM)
#   define AUX778076_COUNT_ARGS_TEMPLATE_PARAM typename AUX778076_COUNT_ARGS_PARAM_NAME
#endif

// local macros, #undef-ined at the end of the header

#if !defined(AUX778076_COUNT_ARGS_USE_STANDARD_PP_PRIMITIVES)

#   include <boost/mpl/aux_/preprocessor/repeat.hpp>
#   include <boost/mpl/aux_/preprocessor/params.hpp>

#   define AUX778076_COUNT_ARGS_REPEAT BOOST_MPL_PP_REPEAT
#   define AUX778076_COUNT_ARGS_PARAMS(param) \
    BOOST_MPL_PP_PARAMS( \
          AUX778076_COUNT_ARGS_ARITY \
        , param \
        ) \
    /**/

#else

#   include <boost/preprocessor/enum_shifted_params.hpp>
#   include <boost/preprocessor/repeat.hpp>
#   include <boost/preprocessor/inc.hpp>

#   define AUX778076_COUNT_ARGS_REPEAT BOOST_PP_REPEAT
#   define AUX778076_COUNT_ARGS_PARAMS(param) \
    BOOST_PP_ENUM_SHIFTED_PARAMS( \
          BOOST_PP_INC(AUX778076_COUNT_ARGS_ARITY) \
        , param \
        ) \
    /**/

#endif // AUX778076_COUNT_ARGS_USE_STANDARD_PP_PRIMITIVES


#define AUX778076_IS_ARG_TEMPLATE_NAME \
    BOOST_PP_CAT(is_,BOOST_PP_CAT(AUX778076_COUNT_ARGS_PREFIX,_arg)) \
/**/

#define AUX778076_COUNT_ARGS_FUNC(unused, i, param) \
    BOOST_PP_EXPR_IF(i, +) \
    AUX778076_IS_ARG_TEMPLATE_NAME<BOOST_PP_CAT(param,BOOST_PP_INC(i))>::value \
/**/

// is_<xxx>_arg
template< AUX778076_COUNT_ARGS_TEMPLATE_PARAM >
struct AUX778076_IS_ARG_TEMPLATE_NAME
{
    BOOST_STATIC_CONSTANT(bool, value = true);
};

template<>
struct AUX778076_IS_ARG_TEMPLATE_NAME<AUX778076_COUNT_ARGS_DEFAULT>
{
    BOOST_STATIC_CONSTANT(bool, value = false);
};

// <xxx>_count_args
template<
      AUX778076_COUNT_ARGS_PARAMS(AUX778076_COUNT_ARGS_TEMPLATE_PARAM)
    >
struct BOOST_PP_CAT(AUX778076_COUNT_ARGS_PREFIX,_count_args)
{
    BOOST_STATIC_CONSTANT(int, value = AUX778076_COUNT_ARGS_REPEAT(
          AUX778076_COUNT_ARGS_ARITY
        , AUX778076_COUNT_ARGS_FUNC
        , AUX778076_COUNT_ARGS_PARAM_NAME
        ));
};

#undef AUX778076_COUNT_ARGS_FUNC
#undef AUX778076_IS_ARG_TEMPLATE_NAME
#undef AUX778076_COUNT_ARGS_PARAMS
#undef AUX778076_COUNT_ARGS_REPEAT

#undef AUX778076_COUNT_ARGS_ARITY
#undef AUX778076_COUNT_ARGS_DEFAULT
#undef AUX778076_COUNT_ARGS_PREFIX
#undef AUX778076_COUNT_ARGS_USE_STANDARD_PP_PRIMITIVES
#undef AUX778076_COUNT_ARGS_TEMPLATE_PARAM
#undef AUX778076_COUNT_ARGS_PARAM_NAME

/* count_args.hpp
8kFrFZSpy/ZuvJNm/2p6kWv4j6BKgR5B12i3Wj55nJFbhyd/ml7pkt5+JB74a9OUnYVBV/qpb1ZE109dNCey/umO5yPYv1ej/AmFUfRfocs3B5GwuDJedOtq1Bcbpb6r8yK/z14euj27V1Ztz5PPR2/P72ZH6b+qLyT+w68VviKjFGY1khiKSmPwCMtjpAx8WlNLzTBgi1Qz/IBrgAdJ3EFJ7lFJPrQl8QQleVwl2WhLQrY6MJXC4ZiYYSyjRLDcfjQJJmsQzXtVOTAC26KS3MPlSFyQa2XDp18lhU7TL0FmT8z0C2RV2a3xyhsznYsTA2BkHJMKkuZc3E9VfFTzo/EVDiyy/Cm2vGxnq38X3p59bgOLrV5ht2ff1ECx1UrbUMa8B8QSTO7AEHTHuCZKnoswkp6j/4WpDVDHyzZJe5q4ixQ//gvA6rrYkHDHy5bTRS/BTzYRuWI2y1y/uzA4l5tzzbblqquBbL1bZK5nKuXySmRcKxeiIsJi1UhVdY3WuVogl4dzpdpyLRcj+JDhVlk6XmhzIzE5RggdD+94rMvV/YH+xlzwyK8JtxBjibz/5teABX1wErNzbf1Xy5CU5xlP6TKvUWVO4DJxiRvz/M+VTbPuf09VxVtj7d4thMBl3YWmO+yquD4lWL0lWL0HPZYqbrADojRevd95FNAXQXohatVkKUnB+f05szFWpOBLkdnkQ7xOLWvpmxxJdAMTbuKaAOHAIFGs9TupJzsZNgB/zGUz431ihb2O694JS84691F7xEsqa5vo8Oax9u0qJCk6GGnzZGstTVIDdBuJJi3LtFGiXnBb9+m21MPavYHbErjafO4O3PgoJZAXceFzBs7FtYGljxKcyjYd/nns2BHoa6TZVttjvNri8rDaILWabKAeNHjRKnw33u8uDZzeSPpZqa0s/4cn5flVVtU5FA3/vJ7lGSoUk5bq232zUn2zGXtKkl4xjDrWqBLa8MR4EEnphZOVKs4dtd+Pb5EmZ5+7cUIpFcfF1pFSopK8C7GzRx9wbi6+nIv3dz8NPXuk8dq2IVi/1mZTCLzl9CeUfghgOmT7D7dosWliCZxTONrt7eHmCDEq0PpSDKQrUptx39oYXF/Gq8H6vXStX7tzXij9Vgfo1zqvCqcfa7xA+7+FzP/dk/B/Wxku/+jbVf7iuaHy9xLvzVfD5Wd7yrqknLZBTTqypF80C7AZxqMcBOqS1SiIHuZd40Y0PomQJOQ+Va8s2JYN6waLFGFr2kNpEEoVNEWZAp8qUzCHvgrmCdwQC01aoJHTqWLI6D/KRGuAPYHpJXumywMzfDEqwcwVChqpuYoF+ALngSEz8pw9/2Ex/jfep/WfBaHm56L7oP8sjDg/4+ZZ8VU+WQECLM+Dj0M6puKkubCO5Zi63g5VlIkXbu155Gabv7/AgUGdD8RNrRP/E6bUVKMLkV8lNnqtrZ1XETMDhxt6k24T7PYLdDd6UC4lRZyhc7XBldHNXP4VrFugEsgWSrLilLuO/2IZe5kPE0fOWWEpxPgXTKysj3TPj6SP/GZE5fTH5kVKf9n8yulXR0zfcnzl9JPmRcWTSC8A/WNRZ3aKEG7sdvAd+4E7lZlnIAnLYuCcIFPolr7LcLpy9L3FfMAWzlAeDn2xYRlv7S5swESsm0Q268mur43v67A/f4Dti8GP7I/H7P5ky0HYR2QH6X+XR9O3Dh4epP+Nmv7puUH636jpp98TpP9dXlwdvIm1+Upel93ZwphIpaOVXWkgTMcxa49HvSSGjQpupoeMpmW3LrDK6ajKORflpMjQ1gVKWnwBn9xWyOc9N2CqTpvoWfiPc8LLq2pp4p8eJBfaeLQZy4Xuz1fWG8w=
*/