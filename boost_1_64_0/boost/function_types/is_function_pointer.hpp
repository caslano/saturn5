
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_FUNCTION_POINTER_HPP_INCLUDED
#define BOOST_FT_IS_FUNCTION_POINTER_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_function_pointer
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag ,detail::pointer_tag> 
        >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_function_pointer,(T,Tag))
    };
  }
}

#endif

/* is_function_pointer.hpp
pv1GhvMeVO0exNUlKXxyqDJkc4PY967FCFgljJ2RCbTp0lO+ckEBqgs9mcOhsdC4sJSN73OjRySP7A5dYjScBl+okOTqSiZUDlqxO4h99lCkb2sfUX/MFzQkjmDWd5bCzimebUkQJp+AZPL9cx7Wph709F06fd4oTS/M7CCee4gqr/QhPtmNmnwX4qFGNhv4uxBlI3axqW/sEKbwmyfUbyex79I0uHUCnZxxmBL27sJfMT0qLTpHgx8H8FA1CuIb3Gl6VQSZ+Y1hI04cJD3heurtD8SqcVqsqySLciozWJiQM8LMHuCrdjJVpzZAWnoKFTwxxJK0Plr5mJGpuznNwB2y6ltAW3QDMPVkE708N5xFO2Zi/NhrLPxZLpUbapLE8AvQn/SFvansR+vtNSzk2VtUJlpy5+CVdO7CG4FHYZiUYsw+tFyjp++1MMJjK7VayRKZ9FIZT2St2UaYOPs6H7VaBMEyAqaWqwpfLUW49EiQ6g7Om8Y/pRQdJ1YtxUjqxALKWqhKTrIXoHRyEX3ZfZcX+Syjs6sfsGcul0jLppoqR/+hgTMjsIV/wVsFD9ap/pcUTnvRkHNqVFGRxD6P+kH/QhbT8Z2rSP/EPe5Ku+Dl10piBskYOP0a53KLBDPNn7tKTKNJ2ccwRnCGyjq/sZZncZSr2MQdBTqqvLaLFl/2w4sjm3igeSFd0AnBeAkbspzzm9k93wi+VYSXOz6ktfclecSrN/Td9CKyE5wp79oZ3mRai7Oq61hkbQUVZwnTvo5FpKzgybKpA/MqtXBuRwZ92dxBRqvD6PyzMWy0rwhOHlMhoxXXEf/LH98Ve3DsQjYvPRYEy1nEtntvxNBSBYxV2IQZc+9zmfOVZCk6jBqNh8FG04try0+ByKGP7I71KRqeJs0PT4ylvnNhZPO7E09dvHCw7xvtu5/HIo6vIYtpkSxRJ4h+dN3j+bmv0bTmHJ/b40AvF9yET8ZDGP8L5yZZtXRv7T9cXuqBaavUufLqJIrdsI2Udr0npYWKSJS0RsOPQTIyEjAdOeLf1tpDpPAQNp88gy2243mh5BnsitwNw6KN5F34ncSFxGlKtCOuW26l6ekHWKidIkWHbcDB7X506+UKjDqmQK3Dd/P7rjYQsA7+fMlCim2NoPrJtlR1PQphV++icvRl9trZBCETb/NCaXns824kjRYL8rn/nsxSb9COi//4nimmuGUthCdV16jzoCvsyhdS1LND7MrOBtphN4eKlgnuw4LjeC53nRw1OpiYfDTNOFnImt9MRGZTJt914xt6qlKZvVQ2fYiwxIafwSi8fQTq0UNowZERfO3iRrqS3QBvizO0+3kxJts3U+7sx2xXiQsOrrxK0jsmkEm4GatxC6CLBwvp36EBmvpBH+d8TpJI8nG2fb01xJvNeOfK04J51siD3PbSpTJinhl6VO2qASZ5H3NDL7M+Y328a4tj5+0Xo7dfic3tNiT5tv9gtVkP0m8PwGiGIC9K3UQv26fQqsYA/unDYejJfaO9Fw0Q2WLOy/2uIzyjm2eOO03THB7gllMXhB1D2LSoKkRPkmTJ89bCfPZk3pf1HXuuBeKteQ51+Q+S+AEb2q9zl18zeEZrH2TznpkqZL9jJM+33kqD7yXIuVsXjhEveZHEUxiN10Lm3hg6Hm3NS3zOY3H3WT7rgBcOhC1lB8oCKTWhi5SGvaL04e40b2QP/uxzZeJDbpPIh7kkkb+OjI8fYqWBN2AsUsz9BT4oQeM+V+v1RnlWGS6m7cNn3gcK7iTpTH0MV9dApuxjXvMYZBwxDnezftHS4pe0fa0W7GRU8ae/BlL3Y+AyMockT3yH463ppLl5Ph5nbEPm5SK2a7o=
*/