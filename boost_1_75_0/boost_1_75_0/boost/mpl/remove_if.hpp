
#ifndef BOOST_MPL_REMOVE_IF_HPP_INCLUDED
#define BOOST_MPL_REMOVE_IF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright David Abrahams 2003-2004
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
#include <boost/mpl/reverse_fold.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/protect.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>

namespace boost { namespace mpl {

namespace aux {

template< typename Pred, typename InsertOp > struct remove_if_helper
{
    template< typename Sequence, typename U > struct apply
    {
        typedef typename eval_if<
              typename apply1<Pred,U>::type
            , identity<Sequence>
            , apply2<InsertOp,Sequence,U>
            >::type type;
    };
};

template<
      typename Sequence
    , typename Predicate
    , typename Inserter
    >
struct remove_if_impl
    : fold<
          Sequence
        , typename Inserter::state
        , protect< aux::remove_if_helper<
              typename lambda<Predicate>::type
            , typename Inserter::operation
            > >
        >
{
};

template<
      typename Sequence
    , typename Predicate
    , typename Inserter
    >
struct reverse_remove_if_impl
    : reverse_fold<
          Sequence
        , typename Inserter::state
        , protect< aux::remove_if_helper<
              typename lambda<Predicate>::type
            , typename Inserter::operation
            > >
        >
{
};

} // namespace aux

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(3, remove_if)

}}

#endif // BOOST_MPL_REMOVE_IF_HPP_INCLUDED

/* remove_if.hpp
9Nl/lF6/mpgwMFQ7SJRvtEL0wgRmL2fwWU5lZbR5gqAX2wuQ465MMDRaBxsz6qOzgDb1mL15EYVEFVz42PbUoYuW8+XdtR6uPyLvF0fiB8FUiiO+GjiGQIY8Ih3EBTjbQPcewCFCAeYKnB0yN7znib8DjDz+7K623kl/QFR29xP8h68k+DjoLUFBJg104zXej/HyTVz1b1Sam/agiw2rc6j33lVZ8jy4op79w0d6NjQ0+VWhmT0SzqjxxKIvCXF4P7d/S3L3mJVyLPjeztkqO8jokuB0DWSPWu078ahCRTJwFrg8IncYj4iFKu8v/UoLhEAzAzXHWQFvggvkB8Pbs2xkEU+5Ik8GMKDmSp4H7i0YLm0Mf8SxG9fLyv02EkzxWJYyBqq1j6WG2cOmLv22agCOL5ld6+3+57Z0ctGTBCKeTcDfPJtQ3ILKqQMqrrxhVT2Dos5z3tPMW1CQ3e3zm4X2TkOWfesaJKAwfR32zNRKvIKwgbiBvoFih9QM33lPDpfVE/xnYX/PJI9shd7LHr0O3evdCoYgw8JqPf6NcN4HJ3iHPNRruElR9Bm0c5S1H8M/PHacd378xQnIQ79GEO7BumY/UDxDZa5AuUnqUe+h2Pni9I4XjQQxBznOdstwgPaHcHYA8g39zrcdTiepiezYmDv0W3S2IACOF9kTJTZ8Qbvi+5t0peEPtD8+/0RgYTpuUeH9SMYF6Ef8
*/