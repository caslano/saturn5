// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_FRONT_EUML_STATE_GRAMMAR_H
#define BOOST_MSM_FRONT_EUML_STATE_GRAMMAR_H

#ifdef BOOST_MSM_EUML_PHOENIX_SUPPORT
#include <boost/phoenix/core/meta_grammar.hpp>
#endif

#include <boost/msm/front/euml/common.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/include/pair.hpp>
#include <boost/fusion/include/as_map.hpp>

#include <boost/mpl/remove_if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/assert.hpp>

#include <boost/msm/row_tags.hpp>
#include <boost/msm/front/common_states.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/euml/operator.hpp>
#include <boost/msm/front/euml/guard_grammar.hpp>

BOOST_MPL_HAS_XXX_TRAIT_DEF(attribute_tag)
BOOST_MPL_HAS_XXX_TRAIT_DEF(flag_create_tag)
BOOST_MPL_HAS_XXX_TRAIT_DEF(defer_create_tag)
BOOST_MPL_HAS_XXX_TRAIT_DEF(control_configure_tag)

namespace proto = boost::proto;

namespace boost { namespace msm { namespace front { namespace euml
{

// provides the typedefs and interface. Concrete states derive from it.
template<class StateNameTag,
         class EntryFunctor=NoAction, 
         class ExitFunctor=NoAction,
         class Attributes= ::boost::fusion::vector<>,
         class Flags = ::boost::mpl::vector0<>,
         class Defer = ::boost::mpl::vector0<>,
         class BASE = ::boost::msm::front::default_base_state>
struct func_state :  public ::boost::msm::front::detail::state_base<BASE,Attributes>, 
                     euml_state_intern<func_state<StateNameTag,EntryFunctor,ExitFunctor,Attributes,Flags,Defer,BASE> >
{
    func_state(){}
    // grammar testing
    BOOST_MPL_ASSERT_NOT(( boost::is_same<EntryFunctor,invalid_type> ));
    BOOST_MPL_ASSERT_NOT(( boost::is_same<ExitFunctor,invalid_type> ));

    typedef StateNameTag state_name_tag;
    // flags
    typedef Flags       flag_list;
    typedef ::boost::mpl::vector0<> internal_flag_list;
    // deferred events
    typedef Defer       deferred_events;

    template <class Event,class FSM>
    void on_entry(Event const& evt,FSM& fsm)
    {
        EntryFunctor()(evt,fsm,*this);
    }
    template <class Event,class FSM>
    void on_exit(Event const& evt,FSM& fsm)
    {
        ExitFunctor()(evt,fsm,*this);
    }
};

// provides the typedefs and interface. Concrete states derive from it.
template<class StateNameTag,
         int ZoneIndex=-1,
         class EntryFunctor=NoAction, 
         class ExitFunctor=NoAction,
         class Attributes= ::boost::fusion::vector<>,
         class Flags = ::boost::mpl::vector0<>,
         class Defer = ::boost::mpl::vector0<>,
         class BASE = default_base_state>
struct entry_func_state :  public ::boost::msm::front::detail::state_base<BASE,Attributes>, 
                           euml_state_intern<entry_func_state<StateNameTag,ZoneIndex,EntryFunctor,ExitFunctor,Attributes,Flags,Defer,BASE> >
{
    entry_func_state(){}
    // grammar testing
    BOOST_MPL_ASSERT_NOT(( boost::is_same<EntryFunctor,invalid_type> ));
    BOOST_MPL_ASSERT_NOT(( boost::is_same<ExitFunctor,invalid_type> ));

    typedef StateNameTag state_name_tag;
    // tags
    typedef int                          pseudo_entry;
    enum {zone_index=ZoneIndex};
    typedef int explicit_entry_state;

    // flags
    typedef Flags       flag_list;
    typedef ::boost::mpl::vector0<> internal_flag_list;
    // deferred events
    typedef Defer       deferred_events;

    template <class Event,class FSM>
    void on_entry(Event const& evt,FSM& fsm)
    {
        EntryFunctor()(evt,fsm,*this);
    }
    template <class Event,class FSM>
    void on_exit(Event const& evt,FSM& fsm)
    {
        ExitFunctor()(evt,fsm,*this);
    }
};
// provides the typedefs and interface. Concrete states derive from it.
template<class StateNameTag,
         int ZoneIndex=-1,
         class EntryFunctor=NoAction, 
         class ExitFunctor=NoAction,
         class Attributes= ::boost::fusion::vector<>,
         class Flags = ::boost::mpl::vector0<>,
         class Defer = ::boost::mpl::vector0<>,
         class BASE = default_base_state>
struct explicit_entry_func_state :  public ::boost::msm::front::detail::state_base<BASE,Attributes>, 
                                    public ::boost::msm::front::explicit_entry<ZoneIndex>,
                                    euml_state_intern<explicit_entry_func_state<StateNameTag,
                                        ZoneIndex,EntryFunctor,ExitFunctor,Attributes,Flags,Defer,BASE> >
{
    explicit_entry_func_state(){}
    // grammar testing
    BOOST_MPL_ASSERT_NOT(( boost::is_same<EntryFunctor,invalid_type> ));
    BOOST_MPL_ASSERT_NOT(( boost::is_same<ExitFunctor,invalid_type> ));

    typedef StateNameTag state_name_tag;
    // flags
    typedef Flags       flag_list;
    typedef ::boost::mpl::vector0<> internal_flag_list;
    // deferred events
    typedef Defer       deferred_events;

    template <class Event,class FSM>
    void on_entry(Event const& evt,FSM& fsm)
    {
        EntryFunctor()(evt,fsm,*this);
    }
    template <class Event,class FSM>
    void on_exit(Event const& evt,FSM& fsm)
    {
        ExitFunctor()(evt,fsm,*this);
    }
};

// provides the typedefs and interface. Concrete states derive from it.
template<class StateNameTag,
         class Event,
         class EntryFunctor=NoAction, 
         class ExitFunctor=NoAction,
         class Attributes= ::boost::fusion::vector<>,
         class Flags = ::boost::mpl::vector0<>,
         class Defer = ::boost::mpl::vector0<>,
         class BASE = default_base_state>
struct exit_func_state :   public ::boost::msm::front::detail::state_base<BASE,Attributes>, 
                           euml_state_intern<exit_func_state<StateNameTag,Event,EntryFunctor,ExitFunctor,Attributes,Flags,Defer,BASE> >
{
    exit_func_state(){}
    // grammar testing
    BOOST_MPL_ASSERT_NOT(( boost::is_same<EntryFunctor,invalid_type> ));
    BOOST_MPL_ASSERT_NOT(( boost::is_same<ExitFunctor,invalid_type> ));

    typedef StateNameTag state_name_tag;
    // tags
    typedef Event       event;
    typedef BASE        Base;
    typedef int         pseudo_exit;

    // flags
    typedef Flags       flag_list;
    typedef ::boost::mpl::vector0<> internal_flag_list;
    // deferred events
    typedef Defer       deferred_events;

    template <class Evt,class FSM>
    void on_entry(Evt const& evt,FSM& fsm)
    {
        EntryFunctor()(evt,fsm,*this);
    }
    template <class Evt,class FSM>
    void on_exit(Evt const& evt,FSM& fsm)
    {
        ExitFunctor()(evt,fsm,*this);
    }
};

struct BuildActions;
struct BuildGuards;

struct BuildActionSequence
   : proto::or_<
        proto::when <
                    BuildActions,
                    ActionSequence_<make_vector_one_row<BuildActions(proto::_)>()>()
        >,
        proto::when <
                    proto::comma<BuildActions,BuildActions >,
                    ActionSequence_<boost::mpl::push_back<
                        make_vector_one_row<BuildActions(proto::_left)>(),
                        BuildActions(proto::_right)>()>()                
        >,
        proto::when <
                    proto::comma<BuildActionSequence,BuildActions >,
                    ActionSequence_<boost::mpl::push_back<
                        get_sequence<BuildActionSequence(proto::_left) >(),
                        BuildActions(proto::_right) >() >()                
        >
   >
{};

#ifdef BOOST_MSM_EUML_PHOENIX_SUPPORT
struct CustomPhoenixGrammar
    : proto::switch_<CustomPhoenixGrammar>
{
    template <typename Tag, typename Dummy = void>
    struct case_ 
        : proto::and_<
            proto::not_<BuildGuards> ,
            proto::not_<BuildActionSequence>,
            boost::phoenix::meta_grammar::case_<Tag>
        >
    {};
};
#endif

struct GuardGrammar
        : proto::or_<
#ifdef BOOST_MSM_EUML_PHOENIX_SUPPORT
            proto::when<
                CustomPhoenixGrammar ,
                proto::_
            >,
#endif
            proto::when<
                BuildGuards ,
                BuildGuards
            >
    >
 {};

struct ActionGrammar
        : proto::or_<
#ifdef BOOST_MSM_EUML_PHOENIX_SUPPORT
            proto::when<
                CustomPhoenixGrammar ,
                proto::_
            >,
#endif
            proto::when<
                BuildActionSequence ,
                BuildActionSequence
            >
    >
 {};

struct BuildActionsCases
{
    // The primary template matches nothing:
    template<typename Tag>
    struct case_
        : proto::not_<proto::_>
    {};
};

template<>
struct BuildActionsCases::case_<proto::tag::pre_inc>
    : proto::when<
            proto::pre_inc<BuildActions >,
            Pre_inc_< BuildActions(proto::_child)>()               
                >
{};
template<>
struct BuildActionsCases::case_<proto::tag::pre_dec>
    : proto::when<
            proto::pre_dec<BuildActions >,
            Pre_dec_< BuildActions(proto::_child)>()               
                >
{};
template<>
struct BuildActionsCases::case_<proto::tag::post_inc>
    : proto::when<
            proto::post_inc<BuildActions >,
            Post_inc_< BuildActions(proto::_child)>()               
                >
{};
template<>
struct BuildActionsCases::case_<proto::tag::post_dec>
    : proto::when<
            proto::post_dec<BuildActions >,
            Post_dec_< BuildActions(proto::_child)>()               
                >
{};
template<>
struct BuildActionsCases::case_<proto::tag::dereference>
    : proto::when<
            proto::dereference<BuildActions >,
            Deref_< BuildActions(proto::_child)>()               
                >
{};
template<>
struct BuildActionsCases::case_<proto::tag::plus>
    : proto::when<
            proto::plus<BuildActions,BuildActions >,
            Plus_<BuildActions(proto::_left),BuildActions(proto::_right)>()               
                >
{};
template<>
struct BuildActionsCases::case_<proto::tag::minus>
    : proto::when<
            proto::minus<BuildActions,BuildActions >,
            Minus_<BuildActions(proto::_left),BuildActions(proto::_right)>()               
                >
{};
template<>
struct BuildActionsCases::case_<proto::tag::multiplies>
    : proto::when<
            proto::multiplies<BuildActions,BuildActions >,
            Multiplies_<BuildActions(proto::_left),BuildActions(proto::_right)>()               
                >
{};
template<>
struct BuildActionsCases::case_<proto::tag::divides>
    : proto::when<
            proto::divides<BuildActions,BuildActions >,
            Divides_<BuildActions(proto::_left),BuildActions(proto::_right)>()               
                >
{};
template<>
struct BuildActionsCases::case_<proto::tag::modulus>
    : proto::when<
            proto::modulus<BuildActions,BuildActions >,
            Modulus_<BuildActions(proto::_left),BuildActions(proto::_right)>()               
                >
{};
template<>
struct BuildActionsCases::case_<proto::tag::bitwise_and>
    : proto::when<
            proto::bitwise_and<BuildActions,BuildActions >,
            Bitwise_And_<BuildActions(proto::_left),BuildActions(proto::_right)>()               
                >
{};
template<>
struct BuildActionsCases::case_<proto::tag::bitwise_or>
    : proto::when<
            proto::bitwise_or<BuildActions,BuildActions >,
            Bitwise_Or_<BuildActions(proto::_left),BuildActions(proto::_right)>()               
                >
{};
template<>
struct BuildActionsCases::case_<proto::tag::bitwise_xor>
    : proto::when<
            proto::bitwise_xor<BuildActions,BuildActions >,
            Bitwise_Xor_<BuildActions(proto::_left),BuildActions(proto::_right)>()               
                >
{};

template<>
struct BuildActionsCases::case_<proto::tag::plus_assign>
    : proto::when<
            proto::plus_assign<BuildActions,BuildActions >,
            Plus_Assign_< BuildActions(proto::_left),BuildActions(proto::_right)>()
                >
{};
template<>
struct BuildActionsCases::case_<proto::tag::minus_assign>
    : proto::when<
            proto::minus_assign<BuildActions,BuildActions >,
            Minus_Assign_<BuildActions(proto::_left),BuildActions(proto::_right)>()
                >
{};
template<>
struct BuildActionsCases::case_<proto::tag::multiplies_assign>
    : proto::when<
            proto::multiplies_assign<BuildActions,BuildActions >,
            Multiplies_Assign_< BuildActions(proto::_left),BuildActions(proto::_right)>()
                >
{};
template<>
struct BuildActionsCases::case_<proto::tag::divides_assign>
    : proto::when<
            proto::divides_assign<BuildActions,BuildActions >,
            Divides_Assign_< BuildActions(proto::_left),BuildActions(proto::_right)>()
                >
{};
template<>
struct BuildActionsCases::case_<proto::tag::modulus_assign>
    : proto::when<
            proto::modulus_assign<BuildActions,BuildActions >,
            Modulus_Assign_< BuildActions(proto::_left),BuildActions(proto::_right)>()
                >
{};
template<>
struct BuildActionsCases::case_<proto::tag::shift_left_assign>
    : proto::when<
            proto::shift_left_assign<BuildActions,BuildActions >,
            ShiftLeft_Assign_< BuildActions(proto::_left),BuildActions(proto::_right)>()
                >
{};
template<>
struct BuildActionsCases::case_<proto::tag::shift_right_assign>
    : proto::when<
            proto::shift_right_assign<BuildActions,BuildActions >,
            ShiftRight_Assign_< BuildActions(proto::_left),BuildActions(proto::_right)>()
                >
{};
template<>
struct BuildActionsCases::case_<proto::tag::shift_left>
    : proto::when<
            proto::shift_left<BuildActions,BuildActions >,
            ShiftLeft_< BuildActions(proto::_left),BuildActions(proto::_right)>()
                >
{};
template<>
struct BuildActionsCases::case_<proto::tag::shift_right>
    : proto::when<
            proto::shift_right<BuildActions,BuildActions >,
            ShiftRight_< BuildActions(proto::_left),BuildActions(proto::_right)>()
                >
{};
template<>
struct BuildActionsCases::case_<proto::tag::assign>
    : proto::when<
            proto::assign<BuildActions,BuildActions >,
            Assign_< BuildActions(proto::_left),BuildActions(proto::_right)>()
                >
{};
template<>
struct BuildActionsCases::case_<proto::tag::subscript>
    : proto::when<
            proto::subscript<BuildActions,BuildActions >,
            Subscript_< BuildActions(proto::_left),BuildActions(proto::_right)>()
                >
{};
template<>
struct BuildActionsCases::case_<proto::tag::unary_plus>
    : proto::when<
            proto::unary_plus<BuildActions >,
            Unary_Plus_< BuildActions(proto::_child)>()
                >
{};
template<>
struct BuildActionsCases::case_<proto::tag::negate>
    : proto::when<
            proto::negate<BuildActions >,
            Unary_Minus_< BuildActions(proto::_child)>()
                >
{};

template<>
struct BuildActionsCases::case_<proto::tag::function>
    : proto::or_<
            proto::when<
                proto::function<proto::terminal<if_tag>,BuildGuards,BuildActionSequence,BuildActionSequence >,
                If_Else_<BuildGuards(proto::_child_c<1>),
                         BuildActionSequence(proto::_child_c<2>),
                         BuildActionSequence(proto::_child_c<3>) >()
                    >,
            proto::when<
                proto::function<proto::terminal<if_then_tag>,BuildGuards,BuildActionSequence >,
                If_Then_<BuildGuards(proto::_child_c<1>),
                         BuildActionSequence(proto::_child_c<2>)>()
                    >,
            proto::when<
                    proto::function<proto::terminal<while_do_tag>,BuildGuards,BuildActionSequence >,
                    While_Do_<BuildGuards(proto::_child_c<1>),
                             BuildActionSequence(proto::_child_c<2>) >()
                    >,
            proto::when<
                    proto::function<proto::terminal<do_while_tag>,BuildGuards,BuildActionSequence >,
                    Do_While_<BuildGuards(proto::_child_c<1>),
                             BuildActionSequence(proto::_child_c<2>) >()
                    >,
            proto::when<
                proto::function<proto::terminal<for_loop_tag>,
                                BuildActionSequence,BuildGuards,BuildActionSequence,BuildActionSequence>,
                For_Loop_<BuildActionSequence(proto::_child_c<1>),
                         BuildGuards(proto::_child_c<2>),
                         BuildActionSequence(proto::_child_c<3>),
                         BuildActionSequence(proto::_child_c<4>) >()
                    >,
         proto::or_<
            proto::when<
                    proto::function<proto::terminal<proto::_>,BuildActions >,
                    get_fct<proto::_child_c<0>,BuildActions(proto::_child_c<1>) >()
                    >,
            proto::when<
                    proto::function<proto::terminal<proto::_> >,
                    get_fct<proto::_child_c<0> >()
                    >,
            proto::when<
                    proto::function<proto::terminal<proto::_>,BuildActions,BuildActions >,
                    get_fct<proto::_child_c<0>,BuildActions(proto::_child_c<1>),BuildActions(proto::_child_c<2>) >()
                    >,
            proto::when<
                    proto::function<proto::terminal<proto::_>,BuildActions,BuildActions,BuildActions >,
                    get_fct<proto::_child_c<0>,BuildActions(proto::_child_c<1>)
                                              ,BuildActions(proto::_child_c<2>),BuildActions(proto::_child_c<3>) >()
                    >,
            proto::when<
                    proto::function<proto::terminal<proto::_>,BuildActions,BuildActions,BuildActions,BuildActions >,
                    get_fct<proto::_child_c<0>
                            ,BuildActions(proto::_child_c<1>),BuildActions(proto::_child_c<2>)
                            ,BuildActions(proto::_child_c<3>),BuildActions(proto::_child_c<4>) >()
                    >,
            proto::when<
                    proto::function<proto::terminal<proto::_>,BuildActions,BuildActions,BuildActions,BuildActions,BuildActions >,
                    get_fct<proto::_child_c<0>
                            ,BuildActions(proto::_child_c<1>),BuildActions(proto::_child_c<2>)
                            ,BuildActions(proto::_child_c<3>),BuildActions(proto::_child_c<4>)
                            ,BuildActions(proto::_child_c<5>) >()
                    >
#ifdef BOOST_MSVC
            ,proto::when<
                    proto::function<proto::terminal<proto::_>,BuildActions,BuildActions,BuildActions,BuildActions,BuildActions,BuildActions >,
                    get_fct<proto::_child_c<0>
                            ,BuildActions(proto::_child_c<1>),BuildActions(proto::_child_c<2>)
                            ,BuildActions(proto::_child_c<3>),BuildActions(proto::_child_c<4>)
                            ,BuildActions(proto::_child_c<5>),BuildActions(proto::_child_c<6>) >()
                    >
#endif
                 >
    >
{};

template<>
struct BuildActionsCases::case_<proto::tag::terminal>
    : proto::or_<
        proto::when<
            proto::terminal<action_tag>,
            get_action_name<proto::_ >()
            >,
        proto::when<
            proto::terminal<state_tag>,
            get_state_name<proto::_>()
            >,
        proto::when<
            proto::terminal<flag_tag>,
            proto::_
            >,
        proto::when<
            proto::terminal<event_tag>,
            proto::_
            >,
        proto::when<
            proto::terminal<fsm_artefact_tag>,
            get_fct<proto::_ >()
            >,
        proto::when<
            proto::terminal<proto::_>,
            proto::_value
            >
    >
{};
struct BuildActions
    : proto::switch_<BuildActionsCases>
{};

// attributes building
#define BOOST_MSM_EUML_DECLARE_ATTRIBUTE(attr_type,attr_name)                                                           \
struct attr_name ## _                                                                                                   \
    : proto::extends< proto::terminal< ::boost::msm::front::action_tag>::type, attr_name ## _, boost::msm::sm_domain>   \
    {typedef  attr_name ## _ action_name;                                                                               \
        typedef ::boost::fusion::pair<attr_name ## _,attr_type> attribute_type;                                         \
        attr_name ## _ (){}                                                                                             \
    };                                                                                                                  \
attr_name ## _ const attr_name = attr_name ## _();

struct make_attributes_tag
{
    typedef int attribute_tag;
};

template <class T>
struct get_attribute_type
{
    typedef typename T::attribute_type type;
};
template <class Seq>
struct transform_to_fusion_pair 
{
    typedef typename ::boost::mpl::fold<
        Seq,::boost::mpl::vector<>,
        ::boost::mpl::push_back< ::boost::mpl::placeholders::_1, 
                                 get_attribute_type< ::boost::mpl::placeholders::_2> >
        >::type type;
};

template<class X = proto::is_proto_expr>
struct attribute
{
   BOOST_PROTO_BASIC_EXTENDS(
       proto::terminal<make_attributes_tag>::type
     , attribute
     , boost::msm::sm_domain
   )
   typedef ::boost::fusion::pair<int,int> attribute_type;
};

attribute<> const attributes_ = {{{}}};
 attribute<> const no_attributes_ = {{{}}};

