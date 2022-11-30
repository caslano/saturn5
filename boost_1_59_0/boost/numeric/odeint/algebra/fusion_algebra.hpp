/*
 [auto_generated]
 boost/numeric/odeint/algebra/fusion_algebra.hpp

 [begin_description]
 Algebra for boost::fusion sequences.
 [end_description]

 Copyright 2011-2013 Karsten Ahnert
 Copyright 2011-2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_FUSION_ALGEBRA_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_FUSION_ALGEBRA_HPP_INCLUDED

#include <algorithm>

#include <boost/numeric/odeint/config.hpp>

#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/view/zip_view.hpp>
#include <boost/fusion/functional/generation/make_fused.hpp>
#include <boost/fusion/algorithm/iteration/accumulate.hpp>

namespace boost {
namespace numeric {
namespace odeint {

namespace detail {

    template< class Value >
    struct fusion_maximum
    {
        template< class Fac1 , class Fac2 >
        Value operator()( Fac1 t1 , const Fac2 t2 ) const
        {
            using std::abs;
            Value a1 = abs( get_unit_value( t1 ) ) , a2 = abs( get_unit_value( t2 ) );
            return ( a1 < a2 ) ? a2 : a1 ;
        }

        typedef Value result_type;
    };
}

/* specialize this if the fundamental numeric type in your fusion sequence is
 * anything else but double (most likely not)
 */
template< typename Sequence >
struct fusion_traits {
    typedef double value_type;
};

struct fusion_algebra
{
    template< class S1 , class Op >
    static void for_each1( S1 &s1 , Op op )
    {
        boost::fusion::for_each( s1 , op );
    };


    template< class S1 , class S2 , class Op >
    static void for_each2( S1 &s1 , S2 &s2 , Op op )
    {
        typedef boost::fusion::vector< S1& , S2& > Sequences;
        Sequences sequences( s1 , s2 );
        boost::fusion::for_each( boost::fusion::zip_view< Sequences >( sequences ) , boost::fusion::make_fused( op ) );
    }


    template< class S1 , class S2 , class S3 , class Op >
    static void for_each3( S1 &s1 , S2 &s2 , S3 &s3 , Op op )
    {
        typedef boost::fusion::vector< S1& , S2& , S3& > Sequences;
        Sequences sequences( s1 , s2 , s3 );
        boost::fusion::for_each( boost::fusion::zip_view< Sequences >( sequences ) , boost::fusion::make_fused( op ) );
    }

    template< class S1 , class S2 , class S3 , class S4 , class Op >
    static void for_each4( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , Op op )
    {
        typedef boost::fusion::vector< S1& , S2& , S3& , S4& > Sequences;
        Sequences sequences( s1 , s2 , s3 , s4 );
        boost::fusion::for_each( boost::fusion::zip_view< Sequences >( sequences ) , boost::fusion::make_fused( op ) );
    }


