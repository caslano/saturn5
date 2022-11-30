//
//  Copyright (c) 2000-2010
//  Joerg Walter, Mathias Koch, David Bellot
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  The authors gratefully acknowledge the support of
//  GeNeSys mbH & Co. KG in producing this work.
//

/// \file fwd.hpp is essentially used to forward declare the main types

#ifndef BOOST_UBLAS_FWD_H
#define BOOST_UBLAS_FWD_H

#include <memory>

#ifdef BOOST_UBLAS_CPP_GE_2011
#include <array>
#endif

namespace boost { namespace numeric { namespace ublas {

    // Storage types
    template<class T, class ALLOC = std::allocator<T> >
    class unbounded_array;

    template<class T, std::size_t N, class ALLOC = std::allocator<T> >
    class bounded_array;

    template <class Z = std::size_t, class D = std::ptrdiff_t>
    class basic_range;
    template <class Z = std::size_t, class D = std::ptrdiff_t>
    class basic_slice;
    typedef basic_range<> range;
    typedef basic_slice<> slice;
    template<class A = unbounded_array<std::size_t> >
    class indirect_array;

    template<class I, class T, class ALLOC = std::allocator<std::pair<const I, T> > >
    class map_std;
    template<class I, class T, class ALLOC = std::allocator<std::pair<I, T> > >
    class map_array;

    // Expression types
    struct scalar_tag {};
    
    struct vector_tag {};
    template<class E>
    class vector_expression;
    template<class C>
    class vector_container;

    template<class E>
    class vector_reference;

    struct matrix_tag {};

    template<class E>
    class matrix_expression;
    template<class C>
    class matrix_container;

    template<class E>
    class matrix_reference;

    template<class V>
    class vector_range;
    template<class V>
    class vector_slice;
    template<class V, class IA = indirect_array<> >
    class vector_indirect;

    template<class M>
    class matrix_row;
    template<class M>
    class matrix_column;
    template<class M>
    class matrix_vector_range;
    template<class M>
    class matrix_vector_slice;
    template<class M, class IA = indirect_array<> >
    class matrix_vector_indirect;
    template<class M>
    class matrix_range;
    template<class M>
    class matrix_slice;
    template<class M, class IA = indirect_array<> >
    class matrix_indirect;

    template<class T, class A = unbounded_array<T> >
    class vector;
#ifdef BOOST_UBLAS_CPP_GE_2011
    template<class T, std::size_t N, class A = std::array<T, N> >
    class fixed_vector;
#endif
    template<class T, std::size_t N>
    class bounded_vector;

    template<class T = int, class ALLOC = std::allocator<T> >
    class unit_vector;
    template<class T = int, class ALLOC = std::allocator<T> >
    class zero_vector;
    template<class T = int, class ALLOC = std::allocator<T> >
    class scalar_vector;

    template<class T, std::size_t N>
    class c_vector;

    // Sparse vectors
    template<class T, class A = map_std<std::size_t, T> >
    class mapped_vector;
    template<class T, std::size_t IB = 0, class IA = unbounded_array<std::size_t>, class TA = unbounded_array<T> >
    class compressed_vector;
    template<class T, std::size_t IB = 0, class IA = unbounded_array<std::size_t>, class TA = unbounded_array<T> >
    class coordinate_vector;

    // Matrix orientation type
    struct unknown_orientation_tag {};
    struct row_major_tag {};
    struct column_major_tag {};

    // Matrix storage layout parameterisation
    template <class Z = std::size_t, class D = std::ptrdiff_t>
    struct basic_row_major;
    typedef basic_row_major<> row_major;

    template <class Z = std::size_t, class D = std::ptrdiff_t>
    struct basic_column_major;
    typedef basic_column_major<> column_major;

    template<class T, class L = row_major, class A = unbounded_array<T> >
    class matrix;
#ifdef BOOST_UBLAS_CPP_GE_2011
    template<class T, std::size_t M, std::size_t N, class L = row_major, class A = std::array<T, M*N> >
    class fixed_matrix;
#endif
    template<class T, std::size_t M, std::size_t N, class L = row_major>
    class bounded_matrix;

    template<class T = int, class ALLOC = std::allocator<T> >
    class identity_matrix;
    template<class T = int, class ALLOC = std::allocator<T> >
    class zero_matrix;
    template<class T = int, class ALLOC = std::allocator<T> >
    class scalar_matrix;

    template<class T, std::size_t M, std::size_t N>
    class c_matrix;

    template<class T, class L = row_major, class A = unbounded_array<unbounded_array<T> > >
    class vector_of_vector;

    template<class T, class L = row_major, class A = vector<compressed_vector<T> > >
    class generalized_vector_of_vector;

    // Triangular matrix type
    struct lower_tag {};
    struct upper_tag {};
    struct unit_lower_tag : public lower_tag {};
    struct unit_upper_tag : public upper_tag {};
    struct strict_lower_tag : public lower_tag {};
    struct strict_upper_tag : public upper_tag {};

    // Triangular matrix parameterisation
    template <class Z = std::size_t>
    struct basic_full;
    typedef basic_full<> full;

    template <class Z = std::size_t>
    struct basic_lower;
    typedef basic_lower<> lower;

    template <class Z = std::size_t>
    struct basic_upper;
    typedef basic_upper<> upper;

    template <class Z = std::size_t>
    struct basic_unit_lower;
    typedef basic_unit_lower<> unit_lower;

    template <class Z = std::size_t>
    struct basic_unit_upper;
    typedef basic_unit_upper<> unit_upper;

    template <class Z = std::size_t>
    struct basic_strict_lower;
    typedef basic_strict_lower<> strict_lower;

    template <class Z = std::size_t>
    struct basic_strict_upper;
    typedef basic_strict_upper<> strict_upper;

    // Special matrices
    template<class T, class L = row_major, class A = unbounded_array<T> >
    class banded_matrix;
    template<class T, class L = row_major, class A = unbounded_array<T> >
    class diagonal_matrix;

    template<class T, class TRI = lower, class L = row_major, class A = unbounded_array<T> >
    class triangular_matrix;
    template<class M, class TRI = lower>
    class triangular_adaptor;

    template<class T, class TRI = lower, class L = row_major, class A = unbounded_array<T> >
    class symmetric_matrix;
    template<class M, class TRI = lower>
    class symmetric_adaptor;

    template<class T, class TRI = lower, class L = row_major, class A = unbounded_array<T> >
    class hermitian_matrix;
    template<class M, class TRI = lower>
    class hermitian_adaptor;

    // Sparse matrices
    template<class T, class L = row_major, class A = map_std<std::size_t, T> >
    class mapped_matrix;
    template<class T, class L = row_major, class A = map_std<std::size_t, map_std<std::size_t, T> > >
    class mapped_vector_of_mapped_vector;
    template<class T, class L = row_major, std::size_t IB = 0, class IA = unbounded_array<std::size_t>, class TA = unbounded_array<T> >
    class compressed_matrix;
    template<class T, class L = row_major, std::size_t IB = 0, class IA = unbounded_array<std::size_t>, class TA = unbounded_array<T> >
    class coordinate_matrix;

}}}

#endif

/* fwd.hpp
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
*/