 struct BuildAttributesHelper
   : proto::make<
       ::boost::mpl::pop_front<
          proto::fold_tree<
              proto::_
            , ::boost::fusion::vector<>()
            , ::boost::mpl::push_back<proto::_state, 
                                      ::boost::mpl::if_< has_attribute_tag< proto::_value>,
                                                         proto::_value,
                                                         get_attribute_type<proto::_> > 
                >()
           >
       >
    >
 {};

struct BuildAttributes 
 : proto::make<
      ::boost::mpl::if_<
          has_attribute_tag< ::boost::mpl::deref< ::boost::mpl::prior< ::boost::mpl::end< BuildAttributesHelper > > > >,
          ::boost::fusion::result_of::as_map< ::boost::mpl::pop_back< BuildAttributesHelper > >,
          ::boost::fusion::result_of::as_map< BuildAttributesHelper > > 
   > 
{};

// helper to build a mpl::vector from a << list
 struct BuildMplVectorHelper
   : proto::make<
       ::boost::mpl::pop_front<
          proto::fold_tree<
              proto::_
            , ::boost::mpl::vector0<>()
            , ::boost::mpl::push_back<proto::_state, proto::_>()
           >
       >
    >
 {};

// flags building
struct BuildFlags 
 : proto::make<
    ::boost::mpl::remove_if<
        BuildMplVectorHelper,
        ::boost::mpl::not_< ::boost::is_same<get_euml_tag_type< ::boost::mpl::placeholders::_ >, flag_tag > > 
    >
 >
{};

struct control_configure_tag {};

// configuration building
struct make_configure_tag
{
    typedef int control_configure_tag;
};

template<class X = proto::is_proto_expr>
struct configure
{
   typedef not_euml_tag euml_tag_type;
   BOOST_PROTO_BASIC_EXTENDS(
       proto::terminal<make_configure_tag>::type
     , configure
     , boost::msm::sm_domain
   )
};

