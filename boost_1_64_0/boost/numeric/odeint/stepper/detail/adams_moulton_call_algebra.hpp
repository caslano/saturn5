/*
 [auto_generated]
 boost/numeric/odeint/stepper/detail/adams_moulton_call_algebra.hpp

 [begin_description]
 Algebra caller for the Adams Moulton method.
 [end_description]

 Copyright 2011-2012 Karsten Ahnert
 Copyright 2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_ADAMS_MOULTON_CALL_ALGEBRA_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_ADAMS_MOULTON_CALL_ALGEBRA_HPP_INCLUDED

#include <boost/assert.hpp> 

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

template< size_t Step , class Algebra , class Operations >
struct adams_moulton_call_algebra;

template< class Algebra , class Operations >
struct adams_moulton_call_algebra< 1 , Algebra , Operations >
{
    template< class StateIn , class StateOut , class DerivIn , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const DerivIn &dxdt , const StepStorage& /* steps */ , const Coefficients &coef , Time dt ) const
    {
        typedef typename Coefficients::value_type value_type;
        algebra.for_each3( out , in , dxdt , typename Operations::template scale_sum2< value_type , Time >( 1.0 , dt * coef[0] ) );
    }
};


template< class Algebra , class Operations >
struct adams_moulton_call_algebra< 2 , Algebra , Operations >
{
    template< class StateIn , class StateOut , class DerivIn , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const DerivIn &dxdt , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        typedef typename Coefficients::value_type value_type;
        algebra.for_each4( out , in , dxdt , steps[0].m_v ,
                typename Operations::template scale_sum3< value_type , Time , Time >( 1.0 , dt * coef[0] , dt * coef[1] ) );
    }
};


template< class Algebra , class Operations >
struct adams_moulton_call_algebra< 3 , Algebra , Operations >
{
    template< class StateIn , class StateOut , class DerivIn , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const DerivIn &dxdt , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        typedef typename Coefficients::value_type value_type;
        algebra.for_each5( out , in , dxdt , steps[0].m_v , steps[1].m_v ,
                typename Operations::template scale_sum4< value_type , Time , Time >( 1.0 , dt * coef[0] , dt * coef[1] , dt * coef[2] ) );
    }
};


template< class Algebra , class Operations >
struct adams_moulton_call_algebra< 4 , Algebra , Operations >
{
    template< class StateIn , class StateOut , class DerivIn , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const DerivIn &dxdt , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        typedef typename Coefficients::value_type value_type;
        algebra.for_each6( out , in , dxdt , steps[0].m_v , steps[1].m_v , steps[2].m_v ,
                typename Operations::template scale_sum5< value_type , Time , Time , Time >(
                        1.0 , dt * coef[0] , dt * coef[1] , dt * coef[2] , dt * coef[3] ) );
    }
};


template< class Algebra , class Operations >
struct adams_moulton_call_algebra< 5 , Algebra , Operations >
{
    template< class StateIn , class StateOut , class DerivIn , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const DerivIn &dxdt , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        typedef typename Coefficients::value_type value_type;
        algebra.for_each7( out , in , dxdt , steps[0].m_v , steps[1].m_v , steps[2].m_v , steps[3].m_v ,
                typename Operations::template scale_sum6< value_type , Time , Time , Time , Time >(
                        1.0 , dt * coef[0] , dt * coef[1] , dt * coef[2] , dt * coef[3] , dt * coef[4] ) );
    }
};


template< class Algebra , class Operations >
struct adams_moulton_call_algebra< 6 , Algebra , Operations >
{
    template< class StateIn , class StateOut , class DerivIn , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const DerivIn &dxdt , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        typedef typename Coefficients::value_type value_type;
        algebra.for_each8( out , in , dxdt , steps[0].m_v , steps[1].m_v , steps[2].m_v , steps[3].m_v , steps[4].m_v ,
                typename Operations::template scale_sum7< value_type , Time , Time , Time , Time , Time >(
                        1.0 , dt * coef[0] , dt * coef[1] , dt * coef[2] , dt * coef[3] , dt * coef[4] , dt * coef[5] ) );
    }
};


template< class Algebra , class Operations >
struct adams_moulton_call_algebra< 7 , Algebra , Operations >
{
    template< class StateIn , class StateOut , class DerivIn , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const DerivIn &dxdt , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        typedef typename Coefficients::value_type value_type;
        algebra.for_each9( out , in , dxdt , steps[0].m_v , steps[1].m_v , steps[2].m_v , steps[3].m_v , steps[4].m_v , steps[5].m_v ,
                typename Operations::template scale_sum8< value_type , Time , Time , Time , Time , Time , Time >(
                        1.0 , dt * coef[0] , dt * coef[1] , dt * coef[2] , dt * coef[3] , dt * coef[4] , dt * coef[5] , dt * coef[6] ) );
    }
};


