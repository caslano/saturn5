
#ifndef BOOST_MPL_MAP_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED

// Copyright Bruno Dutra 2015
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
#include <boost/mpl/map/aux_/tag.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/insert.hpp>

namespace boost { namespace mpl {

template<>
struct insert_range_impl< aux::map_tag >
{
    template<
          typename Sequence
        , typename /*Pos*/
        , typename Range
        >
    struct apply
        : fold<Range, Sequence, insert<_1, _2> >
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED

/* insert_range_impl.hpp
r8aQMHNPuRHTmsuj4qrekClzVD+emszm6nptalDZ934djCgNjKhx8sV4p2Ow2OEz8xDSPvvFQ92xau5DLhWIoaH9olEUWnFPYvKxr0R6+r6qVbJA/nhI/1rxKJaw8IWZfNStTEr5T7xD07lgY7nt155D5kX00hqMA/MEYBuoufaJk87k7OFczbeGapVS/nIOdxnWoITRqOIdmMLBnUJMZG5sSVKnsaYZsMVIHzDq/La0n36NXr9mSUsDX+zBN+MrkRHIFjqZ1JUuJW6iPuwWjCXFqnWd0jzHy4BAXQ6EtAr9lnoOUqNHoFp06ehGqEGwz9hdbcRm6JnOeklYGga5tyHLImpnnUKcez9dtSXuM5e+qpRY2mxAHiTN95oBP29L5ORh87qCvgwUimh/wMibq1EdxKGyiCjDFmyzhzmbq5vQyFePsp6VcawZMxwtM/2kuEg0oR+yjq23THSw2iYhFbH6c3fMqhVSKaiLU4a1YTnf8FNa5UNvK2VTmbkmzuT4Iw65Yth1kXOtKvv2gdiax6R7qpb3jZ18GWUl0r2IHFTw8YH2/otDfHst2kkTBsiQZ+2nIax2COADM6StyFmw2fBe6quvVmBz0S/Bq5hpIm4KHogSNkz/ZW2+XXyanD+UB/S7AioKkNn1mwcrVpDgB+NkRriH1nb2wct1y/4VEhBcA4Zc95Sf4mj5Ddp4pGkI3w720L5J3UEsvIHG
*/