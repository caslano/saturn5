
#ifndef BOOST_MPL_POP_BACK_HPP_INCLUDED
#define BOOST_MPL_POP_BACK_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/pop_back_fwd.hpp>
#include <boost/mpl/aux_/pop_back_impl.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct pop_back
    : pop_back_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,pop_back,(Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, pop_back)

}}

#endif // BOOST_MPL_POP_BACK_HPP_INCLUDED

/* pop_back.hpp
58buKj5/R/4tyK+y8ifZ8IsXlyVkJpUG2fR+ntSZhzoTrTr9oEmpsL7vtHcTboof1zE/mh/PjwDsH0Pa3kQf7MbbTbPFJTBbxKSBa2xcMfDTnfZP0Qvmk1i5h9jLOroOC8TPzE+6AxMIbZRs7JzcRpQZNkuPzlUMVhv6trmCfr6iYOz8ECR6AaaFW7IwA3wOurRHCbKoCzvBNY1NVua9yCQrnATC+xjSm1anycytNAUw0VtLydhyNM0eV0UrTf5y434FdT8vtmRryHh3ZwEr5L2pupww05IiN7i/LmiQmV4OFn8X2RukpRg3gB1oOuCiGc2Dji/VqfZylT2EwjQrWAIBjSbRgH//AXodalX0gpB5oBzkpE3D9srTQu+oPERdAzmbrgM5T+Z8OoT91fmd2F9pz8FjUICMsVCkM/usq47APovaowrFQU9J0JPbWMIk/ZiqduLtueT++010P2x4aDdP/qHGBFlH2UNg8J03ipaRjT3PbWO9ZtitbePyOcy0eRtsgg+yzk2vdeUBwmnb2EKe1kf84dD6Qk/CB3PtU8A4W0z0sd0poThZruGOrnxLEfapLodl3hey4W4+gYAdf7ncuqnOagwHmgCk5eq2e4KWNXVjverZVzfWp579dWP9JIer76A92mnhT4A6BAmeJdbJ4jU8BalUiu9bU6u4lD0dGpwXrRai1UKhYi8FuqhubNERU+XIf5b++1nQT+iDzcJPqGgCOz8LkoRvNjFvgzPlXZOlP7cglXBGR35kpoaQCi3kmclH4edCf98v1fgo7VKe47iLzIvfa5z4/uHW9YgbgSJ9rSMF4UVoO/QAC5T7zfsf12rBzIHC0TMfjclnzGPW6ysnUb9oHe2I4KNwien5OIr9Lo+yw4f7HmxK+VWEajcNYTOffcKkINH8ExojoOjtllfzG+UllaTBY/PMieWnj2zploUFuPslDLRY4fm3axSeOPXUl4K/1k/FqyoI3aerjVXVfqCr4dRTYauG6roExK8i1jeFWOXG6+PVXK+/KkCVarN7hbuRtFWWfbJD4Sf1aaqxr0L2oKm3b2SpLjoqJ3DxKD4unmnK06gi7zjV0ND5qTT7LfiphWl2nwbYvXKJ7vPzfVWfMSRPSyHZo2nDxgD6g40pPAZkKyXvYm1SzirKgrArpUu0T7RirombW3cshvLjYkUoh+WOHKGYlX3ooPHb6VJBOlPVrZ5q9uTdiIpEXa//Aoue0J8V/5y02WsUAyaob8J0n8WsTFQv5un9vixOZH/H2cc+XAjyGu4mk182oBIYIUXFAXImKF8MRxVL2I+LAzBozSL0AlCBRrhF0JIBwqfNQfONUwE8Boc2a36YHYqa/t+vVuund1TIVh9NjFmmkGiLnBn6OWopOaEqztcVX6AE+H3ox+otQARE6en5T3BT7JOQ9MQDk7R4UnKCw8GDI+QuT0JklEL+K9iBCkjXJcb9FJq5pO/rGYg63ql2wB4Ahh76x/k22mEGttEMrGAhXCfa40mLF6L9hVbNSi+/E1p+T1RxZ4iEtOGQUBsg+uKhklfvzzQJl4iAs5urHZYIv+Q6LfnPCjUnD+oa0//BVC0d0SYEfbfKIao9Gix1d/iDtnYual66O40PTJ/IUmh2z6u5X2a8LK+9vZNm/F+5NZcOSojZIud3580DAmY4HoDe3EGaBaS3flN2QoyCrXpegT7b6y5XClKsSibMotgELTXv7KWQQtZ1WpYlLPHnkXPHL8vJoD1W51ASlbQSqjyNZaQuT2Mw5B+Y9LQFkP0fRLX/7/0s/x/X2ecbPibZeTUP6w8wJMCqm9XBmqbXJG/SID6jxsUv44JZiAMdqHG2uRnXn9dnzwE/K5I=
*/