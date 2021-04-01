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
VQlSithHtvK3Gil/AULC5c0cmOs9qNHePrGj+uwcsPqty2NYhcqw9fd+9p31hWaorQncBlvEHkbcGe10SBCSjGQtxsckmla6xG1+49SXcQl1vnUeZLZnFidbVdH0FbJz3qyLv31hMVMykwbD5i+3mNKymZZUb755vZWZjIXZmtfGVTtdRkwM669x9eSBgaTYp34KL6K/z2ip2VA6zJS+7brnKea7PF6jrX1gjAMohizU7t6RhmS2GTq9mwWVBGSaJn9up+/qVvBNGbKJuevXPzSqcvBOz0JB9ahWyOMRLEynJ43uvMV76XRxzNxfEWzNO5f5R6M1jeamqSwhIrLkzImwbnJWAbSF/AnfH1s8uNwnH0dJE0jxQCLLCEeO2ObaODOCMikLZL7Lsbg5o9GDbMMn1wpku68jh3V4Ezja7K9Y3v31/TS9SJp5GV/sWt/j1Ldmb0S/mH+Aww1xfp6WGsZvEE7JJnmHHcdiWjXEG9egKCgfmVS47abdc+WmvJ9424bwThhDahQ1E13A+eRM8hjs9X+TCP91+OSvrsELBg3MW75pLJ/60eLTiQ==
*/