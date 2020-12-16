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
eDzHrD7dmV0iIg8WA+/twGN6ciw8RsuDtWpM6nTvEyr7quP+R/DNvl83X5mG3dF6XGKnN+F8IpQUBbvDJez6xMakCOwm+8Rd8Pq8Yvso3ucMuI1D9R5xJSJ1vtJUZU0U3G6TX/xPSSfDrU/U9uEqIhv4nxEQ2cDvh0/bwEt4AwcfxNAkHWv/FnJh8rz8g1HR5+UkJb8N/aBlvldcN0Ln6p8adSa+WOxBwxB4ftQZ2BI5Aw+LOgOfnRI5A9Nmi1imQHGAMlevUb4ltF+OVYlTP6F/0xNyRD6Q9oC4dLMmzvJQz85JCGr8fVI9oL5vX6I+jyMp67+OlRc8Rzmnrbxgkqb/2BElE800YWWwnlCTFTzWQ3u5DYTGdD3OJ9IIoFbuiJYVpAJiZQUR9l3LChrzpx39ZcO6tX/el+dZ+lTR8GW9oC09JqMtfWqP/NqresTSY8z+ZOUiPa1GmVGep1P3s20oM1e4TkmZMUegMj0KKlf064gyk/4tKTPR+KboMSqCUtok1ujv8TUopa9HJ1FK+Z7Y/RkoHv0l7fvLiRieuReqe+nRgYqdUO7Bt8OrNLJyFXz8hGII1AwPXgbsJenOGCMjWvywl7GK+Qt8YkYv/Z40D+zqU+GTyOowWiHx6DFlmUhZBFF1Cq1xxEVWAD2O+EMvG6Tg9eEevlzhkuW4Dy2uIwJKgXgC09AnHAj2wpYH8QbSzU/rOLCKN3d9y58mn+KXNxGjQ6weubIYXh8NgpO43K/qSZ2tIdY3YNVYWeWt8SExABFovNqoPTLTcfkaM4FbLV0hXSN9PDSbeGiqkqIqsKCCi7QKNvMSnqpV0JnJyu8LFJBi5mx34HzxYDcc4qx80C1wRA6618pF59Ju+oTi5w5wK55cIO7qHnnV6IJVkh99tNxKcIETGOyFspg53XTWur4Fk4QSyYGnR5u4LGTu6i0QF8uECEIlncEPYn+xiA31DwIYFXtxRhVPdJXYZWuLhaAZbFL9vfnizwj1iBqnfGOu1eI/L9d9ZPHflE/1AVCIeqLMlGPg7mosvPQyxKmediD91/bgEpNJuzIFo4CvsFiOa6K4pgvkVhdJn1VtFePhJ/hOphcfMFW84GRUK+sRDRAY7hFTu1NTi7rr86W/o3blZsSGbLdqrurKJ2Evt/ULNuJZveSirbNCS7STW2imbXrjZXbLzIbCxVxlvmi2o/4l2sbwLHlK9E8+XXZ3chdmOEZ3p38j7gKG5yjFaxeJufY2StcW2Jri+dA8GeHoeVOujbyNuXasUR2VtyrBQjnFNV0lOzY8di2juKQrc7c3oQDy3iu/l8bh3pSbKP8kh/HDsT18Cq3/+dWgz5TvDZyHDT2RBMz26S1X/kKukBymQXb9wfUG7cGS0bPsjkrasR21x5T39Uw1k8xb91s8GIYuNAkEoQwfBhL43faWwcoHUelC53uoi+8kSoY4cDRgUn5kMialXvWfEtpMSkdtrj0nBJHmppuJvt00sUKqrrPZTTnupsUfL5+FR1aJ8OyofSmUuAqlghWaOFiWJ1pqxpmnEy7lqAX1XAbVffOnS75mf5kwROrTduIhXtq/+xiS6X+lDlbLnu2J13vGyzeNazoIqstXYREsxfMJ1gUuJdXISbffB8tlVIoZUYOMqGco6seIqka/ynfiLQFQ7u0Lh6v4ODtV23LiT/OI1+O1zcSfrlxg5K2nvMOt8A4zwnZQWD+E0exOxwc8V7nIiHw2qgc9ZA/AmTOLu+BTRuvpCp1iapzcFBPlK+sYB7cRO04v4tk44/NqhVQDKVmeADtNGY80yyeZ4R4mGROWT7KIo8hBhU4i7Brz+vLeKPQyoqEkwPJiGz2oXQ0vtJfSe/U=
*/