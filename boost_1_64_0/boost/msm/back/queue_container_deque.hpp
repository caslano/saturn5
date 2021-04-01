// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_BACK_QUEUE_CONTAINER_DEQUE_H
#define BOOST_MSM_BACK_QUEUE_CONTAINER_DEQUE_H

#include <deque>

namespace boost { namespace msm { namespace back
{
    struct queue_container_deque
    {
        typedef int queue_container_policy;

        template <class Element>
        struct In 
        {
            typedef typename std::deque<Element> type;
        };
    };

} } }//boost::msm::back


#endif //BOOST_MSM_BACK_QUEUE_CONTAINER_DEQUE_H

/* queue_container_deque.hpp
fPcHC8zWEXqR1keDbG6afcw1IBcdmyuZWvShyGYrk1RSm9A+G97+8uY12HdDawchTQ/xyuhp77Vw8yurZ/uKD2gYUcTPaOc2yGP/EaeDP6KCvBJx30oRkwJ/YXQi1dyOnmJDyaMRBPO12IJomVxlTJS48XThWiwRfcOchnuGVSsqtkJ4AqaDz1Doyote8Xr7gHb8Uz6yLo6hXXit+2GYUkczuEMR48mgEHEiLgwHbvV92ts1d4l+eK2gZ/ktg5812dpIRJyzHRGpAA8BgHAX5fFv+Pk4ZqXbgo4D4JuH2jfPpVTrq9ekBLxnhxAuERQL22l1Ilr+iYZKYWNxBr8azxIwzmIBURzNcTbB08IVUtToPsVFfVVuDhdGpeQ2sK5U+wacQGbZ4ELjo5gptoQpyyX4B7TtqL6FP8G/BENarcumKbRfVHBxvFOU1J9C/rSjeP9N/fFrNKUNLxUwDiTbV9sMNQZMweeRB1xnwwt3lOoFtFUf83jJ592+Sf1fpuWh081Rm+bllG0TQbACnoJLt2hQ+GoWvtDu+qpiTM+g5/ttz/XbgEPIVOigcg==
*/