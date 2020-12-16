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
+NnCBuFH/sIPeo+UfZrIkthXeqJ6oh5lj/XpiDwSp0vr6YwID5EB/zoen60SO0Qe6Nn9SCfvaGyivs80+m5OaL+zAdP7+DlBUMA3a3ntsnoXB6BzQ/5quIbJGdy5VWJn51WJH+j5Rp4LqvAzbXohZb+ItJMKyrK2WqRgivPixVVi8xcrWS5xcGnjL7LszWzjS1n2ZY6uz7hGuvLS+SyGMm3pP09UpbGhsTkjPC2GPLeqen6/VMWTAFy/xXW5q18oULeTNYRd4eb+fFG8e+3GpEymyX19dLAvg25w/hvi2iAHK87DqoNpHJeu0uOSa6OVc+csXyDNRIAen841bbLN9ONr2CbXkq6QbYpypDiBqbgRUh7+Fp3daOT4Sm7PQtu4iXLcTLraSMyHlvwY/s0y9w034N/Q5ymB6FHrrzpgfujKf0ucwfn/Fj3/97vfoa+ZOmxnHbaxDrexDrcbus1G53eS7i7Sef1IP77b9ON7qsKfeR8ot+cl7X5J+qIuikQv0BfWNvTZe0DpYXAfff4SJd/XjXwPVYU/4ydH+R4m7b4R+VZPm1q/uj3apj49g3uKR/Seot/2R38Yo+9vUZZvV/Xi097P/vRd07aPmbIeV3MMcKivthHE/RU9Md2nP4evaNJoxbZ5Uq3rHqMtfqBY7pryrBJ3rPwvHnNlYPDDqqhP2Xf2CryfYpnnbXn9qMr/vsyfvvf9Y+r76KGUi/3cvt96hdIPyvFxgUV/rpyn9BwC/C91nzNxAAETedT33+erNE3ymfELhgby4BeleVHWL5DdnEdKfodDfeMxgJkH+Mi3zq1qnHzF2NerZg31R9GPwwGu9At/PSXjU0bGv4qMDrc5QcYdzPOUkfFJJePrRsY3jIxviowOB3ikDd9SMl5uZPynyOhw2xJkfJt5LjcyblEyvmtkfM/I+B+R0ZVzXUQOnHGOE/x7lEH34z2A12P/NUruNNeO1sYGjtMxHCTuqo7hMGic74cXcx9XJ29WwK7lJ30GcXrHybpVaCxdUTBkHPux0PVCPzDYZ5x88+iddkBQAlqRU/qYlnOo6FR4qLFw2DjRhaRl/ThH+AkeuroyF+dld4lpJt/MZEw7Q8UhKw+JAr9Wq3B/d+ZjnI0eB9p+xOQ5MRLTzJ+phKxmB9X+jgPTi4Pq5lx6DADLYB25/egzsod16Z+E9wcZvy63XqlEntx/vwiWL57zsYOmhN/mZSpUIM5VbAvYWHIMu7H/Ze1KwOOqqvArhDZgwSRNSRsChCRN0zatbSi1VqxN2pTSnTZAocIwSaZN2izTzKS0iIhYERGRRVxYFBCQXdAiguwi4IIFZEcEASkqCIgKKqj/u++fOeedeZMF5PuG5t7z33PPPffc9d17Lnhq3UzPty4ZYn5+m6upVvMC5jkBcbqOaxFmmyRN2mSd2BBoXOuatj9ZbAiYoHy63dZXS1jwYhMP0EZOHY+wyzYI9ytfda2s11OlXgMdSr26cI2q1xnIoM74J+wwddsVUbcNqm6Tvq4bDppldM0o0bWut4p89TZEXn69HRRRb7NMvX1U6o00qbePSb2BFl1vH1f1Niui3j4h9Ua8zBlLXFxvT4K6TLpwV2c63eV8iS1mu52HNAWDtttURxxKCJwHuvOJMXe7iH4EzwndB+6Yrusb96ln6DB84jaE95Y6DtThIq9jpg6XGvsZZ+ynwtjPp2g/mbeqm5StHOfXr6lchvPfc82bRub5CyJsodnYwkKxBdLEFhZJPYOWW8+LxVZAj7aVpdoWGF443DqeEVHDM+lrVI0HJazvlU63Tv9O3yMg7GFK3ydn1+0Z3akwdKf720q3T2fOIFYHc+IW6jeyfvLmIXs/R1Q=
*/