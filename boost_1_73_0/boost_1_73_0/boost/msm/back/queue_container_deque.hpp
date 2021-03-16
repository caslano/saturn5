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
3WyOQfhcmGWHo5Vjx8ykgT3nbvtKQ5o311rrBl8SlIYnYA2zHeBvsXkzDsM5Fo8mIfHhAhZejgTFoYVz7D3QVOKyQoscDMaBfLCXVtluxyrjChjiEvvUzisU+9bfY1fwmykdO8FZKz1AZ8JCopMRPr9mS6UKFD6Vy+Bb29kUnVa2AOUlOY3b1/DVLI7Lbn0iAXO/D0p9EK99YnEtoUX8Gh32P6w9NbLejUNmOSYczKB03nurVZgosTcjOGaNKnM=
*/