template< class Algebra , class Operations >
struct adams_moulton_call_algebra< 8 , Algebra , Operations >
{
    template< class StateIn , class StateOut , class DerivIn , class StepStorage , class Coefficients , class Time >
    void operator()( Algebra &algebra , const StateIn &in , StateOut &out , const DerivIn &dxdt , const StepStorage &steps , const Coefficients &coef , Time dt ) const
    {
        typedef typename Coefficients::value_type value_type;
        algebra.for_each10( out , in , dxdt , steps[0].m_v , steps[1].m_v , steps[2].m_v , steps[3].m_v , steps[4].m_v , steps[5].m_v , steps[6].m_v ,
                typename Operations::template scale_sum9< value_type , Time , Time , Time , Time , Time , Time , Time >(
                        1.0 , dt * coef[0] , dt * coef[1] , dt * coef[2] , dt * coef[3] , dt * coef[4] , dt * coef[5] , dt * coef[6] , dt * coef[7] ) );
    }
};




} // detail
} // odeint
} // numeric
} // boost



#endif // BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_ADAMS_MOULTON_CALL_ALGEBRA_HPP_INCLUDED

/* adams_moulton_call_algebra.hpp
U78Xd0C4P4Bg0BCkDgjz6tsowIf1rRGWbx8oWXZBQln4zcCvBL9dgV8dfo8k/ut0QJkcZ1LqrN45ukK5F06HVJlSy7a5jvbdmj0JUrao39aRdXN+/WnSV/OomXojajI3z6o44yKF1GxW9X4ktEJzotU34EM20ZTAuLgYRVWGlvtdnd1Hb3GaCvKpdNfWe9P87iPF8pIiiFReU/LJEMkCNVqBl02tQRUrmUbUsjIxOjkrxmWyqa/s9fubIpKzol2o5277hA7Y1H4fCU95jSu8ID9x73SlHqTLDzgvRFHigr88tbcok0XZjdyBoGSaoHBlnZF1a7xs9WRtGzz3wrhYyea0qMORObmp18LVe4JwC17KuhCatuss8vhxcbEOyTPGoukyGxdwPZmRQXRlZFyscp1pGE/QyUuXwC3I96SblHoReV0z2XK/s6dV/QHytqoVRqqWYHv9Sb8f7MZa1cFgF+SjQbBftidM3Ue5HUHlIeVFkEJ4no04TIj6uQY+myoL2OzQWdUva0RUK7bi0G71niEwDjUF+fK99Zo8rerbAtMYlIuW+7q2yYNSzPHfblZfrmkjSJs67EOwtptVtVcuX6FDS892hDcWw+OQrepwoNPKBH8kUYQwq7JbfUKQimkWygG5bDKSJd9qksvGwpOnpgAjD0XN+hNrxRLETAYzcnk8s8A/m3qFiDYHo5nv1k0GRFnVBFAAwqfkEa13+R5g1pxEru4jIfKST7UubEaSZHF0sqrKpjbldoRb1fntgsxW9SYE5alvws22qjtFfGTr+FEIYiW8LKIsraWojt9ES+y/Wr0Wem5TN30AvhaiHe30RKEAqJ1dykQjqsczAQ3E5JlgUiaaPRPMykSLZ4JFyYws8GQgr4DkI2i4x8XFQ/ZQM51S366yTKppU3NlaRW+vOtPYKvwu2qwZLkWv0evliy/x+8T/CTAXdBMG+DPx3s+YBfe5wP24PcA0n2Nnwx//U+0OKm7rnt3vcEYEhpm6qQL7/7PeCLwM+PXuUswRBaupWu35b8FjzX4fYOfMkT7vTX4X2dz/5cem2OwfXKW0eKIVl0bDFLA3rjOcwzVgtMc8xyx6uENQuMTawrq2UmY2coWIgx2aCZeDr9VHS1QosVgIL+g/nT5Mbmp/LDLmFiTX4/kCYFMjUoYrFWnbPWeD4Uxtqr9BUEjQvtY1R7NQLh/sGrZI3CY7a5XtDZ/8BWh9Y48wbZNfU7AZsFOAXq/M33QjIzqA0iMRmYmW7Bk8Bzt4uyc459jUp/X6NZnq/tEr2USOZyefnUs2GkVbVUfAoVstTezOIQMIAs9JMFc1IjdmsU3wuJ3sUGmQBLdhKurVT22nlbt2/UiKLHmNIWy2pmh6lt/CvI3/rGZvKuLVX1KkDKSFPs8C/rGMPWSt9Exh6iL3ta6ZIfOcQus2nrNpGz965LE6Gs9y5cBN5iXvqA+N8DXVS18OUeLAcrre5q7Ele0VY3UmIKhC3KXPxXJ1aq3MELRuLl8vVC8fgIhBsKJsKnvr2uFveMsHqvNHoYuW7CyH0SCUIxySN25Tiv2ETA7CFWSYFVLEWRD1B14K11YN9uc5ykS9LJ7do76m71CJb7ffUHN97shqwLw82PctLQHZ7rcq0TCY1VDtaIMIyOuGKvaZV1Q9WVkJNrI7H2BNjJoXUs1bzllVv7LOGppl582RXBIVAvksP49v9+bafZlzAADbE2ejOvVYlGWmEBZTlsMR5QfBNW690TJO2JV84qGagDDj2yeFWJJ3Owpi0vhrKIsLgsvm7JBvDHQHOQbCR3E414ULXFYePzNwLCwx3vBYeF57gZ/gbJUUEjcoY4D2dLNzAEaUlnN9vHkPqo=
*/