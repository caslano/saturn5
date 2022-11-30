/*
 [auto_generated]
 boost/numeric/odeint/stepper/detail/generic_rk_call_algebra.hpp

 [begin_description]
 Algebra caller for the generic Runge-Kutta methods.
 [end_description]

 Copyright 2011-2012 Mario Mulansky
 Copyright 2011-2012 Karsten Ahnert

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_GENERIC_RK_CALL_ALGEBRA_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_GENERIC_RK_CALL_ALGEBRA_HPP_INCLUDED


namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

template< size_t StageNumber , class Algebra >
struct generic_rk_call_algebra;

template< class Algebra >
struct generic_rk_call_algebra< 1 , Algebra >
{
    typedef Algebra algebra_type;

    template< class S1 , class S2 , class S3 , class S4 , class Op>
    void operator()( algebra_type &algebra , S1 &s1 , S2 &s2 ,  S3 &s3 , S4 * /* s4_array */ , Op op ) const
    {
        algebra.for_each3( s1 , s2 , s3 , op );
    }

    template< class S1 , class S2 , class S4 , class Op>
    void operator()( algebra_type &algebra , S1 &s1 , S2 &s2 , S4 * /* s4_array */ , Op op ) const
    {
        algebra.for_each2( s1 , s2 , op );
    }
};

template< class Algebra >
struct generic_rk_call_algebra< 2 , Algebra >
{
    template< class S1 , class S2 , class S3 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 ,  S3 &s3 , S4 s4_array[1] , Op op ) const
    {
        algebra.for_each4( s1 , s2 , s3 , s4_array[0].m_v , op );
    }

    template< class S1 , class S2 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S4 s4_array[1] , Op op ) const
    {
        algebra.for_each3( s1 , s2 , s4_array[0].m_v , op );
    }
};


template< class Algebra >
struct generic_rk_call_algebra< 3 , Algebra >
{
    template< class S1 , class S2 , class S3 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S3 &s3 , S4 s4_array[2] , Op op ) const
    {
        algebra.for_each5( s1 , s2 , s3 , s4_array[0].m_v , s4_array[1].m_v , op );
    }

    template< class S1 , class S2 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S4 s4_array[2] , Op op ) const
    {
        algebra.for_each4( s1 , s2 , s4_array[0].m_v , s4_array[1].m_v , op );
    }
};


template< class Algebra >
struct generic_rk_call_algebra< 4 , Algebra >
{
    template< class S1 , class S2 , class S3 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S3 &s3 , S4 s4_array[3] , Op op ) const
    {
        algebra.for_each6( s1 , s2 , s3 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , op );
    }

    template< class S1 , class S2 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S4 s4_array[3] , Op op ) const
    {
        algebra.for_each5( s1 , s2 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , op );
    }
};


template< class Algebra >
struct generic_rk_call_algebra< 5 , Algebra >
{
    template< class S1 , class S2 , class S3 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S3 &s3 , S4 s4_array[4] , Op op ) const
    {
        algebra.for_each7( s1 , s2 , s3 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , op );
    }

    template< class S1 , class S2 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S4 s4_array[4] , Op op ) const
    {
        algebra.for_each6( s1 , s2 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , op );
    }
};

template< class Algebra >
struct generic_rk_call_algebra< 6 , Algebra >
{
    template< class S1 , class S2 , class S3 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S3 &s3 , S4 s4_array[5] , Op op ) const
    {
        algebra.for_each8( s1 , s2 , s3 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , s4_array[4].m_v , op );
    }

    template< class S1 , class S2 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S4 s4_array[5] , Op op ) const
    {
        algebra.for_each7( s1 , s2 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , s4_array[4].m_v , op );
    }
};

template< class Algebra >
struct generic_rk_call_algebra< 7 , Algebra >
{
    template< class S1 , class S2 , class S3 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S3 &s3 , S4 s4_array[6] , Op op ) const
    {
        algebra.for_each9( s1 , s2 , s3 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , s4_array[4].m_v ,
                s4_array[5].m_v , op );
    }

    template< class S1 , class S2 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S4 s4_array[6] , Op op ) const
    {
        algebra.for_each8( s1 , s2 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , s4_array[4].m_v ,
                s4_array[5].m_v , op );
    }
};

template< class Algebra >
struct generic_rk_call_algebra< 8 , Algebra >
{
    template< class S1 , class S2 , class S3 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S3 &s3 , S4 s4_array[7] , Op op ) const
    {
        algebra.for_each10( s1 , s2 , s3 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , s4_array[4].m_v ,
                s4_array[5].m_v , s4_array[6].m_v , op );
    }

    template< class S1 , class S2 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S4 s4_array[7] , Op op ) const
    {
        algebra.for_each9( s1 , s2 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , s4_array[4].m_v ,
                s4_array[5].m_v , s4_array[6].m_v , op );
    }
};

