// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_ACTIVE_STATE_SWITCHING_POLICIES_H
#define BOOST_MSM_ACTIVE_STATE_SWITCHING_POLICIES_H

namespace boost { namespace msm
{
// policy classes

// Default: new active state set after the transition (after entry)
struct active_state_switch_after_entry 
{
    static int after_guard(int current_state,int){return current_state;}
    static int after_exit(int current_state,int){return current_state;}
    static int after_action(int current_state,int){return current_state;}
    static int after_entry(int,int next_state){return next_state;}
};

// new state set before the transition starts
struct active_state_switch_before_transition 
{
    static int after_guard(int,int next_state){return next_state;}
    static int after_exit(int,int next_state){return next_state;}
    static int after_action(int,int next_state){return next_state;}
    static int after_entry(int,int next_state){return next_state;}
};

// new state set after exit action completed
struct active_state_switch_after_exit 
{
    static int after_guard(int current_state,int){return current_state;}
    static int after_exit(int,int next_state){return next_state;}
    static int after_action(int,int next_state){return next_state;}
    static int after_entry(int,int next_state){return next_state;}
};

// new state set after transition action completed
struct active_state_switch_after_transition_action 
{
    static int after_guard(int current_state,int){return current_state;}
    static int after_exit(int current_state,int){return current_state;}
    static int after_action(int,int next_state){return next_state;}
    static int after_entry(int,int next_state){return next_state;}
};

} }//boost::msm
#endif //BOOST_MSM_ACTIVE_STATE_SWITCHING_POLICIES_H

/* active_state_switching_policies.hpp
QeKGHephcz8GUWoV60dXbRDTA6SWYWxivNihABt7HHm9wQmjE0vpKrOJezwOwN9MEhJaIUDF9U52n9r83Lu3vj1MqRQadtYFRP7fJYOdoSXe5yiRHciEXSbjuhDEfyhVk5yp0e/Vm3yxeyZ22ynoMLMy9bMyvyRiDjhJZtIuRhuL1cgchFncYaqhlMQGc+WbSjY90h8LDYPY/vJjkuzQQgrYAMaqK1D4WKSgx98B0gHp2eaNi5dsMdq6jDifORwmgeSenOKffQDE9GNLmX4BdHikQNmjhAAXNkI3veCbQ3CWiMAeepdiwcaBs90v6YlsSEsSwtE4B3tV1usnwokGYk59LrJmBeuDPLZc95b1LkaZ2AI3wFetdRBsKrQcuAjXJ1Q8ktEkcLNMopN7XQCEJDLNWD3RToSnn7/KiEm7sHFiAkna3gPmiQWfM/iIgFPgx7z752dEBph0K9FaNWGC4DHslNQlOJkCZjl0ZTZ/xhONoXHxE2DQFlNPj6ysJGqqaNJmrCMtMvnhGinXdOd+W99Dz/XBZtXn377erWZsfVA8yvXBYBtgmCJnmQ==
*/