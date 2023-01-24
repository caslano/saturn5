
#ifndef BOOST_MPL_INDEX_OF_HPP_INCLUDED
#define BOOST_MPL_INDEX_OF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright Eric Friedman 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/index_if.hpp>
#include <boost/mpl/same_as.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct index_of
    : index_if< Sequence,same_as<T> >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,index_of,(Sequence,T))
};

BOOST_MPL_AUX_NA_SPEC(2, index_of)

}}

#endif // BOOST_MPL_INDEX_OF_HPP_INCLUDED

/* index_of.hpp
KLkLRgADka2eycGJTr/XYgIhW7WCvpqhZ7eoXfaUVxr4DAtbDPiSpT+4Ha648Gumt0jwjQUyy35IraIHKIRiOTPdw1t+Oyd04lFodfBbL/0RMZV4BqvSeWgZRE13qJMO5cK3c7gqXriMw2SKVRp1nD+qdfy9ExNALbihJfgyqHM3L4SiJvheITQFM7Ql+WVz7gpMo+DGE3tJxJoprNe3o3PVH+P0S6kVbOouqoBsnEz2gOiU8VF9vxfGsmqQMj5MrIEpCUoeL3xbXRf0rmj8lrJLnh9Fl/h0/sPiS6PS6nhIJqiShep27pA8XSwCoT+/wFVr5kCYBa82B8sThMkdeOVnipzd/yrR6dXiqf9YzztODH0wdSHuZapboHPlm4rJyhEPKdy0N3fIJ3e25SiDKF1rEwfoEALUeAZ3zGulKJxisLblMsS+fWdWSCOIFOLegvotEv35Oyu2BgmMXT0134TCBYnA00D6V8MoWjx1xEzAIumTTjIzRPq2o9J4Mcygf/UX3zX1wbuVhIRPTCynsofC09BfEJ3NMEQM8xToHg4RNpzGOggaDnqmPb4t4FQShGs68lT++EmO7Pbk64AsGCx0g4DLl5rwh0oTKGfXQoO7Yn6C1dNsOP6EJ6XA969O2EP7Ec0hSSw0V3+OMDl7Hm+LgzSJldHoiZwLiqPcqt/e0pwXyRZcutb8LvIg3BW94iOhphYlPGnjLElb
*/