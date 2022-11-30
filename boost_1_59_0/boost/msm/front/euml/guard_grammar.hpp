// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_FRONT_EUML_GUARD_GRAMMAR_H
#define BOOST_MSM_FRONT_EUML_GUARD_GRAMMAR_H

#include <boost/msm/front/euml/common.hpp>
#include <boost/msm/front/euml/operator.hpp>
#include <boost/msm/front/euml/state_grammar.hpp>

namespace boost { namespace msm { namespace front { namespace euml
{
struct BuildGuards;
struct BuildActions;

struct BuildGuardsCases
{
    // The primary template matches nothing:
    template<typename Tag>
    struct case_
        : proto::not_<proto::_>
    {};
};
template<>
struct BuildGuardsCases::case_<proto::tag::logical_or>
    : proto::when<
                    proto::logical_or<BuildGuards,BuildGuards >,
                    Or_<BuildGuards(proto::_left),BuildGuards(proto::_right)>()
                >
{};
template<>
struct BuildGuardsCases::case_<proto::tag::logical_and>
    : proto::when<
                    proto::logical_and<BuildGuards,BuildGuards >,
                    And_<BuildGuards(proto::_left),BuildGuards(proto::_right)>()
                >
{};
template<>
struct BuildGuardsCases::case_<proto::tag::logical_not>
    : proto::when<
                    proto::logical_not<BuildGuards >,
                    Not_<BuildGuards(proto::_child)>()
                >
{};
template<>
struct BuildGuardsCases::case_<proto::tag::less>
    : proto::when<
                    proto::less<BuildGuards, BuildGuards >,
                    Less_<BuildGuards(proto::_left),BuildGuards(proto::_right)>()
                >
{};
template<>
struct BuildGuardsCases::case_<proto::tag::less_equal>
    : proto::when<
                    proto::less_equal<BuildGuards, BuildGuards >,
                    LessEqual_<BuildGuards(proto::_left),BuildGuards(proto::_right)>()
                >
{};
template<>
struct BuildGuardsCases::case_<proto::tag::greater>
    : proto::when<
                    proto::greater<BuildGuards, BuildGuards >,
                    Greater_<BuildGuards(proto::_left),BuildGuards(proto::_right)>()
                >
{};
template<>
struct BuildGuardsCases::case_<proto::tag::greater_equal>
    : proto::when<
                    proto::greater_equal<BuildGuards, BuildGuards >,
                    GreaterEqual_<BuildGuards(proto::_left),BuildGuards(proto::_right)>()
                >
{};
template<>
struct BuildGuardsCases::case_<proto::tag::equal_to>
    : proto::when<
                        proto::equal_to<BuildGuards, BuildGuards >,
                        EqualTo_<BuildGuards(proto::_left),BuildGuards(proto::_right)>()
                >
{};
template<>
struct BuildGuardsCases::case_<proto::tag::not_equal_to>
    : proto::when<
                        proto::not_equal_to<BuildGuards, BuildGuards >,
                        NotEqualTo_<BuildGuards(proto::_left),BuildGuards(proto::_right)>()
                >
{};
template<>
struct BuildGuardsCases::case_<proto::tag::pre_inc>
    : proto::when<
                    proto::pre_inc<BuildGuards >,
                    Pre_inc_<BuildGuards(proto::_child)>()
                >
{};
template<>
struct BuildGuardsCases::case_<proto::tag::dereference>
    : proto::when<
                    proto::dereference<BuildGuards >,
                    Deref_<BuildGuards(proto::_child)>()
                >
{};
template<>
struct BuildGuardsCases::case_<proto::tag::pre_dec>
    : proto::when<
                    proto::pre_dec<BuildGuards >,
                    Pre_dec_<BuildGuards(proto::_child)>()
                >
{};
template<>
struct BuildGuardsCases::case_<proto::tag::post_inc>
    : proto::when<
                    proto::post_inc<BuildGuards >,
                    Post_inc_<BuildGuards(proto::_child)>()
                >
{};
template<>
struct BuildGuardsCases::case_<proto::tag::post_dec>
    : proto::when<
                    proto::post_dec<BuildGuards >,
                    Post_dec_<BuildGuards(proto::_child)>()
                >
{};
template<>
struct BuildGuardsCases::case_<proto::tag::plus>
    : proto::when<
                    proto::plus<BuildGuards,BuildGuards >,
                    Plus_<BuildGuards(proto::_left),BuildGuards(proto::_right)>()
                >
{};
template<>
struct BuildGuardsCases::case_<proto::tag::minus>
    : proto::when<
                    proto::minus<BuildGuards,BuildGuards >,
                    Minus_<BuildGuards(proto::_left),BuildGuards(proto::_right)>()
                >
{};
template<>
struct BuildGuardsCases::case_<proto::tag::multiplies>
    : proto::when<
                    proto::multiplies<BuildGuards,BuildGuards >,
                    Multiplies_<BuildGuards(proto::_left),BuildGuards(proto::_right)>()
                >
{};
template<>
struct BuildGuardsCases::case_<proto::tag::divides>
    : proto::when<
                    proto::divides<BuildGuards,BuildGuards >,
                    Divides_<BuildGuards(proto::_left),BuildGuards(proto::_right)>()
                >
{};
template<>
struct BuildGuardsCases::case_<proto::tag::modulus>
    : proto::when<
                    proto::modulus<BuildGuards,BuildGuards >,
                    Modulus_<BuildGuards(proto::_left),BuildGuards(proto::_right)>()
                >
{};
template<>
struct BuildGuardsCases::case_<proto::tag::bitwise_and>
    : proto::when<
                    proto::bitwise_and<BuildGuards,BuildGuards >,
                    Bitwise_And_<BuildGuards(proto::_left),BuildGuards(proto::_right)>()
                >
{};
template<>
struct BuildGuardsCases::case_<proto::tag::bitwise_or>
    : proto::when<
                    proto::bitwise_or<BuildGuards,BuildGuards >,
                    Bitwise_Or_<BuildGuards(proto::_left),BuildGuards(proto::_right)>()
                >
{};
template<>
struct BuildGuardsCases::case_<proto::tag::subscript>
    : proto::when<
                    proto::subscript<BuildGuards,BuildGuards >,
                    Subscript_<BuildGuards(proto::_left),BuildGuards(proto::_right)>()
                >
{};
template<>
struct BuildGuardsCases::case_<proto::tag::plus_assign>
    : proto::when<
                    proto::plus_assign<BuildGuards,BuildGuards >,
                    Plus_Assign_<BuildGuards(proto::_left),BuildGuards(proto::_right)>()
                >
{};
template<>
struct BuildGuardsCases::case_<proto::tag::minus_assign>
    : proto::when<
                    proto::minus_assign<BuildGuards,BuildGuards >,
                    Minus_Assign_<BuildGuards(proto::_left),BuildGuards(proto::_right)>()
                >
{};
template<>
struct BuildGuardsCases::case_<proto::tag::multiplies_assign>
    : proto::when<
                    proto::multiplies_assign<BuildGuards,BuildGuards >,
                    Multiplies_Assign_<BuildGuards(proto::_left),BuildGuards(proto::_right)>()
                >
{};
template<>
struct BuildGuardsCases::case_<proto::tag::divides_assign>
    : proto::when<
                    proto::divides_assign<BuildGuards,BuildGuards >,
                    Divides_Assign_<BuildGuards(proto::_left),BuildGuards(proto::_right)>()
                >
{};
template<>
struct BuildGuardsCases::case_<proto::tag::modulus_assign>
    : proto::when<
                    proto::modulus_assign<BuildGuards,BuildGuards >,
                    Modulus_Assign_<BuildGuards(proto::_left),BuildGuards(proto::_right)>()
                >
{};
template<>
struct BuildGuardsCases::case_<proto::tag::shift_left_assign>
    : proto::when<
                    proto::shift_left_assign<BuildGuards,BuildGuards >,
                    ShiftLeft_Assign_<BuildGuards(proto::_left),BuildGuards(proto::_right)>()
                >
{};
template<>
struct BuildGuardsCases::case_<proto::tag::shift_right_assign>
    : proto::when<
                    proto::shift_right_assign<BuildGuards,BuildGuards >,
                    ShiftRight_Assign_<BuildGuards(proto::_left),BuildGuards(proto::_right)>()
                >
{};
template<>
struct BuildGuardsCases::case_<proto::tag::shift_left>
    : proto::when<
                    proto::shift_left<BuildGuards,BuildGuards >,
                    ShiftLeft_<BuildGuards(proto::_left),BuildGuards(proto::_right)>()
                >
{};
template<>
struct BuildGuardsCases::case_<proto::tag::shift_right>
    : proto::when<
                    proto::shift_right<BuildGuards,BuildGuards >,
                    ShiftRight_<BuildGuards(proto::_left),BuildGuards(proto::_right)>()
                >
{};
template<>
struct BuildGuardsCases::case_<proto::tag::assign>
    : proto::when<
                    proto::assign<BuildGuards,BuildGuards >,
                    Assign_<BuildGuards(proto::_left),BuildGuards(proto::_right)>()
                >
{};
template<>
struct BuildGuardsCases::case_<proto::tag::bitwise_xor>
    : proto::when<
                    proto::bitwise_xor<BuildGuards,BuildGuards >,
                    Bitwise_Xor_<BuildGuards(proto::_left),BuildGuards(proto::_right)>()
                >
{};
template<>
struct BuildGuardsCases::case_<proto::tag::negate>
    : proto::when<
                    proto::negate<BuildGuards >,
                    Unary_Minus_<BuildGuards(proto::_child)>()
                >
{};

template<>
struct BuildGuardsCases::case_<proto::tag::function>
    : proto::or_<
            proto::when<
                    proto::function<proto::terminal<if_tag>,BuildGuards,BuildGuards,BuildGuards >,
                    If_Else_<BuildGuards(proto::_child_c<1>),
                             BuildGuards(proto::_child_c<2>),
                             BuildGuards(proto::_child_c<3>) >()
                    >,
            proto::when<
                    proto::function<proto::terminal<proto::_> >,
                    get_fct<proto::_child_c<0> >()
                    >,
            proto::when<
                    proto::function<proto::terminal<proto::_>,BuildActions >,
                    get_fct<proto::_child_c<0>,BuildActions(proto::_child_c<1>) >()
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
                    proto::function<proto::terminal<proto::_>,BuildActions,BuildActions,BuildActions,BuildActions,BuildActions  >,
                    get_fct<proto::_child_c<0>
                            ,BuildActions(proto::_child_c<1>),BuildActions(proto::_child_c<2>)
                            ,BuildActions(proto::_child_c<3>),BuildActions(proto::_child_c<4>),BuildActions(proto::_child_c<5>) >()
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
{};

template<>
struct BuildGuardsCases::case_<proto::tag::terminal>
    : proto::or_<
        proto::when <
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

struct BuildGuards
    : proto::switch_<BuildGuardsCases>
{};

}}}}

#endif //BOOST_MSM_FRONT_EUML_GUARD_GRAMMAR_H

/* guard_grammar.hpp
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
*/