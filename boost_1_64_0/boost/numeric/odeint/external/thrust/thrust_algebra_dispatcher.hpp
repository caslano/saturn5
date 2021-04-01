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
UO1vIXftIpIQ2FLnpXZO8bkGrNUgOeM9Dc/PWTAUt8gS9KGVwpQzVeaZX46m5FmOIeWDzwZTaHRlZ90mfyMX2wiYb2eLN9oQEPDMpez+S0+uxiYZmtCr9YLKktbkZmGn9cl4RLYz6zUBAONjUWtfx3W+F9y9sWZ+BccSa5tQ8sWPHBUMbAsDiVLDp74x+GsleS5+inE/atHdf+QOpI2zSEiZSQy4YDSc6SYo15F4rg1qfafBPVpyQRHwfNfM2GnITGjuAubOaPYd/gO/DA2s425ADTiWEykfb0a7RyQsw1GoQAs6axXquV0fwThUrmeQDIJS9JEuKTUWKpk+3Fd/iWs+yJSrrAvDUl62FUmowCjWlZmrAq2kzRKJauJ6ec5Y7eERvnZTOffr9RW5fXCK8eiEFBiVTSyePmgoJgSrDrEldul0o5c7smy+C3qh2Knen6yNLKqSkWnC+npKufn2iXAL4hdcvoqSrnkpVRMB9JxOlGzuklbKeoMbk7SHuZvDCkKPd6QUcKjhieTyAnshk1r+9oBr1C8z82vueAZC4Nr5CFKDDEI1IF7MhQ==
*/