
#ifndef BOOST_MPL_DEREF_HPP_INCLUDED
#define BOOST_MPL_DEREF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/msvc_type.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/eti.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Iterator)
    >
struct deref
{
#if !defined(BOOST_MPL_CFG_MSVC_70_ETI_BUG)
    typedef typename Iterator::type type;
#else
    typedef typename aux::msvc_type<Iterator>::type type;
#endif
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,deref,(Iterator))
};

BOOST_MPL_AUX_NA_SPEC(1, deref)

}}

#endif // BOOST_MPL_DEREF_HPP_INCLUDED

/* deref.hpp
NsOgNxTUwvpYevNKP10MJmW5LtRYW0E71wlj/jE7SwLT3sBsDl19VXvEgX1cQyHlQb4nJrRtJ4tUbKosz5xLjBJoIOnyhjOj4hgvFqv+IMRRg8LLGHQZgyX0u3EoPJAhOikQbq3AHU9pYzCD/3orABh1s2pQHJb20hT0YSg3Ypith5FkxZ95Uv/aqewitfA1FI4TYjnB3SaUezdcqpUxjXU+e1riu1BxLlQrJnaFodm44mSudbnHmBjRMe+/guTvZD8NpkpxXZ7EUWMhADS2b1l//kN8YYW8P6jonKDB/D9XHKbIUYaIJXAVdAg162eLl2zmt7bCpdljYumJf4qcqyLXJf+l22UgUX4iyH9vk9EPIt3TOj6+VvTL+1AOpt5okBNT7PtYO7d6FHvWwOwkPa5in+1wJ5VI4nhRSRZDkoi6mdQfa3OJ1DzM0OXRIoPcq+ffARIY+g02253HPSgn5judU9jNEzgQfwCxlxvSieyWwWMAMudMCaMcfDa2URc5CQhLsveAyLegOS4vIG7rSW7YbAmDQActA+sKFt0e9fh0EN5EmlkS9CkYSA==
*/