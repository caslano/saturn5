// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_FRONT_STATES_H
#define BOOST_MSM_FRONT_STATES_H

#include <boost/mpl/bool.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/msm/front/common_states.hpp>
#include <boost/msm/row_tags.hpp>
#include <boost/msm/back/metafunctions.hpp>

namespace boost { namespace msm { namespace front
{

struct no_sm_ptr 
{
    // tags
    typedef ::boost::mpl::bool_<false>   needs_sm;
};
struct sm_ptr 
{
    // tags
    typedef ::boost::mpl::bool_<true>    needs_sm;
};
// kept for backward compatibility
struct NoSMPtr 
{
    // tags
    typedef ::boost::mpl::bool_<false>   needs_sm;
};
struct SMPtr 
{
    // tags
    typedef ::boost::mpl::bool_<true>    needs_sm;
};

// provides the typedefs and interface. Concrete states derive from it.
// template argument: pointer-to-fsm policy
template<class BASE = default_base_state,class SMPtrPolicy = no_sm_ptr>
struct state :  public boost::msm::front::detail::state_base<BASE>, SMPtrPolicy
{
    // tags
    // default: no flag
    typedef ::boost::mpl::vector0<>       flag_list;
    typedef ::boost::mpl::vector0<>       internal_flag_list;
    //default: no deferred events
    typedef ::boost::mpl::vector0<>       deferred_events;
};

// terminate state simply defines the TerminateFlag flag
// template argument: pointer-to-fsm policy
template<class BASE = default_base_state,class SMPtrPolicy = no_sm_ptr>
struct terminate_state : public boost::msm::front::detail::state_base<BASE>, SMPtrPolicy
{
    // tags
    typedef ::boost::mpl::vector0<>                               flag_list;
    typedef ::boost::mpl::vector< boost::msm::TerminateFlag>      internal_flag_list;
    //default: no deferred events
    typedef ::boost::mpl::vector0<>                               deferred_events;
};

// terminate state simply defines the InterruptedFlag and EndInterruptFlag<EndInterruptEvent> flags
// template argument: event which ends the interrupt
// template argument: pointer-to-fsm policy
template <class EndInterruptEvent,class BASE = default_base_state,class SMPtrPolicy = no_sm_ptr>
struct interrupt_state : public boost::msm::front::detail::state_base<BASE>, SMPtrPolicy
{
    // tags
    typedef ::boost::mpl::vector0<>                           flag_list;
    typedef typename boost::msm::back::build_interrupt_state_flag_list<
        typename boost::msm::back::get_interrupt_events<EndInterruptEvent>::type
    >::type internal_flag_list; 

    //default: no deferred events
    typedef ::boost::mpl::vector0<>                           deferred_events;
};

// not a state but a bunch of extra typedefs to handle direct entry into a composite state. To be derived from
// template argument: zone index of this state
template <int ZoneIndex=-1>
struct explicit_entry 
{
    typedef int explicit_entry_state;
    enum {zone_index=ZoneIndex};
};

// to be derived from. Makes a type an entry (pseudo) state. Actually an almost full-fledged state
// template argument: containing composite
// template argument: zone index of this state
// template argument: pointer-to-fsm policy
template<int ZoneIndex=-1,class BASE = default_base_state,class SMPtrPolicy = no_sm_ptr>
struct entry_pseudo_state
    :  public boost::msm::front::detail::state_base<BASE>,SMPtrPolicy
{
    // tags
    typedef int                          pseudo_entry;
    enum {zone_index=ZoneIndex};
    typedef int explicit_entry_state;
    // default: no flag
    typedef ::boost::mpl::vector0<>       flag_list;
    typedef ::boost::mpl::vector0<>       internal_flag_list;
    //default: no deferred events
    typedef ::boost::mpl::vector0<>       deferred_events;
};

// to be derived from. Makes a state an exit (pseudo) state. Actually an almost full-fledged state
// template argument: event to forward
// template argument: pointer-to-fsm policy
template<class Event,class BASE = default_base_state,class SMPtrPolicy = no_sm_ptr>
struct exit_pseudo_state : public boost::msm::front::detail::state_base<BASE> , SMPtrPolicy
{
    typedef Event       event;
    typedef BASE        Base;
    typedef SMPtrPolicy PtrPolicy;
    typedef int         pseudo_exit;

    // default: no flag
    typedef ::boost::mpl::vector0<>  flag_list;
    typedef ::boost::mpl::vector0<>  internal_flag_list;
    //default: no deferred events
    typedef ::boost::mpl::vector0<>  deferred_events;
};

}}}

