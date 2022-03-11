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