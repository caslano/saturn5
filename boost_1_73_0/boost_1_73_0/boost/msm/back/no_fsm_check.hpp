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
vO/Jd1TV9gCCGw58a1OCDQjuX8COa3hDbOFK76S5IvS9x1qKTkkjS1lHZLlKUrBGvcuH9MjphTyyidcJPOXpZkb/tRd5JF9kDFg6o/+NZwFfYxZ75NvLmrmmnrXpvqslFxdNv3OQU50Go+Pg/NM/AVBLAwQKAAAACAAtZ0pSldDWdqwBAAD3AgAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDk0M1VUBQABtkgkYG1STW+jMBC9W+I/jFpVPVFLCT0066CibKpEIgsLdLV7dGGiWAsY2U7b/PvakJDNthdsj9+8j8HMoDYl1xgSJtqttMtfPLxJVemQ5JsiJXmUx/0HoudiBcvfxTL7EcUke1oEwWTSrw/3AWH03MjowEWuyTXkqF5R+VpUSJjCrj5YgO6LZVOF5D/aZRr/GaSm02Csg953nVQGqyNiDpPpPUR7s8PWiJK7G0b/oWX0qNWbWNTC4o4myv4wugiJbkw3docEWMsbHPIDvhtULa+Bn7WEbOFNmJ3cGygVVq7Ma20b6dDJtKlEG5KGixpeZHXwHP1QA1bKpuGt9XjrhGeUfnN556esjzerJC/W6ezGGUiTrKAPwfQWfN/R+arsDCgsRedSPOI7b7oa7yzpCbFVdq+xrVBdXhfg
*/