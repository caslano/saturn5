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