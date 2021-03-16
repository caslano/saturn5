
#ifndef BOOST_MPL_ERASE_KEY_HPP_INCLUDED
#define BOOST_MPL_ERASE_KEY_HPP_INCLUDED

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
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/erase_key_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/msvc_typename.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Key)
    >
struct erase_key
    : erase_key_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,Key >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,erase_key,(Sequence,Key))
};

BOOST_MPL_AUX_NA_SPEC(2,erase_key)

}}

#endif // BOOST_MPL_ERASE_KEY_HPP_INCLUDED

/* erase_key.hpp
tjpa63oryBus2Y9cjnOQNbMcB/sW8Dcyr9QYpOEOsW/hZHNHKmdcp/Y+OM1cQ0t8KpWjh4Y6yeEOe5ENjnfwXxfDUHuhz8VwDB+WolNDrhDi61or51c38AU9290oDut0lGMzRpJEB8sWZnWwqH0R4lzwgZz2svMlbmuDORTEtzbAFbiN8Wm0V+B2k0NH8Vms1nNYBb1gLl8UFYt3pxZFqa0g7CG4i2QPk9jsUdpGq2fO5ZNem+hIFPd5Mi4rLj0=
*/