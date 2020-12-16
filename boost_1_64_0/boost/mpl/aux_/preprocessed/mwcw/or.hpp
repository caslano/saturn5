
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/or.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< bool C_, typename T1, typename T2, typename T3, typename T4 >
struct or_impl
    : true_
{
};

template< typename T1, typename T2, typename T3, typename T4 >
struct or_impl< false,T1,T2,T3,T4 >
    : or_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4
        , false_
        >
{
};

template<>
struct or_impl<
          false
        , false_, false_, false_, false_
        >
    : false_
{
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename T3 = false_, typename T4 = false_, typename T5 = false_
    >
struct or_

    : aux::or_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4, T5
        >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , or_
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , or_
    )

}}

/* or.hpp
kS2yRbbIFtkiW2T7f9wOzvN/fkZDPP9bz+9ZxvN7ip7fZ0LFLzuSk5DrNY/om5uebBqhz/W+0E45ADVn+lOicgAypzj9hurn1Z5JvvOaTTQv+6DmNe9D3qSc6CW2/pBZo+6cLsHyGCvWwGceN71wmns/RjmZeSeu/zuS3XW4Zol9HVyqQ1eNiXRGevGZKrs61PnuYPs6mPa2yV5b2WuD9MZeQomNvTrfkYw9vxwhExUPcKbKH4GcSPkptuUXpudnEq0SZj/xzx1JAT513C4fHpQPq5FX0Cu19yGrKCv0/CDKTeo+p1vd5TG+pHM6zC/W4DLZvxTpa42j3WhnH+th5q3198Xso5REQcoL4pfr/yT500f+JCwN5I+TUJLwYjXs8m1Tik8ejmLl4T9ZfvRDzkrkc14/lEt0mJV8pv62lU/UGyfiqt7P9c/tE/M7e3/Kbf1Jy5q9H+0RzCezjTbKpx7yKQnpz/+ib/LzaUR+Tn3eb6K+YuYg9sm7qtgmxUkptsmISeGrxacNnRTu6fMtxFPwN9XOX3cTKqYmhDy7pbdShvLmNuHf1Tlteyc7dGzeLZ5jvfp5js2qOdbXc6yw5thJ7nlKjl1/s/tY0fQcJ3mU3TmCQmorz/nrTNtYWbUdbGovn/aL82u/+Jr2w/4hLTdznpMx1o1j5TepnsrN65f3yPv5Sc10P13G542cYm7/9FnrvpSldhuQ5Nu3EpRzf6T61nDkND5TudzvXJ1jJdEJPQ9OOH3dp2/l+/Qt9nN9/C2Xv8fr+72brs+U27z+Dsly//RxX6Bhf7eH6q/xXe6bm1Q5+xs1xj/4a6Nq/4rt/UvLUj7c6APgozd/s5/POdrfo7jCKfruWo+PyqPs0+Z9Dq8dz5fCZ6JX+NfJuqAPzv3HJ5bt8NrxjIOS8NHWv/rdsxvqujf93qnE4peqr8yC1rXnrOV39cUX2n2yfn0l2PV3pNGXpubMtn6VqD+p/xj3KXd8rKct6FNd/2jfpxa0sL+OS+7y1n1o/n/wOl6svPtpjfAP/kHXcYXpn811HHcAfPTJwc/+Tr/reo8ZP2yeF+1XefZzq89Jo1LvOXHvH3m3/TlKPML+ui+522iD/+B1v+MI++u+3PTvN3jdxysvfSJOt4DdoXXdV5l++1z3B65vBbnubb8zqrR/kW/fpG8Fvgesuse3v+Ws9N2/eJXvfgX7dvn8d6jdFuuesQAZYrXbve52yyniGaXQlZOemzsnrYBA6VyyovLEUmfbeeKW20S7n9V7OoznJx3r5WCzidX2XmuZOdUx17HG9enxIcvIn1fROFBsQKBYhUBxwIHipAPlY/vvycN3oOOb7eO8A+X/CxQPHSjuPFB8ecPFTzvdMR5/WfDSn6teHBw39q2jB378+dz+4cdVN1T89PfuPGMa89NYIOEU7nGkjbrQiNl1x5Ckw5ZwCkyEGbA3nAbHwGx4EcyBF8M8eBnMh0uhE94HL4Yvw0JYAYvg+9AF98AZcC+cBdvgzyWwG7wUDoFz4Wh4GZwOL4cFsBi64DxIvYhD1tihxo5S9FvNpXqdzudawMGwNRwCk+FQ2AcOhwPhCHg+HAkvhKPh5fAsOB+OgXfBs+FKOE71HA+9+SvkR1f50QQm2sQLH6F44c4w2cyDqLGpttI34427S/9YxQ8fJ71UJEV6Z0rPzAcyQed1ImwFz4PHwvNhCvwDHAInwRHwAqNdS0sCt2tr+RMLD/OLH24P2yquvh0cCOPhOMURT4cd4TzFYZfALnCl4rBXG3HYTofG4OBl8uNwmCk/jlP9jlf9ElW/JJ3fE+ApsAc8CybDCbCnznNvOAf2gZfCE6E3P9BSjRXKrhlz1U92+8M=
*/