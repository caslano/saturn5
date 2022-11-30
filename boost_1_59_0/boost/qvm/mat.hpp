#ifndef BOOST_QVM_MAT_HPP_INCLUDED
#define BOOST_QVM_MAT_HPP_INCLUDED

// Copyright 2008-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/qvm/detail/mat_assign.hpp>
#include <boost/qvm/assert.hpp>
#include <boost/qvm/static_assert.hpp>

namespace boost { namespace qvm {

template <class T,int Rows,int Cols>
struct
mat
    {
    T a[Rows][Cols];
    template <class R>
    operator R() const
        {
        R r;
        assign(r,*this);
        return r;
        }
    };

template <class M>
struct mat_traits;

template <class T,int Rows,int Cols>
struct
mat_traits< mat<T,Rows,Cols> >
    {
    typedef mat<T,Rows,Cols> this_matrix;
    typedef T scalar_type;
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
        return x.a[Row][Col];
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
        return x.a[Row][Col];
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
        return x.a[row][col];
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
        return x.a[row][col];
        }
    };

} }

#endif

/* mat.hpp
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
*/