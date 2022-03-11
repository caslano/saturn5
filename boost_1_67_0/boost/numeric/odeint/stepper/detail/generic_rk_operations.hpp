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