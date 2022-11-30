/*
 [auto_generated]
 boost/numeric/odeint/algebra/range_algebra.hpp

 [begin_description]
 Default algebra, which works with the most state types, like vector< double >, boost::array< double >, boost::range.
 Internally is uses boost::range to obtain the begin and end iterator of the according sequence.
 [end_description]

 Copyright 2010-2013 Karsten Ahnert
 Copyright 2010-2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_RANGE_ALGEBRA_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_RANGE_ALGEBRA_HPP_INCLUDED

#include <boost/range.hpp>
#include <boost/mpl/size_t.hpp>

#include <boost/numeric/odeint/algebra/detail/macros.hpp>
#include <boost/numeric/odeint/algebra/detail/for_each.hpp>
#include <boost/numeric/odeint/algebra/detail/norm_inf.hpp>
#include <boost/numeric/odeint/algebra/norm_result_type.hpp>

namespace boost {
namespace numeric {
namespace odeint {

struct range_algebra
{
    template< class S1 , class Op >
    static void for_each1( S1 &s1 , Op op )
    {
        detail::for_each1( boost::begin( s1 ) , boost::end( s1 ) ,
                op );
    }

    template< class S1 , class S2 , class Op >
    static void for_each2( S1 &s1 , S2 &s2 , Op op )
    {
        detail::for_each2( boost::begin( s1 ) , boost::end( s1 ) ,
                boost::begin( s2 ) , op );
    }

    template< class S1 , class S2 , class S3 , class Op >
    static void for_each3( S1 &s1 , S2 &s2 , S3 &s3 , Op op )
    {
        detail::for_each3( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class Op >
    static void for_each4( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , Op op )
    {
        detail::for_each4( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class Op >
    static void for_each5( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , Op op )
    {
        detail::for_each5( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , boost::begin( s5 ) , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class Op >
    static void for_each6( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , Op op )
    {
        detail::for_each6( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , boost::begin( s5 ) , boost::begin( s6 ) , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class Op >
    static void for_each7( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , Op op )
    {
        detail::for_each7( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , boost::begin( s5 ) , boost::begin( s6 ) , boost::begin( s7 ) , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class Op >
    static void for_each8( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , Op op )
    {
        detail::for_each8( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , boost::begin( s5 ) , boost::begin( s6 ) , boost::begin( s7 ) , boost::begin( s8 ) , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class Op >
    static void for_each9( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , Op op )
    {
        detail::for_each9( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , boost::begin( s5 ) , boost::begin( s6 ) , boost::begin( s7 ) , boost::begin( s8 ) , boost::begin( s9 ) , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class Op >
    static void for_each10( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , Op op )
    {
        detail::for_each10( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , boost::begin( s5 ) , boost::begin( s6 ) , boost::begin( s7 ) , boost::begin( s8 ) , boost::begin( s9 ) , boost::begin( s10 ) , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class Op >
    static void for_each11( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , Op op )
    {
        detail::for_each11( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , boost::begin( s5 ) , boost::begin( s6 ) , boost::begin( s7 ) , boost::begin( s8 ) , boost::begin( s9 ) , boost::begin( s10 ) , boost::begin( s11 ) , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class Op >
    static void for_each12( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , Op op )
    {
        detail::for_each12( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , boost::begin( s5 ) , boost::begin( s6 ) , boost::begin( s7 ) , boost::begin( s8 ) , boost::begin( s9 ) , boost::begin( s10 ) , boost::begin( s11 ) , boost::begin( s12 ) , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class Op >
    static void for_each13( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , Op op )
    {
        detail::for_each13( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , boost::begin( s5 ) , boost::begin( s6 ) , boost::begin( s7 ) , boost::begin( s8 ) , boost::begin( s9 ) , boost::begin( s10 ) , boost::begin( s11 ) , boost::begin( s12 ) , boost::begin( s13 ) , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class S14 , class Op >
    static void for_each14( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , S14 &s14 , Op op )
    {
        detail::for_each14( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , boost::begin( s5 ) , boost::begin( s6 ) , boost::begin( s7 ) , boost::begin( s8 ) , boost::begin( s9 ) , boost::begin( s10 ) , boost::begin( s11 ) , boost::begin( s12 ) , boost::begin( s13 ) , boost::begin( s14 ) , op );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class S14 , class S15 , class Op >
    static void for_each15( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , S14 &s14 , S15 &s15 , Op op )
    {
        detail::for_each15( boost::begin( s1 ) , boost::end( s1 ) , boost::begin( s2 ) , boost::begin( s3 ) , boost::begin( s4 ) , boost::begin( s5 ) , boost::begin( s6 ) , boost::begin( s7 ) , boost::begin( s8 ) , boost::begin( s9 ) , boost::begin( s10 ) , boost::begin( s11 ) , boost::begin( s12 ) , boost::begin( s13 ) , boost::begin( s14 ) , boost::begin( s15 ) , op );
    }

    template< typename S >
    static typename norm_result_type<S>::type norm_inf( const S &s )
    {
        return detail::norm_inf( boost::begin( s ) , boost::end( s ) ,
                                 static_cast< typename norm_result_type<S>::type >( 0 ) );
    }

};

} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_ALGEBRA_RANGE_ALGEBRA_HPP_INCLUDED

/* range_algebra.hpp
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
*/