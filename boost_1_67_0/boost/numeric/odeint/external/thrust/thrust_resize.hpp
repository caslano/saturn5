/*
 [auto_generated]
 boost/numeric/odeint/external/thrust/thrust_resize.hpp

 [begin_description]
 Enable resizing for thrusts device and host_vector.
 [end_description]

 Copyright 2010-2014 Mario Mulansky
 Copyright 2010-2011 Karsten Ahnert

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_THRUST_THRUST_RESIZE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_THRUST_THRUST_RESIZE_HPP_INCLUDED

#include <boost/range.hpp>

#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/distance.h>

#include <boost/numeric/odeint/util/resize.hpp>
#include <boost/numeric/odeint/util/same_size.hpp>
#include <boost/numeric/odeint/util/copy.hpp>

namespace boost {
namespace numeric {
namespace odeint {

// some macros that define the necessary utilities

#define ODEINT_THRUST_VECTOR_IS_RESIZEABLE( THRUST_VECTOR ) \
template< class T , class A >                               \
struct is_resizeable< THRUST_VECTOR<T,A> >                  \
{                                                           \
    struct type : public boost::true_type { };              \
    const static bool value = type::value;                  \
};                                                          \

#define ODEINT_TRHUST_VECTOR_RESIZE_IMPL( THRUST_VECTOR )     \
template< class T, class A >                                  \
struct resize_impl< THRUST_VECTOR<T,A> , THRUST_VECTOR<T,A> > \
{                                                             \
    static void resize( THRUST_VECTOR<T,A> &x ,               \
                        const THRUST_VECTOR<T,A> &y )         \
    {                                                         \
        x.resize( y.size() );                                 \
    }                                                         \
};                                                            \
template< class T, class A, typename Range >                  \
struct resize_impl< THRUST_VECTOR<T,A> , Range >              \
{                                                             \
    static void resize( THRUST_VECTOR<T,A> &x ,               \
                        const Range &y )                      \
    {                                                         \
        x.resize( thrust::distance(boost::begin(y),           \
                                   boost::end(y)));           \
    }                                                         \
};                                                            \


#define ODEINT_THRUST_SAME_SIZE_IMPL( THRUST_VECTOR )            \
template< class T , class A >                                    \
struct same_size_impl< THRUST_VECTOR<T,A> , THRUST_VECTOR<T,A> > \
{                                                                \
    static bool same_size( const THRUST_VECTOR<T,A> &x ,         \
                           const THRUST_VECTOR<T,A> &y )         \
    {                                                            \
        return x.size() == y.size();                             \
    }                                                            \
};                                                               \
template< class T , class A, typename Range >                    \
struct same_size_impl< THRUST_VECTOR<T,A> , Range >              \
{                                                                \
    static bool same_size( const THRUST_VECTOR<T,A> &x ,         \
                           const Range &y )                      \
    {                                                            \
        return x.size() == thrust::distance(boost::begin(y),     \
                                            boost::end(y));      \
    }                                                            \
};                                                               \


#define ODEINT_THRUST_COPY_IMPL( THRUST_VECTOR )                        \
template< class Container1 , class T , class A >                        \
struct copy_impl< Container1 , THRUST_VECTOR<T,A> >                     \
{                                                                       \
    static void copy( const Container1 &from , THRUST_VECTOR<T,A> &to ) \
    {                                                                   \
        thrust::copy( boost::begin( from ) , boost::end( from ) ,       \
                      boost::begin( to ) );                             \
    }                                                                   \
};                                                                      \
                                                                        \
template< class T , class A , class Container2 >                        \
struct copy_impl< THRUST_VECTOR<T,A> , Container2 >                     \
{                                                                       \
    static void copy( const THRUST_VECTOR<T,A> &from , Container2 &to ) \
    {                                                                   \
        thrust::copy( boost::begin( from ) , boost::end( from ) ,       \
                      boost::begin( to ) );                             \
    }                                                                   \
};                                                                      \
                                                                        \
template< class T , class A >                                           \
struct copy_impl< THRUST_VECTOR<T,A> , THRUST_VECTOR<T,A> >             \
{                                                                       \
    static void copy( const THRUST_VECTOR<T,A> &from ,                  \
                      THRUST_VECTOR<T,A> &to )                          \
    {                                                                   \
        thrust::copy( boost::begin( from ) , boost::end( from ) ,       \
                      boost::begin( to ) );                             \
    }                                                                   \
};                                                                      \

// add support for the standard thrust containers

ODEINT_THRUST_VECTOR_IS_RESIZEABLE( thrust::device_vector )
ODEINT_TRHUST_VECTOR_RESIZE_IMPL( thrust::device_vector )
ODEINT_THRUST_SAME_SIZE_IMPL( thrust::device_vector )
ODEINT_THRUST_COPY_IMPL( thrust::device_vector )


ODEINT_THRUST_VECTOR_IS_RESIZEABLE( thrust::host_vector )
ODEINT_TRHUST_VECTOR_RESIZE_IMPL( thrust::host_vector )
ODEINT_THRUST_SAME_SIZE_IMPL( thrust::host_vector )
ODEINT_THRUST_COPY_IMPL( thrust::host_vector )


} // odeint
} // numeric
} // boost

// add support for thrust backend vectors, if available

#include <thrust/version.h>

#if THRUST_VERSION >= 100600

#include <thrust/system/cpp/vector.h>
namespace boost { namespace numeric { namespace odeint {
    ODEINT_THRUST_VECTOR_IS_RESIZEABLE( thrust::cpp::vector )
    ODEINT_TRHUST_VECTOR_RESIZE_IMPL( thrust::cpp::vector )
    ODEINT_THRUST_SAME_SIZE_IMPL( thrust::cpp::vector )
    ODEINT_THRUST_COPY_IMPL( thrust::cpp::vector )
} } }

#ifdef _OPENMP
#include <thrust/system/omp/vector.h>
namespace boost { namespace numeric { namespace odeint {
    ODEINT_THRUST_VECTOR_IS_RESIZEABLE( thrust::omp::vector )
    ODEINT_TRHUST_VECTOR_RESIZE_IMPL( thrust::omp::vector )
    ODEINT_THRUST_SAME_SIZE_IMPL( thrust::omp::vector )
    ODEINT_THRUST_COPY_IMPL( thrust::omp::vector )
} } }
#endif // _OPENMP

#ifdef TBB_VERSION_MAJOR
#include <thrust/system/tbb/vector.h>
namespace boost { namespace numeric { namespace odeint {
    ODEINT_THRUST_VECTOR_IS_RESIZEABLE( thrust::tbb::vector )
    ODEINT_TRHUST_VECTOR_RESIZE_IMPL( thrust::tbb::vector )
    ODEINT_THRUST_SAME_SIZE_IMPL( thrust::tbb::vector )
    ODEINT_THRUST_COPY_IMPL( thrust::tbb::vector )
} } }
#endif // TBB_VERSION_MAJOR

#ifdef __CUDACC__
#include <thrust/system/cuda/vector.h>
namespace boost { namespace numeric { namespace odeint {
    ODEINT_THRUST_VECTOR_IS_RESIZEABLE( thrust::cuda::vector )
    ODEINT_TRHUST_VECTOR_RESIZE_IMPL( thrust::cuda::vector )
    ODEINT_THRUST_SAME_SIZE_IMPL( thrust::cuda::vector )
    ODEINT_THRUST_COPY_IMPL( thrust::cuda::vector )
} } }
#endif // __CUDACC__

#endif // THRUST_VERSION >= 100600

#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_THRUST_THRUST_RESIZE_HPP_INCLUDED

/* thrust_resize.hpp
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
*/