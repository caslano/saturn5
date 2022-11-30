/*
 [auto_generated]
 boost/numeric/odeint/util/ublas_wrapper.hpp

 [begin_description]
 Resizing for ublas::vector and ublas::matrix
 [end_description]

 Copyright 2011-2013 Mario Mulansky
 Copyright 2011-2013 Karsten Ahnert

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_UTIL_UBLAS_WRAPPER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_UTIL_UBLAS_WRAPPER_HPP_INCLUDED


#include <boost/type_traits/integral_constant.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/vector_expression.hpp>
#include <boost/numeric/ublas/matrix_expression.hpp>

#include <boost/numeric/odeint/algebra/vector_space_algebra.hpp>
#include <boost/numeric/odeint/algebra/default_operations.hpp>

#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/state_wrapper.hpp>


/* extend ublas by a few operations */

/* map norm_inf onto reduce( v , default_operations::maximum ) */
namespace boost { namespace numeric { namespace odeint {

    template< typename T , typename A >
    struct vector_space_norm_inf< boost::numeric::ublas::vector<T,A> >
    {
        typedef T result_type;

        result_type operator()( const boost::numeric::ublas::vector<T,A> &x ) const
        {
            return boost::numeric::ublas::norm_inf( x );
        }
    };


    template< class T , class L , class A >
    struct vector_space_norm_inf< boost::numeric::ublas::matrix<T,L,A> >
    {
        typedef T result_type;

        result_type operator()( const boost::numeric::ublas::matrix<T,L,A> &x ) const
        {
            return boost::numeric::ublas::norm_inf( x );
        }
    };
} } }

/* additional operations:
 * abs( v )
 * v / w
 * a + v
 */
namespace boost { namespace numeric { namespace ublas {


    // elementwise abs - calculates absolute values of the elements
    template<class T>
    struct scalar_abs: public scalar_unary_functor<T> {
        typedef typename scalar_unary_functor<T>::value_type value_type;
        typedef typename scalar_unary_functor<T>::argument_type argument_type;
        typedef typename scalar_unary_functor<T>::result_type result_type;

        static BOOST_UBLAS_INLINE
        result_type apply (argument_type t) {
            using std::abs;
            return abs (t);
        }
    };


    // (abs v) [i] = abs (v [i])
    template<class E>
    BOOST_UBLAS_INLINE
    typename vector_unary_traits<E, scalar_abs<typename E::value_type> >::result_type
    abs (const vector_expression<E> &e) {
        typedef typename vector_unary_traits<E, scalar_abs<typename E::value_type> >::expression_type expression_type;
        return expression_type (e ());
    }

    // (abs m) [i] = abs (m [i])
    template<class E>
    BOOST_UBLAS_INLINE
    typename matrix_unary1_traits<E, scalar_abs<typename E::value_type> >::result_type
    abs (const matrix_expression<E> &e) {
        typedef typename matrix_unary1_traits<E, scalar_abs<typename E::value_type> >::expression_type expression_type;
        return expression_type (e ());
    }


    // elementwise division (v1 / v2) [i] = v1 [i] / v2 [i]
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    typename vector_binary_traits<E1, E2, scalar_divides<typename E1::value_type,
                                                         typename E2::value_type> >::result_type
    operator / (const vector_expression<E1> &e1,
                const vector_expression<E2> &e2) {
        typedef typename vector_binary_traits<E1, E2, scalar_divides<typename E1::value_type,
                                                                     typename E2::value_type> >::expression_type expression_type;
        return expression_type (e1 (), e2 ());
    }


    // elementwise division (m1 / m2) [i] = m1 [i] / m2 [i]
    template<class E1, class E2>
    BOOST_UBLAS_INLINE
    typename matrix_binary_traits<E1, E2, scalar_divides<typename E1::value_type,
    typename E2::value_type> >::result_type
    operator / (const matrix_expression<E1> &e1,
                const matrix_expression<E2> &e2) {
        typedef typename matrix_binary_traits<E1, E2, scalar_divides<typename E1::value_type,
                                                                     typename E2::value_type> >::expression_type expression_type;
        return expression_type (e1 (), e2 ());
    }

    // addition with scalar
    // (t + v) [i] = t + v [i]
    template<class T1, class E2>
    BOOST_UBLAS_INLINE
    typename enable_if< is_convertible<T1, typename E2::value_type >,
    typename vector_binary_scalar1_traits<const T1, E2, scalar_plus<T1, typename E2::value_type> >::result_type
    >::type
    operator + (const T1 &e1,
                const vector_expression<E2> &e2) {
        typedef typename vector_binary_scalar1_traits<const T1, E2, scalar_plus<T1, typename E2::value_type> >::expression_type expression_type;
        return expression_type (e1, e2 ());
    }

