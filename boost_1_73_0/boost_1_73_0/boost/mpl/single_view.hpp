
#ifndef BOOST_MPL_SINGLE_VIEW_HPP_INCLUDED
#define BOOST_MPL_SINGLE_VIEW_HPP_INCLUDED

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

#include <boost/mpl/aux_/single_element_iter.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct single_view
    : iterator_range<
          aux::sel_iter<T,0>
        , aux::sel_iter<T,1>
        >
{
};

BOOST_MPL_AUX_NA_SPEC_NO_ETI(1, single_view)

}}

#endif // BOOST_MPL_SINGLE_VIEW_HPP_INCLUDED

/* single_view.hpp
4t6wGgAdnNP0GB5B416WFZ2Oznl15xZsr2p6bD5a6Emmm0m1caJy6rlINeSog/6uJdVt3xqGfoXofqkDqXXzFUu42iuh+jgucMg6NtQMGFt9C3DWhe5Rr92iMszPWRpxLPrLEzFwn+R2zU7MmEWCO1PJFYoSJuq0QKmE/v+HS5WmtAqthaC0kUq3cN13qPQL09CrdkxDdiuNS+3p/0mui4fgn+JSjEtfZaRLXyWF/p9mGh76/xuXCqg0mo9OMzU=
*/