 configure<> const configure_ = {{{}}};
 configure<> const no_configure_ = {{{}}};

struct BuildConfigure 
 : proto::make<
    ::boost::mpl::remove_if<
        BuildMplVectorHelper,
        ::boost::mpl::not_< ::boost::is_same<get_euml_tag_type< ::boost::mpl::placeholders::_ >, config_tag > > 
    >
 >
{};

struct BuildDeferred 
 : proto::make<
    ::boost::mpl::remove_if<
        BuildMplVectorHelper,
        ::boost::mpl::not_< ::boost::is_same<get_euml_tag_type< ::boost::mpl::placeholders::_ >, event_tag > > 
    >
 >
{};

template<class X = proto::is_proto_expr>
struct define_init
{
   typedef int defer_create_tag;
   BOOST_PROTO_BASIC_EXTENDS(
       proto::terminal<state_tag>::type
     , define_init
     , boost::msm::sm_domain
   )
};

define_init<> const init_ = {{{}}};
struct BuildInit
   : proto::make<
       ::boost::mpl::pop_front<
          proto::fold_tree<
              proto::_
            , ::boost::mpl::vector0<>()
            , ::boost::mpl::push_back<proto::_state, proto::_>()
           >
       >
    >
 {};

template <class StateNameTag,class Expr1,class Expr2,class Attr,class Configure,class BASE>
inline
func_state<
StateNameTag,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr2,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr2)>,
    make_invalid_type>::type,
typename boost::result_of<BuildAttributes(Attr)>::type,
typename boost::result_of<BuildFlags(Configure)>::type,
typename boost::result_of<BuildDeferred(Configure)>::type,
BASE
>
build_state(Expr1 const& ,Expr2 const& , Attr const&, Configure const&, BASE )
{
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    typedef typename boost::result_of<ActionGrammar(Expr2)>::type exit_action;
    typedef typename boost::result_of<BuildAttributes(Attr)>::type attributes_type;
    typedef typename boost::result_of<BuildFlags(Configure)>::type flags_type;
    typedef typename boost::result_of<BuildDeferred(Configure)>::type deferred_type;
    return func_state<StateNameTag,entry_action,exit_action,attributes_type,flags_type,deferred_type,BASE>();
}

template <class StateNameTag,class Expr1,class Expr2,class Attr,class Configure>
inline
func_state<
StateNameTag,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr2,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr2)>,
    make_invalid_type>::type,
typename boost::result_of<BuildAttributes(Attr)>::type,
typename boost::result_of<BuildFlags(Configure)>::type,
typename boost::result_of<BuildDeferred(Configure)>::type
>
build_state(Expr1 const& ,Expr2 const& ,Attr const&, Configure const&)
{
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    typedef typename boost::result_of<ActionGrammar(Expr2)>::type exit_action;
    typedef typename boost::result_of<BuildAttributes(Attr)>::type attributes_type;
    typedef typename boost::result_of<BuildFlags(Configure)>::type flags_type;
    typedef typename boost::result_of<BuildDeferred(Configure)>::type deferred_type;
    return func_state<StateNameTag,entry_action,exit_action,attributes_type,flags_type,deferred_type>();
}

template <class StateNameTag,class Expr1,class Expr2,class Attr>
inline
func_state<
StateNameTag,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr2,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr2)>,
    make_invalid_type>::type,
typename boost::result_of<BuildAttributes(Attr)>::type
>
build_state(Expr1 const& ,Expr2 const& ,Attr const&)
{
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    typedef typename boost::result_of<ActionGrammar(Expr2)>::type exit_action;
    typedef typename boost::result_of<BuildAttributes(Attr)>::type attributes_type;
    return func_state<StateNameTag,entry_action,exit_action,attributes_type>();
}

template <class StateNameTag,class Expr1,class Expr2>
inline
func_state<
StateNameTag,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr2,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr2)>,
    make_invalid_type>::type
>
build_state(Expr1 const& ,Expr2 const& )
{
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    typedef typename boost::result_of<ActionGrammar(Expr2)>::type exit_action;
    return func_state<StateNameTag,entry_action,exit_action>();
}

template <class StateNameTag,class Expr1>
inline
func_state<
StateNameTag,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
NoAction
>
build_state(Expr1 const& )
{
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    return func_state<StateNameTag,entry_action,NoAction>();
}
template<class StateNameTag>
inline
func_state<
StateNameTag,
NoAction,
NoAction
>
build_state()
{
    return func_state<StateNameTag,NoAction,NoAction>();
}

// provides the typedefs and interface. Concrete states derive from it.
template<class StateNameTag,
         class STT, 
         class Init,
         class EntryFunctor=NoAction, 
         class ExitFunctor=NoAction,
         class Attributes= ::boost::fusion::vector<>,
         class Flags = ::boost::mpl::vector0<>,
         class Defer = ::boost::mpl::vector0<>,
         class Configuration = ::boost::mpl::vector0<>,
         class NoTransitionFunctor = NoAction,
         class OnExceptionFunctor = NoAction,
         class BASE = ::boost::msm::front::default_base_state>
