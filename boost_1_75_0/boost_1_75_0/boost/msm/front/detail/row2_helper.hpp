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
rKm0ZJN+TZ1LNrkBlmx2xIayZPPX04EXdmmud1E1L6NzspPrn673z9rJ9uPedgJi0ykZCueugckN4+SiMoshfa0FmZpRnCDucnaJ1tD8oYdMdjuu0XMx6Ut25TLZ/WXzNWMY7d3sDveTC7bwaB7Yf8fkfuami+dwkxr0FnKvHkLd8gnm9iRjIgfnRNChlGuIGnMUasyB/lPlGMo6DLBDoF2iSPnEQVaJlBQSp05iZQYgb5dTiFIDjO0fbioBjCkJc3wAzsX4XxtuUMtTxzsxgJNrCWDvmDYG74k/FT5TwbsX4F3C4YUMjBBCBhkUHZwAzU3V3FeJ3AdBXVihFIBUgbM3XIOyhMDB15s0lcRGopp+FbGB9HunFcHJ9ALn8b/DfevccTpr+2dwOnuhSWA6G6jxobNRTUKhs1nj/dLZmot++ulbu+XJo7KxGrge37nGdZRuWdLTf+mW/Q3/JfWgy98BivlX1YP+vu0/UQ/67vRQK/IlflD7b63ItzEvpAIux86FS8k9fzkXHjiH/mtVMk3/0/WgjzfSh1hv9s0e/uuSbaz3r68H/doCFbP8v3rQwKztW+t9+PSy6kE/ZwqlFuyMd2v/TbVgpXz3bcfoAue7z6yRuTO9xp+NI+e7P/+rzJ//dD3ofg1C5c+/u/nnz5v1//p60Odfr5M//1896H+0HnTCdf9kPehnu4QiAwoW/KtkgJSevtXjusDp
*/