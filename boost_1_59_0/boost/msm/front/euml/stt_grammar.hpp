// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_FRONT_EUML_STT_GRAMMAR_H
#define BOOST_MSM_FRONT_EUML_STT_GRAMMAR_H

#include <boost/msm/front/euml/common.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/eval_if.hpp>

#include <boost/msm/front/euml/operator.hpp>
#include <boost/msm/front/euml/guard_grammar.hpp>
#include <boost/msm/front/euml/state_grammar.hpp>

namespace proto = boost::proto;

namespace boost { namespace msm { namespace front { namespace euml
{

template <class SOURCE,class EVENT,class TARGET,class ACTION=none,class GUARD=none>
struct TempRow
{
    typedef SOURCE  Source;
    typedef EVENT   Evt;
    typedef TARGET  Target;
    typedef ACTION  Action;
    typedef GUARD   Guard;
};

template <class TEMP_ROW>
struct convert_to_row
{
    typedef Row<typename TEMP_ROW::Source,typename TEMP_ROW::Evt,typename TEMP_ROW::Target,
                typename TEMP_ROW::Action,typename TEMP_ROW::Guard> type;
};
template <class TEMP_ROW>
struct convert_to_internal_row
{
    typedef Internal<typename TEMP_ROW::Evt,
                     typename TEMP_ROW::Action,typename TEMP_ROW::Guard> type;
};
// explicit + fork + entry point + exit point grammar
struct BuildEntry
    : proto::or_<
        proto::when<
                    proto::function<proto::terminal<proto::_>,proto::terminal<state_tag>,proto::terminal<state_tag> >,
                    get_fct<proto::_child_c<0>,get_state_name<proto::_child_c<1>() >(),get_state_name<proto::_child_c<2>() >() >()
        >
    >
{};

// row grammar
struct BuildNextStates
   : proto::or_<
        proto::when<
                    proto::terminal<state_tag>,
                    get_state_name<proto::_>()
        >,
        proto::when<
                      BuildEntry,
                      BuildEntry
        >,
        proto::when<
                    proto::comma<BuildEntry,BuildEntry >,
                    ::boost::mpl::push_back<
                        make_vector_one_row<BuildEntry(proto::_left)>(),
                        BuildEntry(proto::_right)>()
        >,
        proto::when <
                    proto::comma<BuildNextStates,BuildEntry >,
                    ::boost::mpl::push_back<
                                BuildNextStates(proto::_left),
                                BuildEntry(proto::_right) >()                
        >
   >
{};

template <class EventGuard,class ActionClass>
struct fusion_event_action_guard 
{
    typedef TempRow<none,typename EventGuard::Evt,none,typename ActionClass::Action,typename EventGuard::Guard> type;
};

template <class SourceGuard,class ActionClass>
struct fusion_source_action_guard 
{
    typedef TempRow<typename SourceGuard::Source,none,none,typename ActionClass::Action,typename SourceGuard::Guard> type;
};

template <class SourceClass,class EventClass>
struct fusion_source_event_action_guard 
{
    typedef TempRow<typename SourceClass::Source,typename EventClass::Evt,
                    none,typename EventClass::Action,typename EventClass::Guard> type;
};
template <class Left,class Right>
struct fusion_left_right 
{
    typedef TempRow<typename Right::Source,typename Right::Evt,typename Left::Target
                   ,typename Right::Action,typename Right::Guard> type;
};

struct BuildEventPlusGuard
    : proto::or_<
        proto::when<
            proto::subscript<proto::terminal<event_tag>, GuardGrammar >,
            TempRow<none,proto::_left,none,none, GuardGrammar(proto::_right)>(proto::_right)
        >
    >
 {};

struct BuildSourceState
   : proto::or_<
        proto::when<
                    proto::terminal<state_tag>,
                    get_state_name<proto::_>()
        >,
        proto::when<
                    BuildEntry,
                    BuildEntry
        >
   >
{};

struct BuildSourcePlusGuard
    : proto::when<
            proto::subscript<BuildSourceState,GuardGrammar >,
            TempRow<BuildSourceState(proto::_left),none,none,none,GuardGrammar(proto::_right)>(proto::_right)
        >
{};

struct BuildEvent
    : proto::or_<
        // just event without guard/action
         proto::when<
                proto::terminal<event_tag>,
                TempRow<none,proto::_,none>() >
        // event / action
       , proto::when<
                proto::divides<proto::terminal<event_tag>,ActionGrammar >,
                TempRow<none,proto::_left,none,ActionGrammar(proto::_right) >(proto::_right) >
        // event [ guard ]
       , proto::when<
                proto::subscript<proto::terminal<event_tag>,GuardGrammar >,
                TempRow<none,proto::_left,none,none,GuardGrammar(proto::_right)>(proto::_right) >
        // event [ guard ] / action 
       , proto::when<
                proto::divides<BuildEventPlusGuard, ActionGrammar>,
                fusion_event_action_guard<BuildEventPlusGuard(proto::_left),
                                          TempRow<none,none,none,ActionGrammar(proto::_right)>(proto::_right)
                                           >() 
                >
        >
{};
struct BuildSource
    : proto::or_<
        // after == if just state without event or guard/action
         proto::when<
                BuildSourceState,
                TempRow<BuildSourceState(proto::_),none,none>() >
        // == source / action
       , proto::when<
                proto::divides<BuildSourceState,ActionGrammar >,
                TempRow<BuildSourceState(proto::_left),none,none,ActionGrammar(proto::_right) >(proto::_right) >
        // == source [ guard ]
       , proto::when<
                proto::subscript<BuildSourceState,GuardGrammar >,
                TempRow<BuildSourceState(proto::_left),none,none,none,GuardGrammar(proto::_right)>(proto::_right) >
        // == source [ guard ] / action 
       , proto::when<
                proto::divides<BuildSourcePlusGuard,
                               ActionGrammar >,
                fusion_source_action_guard<BuildSourcePlusGuard(proto::_left),
                                           TempRow<none,none,none,ActionGrammar(proto::_right)>(proto::_right)
                                           >() 
                >
        >
{};

struct BuildRight
    : proto::or_<
         proto::when<
                proto::plus<BuildSource,BuildEvent >,
                fusion_source_event_action_guard<BuildSource(proto::_left),BuildEvent(proto::_right)>()
         >,
         proto::when<
                BuildSource,
                BuildSource
         >
    >
{};

struct BuildRow
    : proto::or_<
        // grammar 1
        proto::when<
            proto::equal_to<BuildNextStates,BuildRight >,
            convert_to_row<
                fusion_left_right<TempRow<none,none,BuildNextStates(proto::_left)>,BuildRight(proto::_right)> >()
        >,
        // internal events
        proto::when<
            BuildRight,
            convert_to_row<
                fusion_left_right<TempRow<none,none,none>,BuildRight(proto::_)> >()
        >,
        // grammar 2
        proto::when<
            proto::equal_to<BuildRight,BuildNextStates>,
            convert_to_row<
                fusion_left_right<TempRow<none,none,BuildNextStates(proto::_right)>,BuildRight(proto::_left)> >()
        >
    >
{};

// stt grammar
struct BuildStt
   : proto::or_<
        proto::when<
                    proto::comma<BuildStt,BuildStt>,
                    boost::mpl::push_back<BuildStt(proto::_left),BuildRow(proto::_right)>()
                >,
        proto::when <
                    BuildRow,
                    make_vector_one_row<BuildRow(proto::_)>()
        >
   >
{};

template <class Expr>
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr,BuildStt>::type,
    boost::result_of<BuildStt(Expr)>,
    make_invalid_type>::type
build_stt(Expr const&)
{
    return typename boost::result_of<BuildStt(Expr)>::type();
}

// internal stt grammar
struct BuildInternalRow
    :   proto::when<
            BuildEvent,
            convert_to_internal_row<
                fusion_left_right<TempRow<none,none,none>,BuildEvent(proto::_)> >()
        >
{};
struct BuildInternalStt
   : proto::or_<
        proto::when<
                    proto::comma<BuildInternalStt,BuildInternalStt>,
                    boost::mpl::push_back<BuildInternalStt(proto::_left),BuildInternalRow(proto::_right)>()
                >,
        proto::when <
                    BuildInternalRow,
                    make_vector_one_row<BuildInternalRow(proto::_)>()
        >
   >
{};

template <class Expr>
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr,BuildInternalStt>::type,
    boost::result_of<BuildInternalStt(Expr)>,
    make_invalid_type>::type
build_internal_stt(Expr const&)
{
    return typename boost::result_of<BuildInternalStt(Expr)>::type();
}


}}}}
#endif //BOOST_MSM_FRONT_EUML_STT_GRAMMAR_H

/* stt_grammar.hpp
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
*/