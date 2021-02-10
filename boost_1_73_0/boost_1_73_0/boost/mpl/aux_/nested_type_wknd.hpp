
#ifndef BOOST_MPL_AUX_NESTED_TYPE_WKND_HPP_INCLUDED
#define BOOST_MPL_AUX_NESTED_TYPE_WKND_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/gcc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, BOOST_TESTED_AT(0x0302)) \
    || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x561)) \
    || BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x530)) \
    || BOOST_WORKAROUND(__DMC__, BOOST_TESTED_AT(0x840))

namespace boost { namespace mpl { namespace aux {
template< typename T > struct nested_type_wknd
    : T::type
{
};
}}}

#if BOOST_WORKAROUND(__DMC__, BOOST_TESTED_AT(0x840))
#   define BOOST_MPL_AUX_NESTED_TYPE_WKND(T) \
    aux::nested_type_wknd<T> \
/**/
#else
#   define BOOST_MPL_AUX_NESTED_TYPE_WKND(T) \
    ::boost::mpl::aux::nested_type_wknd<T> \
/**/
#endif

#else // !BOOST_MPL_CFG_GCC et al.

#   define BOOST_MPL_AUX_NESTED_TYPE_WKND(T) T::type

#endif 

#endif // BOOST_MPL_AUX_NESTED_TYPE_WKND_HPP_INCLUDED

/* nested_type_wknd.hpp
Pfyp9f6zq96fSZn57KrFZ1LXPMnyZFqSQGv2s/oLVAkDMVz6a7uTNKBg7xPMR4zEh5JAT2q3z6TddrtZB9PFLTMN8lDyOR/CnVnT5JSGh1IY9IQYM8LZBO6mFyVkRnhA0rooEWvKgm+YB1T8Rg890aspC+NxwB0BLOI0WcPXYCunxghcAwrX4nXBGECnzCEINv+IjiPkU7AW/fbEQkzfElA0wFfpewPBa2iJscVSuWRI4BBxqdJpnX0+ObZPL9p2wzo/LjsjForRUi9icjDOKE6HOat+braOzy6sKuyAnCtw1k/qW4xc0ht5qDcKQlda9Cq/bHarMoAi/Mv7cBKLlhhfTHY/piK+WVzIdOhgAOxJ0S3J8ksxrXqz9FIg17xo2bKaUwvITdGKeDgAkOdG5pCR6XI7/tXMCZpHZMqLDmA2XXcI9JKwoD9Bgi4I93nyhmWKmdjo9QiJUCb2Kc9I5nXSN3FGOXXE+gJ8KJlYToHEmGUJ5As4LaFbMexIluOQIdx6I78RRN7cfplCcwmDRWIi4FTFRAtE7L6ydg+NWFDOzF0n3dNXRvA405xCLp/P9w2iYR0bRr+o4nwe434ud1Do9TL3hKH+VBg3NetIaNARrd8Sp+mnvPUZJFp5YlmfQCzF55N15Fnd+QSO
*/