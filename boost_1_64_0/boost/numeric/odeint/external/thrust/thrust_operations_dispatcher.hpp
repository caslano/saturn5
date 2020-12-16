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
8TtRm/9A1JZf7x/HMUqvkU8ZJXLpOImPEH+Ctx3EkJK1SD1gOgbVSbSRVfg3pGrAv6SLrFkaDV0T6TJKrjsTzroAi8WXaSavmxPoQxjqF/XBV33gw6YPtDENuP6WgzlK6txp6rLerAm6pH3BP95Hswq/XvV50Pl2MPxmGXvBOK/6JXzwzRpklsl/Nownem63ugVjXsFzu0+psW1Q7oyrrSG/BY5AZHyDHcf3vaeDl+Dja+DPjC1wptuPcsN2+RzbJewHm8b6frAY/UDKjO+3zjIyvWbwn6ctbtLzPmnPBczeMzsvb0+yXpvEtriAbXGgpH3ZpJ1kbPkLavzI8tzWrns3K5oLC6zXvyjlgCa+Xr9MyXyhWa9vYT+/QO05thqbv8LY2JVapgJr+qs0TYE1/TbDd4saCy/sZU1/nVnTb5E1vaTVOv5K1Wc0vlTVR7fLZVafxmZuMXi7Lt9u8HZevt3g7Tr7TmOzF5ryv2bwtvx7DN7Kf5/BW/keMHPNGaaP7V9q3q4x/B4fHsU/DLz2m7nf3Pefvpvwv5r3+7XP2rdy84fE4ZdvLSqNOZz+nbQ94Yex1MTIYL//7HC1RxB6yaNjdCqb1nSa75NjY7ywPonzenqsnLkIL1su43EWoAU+RvsjmeOoC5n3+Y1N0sYfbh1x60j7c8VLp9fF83KtK+eJz0lepomXvJzXZN4iL+6T5QzhReHFtOCFl/T/CxS9TmcN/YUyXkha4e+Tsx3hJ2ng43q4zpwb/UVkYVrj43rYU9bhivfuaK/o/PQ66NRbusB7+3uDdr3O0P/d0K8j/Vukf8TQ/9PQP0L6f5F+u6F/x9BvJ/2/SZ819O8Z+izp/2PGEtApPM6vqvQ7UHH8HlW+vAtNeQMA1+VdyPIGAq7KA53Gw3/UlGfxH2B595nyBpvygPexOE15oIvsB/Yx5Vl8Ccu7zpQ3NFoe8PQhJf0Nhn64ob+B9COMfKBTeJxZGfksvlzhT0vH33IeXeXXGyer9UYlYPpMJ10VzzeW+b6p8o0z+cYn5PuQkue1BHk+TL7diu9HDN/9Evjub/Rg59gDBI/1Uzz/gSa/neMPolz3Krk+auSamiDXxwxfu0Y/WOHfTdDHIQr/XAL+UMPfrrcPA77AneqlS5bXqVvuKs2zvcNd/WT/Mtt9YFjY2tK+Lsili4K5Lp3zy5pTpfcvvZdRmyxXbR0uyNYuqVsybw6cUBfMq1tSU10/f8HcFf5zai/4nO8l5V7Yf/6FOZPnAvJ8mbrw27Q6f/eKaUQJxY1BuInNxUlrHb5uZpbkfVgXhroCHleJGhtal+PCu3w7h56hq2VdHY24TbgUJ3vdS1u6s3KfqDhYEAZLmNfR057lGR3fjAlvGWXaQ1YeKbhUsNCf/1G2imTZFresbc7TjAmWdzZ0ZY6uqZ0f1PJNlEWqPdP/Y9ucS93NdzznZ1b3rF2Cg72cDy/0E1be14Qw6KU209jjPA1YfzmPHBzUbAi/ptY1o2pNQR5e7Pgsz2Cz2ux99qgv1K+FbBbSV2yJql/qfdkG49sVRfdOR1aZPUKZjrmk73VoevRj8trH3NFZBjzLgi3JGmZP5K3lnLJcj0ekw/+R+1MrSLuStFrmIersptTeg0HeYzkGloYpjoGryEdkt2fzOLvSdQuIVzLVU6aTyEviccme08aAWQ3a46xfOe3/9ynxJ5f7j90dXdlMkz4jHxzmgYMmDtMDwOCT7fwMcWM3cL6EAyB8k7KPsvx3Ffmgon0RPlOc36fjb5kn1vp6ScxXpM8uljZeU+Xn+halJ8BisUbXVQkPwKJxAuhX1kZdtrNM4efpNb9OsSnIpGXBOZq2X01LXnoN3SNysZw=
*/