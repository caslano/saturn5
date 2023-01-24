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
d3inuLuJVB84F8K5iUpvcDv7S9QnyI+IXplN08iDWLc1O7cevFQYyeQ1y/zB/7D5Qo1+Tjdj4eirZPLn2Yz5VmHloI1yUtQW+JNlPfJhrEIR1jowX4AoDc4h7BPwMLSWPPmnTNZzTWkb1Lvhq7tem4c1Uqi2eN43vQb7AG8rVuvhTc3HrMPKw/DX6kjn2WRRKn7Ag2QB63VZbyu7SMfOmeKvzWxfwA9gYXCyYWxUAeoJ82K9HhO0OSVMQLTeSBvuZ6oUb2BZyEeYxNat7sc2zNMlNisC5VW/X/dbEVlinbNA96VR7liu1qv074pY9FCsp+9b5miYHTNDjPc2rOLdRjHPPpj0Ry7Z677V4XpZK3vP2+XuEjHyNtP1hnDPifU7C923vexLM2dPKO2QvVnFdLd6H9zdQfebCvmoeGMfxrPdo00lCcXuTtY+W+2vkjf0VE7mVvq+mR9hpZ9cK6DWgjZuyueiwwNNlVIep5vPc6/4oBH6QOYKyzGf3u0gxGhZrw4wE575mXAY9w/a/m2U43SKmOlz2yhD2j5rPfoOcsUv1muulEM0c/yyMKuYBdqfy1dZD44JZ436geeTNOF+YmuQ4KuzgOlHT2X6/OhBKYR1k8+4N5cpD+7Bh61JPd8Tpfroz9k/LCq8roWlbH9uG0Edhp9mLsCgT9au3ge83j56xcrg+KM+7zZcwy3DTOha3qZXvJ7yhxrdMyqb
*/