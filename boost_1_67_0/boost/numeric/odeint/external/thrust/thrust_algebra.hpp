/*
 [auto_generated]
 boost/numeric/odeint/external/thrust/thrust_algebra.hpp

 [begin_description]
 An algebra for thrusts device_vectors.
 [end_description]

 Copyright 2010-2013 Mario Mulansky
 Copyright 2010-2011 Karsten Ahnert
 Copyright 2013 Kyle Lutz

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_THRUST_THRUST_ALGEBRA_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_THRUST_THRUST_ALGEBRA_HPP_INCLUDED


#include <thrust/device_vector.h>
#include <thrust/for_each.h>
#include <thrust/iterator/zip_iterator.h>

#include <boost/range.hpp>

namespace boost {
namespace numeric {
namespace odeint {

namespace detail {

    // to use in thrust::reduce
    template< class Value >
    struct maximum
    {
        template< class Fac1 , class Fac2 >
        __host__ __device__
        Value operator()( const Fac1 t1 , const Fac2 t2 ) const
        {
            return ( abs( t1 ) < abs( t2 ) ) ? t2 : t1 ;
        }

        typedef Value result_type;
    };

}




/** ToDO extend until for_each14 for rk78 */

/*
 * The const versions are needed for boost.range to work, i.e.
 * it allows you to do
 * for_each1( make_pair( vec1.begin() , vec1.begin() + 10 ) , op );
 */

struct thrust_algebra
{
    template< class StateType , class Operation >
    static void for_each1( StateType &s , Operation op )
    {
        thrust::for_each( boost::begin(s) , boost::end(s) , op );
    }

    template< class StateType1 , class StateType2 , class Operation >
    static void for_each2( StateType1 &s1 , StateType2 &s2 , Operation op )
    {
        thrust::for_each(
                thrust::make_zip_iterator( thrust::make_tuple( boost::begin(s1) ,
                        boost::begin(s2) ) ) ,
                        thrust::make_zip_iterator( thrust::make_tuple( boost::end(s1) ,
                                boost::end(s2) ) ) ,
                                op);
    }

    template< class StateType1 , class StateType2 , class StateType3 , class Operation >
    static void for_each3( StateType1 &s1 , StateType2 &s2 , StateType3 &s3 , Operation op )
    {
        thrust::for_each(
                thrust::make_zip_iterator( thrust::make_tuple( boost::begin(s1) ,
                        boost::begin(s2) ,
                        boost::begin(s3) ) ) ,
                        thrust::make_zip_iterator( thrust::make_tuple( boost::end(s1) ,
                                boost::end(s2) ,
                                boost::end(s3) ) ) ,
                                op);
    }

    template< class StateType1 , class StateType2 , class StateType3 , class StateType4 ,
    class Operation >
    static void for_each4( StateType1 &s1 , StateType2 &s2 , StateType3 &s3 , StateType4 &s4 ,
            Operation op )
    {
        thrust::for_each(
                thrust::make_zip_iterator( thrust::make_tuple( boost::begin(s1) ,
                        boost::begin(s2) ,
                        boost::begin(s3) ,
                        boost::begin(s4) ) ) ,
                        thrust::make_zip_iterator( thrust::make_tuple( boost::end(s1) ,
                                boost::end(s2) ,
                                boost::end(s3) ,
                                boost::end(s4) ) ) ,
                                op);
    }

    template< class StateType1 , class StateType2 , class StateType3 ,
    class StateType4 , class StateType5 ,class Operation >
    static void for_each5( StateType1 &s1 , StateType2 &s2 , StateType3 &s3 , StateType4 &s4 ,
            StateType5 &s5 , Operation op )
    {
        thrust::for_each(
                thrust::make_zip_iterator( thrust::make_tuple( boost::begin(s1) ,
                        boost::begin(s2) ,
                        boost::begin(s3) ,
                        boost::begin(s4) ,
                        boost::begin(s5) ) ) ,
                        thrust::make_zip_iterator( thrust::make_tuple( boost::end(s1) ,
                                boost::end(s2) ,
                                boost::end(s3) ,
                                boost::end(s4) ,
                                boost::end(s5) ) ) ,
                                op);
    }

