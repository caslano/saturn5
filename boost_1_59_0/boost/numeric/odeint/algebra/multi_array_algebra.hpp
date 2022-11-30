/*
  [auto_generated]
  boost/numeric/odeint/algebra/multi_array_algebra.hpp

  [begin_description]
  tba.
  [end_description]

  Copyright 2009-2012 Karsten Ahnert
  Copyright 2009-2012 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_MULTI_ARRAY_ALGEBRA_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_MULTI_ARRAY_ALGEBRA_HPP_DEFINED


#include <boost/multi_array.hpp>

#include <boost/numeric/odeint/algebra/detail/for_each.hpp>
#include <boost/numeric/odeint/algebra/detail/norm_inf.hpp>
#include <boost/numeric/odeint/algebra/norm_result_type.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>


namespace boost {
namespace numeric {
namespace odeint {

// not ready
struct multi_array_algebra
{
    template< class S1 , class Op >
    static void for_each1( S1 &s1 , Op op )
    {
        detail::for_each1( s1.data() , s1.data() + s1.num_elements() , op );
    }

    template< class S1 , class S2 , class Op >
    static void for_each2( S1 &s1 , S2 &s2 , Op op )
    {
        detail::for_each2( s1.data() , s1.data() + s1.num_elements() , s2.data() , op );
    }

    template< class S1 , class S2 , class S3 , class Op >
    static void for_each3( S1 &s1 , S2 &s2 , S3 &s3 , Op op )
    {
        detail::for_each3( s1.data() , s1.data() + s1.num_elements() , s2.data() , s3.data() , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class Op >
    static void for_each4( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , Op op )
    {
        detail::for_each4( s1.data() , s1.data() + s1.num_elements() , s2.data() , s3.data() , s4.data() , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class Op >
    static void for_each5( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , Op op )
    {
        detail::for_each5( s1.data() , s1.data() + s1.num_elements() , s2.data() , s3.data() , s4.data() , s5.data() , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class Op >
    static void for_each6( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , Op op )
    {
        detail::for_each6( s1.data() , s1.data() + s1.num_elements() , s2.data() , s3.data() , s4.data() , s5.data() , s6.data() , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class Op >
    static void for_each7( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , Op op )
    {
        detail::for_each7( s1.data() , s1.data() + s1.num_elements() , s2.data() , s3.data() , s4.data() , s5.data() , s6.data() , s7.data() , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class Op >
    static void for_each8( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , Op op )
    {
        detail::for_each8( s1.data() , s1.data() + s1.num_elements() , s2.data() , s3.data() , s4.data() , s5.data() , s6.data() , s7.data() , s8.data() , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class Op >
    static void for_each9( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , Op op )
    {
        detail::for_each9( s1.data() , s1.data() + s1.num_elements() , s2.data() , s3.data() , s4.data() , s5.data() , s6.data() , s7.data() , s8.data() , s9.data() , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class Op >
    static void for_each10( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , Op op )
    {
        detail::for_each10( s1.data() , s1.data() + s1.num_elements() , s2.data() , s3.data() , s4.data() , s5.data() , s6.data() , s7.data() , s8.data() , s9.data() , s10.data() , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class Op >
    static void for_each11( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , Op op )
    {
        detail::for_each11( s1.data() , s1.data() + s1.num_elements() , s2.data() , s3.data() , s4.data() , s5.data() , s6.data() , s7.data() , s8.data() , s9.data() , s10.data() , s11.data() , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class Op >
    static void for_each12( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , Op op )
    {
        detail::for_each12( s1.data() , s1.data() + s1.num_elements() , s2.data() , s3.data() , s4.data() , s5.data() , s6.data() , s7.data() , s8.data() , s9.data() , s10.data() , s11.data() , s12.data() , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class Op >
    static void for_each13( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , Op op )
    {
        detail::for_each13( s1.data() , s1.data() + s1.num_elements() , s2.data() , s3.data() , s4.data() , s5.data() , s6.data() , s7.data() , s8.data() , s9.data() , s10.data() , s11.data() , s12.data() , s13.data() , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class S14 , class Op >
    static void for_each14( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , S14 &s14 , Op op )
    {
        detail::for_each14( s1.data() , s1.data() + s1.num_elements() , s2.data() , s3.data() , s4.data() , s5.data() , s6.data() , s7.data() , s8.data() , s9.data() , s10.data() , s11.data() , s12.data() , s13.data() , s14.data() , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class S14 , class S15 , class Op >
    static void for_each15( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , S14 &s14 , S15 &s15 , Op op )
    {
        detail::for_each15( s1.data() , s1.data() + s1.num_elements() , s2.data() , s3.data() , s4.data() , s5.data() , s6.data() , s7.data() , s8.data() , s9.data() , s10.data() , s11.data() , s12.data() , s13.data() , s14.data() , s15.data() , op );
    }

    template< typename S >
    static typename norm_result_type<S>::type norm_inf( const S &s )
    {
        return detail::norm_inf( s.data() , s.data() + s.num_elements()  , static_cast< typename norm_result_type<S>::type >( 0 ) );
    }
};

template< class T , size_t N >
struct algebra_dispatcher< boost::multi_array< T , N > >
{
    typedef multi_array_algebra algebra_type;
};


} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_ALGEBRA_MULTI_ARRAY_ALGEBRA_HPP_DEFINED

/* multi_array_algebra.hpp
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
*/