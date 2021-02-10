/**
 * -*- c++ -*-
 *
 * \file c_array.hpp
 *
 * \brief provides specializations of matrix and vector traits for c arrays and c matrices.
 *
 * Copyright (c) 2009, Gunter Winkler
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * \author Gunter Winkler (guwi17 at gmx dot de)
 */

#ifndef BOOST_NUMERIC_UBLAS_TRAITS_C_ARRAY_HPP
#define BOOST_NUMERIC_UBLAS_TRAITS_C_ARRAY_HPP


#include <boost/numeric/ublas/traits.hpp>
#include <boost/numeric/ublas/traits/const_iterator_type.hpp>
#include <boost/numeric/ublas/traits/iterator_type.hpp>

namespace boost { namespace numeric { namespace ublas {

    namespace detail {

    
    
    }


    template < class T, int M, int N > 
    struct matrix_view_traits < T[M][N] > {
        typedef T              matrix_type[M][N];

        typedef std::size_t          size_type;
        typedef std::ptrdiff_t       difference_type;

        typedef row_major_tag  orientation_category;
        typedef dense_tag      storage_category;
  
        typedef T            value_type;
        typedef const T      &const_reference;
        typedef const T      *const_pointer;
  
        typedef const matrix_reference<const matrix_type>    const_closure_type;

        typedef T row_type[N];

        typedef const row_type *const_iterator1;
        typedef const_pointer  const_iterator2;

    };

    template < class T, int M, int N > 
    struct mutable_matrix_traits < T[M][N] > {
        typedef T            matrix_type[M][N];

        typedef T            *reference;
  
        typedef matrix_reference<matrix_type>                closure_type;

    };

    template < class T, int N  > 
    struct vector_view_traits < T[N] > {
        typedef T              vector_type[N];

        typedef std::size_t          size_type;
        typedef std::ptrdiff_t       difference_type;

        typedef dense_tag      storage_category;
  
        typedef T            value_type;
        typedef const T      &const_reference;
        typedef const T      *const_pointer;
  
        typedef const vector_reference<const vector_type>    const_closure_type;

        typedef const_pointer const_iterator;

        /// iterator pointing to the first element
        static
        const_iterator begin(const vector_type & v) {
            return & (v[0]);
        }
        /// iterator pointing behind the last element
        static
        const_iterator end(const vector_type & v) {
            return & (v[N]);
        }
    };

    template < class T, int N  > 
    struct mutable_vector_traits < T[N] >  {
  
        typedef T &reference;
        typedef T *pointer;
        typedef vector_reference< T[N] > closure_type;

    };




}}} // Namespace boost::numeric::ublas

#endif

/* c_array.hpp
2GYePSN5E5glKBAzkmcye8jT5UqTc+bS4dHRz3RAz/rP+h6dhyJlnGaaiQXLlx69jC3l11V4f99V7NQjpink3QpqvkoVKZnouzBnhDVPIyYUiylUFDMV5ekCm1SQXjFKUs7obDy5vhy98ehulUYrA/IgC1IrWfCYVuEto5xFLL0tMbIw1yQTiAM8TpUGYKFTKbrQzUizfK0MhlEfciUpvA1THi6gKNS00jpTx71eVOQc1vdiGaleVLvfXel148k1jFiHDyQzTVpSoZhHhtOjtYzTxLwREBCzYsFTtfI21kCViHsyJ8U4N1iQS5kqzWY0q8LjGTbKYHGqzUtJoYyqu5Vc7zAijgYlKXIBRYgDmGKJMHtUiJjlltl6XquoYmoD/M3UbOyNSQoYQ21/RpezNi1ClSqP3l/O346v5vTen0790fyaxhfkj64N2G+Xo3OkPoWynNh9ljMF5Tml64ynLK50fr9fr/U4FREvYkZtzRRS1W61eh2U1+LF0aHxpjBFlsAEc0xRqBBwHHl4PDOP5zbaL45+JIBt0F7yFOFX3dXpNjGJhOa7NKsWlcaN6g0VwRQczu9S12wds0WxtGY+jlmSCkbzwWwevPVHb4L55buBCexPfYTysN/vt1qp0NZyJ1qFOXWupkO39bFF
*/