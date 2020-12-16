// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_ROW2_HELPER_HPP
#define BOOST_MSM_ROW2_HELPER_HPP

#include <boost/mpl/bool.hpp>
#include <boost/fusion/include/at_key.hpp>

namespace boost { namespace msm { namespace front
{
    namespace detail
    {
        template<
            typename CalledForAction
            , typename Event
            , void (CalledForAction::*action)(Event const&)
        >
        struct row2_action_helper
        {
            template <class FSM,class Evt,class SourceState,class TargetState, class AllStates>
            static void call_helper(FSM&,Evt const& evt,SourceState&,TargetState&,
                                    AllStates& all_states,::boost::mpl::false_ const &)
            {
                // in this front-end, we don't need to know source and target states
                ( ::boost::fusion::at_key<CalledForAction>(all_states).*action)(evt);
            }
            template <class FSM,class Evt,class SourceState,class TargetState, class AllStates>
            static void call_helper(FSM& fsm,Evt const& evt,SourceState&,TargetState&,AllStates&,
                                    ::boost::mpl::true_ const &)
            {
                // in this front-end, we don't need to know source and target states
                (fsm.*action)(evt);
            }
        };

        template<
            typename CalledForGuard
            , typename Event
            , bool (CalledForGuard::*guard)(Event const&)
        >
        struct row2_guard_helper
        {
            template <class FSM,class Evt,class SourceState,class TargetState,class AllStates>
            static bool call_helper(FSM&,Evt const& evt,SourceState&,TargetState&,
                                    AllStates& all_states, ::boost::mpl::false_ const &)
            {
                // in this front-end, we don't need to know source and target states
                return ( ::boost::fusion::at_key<CalledForGuard>(all_states).*guard)(evt);
            }
            template <class FSM,class Evt,class SourceState,class TargetState,class AllStates>
            static bool call_helper(FSM& fsm,Evt const& evt,SourceState&,TargetState&,
                                    AllStates&,::boost::mpl::true_ const &)
            {
                // in this front-end, we don't need to know source and target states
                return (fsm.*guard)(evt);
            }
        };
    }

}}}

#endif //BOOST_MSM_ROW2_HELPER_HPP


/* row2_helper.hpp
cF3qugjD2VzNjBsnt9auuEMhxpverM3MYowxXbBgNkKmr/O5rRmZzz76IMXpfBb+qJj986l4nc9UM8gn9sCCIWNB6N6O/M6618HeoD85uUnkUrvfF/bDxl+cLL4FuA/fNHNeG0EapBy/Z/key6HXUr5BZ+CNnO7Kmq3NVyedCxry+mYo73i/3wp/79adcW72/ufJ5PPHsisVlhIhGz2AZekwkN0oG2vveqI6N12v1aa9Myw39mXNo52B2z2EuinezGfctqUW5Lfw5W7rEuSLodxFgL75nMl3ZoDd5abmqLq539qMn0YTV3gNeC+XW89A9FMPDDla0+bwwG3EOYSH/H0h5IiRPtOYnHxdnVZfvOGiGKQH/eFujCH/+4CZVIWj87+Tz9ANsBzWSMWHCUMTOv9gxZiohhi7HxKTm92oHMbEFwPG+obWEYeSk3ZL2+1LEbmJQu7/UOnoHJFniZKHBnJXZigLLUdGsMftAocCxk47kM4Lh3Ic4QCzpRjaHkuc9MVs3k4y7rXD7ho2RKDcZLnY+1NMppt4c+Qrgdysua0vt3rLchtzwnp++0M+796pxPhzh6g8s/mkvzwp5XNNUebFHI7KjHU5hxma53BF2vc8zlSdv1ZXv6iUc/ZdFYr3S2SZkZ5ZXe2zvy2Qo1aSDvvbQgb2Ia/Flg/5jF+WvHY4Geek3u1Jxt6H63oN0bfINI3THO4pCJiBLcdVc57c2/P/cMUNzoq3uutK7re1VMpd2bik3BdxvP0AMWJS7u5rQZ8Syu2DoZBvKbnv099Rcn+s3lNyY6OzPFFyfyyvvyOQBz7kVMn7Wfiwt94ZkRuXKJUR6nT18szM01mcowvzFbdMy2/IXEEz4r5w3HGPsDTnVqDBbqzls24Fmtn1/dnB2YHQi0haXb2h/cWYYE5Y7MbiNPVnLT7sAcrnuifvR01E7lGLs7jXH3USTV9n4O2HijGBfyVJY/GZ4yN+Hgq9XA55QLzvR7z2aqDywnjtrwu9jzDyrt5RTG6SLsLYeJdgaAnUxfEArDe9I5BT+Gi3wW9d2A9Af/g4yI31J11oiL8UYWQe0pjc5QF6FjAzlfkTtang7ZEo49+RW388mLG1alYNzpDz0FunTp5w+ZDLDhuZEd1wGKM1R5ho72c9uds83R/SJOykPGeanAu4tZTnokEc7GDjtcjdbwQMvV4v+7/i/WW+cYExz2We4Mvl3RMTvsxVL7fvUiA3rZD6EreDgMt0K865xX/mkntoTlpIWGOPcaut/iCYz0zEuHUKMOCKMQ7uZ7HOpjmaqdyldqfKFLcb1BkYTy92tFw6F8GN4hwci1iLf6LilFMRbUCz0qHYQbvUHJyJYMKywNWgYl6nGVlN/C6Jrx9Y9bI9LHObOjxZneyXVZw+oIe+WLFwEoHZDtrQfQeDtLluHXZoR0/0GermUrTBoI2vtQZL9xVrKoXgt/Jt8J0Z/7fOTEZdFe/syzHTkfdVBHk0o1KsvRTuqTlZwNi346c3utqDPiIME3pi9+PCDtdhSh1gvdPhob4wdgb15e7K6KPMelpuTWcxjwnj6WZ92lmMrffy5e4wN8uD/LgD3WfRtz8Tcr4UMHijarR7ec3k2YJfzGVhC2JMjcUd2HfbMcbZd9jL9qVYnNSCuOvhfi+PtRW8BPs3l4MZxboQS6MtwpOwDaIMtTBisNfiy7E4+9F81OOsysd2Lsf5QP/w3gNgYUeJMXyb5WwjybPkT+G4pmu1Oy3Uqcbduhfa7FNjzArN+No916ewLkVZ12rdoA17PMr2hy6TPb4fNeSswwzy40puLjyEfFP9PrABS0pupstk7/QQxkiHYbzpkJeepuTe2a9dLe/fdzg=
*/