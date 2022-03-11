
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