
#ifndef BOOST_MPL_PAIR_HPP_INCLUDED
#define BOOST_MPL_PAIR_HPP_INCLUDED

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

#include <boost/mpl/aux_/msvc_eti_base.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/eti.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    >
struct pair
{
    typedef pair type;
    typedef T1 first;
    typedef T2 second;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,pair,(T1,T2))
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(P)
    >
struct first
{
#if !defined(BOOST_MPL_CFG_MSVC_70_ETI_BUG)
    typedef typename P::first type;
#else
    typedef typename aux::msvc_eti_base<P>::first type;
#endif
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,first,(P))
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(P)
    >
struct second
{
#if !defined(BOOST_MPL_CFG_MSVC_70_ETI_BUG)
    typedef typename P::second type;
#else
    typedef typename aux::msvc_eti_base<P>::second type;
#endif
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,second,(P))
};


BOOST_MPL_AUX_NA_SPEC_NO_ETI(2, pair)
BOOST_MPL_AUX_NA_SPEC(1, first)
BOOST_MPL_AUX_NA_SPEC(1, second)

}}

#endif // BOOST_MPL_PAIR_HPP_INCLUDED

/* pair.hpp
6OsStrPpy8hW5RZRYvSRz10eSs9SHkr3iDTSg7z6MoLCH17L4orkGY28+D3eLEtglgDEsaEvaG7ooyfeLE3Pe2PxqpHO+pkFPIIt353XCBbryqDFg0DkkxDMi0BJzr9ofiErDxE9owoHH5gFbSTg6zEFmUq7UmC2Om0MWrMw4OW9/1CVqEW5QrlC/Y1f0t7uTRPzJZRkZh7RcB4ZcccJiCq0q3otSRonjp0XUl5I5DDym1fHRShtG2mQgPoCXwfNdhe9g+DLIP31AEMBAfU1IWq/v+d70YkxUQTWMdZsJNOTbRcJNxaJhOG/UuWzdT58SmLdQBfBlLmQJpWhFf/wZ10HHIjvSfgzJ9ohJ9YhJ94hJ9Fhq54Hd662/BPdcd9f37/XkWsN2DeQX4Uh7lBdf0W8CKC8H3KIGJDgR0BGHWJclqDhGRDsQLkKRywkaxugwQxgvAjy4/wku8ufE4B737G6uddpI7rd2jBAdLNybKlA6tOlxmPcn7oQpF0UjxwDlhyJHIa9Xkwj9m0LLT4/3PFeFMZu+8fPCtkI74FCt07Epoi0899dGyR8x68V9wltU7x5eD2aMZV4gRHc/M2s33XXgMd4oFhIVEm6HJkbO41gFs/i+/5IUOvoIVPU59BTo4v8lPQyH0tk7jwUXDxhy1JfvHEBgfTcbkvnj7MmdHUbyAZdhFRGtN8WTvePnY+RCde++/dyuvkyh+8X
*/