///////////////////////////////////////////////////////////////////////////////
/// \file proto_typeof.hpp
/// Type registrations so that proto expression templates can be used together
/// with the Boost.Typeof library.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_PROTO_PROTO_TYPEOF_H
#define BOOST_XPRESSIVE_PROTO_PROTO_TYPEOF_H

#include <boost/config.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/deep_copy.hpp>
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::terminal)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::unary_plus)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::negate)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::dereference)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::complement)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::address_of)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::logical_not)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::pre_inc)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::pre_dec)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::post_inc)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::post_dec)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::shift_left)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::shift_right)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::multiplies)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::divides)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::modulus)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::plus)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::minus)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::less)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::greater)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::less_equal)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::greater_equal)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::equal_to)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::not_equal_to)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::logical_or)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::logical_and)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::bitwise_and)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::bitwise_or)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::bitwise_xor)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::comma)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::mem_ptr)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::assign)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::shift_left_assign)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::shift_right_assign)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::multiplies_assign)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::divides_assign)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::modulus_assign)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::plus_assign)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::minus_assign)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::bitwise_and_assign)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::bitwise_or_assign)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::bitwise_xor_assign)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::subscript)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::member)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::if_else_)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::function)

BOOST_TYPEOF_REGISTER_TYPE(boost::proto::exprns_::is_proto_expr)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::exprns_::expr, (typename)(typename)(long))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::exprns_::basic_expr, (typename)(typename)(long))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::utility::literal, (typename)(typename))

BOOST_TYPEOF_REGISTER_TYPE(boost::proto::detail::not_a_generator)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::detail::not_a_grammar)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::detail::not_a_domain)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::domain, 3)

BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::term, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::list1, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::list2, 2)
// can't use PP metaprogramming here because all typeof registrations
// must be on separate lines.
#if BOOST_PROTO_MAX_ARITY >= 3
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::list3, 3)
#endif
#if BOOST_PROTO_MAX_ARITY >= 4
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::list4, 4)
#endif
#if BOOST_PROTO_MAX_ARITY >= 5
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::list5, 5)
#endif
#if BOOST_PROTO_MAX_ARITY >= 6
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::list6, 6)
#endif
#if BOOST_PROTO_MAX_ARITY >= 7
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::list7, 7)
#endif
#if BOOST_PROTO_MAX_ARITY >= 8
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::list8, 8)
#endif
#if BOOST_PROTO_MAX_ARITY >= 9
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::list9, 9)
#endif
#if BOOST_PROTO_MAX_ARITY >= 10
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::list10, 10)
#endif
#if BOOST_PROTO_MAX_ARITY >= 11
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::list11, 11)
#endif
#if BOOST_PROTO_MAX_ARITY >= 12
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::list12, 12)
#endif
#if BOOST_PROTO_MAX_ARITY >= 13
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::list13, 13)
#endif
#if BOOST_PROTO_MAX_ARITY >= 14
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::list14, 14)
#endif
#if BOOST_PROTO_MAX_ARITY >= 15
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::list15, 15)
#endif
#if BOOST_PROTO_MAX_ARITY >= 16
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::list16, 16)
#endif
#if BOOST_PROTO_MAX_ARITY >= 17
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::list17, 17)
#endif
#if BOOST_PROTO_MAX_ARITY >= 18
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::list18, 18)
#endif
#if BOOST_PROTO_MAX_ARITY >= 19
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::list19, 19)
#endif
#if BOOST_PROTO_MAX_ARITY >= 20
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::list20, 20)
#endif

#define BOOST_PROTO_AUTO(Var, Expr) BOOST_AUTO(Var, boost::proto::deep_copy(Expr))
#define BOOST_PROTO_AUTO_TPL(Var, Expr) BOOST_AUTO_TPL(Var, boost::proto::deep_copy(Expr))

#endif

/* proto_typeof.hpp
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
*/