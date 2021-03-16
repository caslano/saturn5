
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
FNsRr0VMau/MYZgLx0g/ehn4YM4WcWx9R0NTZydbrZHTJmoX71Y5f2gX03D7kDI+JKynJxrOoOebNcZxQGWMcVCHmL7odAMEai8fUp5HKTp1UHmWXvEN9a3c/qZnLu1sz2iuWPfxYyIX/1TNNpOtvN9oY7ueG/cP2f22RGu8JcfyXXadsG02aIfMC+xNC0dKBOoCdHv5JVu5EpVps0dDRNQp32GzRsuaZS9QZg0NBrw8anu9CVpZIdK1HQl0ZMw=
*/