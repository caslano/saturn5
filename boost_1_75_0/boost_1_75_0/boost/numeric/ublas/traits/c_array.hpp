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
uSrFvJ1/a3MukaaK2M7xtnIAKasUei5FykjfOP39uOPSXs4huXlqNlsHyy33uRoyA3BLCUwzH19FaO2IYMm055MvywopoJaRLB3XVIozV5/yOv//RFesKcEKGfI4tsJBbnpVL8OGqKFeyJz3zXS8KN9VosRxoPZGdZhHwi6ipqEUZ4CIoAihY0IgoScgqixR+7cVsQQWTYbqrbwiXIqd080lQLP3lIntN663VZ7T2dcsXKQD6Wet2Ml61NnDIGLWZ9dEVvjXgnep6pGCw92SRAnrDt4z47z08o3WYsY/NavronPSg6c46YrScoGRwmBibIVT3m81zbrizNlhVdKZsZDfPZJETSeTDO+K1EhAI5+aQqRytvKOovUlLV996rdwPLO1xPRc756nMHZfLvhJNAUsa1xaq+khU4O14iWzg0vxDGeWeZggg1fzfXs50Z4C2aDRtzmnIlkcPouZFebmV1ZsScf6Qi1R+I2WPc0ito7PrzbSeVvCL7O3ccXegEId+oQnCkknFaW4NdEaaA27zyKPtYQQxZhVmJ+Z56V/qjAHh4IK3yHbthZidqX5IuSzBerN86T1MK9cebC5q0yhPywT/7WVDcttYbCevBNcOjw+977JBU/saANU17WFhk5OFdUmM+txc7eIAMRCTvrpY0UefYmhJCovdu8KX/lpXu97pG4CCwCKPNL5/u1F9Jln8BP16ryNdP4Kc+/s
*/