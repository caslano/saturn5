/*
 [auto_generated]
 boost/numeric/odeint/stepper/detail/generic_rk_operations.hpp

 [begin_description]
 Operations caller for the generic Runge Kutta method.
 [end_description]

 Copyright 2011 Mario Mulansky
 Copyright 2011-2012 Karsten Ahnert

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_GENERIC_RK_OPERATIONS_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_GENERIC_RK_OPERATIONS_HPP_INCLUDED


namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

template< size_t StageNumber , class Operations , class Fac , class Time >
struct generic_rk_scale_sum;

template< class Operations , class Fac , class Time >
struct generic_rk_scale_sum< 1 , Operations , Fac , Time > : public Operations::template scale_sum2< Fac , Time >
{
    generic_rk_scale_sum( const boost::array<Fac,1> &a , Time dt ) : Operations::template scale_sum2< Fac , Time >( 1.0 , a[0]*dt )
                { }

    typedef void result_type;
};


template< class Operations , class Fac , class Time >
struct generic_rk_scale_sum< 2 , Operations , Fac , Time > : public Operations::template scale_sum3< Fac , Time >
{
    generic_rk_scale_sum( const boost::array<Fac,2> &a , Time dt )
                    : Operations::template scale_sum3< Fac , Time >( 1.0 , a[0]*dt , a[1]*dt )
                      { }

    typedef void result_type;
};

template< class Operations , class Fac , class Time >
struct generic_rk_scale_sum< 3 , Operations , Fac , Time > : public Operations::template scale_sum4< Fac , Time >
{
    generic_rk_scale_sum( const boost::array<Fac,3> &a , Time dt )
                    : Operations::template scale_sum4< Fac , Time >( 1.0 , a[0]*dt , a[1]*dt , a[2]*dt )
                      { }

    typedef void result_type;
};

template< class Operations , class Fac , class Time >
struct generic_rk_scale_sum< 4 , Operations , Fac , Time > : public Operations::template scale_sum5< Fac , Time >
{
    generic_rk_scale_sum( const boost::array<Fac,4> &a , Time dt )
                    : Operations::template scale_sum5< Fac , Time >( 1.0 , a[0]*dt , a[1]*dt , a[2]*dt , a[3]*dt )
                      { }

    typedef void result_type;
};

template< class Operations , class Fac , class Time >
struct generic_rk_scale_sum< 5 , Operations , Fac , Time > : public Operations::template scale_sum6< Fac , Time >
{
    generic_rk_scale_sum( const boost::array<Fac,5> &a , Time dt )
                    : Operations::template scale_sum6< Fac , Time >( 1.0 , a[0]*dt , a[1]*dt , a[2]*dt , a[3]*dt , a[4]*dt )
                      { }

    typedef void result_type;
};

template< class Operations , class Fac , class Time >
struct generic_rk_scale_sum< 6 , Operations , Fac , Time > : public Operations::template scale_sum7< Fac , Time >
{
    generic_rk_scale_sum( const boost::array<Fac,6> &a , Time dt )
                    : Operations::template scale_sum7< Fac , Time >( 1.0 , a[0]*dt , a[1]*dt , a[2]*dt , a[3]*dt , a[4]*dt , a[5]*dt )
                      { }

    typedef void result_type;
};

template< class Operations , class Fac , class Time >
struct generic_rk_scale_sum< 7 , Operations , Fac , Time > : public Operations::template scale_sum8< Fac , Time >
{
    generic_rk_scale_sum( const boost::array<Fac,7> &a , Time dt )
                    : Operations::template scale_sum8< Fac , Time >( 1.0 , a[0]*dt , a[1]*dt , a[2]*dt , a[3]*dt , a[4]*dt , a[5]*dt , a[6]*dt )
                      { }

    typedef void result_type;
};

template< class Operations , class Fac , class Time >
struct generic_rk_scale_sum< 8 , Operations , Fac , Time > : public Operations::template scale_sum9< Fac , Time >
{
    generic_rk_scale_sum( const boost::array<Fac,8> &a , Time dt )
                    : Operations::template scale_sum9< Fac , Time >( 1.0 , a[0]*dt , a[1]*dt , a[2]*dt , a[3]*dt , a[4]*dt ,
                            a[5]*dt , a[6]*dt , a[7]*dt )
                      { }

    typedef void result_type;
};

template< class Operations , class Fac , class Time >
struct generic_rk_scale_sum< 9 , Operations , Fac , Time > : public Operations::template scale_sum10< Fac , Time >
{
    generic_rk_scale_sum( const boost::array<Fac,9> &a , Time dt )
                    : Operations::template scale_sum10< Fac , Time >( 1.0 , a[0]*dt , a[1]*dt , a[2]*dt , a[3]*dt , a[4]*dt ,
                            a[5]*dt , a[6]*dt , a[7]*dt , a[8]*dt )
                      { }

    typedef void result_type;
};

template< class Operations , class Fac , class Time >
struct generic_rk_scale_sum< 10 , Operations , Fac , Time > : public Operations::template scale_sum11< Fac , Time >
{
    generic_rk_scale_sum( const boost::array<Fac,10> &a , Time dt )
                    : Operations::template scale_sum11< Fac , Time >( 1.0 , a[0]*dt , a[1]*dt , a[2]*dt , a[3]*dt , a[4]*dt ,
                            a[5]*dt , a[6]*dt , a[7]*dt , a[8]*dt , a[9]*dt )
                      { }

    typedef void result_type;
};

template< class Operations , class Fac , class Time >
struct generic_rk_scale_sum< 11 , Operations , Fac , Time > : public Operations::template scale_sum12< Fac , Time >
{
    generic_rk_scale_sum( const boost::array<Fac,11> &a , Time dt )
                    : Operations::template scale_sum12< Fac , Time >( 1.0 , a[0]*dt , a[1]*dt , a[2]*dt , a[3]*dt , a[4]*dt ,
                            a[5]*dt , a[6]*dt , a[7]*dt , a[8]*dt , a[9]*dt , a[10]*dt )
                      { }

    typedef void result_type;
};

template< class Operations , class Fac , class Time >
struct generic_rk_scale_sum< 12 , Operations , Fac , Time > : public Operations::template scale_sum13< Fac , Time >
{
    generic_rk_scale_sum( const boost::array<Fac,12> &a , Time dt )
                    : Operations::template scale_sum13< Fac , Time >( 1.0 , a[0]*dt , a[1]*dt , a[2]*dt , a[3]*dt , a[4]*dt ,
                            a[5]*dt , a[6]*dt , a[7]*dt , a[8]*dt , a[9]*dt , a[10]*dt , a[11]*dt )
                      { }

    typedef void result_type;
};

template< class Operations , class Fac , class Time >
struct generic_rk_scale_sum< 13 , Operations , Fac , Time > : public Operations::template scale_sum14< Fac , Time >
{
    generic_rk_scale_sum( const boost::array<Fac,13> &a , Time dt )
                    : Operations::template scale_sum14< Fac , Time >( 1.0 , a[0]*dt , a[1]*dt , a[2]*dt , a[3]*dt , a[4]*dt ,
                            a[5]*dt , a[6]*dt , a[7]*dt , a[8]*dt , a[9]*dt , a[10]*dt , a[11]*dt , a[12]*dt  )
                      { }

    typedef void result_type;
};


// for error estimates
template< size_t StageNumber , class Operations , class Fac , class Time >
struct generic_rk_scale_sum_err;

template< class Operations , class Fac , class Time >
struct generic_rk_scale_sum_err< 1 , Operations , Fac , Time > : public Operations::template scale_sum1< Time >
{
    generic_rk_scale_sum_err( const boost::array<Fac,1> &a , Time dt ) : Operations::template scale_sum1< Time >( a[0]*dt )
                { }

    typedef void result_type;
};


template< class Operations , class Fac , class Time >
struct generic_rk_scale_sum_err< 2 , Operations , Fac , Time > : public Operations::template scale_sum2< Time >
{
    generic_rk_scale_sum_err( const boost::array<Fac,2> &a , Time dt )
                    : Operations::template scale_sum2< Time >( a[0]*dt , a[1]*dt )
                      { }

    typedef void result_type;
};

template< class Operations , class Fac , class Time >
struct generic_rk_scale_sum_err< 3 , Operations , Fac , Time > : public Operations::template scale_sum3< Time >
{
    generic_rk_scale_sum_err( const boost::array<Fac,3> &a , Time dt )
                    : Operations::template scale_sum3< Time >( a[0]*dt , a[1]*dt , a[2]*dt )
                      { }

    typedef void result_type;
};

template< class Operations , class Fac , class Time >
struct generic_rk_scale_sum_err< 4 , Operations , Fac , Time > : public Operations::template scale_sum4< Time >
{
    generic_rk_scale_sum_err( const boost::array<Fac,4> &a , Time dt )
                    : Operations::template scale_sum4< Time >( a[0]*dt , a[1]*dt , a[2]*dt , a[3]*dt )
                      { }

    typedef void result_type;
};

template< class Operations , class Fac , class Time >
struct generic_rk_scale_sum_err< 5 , Operations , Fac , Time > : public Operations::template scale_sum5< Fac >
{
    generic_rk_scale_sum_err( const boost::array<Fac,5> &a , Time dt )
                    : Operations::template scale_sum5< Time >( a[0]*dt , a[1]*dt , a[2]*dt , a[3]*dt , a[4]*dt )
                      { }

    typedef void result_type;
};


template< class Operations , class Fac , class Time >
struct generic_rk_scale_sum_err< 6 , Operations , Fac , Time > : public Operations::template scale_sum6< Time >
{
    generic_rk_scale_sum_err( const boost::array<Fac,6> &a , Time dt )
                    : Operations::template scale_sum6< Time >( a[0]*dt , a[1]*dt , a[2]*dt , a[3]*dt , a[4]*dt , a[5]*dt )
                      { }

    typedef void result_type;
};


// for rk87
template< class Operations , class Fac , class Time >
struct generic_rk_scale_sum_err< 13 , Operations , Fac , Time > : public Operations::template scale_sum13< Time >
{
    generic_rk_scale_sum_err( const boost::array<Fac,13> &a , Time dt )
                    : Operations::template scale_sum13< Time >( a[0]*dt , a[1]*dt , a[2]*dt , a[3]*dt , a[4]*dt , a[5]*dt ,
                        a[6]*dt , a[7]*dt , a[8]*dt , a[9]*dt , a[10]*dt , a[11]*dt , a[12]*dt )
                      { }

    typedef void result_type;
};


}
}
}
}


#endif // BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_GENERIC_RK_OPERATIONS_HPP_INCLUDED

/* generic_rk_operations.hpp
ZKE9dPWgqdcaGMLSOYIqAN9qZ/pSxCDpBXuKctwEoynkOunA253502XogEYkjPJXWgwiOKSQJpxdGlpup37WlF36/cNxaiqHPlxYg21tKmQqmY7raEoCErHv0gbGDh9HIeXoWgZA1Rp26nuYk/r64nIfCpU3kPsjWsAAt5NMvttzMaFJZw846KTfY2nDl8yuT2/ElfjoJ3JAvOJcKxsPYeWBcyjCjioaP9u8w4PFX4fIsayq96267rbMmSs/w3Pvz+4CLBXyuUFjnCZ2+TU5zirtsep10aKg7FFrUsWHlk8WbemmvBH9O1ByC+TZ1I61Yg911nodSC570493iuTWnDptZOmcM1d8eFw+ddVNqlmW6NH02IcjtIL3Cng26zyrgIFoAzKmvFNtfRZm7/qWM3nMAuxvVinwaOVCru3PspmQ8tXK4Yllhsids2W928y8cCZ73j4C705D1P0RtKZyrfLU2foOwqlbBS1dPNcIxHU19Kr+3JbPvU0AjkMl+FtcBjHwRMK4LLD3luC3bWNEapWcGpD7r12E7RjR1bUyt8w/Lf/SvzkY5tr5Xg==
*/