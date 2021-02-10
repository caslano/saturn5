
#ifndef BOOST_MPL_SET_AUX_AT_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_AT_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/at_fwd.hpp>
#include <boost/mpl/set/aux_/has_key_impl.hpp>
#include <boost/mpl/set/aux_/tag.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/void.hpp>

namespace boost { namespace mpl {

template<>
struct at_impl< aux::set_tag >
{
    template< typename Set, typename T > struct apply
    {
        typedef typename if_< 
              has_key_impl<aux::set_tag>::apply<Set,T>
            , T
            , void_
            >::type type;            
    };
};

}}

#endif // BOOST_MPL_SET_AUX_AT_IMPL_HPP_INCLUDED

/* at_impl.hpp
rFfJKiCHdLP3fgFJVmkKvWvgH6+bWEDeD9sscN53JqODHL1/iD9QSwMECgAAAAgALWdKUg+gP487AQAABQIAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q4NTJVVAUAAbZIJGBNkV9rgzAUxd8v+B0uLX2UwErHKEEQcUwo1Kkd7DGLt1OmRpK0W7/90lhsn/KHc37nJJdbMlYKQxHwdjgqt/zQ5Vfp2kSQ7/M1JB0JjRX9WdhlZQWvcbY7FClwdhdyNnlhCUssSZ9Jh6atCbimsbs4gfGXsq8jKNJ894lXFoZpUeCg0Jxkgz0ZI76dhz2IObsRPDrpWhrsDS39YWZHMKpxPbsjQD6InqZXTHHtcBZdW89JyNkkQS5V34uhniBbxlZv+7LK8u3q6s73RcVeNk8Ydhie8OQStoakJuviZqfb3hr5rh+k2+MFa2EFiqMljbYhvH43NsLgF9GAC9MouwB+9lqHIK2Vlqp2nTbPjvhw5qNWVknVRZDEeRzAoUwL3yWAPC5LnBoFfkro2gbwfsiqwFHuTs7mKHaf/D9QSwMECgAAAAgALWdKUotmgValAQAArQIAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q4NTNVVAUAAbZIJGBN
*/