
#ifndef BOOST_MPL_IF_HPP_INCLUDED
#define BOOST_MPL_IF_HPP_INCLUDED

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

#include <boost/mpl/aux_/value_wknd.hpp>
#include <boost/mpl/aux_/static_cast.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/integral.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

namespace boost { namespace mpl {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template<
      bool C
    , typename T1
    , typename T2
    >
struct if_c
{
    typedef T1 type;
};

template<
      typename T1
    , typename T2
    >
struct if_c<false,T1,T2>
{
    typedef T2 type;
};

// agurt, 05/sep/04: nondescriptive parameter names for the sake of DigitalMars
// (and possibly MWCW < 8.0); see https://lists.boost.org/Archives/boost/2004/09/71383.php
template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename BOOST_MPL_AUX_NA_PARAM(T3)
    >
struct if_
{
 private:
    // agurt, 02/jan/03: two-step 'type' definition for the sake of aCC 
    typedef if_c<
#if defined(BOOST_MPL_CFG_BCC_INTEGRAL_CONSTANTS)
          BOOST_MPL_AUX_VALUE_WKND(T1)::value
#else
          BOOST_MPL_AUX_STATIC_CAST(bool, BOOST_MPL_AUX_VALUE_WKND(T1)::value)
#endif
        , T2
        , T3
        > almost_type_;
 
 public:
    typedef typename almost_type_::type type;
    
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,if_,(T1,T2,T3))
};

#else

// no partial class template specialization

namespace aux {

template< bool C >
struct if_impl
{
    template< typename T1, typename T2 > struct result_
    {
        typedef T1 type;
    };
};

template<>
struct if_impl<false>
{
    template< typename T1, typename T2 > struct result_
    { 
        typedef T2 type;
    };
};

} // namespace aux

template<
      bool C_
    , typename T1
    , typename T2
    >
struct if_c
{
    typedef typename aux::if_impl< C_ >
        ::template result_<T1,T2>::type type;
};

// (almost) copy & paste in order to save one more 
// recursively nested template instantiation to user
template<
      typename BOOST_MPL_AUX_NA_PARAM(C_)
    , typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    >
struct if_
{
    enum { msvc_wknd_ = BOOST_MPL_AUX_MSVC_VALUE_WKND(C_)::value };

    typedef typename aux::if_impl< BOOST_MPL_AUX_STATIC_CAST(bool, msvc_wknd_) >
        ::template result_<T1,T2>::type type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,if_,(C_,T1,T2))
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

BOOST_MPL_AUX_NA_SPEC(3, if_)

}}

#endif // BOOST_MPL_IF_HPP_INCLUDED

/* if.hpp
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
*/