//
//  Copyright (c) 2002-2003
//  Toon Knapen, Kresimir Fresl, Joerg Walter
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//

#ifndef _BOOST_UBLAS_RAW_
#define _BOOST_UBLAS_RAW_

namespace boost { namespace numeric { namespace ublas { namespace raw {

    // We need data_const() mostly due to MSVC 6.0.
    // But how shall we write portable code otherwise?

    template < typename V >
    BOOST_UBLAS_INLINE
    int size( const V &v ) ;

    template < typename V >
    BOOST_UBLAS_INLINE
    int size( const vector_reference<V> &v ) ;

    template < typename M >
    BOOST_UBLAS_INLINE
    int size1( const M &m ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    int size2( const M &m ) ;

    template < typename M >
    BOOST_UBLAS_INLINE
    int size1( const matrix_reference<M> &m ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    int size2( const matrix_reference<M> &m ) ;

    template < typename M >
    BOOST_UBLAS_INLINE
    int leading_dimension( const M &m, row_major_tag ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    int leading_dimension( const M &m, column_major_tag ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    int leading_dimension( const M &m ) ;

    template < typename M >
    BOOST_UBLAS_INLINE
    int leading_dimension( const matrix_reference<M> &m ) ;

    template < typename V >
    BOOST_UBLAS_INLINE
    int stride( const V &v ) ;

    template < typename V >
    BOOST_UBLAS_INLINE
    int stride( const vector_range<V> &v ) ;
    template < typename V >
    BOOST_UBLAS_INLINE
    int stride( const vector_slice<V> &v ) ;

    template < typename M >
    BOOST_UBLAS_INLINE
    int stride( const matrix_row<M> &v ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    int stride( const matrix_column<M> &v ) ;

    template < typename M >
    BOOST_UBLAS_INLINE
    int stride1( const M &m ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    int stride2( const M &m ) ;

    template < typename M >
    BOOST_UBLAS_INLINE
    int stride1( const matrix_reference<M> &m ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    int stride2( const matrix_reference<M> &m ) ;

    template < typename T, std::size_t M, std::size_t N >
    BOOST_UBLAS_INLINE
    int stride1( const c_matrix<T, M, N> &m ) ;
    template < typename T, std::size_t M, std::size_t N >
    BOOST_UBLAS_INLINE
    int stride2( const c_matrix<T, M, N> &m ) ;

    template < typename M >
    BOOST_UBLAS_INLINE
    int stride1( const matrix_range<M> &m ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    int stride1( const matrix_slice<M> &m ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    int stride2( const matrix_range<M> &m ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    int stride2( const matrix_slice<M> &m ) ;

    template < typename MV >
    BOOST_UBLAS_INLINE
    typename MV::array_type::array_type::const_pointer data( const MV &mv ) ;
    template < typename MV >
    BOOST_UBLAS_INLINE
    typename MV::array_type::array_type::const_pointer data_const( const MV &mv ) ;
    template < typename MV >
    BOOST_UBLAS_INLINE
    typename MV::array_type::pointer data( MV &mv ) ;

    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::array_type::const_pointer data( const vector_reference<V> &v ) ;
    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::array_type::const_pointer data_const( const vector_reference<V> &v ) ;
    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::pointer data( vector_reference<V> &v ) ;

    template < typename T, std::size_t N >
    BOOST_UBLAS_INLINE
    typename c_vector<T, N>::array_type::array_type::const_pointer data( const c_vector<T, N> &v ) ;
    template < typename T, std::size_t N >
    BOOST_UBLAS_INLINE
    typename c_vector<T, N>::array_type::array_type::const_pointer data_const( const c_vector<T, N> &v ) ;
    template < typename T, std::size_t N >
    BOOST_UBLAS_INLINE
    typename c_vector<T, N>::pointer data( c_vector<T, N> &v ) ;

    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::array_type::const_pointer data( const vector_range<V> &v ) ;
    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::array_type::const_pointer data( const vector_slice<V> &v ) ;
    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::array_type::const_pointer data_const( const vector_range<V> &v ) ;
    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::array_type::const_pointer data_const( const vector_slice<V> &v ) ;
    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::pointer data( vector_range<V> &v ) ;
    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::pointer data( vector_slice<V> &v ) ;

    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::array_type::const_pointer data( const matrix_reference<M> &m ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::array_type::const_pointer data_const( const matrix_reference<M> &m ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::pointer data( matrix_reference<M> &m ) ;

    template < typename T, std::size_t M, std::size_t N >
    BOOST_UBLAS_INLINE
    typename c_matrix<T, M, N>::array_type::array_type::const_pointer data( const c_matrix<T, M, N> &m ) ;
    template < typename T, std::size_t M, std::size_t N >
    BOOST_UBLAS_INLINE
    typename c_matrix<T, M, N>::array_type::array_type::const_pointer data_const( const c_matrix<T, M, N> &m ) ;
    template < typename T, std::size_t M, std::size_t N >
    BOOST_UBLAS_INLINE
    typename c_matrix<T, M, N>::pointer data( c_matrix<T, M, N> &m ) ;

    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::array_type::const_pointer data( const matrix_row<M> &v ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::array_type::const_pointer data( const matrix_column<M> &v ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::array_type::const_pointer data_const( const matrix_row<M> &v ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::array_type::const_pointer data_const( const matrix_column<M> &v ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::pointer data( matrix_row<M> &v ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::pointer data( matrix_column<M> &v ) ;

    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::array_type::const_pointer data( const matrix_range<M> &m ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::array_type::const_pointer data( const matrix_slice<M> &m ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::array_type::const_pointer data_const( const matrix_range<M> &m ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::array_type::const_pointer data_const( const matrix_slice<M> &m ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::pointer data( matrix_range<M> &m ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::pointer data( matrix_slice<M> &m ) ;

    template < typename MV >
    BOOST_UBLAS_INLINE
    typename MV::array_type::array_type::const_pointer base( const MV &mv ) ;

    template < typename MV >
    BOOST_UBLAS_INLINE
    typename MV::array_type::array_type::const_pointer base_const( const MV &mv ) ;
    template < typename MV >
    BOOST_UBLAS_INLINE
    typename MV::array_type::pointer base( MV &mv ) ;

    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::array_type::const_pointer base( const vector_reference<V> &v ) ;
    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::array_type::const_pointer base_const( const vector_reference<V> &v ) ;
    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::pointer base( vector_reference<V> &v ) ;

    template < typename T, std::size_t N >
    BOOST_UBLAS_INLINE
    typename c_vector<T, N>::array_type::array_type::const_pointer base( const c_vector<T, N> &v ) ;
    template < typename T, std::size_t N >
    BOOST_UBLAS_INLINE
    typename c_vector<T, N>::array_type::array_type::const_pointer base_const( const c_vector<T, N> &v ) ;
    template < typename T, std::size_t N >
    BOOST_UBLAS_INLINE
    typename c_vector<T, N>::pointer base( c_vector<T, N> &v ) ;

    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::array_type::const_pointer base( const vector_range<V> &v ) ;
    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::array_type::const_pointer base( const vector_slice<V> &v ) ;
    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::array_type::const_pointer base_const( const vector_range<V> &v ) ;
    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::array_type::const_pointer base_const( const vector_slice<V> &v ) ;
    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::pointer base( vector_range<V> &v ) ;
    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::pointer base( vector_slice<V> &v ) ;

    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::array_type::const_pointer base( const matrix_reference<M> &m ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::array_type::const_pointer base_const( const matrix_reference<M> &m ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::pointer base( matrix_reference<M> &m ) ;

    template < typename T, std::size_t M, std::size_t N >
    BOOST_UBLAS_INLINE
    typename c_matrix<T, M, N>::array_type::array_type::const_pointer base( const c_matrix<T, M, N> &m ) ;
    template < typename T, std::size_t M, std::size_t N >
    BOOST_UBLAS_INLINE
    typename c_matrix<T, M, N>::array_type::array_type::const_pointer base_const( const c_matrix<T, M, N> &m ) ;
    template < typename T, std::size_t M, std::size_t N >
    BOOST_UBLAS_INLINE
    typename c_matrix<T, M, N>::pointer base( c_matrix<T, M, N> &m ) ;

    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::array_type::const_pointer base( const matrix_row<M> &v ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::array_type::const_pointer base( const matrix_column<M> &v ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::array_type::const_pointer base_const( const matrix_row<M> &v ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::array_type::const_pointer base_const( const matrix_column<M> &v ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::pointer base( matrix_row<M> &v ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::pointer base( matrix_column<M> &v ) ;

    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::array_type::const_pointer base( const matrix_range<M> &m ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::array_type::const_pointer base( const matrix_slice<M> &m ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::array_type::const_pointer base_const( const matrix_range<M> &m ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::array_type::const_pointer base_const( const matrix_slice<M> &m ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::pointer base( matrix_range<M> &m ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::pointer base( matrix_slice<M> &m ) ;

    template < typename MV >
    BOOST_UBLAS_INLINE
    typename MV::size_type start( const MV &mv ) ;

    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::size_type start( const vector_range<V> &v ) ;
    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::size_type start( const vector_slice<V> &v ) ;

    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::size_type start( const matrix_row<M> &v ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::size_type start( const matrix_column<M> &v ) ;

    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::size_type start( const matrix_range<M> &m ) ;
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::size_type start( const matrix_slice<M> &m ) ;



    template < typename V >
    BOOST_UBLAS_INLINE
    int size( const V &v ) {
        return v.size() ;
    }

    template < typename V >
    BOOST_UBLAS_INLINE
    int size( const vector_reference<V> &v ) {
        return size( v ) ;
    }

    template < typename M >
    BOOST_UBLAS_INLINE
    int size1( const M &m ) {
        return m.size1() ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    int size2( const M &m ) {
        return m.size2() ;
    }

    template < typename M >
    BOOST_UBLAS_INLINE
    int size1( const matrix_reference<M> &m ) {
        return size1( m.expression() ) ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    int size2( const matrix_reference<M> &m ) {
        return size2( m.expression() ) ;
    }

    template < typename M >
    BOOST_UBLAS_INLINE
    int leading_dimension( const M &m, row_major_tag ) {
        return m.size2() ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    int leading_dimension( const M &m, column_major_tag ) {
        return m.size1() ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    int leading_dimension( const M &m ) {
        return leading_dimension( m, typename M::orientation_category() ) ;
    }

    template < typename M >
    BOOST_UBLAS_INLINE
    int leading_dimension( const matrix_reference<M> &m ) {
        return leading_dimension( m.expression() ) ;
    }

    template < typename V >
    BOOST_UBLAS_INLINE
    int stride( const V &v ) {
        return 1 ;
    }

    template < typename V >
    BOOST_UBLAS_INLINE
    int stride( const vector_range<V> &v ) {
        return stride( v.data() ) ;
    }
    template < typename V >
    BOOST_UBLAS_INLINE
    int stride( const vector_slice<V> &v ) {
        return v.stride() * stride( v.data() ) ;
    }

    template < typename M >
    BOOST_UBLAS_INLINE
    int stride( const matrix_row<M> &v ) {
        return stride2( v.data() ) ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    int stride( const matrix_column<M> &v ) {
        return stride1( v.data() ) ;
    }

    template < typename M >
    BOOST_UBLAS_INLINE
    int stride1( const M &m ) {
        typedef typename M::functor_type functor_type;
        return functor_type::one1( m.size1(), m.size2() ) ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    int stride2( const M &m ) {
        typedef typename M::functor_type functor_type;
        return functor_type::one2( m.size1(), m.size2() ) ;
    }

    template < typename M >
    BOOST_UBLAS_INLINE
    int stride1( const matrix_reference<M> &m ) {
        return stride1( m.expression() ) ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    int stride2( const matrix_reference<M> &m ) {
        return stride2( m.expression() ) ;
    }

    template < typename T, std::size_t M, std::size_t N >
    BOOST_UBLAS_INLINE
    int stride1( const c_matrix<T, M, N> &m ) {
        return N ;
    }
    template < typename T, std::size_t M, std::size_t N >
    BOOST_UBLAS_INLINE
    int stride2( const c_matrix<T, M, N> &m ) {
        return 1 ;
    }

    template < typename M >
    BOOST_UBLAS_INLINE
    int stride1( const matrix_range<M> &m ) {
        return stride1( m.data() ) ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    int stride1( const matrix_slice<M> &m ) {
        return m.stride1() * stride1( m.data() ) ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    int stride2( const matrix_range<M> &m ) {
        return stride2( m.data() ) ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    int stride2( const matrix_slice<M> &m ) {
        return m.stride2() * stride2( m.data() ) ;
    }

    template < typename MV >
    BOOST_UBLAS_INLINE
    typename MV::array_type::array_type::array_type::const_pointer data( const MV &mv ) {
        return &mv.data().begin()[0] ;
    }
    template < typename MV >
    BOOST_UBLAS_INLINE
    typename MV::array_type::array_type::const_pointer data_const( const MV &mv ) {
        return &mv.data().begin()[0] ;
    }
    template < typename MV >
    BOOST_UBLAS_INLINE
    typename MV::array_type::pointer data( MV &mv ) {
        return &mv.data().begin()[0] ;
    }


    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::array_type::const_pointer data( const vector_reference<V> &v ) {
        return data( v.expression () ) ;
    }
    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::array_type::const_pointer data_const( const vector_reference<V> &v ) {
        return data_const( v.expression () ) ;
    }
    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::pointer data( vector_reference<V> &v ) {
        return data( v.expression () ) ;
    }

    template < typename T, std::size_t N >
    BOOST_UBLAS_INLINE
    typename c_vector<T, N>::array_type::array_type::const_pointer data( const c_vector<T, N> &v ) {
        return v.data() ;
    }
    template < typename T, std::size_t N >
    BOOST_UBLAS_INLINE
    typename c_vector<T, N>::array_type::array_type::const_pointer data_const( const c_vector<T, N> &v ) {
        return v.data() ;
    }
    template < typename T, std::size_t N >
    BOOST_UBLAS_INLINE
    typename c_vector<T, N>::pointer data( c_vector<T, N> &v ) {
        return v.data() ;
    }

    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::array_type::const_pointer data( const vector_range<V> &v ) {
        return data( v.data() ) + v.start() * stride (v.data() ) ;
    }
    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::array_type::const_pointer data( const vector_slice<V> &v ) {
        return data( v.data() ) + v.start() * stride (v.data() ) ;
    }
    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::array_type::const_pointer data_const( const vector_range<V> &v ) {
        return data_const( v.data() ) + v.start() * stride (v.data() ) ;
    }
    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::const_pointer data_const( const vector_slice<V> &v ) {
        return data_const( v.data() ) + v.start() * stride (v.data() ) ;
    }
    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::pointer data( vector_range<V> &v ) {
        return data( v.data() ) + v.start() * stride (v.data() ) ;
    }
    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::pointer data( vector_slice<V> &v ) {
        return data( v.data() ) + v.start() * stride (v.data() ) ;
    }

    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::const_pointer data( const matrix_reference<M> &m ) {
        return data( m.expression () ) ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::const_pointer data_const( const matrix_reference<M> &m ) {
        return data_const( m.expression () ) ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::pointer data( matrix_reference<M> &m ) {
        return data( m.expression () ) ;
    }

    template < typename T, std::size_t M, std::size_t N >
    BOOST_UBLAS_INLINE
    typename c_matrix<T, M, N>::array_type::const_pointer data( const c_matrix<T, M, N> &m ) {
        return m.data() ;
    }
    template < typename T, std::size_t M, std::size_t N >
    BOOST_UBLAS_INLINE
    typename c_matrix<T, M, N>::array_type::const_pointer data_const( const c_matrix<T, M, N> &m ) {
        return m.data() ;
    }
    template < typename T, std::size_t M, std::size_t N >
    BOOST_UBLAS_INLINE
    typename c_matrix<T, M, N>::pointer data( c_matrix<T, M, N> &m ) {
        return m.data() ;
    }

    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::const_pointer data( const matrix_row<M> &v ) {
        return data( v.data() ) + v.index() * stride1( v.data() ) ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::const_pointer data( const matrix_column<M> &v ) {
        return data( v.data() ) + v.index() * stride2( v.data() ) ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::const_pointer data_const( const matrix_row<M> &v ) {
        return data_const( v.data() ) + v.index() * stride1( v.data() ) ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::const_pointer data_const( const matrix_column<M> &v ) {
        return data_const( v.data() ) + v.index() * stride2( v.data() ) ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::pointer data( matrix_row<M> &v ) {
        return data( v.data() ) + v.index() * stride1( v.data() ) ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::pointer data( matrix_column<M> &v ) {
        return data( v.data() ) + v.index() * stride2( v.data() ) ;
    }

    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::const_pointer data( const matrix_range<M> &m ) {
        return data( m.data() ) + m.start1() * stride1( m.data () ) + m.start2() * stride2( m.data () ) ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::const_pointer data( const matrix_slice<M> &m ) {
        return data( m.data() ) + m.start1() * stride1( m.data () ) + m.start2() * stride2( m.data () ) ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::const_pointer data_const( const matrix_range<M> &m ) {
        return data_const( m.data() ) + m.start1() * stride1( m.data () ) + m.start2() * stride2( m.data () ) ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::const_pointer data_const( const matrix_slice<M> &m ) {
        return data_const( m.data() ) + m.start1() * stride1( m.data () ) + m.start2() * stride2( m.data () ) ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::pointer data( matrix_range<M> &m ) {
        return data( m.data() ) + m.start1() * stride1( m.data () ) + m.start2() * stride2( m.data () ) ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::pointer data( matrix_slice<M> &m ) {
        return data( m.data() ) + m.start1() * stride1( m.data () ) + m.start2() * stride2( m.data () ) ;
    }


    template < typename MV >
    BOOST_UBLAS_INLINE
    typename MV::array_type::const_pointer base( const MV &mv ) {
        return &mv.data().begin()[0] ;
    }
    template < typename MV >
    BOOST_UBLAS_INLINE
    typename MV::array_type::const_pointer base_const( const MV &mv ) {
        return &mv.data().begin()[0] ;
    }
    template < typename MV >
    BOOST_UBLAS_INLINE
    typename MV::array_type::pointer base( MV &mv ) {
        return &mv.data().begin()[0] ;
    }

    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::const_pointer base( const vector_reference<V> &v ) {
        return base( v.expression () ) ;
    }
    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::const_pointer base_const( const vector_reference<V> &v ) {
        return base_const( v.expression () ) ;
    }
    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::pointer base( vector_reference<V> &v ) {
        return base( v.expression () ) ;
    }

    template < typename T, std::size_t N >
    BOOST_UBLAS_INLINE
    typename c_vector<T, N>::array_type::const_pointer base( const c_vector<T, N> &v ) {
        return v.data() ;
    }
    template < typename T, std::size_t N >
    BOOST_UBLAS_INLINE
    typename c_vector<T, N>::array_type::const_pointer base_const( const c_vector<T, N> &v ) {
        return v.data() ;
    }
    template < typename T, std::size_t N >
    BOOST_UBLAS_INLINE
    typename c_vector<T, N>::pointer base( c_vector<T, N> &v ) {
        return v.data() ;
    }

    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::const_pointer base( const vector_range<V> &v ) {
        return base( v.data() ) ;
    }
    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::const_pointer base( const vector_slice<V> &v ) {
        return base( v.data() ) ;
    }
    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::const_pointer base_const( const vector_range<V> &v ) {
        return base_const( v.data() ) ;
    }
    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::const_pointer base_const( const vector_slice<V> &v ) {
        return base_const( v.data() ) ;
    }
    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::pointer base( vector_range<V> &v ) {
        return base( v.data() ) ;
    }
    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::array_type::pointer base( vector_slice<V> &v ) {
        return base( v.data() ) ;
    }

    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::const_pointer base( const matrix_reference<M> &m ) {
        return base( m.expression () ) ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::const_pointer base_const( const matrix_reference<M> &m ) {
        return base_const( m.expression () ) ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::pointer base( matrix_reference<M> &m ) {
        return base( m.expression () ) ;
    }

    template < typename T, std::size_t M, std::size_t N >
    BOOST_UBLAS_INLINE
    typename c_matrix<T, M, N>::array_type::const_pointer base( const c_matrix<T, M, N> &m ) {
        return m.data() ;
    }
    template < typename T, std::size_t M, std::size_t N >
    BOOST_UBLAS_INLINE
    typename c_matrix<T, M, N>::array_type::const_pointer base_const( const c_matrix<T, M, N> &m ) {
        return m.data() ;
    }
    template < typename T, std::size_t M, std::size_t N >
    BOOST_UBLAS_INLINE
    typename c_matrix<T, M, N>::pointer base( c_matrix<T, M, N> &m ) {
        return m.data() ;
    }

    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::const_pointer base( const matrix_row<M> &v ) {
        return base( v.data() ) ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::const_pointer base( const matrix_column<M> &v ) {
        return base( v.data() ) ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::const_pointer base_const( const matrix_row<M> &v ) {
        return base_const( v.data() ) ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::const_pointer base_const( const matrix_column<M> &v ) {
        return base_const( v.data() ) ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::pointer base( matrix_row<M> &v ) {
        return base( v.data() ) ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::pointer base( matrix_column<M> &v ) {
        return base( v.data() ) ;
    }

    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::const_pointer base( const matrix_range<M> &m ) {
        return base( m.data() ) ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::const_pointer base( const matrix_slice<M> &m ) {
        return base( m.data() ) ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::const_pointer base_const( const matrix_range<M> &m ) {
        return base_const( m.data() ) ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::const_pointer base_const( const matrix_slice<M> &m ) {
        return base_const( m.data() ) ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::pointer base( matrix_range<M> &m ) {
        return base( m.data() ) ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::array_type::pointer base( matrix_slice<M> &m ) {
        return base( m.data() ) ;
    }

    template < typename MV >
    BOOST_UBLAS_INLINE
    typename MV::size_type start( const MV &mv ) {
        return 0 ;
    }

    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::size_type start( const vector_range<V> &v ) {
        return v.start() * stride (v.data() ) ;
    }
    template < typename V >
    BOOST_UBLAS_INLINE
    typename V::size_type start( const vector_slice<V> &v ) {
        return v.start() * stride (v.data() ) ;
    }

    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::size_type start( const matrix_row<M> &v ) {
        return v.index() * stride1( v.data() ) ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::size_type start( const matrix_column<M> &v ) {
        return v.index() * stride2( v.data() ) ;
    }

    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::size_type start( const matrix_range<M> &m ) {
        return m.start1() * stride1( m.data () ) + m.start2() * stride2( m.data () ) ;
    }
    template < typename M >
    BOOST_UBLAS_INLINE
    typename M::size_type start( const matrix_slice<M> &m ) {
        return m.start1() * stride1( m.data () ) + m.start2() * stride2( m.data () ) ;
    }

}}}}

#endif

/* raw.hpp
CXUqKe2Tuksc9JW7E5VkopvEkKx6nDQE2CXxadXft61nyf2zfif3b9kn92+1sRPmP3ko5J2AZzIpN3fiBFEUTDF+EuykG6TNlAR/EycZHuIUCfaWX9rwu6y0rCS+06osKysVdXy9SzQDPSwzs57F62fMvnK+6hur552AD3Jy5zDgzjyHYX2+mDL7Opfv6OtOn2nmwl8uzP7B3rXASVWV8XN3Z2VB1BEQQVGvJromKE8FFOOxi6ALbLugkNg4uzO7O7K7M83MwmKWmKiYWFhYWpSoVKaUWlb0JqPEpDIjpaI0o7LynZWZZv/zncc9c/ae3Zmhfr8ee3/77Zzzne//nff73HNf4jz5VINmgRd9NeCN4OtTFo8blknedZI3CtQueTdGxU4tX8zKgxeRvArYa0CXKx7MlTwcoPXgPfM34lHYeMZtNPRVwc5nGHeC94qUOwh0Nmg7yQneIFA9aHfAo3g1gPYb+gbzuIJeBm+IlBvC48rj3BVgD5bnbk4MeGRfwsPdFeg7hKcJ19kl9HkynaatjESHyzS6hOvvivxb9g5wsCeHlSF1vilm2ltSmfZkFvxkjvNiqYTAdMZzeSzArkyuEXYYYvFsG5nzqc6k+k1354mXSXItpp5YSxpfTurJ6zCkWtdgxTPX3cFZ+Y4c3GLt6Vy+Kw51pCO3EjgcTUrl18TaU10EtfgswOZTLStR/luTPBxK3nIXcUx3ZlTEctlMrBtLZcrT1o54W47R+nmsqa6pacHiRbHZTYsm9l2fkIjxXJe5CN/AwwlaC9oRHEegdfnWdNYX8fdb4h0dzXGEq1/9LVjOM/QTi85tBXZxZkvYx+ZOH8vjcTKWIRc31C3i8ald0Bjj6/E1J7Xke8b5JytdF4iwJLPZdHYGx46fNDnnj8355/fMHDt+Ws6f3Y3fKTm/rqsFhuk5f2G8hThDCk5LHSePrY2jeinqYTXXJ8v3CVTP6aH6dIcn0uduTyh4vkIoeLFCKDitUigYXCkUXFEpFFxdKRSsrRQJfE0lhYDsUMDtpOCH+OUKXq2EK+eQK0HJfEqlCN/plSJ8WypE+G6rEOF6rFKE65FKAXwcv/yhJObhrxC/t1cI/YdEhN5D8Y87HRYReqIRoefwiPB7WET4Ozwi/BsREf4fERF6Rkr3IyV/lNQ3WsofJfUeLfWNkf4ew//xtvDqwnbjCdznzIp8NplYSu7inzuvLq69CtO5g2MpmUp/dhGWp1HpzyMHgN17ANh9hOX5Vvqz/wCwzxwA9mWOpRpV+vMax1LdK/2pvgZYquqlPyM4tsyC5QNbah1QT43AlrX5P0Fgywr2NIktp1zOOgBsrcSWU7bqJbacsrXkALArJLacfEoAW04bSeMXiS2nTF9uYLew0p51EltOPdxwTdDW/b2E/oT6owPAbpLYSBnYzQeA3XpN+f3gNon1yqi/96q0KqMe3a/iWwb2axK7q9QA49lxAO3kToktp93ZLbHltDuPSGw5bcceiS2n7djHsWV6vP8AyuQztr+R4lPrZQs7q6H4QvKahV27pfgcjlxbiN3xQiUr9qm2sFg4KPqJ2tgdxfs7ysay4rEnKmwZnf8Uji2zItUCW2aQWQPHllmgVwhsWVG+RGDLinL7AWA7JLacdicfgq0uMsJrJbacdme9xJbTdmw0sKWOWW4OsCVXiS0OrFcE9s4DwN7vwFYWgd1xbXHz37CytrNIbFhZ210kNqxm7rm2uLWCMA/2SWyFRfYzKoT3ioH1SsQOPAPPwPPf8cyur8cZ5YUN9XUL6xYtWTwPduKbvNq6ebOX1i8R+wrYDKPfutr59IsNMv4LG3h1c8XvXOIKG+zYBlRYYVQyZCMdmo8=
*/