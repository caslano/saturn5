// Copyright 2008-2010 Gordon Woodhull
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_MPL_GRAPH_MPL_UTILS_HPP_INCLUDED
#define BOOST_MSM_MPL_GRAPH_MPL_UTILS_HPP_INCLUDED

#include <boost/mpl/fold.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/set.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/and.hpp>

namespace boost {
namespace msm {
namespace mpl_graph {
namespace mpl_utils {
    
// This is a grab bag of little metafunctions I expect already
// exist under some name I haven't looked for

// I figure there are probably better ways to do all of these things,
// but for now I'll just write some utilities to isolate my ignorance

template<typename Seq>
struct as_map :
    mpl::fold<Seq, 
              mpl::map<>, 
              mpl::insert<mpl::_1, mpl::_2> >
{};
template<typename Seq>
struct as_set :
    mpl::fold<Seq, 
              mpl::set<>, 
              mpl::insert<mpl::_1, mpl::_2> >
{};

template<typename AssocSeq, typename Key, typename Default>
struct at_or_default :
    mpl::if_<typename mpl::has_key<AssocSeq, Key>::type,
             typename mpl::at<AssocSeq, Key>::type,
             Default>
{};

template<typename Seq1, typename Seq2>
struct set_equal :
    mpl::fold<Seq2,
              mpl::true_,
              mpl::and_<mpl::_1, 
                        mpl::has_key<typename as_set<Seq1>::type, 
                                     mpl::_2 > > >
{};
                                       
}
}
}
}              

#endif // BOOST_MSM_MPL_GRAPH_MPL_UTILS_HPP_INCLUDED

/* mpl_utils.hpp
zQpNYkWFhBlsm40H2FgsZZWS4W12C4F5Udxf+dZPX6zijqfk/OdZ8qARcilcDexV46kN11/4j8u2wdNSy3QQYWNuzGYHrMPjf1CYYrMSaoeV8fUtmNFOBqNb9dHWsBGo3NZWGR+9r5RY6drei68vkbt3gz4bUSnyYy3Uxbn/35eBKS6xixgkF41Qf6ER1kHIG46/BH4C6yB6FxrY97bVxnkS2rEA89IlV1Wn5IbSo/E8LybZzVFoyubPBb2+vIYkCaMSU7YO7o33UFlIXuJIr67n8NetwWj9Nxqx3EBIBfjSoQFXI4TFgZpb+IOo4MDW2h0QtopYT9Ea7XSpm5SMxo9z8NMHcZX6uTs3A/K0mBQh9n0Loz0P3S/oB1BLAwQKAAAACAAtZ0pSorDIx5EBAADDAgAAHQAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDk3VVQFAAG2SCRgZVLBauMwEL0L/A+DSy4Fr5Jl2bJGNZSykLJlExq3d0WeVG5lyUjapv77HdlpTduLPeN5M++9GYuIISoZsGKitQdHr2ccjs43oWLrut6OD9hudvUUeeyNVNiARtmgD0zwuUHwacYZO4Md+hf0RWgbZCJ1DVRvZJTTXL76toTvyyVs/mRswpaQxBRhTPhB
*/