    // addition with scalar
    // (t + m) [i] = t + m [i]
    template<class T1, class E2>
    BOOST_UBLAS_INLINE
    typename enable_if< is_convertible<T1, typename E2::value_type >,
    typename matrix_binary_scalar1_traits<const T1, E2, scalar_plus<T1, typename E2::value_type> >::result_type
    >::type
    operator + (const T1 &e1,
                const matrix_expression<E2> &e2) {
        typedef typename matrix_binary_scalar1_traits<const T1, E2, scalar_plus<T1, typename E2::value_type> >::expression_type expression_type;
        return expression_type (e1, e2 ());
    }

} } }




/* add resize functionality */
namespace boost {
namespace numeric {
namespace odeint {

/*
 * resizeable specialization for boost::numeric::ublas::vector
 */
template< class T , class A >
struct is_resizeable< boost::numeric::ublas::vector< T , A > >
{
    typedef boost::true_type type;
    const static bool value = type::value;
};


/*
 * resizeable specialization for boost::numeric::ublas::matrix
 */
template< class T , class L , class A >
struct is_resizeable< boost::numeric::ublas::matrix< T , L , A > >
{
    typedef boost::true_type type;
    const static bool value = type::value;
};


/*
 * resizeable specialization for boost::numeric::ublas::permutation_matrix
 */
template< class T , class A >
struct is_resizeable< boost::numeric::ublas::permutation_matrix< T , A > >
{
    typedef boost::true_type type;
    const static bool value = type::value;
};


// specialization for ublas::matrix
// same size and resize specialization for matrix-matrix resizing
template< class T , class L , class A , class T2 , class L2 , class A2 >
struct same_size_impl< boost::numeric::ublas::matrix< T , L , A > , boost::numeric::ublas::matrix< T2 , L2 , A2 > >
{
    static bool same_size( const boost::numeric::ublas::matrix< T , L , A > &m1 ,
                           const boost::numeric::ublas::matrix< T2 , L2 , A2 > &m2 )
    {
        return ( ( m1.size1() == m2.size1() ) && ( m1.size2() == m2.size2() ) );
    }
};

template< class T , class L , class A , class T2 , class L2 , class A2 >
struct resize_impl< boost::numeric::ublas::matrix< T , L , A > , boost::numeric::ublas::matrix< T2 , L2 , A2 > >
{
    static void resize( boost::numeric::ublas::matrix< T , L , A > &m1 ,
                        const boost::numeric::ublas::matrix< T2 , L2 , A2 > &m2 )
    {
        m1.resize( m2.size1() , m2.size2() );
    }
};



// same size and resize specialization for matrix-vector resizing
template< class T , class L , class A , class T_V , class A_V >
struct same_size_impl< boost::numeric::ublas::matrix< T , L , A > , boost::numeric::ublas::vector< T_V , A_V > >
{
    static bool same_size( const boost::numeric::ublas::matrix< T , L , A > &m ,
                           const boost::numeric::ublas::vector< T_V , A_V > &v )
    {
        return ( ( m.size1() == v.size() ) && ( m.size2() == v.size() ) );
    }
};

template< class T , class L , class A , class T_V , class A_V >
struct resize_impl< boost::numeric::ublas::matrix< T , L , A > , boost::numeric::ublas::vector< T_V , A_V > >
{
    static void resize( boost::numeric::ublas::matrix< T , L , A > &m ,
                        const boost::numeric::ublas::vector< T_V , A_V > &v )
    {
        m.resize( v.size() , v.size() );
    }
};



// specialization for ublas::permutation_matrix
// same size and resize specialization for matrix-vector resizing
template< class T , class A , class T_V , class A_V >
struct same_size_impl< boost::numeric::ublas::permutation_matrix< T , A > ,
                       boost::numeric::ublas::vector< T_V , A_V > >
{
    static bool same_size( const boost::numeric::ublas::permutation_matrix< T , A > &m ,
                           const boost::numeric::ublas::vector< T_V , A_V > &v )
    {
        return ( m.size() == v.size() ); // && ( m.size2() == v.size() ) );
    }
};

template< class T , class A , class T_V , class A_V >
struct resize_impl< boost::numeric::ublas::vector< T_V , A_V > ,
                    boost::numeric::ublas::permutation_matrix< T , A > >
{
    static void resize( const boost::numeric::ublas::vector< T_V , A_V > &v,
                        boost::numeric::ublas::permutation_matrix< T , A > &m )
    {
        m.resize( v.size() , v.size() );
    }
};







template< class T , class A >
struct state_wrapper< boost::numeric::ublas::permutation_matrix< T , A > > // with resizing
{
    typedef boost::numeric::ublas::permutation_matrix< T , A > state_type;
    typedef state_wrapper< state_type > state_wrapper_type;

    state_type m_v;

    state_wrapper() : m_v( 1 ) // permutation matrix constructor requires a size, choose 1 as default
    { }

};




} } }


#endif // BOOST_NUMERIC_ODEINT_UTIL_UBLAS_WRAPPER_HPP_INCLUDED

/* ublas_wrapper.hpp
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
*/