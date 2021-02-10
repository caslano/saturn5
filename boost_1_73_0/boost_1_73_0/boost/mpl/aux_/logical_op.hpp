
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

// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION!

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/bool.hpp>
#   include <boost/mpl/aux_/nested_type_wknd.hpp>
#   include <boost/mpl/aux_/na_spec.hpp>
#   include <boost/mpl/aux_/lambda_support.hpp>
#endif

#include <boost/mpl/limits/arity.hpp>
#include <boost/mpl/aux_/preprocessor/params.hpp>
#include <boost/mpl/aux_/preprocessor/ext_params.hpp>
#include <boost/mpl/aux_/preprocessor/def_params_tail.hpp>
#include <boost/mpl/aux_/preprocessor/enum.hpp>
#include <boost/mpl/aux_/preprocessor/sub.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/inc.hpp>
#include <boost/preprocessor/cat.hpp>

namespace boost { namespace mpl {

#   define AUX778076_PARAMS(param, sub) \
    BOOST_MPL_PP_PARAMS( \
          BOOST_MPL_PP_SUB(BOOST_MPL_LIMIT_METAFUNCTION_ARITY, sub) \
        , param \
        ) \
    /**/

#   define AUX778076_SHIFTED_PARAMS(param, sub) \
    BOOST_MPL_PP_EXT_PARAMS( \
          2, BOOST_MPL_PP_SUB(BOOST_PP_INC(BOOST_MPL_LIMIT_METAFUNCTION_ARITY), sub) \
        , param \
        ) \
    /**/

#   define AUX778076_SPEC_PARAMS(param) \
    BOOST_MPL_PP_ENUM( \
          BOOST_PP_DEC(BOOST_MPL_LIMIT_METAFUNCTION_ARITY) \
        , param \
        ) \
    /**/

namespace aux {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< bool C_, AUX778076_PARAMS(typename T, 1) >
struct BOOST_PP_CAT(AUX778076_OP_NAME,impl)
    : BOOST_PP_CAT(AUX778076_OP_VALUE1,_)
{
};

template< AUX778076_PARAMS(typename T, 1) >
struct BOOST_PP_CAT(AUX778076_OP_NAME,impl)< AUX778076_OP_VALUE2,AUX778076_PARAMS(T, 1) >
    : BOOST_PP_CAT(AUX778076_OP_NAME,impl)<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , AUX778076_SHIFTED_PARAMS(T, 1)
        , BOOST_PP_CAT(AUX778076_OP_VALUE2,_)
        >
{
};

template<>
struct BOOST_PP_CAT(AUX778076_OP_NAME,impl)<
          AUX778076_OP_VALUE2
        , AUX778076_SPEC_PARAMS(BOOST_PP_CAT(AUX778076_OP_VALUE2,_))
        >
    : BOOST_PP_CAT(AUX778076_OP_VALUE2,_)
{
};

#else

template< bool C_ > struct BOOST_PP_CAT(AUX778076_OP_NAME,impl)
{
    template< AUX778076_PARAMS(typename T, 1) > struct result_
        : BOOST_PP_CAT(AUX778076_OP_VALUE1,_)
    {
    };
};

template<> struct BOOST_PP_CAT(AUX778076_OP_NAME,impl)<AUX778076_OP_VALUE2>
{
    template< AUX778076_PARAMS(typename T, 1) > struct result_
        : BOOST_PP_CAT(AUX778076_OP_NAME,impl)< 
              BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
            >::template result_< AUX778076_SHIFTED_PARAMS(T,1),BOOST_PP_CAT(AUX778076_OP_VALUE2,_) >
    {
    };

#if BOOST_WORKAROUND(BOOST_MSVC, == 1300)
    template<> struct result_<AUX778076_SPEC_PARAMS(BOOST_PP_CAT(AUX778076_OP_VALUE2,_))>
        : BOOST_PP_CAT(AUX778076_OP_VALUE2,_)
    {
    };
};
#else
};

template<>
struct BOOST_PP_CAT(AUX778076_OP_NAME,impl)<AUX778076_OP_VALUE2>
    ::result_< AUX778076_SPEC_PARAMS(BOOST_PP_CAT(AUX778076_OP_VALUE2,_)) >
        : BOOST_PP_CAT(AUX778076_OP_VALUE2,_)
{
};
#endif // BOOST_MSVC == 1300

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    BOOST_MPL_PP_DEF_PARAMS_TAIL(2, typename T, BOOST_PP_CAT(AUX778076_OP_VALUE2,_))
    >
struct AUX778076_OP_NAME
#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    : aux::BOOST_PP_CAT(AUX778076_OP_NAME,impl)<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , AUX778076_SHIFTED_PARAMS(T,0)
        >
#else
    : aux::BOOST_PP_CAT(AUX778076_OP_NAME,impl)< 
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        >::template result_< AUX778076_SHIFTED_PARAMS(T,0) >
#endif
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          BOOST_MPL_LIMIT_METAFUNCTION_ARITY
        , AUX778076_OP_NAME
        , (AUX778076_PARAMS(T, 0))
        )
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , BOOST_MPL_LIMIT_METAFUNCTION_ARITY
    , AUX778076_OP_NAME
    )

}}

#undef AUX778076_SPEC_PARAMS
#undef AUX778076_SHIFTED_PARAMS
#undef AUX778076_PARAMS
#undef AUX778076_OP_NAME
#undef AUX778076_OP_VALUE1
#undef AUX778076_OP_VALUE2

/* logical_op.hpp
XSUN6xCdDsg9EA1r52YS1PUYfzy7ig/Prv76ctSNvd8vo1m8+PPL5ysUZwxKtPTB/qDzfu3O/U/uVl0Dgyo0P6YF6B32jceefi0yF9mwee26EjdvfMMmxF2/y4JukPS2wI3jrYR6PRYFtOs6ruOx5iMwvNdlzX9F1tzbrPl3WNvq+Q6DuM8oZazruH6v13H6vcjrJp1OjwWPsRa8IgzvNozgDowgYr0esD5zY9/3IrdHnSgIEieJ+0kUOd59GLoU6/IJ7euastf/fPwLUEsDBAoAAAAIAC1nSlKwPe/MHgUAAHMbAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MjAyNVVUBQABtkgkYOVZW3PaOhB+90z+g5pO5/QSYjDQJhwnM4ZwcQqEgoGkLx1hC9uNsVxJhJJff1YWt6blnORM6S0exki2tLvft9rVIkxBuHAxJ6eaGcZjCl/XZD6jzOOnWsNxOukN1auOapQxD12EpyJQ/bbTbKmuqa8nmrqS9RT1CLshLMNDj2gmI0k0P9U080kmg6xIEBZjQZAICIJ5hEELi6WK2FPCA4LhFUc4SQhmKIwRIzyhMSccCaqRmE8ZUTPXgjxKePyXQBMsQMshymSWamsh4wJEfJoCcBRgvgHpAM0Y
*/