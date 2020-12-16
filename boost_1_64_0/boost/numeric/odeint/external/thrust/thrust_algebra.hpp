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
LwpfXRrH/0DKID5exlOGJmld8EOpv/Apcj8Z01D/Z1X9i0t7r/+PpVzQJtf/p6p+xQn1+7letyfgf6nKKC1Q/+c0TYH6/9rY09BS0UdpL/p4UeljVR/28JLIAdpkffx+jK4fY5Gr9Jbhel+RXN9Xx2ia5Pr+SdobNIXr9xeulc4t9fXZBn8HnU4hzT0uxx09pifHId4JnlMKxalc29UhwVtUGvtW61NdZer0pukr+EXGo7cEj7Wh/2n8P8dEfRLGil8V9CLfKKRcr6N3mO+O+PkUdIufKec9aR/wk7gveu0bVJKHotFnZLtXyp5D7x3TKq3x68UPh2k/xnapb/eDKv0YSx2QTmQFL2/XZo7eu9LzekPtx4eQl+5TPymRvjJI7WFG6Lc2+Q2tuFLT0oYL0JYaWtkPxmnLKqVNAZM4u8buh1O/E+XenLr3Jnxnsz1Gar5aVmMr5ZWaT/ysa3Ql4z+URr8TVwLO/TVwnjYt9Qbe7q8VLepdZWhRbkHa8YZW9Bmn3VfVpz1hbzxB6aVdxl78ovreT/hgTxfnM7GSdij42Jg2ydAkjXuTaavz1NpiCmB6bfFRpLXdThXZgIu3/bRK5mUd9TpnutGPPSOZAfy0xLFwdUuHiTskED0eig+urethed0LTVUQH78OFzr46xammwM6XeaOhDLnGZr9Sz2dpllAGz+Y8S9ZNn2Rk8terGTsLCocH/sIth32ibH5aCXPNmNnIpV9xp9w56dLqhfWuIaIg/M+ezViS/hbbOzjxsZqjY0tV3ayDH9vM99QVih8rbLBL9MGj67sM+7QXDwQt6S2fvGc5YulFgaRr8exlHdGoGNSIW5gJL440vUSo/k45BkU+LiCLj4j7yyuqhRpBu9ifMPcvUU3HznekVhyPWvWtGwMy1rIO20nqLIGvY84iP3ToYmDYjE8Y6+nDqexDvXDXL+GzBJD6aRK6rFbYisPkthCTn8NBfQXr4yrRfJ40o987jzLySx9pqkyuc9kAM+1zXHOBqGDMFQG7eNiB/MxnhYy3sZa5Hmoz3gbjF2lg7+5kBuvF/CBg+wN2WlTWz46xVVKkhJDq1LPpb4+JwOmx+F1HJNa1boFbRPZS9er/txh+nOn6c/rVX8N+cw2sV66Df4wG5tJ4TtVfwedw28QvOt3B5v8p6o56TPEgc7J9gmTt8PI9inOkceq+p5udHiGkulgyvSZSr9XmMPxe3YgsVza3XcTf9/5c06O9cEk2sWmUD992sVsx7uHvNPgvZC8z3T8Fge5cmYb37UzMJdmO9asyfW5s0C/KYQxHug0+oKdrfrZTcHRi5fULl1WU7O0fl7dMc60IhA1/47g+XDa+CycU2hu7wfvUOfnmb54fqWUpb8lXCDtCRlAZ2z7IrEF4sROL5a08FJvEC8r9vu9cfm0tOkXK6VNLzVtelllSNu/Nh2XYC9byE/bzlzyvrxf9rKhuaWrtbOjo7XevYLBMSTU61Y1R48LxMavVPDDygR+lYP3uUZYsQTBsGqXVC9yDRoH58ejbeTXzrpe7eqKlR3ntmvCOQF8uxBgoht5ZF5w76w6487FrBtsY9bJux0Su5/zyb701bxW2Xkq6Mlf1sZfnHMT6hmn8288mXHwBmNfN3Jc/YoeP0iXteebpP2qtnvSyjmCfIO5lfTbSX9vkBw/8yanT0jd0ZlpR7TQ7jAEc+49ILdmAW5DF4KY1nulA5fLNzjErWntwbojT18cwroyDU058jeEvizENbYi2GauIMbJrKSuGzvakaunMYsA4B1t7k2eaYwBfrtqlwrQmuW/ALhWCe1n92HulvySOjyeXL0g2Bmmd3PpZbU1Ry2rg2wOtnsI4zWTHGw=
*/