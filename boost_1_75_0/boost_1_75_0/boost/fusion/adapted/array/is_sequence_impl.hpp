/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_IS_SEQUENCE_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_IS_SEQUENCE_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct is_sequence_impl;

    template<>
    struct is_sequence_impl<po_array_tag>
    {
        template<typename Seq>
        struct apply
          : mpl::true_
        {};
    };
}}}

#endif

/* is_sequence_impl.hpp
wZv48IzOkDznnI5Ifnmu8FnTXu7NaAg6T+niY8EMkntJhtxLSp1ZIJWS4x5NKnmarxPZBDq+UN+v+myzG0EWIkwVP5NDI19lt5aTihLSjflCIdYZ5nODWJ6bsRZM1vWTAqey+Wd3JDffLRb99EoxrfgyF2F/Xbmo43kge3fo9rh9+v+1Pabt7bA9Mtq1h2X6/709bjuro/Z4/l7RHo/fS+1xCU3xFyzsuD2u/Dp0e8yY9n9tj3E/dNgecrv2aLn+/94e0+0dtceye0R7lNxD7THofmyPM+83rYcFEhM0RvJXfoPZha5zyckOly3jr6e9Hi0T6vAU3pF6v8zd08Iun0A9EUQATt0bbm/TnHQYZUfjvfE5au6FcSCyisC0Fg7e8Fg4D1bFxTfrYmzPddgofvrfgdJhs7H+H0gNAevXDDxSpGZY6hbNsMBNzXAWTR29F4jztkTuwo2DhA39sp8wbiKDPwHJ4UWLmfCpbIvA9q1Fk1nauEnk+becjn7sU9DsLW7Jb7hLeP0z3CUU4oMbIs+7BjYKAjzznSkmLE116eUStl0BAoFCK3yfSw1eYDR4AWvwPKn0BeE/bgXd7UklLyLmiTh/7WKgudpGHIbrNr4jLiU/UfnSQoFg+jEaMXC4XDwy8UVFPpigY85iUjgNlqZuYb/JzhUDwUAy2ze+kXVjljKlECoCH6g70jQNzA/Q7olDr2LE91cYEd05
*/