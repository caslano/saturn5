
#ifndef BOOST_MPL_EVAL_IF_HPP_INCLUDED
#define BOOST_MPL_EVAL_IF_HPP_INCLUDED

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

#include <boost/mpl/if.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/gcc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(C)
    , typename BOOST_MPL_AUX_NA_PARAM(F1)
    , typename BOOST_MPL_AUX_NA_PARAM(F2)
    >
struct eval_if
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300) \
     || ( BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, >= 0x0300) \
        && BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, BOOST_TESTED_AT(0x0304)) \
        )
{
    typedef typename if_<C,F1,F2>::type f_;
    typedef typename f_::type type;
#else
    : if_<C,F1,F2>::type
{
#endif
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,eval_if,(C,F1,F2))
};

// (almost) copy & paste in order to save one more
// recursively nested template instantiation to user
template<
      bool C
    , typename F1
    , typename F2
    >
struct eval_if_c
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300) \
     || ( BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, >= 0x0300) \
        && BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, BOOST_TESTED_AT(0x0304)) \
        )
{
    typedef typename if_c<C,F1,F2>::type f_;
    typedef typename f_::type type;
#else
    : if_c<C,F1,F2>::type
{
#endif
};

BOOST_MPL_AUX_NA_SPEC(3, eval_if)

}}

#endif // BOOST_MPL_EVAL_IF_HPP_INCLUDED

/* eval_if.hpp
aOCHcd2KMlXr10l9oHI4DSTx7tvt8nq6TA8IKMLRSXNvPzhcXi879/3b8nFkN7Zbnf8upSHJvuAEzM2y8yanPwNSzS/WvpBfPaZ1UKXGTqCEVgGWUmWVZOTx9KuQ09hCTkEzmoXGlThHG8jA40ryPxzzy8DrgdBIBst+bwfhJFhx1VTteO2fBVbOlyjU03VRb3jMxdWGZF8PuFo//PGd2RQetQ8PDaVcYPPPaMadUbfJ46GM242mgHoBhrjiFzrtaStggEIL9UOF4XnvLo8wUFa4FjYdZf1b0NX4jCBiph1l7kHyhf93R4+BA75zdH0xRzrHYLkY8SvDi9HzL7DkbnsCPPOT+KIqXrPoNRMNC90u7JF3SyuRWOPaf8PDf8K7lZMiP+4wFMY2xsLcj59DxD14vI21hH77o8eP7bnz0kr4sntVNNYYpveyruSC8QxGE/gaVB1QFSC7vwu777m0emq5LDtzBQUbm0c9FSyuufHi5JqVPcuS91/3iDtzQXydGr/kKorc2tA6ljgWEKmRfUIDoAFQSN/Qf1Im0ESqeiuCVYVCMtOJDsCuNAgBsRNe+wO/Kj6EXpRJzSvLHZPLHNO4qdIsReTIT4MxPTLtbLEFSAdc8cifjrQmQfa7ntfhGe9N8Jd+e7qizPUx9zFkCbuvMFXZojiWUkD/RlHwkReMHzVD4JGkAuaGsupZaESNyH9kQDVT/0IjX2Wo
*/