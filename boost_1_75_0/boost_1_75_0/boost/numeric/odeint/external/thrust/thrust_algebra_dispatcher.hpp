/*
  [auto_generated]
  boost/numeric/odeint/external/thrust/thrust_algebra_dispatcher.hpp

  [begin_description]
  algebra_dispatcher specialization for thrust
  [end_description]

  Copyright 2013 Karsten Ahnert
  Copyright 2013 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_THRUST_THRUST_ALGEBRA_DISPATCHER_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_THRUST_THRUST_ALGEBRA_DISPATCHER_HPP_DEFINED

#include <thrust/host_vector.h>
#include <thrust/device_vector.h>

#include <boost/numeric/odeint/external/thrust/thrust_algebra.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>

// specializations for the standard thrust containers

namespace boost {
namespace numeric {
namespace odeint {

// specialization for thrust host_vector
template< class T , class A >
struct algebra_dispatcher< thrust::host_vector< T , A > >
{
    typedef thrust_algebra algebra_type;
};

// specialization for thrust device_vector
template< class T , class A >
struct algebra_dispatcher< thrust::device_vector< T , A > >
{
    typedef thrust_algebra algebra_type;
};

} // namespace odeint
} // namespace numeric
} // namespace boost


// add support for thrust backend vectors, if available

#include <thrust/version.h>

#if THRUST_VERSION >= 100600

// specialization for thrust cpp vector
#include <thrust/system/cpp/vector.h>
namespace boost { namespace numeric { namespace odeint {
    template< class T , class A >
    struct algebra_dispatcher< thrust::cpp::vector< T , A > >
    {
        typedef thrust_algebra algebra_type;
    };
} } }

// specialization for thrust omp vector
#ifdef _OPENMP
#include <thrust/system/omp/vector.h>
namespace boost { namespace numeric { namespace odeint {
    template< class T , class A >
    struct algebra_dispatcher< thrust::omp::vector< T , A > >
    {
        typedef thrust_algebra algebra_type;
    };
} } }
#endif // _OPENMP

// specialization for thrust tbb vector
#ifdef TBB_VERSION_MAJOR
#include <thrust/system/tbb/vector.h>
namespace boost { namespace numeric { namespace odeint {
    template< class T , class A >
    struct algebra_dispatcher< thrust::tbb::vector< T , A > >
    {
        typedef thrust_algebra algebra_type;
    };
} } }
#endif // TBB_VERSION_MAJOR

// specialization for thrust cuda vector
#ifdef __CUDACC__
#include <thrust/system/cuda/vector.h>
namespace boost { namespace numeric { namespace odeint {
    template< class T , class A >
    struct algebra_dispatcher< thrust::cuda::vector< T , A > >
    {
        typedef thrust_algebra algebra_type;
    };
} } }
#endif // __CUDACC__

#endif // THRUST_VERSION >= 100600

#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_THRUST_THRUST_ALGEBRA_DISPATCHER_HPP_DEFINED


/* thrust_algebra_dispatcher.hpp
6Q4RJCkc9/ieDd2OiPe0W5UxliJ1fokEOZhoSDteblp+X8Dhdn7jFRo44pKR7lGDFXymoFU2KxNJ6fs7sY6cuTukOfkpBz1rDgd0DR0v9FIQ3m5DDrpTXzzAEmZIHUUv6000naSr9KVJmXS/FlUGOpTeGmaN5ZAYPdCpJ1YlxO8/Ate1DQLC8q1j3bhiLetGtHur5V049N/1CnRrZqmRdlAysuWaN7EKahtTIfLyBxo3MzRqajvKuIUtrXUuNPZr97MBmyk/PIP1vBzQ83Jgzwdxabp/UxeBxmsDs819NDDxINvLz7JqIi5d6WqXmHHniJHYzxNZ7jzHK29/g9hWpmKuyFPxOfFQvcJG1GEaJmfVYTLuA0w8CQbh/KC2yZ9GbdMp4EqDFrbNITrs26htHs1HXJqYYBvIG+swCcmUbEj9rdRxbX5IqYMmrnZv6fLw2wl12pplN+4DBUpmivnZqRrrtsilD3DWfTmMWvzkWWrxQ39Ri48jAMkOvUas2yK3O8Z5bvpU1vIW+b4HqTdEeXcinzEKvwqaMbiYmUl1XhK6zjfdF3KlRHX+fXq9NlmfnK5P6I8fDRRy2Xz16hSq9CSilR3TiHZhAnz0qDaVjiazbeOJP/Wp1HWWWuGls5zu9r1KrZApRx3lrTBsikp/90wnMsuXxhbQFRRMJpO/O1IL4xQPteC1Nu7cAjZR5X7ZaE6FjwuohTaEbqEO
*/