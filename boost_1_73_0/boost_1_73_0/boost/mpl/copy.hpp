
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
VoNoTqvzHdFnRyle8EJH9NUrwHPAi8HLwBrwFvAb4MPgpeCPwcvBj4I8fuHOwPO7ClwI/i24FLwaPA+8BqTv6FpHWj+ltvVTyi0dWixHZPMCRrbayq62sl4r67OyzJWpqJSxDSSjP0ZRGYqwMwnjzUMrU8NczkYrQ5FOHhMPU2laWZjIQ/hUQWrYa+NSaZjexn1cZRu10ZdNarMG/N2Vs9RoaV/b4VlHlKqcv2WeO4/zaqR/hj6e1RXOVFZW29A=
*/