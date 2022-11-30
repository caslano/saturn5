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
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
*/