struct func_state_machine :  public ::boost::msm::front::detail::state_base<BASE,Attributes>, 
                             euml_state_intern<func_state_machine<StateNameTag,STT,Init,EntryFunctor,ExitFunctor,Attributes,Flags,
                                                        Defer,NoTransitionFunctor,OnExceptionFunctor,BASE> >
{
    func_state_machine(){}
    // grammar testing
    BOOST_MPL_ASSERT_NOT(( boost::is_same<EntryFunctor,invalid_type> ));
    BOOST_MPL_ASSERT_NOT(( boost::is_same<ExitFunctor,invalid_type> ));
    BOOST_MPL_ASSERT_NOT(( boost::is_same<NoTransitionFunctor,invalid_type> ));
    BOOST_MPL_ASSERT_NOT(( boost::is_same<OnExceptionFunctor,invalid_type> ));
    BOOST_MPL_ASSERT_NOT(( boost::is_same<STT,invalid_type> ));

    // flags
    typedef StateNameTag state_name_tag;
    typedef Flags                        flag_list;
    typedef ::boost::mpl::vector0<>      internal_flag_list;
    // deferred events
    typedef Defer                        deferred_events;
    // customization (message queue, exceptions)
    typedef Configuration                configuration;


    typedef BASE                         BaseAllStates;
    typedef STT                          transition_table;
    // the initial state of the player SM. Must be defined
    typedef Init                         initial_state;

    template <class Event,class FSM>
    void on_entry(Event const& evt,FSM& fsm)
    {
        EntryFunctor()(evt,fsm,*this);
    }
    template <class Event,class FSM>
    void on_exit(Event const& evt,FSM& fsm)
    {
        ExitFunctor()(evt,fsm,*this);
    }
protected:
    // Default no-transition handler. Can be replaced in the Derived SM class.
    template <class FSM,class Event>
    void no_transition(Event const& evt,FSM& fsm,int state)
    {
        NoTransitionFunctor()(evt,fsm,state);
    }
    // default exception handler. Can be replaced in the Derived SM class.
    template <class FSM,class Event>
    void exception_caught (Event const& evt,FSM& fsm,std::exception& e)
    {
        OnExceptionFunctor()(evt,fsm,e);
    }
};

template <class StateNameTag,class STT,class Init>
inline
func_state_machine<
StateNameTag,
STT,
typename boost::result_of<BuildInit(Init)>::type
>
build_sm(STT ,Init)
{
    typedef typename boost::result_of<BuildInit(Init)>::type init_type;
    return func_state_machine<StateNameTag,STT,init_type>();
}

template <class StateNameTag,class STT,class Init,class Expr1>
inline
func_state_machine<
StateNameTag,
STT,
typename boost::result_of<BuildInit(Init)>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type
>
build_sm(STT ,Init , Expr1 const&)
{
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    typedef typename boost::result_of<BuildInit(Init)>::type init_type;
    return func_state_machine<StateNameTag,STT,init_type,entry_action>();
}

template <class StateNameTag,class STT,class Init,class Expr1,class Expr2>
inline
func_state_machine<
StateNameTag,
STT,
typename boost::result_of<BuildInit(Init)>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr2,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr2)>,
    make_invalid_type>::type
>
build_sm(STT ,Init , Expr1 const& ,Expr2 const& )
{
    typedef typename boost::result_of<BuildInit(Init)>::type init_type;
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    typedef typename boost::result_of<ActionGrammar(Expr2)>::type exit_action;
    return func_state_machine<StateNameTag,STT,init_type,entry_action,exit_action>();
}

template <class StateNameTag,class STT,class Init,class Expr1,class Expr2,class Attr>
inline
func_state_machine<
StateNameTag,
STT,
typename boost::result_of<BuildInit(Init)>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr2,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr2)>,
    make_invalid_type>::type,
typename boost::result_of<BuildAttributes(Attr)>::type
>
build_sm(STT ,Init , Expr1 const& ,Expr2 const& ,Attr const&)
{
    typedef typename boost::result_of<BuildInit(Init)>::type init_type;
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    typedef typename boost::result_of<ActionGrammar(Expr2)>::type exit_action;
    typedef typename boost::result_of<BuildAttributes(Attr)>::type attributes_type;
    return func_state_machine<StateNameTag,STT,init_type,entry_action,exit_action,attributes_type>();
}

template <class StateNameTag,class STT,class Init,class Expr1,class Expr2,class Attr,class Configure>
inline
func_state_machine<
StateNameTag,
STT,
typename boost::result_of<BuildInit(Init)>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr2,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr2)>,
    make_invalid_type>::type,
typename boost::result_of<BuildAttributes(Attr)>::type,
typename boost::result_of<BuildFlags(Configure)>::type,
typename boost::result_of<BuildDeferred(Configure)>::type,
typename boost::result_of<BuildConfigure(Configure)>::type
>
build_sm(STT ,Init , Expr1 const& ,Expr2 const& , Attr const&, Configure const& )
{
    typedef typename boost::result_of<BuildInit(Init)>::type init_type;
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    typedef typename boost::result_of<ActionGrammar(Expr2)>::type exit_action;
    typedef typename boost::result_of<BuildAttributes(Attr)>::type attributes_type;
    typedef typename boost::result_of<BuildFlags(Configure)>::type flags_type;
    typedef typename boost::result_of<BuildDeferred(Configure)>::type deferred_type;
    typedef typename boost::result_of<BuildConfigure(Configure)>::type config_type;
    return func_state_machine<StateNameTag,STT,init_type,entry_action,exit_action,attributes_type,flags_type,
                              deferred_type,config_type>();

}

template <class StateNameTag,class STT,class Init,class Expr1,class Expr2,class Attr,class Configure,class Expr3>
inline
func_state_machine<
StateNameTag,
STT,
typename boost::result_of<BuildInit(Init)>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr2,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr2)>,
    make_invalid_type>::type,
typename boost::result_of<BuildAttributes(Attr)>::type,
typename boost::result_of<BuildFlags(Configure)>::type,
typename boost::result_of<BuildDeferred(Configure)>::type,
typename boost::result_of<BuildConfigure(Configure)>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr3,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr3)>,
    make_invalid_type>::type
>
build_sm(STT ,Init , Expr1 const& ,Expr2 const& ,Attr const&, Configure const&, Expr3 const& )
{
    typedef typename boost::result_of<BuildInit(Init)>::type init_type;
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    typedef typename boost::result_of<ActionGrammar(Expr2)>::type exit_action;
    typedef typename boost::result_of<ActionGrammar(Expr3)>::type no_transition_action;
    typedef typename boost::result_of<BuildAttributes(Attr)>::type attributes_type;
    typedef typename boost::result_of<BuildFlags(Configure)>::type flags_type;
    typedef typename boost::result_of<BuildDeferred(Configure)>::type deferred_type;
    typedef typename boost::result_of<BuildConfigure(Configure)>::type config_type;
    return func_state_machine<StateNameTag,STT,init_type,entry_action,exit_action,attributes_type,flags_type,deferred_type,
                              config_type,no_transition_action>();
}

template <class StateNameTag,class STT,class Init,class Expr1,class Expr2,class Attr,class Configure,class Expr3,class Expr4>
inline
func_state_machine<
StateNameTag,
STT,
typename boost::result_of<BuildInit(Init)>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr2,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr2)>,
    make_invalid_type>::type,
typename boost::result_of<BuildAttributes(Attr)>::type,
typename boost::result_of<BuildFlags(Configure)>::type,
typename boost::result_of<BuildDeferred(Configure)>::type,
typename boost::result_of<BuildConfigure(Configure)>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr3,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr3)>,
    make_invalid_type>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr4,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr4)>,
    make_invalid_type>::type
>
build_sm(STT ,Init , Expr1 const& ,Expr2 const& , Attr const&, Configure const&, Expr3 const&, Expr4 const& )
{
    typedef typename boost::result_of<BuildInit(Init)>::type init_type;
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    typedef typename boost::result_of<ActionGrammar(Expr2)>::type exit_action;
    typedef typename boost::result_of<BuildFlags(Configure)>::type flags_type;
    typedef typename boost::result_of<BuildDeferred(Configure)>::type deferred_type;
    typedef typename boost::result_of<BuildConfigure(Configure)>::type config_type;
    typedef typename boost::result_of<ActionGrammar(Expr3)>::type no_transition_action;
    typedef typename boost::result_of<ActionGrammar(Expr4)>::type on_exception_action;
    typedef typename boost::result_of<BuildAttributes(Attr)>::type attributes_type;
    return func_state_machine<StateNameTag,STT,init_type,entry_action,exit_action,attributes_type,flags_type,deferred_type,
                              config_type,no_transition_action,on_exception_action>();
}

template <class StateNameTag,class STT,class Init,class Expr1,class Expr2,class Attr,class Configure,class Expr3,class Expr4,class BASE>
inline
func_state_machine<
StateNameTag,
STT,
typename boost::result_of<BuildInit(Init)>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr2,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr2)>,
    make_invalid_type>::type,
typename boost::result_of<BuildAttributes(Attr)>::type,
typename boost::result_of<BuildFlags(Configure)>::type,
typename boost::result_of<BuildDeferred(Configure)>::type,
typename boost::result_of<BuildConfigure(Configure)>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr3,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr3)>,
    make_invalid_type>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr4,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr4)>,
    make_invalid_type>::type,
BASE
>
build_sm(STT ,Init , Expr1 const& ,Expr2 const& ,Attr const& , Configure const&, Expr3 const&, Expr4 const& , BASE )
{
    typedef typename boost::result_of<BuildInit(Init)>::type init_type;
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    typedef typename boost::result_of<ActionGrammar(Expr2)>::type exit_action;
    typedef typename boost::result_of<BuildFlags(Configure)>::type flags_type;
    typedef typename boost::result_of<BuildDeferred(Configure)>::type deferred_type;
    typedef typename boost::result_of<BuildConfigure(Configure)>::type config_type;
    typedef typename boost::result_of<ActionGrammar(Expr3)>::type no_transition_action;
    typedef typename boost::result_of<ActionGrammar(Expr4)>::type on_exception_action;
    typedef typename boost::result_of<BuildAttributes(Attr)>::type attributes_type;
    return func_state_machine<StateNameTag,STT,init_type,entry_action,exit_action,attributes_type,flags_type,deferred_type,
                              config_type,no_transition_action,on_exception_action,BASE>();
}

template <class Expr>
inline
::boost::msm::front::detail::inherit_attributes<typename boost::result_of<BuildAttributes(Expr)>::type>
build_attributes (Expr const&)
{
    return ::boost::msm::front::detail::inherit_attributes<typename boost::result_of<BuildAttributes(Expr)>::type> ();
}

template <class StateNameTag,class Expr1,class Expr2,class Attr,class Configure,class BASE>
inline
func_state<
StateNameTag,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr2,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr2)>,
    make_invalid_type>::type,
