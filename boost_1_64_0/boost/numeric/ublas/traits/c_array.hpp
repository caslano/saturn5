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
Ja/XD1tdoOm560RMMwQ0ByVNWheHnqfpfo7nX6Tw/Qbdv7LdcqndHLa4/M0W3qO8UhE/DJDt8iXAUeCtTewX5+5dSbS0tnKxyx5eW8mH6NcKaYl2C8D1PNRof56PoqYfwROUXiQGmfYxPDa0vr6FcC5FGcivkPQc3Wa/jAC4zXymfUsKdnuST73gsciy/S7lBR/ZrPjv3pRdpZg9ByB7acAMCNCsJc23YWVpfVQkacMo0e8QUawzVrv6UnAeTv3CKe+E697eedrmitIniAhK01eE7Hek/zOxNfFUtf8Ura2vmR9dHHuvfo5oc500bL9wCHTvSDgdO0pffH88Q3kKMTsSP9fsvloxewvQGvAm4GN539VnEvoDGnJJXenc0toKV730WcK/QYxyv1eN+VlJfR6up/TOrn3BtPH7DCXxvlJHCKeXyBKZiDN8xymb+LvRygh3BsXpu9FqKK4341mEd+6tMi6N8SzC63Zr4nq+fnFNNPZOvpv49OVnS/Fgv8lyyP6QKdCL5fzV7qJwqL1o0nd+M/HqoN/TujyuvvE5XLcvE80t4irMdvlG/WZT/HdA21s8KDJc66T3cGm9PAlrlcl8F8M06TjvU76fiNsxmX2xr4v5zWdz2t7J2m9+Wsxnl/kVTlE+896LQpXwl0/3gq03Q/kD7+f7mLXP/GXSZz5Tzes6vR/SnyR6SZgONADS7Xy4jbfofAokXmaont3zJZ/hSFtk5NNH5hNk33xO30T5EH0w7EsHhi8YSov3zc/nvA4B91eSV5o3h0olhLq3EfEHjXw6sq8U5cO0OfIOaWqrxk2Su8wi3DocxDiM3WeU8G77dQSg1+qn8G0i01enF+75PJmHPOge0/mTaXSPrl6woLpqzKL6aFVdRXVV3QQllj2A+3e5bjVxY1ijKquxc594p8W1qkBjLaULFlnqfTnr1oS5xbn6NecY206zmugGWsuQS5rlER0BrvP8re5ztx6jH1N6meM9qd+JsfUiqYH2eHyA6Cbb+4Yf0vMkMQS6lZsd3POU3pfeGdkxfND70J5t2cZU6dU3RM78O/j82+LfwcP4HbxxqmK2k+8qewaAQY/DE7tf+ECmrKKudHZltMzxzqX5Jp3wv0b3P9zv+s5lnqwT1hH9HG5PpFPaVuecT3SJZ7fVNa7+WgauvZ+Xgu6XzAerjp7nxO/rcN6mH0vxdMXsEDN9W/4HIT1mtyH5sZQ2YGldVh7fflofO064F4kBSXTzY1yv2Nq+rBxjZc7sCtrCssdFl6USbwvyaCMupBa+iNqN9Y+a+cZ7tj/hBqk8K7Nl+jz7HX4dpcH6m+8WnRZRedYYZxkTCedGYHjENYAYnxr7XXwL4aQj1W/r/8spbrjogv+HoZ8yEfdeROk6vwEcAfwW8DvA7yNqnngf8AfAfIY/nkK/mvZ/S2bG7ir2813FrVG4yDK7z4wNEZgaVJRB40x+b1sO0Q0U/V11dubL/pZT+M598z6LfI4vmom+Vn613QMZYT94u+sF3Ja9iW++vS9UQM+90BbnNHkHU3fC6xF31/C5FNeT8UjvYX5+xiMdgeO89G47ijIfncG6QaeYbrAJcftmsG7Q1dANOO3IDK0bdLLfhZrfiJn8vbXc2B1Nx/j7A/qOpg78DtVpw5F2J9PoO5qavydEuN9FmbBvu+s6hXwXfz9nFUA2/qxlyb/5yO8u1/VJNdEtFiORy42u8sK8nd/lc50fGTfpOywfY4zsfFCOD/i98ifjm22+U1hTGG2V+M5x7ntfrxgu5fa7jdsvcrvrdw2bbb/ORFdDdxeXu7cfeKfefoybtP30u/lDbrvj/4a2G6vfzyWKYVtmnMf7DLuNtquNovk=
*/