#endif //BOOST_MSM_FRONT_STATES_H


/* states.hpp
Np2+X4X+4KSn29NEmPe0PH226a55nfb04+6bTssvlXod/gzmtWelbmzVlgYKNuG34RYkuxXLfcrBK1gTT2xusj8p9LVxHjvQRLj+t6XLr2aN77nQ6q9guudchtMuvrXsM/bmV7VJ5kFFRunhNaIHeay2NT7H8FzFshWJNPbu5XHcgFt4S0n2YY0Oyn1blI+1PV7jEFp6b5ks8Cz70KXnCT3Jlo3S13lJFmcRXE7UP9uSExZejmff7fmebtuLHP+iF3iM7R9RTw92dF32ifDF/bBM1uR7tq9l3Y4rMfqm13ua6Cjk3trOQ5jjfsk2MsGVTjjcZrxRF1XMtj56MTjs6KBPvecVWKP7mUuL9P+l8bAIWxi8iX9vp26wxcJt7HxA7by4Y2Upl3PHyslczl1XL13ssszZJazxRRVx5rR3B2ZEP7SOPvuOrFP/ofTeNOto48LfWZZpjSkBgS/9o80o1nQs3GaKt1W6XB+ew9qA4pJxOJk+eSeRZiOZCWEk4rnAVVIdb6OXySuez5zGOYyPOZz0zybzGKopmebo6Vcec/NHZw+fYNOYRp52hA6TYL2ofk8RkI4+QOr3ODZ1lOM4A2YnwHhznOVgOBSXvBf7b8Ho11HneB0tjzNxMjfMDY/iFfXRp7IGR/s/5TJdYk8DqyP9Fw4w3h2McpAxwTCzHWRMevhcS/EfaboX5u91It16NoWVvr2/ODs/l0bLPuXkf+Mb7K+W/xtLSZFnEWPB21Tb6NkGC5px30XSuvNGbe8L43a1QPPI7BB9dIUsvd9gjXoA/KbPf08POUcR96nfZY0uwzWlf7U8ZG2tsVH37zMXvsm66Zba5FCMP2LbqvEa4o/A2GdfKSA5Joj44xbdjBF3k4rfElpS/w9l5x3c1lPE8UfoXYQemukMVQm9DEixlURgW8Ky6SArthxEbOuhEhKq6R1MHTqmdzC9g+kdTO9geh0Qbehl793pu3u39wz88ctv/Pajq3t3e7dXhstdJJ/vjf0+M/0lKuz15ORYlorfmwcsEnknqJSN005HYzvrbfZBflsxyB/st++AGZ+ZXb4q1rIgc05ik3lxlvXnVj55RF4PL2y781wG8uD6dsSf/HkcBkaWJdil/4BMXh2Psi/8DXInY10eXRBxd/PiTv+N37tXm5Olg3gn1v3+Zkkfunb58TdcNb8EPYCMw0Id39PKquRtn7JvnyCP6SFf5i60RhmXrhbI7RyCyziQyxu2MR8MGXdygfcFGrm/M8LNERKkI8bIcyuQY8eECQLyNCI3GUFfCXmzVq7Um9kRkuDOwK0oE9yHFGV8m6f+BTBmfD+MjkiEs/sQZhoNmRxmRopBcsAkDw0ZJIfDueRlx8zdbn3Tw+7p8uxMIK8dXcZnTrXJ2KVqMJpGJNtHF/M5cyS32Vnmtwweg/SYF6L5bIv4vkonEs0yCV3CAvluTL4u7LKHQW6vGKF0eeeqlNxPd+nZkJszuj33MAa31cdC7iRJC3nCb/09JxtPwndZXNz/PwXysDjPQVeeA8beDtHD6998ViBgXDfcgv0byFdaS4Nuj+fme4Gc0sD2/nOlbHxzu+vF5VjncZQFe9PuGspCyvn3axhjXwy5kXltd2PLlzmbYA266cudxZ2mNgmiTUU4NyYPYMdppnkyOxZMeUpFm9GcWZro9O8r7ip6iWac8oApaMZ6jQUzoRg88Q+mqBkkGna+YuwL8WbkIzG4eh5HY5i3Ph7jhidNcGDSOENBMbOhGNzrAmZTM7jtCL7YgJFr3/WX+rJ+jo6kmjsc6kjyMsVEdWRCcVpHSorROrKoGK0jG4rROrKlGK0jO4qJ68ie4uI6krxccUpHJhSjdaSkGK0=
*/