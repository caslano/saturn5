
#ifndef BOOST_MPL_NOT_HPP_INCLUDED
#define BOOST_MPL_NOT_HPP_INCLUDED

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

#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>
#include <boost/mpl/aux_/nested_type_wknd.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

namespace aux {

template< BOOST_MPL_AUX_NTTP_DECL(long, C_) > // 'long' is intentional here
struct not_impl
    : bool_<!C_>
{
};

} // namespace aux


template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct not_
    : aux::not_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T)::value
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,not_,(T))
};

BOOST_MPL_AUX_NA_SPEC(1,not_)

}}

#endif // BOOST_MPL_NOT_HPP_INCLUDED

/* not.hpp
y5cWZoblXyoRvk9hPb7CJtzCU/g+e3Mnk/kBJ/LPnMQPOZ0fcSZ38yZ+wqX8nHfyC2bv9x0hPpMK2O9fh/R8w7r8lu2pLki+ijtHshwTWJ5hv4fv2+yDAvZ7VfMVYTVWYXU2Y212Yh1mX2+tDOspU8B1dH3zVWUD1mNDtmVjjmBTTmAzXsQWvJTH8Ga25O1sxbvYmmvZlk/yeD7DE/gW2/MDduAunsxI5E4p+cv9EZ5bOTK9
*/