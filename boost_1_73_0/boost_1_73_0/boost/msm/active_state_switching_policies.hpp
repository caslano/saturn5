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
J4zesoxGkMzIDHLUJ9R3pimRMI1De3FAKa1MyOL+4U7UjQETGDC/w6C0NWBrhEq1rTo3/TcUqutkX5rlxFeAkztAunFHtuYCnldiBVmeCtivtjs4Zi+fkH7wV3h73woP84kzFAUZHQ0EZ+u2wd6OzooQOCR6SYjp7OAK/kNgvewwThy6ugyNKWCjw1i0pHS+OeRiy5dzT/NDJujT4tE1u3LuOeoFJ0fUTXUBbxJkZd0q/Ab84qGWBr4Qe5iaWtkpYafAuhaDVlYVqk1IWIZTmJA4rp/cD30jGL2W0dt//gFQSwMECgAAAAgALWdKUiYw/L33AAAAjAEAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q5MjlVVAUAAbZIJGBVkd9rgzAQx98P/B+OlsL2IIG9tQRfilBhXWzVsddUT5SpkSR0+N8vRteyp9zB5/uDC7dkbCkNRcDboVbu+abpR+nKRJCd8xQ+hEjhWGS5OF/jSxFnOXD2ZDhbZLCFLWak76RD01YEXNPYTTOwDp44di0NdiVKvzjEeF0EprejE/ytyAfZ09ID5x748q/IqyPYgiAvVd/LoVpMDoztTiLLk/Swm9WpuOZs/7bH8GsxChOX85C4ca3iS36SbusJK2klytqSRtsQ
*/