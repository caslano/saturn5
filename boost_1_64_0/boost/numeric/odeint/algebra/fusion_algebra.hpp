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
H+I4f3jkWx75xCPf9ciXv8a8Ik7XjzzysYc3xL9A52OL99H6uzie33Ka/G+yP8XR/xen+EEiPht4XJd9B/3fTmfeEMf6/uL0/C3x38L82fh6YJNAvvyNQOubYP+Ibwbjoy3+GKwvJmcEtgPppzMDWxPWr5pnBfZTsK/iswP70v+uP8z+u5Y4ji8P74qPpPy/czz6Vxz1r4fHHt7w8JaHJ57n74pj/so8lg/F0X7z8Jr4KvT+4s9DfKt1bmAH0f738wLbkOZ3D295eFc8pPY5X/E/GL9d8Rezagdz6Mcfyr4i//4Cz/qHeIG+jzja1x5eEz8Z9kdUL5R9QPE18YspvndRYOOpf4vT+O2Kn0H25cWBXQu8fklg10uBbePaH3w566/yFeo/tP4hfjTVtxX/MvT/8pWBzYT5uSk+htZvxfeC+EbtZ4HNoP4rvhPY19HPAzsG5BPxZWl8iW9M/fsq2QfA6+LUvna15h+a3z28Jt4y2N/+C63/0fwtfh6tb/8ysCrFPzzcfhXYcWQ/iNP5+HZNYKtR+4hvAfZfXZzs7674SBo/v9b8T+c7Xcv2VVWc7KvII1/z8NjD6+J4fpeHt8XXpe/b4vuXW3z9ivhBtP4kXk5Bftl1gT0B80f4W82fsH5Znq/5Efz3xvWB/jusv4j3puD82hsCuxzip4n4GfT9bmT7tiN+O/j34c2BLQ/7r+t/0Pq/+CjH/vXOLZ740a2e+JE42q8eHomj/erhDc/1W57nb3vkO577223MQ3FcP/PI18Qpf7QtviWNz3aA54dV2mxfNMQPBf1bvp3971B8Q8qPEp+4dG/5MOer3xnYtvpRTQ+fX1u7l79vLE77y5viE6H+SPk+lq+Kk3xLPAX5o/bHwJ5MueurRg8G9g7YV40/8ffripN/UXlI+TGgv9vi21H8LRmYX5zPFz+s/B7a//6I7G88f4zt74Y46d+mOJ5vKE7r/81HA6vT+tZjgf0Q2s8eV/yY/DfxHcm+Ef8Ixl/7Ce7/iTj65+IY/3uSecXDI/GzQX/bU4rfQn2LunihB/ybhYvXb0c5ePjXwBrQP8Pn5H/0uNs3flH2SRrsk38Gth/sb2y/5Pk+4vh9PLz8L8/38fBIfAyNH3GMH4rj+aAenoiX6P3F59L+1JcDW4vsW/G1gXfF8fzdV2QfwvxTESf/MhJvUH2OV9X+af125tfLv6X8rm5gJ5J/9YYnviaO8TXxF23J+tVw+vdN2Z9k34pfAfX/orf0/PT9xZen7/M284qHR+Lon4lHFN/3yHfEqX/bOyxfFqfxF4qfAPGbtvhXqP79u8pPoPVV8SOB23ssH4lfDDx8P7A/AC//m+U74pT/F30Q2DeA24e8PlgXX4XiI+Jbk3/wkfJb6PwC8Vcg/zn52KMfxFF/f+LRD+Jn4fmIbJ9U1TtfgPNhmul+jL8n4qsCt55+m0X1c8Rpfm6Jj6D4Ql+/rZVy2w/1TL9NIvsu22/3Qv5PNei3eT3u+bNV7LeR1D7i/dT/xWn9vVzqtwMg/lf38K445R/Xl+nH/tkUp/7XFp8I8pVyP+/fF5+tH6Nd9b2W67cJukDFkX/QXr3fNh6o/+Kor7ROv43WBD5xER/m+9nW/bY21Y/Zvt9ODSTvyP+Mdtfzpd35B5Wo347Sh6nqdzgMbx3Wb8Hq7vpd1XP77ZRwSf8f5nySznV8//b1/VYuuNuvc5fGL5wv1LhH4z/tzp+o3t9v+1F8UHwlGh/iY/UjGfJ+/XMG6zdWkn5boA5YG3L/b54w+P7xy+rf+rHJQPsO833f6Lczof5O691+6+j7j3XlD32s+Un/3sTBK7m8/X1g/nfEJ/vzaJ93xO/W3+c75pc=
*/