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
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
*/