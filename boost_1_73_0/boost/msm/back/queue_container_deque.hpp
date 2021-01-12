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
ZqfbdNkxmBwWTEmmPi9u/1/1SXo0RvYnuWSlLusF4rkktQ8/u0TODZNkfEzv7p6bTm21OTUwDQ73/OTkp0Dh9BVbcJyaAdc/n09Z/mkQ9CZFVqBs7BjahLIiZXwDJfIS5c42p+W3UQ6DnaNjzl4n5e1ZOQ6dUM/EOiLMxRnw2i7Jl1oJTnOteDHgo2Njww8eHCOc7CFeIp6aIU7/qmHLFrN+w4i3EadpZp6GZX0OHPY3PXXY
*/