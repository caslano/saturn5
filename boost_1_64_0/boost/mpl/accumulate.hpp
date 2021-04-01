
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
n4dpksVo4Krt2ScCNG4Bc6Q2GlNb8vZKl9XJeTe3icF7gazms318wOcBTEO1TtJHwVR42KD7GACfB2KhmmhIoBoPW7jYrwM/j89411eSi1kW1T9BbfOWP80Ihy5IhQxBdwYRw6RbtfPUj4pNfG4i75/rqkoAx2d9RfV1gQm84wH0M5lACNoOZChtQu9XZJWNAyHeEiM/BL1/UJyRcSVPkkqw1s+HiIkjReUrGZeAxOx0rlzOlWSKQN3UVDf93LsaIQoIqjX/xLGyP4f6xtDqhRiYPk3+DcMgPxdv4sTvNNBk7VeYEMP1dg/95Aj8WF3bBvhgjeN+tSJJASFucjRL9mybq9jULZcNw1TH9+lhYhtIlwxKdM5XeuFaar3oFDU+UHqrzRFi7rB8yKM82Kq9gYIaJ7U16iNcNWSQQM5Bo9nJ7vJIxw2130I+WVIgCc+6mUJyusJcobkaHEB6JWqWLfuLyMzETIWzhrpGmTixSoMSan9bGZMskMDO2S89KAzPXHmTFB8U5PsodzO10r/0pHMYUCJfVNZS0tJDJy3w5ZH2scT/Bkc0cMobHw==
*/