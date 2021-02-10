
#ifndef BOOST_MPL_INSERT_RANGE_HPP_INCLUDED
#define BOOST_MPL_INSERT_RANGE_HPP_INCLUDED

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

#include <boost/mpl/insert_range_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/insert_range_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Pos)
    , typename BOOST_MPL_AUX_NA_PARAM(Range)
    >
struct insert_range
    : insert_range_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,Pos,Range >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,insert_range,(Sequence,Pos,Range))
};

BOOST_MPL_AUX_NA_SPEC(3, insert_range)

}}

#endif // BOOST_MPL_INSERT_RANGE_HPP_INCLUDED

/* insert_range.hpp
AQAAywQAAB0ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNlVUBQABtkgkYN1UTW/iMBC9W8p/GHXFpdpggqqVsFy0tNuWqrsFlcCBmxsGEjWxI9sB0l+/NobSw0p73o3yYXteJvPeG4dbNDYTBoeEF3Kt3OMN253SKzMk4zSdHm7wcJeGQa3Vvv00hBthigxEY3PC6flVTkM28gVmqLeoY1OskHCNddm68EpYET5Ak24C/V4PJk8R+SEsMkgb/Aq9ATyrrYskPUiu2NWAOczDrzQiISEDX3psDhO6Fm8YkVslLUobp22NPr63NLdVGZH7Rso2zlGsGLRo3HkG/0S5sTmDfj8iEbE5QhYisFFoIEft6qahYE6PBByv27Lwrwde2WHiAKGeIcmtrR38NAUuRYWBMewKmx/l88IpXbwLWyjpUDTAgGeqqoRcuWE8B8/ue+NysVL9I4fcQLyHzngySx+nrON5TycvKXhdGKU77O6EtF2bC9s1hcWuI0yTb06yD+Z8jcI2Gl07hbbj9LzicEfJnRUL1MW6Be8RiLVFDd5G3x+QCwOviBIuTK7sBeHbA9YlcDmtylQ5JK67/1YXnFo1ImNlLIM/AiMy9YXGo8+usuMeWVb3ejm/SbL+op1U++1rf/A/
*/