
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
pzmgcsZdLmwe+CBUolNUpe8jv6Dnv0e3VeiVa5tc8bAyfZ9ygDeezWYrbFE2dTlmPmWEeGDKAJ4ySvVM5ZqnxIo80QPxZSYTTmI7C8QTbiZgsaj7/jTt+IOZCLTK54Frt8BORIA1qrFGsWnINyhK/YAVlcaMls9RzIS3Ol1/cBSGo3DU6XZHnXY36Yw4F8ejdjdrZZ0k7LUP+FHSy7Kw1U1DnvFWJkbo1DnOeukB56PO4QZ+zJ4Rj5dFZmDKH5NVu6Jeob8gVZX5ghNJ6ENRigybSCVoOT7wBwthd86v74YXN9EOFe/N9e2QkWIxw+OL6KtYTmZGOpPybCF9zJZ5od/1bozDwDoNB14hkMjO3e3J6cUty+WISoUpjTNEGmuaRe6K0xUq/VjOjKdVjNgboFjBi452vf6ZBJqDm5U8s6IETF1dtigjljHWMqZGW9+rq4AmK6bS6kTjNXE0Q81gOVkb3jkGi+CZOg3vZxwHwYcxBsfhiCqxnc9nt3cX1z81vA9JIgo0v2VvG16DGK9CuPIM/7o+/9G4c1jUu0O85fb8BhqBPBEwQQSQBqxGCVRKTS1x+5B1IJVjaaHQpQVVTUeollQIRpIlNRiOQFvKwmk/8Ay75Fj/V9i5mRRp1HzLGBqfPRzHX7pHX5+Z
*/