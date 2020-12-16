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
nNG6N9r1YuvOvhNLM0Lk9mk2XA47XCbuDV+fSwc30B8Vmwn53Ksfgs2F/NWEU7hQ764Wy//OSCUDq6upqYElbXnZl6CMzCZjZSM0aVrcFGfv5Ic4t543wL4/mJk2N/xOEnOFmDKxRoAeI5jN909q2bg3HmIeeTbnNe6NNSK7q/1rNrN4N5UFr2TFBUJyEZKtZpZpQzCTZzKHTHKlm3MjU/Bik7JsinadYHKlDmKJUTKCVwAiSzcOCWzDOk2FvjQd7gN0VkJ5HyBNVxXKFaAKsuCdaUCm/bPVr9zM709wLwuTZM6z3Ef0rgX+NcRS33MHLt+5/bpFWLoTC2Hjww1vQPyx7o3ibxKhQ+gHJhKcBWKhxqpe9GBg29t1vT3eGJSVt5WsDi0OLvcXTG+ulYYnAuI6EuoK8c7XN92T6F/HZsPvhYw82uTOxcW4+EeCk3Uz8xS3DZ2DUH5vXrhDp2TNQGScwWeo46ZUbDYGrWKXwoJdihEKQgw8Aop3k5EQikLu8UvAImWowccoEkMfh7seuhwldYZVkQQF9xHdnVFgF0wHOY4KcKxUxEaIRTVD5SipGdBXjtIpFd0AeEbpC5WKqAi2rFGhzFjc6zDJa+CtHNVJ2xOKxp6Qd9QJq6NzduAaRmBHiPXsBmZnVrW3whLBHf1bH/P7WVbWzcK46yVXijiuVmEPKEZujq9iBvx8sq2eh46Eg49lRnJT8QP9D0nwqwt/LXZYCqYjdarYvUz7jSjUmTXi/+KHixFmv8uoZgprYHQfmbEQA9rp9bk2O3fltc5inPp4CZuATVwE+uNjYvsUq15+uSwddcTbgEPxFh+8sPNvSznQOHdTvrJSsY/vTKNsqRjJTzp0zTQpFZP1DIvWRp6yRcpGcIxsSbXg3Q/vWLxTPAtMvgpQEQ/2gH0gFQC6Clo+0hGPGvMQu/a7Htd2ytDoxtjXNbM/0v691uKKF+Ey4PpgOG/3v1uMkFeCITZ1K+Bc9clVpJPAljkVoqB8ilaK5iwo13WkHEfK9a0pLyTlzS2UZwnK49tQLpgqOtDp9fYHWxBHCMS4VTzN1TGjV4rFmS6NwL9ePTnzDZ4Jn2/y/p7VYFUvvR/NMIxry27Wl5IJz75w1mymSe4aqmRGezIsAGLkrm6txjP7watq3hR4j8CryAX5SlqIxx1OG6GkdSr0uLtEnN1ikzI5wJ82ufCFiY5CEcZo7QBla1J6nCusIN+bhnlUKoHehUm3xThjlXSofpQTg+weru6+MDHpcjMVtpJrLNoZ9jNhQTt/T+unDeV2QSMD53Uv1rHLitXKFlOYjOVqLk+6Nwollu+6EID/tlj11y1JDiKihdbMh1qus1+CG9tzeKnn7dY6Z1rIA0KN94kDQspGJlTu+8HIsstKbfJOV4jbZ2zqk5q8Uy5fw3MkSRNj5LJnRS77gEYRdIIIcCuSPY7Pwhbu1T5g8/YDwWNc/QFd/XgQivVWcOMkW+PTXROHvu/phwKbFPNnN0X6KvYH/v5aSwNuKdQLjwVLW97Nj/It06pKV+hJi2sBUgHGBEeb9s66lmaxWlujfHyB6EvP4Ib4P/apHkfrM/eh1uOzLDSSaeLrP1MSD1ANZ3g4tMaggdPPpOfYZly9cSrl18FzBD0K2KGy98lC37NFSG+cOC1AXZ5RvtcZ7j7eE9p5PMoVkTQrzumMItzVfmOLJBqVUHEtb052rlXNM0valULneVN9YVFieh4kXxggb1WfXRFkYAhuTa8MAM6+rU41yJVXm8BttH0Br4JdhCy4lNFSpVZfRqSOIpj0aDB5hnujiHUNC9ZygvrcA21V9+XjtG66Vqo7/g6qbn/BUTTzsKrLgvJZtCpA0mk=
*/