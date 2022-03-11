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