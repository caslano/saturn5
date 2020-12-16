
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
AMWNw1ACcAHodYvYlckC6SnxiZBrfhpaD/w4FnIHMF88aLNihQrCQRUEBEMjZkTwxY+VCWQSyYjmwqPF5viZkUbBcRgMNYy6WIcgcGDkJzwU96NxYm2SFYoVi4XzJrGSgtFwoM9rRI9h08EdQ8B1kqGgkchJuj3tCrSY4QoH3vs00Yt2uS+zBAMBkDOhUiKRW66TMbXmJFAvIeAGGjPc44heBYz6e66D4tbnxRo2ciUxdAc2HDCNJw49L6j3HlvoX4j2MOQ0JImBaehy6SNjh7jz4lC5cPl7ZINqTtNZ0BgTgYz5ubVhMRydp07BD004CTtEvvdOAvTaSN5bU4HWo56NdjIMh/DEIpdbRkLvhUJCc+TBoxcxxyfCzTRwOUpiJKKzyxr4mAkSHOCZzxx++Mzoz8blcAa68yng3Nqeuy9pYGXAyoNVIGDvJDZg7cE6gPUE6wXWF6zfHz8XwsOMYv80z9hYyZ9tIu52g+l1BZ/JyzRSoRG5aCSUQCKRwVBwQ+UzQn/DCP+DRuTfbAh/p/nb9YVqcf9T9QJiCJH9agsFcTQpsXFRG7jiIVQIhGGDBRhoI8AKpEAu6JAHHfjjaHb8HWWGAfOP+i7yuPrTfgCPkX+yXGMJScAvUK6Ai+mjbRHF0WUJAiquQcOFDQYsv+nGzW/c5fd3cTC8/l98eE7f5ev//cVD5M4Dn0Hj4ITnDyeYhvh5w/Vv+McftLz9pEHC4+rqJ39ksF188iDzXbGA0Dq56IDjGCrYzr9Srt84jd/tgUlc/NzyFFx+/njBcMr3100Xp9zc5e3f/OLIgbv8/ZtOLrkgcMff4EfLz13v3H4Bz5k/Le8/bCCxtrEqnLum8Xz947cS/+r+Bw2ZEDGu77rnk3F91zPPmajQJMCV4MKJjFehyYArw4UzHdeXLxdwUuBKceFSIT70GhEuXL6pCk0RXEUuXCCkoQGuBgf3v2dIMLJQoYbECZIgazm4N0KVoE7QhOfgKII+YSzBHEZ0uBGa4AI6ij6gnxgET5hwQjQ8MxII8wmLCSsIqwibCFsIOwl7CAcIRwkFhELCFcI1wg3CLUIVoY7QSHhFeENoJXwidBKIRGGiJFGaqEBUIioTNYljiCbE8URLoivRi+hPnEkMIoYT44lJxDnE+cSlxNXEdcRs4h7iPuJx4kniWeJF4jViKfEesYJYRawjvia+I34h/iB2EUVJ4iRV0jCSLmkMaTzJnGRDciV5kaaQppECSKGkSFI0KYW0kLSYtIy0mrSBtImUR9pHOkwqIF0i3SBVkB6TakmNpNekVtI30k8SkUwly5FVyTrkUeSxZBOyOdmS7ET2I08j+5MDyLHkBDKLnEJeRV5L3kLOIx8kHyUXkM+Tb5Hvku+TH5PryK/In8jfyJ3kLrIwRZQiTVGiKFM0KVoUXcoEih3FgeJC8aD4UWZSGJRIynzKQsoqygbKTsoeykHKScolyjXKLco9SgWlmtJAeUfponRTyFRRqjhVhqpAHUxVpmpRdaj6VC/qFOpMaig1hbqQupa6gbqJmk3dRT1APUw9+hf2zj0aygaP40/JZTAG434bDMa4jdu4DcYYkqwkSZJkJUmSJCtJknSTJKkkyUryWkmSJJVVSSVJKklSqSRZSZLsd5/ds2dv5+zlnz17ec75vM47J+/LzO/7+X3P9DzPiFaLNoq2iLaKtom2i3aKdosOiI6KToqKi1HF5MSUxRhiTDFjMY6Yk5hAzEPMU8xbzE/MXyxILFwsUSxFLE0sXaxArEisWKxCrE6sXqxZ7K5Yh9gTsV6xEbFxsUmxKTGKOF2cIc4StxV3F/cS9xH3FfcXDxAPFY8WjxNPFN8jnileIF4oXiM=
*/