typename boost::result_of<BuildAttributes(Attr)>::type,
typename ::boost::mpl::push_back< typename boost::result_of<BuildFlags(Configure)>::type,
                                  ::boost::msm::TerminateFlag>::type,
typename boost::result_of<BuildDeferred(Configure)>::type,
BASE
>
build_terminate_state(Expr1 const& ,Expr2 const& , Attr const&, Configure const&, BASE )
{
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    typedef typename boost::result_of<ActionGrammar(Expr2)>::type exit_action;
    typedef typename ::boost::mpl::push_back<
        typename boost::result_of<BuildFlags(Configure)>::type,
        ::boost::msm::TerminateFlag >::type flags_type;
    typedef typename boost::result_of<BuildDeferred(Configure)>::type deferred_type;
    typedef typename boost::result_of<BuildAttributes(Attr)>::type attributes_type;
    return func_state<StateNameTag,entry_action,exit_action,attributes_type,flags_type,deferred_type,BASE>();
}

template <class StateNameTag,class Expr1,class Expr2,class Attr,class Configure>
inline
func_state<
StateNameTag,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr2,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr2)>,
    make_invalid_type>::type,
typename boost::result_of<BuildAttributes(Attr)>::type,
typename ::boost::mpl::push_back< typename boost::result_of<BuildFlags(Configure)>::type,
                                  ::boost::msm::TerminateFlag>::type,
typename boost::result_of<BuildDeferred(Configure)>::type
>
build_terminate_state(Expr1 const& ,Expr2 const& ,Attr const&, Configure const&)
{
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    typedef typename boost::result_of<ActionGrammar(Expr2)>::type exit_action;
    typedef typename ::boost::mpl::push_back<
        typename boost::result_of<BuildFlags(Configure)>::type,
        ::boost::msm::TerminateFlag >::type flags_type;
    typedef typename boost::result_of<BuildDeferred(Configure)>::type deferred_type;
    typedef typename boost::result_of<BuildAttributes(Attr)>::type attributes_type;

    return func_state<StateNameTag,entry_action,exit_action,attributes_type,flags_type,deferred_type>();
}

template <class StateNameTag,class Expr1,class Expr2,class Attr>
inline
func_state<
StateNameTag,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr2,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr2)>,
    make_invalid_type>::type,
typename boost::result_of<BuildAttributes(Attr)>::type,
::boost::mpl::vector<boost::msm::TerminateFlag> 
>
build_terminate_state(Expr1 const& ,Expr2 const& ,Attr const&)
{
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    typedef typename boost::result_of<ActionGrammar(Expr2)>::type exit_action;
    typedef typename boost::result_of<BuildAttributes(Attr)>::type attributes_type;
    return func_state<StateNameTag,entry_action,exit_action,attributes_type, ::boost::mpl::vector< ::boost::msm::TerminateFlag> >();
}

template <class StateNameTag,class Expr1,class Expr2>
inline
func_state<
StateNameTag,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr2,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr2)>,
    make_invalid_type>::type,
::boost::fusion::vector<>,
::boost::mpl::vector<boost::msm::TerminateFlag> 
>
build_terminate_state(Expr1 const& ,Expr2 const& )
{
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    typedef typename boost::result_of<ActionGrammar(Expr2)>::type exit_action;
    return func_state<StateNameTag,entry_action,exit_action,
                      ::boost::fusion::vector<>, ::boost::mpl::vector< ::boost::msm::TerminateFlag> >();
}

template <class StateNameTag,class Expr1>
inline
func_state<
StateNameTag,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
NoAction,
::boost::fusion::vector<>,
::boost::mpl::vector<boost::msm::TerminateFlag> 
>
build_terminate_state(Expr1 const& )
{
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    return func_state<StateNameTag,entry_action,NoAction,::boost::fusion::vector<>,::boost::mpl::vector<boost::msm::TerminateFlag> >();
}
template<class StateNameTag>
inline
func_state<
StateNameTag,
NoAction,
NoAction,
::boost::fusion::vector<>,
::boost::mpl::vector<boost::msm::TerminateFlag> 
>
build_terminate_state()
{
    return func_state<StateNameTag,NoAction,NoAction,::boost::fusion::vector<>,::boost::mpl::vector<boost::msm::TerminateFlag> >();
}

template <class StateNameTag,class Expr1,class Expr2,class Attr,class Configure,class BASE,class EndInterruptEvent>
inline
func_state<
StateNameTag,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr2,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr2)>,
    make_invalid_type>::type,
typename boost::result_of<BuildAttributes(Attr)>::type,
typename ::boost::mpl::push_back<
    typename ::boost::mpl::push_back< typename boost::result_of<BuildFlags(Configure)>::type,
                                      ::boost::msm::InterruptedFlag>::type,
    boost::msm::EndInterruptFlag<EndInterruptEvent>
    >::type,
typename boost::result_of<BuildDeferred(Configure)>::type,
BASE
>
build_interrupt_state(EndInterruptEvent const&,Expr1 const& ,Expr2 const& , Attr const&, Configure const&, BASE )
{
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    typedef typename boost::result_of<ActionGrammar(Expr2)>::type exit_action;
    typedef typename boost::result_of<BuildAttributes(Attr)>::type attributes_type;
    typedef typename ::boost::mpl::push_back<
                typename ::boost::mpl::push_back< 
                    typename boost::result_of<BuildFlags(Configure)>::type,
                    ::boost::msm::InterruptedFlag>::type,
                boost::msm::EndInterruptFlag<EndInterruptEvent>
    >::type flags_type;
    typedef typename boost::result_of<BuildDeferred(Configure)>::type deferred_type;
    return func_state<StateNameTag,entry_action,exit_action,attributes_type,flags_type,deferred_type,BASE>();
}

template <class StateNameTag,class Expr1,class Expr2,class Attr,class Configure,class EndInterruptEvent>
inline
func_state<
StateNameTag,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr2,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr2)>,
    make_invalid_type>::type,
typename boost::result_of<BuildAttributes(Attr)>::type,
typename ::boost::mpl::push_back<
    typename ::boost::mpl::push_back< typename boost::result_of<BuildFlags(Configure)>::type,
                                      ::boost::msm::InterruptedFlag>::type,
    boost::msm::EndInterruptFlag<EndInterruptEvent>
    >::type,
typename boost::result_of<BuildDeferred(Configure)>::type
>
build_interrupt_state(EndInterruptEvent const&,Expr1 const& ,Expr2 const& ,Attr const&, Configure const&)
{
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    typedef typename boost::result_of<ActionGrammar(Expr2)>::type exit_action;
    typedef typename boost::result_of<BuildAttributes(Attr)>::type attributes_type;

    typedef typename ::boost::mpl::push_back<
                typename ::boost::mpl::push_back< 
                    typename boost::result_of<BuildFlags(Configure)>::type,
                    ::boost::msm::InterruptedFlag>::type,
                boost::msm::EndInterruptFlag<EndInterruptEvent>
    >::type flags_type;
    typedef typename boost::result_of<BuildDeferred(Configure)>::type deferred_type;

    return func_state<StateNameTag,entry_action,exit_action,attributes_type,flags_type,deferred_type>();
}

template <class StateNameTag,class Expr1,class Expr2,class Attr,class EndInterruptEvent>
inline
func_state<
StateNameTag,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr2,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr2)>,
    make_invalid_type>::type,
typename boost::result_of<BuildAttributes(Attr)>::type,
::boost::mpl::vector<boost::msm::InterruptedFlag, boost::msm::EndInterruptFlag<EndInterruptEvent> > 
>
build_interrupt_state(EndInterruptEvent const&,Expr1 const& ,Expr2 const& ,Attr const&)
{
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    typedef typename boost::result_of<ActionGrammar(Expr2)>::type exit_action;
    typedef typename boost::result_of<BuildAttributes(Attr)>::type attributes_type;
    return func_state<StateNameTag,entry_action,exit_action,attributes_type, 
                     ::boost::mpl::vector< boost::msm::InterruptedFlag, boost::msm::EndInterruptFlag<EndInterruptEvent> > >();
}

template <class StateNameTag,class Expr1,class Expr2,class EndInterruptEvent>
inline
func_state<
StateNameTag,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr2,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr2)>,
    make_invalid_type>::type,
::boost::fusion::vector<>,
::boost::mpl::vector<boost::msm::InterruptedFlag, boost::msm::EndInterruptFlag<EndInterruptEvent> > 
>
build_interrupt_state(EndInterruptEvent const&,Expr1 const& ,Expr2 const& )
{
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    typedef typename boost::result_of<ActionGrammar(Expr2)>::type exit_action;
    return func_state<StateNameTag,entry_action,exit_action,
                      ::boost::fusion::vector<>, 
                      ::boost::mpl::vector< boost::msm::InterruptedFlag, boost::msm::EndInterruptFlag<EndInterruptEvent> > >();
}

template <class StateNameTag,class Expr1,class EndInterruptEvent>
inline
func_state<
StateNameTag,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
NoAction,
::boost::fusion::vector<>,
::boost::mpl::vector<boost::msm::InterruptedFlag, boost::msm::EndInterruptFlag<EndInterruptEvent> > 
>
build_interrupt_state(EndInterruptEvent const&, Expr1 const&)
{
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    return func_state<StateNameTag,entry_action,NoAction, ::boost::fusion::vector<>,
                     ::boost::mpl::vector<boost::msm::InterruptedFlag, boost::msm::EndInterruptFlag<EndInterruptEvent> > >();
}

template <class StateNameTag,class EndInterruptEvent>
inline
func_state<
StateNameTag,
NoAction,
NoAction,
::boost::fusion::vector<>,
::boost::mpl::vector<boost::msm::InterruptedFlag, boost::msm::EndInterruptFlag<EndInterruptEvent> > 
>
build_interrupt_state(EndInterruptEvent const&)
{
    return func_state<StateNameTag,NoAction,NoAction, ::boost::fusion::vector<>,
                      ::boost::mpl::vector<boost::msm::InterruptedFlag, boost::msm::EndInterruptFlag<EndInterruptEvent> > >();
}

