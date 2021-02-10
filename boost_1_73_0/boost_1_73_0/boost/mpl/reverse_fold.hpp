
#ifndef BOOST_MPL_REVERSE_FOLD_HPP_INCLUDED
#define BOOST_MPL_REVERSE_FOLD_HPP_INCLUDED

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

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/O1_size.hpp>
#include <boost/mpl/arg.hpp>
#include <boost/mpl/aux_/reverse_fold_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(State)
    , typename BOOST_MPL_AUX_NA_PARAM(BackwardOp)
    , typename ForwardOp = arg<1>
    >
struct reverse_fold
{
    typedef typename aux::reverse_fold_impl<
          ::boost::mpl::O1_size<Sequence>::value
        , typename begin<Sequence>::type
        , typename end<Sequence>::type
        , State
        , BackwardOp
        , ForwardOp
        >::state type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,reverse_fold,(Sequence,State,BackwardOp))
};

BOOST_MPL_AUX_NA_SPEC(3, reverse_fold)

}}

#endif // BOOST_MPL_REVERSE_FOLD_HPP_INCLUDED

/* reverse_fold.hpp
kVmwokK1tcDrHIxUe2/OseiRBixTVeWx09xzd9Bt94wp7b1FSTqPxz0nHkfLlDbcltQqWgiJdPDUh/sKPJjO38OhM3bS8mHPqVzaT9SiOEDOLQdeWNRgSwR/ACi5gW/EGrqmVLZL2K6dDRxrOAJhYLpaLsJNFIfLSTqPPjZ+0yxapYSh1kpnKnchhiO38KZmjVZWZUoGZJWESxdd1YdKbU2HxJMkAZfuBX951Uh8cJZddz3rEH80H7DjxK4CjJ4tMXr9M39QSwMECgAAAAgALWdKUhqYiAwFAgAAkAQAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxOTA0VVQFAAG2SCRg1VRRb9owEH63xH84teKlWmqYeMGyIiHG2qobQZBV26MXDhIR7Cg+oPn3dewAqtRpD3uaFDnx5fN333d3iSS0lCmLMZOF3hh322FzMvXaxuwxTRd+gYdZGh6myXw+m3abqjavDfMrHbTGkkl+PS15IGS37BZWWB+xjmyxRiZrrMrGAdaKVMjCh/dD+DwYQPLMvihCAekBP8FgDHNzdC+GAxiOxGgsHOThe8oCnYBWfWT9hm/UDsGebFYai2xqNKGmKG0qbHGvxHPal+yrE9pEOaq1gAatuy7Qb6i3lAsYM5aF
*/