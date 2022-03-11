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