    template< class S1 , class S2 , class S3 , class S4 , class S5 , class Op >
    static void for_each5( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , Op op )
    {
        typedef boost::fusion::vector< S1& , S2& , S3& , S4& , S5& > Sequences;
        Sequences sequences( s1 , s2 , s3 , s4 , s5 );
        boost::fusion::for_each( boost::fusion::zip_view< Sequences >( sequences ) , boost::fusion::make_fused( op ) );
    }


    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class Op >
    static void for_each6( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , Op op )
    {
        typedef boost::fusion::vector< S1& , S2& , S3& , S4& , S5& , S6& > Sequences;
        Sequences sequences( s1 , s2 , s3 , s4 , s5 , s6 );
        boost::fusion::for_each( boost::fusion::zip_view< Sequences >( sequences ) , boost::fusion::make_fused( op ) );
    }


    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class S7 , class Op >
    static void for_each7( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , Op op )
    {
        typedef boost::fusion::vector< S1& , S2& , S3& , S4& , S5& , S6& , S7& > Sequences;
        Sequences sequences( s1 , s2 , s3 , s4 , s5 , s6 , s7 );
        boost::fusion::for_each( boost::fusion::zip_view< Sequences >( sequences ) , boost::fusion::make_fused( op ) );
    }


    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class S7 , class S8 , class Op >
    static void for_each8( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , Op op )
    {
        BOOST_STATIC_ASSERT_MSG( BOOST_FUSION_INVOKE_MAX_ARITY >= 8 , "Macro Parameter BOOST_FUSION_INVOKE_MAX_ARITY to small!" );
        typedef boost::fusion::vector< S1& , S2& , S3& , S4& , S5& , S6& , S7& , S8& > Sequences;
        Sequences sequences( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 );
        boost::fusion::for_each( boost::fusion::zip_view< Sequences >( sequences ) , boost::fusion::make_fused( op ) );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class S7 , class S8 , class S9 , class Op >
    static void for_each9( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , Op op )
    {
        BOOST_STATIC_ASSERT_MSG( BOOST_FUSION_INVOKE_MAX_ARITY >= 9 , "Macro Parameter BOOST_FUSION_INVOKE_MAX_ARITY to small!" );
        typedef boost::fusion::vector< S1& , S2& , S3& , S4& , S5& , S6& , S7& , S8& , S9& > Sequences;
        Sequences sequences( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 );
        boost::fusion::for_each( boost::fusion::zip_view< Sequences >( sequences ) , boost::fusion::make_fused( op ) );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class S7 , class S8 , class S9 , class S10 , class Op >
    static void for_each10( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , Op op )
    {
        BOOST_STATIC_ASSERT_MSG( BOOST_FUSION_INVOKE_MAX_ARITY >= 10 , "Macro Parameter BOOST_FUSION_INVOKE_MAX_ARITY to small!" );
        typedef boost::fusion::vector< S1& , S2& , S3& , S4& , S5& , S6& , S7& , S8& , S9& , S10& > Sequences;
        Sequences sequences( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 );
        boost::fusion::for_each( boost::fusion::zip_view< Sequences >( sequences ) , boost::fusion::make_fused( op ) );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class S7 , class S8 , class S9 , class S10 , class S11 , class Op >
    static void for_each11( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , Op op )
    {
        BOOST_STATIC_ASSERT_MSG( BOOST_FUSION_INVOKE_MAX_ARITY >= 11 , "Macro Parameter BOOST_FUSION_INVOKE_MAX_ARITY to small!" );
        BOOST_STATIC_ASSERT_MSG( BOOST_RESULT_OF_NUM_ARGS >= 11 , "Macro Parameter BOOST_RESULT_OF_NUM_ARGS to small!" );
        typedef boost::fusion::vector< S1& , S2& , S3& , S4& , S5& , S6& , S7& , S8& , S9& , S10& , S11& > Sequences;
        Sequences sequences( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 , s11 );
        boost::fusion::for_each( boost::fusion::zip_view< Sequences >( sequences ) , boost::fusion::make_fused( op ) );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class Op >
    static void for_each12( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , Op op )
    {
        BOOST_STATIC_ASSERT_MSG( BOOST_FUSION_INVOKE_MAX_ARITY >= 12 , "Macro Parameter BOOST_FUSION_INVOKE_MAX_ARITY to small!" );
        BOOST_STATIC_ASSERT_MSG( BOOST_RESULT_OF_NUM_ARGS >= 12 , "Macro Parameter BOOST_RESULT_OF_NUM_ARGS to small!" );
        typedef boost::fusion::vector< S1& , S2& , S3& , S4& , S5& , S6& , S7& , S8& , S9& , S10& , S11& , S12& > Sequences;
        Sequences sequences( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 , s11 , s12 );
        boost::fusion::for_each( boost::fusion::zip_view< Sequences >( sequences ) , boost::fusion::make_fused( op ) );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class Op >
    static void for_each13( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , Op op )
    {
        BOOST_STATIC_ASSERT_MSG( BOOST_FUSION_INVOKE_MAX_ARITY >= 13 , "Macro Parameter BOOST_FUSION_INVOKE_MAX_ARITY to small!" );
        BOOST_STATIC_ASSERT_MSG( BOOST_RESULT_OF_NUM_ARGS >= 13 , "Macro Parameter BOOST_RESULT_OF_NUM_ARGS to small!" );
        typedef boost::fusion::vector< S1& , S2& , S3& , S4& , S5& , S6& , S7& , S8& , S9& , S10& , S11& , S12& , S13& > Sequences;
        Sequences sequences( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 , s11 , s12 , s13 );
        boost::fusion::for_each( boost::fusion::zip_view< Sequences >( sequences ) , boost::fusion::make_fused( op ) );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class S14 , class Op >
    static void for_each14( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , S14 &s14 , Op op )
    {
        BOOST_STATIC_ASSERT_MSG( BOOST_FUSION_INVOKE_MAX_ARITY >= 14 , "Macro Parameter BOOST_FUSION_INVOKE_MAX_ARITY to small!" );
        BOOST_STATIC_ASSERT_MSG( BOOST_RESULT_OF_NUM_ARGS >= 14 , "Macro Parameter BOOST_RESULT_OF_NUM_ARGS to small!" );
        typedef boost::fusion::vector< S1& , S2& , S3& , S4& , S5& , S6& , S7& , S8& , S9& , S10& , S11& , S12& , S13& , S14& > Sequences;
        Sequences sequences( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 , s11 , s12 , s13 , s14 );
        boost::fusion::for_each( boost::fusion::zip_view< Sequences >( sequences ) , boost::fusion::make_fused( op ) );
    }

    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class S14 , class S15 , class Op >
    static void for_each15( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , S14 &s14 , S15 &s15 , Op op )
    {
        BOOST_STATIC_ASSERT_MSG( BOOST_FUSION_INVOKE_MAX_ARITY >= 15 , "Macro Parameter BOOST_FUSION_INVOKE_MAX_ARITY to small!" );
        BOOST_STATIC_ASSERT_MSG( BOOST_RESULT_OF_NUM_ARGS >= 15 , "Macro Parameter BOOST_RESULT_OF_NUM_ARGS to small!" );
        typedef boost::fusion::vector< S1& , S2& , S3& , S4& , S5& , S6& , S7& , S8& , S9& , S10& , S11& , S12& , S13& , S14& , S15& > Sequences;
        Sequences sequences( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 , s11 , s12 , s13 , s14 , s15 );
        boost::fusion::for_each( boost::fusion::zip_view< Sequences >( sequences ) , boost::fusion::make_fused( op ) );
    }

    template< class S >
    static typename fusion_traits< S >::value_type norm_inf( const S &s )
    {
        typedef typename fusion_traits< S >::value_type value_type;
        return boost::fusion::accumulate( s , static_cast<value_type>(0) ,
                                          detail::fusion_maximum<value_type>() );
    }

};



} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_ALGEBRA_FUSION_ALGEBRA_HPP_INCLUDED

/* fusion_algebra.hpp
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
*/