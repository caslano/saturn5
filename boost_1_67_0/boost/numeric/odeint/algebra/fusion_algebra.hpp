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