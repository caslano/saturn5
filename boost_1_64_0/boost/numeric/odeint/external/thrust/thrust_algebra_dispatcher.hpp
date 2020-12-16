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
Dwebi0FnwZzqwMOKHMytdF16gEsvqK2tqcVYtqezn7C97qwMS6UC3BqwOxTy6KkGCEF3VkfiASPSSE8rIlO2tNt3aYryuIaNGod2RxtlM+hMWDzJuuhrel0UHw9W2LFmYSSObUNjFq1T35TpbgykHMTSRBDK5gasx1TZjQ2I/9jq4VL+PbtY/hSWf7fLRy2pvnuvg6/GkIXIlIxXnxtP7wttsc8xb3ZwCsu4y/Hi2lzq1pM1NpsN/LtencD4UUPHYWZ7QOs5+vud/dcrv3mfaxrHlgeUTtKwYRanbJgA2nDunAHl4Sd3Tex3/K/L/q8wHWr4DdApH1J35U/mSuez4t+LqhT/mkcrPe0Z/q1Ox2t3yLYmsvdoX4rgGdlmwAlDae1LENgYsYfnOcPIweErv2Eeohkf3bAu09N5VHjtIJ9ncIjrwP6mo/XIzKnLsVbNBCu5/viO0h10PK+mejm6Zn3tgjnz+Tdg2F/ULHW67I3A6XZl0jj+f+Dr4ompdfKsMnOHh+cIeh74PsfqJ1w+OfvZE7itZXwHS+GQ37XCb4bxLUkzfyCvPocEH9wrZhnPGtoQjzZ2tPjX8f0xaX8S2xsY2UH7M9L+nLS0Q85hyT55v6Qdrvd2CJD4FByHMtaH8gdy1ronRuPnWc6vWQ77BurK+vLs9fFKXe8BwW+Y70U9b0o/YX1k3nyJ9L+LzclxX/Q/AEb/VeL1T+6xav/VVyrpV8Y8mi6uq4HBHyu1DOYsFjL8WWQoxA8wc3fYjAPgvVOn90Q6v3bYJHbs7w6K7lEefcK9XH8tjo5Lb6i1dZhfjzV/r2RarYW0P2BPiVkPBQoPif8FmOhB8l8t+1LBCz1kE/5CL/n93CB4rFsi8t5m0rdI2svLut5k9hlF6Sj+NoMfaPC3GPygNPs+4HY8QR2Io59MWq0rN6l14ybROenUOjLZx6A4rdtByrqaY0Wp5VES/6ZVlo7a2xDY137Is1cv/QbtkNB/9gpGpHX/6YW+xPefkaCXsix9vJ/osspV3ejnBB7mLjDb5RpzHrJNnQ+k09F9wNh01BarlI5DPhvM+eZ4g7d7g30FD95qDMl9Z0hHv1N+AfrX6Wb2985A7GViWsWGS5vYcOnwZ/wpaXOTHa3w0PWewjzvcCz5KPNMNXTvmLFiGukOJl1173vNmmULqpcvX1q/zO44LVLvOw9J93YXtDU8CNXZFesCOO4BD1X6mMm/RW9St1mK7nD+fWFkb9De04ZHGzKtTflY6zPS0buIh6X9erUp4+/0zUZ6cLC+J/f+Q6lbO2W6ujq6gly6LGjoWnuQ4FNheopLu3aoCNP1XR0boKdJ0M0gNPactF7HZjfiGuzq3CI2n0L9E99bLERPfc1LR+f3+bTnUCejimG7Zo5ZkKbdkFbbzSLVf8kHddI2iNjJ0ndAQ7yy6yMVvk2tqUHr8EdF8CJDKfPXKDzaX/UB3odW8s808i83eUV2fvdQ+BkJsh+teM8wvI9lGnA9bqEfyLh1vOmXJ5hx60Qp3+EAj8h3Ulpi7509NITJGwkSe48vlACWi723Oq2/UyxYvjz6mImzmxiU9tMyXMssMdCa0vQ5ZX9bw7pNktiP/IbiAk0GIl8IyzTVt3Wv1TI2R2SsWx7i61va3HsqOds20MLxAXexjidTduoWcka//6xz40KU3xTK3RrTLcOM+hIlre4fNxnbaacOOyjHg5QD86N+18z5uBT5d4kS76ZPdHel+VoFbWKSv5/eFLZCDpZ253RUYyDvnaRyMHmv1/XBChkT/RtuQXtHe6OX4VnY4fgg291Q78/ApvF9m/VKLxPC9sw985HdyLZUkELtuAt24N6hoP4+HWlHFKM=
*/