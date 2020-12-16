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
cllptnelLp2NrTTtXhjug71lUSnJ+qQoDxXdl/Eu2N4F809fthzTSaEU6Cuzry7eX2e+vprSvKtsVfB50Ji8oa1oxLVczheSgrW1Nd81ObkMPZjCbqsWfbs629ZEEt5MaG/v5itQY/leN4T0O/PveG+fHtIWzDpAYkhb9Gl39jyXfBoqY3Xdh9LdxGZ13XdMx1swK3u/MQ13jCUV7c0nzfqVy8OCyquTfkwewM4F6FaidfXASd5yniwlbaj/Qf4sOOzTHjymYUs+HMb9IWOafzHRqgg8lsc8MswP5R9q59TSsAwCWoSLPm/F8e+wUk7S2Rra+7CZvFZpNgZvutzId3k5rxYWl0L6m2267jGvjoT0t/h0+iShfW/l6fj+bsy+cB0X+39IsBbQePxIw8fm4NsY7XROvd3mYYtY5Onv8DSY9N3geb0z8KqyRkV73rtMnv169NFD3rttXquKJLv/gsIH8XnvifLo8hro3mvzej1uHgOfK+/zbQmUvA/vd+1ZWqgyNvYfcOlVkbTFouf3QZuetZXSSzaX8fuQy78P+sfkkw/bdJqvcswMNB+xeebdL6R/1KQ7ycXz+phLp007XegbxuvjNo8+CO/nJ9wca5PFJZb+w4tR+kkz99ie+iObjlnry/7YptHK4rx/YtOn5/9PebqREXzez0yel+44v5+HuinLp//CpLs+oK2XvsqXkG7uQLh7EQ+k/cSnEcxRSP+ETzd+QpRD6b9GeqG0B37JUlP+NVfHfrjYMoQn9A3p30T5RaiLCIBsBOFKCrXcliPNL3hepecpndr5daR7p2zL5w++PR4tG00yeT9AngkVSH6yHreCeNG9gW4MuzuPoquCaetfkYYVHm4RF2yO6TdBXdQWdA3bZFe1o0x6K6P7uAzJ31AlBPaguZXFN6c8Gj/T7xva9NddgdKZs5XJ9jyvfTXKX13zTWZ5X7o65ZEPs8uEf7fNe9o1KG8fOB1Gf/drmTJ7jPctkWdsZSgP9ng+08RSXjaf39fzF1YO4xpsqFg9r74hlRldl1dPG1wZn/f6G1FegB9A9z3va9+E8mYhOlDG01/+plTGul7TAyGr99zNKC/ybvbf4/K3pDwoG5cftrV6nmhuYXSyt6H0CHLAf6s9TXnoJoPZAk8/Zn/pXf4URgel2Fx44r3HcqZqPkceiHTSb5iMECPia3NcZ6izqmrSBLjsKxdab4Zgd/tEXva4rNq0GXQtjAOcDwUdeD894t10isChpTiDBz3HW/iYgxHeeN/Lvq27RBAioC0afE2eD76RrVXVFFWVIO6CceqxE4UU97t7eEO2DC7ibUg5fUbOdt1QykoF3HDECt6JDW+iYMLMp/CHUR+hqB7IlATT7Zx/yz/tbRhRNvL1zDucSHUmMlcHVfiodYo8OkZzWie9oeFFr5/eZyfCJO6FSspSS8n4kBmmMWXmnEZ48hPhbe7VE2zjvmzBpVP/DEj6kI9/vxP5kl/563GbiiqViepiKOApL4ZzzO2PRcQLPLSus77q/jWmMRS0cHZymMbzTt/L+aWpyKHrxnxRYnVlc420civLFrOdvljQx38toitEjWFWXZILmWg1+kIn0FSPeMacfsfV+9tJvWWmVdlnFat3Z4dcxAzdurfp+sYEwzWRrS6TqFpLSOEJyV3W+fltkV2yf9P4Rtz+Pk/7NCltv7GzA1WF9pkxmtwkRpz8xiQ2oEzyQrd5CDRhnMINrYuubWHTWIzPJ3I+J7qsSAeVUTzeKARf8DV5elRvLTDkedHUtZA7W9vWqw5L88QZmDDYGR7OBTONau8nENVdDbrRaUmWhVuPpkNx19Z9wtuzTsZdp3mV1m0iFkExOlRG768=
*/