template< class Algebra >
struct generic_rk_call_algebra< 9 , Algebra >
{
    template< class S1 , class S2 , class S3 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S3 &s3 , S4 s4_array[8] , Op op ) const
    {
        algebra.for_each11( s1 , s2 , s3 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , s4_array[4].m_v ,
                s4_array[5].m_v , s4_array[6].m_v , s4_array[7].m_v , op );
    }

    template< class S1 , class S2 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S4 s4_array[8] , Op op ) const
    {
        algebra.for_each10( s1 , s2 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , s4_array[4].m_v ,
                s4_array[5].m_v , s4_array[6].m_v , s4_array[7].m_v , op );
    }
};

template< class Algebra >
struct generic_rk_call_algebra< 10 , Algebra >
{
    template< class S1 , class S2 , class S3 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S3 &s3 , S4 s4_array[9] , Op op ) const
    {
        algebra.for_each12( s1 , s2 , s3 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , s4_array[4].m_v ,
                s4_array[5].m_v , s4_array[6].m_v , s4_array[7].m_v , s4_array[8].m_v , op );
    }

    template< class S1 , class S2 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S4 s4_array[9] , Op op ) const
    {
        algebra.for_each11( s1 , s2 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , s4_array[4].m_v ,
                s4_array[5].m_v , s4_array[6].m_v , s4_array[7].m_v , s4_array[8].m_v , op );
    }
};


template< class Algebra >
struct generic_rk_call_algebra< 11 , Algebra >
{
    template< class S1 , class S2 , class S3 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S3 &s3 , S4 s4_array[10] , Op op ) const
    {
        algebra.for_each13( s1 , s2 , s3 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , s4_array[4].m_v ,
                s4_array[5].m_v , s4_array[6].m_v , s4_array[7].m_v , s4_array[8].m_v , s4_array[9].m_v , op );
    }

    template< class S1 , class S2 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S4 s4_array[10] , Op op ) const
    {
        algebra.for_each12( s1 , s2 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , s4_array[4].m_v ,
                s4_array[5].m_v , s4_array[6].m_v , s4_array[7].m_v , s4_array[8].m_v , s4_array[9].m_v , op );
    }
};

template< class Algebra >
struct generic_rk_call_algebra< 12 , Algebra >
{
    template< class S1 , class S2 , class S3 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S3 &s3 , S4 s4_array[11] , Op op ) const
    {
        algebra.for_each14( s1 , s2 , s3 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , s4_array[4].m_v ,
                s4_array[5].m_v , s4_array[6].m_v , s4_array[7].m_v , s4_array[8].m_v , s4_array[9].m_v , s4_array[10].m_v , op );
    }

    template< class S1 , class S2 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S4 s4_array[11] , Op op ) const
    {
        algebra.for_each13( s1 , s2 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , s4_array[4].m_v ,
                s4_array[5].m_v , s4_array[6].m_v , s4_array[7].m_v , s4_array[8].m_v , s4_array[9].m_v , s4_array[10].m_v , op );
    }
};

template< class Algebra >
struct generic_rk_call_algebra< 13 , Algebra >
{
    template< class S1 , class S2 , class S3 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S3 &s3 , S4 s4_array[12] , Op op ) const
    {
        algebra.for_each15( s1 , s2 , s3 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , s4_array[4].m_v ,
                s4_array[5].m_v , s4_array[6].m_v , s4_array[7].m_v , s4_array[8].m_v , s4_array[9].m_v , s4_array[10].m_v , s4_array[11].m_v , op );
    }

    template< class S1 , class S2 , class S4 , class Op>
    void operator()( Algebra &algebra , S1 &s1 , S2 &s2 , S4 s4_array[12] , Op op ) const
    {
        algebra.for_each14( s1 , s2 , s4_array[0].m_v , s4_array[1].m_v , s4_array[2].m_v , s4_array[3].m_v , s4_array[4].m_v ,
                s4_array[5].m_v , s4_array[6].m_v , s4_array[7].m_v , s4_array[8].m_v , s4_array[9].m_v , s4_array[10].m_v , s4_array[11].m_v , op );
    }
};

}
}
}
}

#endif // BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_GENERIC_RK_CALL_ALGEBRA_HPP_INCLUDED

/* generic_rk_call_algebra.hpp
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
*/