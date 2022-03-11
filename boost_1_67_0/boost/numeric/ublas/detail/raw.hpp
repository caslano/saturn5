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
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
*/