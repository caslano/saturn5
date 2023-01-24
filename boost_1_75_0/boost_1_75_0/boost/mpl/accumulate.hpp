
#ifndef BOOST_MPL_ACCUMULATE_HPP_INCLUDED
#define BOOST_MPL_ACCUMULATE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
// Copyright David Abrahams 2001-2002
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/fold.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(State)
    , typename BOOST_MPL_AUX_NA_PARAM(ForwardOp)
    >
struct accumulate
    : fold<Sequence,State,ForwardOp>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,accumulate,(Sequence,State,ForwardOp))
};

BOOST_MPL_AUX_NA_SPEC(3, accumulate)

}}

#endif // BOOST_MPL_ACCUMULATE_HPP_INCLUDED

/* accumulate.hpp
z7QQZj0asxKTp+/x8il+Shlj6Rp3yI8oZ9InlaqsHlkZKu/bwQdVV4vrbTaTOzFvglCHR4PHRLfNfOqKD/g0ah9hVZ1IU0aPuoog2ye0gt9mxpsDTQvnqYwaDCP8hRCkx7V3c+iZx2sDnzTeBLWpsAIzPz+GNLcCBNEY5km1ra2Lc0sTpBzxNsm8YuntNfJK3IMdEj7GYyJGgOnDEX21xm1b3mMlsJm9kptv9Puul8HGNQGKQm0Hr+Nna9nmG0F5R/TDp13+9xM5ZNF0ydeLioPdQcCs0wVKL9zzaXeaOefv35JOoklyhEklxNrEUMb3ftO8LI1cljHkH++6Vwp081btALG0Qu5eToFaIcDfSiF7IbTPKQy9ixqHqhbpddIR75SvMGpxgfVbXC/C28VEDnHuvA/tdpshKyekDL0GYQTri+eYL2bXwCenBmnTB9Or89K5Hx+mfmJEyERPB+c/yAaBddKMxXwiQ8bL9b4UERbIdx1qLQ59DS4T86vtNIyi70oLrFkNTDs7elmfXt0WR3ddt4/me+eHdj4dzGBr1EbG8GkjvMrxYVM8l8b26/L+Exi0Celbvf37TB5iS7TZEhum/nVFO+556nCVyBf2qk4+cQ4FbPyEVI5cmxN04cPULELWRkGb2tBFl2fpMM/JX9fi+CEMae8vxf4Qh4uEwMVKnLBhHMlCj4xwoCT4cDLAK3OXyPsVTqd8IjKo
*/