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
SBWHtGA6ipqhle11gMDUAd42hJUOjmFy9QTR3UafGTxgTHhWlD7OUnTlJFCWZDP3HHe8AOjyT3+xJM2Z5LHbCOAMApAe/Yz8+rI2iZ6eakAEq85IyUtR7UzNlxLv4J6Li2jZQRDepjao+KCF3Xl9bu1w5F+RihM3jJsnOf7ofIpVSJ7XntqWRv+EY4RcxT05HAMZX+7fTzR2Ux1qK3CI5Jw6hIvPOsYrDD6EgJWPq8+xqiy4eGG72dHK+lUQsvuF5S1YqzZFNu7cUXKZnJhWtCNM9eQeLwtPvv770W05T9XjzecihuxZTVAD/zFYV4LRTJkwY/qTf0f5uuBTJ5gW3u8/PJSwWpIVzsP+BK1LGAE+waH3wND9jvqrM2pyTDqS11Movbb5AuDgXhM/jLNsb7A28ZY/gUEn5iN9yTm7asjFqpk0qIXBih040YOoO0a3ynesfbpgqapbArv0iVn5OIftjrnH3MaSWjz3o0huIC9FP/ojPj15Dv4CKpRrSaEetob5QgU4X0rDnIoffkh630H8lWf5l1GhQcudDr/G/VXGmgsndblH9u5lvg==
*/