
#ifndef BOOST_MPL_COPY_HPP_INCLUDED
#define BOOST_MPL_COPY_HPP_INCLUDED

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
#include <boost/mpl/aux_/inserter_algorithm.hpp>

namespace boost { namespace mpl {

namespace aux {

template<
      typename Sequence
    , typename Inserter
    >
struct copy_impl
    : fold< 
          Sequence
        , typename Inserter::state
        , typename Inserter::operation
        >
{
};

template<
      typename Sequence
    , typename Inserter
    >
struct reverse_copy_impl
    : reverse_fold<
          Sequence
        , typename Inserter::state
        , typename Inserter::operation
        >
{
};

} // namespace aux

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(2, copy)

}}

#endif // BOOST_MPL_COPY_HPP_INCLUDED

/* copy.hpp
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
*/