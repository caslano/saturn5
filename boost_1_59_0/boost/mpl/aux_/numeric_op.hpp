
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION!

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

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/numeric_cast.hpp>
#   include <boost/mpl/apply_wrap.hpp>
#   include <boost/mpl/if.hpp>
#   include <boost/mpl/tag.hpp>
#   include <boost/mpl/aux_/numeric_cast_utils.hpp>
#   include <boost/mpl/aux_/na.hpp>
#   include <boost/mpl/aux_/na_spec.hpp>
#   include <boost/mpl/aux_/lambda_support.hpp>
#   include <boost/mpl/aux_/msvc_eti_base.hpp>
#   include <boost/mpl/aux_/value_wknd.hpp>
#   include <boost/mpl/aux_/config/eti.hpp>
#   include <boost/mpl/aux_/nttp_decl.hpp>
#endif

#include <boost/mpl/aux_/config/static_constant.hpp>

#if defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    || defined(BOOST_MPL_PREPROCESSING_MODE)

#   include <boost/mpl/limits/arity.hpp>
#   include <boost/mpl/aux_/preprocessor/partial_spec_params.hpp>
#   include <boost/mpl/aux_/preprocessor/def_params_tail.hpp>
#   include <boost/mpl/aux_/preprocessor/repeat.hpp>
#   include <boost/mpl/aux_/preprocessor/ext_params.hpp>
#   include <boost/mpl/aux_/preprocessor/params.hpp>
#   include <boost/mpl/aux_/preprocessor/enum.hpp>
#   include <boost/mpl/aux_/preprocessor/add.hpp>
#   include <boost/mpl/aux_/preprocessor/sub.hpp>
#   include <boost/mpl/aux_/config/ctps.hpp>
#   include <boost/mpl/aux_/config/eti.hpp>
#   include <boost/mpl/aux_/config/msvc.hpp>
#   include <boost/mpl/aux_/config/workaround.hpp>

#   include <boost/preprocessor/dec.hpp>
#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/iterate.hpp>
#   include <boost/preprocessor/cat.hpp>


#if !defined(AUX778076_OP_ARITY)
#   define AUX778076_OP_ARITY BOOST_MPL_LIMIT_METAFUNCTION_ARITY
#endif

#if !defined(AUX778076_OP_IMPL_NAME)
#   define AUX778076_OP_IMPL_NAME BOOST_PP_CAT(AUX778076_OP_PREFIX,_impl)
#endif

#if !defined(AUX778076_OP_TAG_NAME)
#   define AUX778076_OP_TAG_NAME BOOST_PP_CAT(AUX778076_OP_PREFIX,_tag)
#endif

namespace boost { namespace mpl {

template< 
      typename Tag1
    , typename Tag2
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_) = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value 
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_) = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value 
    >
struct AUX778076_OP_IMPL_NAME
    : if_c<
          ( tag1_ > tag2_ )
#else
    >
struct AUX778076_OP_IMPL_NAME
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )
#endif
        , aux::cast2nd_impl< AUX778076_OP_IMPL_NAME<Tag1,Tag1>,Tag1,Tag2 >
        , aux::cast1st_impl< AUX778076_OP_IMPL_NAME<Tag2,Tag2>,Tag1,Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct AUX778076_OP_IMPL_NAME<na,na>
{
    template< typename U1, typename U2 > struct apply 
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value = 0);
    };
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
template< typename Tag > struct AUX778076_OP_IMPL_NAME<na,Tag>
{
    template< typename U1, typename U2 > struct apply 
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value = 0);
    };
};

template< typename Tag > struct AUX778076_OP_IMPL_NAME<Tag,na>
{
    template< typename U1, typename U2 > struct apply 
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value = 0);
    };
};
#else
template<> struct AUX778076_OP_IMPL_NAME<na,integral_c_tag>
{
    template< typename U1, typename U2 > struct apply 
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value = 0);
    };
};

