
#ifndef BOOST_MPL_AUX_ERASE_KEY_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_ERASE_KEY_IMPL_HPP_INCLUDED

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

#include <boost/mpl/erase_key_fwd.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>

namespace boost { namespace mpl {

template< typename Tag >
struct erase_key_impl
{
    template< typename Sequence, typename Key > struct apply;
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(2, erase_key_impl)

}}

#endif // BOOST_MPL_AUX_ERASE_KEY_IMPL_HPP_INCLUDED

/* erase_key_impl.hpp
CE18wriNynWhTBoU6itcCsNTD4W6vbA8X+DoCHG85KObqyTKrE1mHQpl1mEeRnNRD9Gc3477Fa26V6hj35mltT2fts7UnahMkU0q46fOFWypMh4hbnZsohBeFscea1C5PhA+fMIYrnyHq0CNcn00PBOJiRkJtDJDFTB3VKRVxo91R0XggJlJ2v0WI74Hizy+fK/GzlB8iSCUD7rp9kzFN91CSfCXKTyFqvwV+BKgWH3P1kUeGi4fB67nKN70ea4=
*/