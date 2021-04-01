// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_BACK_NO_FSM_CHECK_H
#define BOOST_MSM_BACK_NO_FSM_CHECK_H

#include <boost/mpl/assert.hpp>

#include <boost/msm/back/metafunctions.hpp>

namespace boost { namespace msm { namespace back
{
    struct no_fsm_check
    {
        typedef int fsm_check;
        // no fsm structure checking
        template <class Fsm>
        static void check_orthogonality()
        {
        }
        template <class Fsm>
        static void check_unreachable_states()
        {
        }
    };

} } }//boost::msm::back


#endif //BOOST_MSM_BACK_NO_FSM_CHECK_H

/* no_fsm_check.hpp
sYafTff5VAUjP1AB1quHEXk8mjxLySjkr89Mw0Gl/xSgyvMdbsKVOLq22vNoH+g20ukTQE/s/Rk6HMxpwrfVZZgNCxdEc1dl0UDe+RiP0WBh8pJzHJiHiXSPzaK+2YBc0vP9zcuybvD8YxUHScht0C0Gf70tY67r/JGwQak0aq9eyJV+ivBE4XgCOI21DwCjfiIzX9V9gnQDw+LBvQJ+o35qElG2c/71B2V+DOZzHdLMHiPKc5cm3ZJNGdAfGVd6XkgX8bpN+Np57YNOlpI+txzkk4ccyzqtmALf530keTojy4sIYdWHJYhm5BehxIooQbt/CX2KBz8zeYpSihdD4W0zNI3cQwmd9fYQsQWHkwjoj4QF6zr9ncPoC1n0Is7UkcTMgJbH11/rieiHNkZ5HZ/coNwYTRqkPRvDn3uLB25WMBU+/yBWrWdkex4GEhZM7BhOo03RhaPrFcJHVLKwyyTpwUTdU8uL8sVRjW7WtEmTCtW+L9DIuIjfPKgMjpOItTqpduwg5b5hFEKjOjdRcpOwvHpSHbK/0mFFD8rgy+jbfGupNWln4c1nzQ==
*/