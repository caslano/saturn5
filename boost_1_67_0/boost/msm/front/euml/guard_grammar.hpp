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