template<> struct AUX778076_OP_IMPL_NAME<integral_c_tag,na>
{
    template< typename U1, typename U2 > struct apply 
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value = 0);
    };
};
#endif


#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
    && BOOST_WORKAROUND(BOOST_MSVC, >= 1300)
template< typename T > struct AUX778076_OP_TAG_NAME
    : tag<T,na>
{
};
#else
template< typename T > struct AUX778076_OP_TAG_NAME
{
    typedef typename T::tag type;
};
#endif


#if AUX778076_OP_ARITY != 2

#   if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

#   define AUX778076_OP_RIGHT_OPERAND(unused, i, N) , BOOST_PP_CAT(N, BOOST_MPL_PP_ADD(i, 2))>
#   define AUX778076_OP_N_CALLS(i, N) \
    BOOST_MPL_PP_REPEAT( BOOST_PP_DEC(i), BOOST_MPL_PP_REPEAT_IDENTITY_FUNC, AUX778076_OP_NAME< ) \
    N1 BOOST_MPL_PP_REPEAT( BOOST_MPL_PP_SUB(i, 1), AUX778076_OP_RIGHT_OPERAND, N ) \
/**/

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    BOOST_MPL_PP_DEF_PARAMS_TAIL(2, typename N, na)
    >
struct AUX778076_OP_NAME
    : AUX778076_OP_N_CALLS(AUX778076_OP_ARITY, N)
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          AUX778076_OP_ARITY
        , AUX778076_OP_NAME
        , ( BOOST_MPL_PP_PARAMS(AUX778076_OP_ARITY, N) )
        )
};

#define BOOST_PP_ITERATION_PARAMS_1 \
    (3,( BOOST_PP_DEC(AUX778076_OP_ARITY), 2, <boost/mpl/aux_/numeric_op.hpp> ))
#include BOOST_PP_ITERATE()

#   undef AUX778076_OP_N_CALLS
#   undef AUX778076_OP_RIGHT_OPERAND

#   else // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

/// forward declaration
template< 
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct BOOST_PP_CAT(AUX778076_OP_NAME,2);

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    BOOST_MPL_PP_DEF_PARAMS_TAIL(2, typename N, na)
    >
struct AUX778076_OP_NAME
#if BOOST_WORKAROUND(BOOST_MSVC, == 1300)
    : aux::msvc_eti_base< typename if_<
#else
    : if_<
#endif
          is_na<N3>
        , BOOST_PP_CAT(AUX778076_OP_NAME,2)<N1,N2>
        , AUX778076_OP_NAME<
              BOOST_PP_CAT(AUX778076_OP_NAME,2)<N1,N2>
            , BOOST_MPL_PP_EXT_PARAMS(3, BOOST_PP_INC(AUX778076_OP_ARITY), N)
            >
        >::type
#if BOOST_WORKAROUND(BOOST_MSVC, == 1300)
    >
#endif
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          AUX778076_OP_ARITY
        , AUX778076_OP_NAME
        , ( BOOST_MPL_PP_PARAMS(AUX778076_OP_ARITY, N) )
        )
};

template< 
      typename N1
    , typename N2
    >
struct BOOST_PP_CAT(AUX778076_OP_NAME,2)

#endif

#else // AUX778076_OP_ARITY == 2

template< 
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct AUX778076_OP_NAME

#endif

#if !defined(BOOST_MPL_CFG_MSVC_ETI_BUG)
    : AUX778076_OP_IMPL_NAME<
          typename AUX778076_OP_TAG_NAME<N1>::type
        , typename AUX778076_OP_TAG_NAME<N2>::type
        >::template apply<N1,N2>::type
#else
    : aux::msvc_eti_base< typename apply_wrap2<
          AUX778076_OP_IMPL_NAME<
              typename AUX778076_OP_TAG_NAME<N1>::type
            , typename AUX778076_OP_TAG_NAME<N2>::type
            >
        , N1
        , N2
        >::type >::type
