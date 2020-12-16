/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_ASYMMETRIC_INTERVAL_HPP_JOFA_100327
#define BOOST_ICL_TYPE_TRAITS_IS_ASYMMETRIC_INTERVAL_HPP_JOFA_100327

#include <boost/icl/type_traits/is_interval.hpp>

namespace boost{ namespace icl
{

template <class Type> struct is_asymmetric_interval
{ 
    typedef is_asymmetric_interval<Type> type;
    BOOST_STATIC_CONSTANT(bool,
            value = (mpl::and_<
                        is_interval<Type>
                    ,   has_static_bounds<Type>
                    ,   has_asymmetric_bounds<Type>
                    >::value)
                );
};

template <class Type> struct is_continuous_asymmetric
{ 
    typedef is_continuous_asymmetric<Type> type;
    BOOST_STATIC_CONSTANT(bool,
            value = (mpl::and_<
                        is_asymmetric_interval<Type>
                    ,   is_continuous<typename domain_type_of<interval_traits<Type> >::type>
                    >::value)
                );
};

template <class Type> struct is_discrete_asymmetric
{ 
    typedef is_discrete_asymmetric<Type> type;
    BOOST_STATIC_CONSTANT(bool,
            value = (mpl::and_<
                        is_asymmetric_interval<Type>
                    ,   mpl::not_<is_continuous<typename domain_type_of<interval_traits<Type> >::type> >
                    >::value)
                );
};

}} // namespace boost icl

#endif



/* is_asymmetric_interval.hpp
YtZseal8CmbNkfeWL8OsBnlf+TrMulC+n19/zJorr5AX8XerrHnyA+WTMatRPki+CLMukg+Rb8Ksi+VV8l2YdYn8UHklf+fKmi8f4dsBsy6VH+6/F7Muk4/2+wuzFsiPkm/DrIXycfK9mHW5Xu8d69vtjOJY9RTm/7Mep03YMrpSj9Nq/71YMzXJP+2/F7Oukp8r34PFzmL+X36BfCA2lq6RN8prMGuR/HLfb7HldK18sXw9toUWy2+U78Cs6+QrfDtgfT7Dc0DW7a3CJtFns7wWW0ify/IVmHW9tuedfn0wa6l8rbwVs26QPyQvPpv9jT6PB3z9mLzpbNZPN+r6PylfhW2gZfKf+H6IbaUvZF3PNqyolvn/LB+Ijaebs28vtoSWZ/k6bCd9Mctj5/C8QF/K8jqsiW7R9dym67kUq32oOLZCz1+/8f0Qt27V5Xf64xezbpO/Kd+JWbfL35fn8/eyrJXy6PV63GHWl+VF8smY9RV5d3kjZt0h7ytfjlmr5AfK12PWnfIq+VbM+qr8cPluzLpLPk5ezN/islbLT5QPx6y75ZP9+mPW1+RnyRumcj3pHvl58g2YtUY+Rx7ib3dZ9+K5fDnffy9mfV1+hbwes+6TL5Kvxqy18s/57cWs+/V7l/n6p7F++oYuf6t8KWZ9U36HvAWz1snv9u12HtuNHpDfJ5+CWd/K2j8XYda3s3wNtpXWZ/lebOx05v+zvB5bS9/J8q1YUT3z/3ghXz+g61OFzaQN8od9v8K20nflT8j3YlUzmP+X/8Tv9xlcf3pYx5NfyddhrbRRvkPe53yuPz0i/4Pfj9gy+n7W9V+PtdKjWR5cwPWh5iyvxpbSD/Q67X2/PtguekweWar7aybHW3pcXihvxNbSJnlX+RZsDz0h7yUvncX+Q0/K95dPxhbSD+WD5KuwzZZ8mHw31mc28//yI+SjsRr6kXycX09sBT0tP0G+AdtFW+Sn+u2dw/5JP9b+f4Z8PGY9g+fw9VR5NWb9JGs7N2BWS5Yvw6xntf/Xaz3NmPVTHW9ny3dgsQbm/30ez7cb1kRb5Zf7ejDr51rPtfI2rOhC5v99Pk0+BWukX/p8mm8fzNqm9ayUb8fK5zL/7+9T5PXYavq1v0+R78Ws57Seb8ur5vH8Qtt1+e/Jl2Gb6Xn5Y74ezHpB6/mRvLyR60Mvyp/1/QGzWrWebfKZmPUbeat8DWa9pPtlp3wrZr2s9b8h34NZO7Sed/z3XsT2pFd8/s23J7aLfuvzbzfo+e5itgO9Ku8sX4FZO/V7S+XNmPWavJ98J2b9TtfnAHmfS3j80uta/8HyRZi1S5cf6b8Xs36v/fwo+TrMekM+Xr7Z1kF/kB/vv3c+jxdqk58sb8SsN7MeFysx663s4zNmvZ3lRfwtLmt3lk/ErHeyn0cw690sX4dZ72V5K2btyfIYf4vL+mOWj8Zm0vtZvgproQ+yPLSA4zPt1fY/TdunFltGH2ZdfgO2gz7S5c/0/Wchz5v0J/lUvx+xzRQKkn6BvPhy9gcKy+f5/oA1U0S+QN6GVVzB/L/8GvkUbCUF8uvlW82uZP5ffrN8NDafcuW3yzdgVl6QfNzdJd+BNfP3qfKD5H5+r3wvVsXfiSqQr/PHxW+6x6xC3DbdQ/LlXNbqIP+e/16slYrwzFP+kfwdIeqY5dVYI3XK8iZsNXXO8masjWJZXsHfcKqhLlm+DNtEXbN8L1Y5lr//k+VTsHoqzvJGbCl1z/JV2HrqkeVbsFYqyfI9WJH9raUsL8eGU88sn4jVUq8sX4ptoN5ZvgMr4u8O9cnygdh4KgtC/9ZpJutYQeVB8nXUI36/YztpP/lmeekx3FbaX/4zeQ0=
*/