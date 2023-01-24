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
hL/JecE7o8ZnPJ8YpVjZK6Zi0lvl2Wf7Od6wnqA5+Y08OCoh++ldrO093MCNbjcIrvW+auW/aHgQT+4VY4GbFPJJ6XpUS7aKvcGLzafpwvwrziQdQjAU0IWHn7ast1OGtyiAMFfL+aqjoFL4M5lUps+8nXaXr9ZDv8TcAPyN41PP6yj0eXPFd0xD2Gjn6/3BgIODxa0w38edcPAXiQ57IVww7dx9la4HT6mR/YP14HpAJvtSCWnLotZZpq+sOhfvogsGa578YxtLvWKc8WwmtJ4pJ3IM1cRWeEi63jjHx9YOdD3ZUxc6+Vnrs+bys+j8DKv72ylO34f11rNw/wydIVYZ2YXVQpn4ulFWlc4Xt0r30uVHz2wt+7KPpZ8T5Inu8k3Us1VK53/Uyr824flWlXwyz89dxM18XugtB9kAx9iu7u8o1KEUltEGilm2XMT31lh1Z1stq4aX259bD0QPbRvetv1lGZ4fVcueEvM5/6GnaTl/KGUQv7rfxVoWTOJyPOluhFGWOZc9pQ6TrlfI/2fy3RudklIe8Ux4y6J8bX1BOvNTPKLRs63CijtUnqyvMoT7U3jnsO8HxYCN/sa4Wg/mmrWF4ZQ4fmkV3/fKYcGf0XDohe2m+T51L1gZRk2ZXWW+heuN2D/U891vBSaX6keQGYOQE6vQs2B7antAfmdkZwzqZURR/bn9tUF1KxM2YuYZkyuJJ61hinIG
*/