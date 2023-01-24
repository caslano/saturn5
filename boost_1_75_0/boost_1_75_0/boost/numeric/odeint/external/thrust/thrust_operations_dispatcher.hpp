/*
  [auto_generated]
  boost/numeric/odeint/external/thrust/thrust_operations_dispatcher.hpp

  [begin_description]
  operations_dispatcher specialization for thrust
  [end_description]

  Copyright 2013-2014 Karsten Ahnert
  Copyright 2013-2014 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_THRUST_THRUST_OPERATIONS_DISPATCHER_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_THRUST_THRUST_OPERATIONS_DISPATCHER_HPP_DEFINED

#include <thrust/host_vector.h>
#include <thrust/device_vector.h>

#include <boost/numeric/odeint/external/thrust/thrust_operations.hpp>
#include <boost/numeric/odeint/algebra/operations_dispatcher.hpp>

// support for the standard thrust containers

namespace boost {
namespace numeric {
namespace odeint {

// specialization for thrust host_vector
template< class T , class A >
struct operations_dispatcher< thrust::host_vector< T , A > >
{
    typedef thrust_operations operations_type;
};

// specialization for thrust device_vector
template< class T , class A >
struct operations_dispatcher< thrust::device_vector< T , A > >
{
    typedef thrust_operations operations_type;
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
    struct operations_dispatcher< thrust::cpp::vector< T , A > >
    {
        typedef thrust_operations operations_type;
    };
} } }

// specialization for thrust omp vector
#ifdef _OPENMP
#include <thrust/system/omp/vector.h>
namespace boost { namespace numeric { namespace odeint {
    template< class T , class A >
    struct operations_dispatcher< thrust::omp::vector< T , A > >
    {
        typedef thrust_operations operations_type;
    };
} } }
#endif // _OPENMP

// specialization for thrust tbb vector
#ifdef TBB_VERSION_MAJOR
#include <thrust/system/tbb/vector.h>
namespace boost { namespace numeric { namespace odeint {
    template< class T , class A >
    struct operations_dispatcher< thrust::tbb::vector< T , A > >
    {
        typedef thrust_operations operations_type;
    };
} } }
#endif // TBB_VERSION_MAJOR

// specialization for thrust cuda vector
#ifdef __CUDACC__
#include <thrust/system/cuda/vector.h>
namespace boost { namespace numeric { namespace odeint {
    template< class T , class A >
    struct operations_dispatcher< thrust::cuda::vector< T , A > >
    {
        typedef thrust_operations operations_type;
    };
} } }
#endif // __CUDACC__

#endif // THRUST_VERSION >= 100600


#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_THRUST_THRUST_OPERATIONS_DISPATCHER_HPP_DEFINED


/* thrust_operations_dispatcher.hpp
VBFNqzdDjcfyiSFlH2q3n3Y0FC5xcdEiDerk5ovIbmqhMGlmixok8p9mm9+ibDfeFXLlQXxySWd9IFgYs8LJzCewAcL0iU0M+XUobhFdrQ9NVz2bRyYxWAHIrhCHuXLlx43nyjjfM4YLAbPuEoEnvqvJxLsMF7RxYf5N1wwW+puQEXEkaTIifsJlxAWnA2VEepWixTIiZhNCRlxna0ZGDORBDglZa1aqPDbiAqoNoAeykuV54CGe9GUV8CS9VarVVrFvbSyLyGpkYhORRWpk2yYi16qRv5c2VM1+FH6huc2+UFNC6ztDjlsizdbWC9qi+MG9gWNY/Cdj+PnsZosTA4sb1F6ftsPyyF2NJ1DO5FzQWPOKuy9orPnoGX1Jtay88SbNuiXqaHk69Gj5a/zft4neJ4fZaAG5a0tAn5AB1tJyovs1+0lESmZjItW3OrcuwJ/pWxrkz/c9HOBfWo5Y+yYHBZEePGVSfUDQcQw6vLs2IAhNqXwD1wYGobGSr3dQED4H4NtaEZg9Xl3rq213ISAoFYN+ezbwQ7yg3feSKTBVNgZVBqXCa959HwUF5WPQK0FBMzHo8aAgNJf2zQ8KWolB+UFBRRiUFRSE3Ms3NChoPQb961ldMI306qRVGeD+8PFA1sbujc8Q5SXFAT1LtDn5Kf2jRe2DdneYwLIQwOhgArs71iFVSOOj5OvT8RnaY3jndpMEFt9gQ2ZD
*/