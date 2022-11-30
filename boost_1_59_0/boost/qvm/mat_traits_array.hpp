#ifndef BOOST_QVM_MAT_TRAITS_ARRAY_HPP_INCLUDED
#define BOOST_QVM_MAT_TRAITS_ARRAY_HPP_INCLUDED

// Copyright 2008-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/qvm/inline.hpp>
#include <boost/qvm/deduce_mat.hpp>
#include <boost/qvm/detail/remove_const.hpp>
#include <boost/qvm/assert.hpp>

namespace boost { namespace qvm {

template <class T,int R,int Q,int C>
struct
mat_traits<T[R][Q][C]>
    {
    static int const rows=0;
    static int const cols=0;
    typedef void scalar_type;
    };

template <class T,int Rows,int Cols>
struct
mat_traits<T[Rows][Cols]>
    {
    typedef T this_matrix[Rows][Cols];
    typedef typename qvm_detail::remove_const<T>::type scalar_type;
    static int const rows=Rows;
    static int const cols=Cols;

    template <int Row,int Col>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element( this_matrix const & x )
        {
        BOOST_QVM_STATIC_ASSERT(Row>=0);
        BOOST_QVM_STATIC_ASSERT(Row<Rows);
        BOOST_QVM_STATIC_ASSERT(Col>=0);
        BOOST_QVM_STATIC_ASSERT(Col<Cols);
        return x[Row][Col];
        }

    template <int Row,int Col>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type &
    write_element( this_matrix & x )
        {
        BOOST_QVM_STATIC_ASSERT(Row>=0);
        BOOST_QVM_STATIC_ASSERT(Row<Rows);
        BOOST_QVM_STATIC_ASSERT(Col>=0);
        BOOST_QVM_STATIC_ASSERT(Col<Cols);
        return x[Row][Col];
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element_idx( int row, int col, this_matrix const & x )
        {
        BOOST_QVM_ASSERT(row>=0);
        BOOST_QVM_ASSERT(row<Rows);
        BOOST_QVM_ASSERT(col>=0);
        BOOST_QVM_ASSERT(col<Cols);
        return x[row][col];
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type &
    write_element_idx( int row, int col, this_matrix & x )
        {
        BOOST_QVM_ASSERT(row>=0);
        BOOST_QVM_ASSERT(row<Rows);
        BOOST_QVM_ASSERT(col>=0);
        BOOST_QVM_ASSERT(col<Cols);
        return x[row][col];
        }
    };

template <class T,int Rows,int Cols,int R,int C>
struct
deduce_mat<T[Rows][Cols],R,C>
    {
    typedef mat<T,R,C> type;
    };

template <class T,int Rows,int Cols,int R,int C>
struct
deduce_mat<T const[Rows][Cols],R,C>
    {
    typedef mat<T,R,C> type;
    };

template <class T1,class T2,int Rows,int Cols,int R,int C>
struct
deduce_mat2<T1[Rows][Cols],T2[Rows][Cols],R,C>
    {
    typedef mat<typename deduce_scalar<T1,T2>::type,R,C> type;
    };

template <int Rows,int Cols,class T>
T (&ptr_mref( T * ptr ))[Rows][Cols]
    {
    return *reinterpret_cast<T (*)[Rows][Cols]>(ptr);
    }

} }

#endif

/* mat_traits_array.hpp
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
*/