template <class StateNameTag,int ZoneIndex,class Expr1,class Expr2,class Attr,class Configure,class BASE>
inline
entry_func_state<
StateNameTag,
ZoneIndex,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr2,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr2)>,
    make_invalid_type>::type,
typename boost::result_of<BuildAttributes(Attr)>::type,
typename boost::result_of<BuildFlags(Configure)>::type,
typename boost::result_of<BuildDeferred(Configure)>::type,
BASE
>
build_entry_state(Expr1 const& ,Expr2 const& , Attr const&, Configure const&, BASE )
{
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    typedef typename boost::result_of<ActionGrammar(Expr2)>::type exit_action;
    typedef typename boost::result_of<BuildFlags(Configure)>::type flags_type;
    typedef typename boost::result_of<BuildDeferred(Configure)>::type deferred_type;
    typedef typename boost::result_of<BuildAttributes(Attr)>::type attributes_type;
    return entry_func_state<StateNameTag,ZoneIndex,entry_action,exit_action,attributes_type,flags_type,deferred_type,BASE>();
}

template <class StateNameTag,int ZoneIndex,class Expr1,class Expr2,class Attr,class Configure>
inline
entry_func_state<
StateNameTag,
ZoneIndex,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr2,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr2)>,
    make_invalid_type>::type,
typename boost::result_of<BuildAttributes(Attr)>::type,
typename boost::result_of<BuildFlags(Configure)>::type,
typename boost::result_of<BuildDeferred(Configure)>::type
>
build_entry_state(Expr1 const& ,Expr2 const& ,Attr const&, Configure const&)
{
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    typedef typename boost::result_of<ActionGrammar(Expr2)>::type exit_action;
    typedef typename boost::result_of<BuildFlags(Configure)>::type flags_type;
    typedef typename boost::result_of<BuildDeferred(Configure)>::type deferred_type;
    typedef typename boost::result_of<BuildAttributes(Attr)>::type attributes_type;
    return entry_func_state<StateNameTag,ZoneIndex,entry_action,exit_action,attributes_type,flags_type,deferred_type>();
}

template <class StateNameTag,int ZoneIndex,class Expr1,class Expr2,class Attr>
inline
entry_func_state<
StateNameTag,
ZoneIndex,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr2,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr2)>,
    make_invalid_type>::type,
typename boost::result_of<BuildAttributes(Attr)>::type
>
build_entry_state(Expr1 const& ,Expr2 const& ,Attr const&)
{
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    typedef typename boost::result_of<ActionGrammar(Expr2)>::type exit_action;
    typedef typename boost::result_of<BuildAttributes(Attr)>::type attributes_type;
    return entry_func_state<StateNameTag,ZoneIndex,entry_action,exit_action,attributes_type>();
}

template <class StateNameTag,int ZoneIndex,class Expr1,class Expr2>
inline
entry_func_state<
StateNameTag,
ZoneIndex,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr2,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr2)>,
    make_invalid_type>::type
>
build_entry_state(Expr1 const& ,Expr2 const& )
{
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    typedef typename boost::result_of<ActionGrammar(Expr2)>::type exit_action;
    return entry_func_state<StateNameTag,ZoneIndex,entry_action,exit_action>();
}

template <class StateNameTag,int ZoneIndex,class Expr1>
inline
entry_func_state<
StateNameTag,
ZoneIndex,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
NoAction
>
build_entry_state(Expr1 const& )
{
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    return entry_func_state<StateNameTag,ZoneIndex,entry_action,NoAction>();
}

template <class StateNameTag,int ZoneIndex>
inline
entry_func_state<
StateNameTag,
ZoneIndex,
NoAction,
NoAction
>
build_entry_state()
{
    return entry_func_state<StateNameTag,ZoneIndex,NoAction,NoAction>();
}

template <class StateNameTag,class Event,class Expr1,class Expr2,class Attr,class Configure,class BASE>
inline
exit_func_state<
StateNameTag,
Event,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr2,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr2)>,
    make_invalid_type>::type,
typename boost::result_of<BuildAttributes(Attr)>::type,
typename boost::result_of<BuildFlags(Configure)>::type,
typename boost::result_of<BuildDeferred(Configure)>::type,
BASE
>
build_exit_state(Event const&,Expr1 const& ,Expr2 const& , Attr const&, Configure const&, BASE )
{
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    typedef typename boost::result_of<ActionGrammar(Expr2)>::type exit_action;
    typedef typename boost::result_of<BuildFlags(Configure)>::type flags_type;
    typedef typename boost::result_of<BuildDeferred(Configure)>::type deferred_type;
    typedef typename boost::result_of<BuildAttributes(Attr)>::type attributes_type;
    return exit_func_state<StateNameTag,Event,entry_action,exit_action,attributes_type,flags_type,deferred_type,BASE>();
}

template <class StateNameTag,class Event,class Expr1,class Expr2,class Attr,class Configure>
inline
exit_func_state<
StateNameTag,
Event,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr2,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr2)>,
    make_invalid_type>::type,
typename boost::result_of<BuildAttributes(Attr)>::type,
typename boost::result_of<BuildFlags(Configure)>::type,
typename boost::result_of<BuildDeferred(Configure)>::type
>
build_exit_state(Event const&,Expr1 const& ,Expr2 const& ,Attr const&, Configure const&)
{
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    typedef typename boost::result_of<ActionGrammar(Expr2)>::type exit_action;
    typedef typename boost::result_of<BuildFlags(Configure)>::type flags_type;
    typedef typename boost::result_of<BuildDeferred(Configure)>::type deferred_type;
    typedef typename boost::result_of<BuildAttributes(Attr)>::type attributes_type;
    return exit_func_state<StateNameTag,Event,entry_action,exit_action,attributes_type,flags_type,deferred_type>();
}

template <class StateNameTag,class Event,class Expr1,class Expr2,class Attr>
inline
exit_func_state<
StateNameTag,
Event,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr2,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr2)>,
    make_invalid_type>::type,
typename boost::result_of<BuildAttributes(Attr)>::type
>
build_exit_state(Event const&,Expr1 const& ,Expr2 const& ,Attr const&)
{
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    typedef typename boost::result_of<ActionGrammar(Expr2)>::type exit_action;
    typedef typename boost::result_of<BuildAttributes(Attr)>::type attributes_type;
    return exit_func_state<StateNameTag,Event,entry_action,exit_action,attributes_type>();
}

template <class StateNameTag,class Event,class Expr1,class Expr2>
inline
exit_func_state<
StateNameTag,
Event,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr2,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr2)>,
    make_invalid_type>::type
>
build_exit_state(Event const&,Expr1 const& ,Expr2 const& )
{
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    typedef typename boost::result_of<ActionGrammar(Expr2)>::type exit_action;
    return exit_func_state<StateNameTag,Event,entry_action,exit_action>();
}

template <class StateNameTag,class Event,class Expr1>
inline
exit_func_state<
StateNameTag,
Event,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
NoAction
>
build_exit_state(Event const&, Expr1 const& )
{
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    return exit_func_state<StateNameTag,Event,entry_action,NoAction>();
}

template <class StateNameTag,class Event>
inline
exit_func_state<
StateNameTag,
Event,
NoAction,
NoAction
>
build_exit_state(Event const&)
{
    return exit_func_state<StateNameTag,Event,NoAction,NoAction>();
}

template <class StateNameTag,int ZoneIndex,class Expr1,class Expr2,class Attr,class Configure,class BASE>
inline
explicit_entry_func_state<
StateNameTag,
ZoneIndex,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr2,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr2)>,
    make_invalid_type>::type,
typename boost::result_of<BuildAttributes(Attr)>::type,
typename boost::result_of<BuildFlags(Configure)>::type,
typename boost::result_of<BuildDeferred(Configure)>::type,
BASE
>
build_explicit_entry_state(Expr1 const& ,Expr2 const& , Attr const&, Configure const&, BASE )
{
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    typedef typename boost::result_of<ActionGrammar(Expr2)>::type exit_action;
    typedef typename boost::result_of<BuildFlags(Configure)>::type flags_type;
    typedef typename boost::result_of<BuildDeferred(Configure)>::type deferred_type;
    typedef typename boost::result_of<BuildAttributes(Attr)>::type attributes_type;
    return explicit_entry_func_state<StateNameTag,ZoneIndex,entry_action,exit_action,attributes_type,flags_type,deferred_type,BASE>();
}

template <class StateNameTag,int ZoneIndex,class Expr1,class Expr2,class Attr,class Configure>
inline
explicit_entry_func_state<
StateNameTag,
ZoneIndex,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr2,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr2)>,
    make_invalid_type>::type,
typename boost::result_of<BuildAttributes(Attr)>::type,
typename boost::result_of<BuildFlags(Configure)>::type,
typename boost::result_of<BuildDeferred(Configure)>::type
>
build_explicit_entry_state(Expr1 const& ,Expr2 const& ,Attr const&, Configure const&)
{
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    typedef typename boost::result_of<ActionGrammar(Expr2)>::type exit_action;
    typedef typename boost::result_of<BuildFlags(Configure)>::type flags_type;
    typedef typename boost::result_of<BuildDeferred(Configure)>::type deferred_type;
    typedef typename boost::result_of<BuildAttributes(Attr)>::type attributes_type;
    return explicit_entry_func_state<StateNameTag,ZoneIndex,entry_action,exit_action,attributes_type,flags_type,deferred_type>();
}

template <class StateNameTag,int ZoneIndex,class Expr1,class Expr2,class Attr>
inline
explicit_entry_func_state<
StateNameTag,
ZoneIndex,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr2,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr2)>,
    make_invalid_type>::type,
