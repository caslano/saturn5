// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_GRAMMAR_H
#define BOOST_MSM_GRAMMAR_H

#include <boost/proto/core.hpp>
#include <boost/msm/common.hpp>


namespace boost { namespace msm
{
// base grammar for all of msm's proto-based grammars
struct basic_grammar : proto::_
{};

// Forward-declare an expression wrapper
template<typename Expr>
struct msm_terminal;

struct msm_domain
    : proto::domain< proto::generator<msm_terminal>, basic_grammar >
{};

template<typename Expr>
struct msm_terminal
    : proto::extends<Expr, msm_terminal<Expr>, msm_domain>
{
    typedef
        proto::extends<Expr, msm_terminal<Expr>, msm_domain>
        base_type;
    // Needs a constructor
    msm_terminal(Expr const &e = Expr())
        : base_type(e)
    {}
};

// grammar forbidding address of for terminals
struct terminal_grammar : proto::not_<proto::address_of<proto::_> >
{};

// Forward-declare an expression wrapper
template<typename Expr>
struct euml_terminal;

struct sm_domain
    : proto::domain< proto::generator<euml_terminal>, terminal_grammar, boost::msm::msm_domain >
{};

struct state_grammar : 
    proto::and_<
        proto::not_<proto::address_of<proto::_> >,
        proto::not_<proto::shift_right<proto::_,proto::_> >,
        proto::not_<proto::shift_left<proto::_,proto::_> >,
        proto::not_<proto::bitwise_and<proto::_,proto::_> >
    >
{};
struct state_domain
    : proto::domain< proto::generator<euml_terminal>, boost::msm::state_grammar,boost::msm::sm_domain >
{};

template<typename Expr>
struct euml_terminal
    : proto::extends<Expr, euml_terminal<Expr>, boost::msm::sm_domain>
{
    typedef
        proto::extends<Expr, euml_terminal<Expr>, boost::msm::sm_domain>
        base_type;
    // Needs a constructor
    euml_terminal(Expr const &e = Expr())
        : base_type(e)
    {}
    // Unhide Proto's overloaded assignment operator
    using base_type::operator=;
};

} } // boost::msm
#endif //BOOST_MSM_GRAMMAR_H


/* msm_grammar.hpp
mNzqkWsbaKwJPGlrdHUss8+fakf2+XM4xnxmzf7Tw3p6a9kLMmvb5XtB5t/hsZKiCr7m6z8rpIFasYIo++eVERp/69VLyBp57CPZGlmoCVRVakelH7NrgR/yFhzLklXL1VRraHUC0nWl85cFRNf18ZE5CRJda0l/0HpyzW8SXaNYmpmICgXmuO7YcTvJXjkMc/PS9hq+GM7vTmZ3zeI9gmO2VDgq0zlre4RG7R045EnuTHnhFXEOV25m2W1lKH5WPQndvTWowcjLIzIM1dxO+maJJuDadJvlEpJilyP9dpWxFkEXOq7Aw0106PGNrz9TNiffX+xlTuKuUVoIY4/PZ9Q9HwBotJVP41U1RZLfWog4HI+WFxNMVnUtYEffs4K6FDAaOcPClAUqVf1byRripk43dcFgAUO3MemiO/aDLXpNicfqFLd0BHUUSpIUhcKxm+D8+EZu7bA2nthCxjHPXbv0eo2Sus4wo0KjWq1KEDyLHX+qVc1w8/nNPG4xvcpv5nJFmSvPcmm1Yjq3JuP5nCqXvzdWq5GJDGuo5mqlubC/KW0eDzWZtVmv7ksRL4+YL9lYUi4+bpbL7ycgmKW1FL6bwCNQFrPfhuIaRNzsxUTNTAcDfSI1/8KpGZVuvc16eTRbbVZjxM/iWbAywcgROf4miooFduRWDwvMezLe+CuJ+CO/IpF1+zI69uEirAc/pvKjgd/vwH+7+Xst
*/