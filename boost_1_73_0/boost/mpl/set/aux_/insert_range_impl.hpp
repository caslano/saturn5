
#ifndef BOOST_MPL_SET_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED

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
#include <boost/mpl/set/aux_/tag.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/insert.hpp>

namespace boost { namespace mpl {

template<>
struct insert_range_impl< aux::set_tag >
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

#endif // BOOST_MPL_SET_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED

/* insert_range_impl.hpp
a0TXfXaL3fd8JGgLNBbWmN1kujCr/rPiQNOaxEbe/YtFE8iwOVoVCerfyc1H80EO1X9Qt1ph1eSn/5g1L4SvBhyW/3wpy28zW1cZ581quyfqbR78OUds+/LyEI8c1ZPzKz69jrkFd4bKo301m9ZYFQvu3Q7PGOMx9LHmF+4PdIw3xRKafglk/7ryFl1BlSV8ln7fCPHQtCvpZRqjFs+kzaPYpKk+eOQT2bJU1UZNSKpqimwK
*/