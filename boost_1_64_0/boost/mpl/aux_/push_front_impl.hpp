
#ifndef BOOST_MPL_AUX_PUSH_FRONT_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_PUSH_FRONT_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/push_front_fwd.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/aux_/has_type.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

struct has_push_front_arg {};

// agurt 05/feb/04: no default implementation; the stub definition is needed 
// to enable the default 'has_push_front' implementation below

template< typename Tag >
struct push_front_impl
{
    template< typename Sequence, typename T > struct apply
    {
        // should be instantiated only in the context of 'has_push_front_impl';
        // if you've got an assert here, you are requesting a 'push_front' 
        // specialization that doesn't exist.
        BOOST_MPL_ASSERT_MSG(
              ( boost::is_same< T, has_push_front_arg >::value )
            , REQUESTED_PUSH_FRONT_SPECIALIZATION_FOR_SEQUENCE_DOES_NOT_EXIST
            , ( Sequence )
            );
    };
};

template< typename Tag >
struct has_push_front_impl
{
    template< typename Seq > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : aux::has_type< push_front< Seq, has_push_front_arg > >
    {
#else
    {
        typedef aux::has_type< push_front< Seq, has_push_front_arg > > type;
        BOOST_STATIC_CONSTANT(bool, value = 
              (aux::has_type< push_front< Seq, has_push_front_arg > >::value)
            );
#endif
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(2, push_front_impl)
BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1, has_push_front_impl)

}}

#endif // BOOST_MPL_AUX_PUSH_FRONT_IMPL_HPP_INCLUDED

/* push_front_impl.hpp
ELd30cum/yrlTm/Jc+VGAl9UtExyQl/OnxVJRFgsjaNRAeqbSb2hPFVUba7jj93ybppjZXUMc0KMzuBmAwPWGPya4oCc7Fk+mc79CYkgtRUkO0q4olyfCOqQmQY8HqJmyfqN2tbI23cqeHUjcaeciJzWgAiZzkea0xFt6Bbp2CMvcDsRv/UXS4E+THe8qmGNwnSkgaIc6/NKM7tvaQ9zPLEioIq/1hvMhJVgDfok9GYghWtazN+pW+6t8FEImbLgzuFB0oW4GG6W6W+Mq8vYcMY/bBEP5VPUStuDmWN9mWt47Z9p7FA9BIG6DUX9UV2JMUcLuj13EZ/kSzmd4rHp3aiaQz88DXfHphD8/BPKa4anLQ3i0nzCJVgi9FORyYA9sNMeTSx9j1mEhqFjjcGk5PLFARORYJ7ePRlpex03DvcH8+i66mM8PUc3pkUZnobf80VYRXr9t6YfcjiGtakOQESYIWat7zjMVy/Ixvj3BVUHLJJLJqER6kGbG7Q/KVErmB1LQY0WczjhIAyAeP49h9bBa9u4KL7IlBeUHmuULiDI3QKGlIov/gns4w==
*/