#endif
{
#if AUX778076_OP_ARITY != 2

#   if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          AUX778076_OP_ARITY
        , AUX778076_OP_NAME
        , ( BOOST_MPL_PP_PARTIAL_SPEC_PARAMS(2, N, na) )
        )
#   else
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, BOOST_PP_CAT(AUX778076_OP_NAME,2), (N1, N2))
#   endif

#else
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, AUX778076_OP_NAME, (N1, N2))
#endif
};

BOOST_MPL_AUX_NA_SPEC2(2, AUX778076_OP_ARITY, AUX778076_OP_NAME)

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS

///// iteration, depth == 1

// For gcc 4.4 compatability, we must include the
// BOOST_PP_ITERATION_DEPTH test inside an #else clause.
#else // BOOST_PP_IS_ITERATING
#if BOOST_PP_ITERATION_DEPTH() == 1

#   define i_ BOOST_PP_FRAME_ITERATION(1)

template<
      BOOST_MPL_PP_PARAMS(i_, typename N)
    >
struct AUX778076_OP_NAME<BOOST_MPL_PP_PARTIAL_SPEC_PARAMS(i_, N, na)>
#if i_ != 2
    : AUX778076_OP_N_CALLS(i_, N)
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          AUX778076_OP_ARITY
        , AUX778076_OP_NAME
        , ( BOOST_MPL_PP_PARTIAL_SPEC_PARAMS(i_, N, na) )
        )
};
#endif

#   undef i_

#endif // BOOST_PP_ITERATION_DEPTH()
#endif // BOOST_PP_IS_ITERATING

