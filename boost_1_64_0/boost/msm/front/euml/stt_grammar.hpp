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
joHhYyWA6jCWTpXP6nDVx9eacT/0CxwY47bgl4461pi2sa7XenBNv9fnMSyfg7ZW5hk3Wan39qGc55w1vf8j10Xbe1o52NpjVGRa8Z9b09sfx0+/3UaFhjAxuNjbANvmZH7Z7ECSUWyvGbKSsIAFSid0hliZp1M2vZf4/Y4ZlI7mTGF83qOzsEPr2ZqxnqVe4flRQT432OTd2rwgRA9yPVvT14pWDF1N6IiofFO8pIlhQ+12XeOLcPZOAih5NiUfW6sHPTQfLfmqj4xfrenzJmA6k3FO/lJkg1EKVGcaQxeNs007a8ZtL5JpDEfrODbMe6PVgci/4j140fCv5bbhcMVTyj+cGEsyzbnFi8aY6SRBHOMeSbybzDx2wuwVpn2y66a9PFH5oQLtxlEzwdghdpqm0ifSjbcu6HmmYQCnIp5kYrJC9Nb04hZzDy7ylHdfvb44QLgwpLbYKWd1fZpf1NenVhK0k3bLYqaDkupPLmqo+16YwwAiSdqSlQalvoe986J59iyaWSdomYyicWk9vqrxwYgJwh9c0ELBR5sm+peuh+ZZ8tpFba+GHM7FyVcOK2F0T34Sqrx/bOQduEXWarepsnIm23mH1RlRSyNzYDqDG0LmK2lMx9uXKSla6Iw6HFzX2y+AQzdYDiiVmGxNJ+OZ6C+yo33qujY2w7jJ/AcpzT7rrQ2NPj5p5gVHLrHXobxoAxJ50XlxXT9Du26Aq4FsLrHg0fyjO/S6Pu8hiCnyCOORX8DKM864r63YdJ66I26o55OgleAgFiXOJnjRjDSI1TX6tVp+OQTAUGb3k44zGgzYaJhe7EH83ONbbG9kjk2ag1fXjXkECzYYJzYhJCwPGmtD5A/ReO9Cr+qXrWr+f33dPKdgBUhaUcnL662bCoh9qsr7x+vG2byFQ3IrSzk/tdscwuyZeUb6w7q+17eQcycJed47DunGlOxTh7pNTI79MY+SGPw0nFnRZWIb2HG2EFeIFUm5s798l9Z3eavTioMEyejejET+l6u6nxjq7Y7XCDdwISxnjOIea1S+V9W9GOrtztyQwWdk4DBD7R45FGPseP+kA0avKvPGUJ8bad6C4AUb3ni+PrCPxP3qjHNlaLxdFB4sSIrYsZqIjsZGERrSrs6oP9zDN3HXSSgt9hKjOyYjv2TXtHL4Dhw0uVlM5dB5zbI4cl37w1C3L2zj4tSBEg6l8+r1wYhGg6zcdAAPEsocOvIKfRy34RQT8rvCoTOueWqUfslOarxwwgKZVF7kBfxicePC+Zi7YqyfEFSX81o6iZM34dKz7e6cDhuVdPWQ6Vx5hWGvAxkkDOc60r/YheGcTj+0tVvnoNuMNslzL/KDxKN07LvHZjW+v/kKQ87nwZkqbKgsXjrQ62v4xj93a3IJbFVhO8qI3dgrN0nO9wrTN2CKM5CruigzeV2Sa2QN/Q7uuTg1ex2dmVwJ0fpxp5onG4KFm7I3GubXj3Uaek3KmYWNxskHQXb6QmbfIQQK0uKmtKd5PuhXlg06WdxI38d34fc9pH6NAJPuDPlPuLPzMDt23AxPkxRKTdp4H174b7HjSiaKQ91IeLriOwsaN36woH2xX9I4hfuD4Pus6ncCQ3nCn+o3Hyboi7slvfRssz4l/zRfk/5uNifgqb5/hr7j4KKkFalpoVnUtO7iPPiKZQb7SlW+FbV8oI5YVkizop9T6BwwBELGyruSlemy1+zysI9Pq1WeTreklXo8YCIZyfb/G/+O+kyGv8uqdwvtXTrFnROTLu38T78WzD8Mlpaj2xg8qq3/m9cbis+9yGMOceE5El7JAzo7kW8EFbuEGNaQd2A1R0C9ZQGW2Egt5/Ekh8Ex5JXOfLo=
*/