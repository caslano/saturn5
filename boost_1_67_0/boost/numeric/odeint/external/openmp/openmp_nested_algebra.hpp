/*
 [auto_generated]
 boost/numeric/odeint/external/openmp/openmp_nested_algebra.hpp

 [begin_description]
 Nested parallelized algebra for OpenMP.
 [end_description]

 Copyright 2013 Karsten Ahnert
 Copyright 2013 Mario Mulansky
 Copyright 2013 Pascal Germroth

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_OPENMP_OPENMP_NESTED_ALGEBRA_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_OPENMP_OPENMP_NESTED_ALGEBRA_HPP_INCLUDED

#include <boost/assert.hpp>
#include <boost/range.hpp>
#include <boost/numeric/odeint/algebra/norm_result_type.hpp>
#include <boost/numeric/odeint/util/n_ary_helper.hpp>

namespace boost {
namespace numeric {
namespace odeint {

/** \brief OpenMP-parallelized algebra, wrapping another, non-parallelized algebra.
 *
 * NestedState must be a model of Random Access Range, where the elements are sub-states
 * which will be processed in parallel.
 */
template< class InnerAlgebra >
struct openmp_nested_algebra
{

#if __cplusplus >= 201103L // C++11 supports _Pragma

#define BOOST_ODEINT_GEN_LOCAL(z, n, unused) \
    BOOST_ASSERT_MSG( len == boost::size(s ## n), "All nested state ranges must have the same size." ); \
    typename boost::range_iterator<S ## n>::type beg ## n = boost::begin(s ## n);
#define BOOST_ODEINT_GEN_BODY(n) \
    const size_t len = boost::size(s0); \
    BOOST_PP_REPEAT(n, BOOST_ODEINT_GEN_LOCAL, ~) \
    _Pragma("omp parallel for schedule(runtime)") \
    for( size_t i = 0 ; i < len ; i++ ) \
        InnerAlgebra::for_each##n( \
            BOOST_PP_ENUM_BINARY_PARAMS(n, beg, [i] BOOST_PP_INTERCEPT) , \
            op \
        );
BOOST_ODEINT_GEN_FOR_EACH(BOOST_ODEINT_GEN_BODY)
#undef BOOST_ODEINT_GEN_BODY
#undef BOOST_ODEINT_GEN_LOCAL

#else

    template< class S0 , class Op > static void for_each1 ( S0 &s0 , Op op ) {
        const size_t len = boost::size(s0);
        typename boost::range_iterator<S0>::type beg0 = boost::begin(s0);
        #pragma omp parallel for schedule(runtime)
        for( size_t i = 0 ; i < len ; i++ ) InnerAlgebra::for_each1( beg0 [i] , op );
    }
    template< class S0 , class S1 , class Op > static void for_each2 ( S0 &s0 , S1 &s1 , Op op ) {
        const size_t len = boost::size(s0);
        typename boost::range_iterator<S0>::type beg0 = boost::begin(s0);
        typename boost::range_iterator<S1>::type beg1 = boost::begin(s1);
        #pragma omp parallel for schedule(runtime)
        for( size_t i = 0 ; i < len ; i++ ) InnerAlgebra::for_each2( beg0 [i] , beg1 [i] , op );
    }
    template< class S0 , class S1 , class S2 , class Op > static void for_each3 ( S0 &s0 , S1 &s1 , S2 &s2 , Op op ) {
        const size_t len = boost::size(s0);
        typename boost::range_iterator<S0>::type beg0 = boost::begin(s0);
        typename boost::range_iterator<S1>::type beg1 = boost::begin(s1);
        typename boost::range_iterator<S2>::type beg2 = boost::begin(s2);
        #pragma omp parallel for schedule(runtime)
        for( size_t i = 0 ; i < len ; i++ ) InnerAlgebra::for_each3( beg0 [i] , beg1 [i] , beg2 [i] , op );
    }
    template< class S0 , class S1 , class S2 , class S3 , class Op > static void for_each4 ( S0 &s0 , S1 &s1 , S2 &s2 , S3 &s3 , Op op ) {
        const size_t len = boost::size(s0);
        typename boost::range_iterator<S0>::type beg0 = boost::begin(s0);
        typename boost::range_iterator<S1>::type beg1 = boost::begin(s1);
        typename boost::range_iterator<S2>::type beg2 = boost::begin(s2);
        typename boost::range_iterator<S3>::type beg3 = boost::begin(s3);
        #pragma omp parallel for schedule(runtime)
        for( size_t i = 0 ; i < len ; i++ ) InnerAlgebra::for_each4( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] , op );
    }
    template< class S0 , class S1 , class S2 , class S3 , class S4 , class Op > static void for_each5 ( S0 &s0 , S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , Op op ) {
        const size_t len = boost::size(s0);
        typename boost::range_iterator<S0>::type beg0 = boost::begin(s0);
        typename boost::range_iterator<S1>::type beg1 = boost::begin(s1);
        typename boost::range_iterator<S2>::type beg2 = boost::begin(s2);
        typename boost::range_iterator<S3>::type beg3 = boost::begin(s3);
        typename boost::range_iterator<S4>::type beg4 = boost::begin(s4);
        #pragma omp parallel for schedule(runtime)
        for( size_t i = 0 ; i < len ; i++ ) InnerAlgebra::for_each5( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] , beg4 [i] , op );
    }
    template< class S0 , class S1 , class S2 , class S3 , class S4 , class S5 , class Op > static void for_each6 ( S0 &s0 , S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , Op op ) {
        const size_t len = boost::size(s0);
        typename boost::range_iterator<S0>::type beg0 = boost::begin(s0);
        typename boost::range_iterator<S1>::type beg1 = boost::begin(s1);
        typename boost::range_iterator<S2>::type beg2 = boost::begin(s2);
        typename boost::range_iterator<S3>::type beg3 = boost::begin(s3);
        typename boost::range_iterator<S4>::type beg4 = boost::begin(s4);
        typename boost::range_iterator<S5>::type beg5 = boost::begin(s5);
        #pragma omp parallel for schedule(runtime)
        for( size_t i = 0 ; i < len ; i++ ) InnerAlgebra::for_each6( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] , beg4 [i] , beg5 [i] , op );
    }
    template< class S0 , class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class Op > static void for_each7 ( S0 &s0 , S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , Op op ) {
        const size_t len = boost::size(s0);
        typename boost::range_iterator<S0>::type beg0 = boost::begin(s0);
        typename boost::range_iterator<S1>::type beg1 = boost::begin(s1);
        typename boost::range_iterator<S2>::type beg2 = boost::begin(s2);
        typename boost::range_iterator<S3>::type beg3 = boost::begin(s3);
        typename boost::range_iterator<S4>::type beg4 = boost::begin(s4);
        typename boost::range_iterator<S5>::type beg5 = boost::begin(s5);
        typename boost::range_iterator<S6>::type beg6 = boost::begin(s6);
        #pragma omp parallel for schedule(runtime)
        for( size_t i = 0 ; i < len ; i++ ) InnerAlgebra::for_each7( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] , beg4 [i] , beg5 [i] , beg6 [i] , op );
    }
    template< class S0 , class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class S7 , class Op > static void for_each8 ( S0 &s0 , S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , Op op ) {
        const size_t len = boost::size(s0);
        typename boost::range_iterator<S0>::type beg0 = boost::begin(s0);
        typename boost::range_iterator<S1>::type beg1 = boost::begin(s1);
        typename boost::range_iterator<S2>::type beg2 = boost::begin(s2);
        typename boost::range_iterator<S3>::type beg3 = boost::begin(s3);
        typename boost::range_iterator<S4>::type beg4 = boost::begin(s4);
        typename boost::range_iterator<S5>::type beg5 = boost::begin(s5);
        typename boost::range_iterator<S6>::type beg6 = boost::begin(s6);
        typename boost::range_iterator<S7>::type beg7 = boost::begin(s7);
        #pragma omp parallel for schedule(runtime)
        for( size_t i = 0 ; i < len ; i++ ) InnerAlgebra::for_each8( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] , beg4 [i] , beg5 [i] , beg6 [i] , beg7 [i] , op );
    }
    template< class S0 , class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class S7 , class S8 , class Op > static void for_each9 ( S0 &s0 , S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , Op op ) {
        const size_t len = boost::size(s0);
        typename boost::range_iterator<S0>::type beg0 = boost::begin(s0);
        typename boost::range_iterator<S1>::type beg1 = boost::begin(s1);
        typename boost::range_iterator<S2>::type beg2 = boost::begin(s2);
        typename boost::range_iterator<S3>::type beg3 = boost::begin(s3);
        typename boost::range_iterator<S4>::type beg4 = boost::begin(s4);
        typename boost::range_iterator<S5>::type beg5 = boost::begin(s5);
        typename boost::range_iterator<S6>::type beg6 = boost::begin(s6);
        typename boost::range_iterator<S7>::type beg7 = boost::begin(s7);
        typename boost::range_iterator<S8>::type beg8 = boost::begin(s8);
        #pragma omp parallel for schedule(runtime)
        for( size_t i = 0 ; i < len ; i++ ) InnerAlgebra::for_each9( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] , beg4 [i] , beg5 [i] , beg6 [i] , beg7 [i] , beg8 [i] , op );
    }
    template< class S0 , class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class S7 , class S8 , class S9 , class Op > static void for_each10 ( S0 &s0 , S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , Op op ) {
        const size_t len = boost::size(s0);
        typename boost::range_iterator<S0>::type beg0 = boost::begin(s0);
        typename boost::range_iterator<S1>::type beg1 = boost::begin(s1);
        typename boost::range_iterator<S2>::type beg2 = boost::begin(s2);
        typename boost::range_iterator<S3>::type beg3 = boost::begin(s3);
        typename boost::range_iterator<S4>::type beg4 = boost::begin(s4);
        typename boost::range_iterator<S5>::type beg5 = boost::begin(s5);
        typename boost::range_iterator<S6>::type beg6 = boost::begin(s6);
        typename boost::range_iterator<S7>::type beg7 = boost::begin(s7);
        typename boost::range_iterator<S8>::type beg8 = boost::begin(s8);
        typename boost::range_iterator<S9>::type beg9 = boost::begin(s9);
        #pragma omp parallel for schedule(runtime)
        for( size_t i = 0 ; i < len ; i++ ) InnerAlgebra::for_each10( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] , beg4 [i] , beg5 [i] , beg6 [i] , beg7 [i] , beg8 [i] , beg9 [i] , op );
    }
    template< class S0 , class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class S7 , class S8 , class S9 , class S10 , class Op > static void for_each11 ( S0 &s0 , S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , Op op ) {
        const size_t len = boost::size(s0);
        typename boost::range_iterator<S0>::type beg0 = boost::begin(s0);
        typename boost::range_iterator<S1>::type beg1 = boost::begin(s1);
        typename boost::range_iterator<S2>::type beg2 = boost::begin(s2);
        typename boost::range_iterator<S3>::type beg3 = boost::begin(s3);
        typename boost::range_iterator<S4>::type beg4 = boost::begin(s4);
        typename boost::range_iterator<S5>::type beg5 = boost::begin(s5);
        typename boost::range_iterator<S6>::type beg6 = boost::begin(s6);
        typename boost::range_iterator<S7>::type beg7 = boost::begin(s7);
        typename boost::range_iterator<S8>::type beg8 = boost::begin(s8);
        typename boost::range_iterator<S9>::type beg9 = boost::begin(s9);
        typename boost::range_iterator<S10>::type beg10 = boost::begin(s10);
        #pragma omp parallel for schedule(runtime)
        for( size_t i = 0 ; i < len ; i++ ) InnerAlgebra::for_each11( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] , beg4 [i] , beg5 [i] , beg6 [i] , beg7 [i] , beg8 [i] , beg9 [i] , beg10 [i] , op );
    }
    template< class S0 , class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class S7 , class S8 , class S9 , class S10 , class S11 , class Op > static void for_each12 ( S0 &s0 , S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , Op op ) {
        const size_t len = boost::size(s0);
        typename boost::range_iterator<S0>::type beg0 = boost::begin(s0);
        typename boost::range_iterator<S1>::type beg1 = boost::begin(s1);
        typename boost::range_iterator<S2>::type beg2 = boost::begin(s2);
        typename boost::range_iterator<S3>::type beg3 = boost::begin(s3);
        typename boost::range_iterator<S4>::type beg4 = boost::begin(s4);
        typename boost::range_iterator<S5>::type beg5 = boost::begin(s5);
        typename boost::range_iterator<S6>::type beg6 = boost::begin(s6);
        typename boost::range_iterator<S7>::type beg7 = boost::begin(s7);
        typename boost::range_iterator<S8>::type beg8 = boost::begin(s8);
        typename boost::range_iterator<S9>::type beg9 = boost::begin(s9);
        typename boost::range_iterator<S10>::type beg10 = boost::begin(s10);
        typename boost::range_iterator<S11>::type beg11 = boost::begin(s11);
        #pragma omp parallel for schedule(runtime)
        for( size_t i = 0 ; i < len ; i++ ) InnerAlgebra::for_each12( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] , beg4 [i] , beg5 [i] , beg6 [i] , beg7 [i] , beg8 [i] , beg9 [i] , beg10 [i] , beg11 [i] , op );
    }
    template< class S0 , class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class Op > static void for_each13 ( S0 &s0 , S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , Op op ) {
        const size_t len = boost::size(s0);
        typename boost::range_iterator<S0>::type beg0 = boost::begin(s0);
        typename boost::range_iterator<S1>::type beg1 = boost::begin(s1);
        typename boost::range_iterator<S2>::type beg2 = boost::begin(s2);
        typename boost::range_iterator<S3>::type beg3 = boost::begin(s3);
        typename boost::range_iterator<S4>::type beg4 = boost::begin(s4);
        typename boost::range_iterator<S5>::type beg5 = boost::begin(s5);
        typename boost::range_iterator<S6>::type beg6 = boost::begin(s6);
        typename boost::range_iterator<S7>::type beg7 = boost::begin(s7);
        typename boost::range_iterator<S8>::type beg8 = boost::begin(s8);
        typename boost::range_iterator<S9>::type beg9 = boost::begin(s9);
        typename boost::range_iterator<S10>::type beg10 = boost::begin(s10);
        typename boost::range_iterator<S11>::type beg11 = boost::begin(s11);
        typename boost::range_iterator<S12>::type beg12 = boost::begin(s12);
        #pragma omp parallel for schedule(runtime)
        for( size_t i = 0 ; i < len ; i++ ) InnerAlgebra::for_each13( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] , beg4 [i] , beg5 [i] , beg6 [i] , beg7 [i] , beg8 [i] , beg9 [i] , beg10 [i] , beg11 [i] , beg12 [i] , op );
    }
    template< class S0 , class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class Op > static void for_each14 ( S0 &s0 , S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , Op op ) {
        const size_t len = boost::size(s0);
        typename boost::range_iterator<S0>::type beg0 = boost::begin(s0);
        typename boost::range_iterator<S1>::type beg1 = boost::begin(s1);
        typename boost::range_iterator<S2>::type beg2 = boost::begin(s2);
        typename boost::range_iterator<S3>::type beg3 = boost::begin(s3);
        typename boost::range_iterator<S4>::type beg4 = boost::begin(s4);
        typename boost::range_iterator<S5>::type beg5 = boost::begin(s5);
        typename boost::range_iterator<S6>::type beg6 = boost::begin(s6);
        typename boost::range_iterator<S7>::type beg7 = boost::begin(s7);
        typename boost::range_iterator<S8>::type beg8 = boost::begin(s8);
        typename boost::range_iterator<S9>::type beg9 = boost::begin(s9);
        typename boost::range_iterator<S10>::type beg10 = boost::begin(s10);
        typename boost::range_iterator<S11>::type beg11 = boost::begin(s11);
        typename boost::range_iterator<S12>::type beg12 = boost::begin(s12);
        typename boost::range_iterator<S13>::type beg13 = boost::begin(s13);
        #pragma omp parallel for schedule(runtime)
        for( size_t i = 0 ; i < len ; i++ ) InnerAlgebra::for_each14( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] , beg4 [i] , beg5 [i] , beg6 [i] , beg7 [i] , beg8 [i] , beg9 [i] , beg10 [i] , beg11 [i] , beg12 [i] , beg13 [i] , op );
    }
    template< class S0 , class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class S14 , class Op > static void for_each15 ( S0 &s0 , S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , S14 &s14 , Op op ) {
        const size_t len = boost::size(s0);
        typename boost::range_iterator<S0>::type beg0 = boost::begin(s0);
        typename boost::range_iterator<S1>::type beg1 = boost::begin(s1);
        typename boost::range_iterator<S2>::type beg2 = boost::begin(s2);
        typename boost::range_iterator<S3>::type beg3 = boost::begin(s3);
        typename boost::range_iterator<S4>::type beg4 = boost::begin(s4);
        typename boost::range_iterator<S5>::type beg5 = boost::begin(s5);
        typename boost::range_iterator<S6>::type beg6 = boost::begin(s6);
        typename boost::range_iterator<S7>::type beg7 = boost::begin(s7);
        typename boost::range_iterator<S8>::type beg8 = boost::begin(s8);
        typename boost::range_iterator<S9>::type beg9 = boost::begin(s9);
        typename boost::range_iterator<S10>::type beg10 = boost::begin(s10);
        typename boost::range_iterator<S11>::type beg11 = boost::begin(s11);
        typename boost::range_iterator<S12>::type beg12 = boost::begin(s12);
        typename boost::range_iterator<S13>::type beg13 = boost::begin(s13);
        typename boost::range_iterator<S14>::type beg14 = boost::begin(s14);
        #pragma omp parallel for schedule(runtime)
        for( size_t i = 0 ; i < len ; i++ ) InnerAlgebra::for_each15( beg0 [i] , beg1 [i] , beg2 [i] , beg3 [i] , beg4 [i] , beg5 [i] , beg6 [i] , beg7 [i] , beg8 [i] , beg9 [i] , beg10 [i] , beg11 [i] , beg12 [i] , beg13 [i] , beg14 [i] , op );
    }

#endif


    template< class NestedState >
    static typename norm_result_type< typename NestedState::value_type >::type norm_inf( const NestedState &s )
    {
        typedef typename boost::range_iterator<const NestedState>::type iterator;
        typedef typename std::iterator_traits<iterator>::value_type value_type;
        typedef typename norm_result_type<value_type>::type result_type;
        result_type init = static_cast< result_type >( 0 );
        const size_t len = boost::size(s);
        iterator beg = boost::begin(s);
#       pragma omp parallel for reduction(max: init) schedule(dynamic)
        for( size_t i = 0 ; i < len ; i++ )
            init = (std::max)( init , InnerAlgebra::norm_inf( beg[i] ) );
        return init;
    }

};


}
}
}

#endif

/* openmp_nested_algebra.hpp
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
*/