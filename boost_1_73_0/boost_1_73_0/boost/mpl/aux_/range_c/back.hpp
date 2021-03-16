
#ifndef BOOST_MPL_AUX_RANGE_C_BACK_HPP_INCLUDED
#define BOOST_MPL_AUX_RANGE_C_BACK_HPP_INCLUDED

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

#include <boost/mpl/back_fwd.hpp>
#include <boost/mpl/prior.hpp>
#include <boost/mpl/aux_/range_c/tag.hpp>

namespace boost { namespace mpl {

template<>
struct back_impl< aux::half_open_range_tag >
{
    template< typename Range > struct apply
    {
        typedef typename prior< typename Range::finish >::type type;
    };
};

}}

#endif // BOOST_MPL_AUX_RANGE_C_BACK_HPP_INCLUDED

/* back.hpp
h52rhB52kilb0FkZKTvTpWUVRhYysgy68d5CGuhI9ffemLewraxQLC0K1XpZy6yAhh+HN4ZqcwupMS/o9GYnvUID6O53928aRMudBrxTU9qNG4XUcr8O/zaltRvyV+PU/XBzouG6GnUibozI+KeueioQZgW2/haj5K6resaLhygcVB8p+hVK9plParl/4ZP1cQCkd1+CPwO/Aq8FvwYp/N+oacC9QucHmaQWu5StMbKKDFrsRlcxTYt9gIzxdr4=
*/