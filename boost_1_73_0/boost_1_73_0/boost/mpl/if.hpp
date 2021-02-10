
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
bFWW2ootOA0bAUa4yihcHnKhGvs6OGTCWWCQSmMdoQhWG/knc1KrbhOgkEpAySz6ChDMJR4vpFAOgsBj9lg77Xan4SHs3HXgvt2BuT5AJvd7gScYwhdcqy1i+b3y2egUuGFlizQ8dGEmudFWpy6YTNbhw127RQZaOQwTJMdSdJGEP1yYu33xC/CcGStcT1odfP788CXoXI2nQmUu78LP9y3y+voa+LRwX3LmxCmrpFjNkpd58kzpgPqR4XNYzx4zPaL8oUPfXobZcc7pZTze001Gj366bM/w3JIuDzGeGtFRFn+lowNdL+OEjkZ06ddfl3TtX8YZfTvEv9HBPWVLfD4+019pXNDxG51mcUXHiOJArd/f0Lik4xl9W8bSr7c01v7cv56vR69Xk6AEbwrIC2yBFmldukJpVxfPCFZgUTMBQuLa3GBbXmvY1JPngu/+L+h/u6CnIuLqrC8fYVDf3JPsNNcYZSkVDCVCoEJ5Psl6PSU36/ViQrZiU2Xo4GoQNdrRJ7lzJb45LyFSbC+aloED4rhK4EVVTgLEip1UGZyaqw0/7JQ+KC9WKZPFj+gqbHwBBsMeeO8jcBS+VBtUQF0Z8Oa5xq7zdj95nUR9RUFDF3u2EzUrtWjukQSvYVJtRSnwTzkyeF5Nv6FQ
*/