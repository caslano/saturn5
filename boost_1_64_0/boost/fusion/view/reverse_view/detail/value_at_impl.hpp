/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_VALUE_AT_IMPL_HPP
#define BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_VALUE_AT_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_at_impl;

    template <>
    struct value_at_impl<reverse_view_tag>
    {
        template <typename Seq, typename N>
        struct apply
          : result_of::value_at<
                typename Seq::seq_type
              , mpl::minus<typename Seq::size, mpl::int_<1>, N>
            >
        {};
    };
}}}

#endif

/* value_at_impl.hpp
oLXqeigbWSYTnInEzURr0ab7cTKdCf4TI+3K09c0f+GsJvAzK1RmoVuY04jjwmzj54lAZsF5YJbz5JClNEc5TFAq7qvNQkvxd947NNYFTHSv2Yt29fb9I8L8aMGU0r5ceJkoDOwmaARk8rNBNDdabMR+RKPjNJoHrQ6zh05Tia+2KzbE2pyt7JJtojmLmuC8Iu30rd0eYb7iJrommYOW/tzHZcICaIsjNhetwq1qfYR5SphgOLO2Y76UEmYraYJFzDYbirahPNHaKtIqp/3+IOVS2gSVmSWanjUWZi9rghCzkHP9fWHe8iaYBtL2ZOlkFOaoYILJzGw/vK4kLIy2idnJyrWvCwtWNEFvZu6BoRbCXJVwrJnxsQ6iNWSW8sHycpRLZVzzEZuH1mvD6QM01mjvmNVNmrRJGFQxQQZF2htPzRs0t1VNcJLF5X/+ykFWzQR5mCW1bLiF5g+tPGtzxuRXc4TpapjgXxZ37OG//1Cb35mgayRuPlog6/7FFFfLBFtAWqeFC6rTWKMlMfvPm0eUi6u2CZ4z69zY46a5rWOCO8welPqxhjB/XRP0Y7b889kzNNb1TBBmea7LdKsgxTUwwXUW96JJOBPNQ0MTVGXW6JmrszCb0wT1meXef1xH44nWntmjuOvDhUEjEyQwo8//0Bwa5kEryYx+PxUtiJabGd0fRIPG6mbXMBeaWi4+DQtptKlroh7nRItnRp9vonnREvk85D7WhWpHa8Cses5zZhrPJBOsYhZ63jGJcmlqgnHMHpfuJ7c/NKM09tkuttFUo75mGvVpmBdNrfYgmvitsAVoe2dbctIctYrseyL26WiLTRSH1kWRdulh1jrUXxsT1GRxnoH3bMLCGuZsq25+tGKsvztzt94VZm+P+09Ww823cYtpjjqawArSuvx0kPY97mR2cG+gkDAf2g5m6xY2nET1dcLjNLPuD1LXo/lDs7E8szRb8Znq62ICC7P6B7LnoPq6miAns61p36QRZutugqs8z0VKL6r9exNsSCmt7Tent1B/7uga8tew9KVx6WeC6szybKgUoNrR2rJcKmR+sZDWxAC2JpIfj9CGsbjyPZsMofoGmcDB7ORTzyHKZYgJioK0hXtP0jrzoNmYZWy/9SW1idaF2aYiM8rQuAzFGpj1i53VgeLQEpjxbSWMlpsZ3/5sw9TjXBrm07AQWjwzvm3ahuO+h9mWweWuCvOiVZbGns/CNtFGMltcv8pgGs8RJljC7NcijYYLc45Ub9OHVo/ZA0tsVmEwSj3OieaM2EI0+pwELYDWMWKL0D7nzpRNmGO0CQ4o0o5ned5fmNtjgiIRW4xWO+7v0jR/YyP7kIjl2RY7k3L5IdroGTo0P9pzZnN0PdbSeI4zwRtmGUqujxOmmxDdZtfw8UGUJ1oisw8tVnWm/tCs0thvvWF/aJWZ8fG0T8T1yYye2UNzobViVmDyG9q/BNHU2rRNwvVJlmxdo/H++Pbg1bCARpswWd0caGptutHimfFtxY8WF7ElaPSMBFpAw4IaFtKwsIbBFHXTaZhNw+wa5tAwJ1o8s9lxZ7vT/GnE+dByMXt5qMJlGjONNnVT1eMcaGpxHo04v0ZceKrGPExTb9OOptamWyPOpxEX0ojTTVePc6Kp1eBCU2vTq9FmUCMOZqjHOdDU4twacX6NuJBGnG2mxppHU2vThabWpk8jLqgRp5ulsW2iqbXpnKWxjWnEBTTiwKuxdtEqMhswYe9/hHk0LKhhth/Vza1hAQ3TzVY3l4b5NQzmqJtTw3waFtYwx1x182pYCK04s/ErHVdprOepm0vDfBoW0jDbfI3+NMynYSENsy3Q6E/DfBoW0jDbQo3+NMw=
*/