typename boost::result_of<BuildAttributes(Attr)>::type
>
build_explicit_entry_state(Expr1 const& ,Expr2 const& ,Attr const&)
{
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    typedef typename boost::result_of<ActionGrammar(Expr2)>::type exit_action;
    typedef typename boost::result_of<BuildAttributes(Attr)>::type attributes_type;
    return explicit_entry_func_state<StateNameTag,ZoneIndex,entry_action,exit_action,attributes_type>();
}

template <class StateNameTag,int ZoneIndex,class Expr1,class Expr2>
inline
explicit_entry_func_state<
StateNameTag,
ZoneIndex,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr2,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr2)>,
    make_invalid_type>::type
>
build_explicit_entry_state(Expr1 const& ,Expr2 const& )
{
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    typedef typename boost::result_of<ActionGrammar(Expr2)>::type exit_action;
    return explicit_entry_func_state<StateNameTag,ZoneIndex,entry_action,exit_action>();
}

template <class StateNameTag,int ZoneIndex,class Expr1>
inline
explicit_entry_func_state<
StateNameTag,
ZoneIndex,
typename ::boost::mpl::eval_if<
    typename proto::matches<Expr1,ActionGrammar>::type,
    boost::result_of<ActionGrammar(Expr1)>,
    make_invalid_type>::type,
NoAction
>
build_explicit_entry_state(Expr1 const& )
{
    typedef typename boost::result_of<ActionGrammar(Expr1)>::type entry_action;
    return explicit_entry_func_state<StateNameTag,ZoneIndex,entry_action,NoAction>();
}

template <class StateNameTag,int ZoneIndex>
inline
explicit_entry_func_state<
StateNameTag,
ZoneIndex,
NoAction,
NoAction
>
build_explicit_entry_state()
{
    return explicit_entry_func_state<StateNameTag,ZoneIndex,NoAction,NoAction>();
}



}}}}

#endif //BOOST_MSM_FRONT_EUML_STATE_GRAMMAR_H