    template< class StateType1 , class StateType2 , class StateType3 ,
    class StateType4 , class StateType5 , class StateType6 , class Operation >
    static void for_each6( StateType1 &s1 , StateType2 &s2 , StateType3 &s3 , StateType4 &s4 ,
            StateType5 &s5 , StateType6 &s6 , Operation op )
    {
        thrust::for_each(
                thrust::make_zip_iterator( thrust::make_tuple( boost::begin(s1) ,
                        boost::begin(s2) ,
                        boost::begin(s3) ,
                        boost::begin(s4) ,
                        boost::begin(s5) ,
                        boost::begin(s6) ) ) ,
                        thrust::make_zip_iterator( thrust::make_tuple( boost::end(s1) ,
                                boost::end(s2) ,
                                boost::end(s3) ,
                                boost::end(s4) ,
                                boost::end(s5) ,
                                boost::end(s6) ) ) ,
                                op);
    }

    template< class StateType1 , class StateType2 , class StateType3 , class StateType4 ,
    class StateType5 , class StateType6 , class StateType7 , class Operation >
    static void for_each7( StateType1 &s1 , StateType2 &s2 , StateType3 &s3 , StateType4 &s4 ,
            StateType5 &s5 , StateType6 &s6 , StateType7 &s7 , Operation op )
    {
        thrust::for_each(
                thrust::make_zip_iterator( thrust::make_tuple( boost::begin(s1) ,
                        boost::begin(s2) ,
                        boost::begin(s3) ,
                        boost::begin(s4) ,
                        boost::begin(s5) ,
                        boost::begin(s6) ,
                        boost::begin(s7) ) ) ,
                        thrust::make_zip_iterator( thrust::make_tuple( boost::end(s1) ,
                                boost::end(s2) ,
                                boost::end(s3) ,
                                boost::end(s4) ,
                                boost::end(s5) ,
                                boost::end(s6) ,
                                boost::end(s7) ) ) ,
                                op);
    }

    template< class StateType1 , class StateType2 , class StateType3 , class StateType4 ,
    class StateType5 , class StateType6 , class StateType7 , class StateType8 , class Operation >
    static void for_each8( StateType1 &s1 , StateType2 &s2 , StateType3 &s3 , StateType4 &s4 ,
            StateType5 &s5 , StateType6 &s6 , StateType7 &s7 , StateType8 &s8 , Operation op )
    {
        thrust::for_each(
                thrust::make_zip_iterator( thrust::make_tuple( boost::begin(s1) ,
                        boost::begin(s2) ,
                        boost::begin(s3) ,
                        boost::begin(s4) ,
                        boost::begin(s5) ,
                        boost::begin(s6) ,
                        boost::begin(s7) ,
                        boost::begin(s8) ) ) ,
                thrust::make_zip_iterator( thrust::make_tuple( boost::end(s1) ,
                        boost::end(s2) ,
                        boost::end(s3) ,
                        boost::end(s4) ,
                        boost::end(s5) ,
                        boost::end(s6) ,
                        boost::end(s7) ,
                        boost::end(s8) ) ) ,
                op);
    }

    template< class S >
    static typename S::value_type norm_inf( const S &s )
    {
        typedef typename S::value_type value_type;
        return thrust::reduce( boost::begin( s ) , boost::end( s ) ,
                               static_cast<value_type>(0) ,
                               detail::maximum<value_type>() );
    }

};


} // odeint
} // numeric
} // boost



#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_THRUST_THRUST_ALGEBRA_HPP_INCLUDED

/* thrust_algebra.hpp
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
*/