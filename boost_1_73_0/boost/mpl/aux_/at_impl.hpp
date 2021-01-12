
#ifndef BOOST_MPL_AUX_AT_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_AT_IMPL_HPP_INCLUDED

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

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>

namespace boost { namespace mpl {

// default implementation; conrete sequences might override it by 
// specializing either the 'at_impl' or the primary 'at' template

template< typename Tag >
struct at_impl
{
    template< typename Sequence, typename N > struct apply
    {
        typedef typename advance<
              typename begin<Sequence>::type
            , N
            >::type iter_;

        typedef typename deref<iter_>::type type;
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(2, at_impl)

}}

#endif // BOOST_MPL_AUX_AT_IMPL_HPP_INCLUDED

/* at_impl.hpp
GI9z8G+4GlfiWlyDxzABz+J6vIiJmI6b8TfcgnlLcFzGYvgxvo7bsSImow/uxN64C4NxN0biHozBz3Ec7sM43I+L8ACuwoOYhF/gdjyEn+Nh/AqP4CU8iun4JT7FrzC7E8dvLIBfYxE8gaUxBSvjKayCp7EOnsGmeBY74znsjqnYD8/je3gRg/ESRuJltOBVHIPXMBZv4HhMx+l4Ez/EWzgfb+MSvIPxeB/X4wNMxl9xPz7G
*/