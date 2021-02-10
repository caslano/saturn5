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
rgVncRnz+11+40eeRaKIGTQ1U7hVzcaBCbtAGHNtxUQzgcL2rSlLY7YoVpaCZ7i76NyKEppD53oathv/NgAGeDe7gI5K4DcYX4fhaWmETrRrMv5FtuRuYyrQZ0Slpw18Mo1GVkIuqCAI0i3zmnwMJ38EIQnCsO1QKVJaaFoIzR2ybfmXrR+itA1G0z5bJBjNirWDAZ4Rje0BffP0jB8r3OIVZsYOKFXStl4ria1UMtV6nYdiGnu/ZTrbVWNyNSezi2A6dAYSTgaX5CyYB2QwmVyOhpb9fxIYhq1yRtXjYS2+Kdw6lGGjMuxOUMz69BgUFw9MGxxFOs3noxCZm0KucI7If/CY99/2fm2+1v1TMP2yd+XuGoLGMUlwWgjWilKcQ4lD1J2HJbNbjzMUMbW96hzTp5+DPxHWc/0iZLbC+fZAtCy0My1joxNQ0I0HQ2fDCVHgz53mKdtQYVeLty/Pz8hfw+mkdTItm3BruDk0DEvDTk448ZYyT21CJzuKS/Id5DJGXQ6H4k5Q3QnW/ATzeclaKnToKr+KEzuoMsEH6FXFgSqvrt5gCSKs0hbmQ7/XK2u2hyscsCb8ySLbOBxrj2f7zYRiXw/1DfJdIrcdTOB/Hy2zkz9D/6AepX/bjYDX9V84ms2xAc/D69nF
*/