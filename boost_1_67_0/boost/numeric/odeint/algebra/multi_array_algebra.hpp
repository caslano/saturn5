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