/* state_grammar.hpp
RuPwWphyq/XV4ZsIj/nGo4yvFdg5a0x1BDXGteU6GshFcK8IV6acAs3tl4ObiCoG7Mi04tBiOfBjVyh77W4ItoT6YYXP3Hv/PI3eFn0G/Yg+gUSIvknGG7AQMvNFhwlHjFlOpCsiLJrMExbC9jlJDaAITIXvSuAZlBbGhvzg87ESOMkeJb/yySTW4zO+o3jE34DLaAZJ+0lfCRUDXngYvVCGQAaDulgXuTe4hSQG1PVKCK7HpBqNjR11O5W7lSOV13ULdRAP4A+YQFiD97JjAHM5993rnWlqOIHxvu0T4WLAVh7Y9R7MdnA8vR6sMm0x95huC93G1PepgWQE//EVywkYzMR5n+/s93b3GkuNaFq4grrmaLVsZfIuCXJxumFBYgFnZuO/OyGIvjqq6AyMEBy9p4buwQJZMVg9kRDsArVzziJnhl0mzYJrKmMp1wl/CY8LDwqvMEIe7+sT35GRXRm9Db3NvK1Z6vBzL+v1mlSalA9Uov7y0D1/ub0yX5idyn/66VaO/ur9Zvw0fVvUXKSgVw1+Mt98No+6FtSlxyFWyl9x3quu4v3eLYwW8rcBsZO6RZLeT09Yb24Pbg8xtZ6sBCqw+v3sT+8Mrk/3YQZI3VCNeKyZ6EDDRm1r7jGyMsu/fDTnIdOI+xkJp3wZrUx3pVSWFVYh1XazY2+Rbc3jGfNkcK1wIXKncJn4WPP3+uEEGvXbUhzUywjSCZLUZ9U/FiwWtBSIjF+Od7yZBDMET2+r6di8QG3LW3+wda7ufs+f+uAU6VS1yiWt8/RtoHhQb9BzBpFFkBfMbJIPJLWIK4sfvm6+GkokEFYocSqFBLGyfOMAy6WUZoTNRvOdzJ+kXGRdGKeQoD6jnqGuVT1VzVehxpSx1mVJQ1Ouco3qfTeojZ3OGKlmqRPmnA9u9Trgt9pjIpV81xtIGZg3SDWIDTUPxTrzkZKRekoJygBFa/KPbcIV+vF3XOB7zvWoiaGKweKUxmypH6iVqIecn8jZm0WfXdx1wlLQjV2x22zFGued6jjLfkZLwIBfV2XvxZbLkeNa6T7iZ9x8b3zz2u9ubq93L/L9l+KwUbYHzQPv6eEx5OsF4OeV41nr/cBJySnPq8V3wNuze5771gh4F/+IqfWKcZqR8LiqwGEfzaAh4bP2r+jgc5XorhDJFnP2NQ0KGxXUAXltib5M3bytKAIWF70v4l2oWvTE5DY0ehLQCD0Imzh2MpUJ9Rgqk1aCRgDUZZRvpFHE5d62y63jLVPcixqDUkKmXYViy13He+6jA3FDydfLFfvtAeSatpbgZqkNoAO2KRZdllogRrqpxGZBwajdi8IFTTUsizatvFtctpBHhFtGuvSYO6a+b1/lC1hppUViwMIlyHhIR0ITf5Tv0jP8maO2vIaiBITikqYvdzDJKSU/D66YQeQDfGgScOLeuPQfnqUUVwIrJqcFq6iVkFlu1A9sALNInH4WfuhvUKIy6cBgoav3LVOkbb0bfLX07ctULS/Hi/KBIlnpf93le0eTQVtDP7NvdHBxP33LJxmJo42b/wyVW3nN8j6oRxif2aca1dI2LmENWWezQjmKKjutVrJn59Co00brmCGtMK1iT15DSeW31lhjnIpO9tbV2lVphrXWdnRbmFSZOnVoe/o+2wwXDYGMuJjp3enY8SyXWLqjwDZ/VnHfGFj4o+8frKve7Vsff11b5dn1ZgxsDW6MbG0fmhHVqhavLO/YFjgttIRYkhxxaPqSdc1WNJbaN1G0i9aN1YfeG9ZLLtyyE310+fRt+457p1142xbNO77+tbmgEmQfpdwbu4x0f5imWbX7vN+/lxrFGM6EtwZ5ChzWRpV1fg149+JdvEPIgRQNhPSHFEgl5GpyamjeqXK0qvxbJ30cTpyA4tSFOtWrM2Ey4bl3NB0fA0ObRaVyo/bzpVu5wTCDt4I1+2js+VoUqKSxHGhYzELWkN041CTY2X0o4klggW8CixkrCY+HSuFcwyXdS1mZ+c2Bp2TMM0U6/aq5Oews61rNZHh2m7x097P8JHk4rkbe8XKTq+S+aO9pstFaq9g5qbX9QpAWVjaqkRLYe1m8H35wcW4jEfVzt4LUWHw25m2hAeAAACz/0/OdJO0ZOHPa4gGDRwK9U7Mx6Vjxo+25ZBkyGAjZ2NmKaCb75sPbvjI/81bbw9s1fJ7pmuiawr/Qn1J9aiF2IULb793fbi/jz7oebseqYLd/eERY8JUEbuOgdFe9EtMhI73+vKE/q2+H9kfFs56GkmMBg90O9vDh/7x26sRHDUUx6prvWuLjwo9cHQ2qpIfxpQ6hgPYy83PPbOkZrjaRWrfaaLODd0U0if0YecfkecGTgIG/HebNWsvK8gP8KSuMDuD6xAdFB/3C34R16LDQVaw+kXqxr079vp2+fB8QDx9bnwp1dDFxBmUCzP85lOfcHQPGNEOeTb6FD7N92pWm60S3InoxHJdDm/uK0pg2Ztlk0UVbHA6F4sX18fMnP+AKyn2c/sX4T9nXZVXt0or24bn7/U3F9aQ6+Vt+v0yvQ7VtzeWoUf55bOReOe39eaxlb63o2RH10bElYGBwdsTy+82wQ4yq7B0lra7H57kG9MWXzw1PKj1RzjWpCAHAJJSOWW3qWTBSpf9FtGp9JVgBqEoWOp0RWBl3ahj2mOuOXh+P+tS+S01jJfbAu9nMvZQp3xdpzeMiDLug8LGFRhGv1ePn6yknz1szQsTmTtPU+mGwgy1m47vrxpbpqUOoJVmg0EWQggC8WDhTasKHnABmilfTgRvnk3mDMKb08qFsNLlP74hSKKTToESSLxJyJ21rTTXNwYu2007hOyJ2TOiK8HfZjvPpQWy2GC/E07MMKyxjJ2fNKcMPj8TupnGr5thrtjGk7Db3Fo9sdidMDylsXtgMUSY81FCKT8zCl+XC1mT7B+5lL8VmHZMSbMY2ZPqJLME48sinNjhp1JhmhV5P8dVH3pFaDsf3nTmXSv5nZVkkAV+FEYmE8AHMiG65tKburU0aqT5VgQTmuVY+KW6nJK4FcyX6RET2lLXS9dFmhnShbkWsKI9ujKfRq3+iXvThQsY37ukRNMlaL2NYesw6JS9lm5V+KaO1Ct22Nh3KPw17vfZWpoPbp0WnfsQ5EvCss++jcOPF1B1mvt0NF4l+ZVpdk5AwY6baZ5Kfc0dsipwF6qRMf2ouNoCctd90aCTttuMcEHaD8+S+FALiaptEAmCozDR8GjRE5D54KaLj4Dmi9agjpxgg8jBOmComTOYorwYydGrlsSVrW8z861kKJ65soeOdkeSmkE1dim/5vKmr6oRMPdPb6SHh3+dXSOl1LfYAG83oXkJbCirkcJAn5qJMkVxoKAE20NzJ1jC/wACQCZEku3jM4TqLxqc5aEF4G9Yl9shBdXLxWu6FZFdY+MjKB7vy5VpBqDgfMWGuZnYLCOLFZGaH5B4h2hV2RWeUDtJldx7rhsYPqCFsJP+2tqdGekhgdD2kp0r1vXZmE8hOpcwjBQZ242FnPuWtaYU2UirwXJBKWH2i3WHJtOyFkDP2KkMK4jiIjnBX+ZMV7fzsB+Pqd/zLLBoxqkP7LmW0Ae/rdYzINZJP5vpAmwGPC/yoRvEtG3W18fDdRsR9oCkbXBeiphZPHnnprJVIsC7HC1nPqSv5nac4oiwetk8KeGoWWQgWu2kxdGGSsOyGJ2PKgMzmzW2XYjW829bbcJUZJ6GV0qH7Lh0GySBuYOX15q4BgdqiM9FtwZimD+9Ugr8N/Z2F5HN9EQ5oIFQOMRALmwDPBK71gj6dEEraosMQoWRxesix0SJwpMsICSPBIvBtDQOkp3Y4cg3ZP5NsAqZPCO7UpkMhi6iGcsYx9U0XkmEXL3OAGP1oKX+ukMkNakhAHp53RZl/YBZ1Q11lcEz8SQi5qaWnhBD7uoQpCteNY8qePa9c56amtPMQIK57yi4KKi57UkokyCn0HbqAznFRd6IupIaR8R/Y4Tzb/sBijmFugMPUfnerthcooPhkMV0YDvi+8hrgKNWevDWZ6kEAPTAHpt+wV/Pdj0FPcl57CY7yphWwWx2urKEOHZ5hkPH/ZPBmuJFmBdks0pbiFc3jB6QQjZNci43ExVMq63ksmPJRBlMwtTRewYzOWrzMoxjQcuM1gP0Lhw4nlioFurW+RQLjQcYhmr5XoS6+CUS06q+d7zcbYq5FgM+cSgn6PbtwQpTmkzJOpN2GZoQ+xZHmSkKgPqf2XVcrBEnnxEGCWu+HvDPqAekFcZout1eLPK1AEA1yHCKo1wd+G1f9acTb2Pa5uMOr94K5Qlm99MkgCZ5xc+GD91qB6XWBqgKpRdbMZeT/M8oMTLqW+IzfR+NPobs+oSKYVw9sNfN2Akypb5fxdGx1s3GJkOXmvoc5ai9XRN2h2+9Finxxo1ztTS2Y4UhjWM9vHNMxQE6PHnSP8qMbOVCQto/xZq4AxlE7RXPnHHB7GPjGgi68nozqaE8INnE4P/5MbVbmrX/qMsSgtH3/3rNNsS1ZjjNxxm/DIs0u/8dgAWlm9UXgaupstGG3dduZ9kBXcmocEzLldup8QJFtjJvH23TVjvuYWej7OjiHPTtdaiolQnXcCgUwIgDipMvkE4whpI8nQ6p4b/tyiD4dkuFUyCFaBeCM6XwbNb1H8EkoE0IhfBO8z6UNitcmhtuUHor09lgnanPxgmeB5Yx7tA1TinCqnRwHfYa+csDwnTq8mMagXbmSJdLOi/u61OeMI2Zs03902QdiTwlMbXHjBcHHJpUDeQl0NILvlpMXJwajy6uuGTGtPTr0ZtkkKE2vKmWZHenwEMSPuhfTwAdOsDDOZlUDwWdJLtjPC1Eo68bJjXpToScXu/DoOiOJyqSxUP3fzpIBEH46WIpgN4MDTabqSEe7f6Oie/LTBsTioiIpm9RjiYy6m5HaXmrCuOSjE7S1Um3LMJbQwY4Jtetb56CQ6uHh26B7Aw4ewdYPjp0cSGNcW7NEE2Nif/5pL45vl3LxMpojLbC+uBApbYr8GE1Av52MVCwQhRI/tlWQHaIqllDB8MOoHneCAF542Mcr7pk+ZxsxliAzwxq0ARv9cixaF8IgW0La59di5BjZg5jVeFwTThZapvs4yLO69JBv4EGPv7AIRLDSC7z3tj6cFTskRh5xoWTjwbhcE+nK4FGfs+wpvQWwd4pfNtGpqA0rT2wnazAyP8LwO8n0Q3mOews23JSml3oRkz7qStQ2omvde9mF4zAI7DpPRHtqb6HfzMvQFaEJRx8uPCZjUroAC4dZRNIJ3dNpVtKAPLdKz97Gr6Sb9fxgr4lOaPM6ZX4XDqRgFDHMaQOtgQEkzvHJ8FmcwGTGfBf7qvrPtXfEwgUQUsWjmzei50vco61ztsOMe6XwfxPJbzbEm7Jo/RY4tihXGUVgGSoN0iNP+wzNfEtmMcfQAGAwyRC3ryWNYZnky0orMWI2gnWPPnlo6ZJu7iKuC0QvWnjM0Pul8LDnD80r33zFhAc0/22Jh3W6Sp/dPDbrkwwuMdN8422QUpgfnJLNLy9LDr1+6kbKtKvpgXQvEe3LOmOLEzVsm87wcrNnQoSUiBfPENI/2s/BJbPY2+NTkh166Q+0izgzQBV3jZEoLpNKb9dvEYZFtLJXONO2kqduoQk6DU3qUArVcHlvb2Gu6WBwBdw686b2j1Zmep9Ap+SchPhoxP0KY3EDzxw4OjUKD8m/NSy1b42Zl4Pe7vsCNbnOM387s1Xf+Ho0LcWJ5nKi4qpnxb8sxDvYWNV/KFvnKA5zSs2fi1KyFVkRMLimrImXuz1I4u2mUEQ+G6sLfq/dJQKi8eBJAs1u1ZDQ8Rvmjl7dtVYcCvkgli3BBesHNTS0Fd69nXC6aa7Ny4sqFYodTdeWbh7uwdLoyUT8xDL0Vuy0rgGT9CLzEHD9RJEysYC/Zxs95+G8oG2uqZ2iI6bQx6fMMrrrEWsPS2vIxM+Po32PQvOAvEVRDZSXszFmufHm4+AtJOJSKfClMK7jU+uOp/Lclvg3WaQFLtXHRsLIquidA9jQNvhIRZE2e0aA1A0Z6q/4uCUjuzHzg0hunOBMrhn2KoeVG7uT5jQ58F3nV4nRV0gj9SHEiVSl3lACCtvBIpBbVIQwu8k14Qj2ss6HKyCN1fFN9cVerGYYsVXT/8MZju3drf9EYFjHtaQxsEae2kdMyKH9qEdCttKWBqaTeWgNO73MkF3McWaPFI0KY9K+HXvg6uAgE/8HFRqMTwSncLUeVWoAbaqgmc4BLjo1N31TiTa/I5m8RZ1/d8iZce5XvW/MRPzYcTWqUk2wjmwX4zWqRauGxrdTzQZoMaMO4SzntU+hyhwy3yPnO1CiKxXS4IsULQ2nR/v9ddqR+4m3xlo4yaEdoURgzkPNPQNiconXzBNdNrMiDz62AKlIEc2XleHK5+PRDHxYStJkpYTGWCuazsXdIHdSWmSJx7cVZiNfXhvTYBFoeEt7+zNUOecVXLbjsPe5xSkISYAm0xdKo2wUTPMvCu8pPGRvEF10yz6e3krAsJvfSPzUTUFmUS8/k1tU9tpFeuaVyJMwR/sSu0OPdKgEzOKUwopFK22HSUiOZUA5ccbXDavk+Aaz/6ehkctRyiUKsUWo3CZ6HeveiV7e+PdJhLXUJiQ6Kp3Tp173384zd0TqZ1xg8WwLTvLUKjusHtrhrQ9Bp30QevizbN6zpZPHULcpx2lY1HgVaNTLxHZ0eVRRkrIU4u3S4OWanXvViHEgNJuhXp3jRp31irBtKnwTg8OKcXEzr5nWFeDbf2oGV3TsVlfYFw3NDbPrvAgQqIwGQoYOUNueMMJFS7QC+RT1wInR68x8QRP6WtE03KWdl+/b+HTprXmC32XJBLRp/YfS/v79CdSbSP8JUaYdF/zQqsyVU4i8N9/Ng0YgrCf4p/FGPWvdGiE2yRWqI07N3kCdchp2fiqa5ymHnQVNsg9ftFCoKsT491moRvVX7jTMig9vUqUcXz3mG3smsfcy3ntpGTbH2skfUUCusIFw3k7qnL26FV9FV4IP1EEfzVmerUBy3AJynVSd4fTNrZHKLDWLyb0om2kxkpRIAqiB5Dwdk+YhBfnHAxfyk9emfhoRZhwKAgbuAQ5w7KG5QrPyMcbbhHNGebmql5G8aX9iBp+qfbYdZsdkNfqw/LRENT9rRpyyBFIkaDGl8iRmlzzGKQlZNNRq887FBhPhkcYL9xyeEBe4iJDQMvBRlDSC4/foVjzFXSKTa+Act4bBEMGaYfUMtjyb0osxLrl2EpaiVWjbN+yoe2h9bKrqdR/+dsy8pqrwg4Q9sBqrECy2KkQBgLw9M+8LTckISZz8QCicHNfDbo+0svJRioAD3S3iyklTGUXoIinJJnPXLDRvvOAbIMzDsP6XvooWYDOM55i60Q9aZFlZubnV0oY9BUuNtDdQg5pRWQatZuCH9vQMlAC/CNUMt9CV/BMnXBnqIx8VoEHWG7oF4pMOWd8Q+/rskQHw8/rND9JWaBxIr3MEldE5+oFRdsqgMoNZK07AQUyi9EsYSot5rS6ncoEdmsQ7P+LXRY6hzS29ihfET/CgH6g4cOzCGaFJy5Tot+SbmYvWCYmzQAECSbUS2uM2oQPP0A/2DVUm
*/