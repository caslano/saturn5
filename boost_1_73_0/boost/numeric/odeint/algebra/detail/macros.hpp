/*
 [auto_generated]
 boost/numeric/odeint/algebra/detail/macros.hpp

 [begin_description]
 Some macros for type checking.
 [end_description]

 Copyright 2010-2012 Karsten Ahnert
 Copyright 2010 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_DETAIL_MACROS_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_DETAIL_MACROS_HPP_INCLUDED


//type traits aren't working with nvcc
#ifndef __CUDACC__
#include <boost/type_traits.hpp>
#include <boost/static_assert.hpp>

#define BOOST_ODEINT_CHECK_CONTAINER_TYPE( Type1 , Type2 ) \
        BOOST_STATIC_ASSERT(( boost::is_same< typename boost::remove_const< Type1 >::type , Type2 >::value ))

#else
//empty macro for nvcc
#define BOOST_ODEINT_CHECK_CONTAINER_TYPE( Type1 , Type2 )

#endif // __CUDACC__



/*
#define BOOST_ODEINT_CHECK_OPERATION_ARITY( Operation , Arity ) \
        BOOST_STATIC_ASSERT(( boost::function_traits< Operation >::arity == Arity ))
 */

#endif // BOOST_NUMERIC_ODEINT_ALGEBRA_DETAIL_MACROS_HPP_INCLUDED

/* macros.hpp
ZGhoe2SeLeu+gL0Oz+ZzGZwMOSOv4C6I6ftA0/F3OrmI82Xe0feDpuexx3KGPRHtZr4taJLMH0FZFHmDfPuAptvRa8hEu7mmzS3jEPIRgsXUzVwel+h4h3FRXKLIdi29Bej2CLCtiFX7tf+WTBeK6pdbMQ23VPMoOGeXF2073ho0nlzJz1n8NoyTqEmo9LPij7cdEEfzyduF4si4UPlMD4qj8km6ODPpJLI9g80wRjuUY4Gd
*/