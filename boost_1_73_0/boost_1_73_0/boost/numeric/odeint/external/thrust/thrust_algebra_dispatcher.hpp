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
0s8Zu0/ozHvzP6lHnjE/pRWCeeSBbi+N3FQOooMY9p8/fwaP4emTp08SmHAlsYalQ7VGs0ngpQgrbyp+cbFn8XUC6IDXez3VqpIWrC7dOTcINK9lgcqiAG5BoC2MXNOLVOAqhFLWCAeLk9PZ8fsEzitZVJ7kUndgK93VAiq+RTBYoNzuOFpuHOiS4EQupHVE2Dmp1R5pIzg0jfUcXp7XVgPfclnzNQlxB5VzrX2RpkVnanKfCl3YtLjZ/l7lmh87OSUTDb8E3TpwGjqLCfjKBBotZOlHCoQW225dS1slt25ISolUG7BY156LcBLtzjbCso8n8WXQkmPp/GC1sl7qvNLNT4WUo2cpO6NIiHKgIqEp5gQ6JdCE4rDzG4k+0xDwH1tz61eAVmQGhtkSZsshrLmVNoHPs9Xh4tMKPmd5nh2vTmHxDrLjU0/2cXY8odZLEjOAF61BS+IGZNPWEkWv+f+edPBQqqLuBMLQoaVWDQd3lhpsBK67TViWijpGNVFRcQOjT/k8HnwbABzQrNDCnyc77t9h5I/CeECv0VZLEdPaGNIRnCNFrB453/jdYSMPVCXLyCPYptZrXjOppIs8EXs/X7zN5iybz2N48CqQT9niYwxeGqBsDfkqI+uoYSaB4S8sMZR0UlGcqWE8
*/