/* numeric_op.hpp
3KM62FSWLSL40Lwigjg/OLbew8Vr8uVmQA6jVTVA/BmuhrG57X5CxL3RAkztexq7FNQiWLNZqZ3xczKfX6CO4tQgo7XuglFZDtpQsflYtdWSRwmN9WjJbtSSqhlMul8ZI0M4W4a2v3bzKSyDth+R/iAx43SzG46Htc9rNwZRncQpj/SL5mP+FrQHXfl8anrVQA4wBAoPuRnJ4vuS+c+rsSVTOrmas3v5ZcBmttjpH52pcX99QublZ4eVNZGeYp0vWVe+uLgReUp5V+rRxlmnmRQurKQCoEPZ0DVK9QIXbOnRRFHocQWbphUJbE2yWToGTkHO/B3sZyISMaawrM+CoulFp+LzHbv6vIRXv72Rtd3fBV9O/boQaoMdcbguAhfGZccIbB9SUr3me4p4gnOrZp0Cf9kxzfsrPOgdX1oOjTvirIVtBedl4mOxQERs8gRVwDzfhWS5ndDZmQFPYmkpB/uRu/qDWzTrtA8VhAZjnoTwpe2myMBwNvWI7U4c/+/fR9lGW5qg90DbkvZ62IQvFIgWoW7IATV+DgAFkKUqpsOZNZR9PlDjLcipCmclbr3n5NTSBK1j0VLyuT4bzEy3iXvweEN/tiXexGzQIV/cD2UcGK1bRk4Gi9JcdCH7p2LvMVl2DgFeWaiNktY4o3MZSEa64awEBwNdQvfD8RlLgKsrmM05Dy1Uyq+K6snKHFRQPUy4tIv3k8xzW2yYBalbWULOEePjqd90iYZtpF0cawSGap0qrSYqPszDPRZx+D5jOuGxQTtdrvpcmFsw1F5jYdiGETyANyP8MK9Dfvmj5GhKwu9lzjGlGrTA3f0TPZKnssOEgzdFBPNgMEKr1EaslNArxC62+fmnmgp5yZxKZxCKS4YET1dFTKsH4nfMpd3cFd4zBK+Wl7wG0tlwkUtf1Il5c1+QfkP6jFakBrsNs3/MdDdzPuZJDGnEKChs5DOrr62C0w6ex3sNYsIZURTCUfqXPPocGOTvckoD1OfGAHWnsZeWTdR8TZL5Ci63anLBQ+sIV1jcBHTTb7gi/3j+2OVSnbX8pxQn8+1sovnCxsXJI1tvHHcLsiLwIvC8QNG/kDjpemKox9ZEVcPIHdKKQn8JadSd9DJnaZFfoSNhTnOnpZelwi6ehy5Qs9tiQ33uVcLAzhPVhG68fxIBNESndSUYeVyeKu+j0P0bvCldDWdv0sY3wa+/z+Vy/2nE4UkGxqX2Hh4g0/QxVPKXmnk8Gkm27yvrEKJbpEl9sE0vM6BHM5o7TX6SXTP/k84f6KLHeJKmpMohzus7DBmS1rhYcNC8xnoRCoqnjC+hb0QPDbsE01VBE8iZIZoFi4hpMyBOJjZQSG1wXY58+u/CAz1S6papG3S2wqAi3+aOzAef3Vkp8DglZsDfiG6UTH7oDRV8HxNPRqiS9Pmas0BGAG0fMY8uSniVEiYfASrER0oUwIiyUm4/Ne6RYmI14OsdRN076Ga6V9maoGOLb7Wfuyceza+e2CteFheSeBXzP3uTLNMUYXnPxTVilSeHybJ5MK1EUnmn0KwQ6h3EhGHYUQzuJ32u0I9qBbdOk4FlLkqXHN91UnthALF3PFGbQ2BwBTtKAmz2fqD4lQ/5Lgk/pxFMivcEEouc/4yaRKpSiSsxchxrQ+xoo+2BNVJ8GXuO/RLYH0ESqciPR9uf7fWd21BeEmrTp6hYYG0Ir9wsGADrR0kCaP6ZXZc4nzy0BcOWH0fAssOMxLD3ceA9WSIsQ8SgZgNawsKQWg0oCbIBoFB69Km2YdSESoCoON7Ye/JPl7U1qvoZC1auPMjKd2HHUjUEdyiX6lMWnYeCBywR0Kr7eFp5kat/osTveGs2Xc62jZQkqE9EzEpN0c69N0DDkcjlkhlpaMMZL9J3CHnyXX9lZ6T8N0qHAAAs/9MujqO7U5TBSFdzBHxCe5kb+R0YFQZ4bTcU8eiSNuoYBt1TM8uWRLWsrzHaY+itZMbj49vBiDqW4YZoLXcfnBBr/6N0N3Fs2TFi9rzFUEGwiElBUYz9EiSeePNJvpIpbcBd51AEbqAWLOBJcSsYrYJc09xnw45sI2ghGW+z1M5hRLeGdEzDG1Km/8DtIQk8mF+a8qM2QV4nuKqYqV2toLti+9skMts5a5pzGoRvGpkq8Jo3YoV/GcE0eUFEOpJQ829J++vZ4jx3aJ+1DfffnRRSrMsDyrLDmVXL6qSoDR13Z6hdMxTJgnCEQX3zbaHHPeyJO9K8aRy44tzt8yOWQzJjD1dSKa3dJDXeXDihcD80UUzE7E6q3DJmD4214nBlpFeukYjzLO9SKzBU+AQBhHng/O2jU2EOq3bAt4AqaAJ89M55Q29OQG4vuWDg867TVy26JY28iEX8IBq5GD3CUYdSw9oy8lRoRVBEN57UjQP5skeOs9SckxuuDlWDJCe3rdf23pQmr0Rwq6DnWYWKrHvb2tOOvtEnj3na79H6SFAeG7U2RPD3oaXFh2xxLc6WosgypkV95JREA3evtTmn26SgqAtN4uFDGs5y0A2vrXYmCq9SYaaPPt8dGlx29Lyh996QTaX7aml64Bas3zzppWhAs5YwN2aOMCevx0MDeA9pHYc9/tKyia/Z9QSp28cR1g2ipCuIkbV4FZAWnoSejXpGAbCUuTM1Zxk3EMYRJVyRQ+pogP/uONQDK/Q2VqAB/+NQ1lVohzDfjjR9PGlMuVUNDMIdFcQ+cd5thQrlGs6gXflFQTfySMuASk38sdBxYn2joNOVxBEt2fpkp4ejpxLc+rGHpspO+VvVfkLZZKaaXrf5+E3VaVzcBzlzL5U+3qmX3PwUsU/BLKnsag93tfcBEmJcvg7qHK10nRn5NuL2lbrjmpcrM69i+aoTRk4GZqPSa6gDLLeFMzK9+WzUf3NTT1+PMSjKgLVqWJip1WEsJDmaTUpMwDAU5z6XlHFyfvig1V/hY/wDNqOWnJexa4YCpjOTsIX7s8UV07WNHvaRTx8e2snZCJKc7Msrbhv3AuN4VRwKCsOp9OFUMrwmNAcepSvpXQ7ihlMTMZ9M6EVnUlYXmLQHq0/Mt4wON0p46GMLHZ/zrIwPjssy9v+uepYYAekPmxCAw9el1agsWUTR1ZIj/bxXY30aM8Xab+4JWTXFBJqg9qItjTmf5vNk9KbKombra1OACGonl7jYOKC4MJd1QTqlj45p6SO4ctx2AfNxl/oD7r6bnssaSQtTrWSLwmS60yNIXRxccv1OVmOHDKuA24wK+k7LRKshQb9gfit4D9EAB+DJZt7+GnrvG6eqQZ8exKrGNvmqNS6h2GOyEKVMNOaKc+nTZSPju2h74LlmIX9qssSw2lSNJdOvMY2IKqitl3N9LyVKOKLl6cl9dOc8GqHxNidRrprO9GAeFmuvc0EFEr6NxGj3v5FN5SRCsgv32+Nqoq70+1mVBbOHyxh+elFpzP/qSa3fSB93m8MQrt10s7S77e9PB+MTJ3Q6v6as5GnJ9KiFZ/WLiiGBNFZodAKkuuwe9jbnEccwZmwR1sV888KuQ1PJzZLvJoukCZVp8ubfbMAHSamHFcInMJWSMECz7DUnwQu7WQB1wGfKPmsFwIGRA+w7NO419aI9LuRgy0K6mE4NEKXwTIxh+FI3vDAtsmKw23kwP7wjkkPvddDPcVcbWtPvvBM1nZSBXBpBvjkP2lVzxfaQd78Fbb+cQeKtcdymyYpoEtW3bX8yh1EX5k+zcFbaGruGl7+eW2VjU419HWpZ05TCaal07S5iJ4rcTpkojb4ZqkJJNFp3iUMh3U4fBmvhKX+5IKqvMYc2fpMzk4rEj731P2CqZmc/Pqr+P9/PvggmqYCCiUo++5HBSAZ/qeau9n/jM6J880XZ/cOeUt0Rl3mAgfz4fQZjsLT/IXCvsEuACFoK282VlK0C6z6jalUlraW6Jy3bxucXo5CWysJHFlAZ9hbM9FNNR83y8xm5kh0qXEryih4VEEc8nIlrGJS/jO4RAx4Aizbn4mJAeStH9xvszp+vzM+a7LzsNX5Zc5O2a91WMzle4fbVxdXdrgCfVaJiK9GRpouEaPRHEn8iwiM6Q08IQv6JOH6pck1ptoVujBn+9I1OcR/NTYutIINrKKwdHM6j3JVrb5k3221RlVYeD+egH4zGnHzM0+svfAi6N633lj/GOmhfaZiitrqg1Jn9bEIgFSxXtowi+gntxLXmm/cOjhAjYoNumP6pCwNarYrd4dcSTtMjveaLyK0fIhM/7eRT/48CKaWXNCZw5aD43842buPBRvsTiVQ4lAGKP/P9FzZinEj7kRZD0GRLwGSA3yw/KTt6RUnxVcM24wWqbA0gy0f3aClPFN1PJ3oCFhzFg+wk+1Vg9V2HxWc45X9GHzD8d1wuruOrJ/QPpufd7pev61dManFrBXB+VLYG/eidNeA3GgslC18SKFHX/EJ1eQ147Fj9KGMc+Rjd6Lnyg9/YdcImydvxhB5wETmrN25FEqQMuJ/4AS6xnm7ANtfd7JIH9TyqR25dGyEesMnp7jskdf8NvaB/lns7YjVYfcf6LIr3F3RbymdkSR6ivzyjLbT9/genoxXJz24lsh6vHGMFXbcUqFjzzcEJp52XTq4jPbZNdIoeCzIdxl6ddr7mSpTnnjZ5hBHfm2UGgwPBGD1bdX9GlNjjzYjD4446c82rT6bN9+2bmlZzI90mlValoWDX70A3H6ARV4wKOSbynmLFLjuCLr/UnJ2V0AxQDIm5U/HBmFN1D0PPKGECf6nEDer8KndjxHSlIb8MUVspOZ9IOMDU5xhCXqHkk7nK7Mj9IJM+NLFYpDRdT8fl0UNhF7dSJyFIJQQ55771zmDGx4KnR/hProiRZuGpk4Iu3ReU0tR07LWL0FeFFcDU+BNj352azxFh9EJBon7zkknajaf9qxg1pDpQ4D+DbvRtjeJXcCh5M2nLKtMt4tmeneu2sANim4AFkGRIaOT3fBpTjCWf+4OUGvmIZ/9DU/4XRdLEM68bWH1KBMF0mwuzTXtQzdJQWdiF0u6C/ngxrzLslbMzYIQPSBHh/BDdCXM0e/iSxKeL/JeybA+Ft4MJNKBUDDstWMqR0xtvsUtarw4Rpp3YJtN65OC0GB084/lAzj1iFIDHvb1HqizOEf1Eg+qZvH8GxFN34qSCI6KOTSm2JLSRY7QNpbxXXto/7i8oEhrgm1mdgSdsgeWxFch9ayLfsTEWm91vTVa+rb57Q/4CSmo8693/HORUWJa22pmn8S3O3ebY1cvkeZ270QGCpgpJph0vObu5g5VtO1iSNgTTwP87iDR/M+guPkmONsK5ZY9tOgQf64bptXb/bz/EwXs7xlOFEFIc0/FFtANb8TXZX8P8FqNAHXuL8WNgU61VD20dCGW6c+yuFgJX+i7Itw232rTOPWzewD0h3U9bk/ghddrA5rDui6BNLRa/lmB6a8CJLpataGxXeo/aGKjBfeVaLhbg88rKfbGmGesOrgLSfr9NL0lW5+eKBM7hmeljvPFhFnDktAouTmlwiyF9tOUuUtnX6/SCX7ofT+JcKh7mBUi4v6gwNiX7OQhZXmY3AjKIEDA7Ce/bp7lsUIHAtyZWn4ivPBv8nUC2Rm7nxn48vzOcPba2OL39g9wTwmXogLCHWt7SAFZ9j0gmhnzNFHAeyxCQzW0JNHBQTFR+8t9xBT7K9yNlUHOVEfGi6oaKMPoKW1+3hW2ermfhsy6nLteRxywT8pc6rnzX7wIyVFIKTkNFtnrjgpVWllecbgpojJyX6UQLmlLYda/XYHIK0Iqb+z2OfMNLQXMrQjEBS/ZKHu+97mMeYPHbp+Y/CG6MnmGBIfdVWYv5dIH6vaJQ+j1TQrtEVMqnISsF3rL9S17jh2PYJOhxE8VaFreJgIkpZxjCMFMFQfbP/eDAT3CMvMNYv54mGDsgAdNCEiETdRu380ZSrkm3Rp93Sz1HJGtX7uITMHbXYk61rwI6fKYWXOTf/F4vlkns5RFwpX21B7q2FZ4GMTjlOAsynjcL0IUfQw1DD9x1C3TFYpZubVPnyDS24gyzZX0Ejl9V27cR5FHWpLresbUE/WOWpngd3Y8AY0PpSazDiTiYW5KfCPY7DPNfEe9f5i78a24ZqpDMCcVUVFqNPoc1zc9Ynpbihp7REpXu/Bwvz0E3eP2hcq/Y052lcMBNzOVXZ+GKovKnAiHlh8Mh7bRmScl3akqe17S3aZHrI5+ePY/dl9GTU7jlr0pmCTo69U26+otXJO9ZkMm4OOdVP1drvHrxRKJTPhAv2hdAaqPYVtLiCEtbLieMjRhFGgKDIzu3OIrISVYL8qHrounIC0ZLRZS3gDZrXq0Ohb7AWLDDK6MOLjARBo+1Sa5L0Qvhyw/cSoJ1JsZidA0O3bV74EHKZ2bqRhg6HLIJ6w8ic2bTrkln2TPHuX/fbMN70tCPRlDXT6cbI1O/l5xdjUp+hWfB9UnHRFtyD9cjdmOnLpyuGJvOpbNyBflqS0IGTMJsNm/QB0nj5bSAnx7U1zHHyK28l7zk54jk2zPBVIcZ/QbiRC6GALstB4XZnQZCvi3XK4/SGNTAUxiBE3zpwI3X7JL+v457TQaOb14hJa75elGNpEj3Rx1HuJpzWXeU3xLBHEbETwVT04tjKdXmUd6rL9bNQrTDcuFuy77DyNb30nH81+yTmH1hY5uFFR0uNdugjFVt3wfo0IZ3df9xNpZWwDDiyEUm9GF7TpxhMzVMewq7Pw68W99YpUYzjqfvBxxZu7bbfaGfLO7ZR+SvY2z3u0oYGsZNclcae1Q6gyE5Iuvrty2mHIRFGzTiKFGa8TKxsSiRi7z/UkPi9ULGgjrO7ndMYnbvrgFvkh/XU8wGKsNRx2XeUGkIdbBhaz97pJbAeDJ1k2OxcPlTDuT9Y0zLnIQDGF6PdfzPGYJiSWGIwSetktYGrnJePB5l7TWmsVe9UrMSf7kPCx5b+JYiaD+rRkbssvMlvETJkQ2HxRthltu8O8SaIxXam5uAP9YXf73aY2pkUXrKDLpyMB3J8jajV0BJKYOnw2mZhHiCDBRy5Ft7k5MTG3nXPc81CadJe5xod/+At/F0i5Sq/u3NVc9qK6xOjEBPXJIP9ULwJGwAFk9LOSq1+CeXddYocngkh0v2YP1yvXX9lki7dbde0iTuI2Zo7IfJMzgiRZ1kBXHWZ8QUO0m+AUHbMnxsgv1nYVdszlLlLSEqoQm7CZrUze+/s8MA5xbrE3yentXuOGFc7kXbqRw2KuvMqAa7neXnsRjdpkmXLu6BPPcZUXKRNd1QM2jKeqglZ//6IfvmT7wEpEfh0BNrBk+IdzchQ/w4F2IASuRV8i8hYcKSBflNrLSxX6LX+lvSQZiQyqUCDn5yGbyTbToDUZWd1+JyssYnMZ7wjiuAYrQo6H/GDpC90FtlqENTyV2WkAOTPRcS/yBMeYjahVVGsN9jj89jeNUe7xIelBqVdcJEph3yWRD8ieIkVWZwY6jL7X5mBll8axjJT1jgBR+Au0WEnhuNiNHzyI0GHzNXOzUVxD9OhXKhQOyRhy8Fzld4f4+zB860ffOFKp5JUyzqotPBOB6ydTLWjcVqWeHrRz8WT5Yt3G6va8TTcMpB1TXd+nUZNI+4C07Z+ufNCGthyo4W
*/