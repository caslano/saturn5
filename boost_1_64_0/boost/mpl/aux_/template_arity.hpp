
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

#ifndef BOOST_MPL_AUX_TEMPLATE_ARITY_HPP_INCLUDED
#define BOOST_MPL_AUX_TEMPLATE_ARITY_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/ttp.hpp>
#include <boost/mpl/aux_/config/lambda.hpp>

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/aux_/template_arity_fwd.hpp>
#   include <boost/mpl/int.hpp>
#   if !defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)
#   if defined(BOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING)
#       include <boost/mpl/aux_/type_wrapper.hpp>
#   endif
#   else
#       include <boost/mpl/aux_/has_rebind.hpp>
#   endif
#endif

#include <boost/mpl/aux_/config/static_constant.hpp>
#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER template_arity.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   if !defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)
#   if defined(BOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING)

#   include <boost/mpl/limits/arity.hpp>
#   include <boost/mpl/aux_/preprocessor/range.hpp>
#   include <boost/mpl/aux_/preprocessor/repeat.hpp>
#   include <boost/mpl/aux_/preprocessor/params.hpp>
#   include <boost/mpl/aux_/nttp_decl.hpp>

#   include <boost/preprocessor/seq/fold_left.hpp>
#   include <boost/preprocessor/comma_if.hpp>
#   include <boost/preprocessor/iterate.hpp>
#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>

#   define AUX778076_ARITY BOOST_PP_INC(BOOST_MPL_LIMIT_METAFUNCTION_ARITY)

namespace boost { namespace mpl { namespace aux {

template< BOOST_MPL_AUX_NTTP_DECL(int, N) > struct arity_tag
{
    typedef char (&type)[N + 1];
};

#   define AUX778076_MAX_ARITY_OP(unused, state, i_) \
    ( BOOST_PP_CAT(C,i_) > 0 ? BOOST_PP_CAT(C,i_) : state ) \
/**/

template<
      BOOST_MPL_PP_PARAMS(AUX778076_ARITY, BOOST_MPL_AUX_NTTP_DECL(int, C))
    >
struct max_arity
{
    BOOST_STATIC_CONSTANT(int, value = 
          BOOST_PP_SEQ_FOLD_LEFT(
              AUX778076_MAX_ARITY_OP
            , -1
            , BOOST_MPL_PP_RANGE(1, AUX778076_ARITY)
            )
        );
};

#   undef AUX778076_MAX_ARITY_OP

arity_tag<0>::type arity_helper(...);

#   define BOOST_PP_ITERATION_LIMITS (1, AUX778076_ARITY)
#   define BOOST_PP_FILENAME_1 <boost/mpl/aux_/template_arity.hpp>
#   include BOOST_PP_ITERATE()

template< typename F, BOOST_MPL_AUX_NTTP_DECL(int, N) >
struct template_arity_impl
{
    BOOST_STATIC_CONSTANT(int, value = 
          sizeof(::boost::mpl::aux::arity_helper(type_wrapper<F>(),arity_tag<N>())) - 1
        );
};

#   define AUX778076_TEMPLATE_ARITY_IMPL_INVOCATION(unused, i_, F) \
    BOOST_PP_COMMA_IF(i_) template_arity_impl<F,BOOST_PP_INC(i_)>::value \
/**/

template< typename F >
struct template_arity
{
    BOOST_STATIC_CONSTANT(int, value = (
          max_arity< BOOST_MPL_PP_REPEAT(
              AUX778076_ARITY
            , AUX778076_TEMPLATE_ARITY_IMPL_INVOCATION
            , F
            ) >::value
        ));
        
    typedef mpl::int_<value> type;
};

#   undef AUX778076_TEMPLATE_ARITY_IMPL_INVOCATION

#   undef AUX778076_ARITY

}}}

#   endif // BOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING
#   else // BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT

#   include <boost/mpl/aux_/config/eti.hpp>

namespace boost { namespace mpl { namespace aux {

template< bool >
struct template_arity_impl
{
    template< typename F > struct result_
        : mpl::int_<-1>
    {
    };
};

template<>
struct template_arity_impl<true>
{
    template< typename F > struct result_
        : F::arity
    {
    };
};

template< typename F >
struct template_arity
    : template_arity_impl< ::boost::mpl::aux::has_rebind<F>::value >
        ::template result_<F>
{
};

#if defined(BOOST_MPL_CFG_MSVC_ETI_BUG)
template<>
struct template_arity<int>
    : mpl::int_<-1>
{
};
#endif

}}}

#   endif // BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_AUX_TEMPLATE_ARITY_HPP_INCLUDED

///// iteration

#else
#define i_ BOOST_PP_FRAME_ITERATION(1)

