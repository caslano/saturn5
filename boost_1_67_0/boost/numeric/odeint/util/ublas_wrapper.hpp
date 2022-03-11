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
polAlraKrhfcoTsev02a9YpyYthosI+N5C33+jFc5e4X2EY2BD45wjHoEbaRgeQZtZFNhqwRDO+NW7TeRPxpDscKLPrGbDJQzzORYYz6/qC08PCnMekz6o5Gvj8puVWNCylWKunBPeGR/bWSI6myE1G+6c9xe7MuIU8R9nXXMeqhH0/NHXNvxwza/v9gGeLHKJhaYYLueMdjlcyZdPxCHg01rJlaH5KcD2gv/UfXo75DJA4ufC/mEwxCILLVL1MZd8Ul3E7oq9FQHCPogqyXnQjyXv6ErEHzF9Lz/x91lS/XS0QAgENLpX15fFNV2n/SdLMLKbRhEYSqRapBqdalsaKNvVdTSLQKVVQYcRAHFxQ1URwtUtNaMsewqug4Co7jgC8zA4wzAopSQNuytixCEZQyoNxOQIp2g4He37Ocm6QtOO/7+f3RJrn33HPP+pxn/T4m06cx5GiOarx8aEFoUZQv8YbDrbphO7vUWChaTJR6nqRTggX6lKPyKQ/nuXnvAtKrnNTcm1p1TDYKA+OL12Znwz4vezmtHeRf3wyXmD2TPEa36kirrnA57ivwZhmxzK6g7cTlwI+Krar4EsNGOHZEu3Uyjs9sQ4TPo6eukVkU7ytwOYb4outYdq46Oh9u1aEZ66AbjHS0XTt6ltm6YlYiA1M7BVUGqFUmt7EoH8x9jnkvsXM0ag8C/COdeLfIEC08awwR4hZ0S9mINp6fGgw2sEMRxP+6gmWoAASm0CM0N+eFgc0Q5xQ1IVIlu/OrrBUBOrfJ5uKDQ5bsLXj+kr3Fd4Ez6DzWhNjO7PmIcOqISK0ECwx3d9WVTwahUtjEZXhssFnETkyES2TU20dli1sz7akdn6QDh1GJ1Tgtm4Juc2dgDrazaQTCF224DNMZBd8nP2RRg5jCcUWYepRauY5SPJKlyVp+BUlOgeI0MuZpmOUR/pph/ytSoomy+DhryrNQ1CLJBb6nmA0pWCsESoMBKy1wwAQmNAbUI1rsQzLDcLJQm+2qZmmAG5hFJM2A4ufItpuI9j5Y8L9/228Lk/ksQ+9GPM9WM9SebpupkpQu9f/Xdq9SDaylKvEzhUS0EVCVR3xVhPSoTruLvKEYLOyv1dIt0fAZfmDCxl+e3IymZXj6T6LZVfLL2Bz4LuUqh7l155d1m1uc1VEio8pObJyIu+Sf6SbLqGz7qEyeVLMzWGDmWebpDY3RfsiijNpl6LlKS7AoagkCjxdYQwWvgCLo6dqjCGeOFSStsawFUgp16ib4Qp3KhS/UqSsEvVUsXEwHPmqQXTX5G0oTKzbBt7pQjNgs29VHVP6BljSWCNB3JZ9uWcunUSYRZklYlKvTXjuqk3nJsOBPu8U4fz9xJpuaRuIjwTJprOneATdVaDbIOhyWqXTFFU6KeVeabvseZrapBba6pA1IEIBABObNPBdN8J+K0IQILSFZzqAl9KP7c6O7PZdTJBpQoziOT4yWkE7a4BRoPFBii6EyR2TbAj7nIlpvI9EgqgynF4lTBJWyL/d40GPO3+FN9J+OUcTXPosidiiBBS5iDrfBRaf1dRCjxTi68JX/dKwzotnH33HwM6LaT/CfThBf+WLE+oB/bET3L8opSX3Ar9Fy3enr6z9t8faG2rwpUAU95o0R2wIC5QwJFBzwT7RwaatTrFdB1la/CvixIe5g3F/nplKo8URXMLVsRIZJM51As70gtWie1LiTFR0DAUlN6lwDl+6BZy+Q7idFs1plmqCJ/z1NUA9VbM/YXsKYPqX1fQeNE5IXRiGeJBXU/U0bmcx+WcGMQstO+0+67VcjyT2r+eUL/EvQE8sUulhUUxESgPChfC7SYL3z58AqLONfx0a+TP86NvL1869jk3uvaHVy6ClCaFzC1uolZK02VvB9ySiRXexMjjDtJtqKFKpFWV65Ior0gWowxd8uhA/UbaEC3kzONRVxYVv9bTdLU2E31X9ToE3Xe+RwIaVIPfPUS6LytzTsME7Gfq5JjE16HDVsV8OL8lcywRuKezx/JYtABABOARaqaPV36LA2q/OrYRP5LgmrNHuFPYe1xh8kZ9V0CN1+9uhzG2M5MXGdTPrw3j+lBSj1D+NTTNperVVXxfdKYOpCzmcM9Q1THMtqcbMOVhxLYyk7hOK4cuQb6SZfoiKOBkoXhmLxAeZkJ9/CnOypt3FRdDjIF3nGAMzBkhGmJ8nMys67JdnQQHqz4C0rJJh6lOYR3p/E7B7GEgc+Nnr2zH69a+wlp2Tx9SeNYU2wOLmI6N9V8Iqmf8FUEzY51lMA9ch3+ZLpRNNt2Q4UcJahPOr1CYECjl2gbCP8x8jLAYVGS80XfXGPebNyAm7OjgxilYL4TVWsj5wHVZ/v6V947P4HWvXo6DNehdAeEsklPuXVLYYm03Izj/DCt4ypW7kq3aQNOoo/m4mAbzWFE8bMr09gCYhStH98M2W/cIpt3dNfjHyyZ2IodRH5a6qLopo2jVinkkXISX4/Dmv7USZVnVvLIo2NkQvHj5T5jxe2cjK6496+IAjEyi1UJDyYx/pGyi0L1XVJdYbbIDoJBozFTKlzWUZqr3DyEhOR6RojreHzeYYS83OoWQVZXMUkX8HU7zRY3ae+p6aoaMsnj+Zarc9hyuhJnha12qDQGT3UV3Fc174k3eRNxcm57v5WPWSBR9zBZXiAYj98HoevwPuUItqxH7SCbr6Be5tUy6A7iltMTEROMZ/O5GKQOVdpl9ckmmrUVcW4iko/c8MldIqb2Ew4ALqtTx5ZbOLb1I0WL76SUtxs074bh+bHtq5LBEMC5Ob6reLwLfR6eeXj7uKln3sTLuqPs0ivgzDWUqi3mtjVLIEH6oDDGLL/yec+3Pwmm7CgiLYziQC6EjADIBBA5vy4/kIHpsnGBvlP695SzDM/PexlSKsE1+bk+1JN2swjrTJnkrfELVh+c8LpxVaTIpGRhQMwH+d4aZr3Qv9sZOjSEAzqMiOVErJ0of7+P+OdE3gnvARop9VwMgBPP+Q1nWvZfpLJ4L9IeLsmqEH63I06N/Lg7D0Hhvs1W9MjCfBOIXx04H10iHCVrb+WVHFXXx91rpDeWmgBVeCu23eBodPW5zfHSC/dCzBtnTfLrDiWEBc0Vs3/8eU7naLFKQ7ANdaBLbqAYKymX23YYLOjjK8ckLDmOpCtLW1Flu/ySXH2Ul3To/CU1vtCMmOEjb+FbsdDBd6RMt9tqvQe1229byT2PgvRrxnI2otAy54hhoGYq9A+HHFWh/tWRMom30fPcm1oCnkNVjJirW12dgYstiVIsVxWtL1BkdNWhOlThzjF1ih4P+8AaJwSWELmj4W7SUGHR3agpFIVLR5xJjwCSLY96Nu3C1mg/HV8BFZborSAgzpg1NyOSf198f4X03QEZ6rkaEJ1iWiGmmbKEPYlhvJ2iVTe5q8iO18atP2nYZijFhpcBA1WxTHFMcllLW8m6XNSsRek0q2hAS4xJhGGZpEibgWmx7NOt+2/HNa/Z5GI+2QpSI/BWKdiiVuOXy3VCsJqOpaQevhK1sbZSUFHTA76xxfm9bgMiyY0TrbU21fETYK6LFVcwEKFQwNl+7058um4m6EADizx0xAX4VoVsbyRLEpXZmFT7Mvplr4NHiTCebHR8f7R7/drMebCPDzGJ+UZgzYgeoiWXyaH6LJebboYjYXItGEVlZy8Y0Zcfq3VUxtdacCz0F/VGVDfYd2kKKkMlMwJqAsCJQeDsb0D6lEYxjmkdPMcdgl1IdrrLesDasiaph782fpyIRrWFMdol+9G6VuASAhogfoQjZGwpK3l75gJvx1XZ4J7UuFNMEO4cDX9qrN604uocuHcV46FpCbtBzIrovAFR8PusVyTzBjRd8FGnEMmlHsVUcnK/sLsGaOMAciERegb6BT19jGZIq72z+loLVBN+TteioeJzg5drARG53Gdw6BOemNg4WtkCTjS1MqJWWcaCD6Yz9XtKILGB6llo8f6UuD9czmBH0Ie/MSGFEdh5kvJ3B5sDt6AcjTscETNwXGfkSoKs+2FmfmFeU6r+yegwPFuaEcoA9N4SnKP0HJopT+B44Njc/jKswgw38fo3gWILIKhClYxOlush+qc9q9gtoJjY8ywKe3Qr/XmObRdK//EnYIBmXEB2VD+RKNF+97bW1SG4e7NhdlQBfGeiqXZbelQmERZX7viDPqnThWheO1RG5ICXkrWClzY+WRrsb6msK6efX1pNDDqxNl+VjSz4c9pbzM22F2KmMNrnvQ6q+8pKSlxtjeJzeubhlh2KPYN4UfFHKQNPTaeZX1+9YxkELnoV/BaM2nRvnKK3Yoghxg4nNSK/TNuh/mbfpMrfw6R41xJhNwio1Z1/Nrl7eN0PJNXmoIBKrfmKZZa1V7ttOwpsmzPX0jEeT30+PkM6LGKqqoXMGsavNLZ3mFpVsQ6NnJNrvSIlqJJ65F+wSuts90xSAPbrLOGo34yfxXTwCEx0TSwGQmW75boRfZteIfsMnNS1y6rgXfKCVwNX9thp/yNFt/ucxPSRaJeQajc/GqnddGXuGMqjihWtVrErf8g3RRMick/WXqRqMTobCRXu4lc4czhoAOTi4jrhcDCuZq98bDci71JIs7/AZHMW2Edj2Vy131S1KBi0qOvKgF1DtGTBUL+Ll0IxAU+dBWWV6AU+BnPQqYnwBiocwx6kgz0RCd6Am9jJ8s5RsIfaRXsh0xagaQLoSuJLjgJO94YUu+DuGe990Hf0QgPm/YSuWl9A1RxCEb2oBzho3K/HQwlYIJJqNLYeI9dcZbyd2cItVK6mUT2HrIVckH3HIz2BgW6CJvG7Zi8BCiBXgNVkFIdO1jptpzMr+TdVX8Wd9fJ0EVaSh+yNEV2JO1V3j3AcQ8hcn5vIrC/fDRYy7PMEYnYOqsvcZoJ7mDltXTignA8hWhAHrWtgKb5JrIRYgFUlMObN7iCc5gpeh2GUct9rl0XizTaJolGqqh5BbB82xuc+d8V1VTpaGSzKtUUj8BPPjYc+VCDe7GWv2YyFvMrNLRUzEMJrLS+lwNrMomc+TzALP3KLZmlksj2aICvM2VEvOJ2TCzw3oz8owOTkui2s8OJB7IL6oXTXg2yuNwfVmaByB/vb9lnEbN0VRrjiS7XApZIRuAdK9mw1fhLhi3OZ0YpF3agNisPcTzfAcEt/ThKdgopELI3dtcdSHTAGrUhSm+weH16JIT9lNZ7m9lkZFQsYL26O1DaiNpnxbGOLdl9KQjtus67YHEHn4ITbx3R7F+7gotI9yksfpBOdc5TFfQ0OlFeLHbJxPJorTKk93v7oDz60X0duhJYlzKIbPMdpD7d7xR70TYxBl3IKFR/16h23R1cQtgeIjbrPK9A5p9eYehO+xu6U6tsJ7skI4RQDdtLxfr2BnXgJmf7Dqf/UL/2feiRfMa/wYYiWy9uGrqZQNPQ8+uza0yRytONypPELiw+4v4OHSS1Imh7XJHAtACy8X2p8atY7R9/3rZv//9qe19u+2n/hgyoSrt7HLX9TBq1XUs7X7O3a9Pvw2a3YbNji8Q94VZPLGrXo2eX1Nb/+9m9C8Utbcu91IxBw6gZicNodou6z26rC91aVpFe+TwDFLS9Rt5E/4dBItqLME/bNYWbMfwaakb/a7AZbbIZkR4/6Qr32FpxFZlj5KK/GLfuuiulzqNHMuyiCT1Tfk6od36++GY8DrdpZ68h52O2S6WraCWrp0wzc+e1wJaFoqIuIti8kxLJ+5n/mw79iz9i5tDt2qoutVDiPa5l1LlqKZG14MpsfQRq+YBrefp8tcSeqxZruJbt2vJHOn4xwyiM1jgSDVyM2ANX/RgN5RZ1iG2B/mvF4dmjZTXU0JYawYRTLjIiyjD8UPvc1KaHVJ5SkheZhvZ65ywabIcbNktaMPQqp3+Triavh9XyA2L8SZp7qwt9QOkcCNelbfo9EHzHyO0DMjArSfItrboWf0uX/CX7L6OsJH+BElDwr1zwXzdDwW9v7pK+5O9cUCCauuwQWoFJj0B+mKeWsR6hiq0M07ooEc6R49bFaNfilIHtlioD16zlIUq6ikKGNsJO6pXcnbQcN1TsNJbjp/fzcoxKP1sgyLervWFgW9kPqFgMzsb1oE3KYbf4AUrwVbwgnfgLtLbZLZzGJjojrTkJVoN/HcfQoSscR4Hs0l5/GMM36rSZK3W9i2K8qxY9rCZPjVaT/9KaYi8EgaMRzlPZReeytJazmlNYU41adQ61y2efykOugoD+Mb3ODlcwiJYS7cSZVsTyr3EF36AQpqAnU8vfSxoJX4GaC7KBL8dlVXzZruBCBnHk5y49AbQAJmmKO+BbrL0xtZ2QxYOexYiG4yJ4cPxWgN+8+C2Pkkzhtxz8Ng2/ZeO3sS4jK9V0PM2LDeZmPqISQe3N8NfBaOzkB3MZ4ypMQepwqLMVFSNLnWJ7lGLkgUSUhhApUmLFBz1ztR90yjgNbwlfnKntMC6ODV9coa3ViTUpmYtveLmTtO9dX3A6gYgCzyDaaUSDNVttJqgDxbFK+h7NYdn9SMT36BgM4hGZrvjH4626NXsqPjQV8zLRADKlYGRRHAJ0qgHeF+pEMCrfpUC2hqBvxxRg54Bv83LMAI3NHYm6bcMw4BQveAJTgTHUsOkcdWKmZ+PF9UgvKvb77jZaHeX+dCDa/Wk3vA3KkFZKqIt9cchnTaGANTdaEAmDAJuwaGiyqelFHJI5WCEM1wWKIN0JcvGkUhELyU9rp68/HiCGi9aByDDthjdN4YBkTk9QTyNbsdM7CJ6IauKx6CYeUcV6J2dS020TL0GVLY2atbyVTIdHrBXHcAuqDaKk3r4BRccD9PuAItTdTnsVXtmMEvHai03NJnL94Di5Ldy1P/XFMGcPPq7YN/P98YQjuJsL+KnABKpPtUO5BvsufbMSHG2WfiTj0ccHS97XtSrKbLUxXCOXuS6qDN7Bq1hYzlSKwv5j8Gwoif3HZD8YfLrNRiNAx0wu5oPDRbfyP60gWqj1imWjKrahFXQcXq7+uVWn1tLJvF3rcwyLKVnTVFJeN+K1vsfaIpSNFbC+3tGFOM8Pj7k3A+8URz2+N4Ty0SoOx3uAlvVkzYlKC17aFsV+GMoZvbsCW6zFUHM9x5z6JoQfDbe378/UDbheG7oEY721htNU8kiXYid+omJHKOZgu3ZTqFVvajSbIgtjl5mDIydia8fyIt6uDYem+jezCIZrKSMzmUoVYymvUSoeS6H5qYrZB912bEgyL7PHzF2X2f3m7svMZT7/MhuZ8V+W2aCMnsssssDC9bSm//c1tiP9/2uNzU8/xxrznDrnGvv1ya5r7G+YSO0/MTMyyMEMemAM94eDk3H07Gp9RdWMa+HVdnU3fLuCyDROwURjCvxNwB31icjL+PRvBlOTEMLP+5B/HeHM+cYZ1HxlB7aNlVwCRD6jcV81U5tbBFJSWP9N2NYOHUetBS+YIxeI3uC14xqeDPGuYCXDEdh2p2UYo0Gae7HdqRcXu0Wzmns82k4Yr31qhvNDwlds1976ASsaLGxDrMg/wVNjJrLGjnVA7uDQu7zJIJfGWWcjW9VF34wXdyGVTKuUQHkqdG2jjFL1mHRbCbCU7sBUzRWMi8HU9Ih5Tzf+0lvymp5GbWwbdJBUdPoW96TD1llvGo7DlRHH4dIZUhdwhxje6PSXukze8YFFiKMsgwDvMHZ7b+AO/OuYdcsyFsa17eTdAFKJB5fAHiYl9Zg13gaHafR1fW4tCrr6Vhg6fYs18AwnOnnFRGrO5YNIQ/MJMTPxwjaiF42bXjxRKjBQ4TdrHmruWIlhDZabw3q+O0QWQlm8LhME0tr8ES3Zy9m9P5VuLCT4D7g3o41mB65w7hucnmIMNpfHP6bUwRCn7TBrRk9H0TND2FsTY9CjO6uIRaSG1Tc6gbfL1Dcq+fud1jv3q47xiDrQGBVahVKBggyu5E3StMx25k3S8DWHW3HVbjRWseHC3FuFnZKlnTyOHghKVlbIiheGa43ywnAnOnpiBVf8gFFDe/HrwlbkA4NDjz6Nq2VyGr1t/rcteug+qJfsGJd3i/hCv32EtMS81bANbC2pchpgeBK69Z0nFKZwXWcLugAOfflpdvvYrn1/jLoUN/mt8OJs1PrDm10GeOcHF5Jm6QmD54BlYrAdCxkjCGnZV4MRNGj5P3gXTE0Lk+yJxniN+b4LyU7TbY4Lo0j7WKOc/fs2Yzl4n4QvyMHPmGzQkKktuFUoSmXLOUZ/kMKMn1Nfrz1J5yjHSfi1mFA/SXu0Er5B5fxVMSzq/uEISWkcXbN8APX5Du3GXyNiuRG1RxwdkFUONTSjixVyt8xWC8l0Z+P+Zq4aIyAl3+ciVXc8eRTyJJUsxde++3N4EczHc9UxNcebYTCqktt3HsbVEZi8ghjkF/e30K+ZxENPlb/mEpv9IP4iKeKrrSRFcAUaZT8OkvwB8mDTu6znQ6Hl/Hq+YNyhx1MlnndxWg9dXjGIO1o4pzxINf6Rc6+nVFQXM9XcP5fWcrMLczrptiODDHrXrJ1Z0oaeALltRqDEkzGkErHOehC/GOaBuyPmAbcY3kw0z1p+AVoc1v0B9a32ziLhSXT5m/pr/5wES5a9PVBbUz01lcCitNL/wfEhvsT2EV8s1sa1tujuYNzb9Nv2d8wRjZedfPkVvIxOpHjtSrhGyOWeDt02ayAFks5GL3xtxKBWPZLwzVo+1xx2VrnbcDwZ51xjiiXQnnHIBmHfW6jvGB0zzoWxbW9sRHpZfjs9PaEYtVaOhYnwmuk3UJkuDiVdhFOn/iU36yTuo/xG62tTkFCPVEUdBds6V+O7if3CUo8PZB+VnlUODleJ2qEat/AUI3HAh169EP19PRSaMpZjrz1hFdvLbH6ff2GyDBr1DSkSao6LgF83oWumq+DT71Azbuvbj8o4UYuS+mhFukk7syEedkl/GujuDUoKNwgbXPyLY1Dt0qulUa50YNOqs7rOWohrR8HE89fL8SusyKLZyUgEPz1F+okHC1wi9bvcDFIUYby/ixNxedzAd4DQDwxHcTZ6Bm7RbbcwPYgJ5X+KC8++Z/pQtoaVXlRTaUBPGgQaA/D9SxQL5+x7qRw6W3j6NO3SZloCpR+izj2ccLi4iz4G9t1dMD5dsBO+gVV6UwWmwzqlvfQTeiNYpL9ezTk=
*/