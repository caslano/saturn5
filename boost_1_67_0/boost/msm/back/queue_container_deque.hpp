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
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
*/