template<
      template< BOOST_MPL_PP_PARAMS(i_, typename P) > class F
    , BOOST_MPL_PP_PARAMS(i_, typename T)
    >
typename arity_tag<i_>::type
arity_helper(type_wrapper< F<BOOST_MPL_PP_PARAMS(i_, T)> >, arity_tag<i_>);

#undef i_
#endif // BOOST_PP_IS_ITERATING

/* template_arity.hpp
ZvzZ0+Qhp5HvnYt63XLhcdmBRUZ3OdTHk9InGvqO7WmvvI/27/Ngp2Enjk59j6Pdngr1SE/47EuX2wtmQOeoElZvzUXZxRix/K4TTc0/oUXiEkZlxWF+3ysM36otStyuQyTOZMfQZNzOapQu07by7+86vnXazMzgu3xx6BQ6+h6Ru4QvZh9pyhlPBjBcLJQr10zlkw2eYnH7IbilskiMG+rCZRub/DL5E+au3yeWHr+IM1O/ipzdKTwxwgOfzhux5p8yY1dK6lTvkEb6Cfju3kduvhKDFfkjud75GHulSHinmvCqWzeO2dGIwBEbRczBVJ5r+4t/Zx7BjCxlmZJjR+1++mLp40SoX+uLzef24dHT5jj+rhAThy7hAr1MTrtcxrM9GmFzbDbXaJ/DDOunYsbM3XznXiTOONzjT+dfIsXXiwkZ17H5wlrYSycG10xi7597uTN2MdNdO8jiPG+El62lsVIdEnYdQOD0HCp7vaLjS8G/fwdLr5g1XG2wQeTZP+H++8XUmNVA5Z/BYuqck6zVq4CZawpXTdoip0Ub8Mh/M2FwRpcqF2fy8GJNeNzy4pjXUchNEbJ1rAPiRQ8GRn9gz6gSsbh6HkqEF+9nCzg32yO0hg3Cl3dHeKrxGTOsFbFgci1enYhgjaYvy1Y5yJv3FLBUW525x325YI6beDNiMd3vhctSczd87momjEK6YZGCo0x68QUfPm6Dh3kQ9JOq0O/GGEw50WTNC1xp8iJJJH36S80VnTlvpi40cuyF47+DuG8yHntaW2O60hnx995UdF4+g0HiNtpstBD2yqH8V3pdtJ+YilknZssRboOop35VajxsD7UPhfL3mDtwm3AZUfe0GVnnT52hU5g7a5McZPkHpuF1MkzXjHO6G6PPTHWmD+0gr423Q5uYdOEa7IcjK1bAL2oSc0btknrt2jHqZjNpO3Eg9I9lyEHeLRH2PEJonPXA2O724qvhIaZv/CMf3brBhHnbpXH/ahSKPJl0WhO76/SElqEX29fe5vuj63j2zH053nQi+peZID92BC+5OqH9irbo2Xoqt2yop17tYoy70J5KBT2hkO6P7x9fioB7DmxWeF9c3WRLZ/f8pv2oh6m31IWLxnfGx2ZCa9Uu3LdqQW2TcBxsUyc2zPrIPyFFIiNtJeaWTOG432EwXGGIeZ2n44fWanli4Qx2vdVSbLDQwr8xPaXl11M8rvpcjjqzC8M3NIeN9yd4HeuPvXataKlRxeKTuzjN+RoRfp3hE67IpdYb+OnwJxFi/4357b6KaC8tnl/4EudPdMD15YpCdVRAU/Y8z/iAAO67aisn1Hiyq3cbvn85lImGn7nKxpO91FbzUo0b3tvv5cTi31x00kUERUSgamtb8T5PE/mrNcSi1p/h7bBX7GtQRs2RFLnQ2w+3dx+S/U3smvxSHwONp/LIjSg4FszD6XYqosXEd8yTEZh++TEWKq6Tvu7J/PsA8tjjYTCZ2CBMmrxIafQy6ehuxLcXfoud3IKKUFV8MukCP/GdT09G0s1NUWa0v8HTi71EartGnnNoJbuZjaVSn2b8vcAMGj3DxNlwJbj4PxZXHdSR4Szl6uG5UDccj7XGLbHHKgzl7xrocbNUnB77CrGXtbh30XYebtMFgXqu+OL0Vpp4H+P4NXXiUMNwBvVTFd+n/4D9uE7CuXwSp1lZ8vb7SliE2fN0dBd6r3klX+i04eYrW+FclImFgx2RJ8+wtMNzeXqsJ9+X21Dn9VOceH9A9rreAcfS2wiluc4sSXXAiScfeG+bETa5vOauq5Vy58qN9En+Kg1KOtKsYzLLva6i49ve8o5KKt7LbSKk3xIcsH7Ewqp3GF60RVY=
*/