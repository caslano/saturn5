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
j84y0PgjxI8cvjhoiFP6FPoukfww8RqOV5cuKMk5+3G2bLE0WFfoPKYLL4bgauWRxnmaBm/XxJ1S2Ut77F+7XbZEda3pVba12XZQz8WTLPzD5fnbCTZAUsKdb1pqF5hjKTsOJzlOzb6uWtPseyAOYQ5LHw2FTP+TpO7jpB4/9w1QSwMECgAAAAgALWdKUs93k+b9AQAAUQMAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q5MzJVVAUAAbZIJGBVU9tu4jAQfbfEP4yo+lIpm22BVqAILQrZBSkEFsJK+1QZZwJREzuynbb8fScJl/ISOzPH5zJxPIvGCm5wzLxMpoqWNzx+KJ2YMdss4hXbTDZh84DJNp6Bv54snMV00Jb8SeQHYTiJ58uIrX/7T4/DQb32h4M+89wrlee27OyO3cEG9Ttqx2QJMk9jmR8JYJqiKJIxuxVaB6vwfyve6/VhXe12mTmcyg8w+PnYNvFTHLjcIwguBeY5JrA7gsgzlJb0v/F77km0ceM3iJObFn6xM2amsOXlNNVT5LbSSJGEPpZWUe9aAk/yAtvBXQLAXnOBaZWfjXGbKUlYtwWDJ1RRcJm0YiPXvZ8tN/F8NbqveVbLdewOe0/gOAXPckeL0oJGkZW101/4
*/