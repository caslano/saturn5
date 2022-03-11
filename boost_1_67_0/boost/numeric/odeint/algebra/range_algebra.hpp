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