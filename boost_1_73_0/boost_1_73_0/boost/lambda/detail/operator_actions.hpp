// -- operator_actions.hpp - Boost Lambda Library ----------------------

// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://lambda.cs.utu.fi 

#ifndef BOOST_LAMBDA_OPERATOR_ACTIONS_HPP
#define BOOST_LAMBDA_OPERATOR_ACTIONS_HPP

namespace boost { 
namespace lambda {


// -- artihmetic ----------------------

class plus_action {};
class minus_action {};
class multiply_action {};
class divide_action {};
class remainder_action {};

// -- bitwise  -------------------

class leftshift_action {};
class rightshift_action {};
class xor_action {};


// -- bitwise/logical -------------------

class and_action {};
class or_action {};
class not_action {};

// -- relational -------------------------

class less_action {};
class greater_action {};
class lessorequal_action {};
class greaterorequal_action {};
class equal_action {};
class notequal_action {};

// -- increment/decrement ------------------------------

class increment_action {};
class decrement_action {};

// -- void return ------------------------------

// -- other  ------------------------------

class addressof_action {};
  // class comma_action {}; // defined in actions.hpp
class contentsof_action {};
// class member_pointer_action {}; (defined in member_ptr.hpp)


// -- actioun group templates --------------------

template <class Action> class arithmetic_action;
template <class Action> class bitwise_action;
template <class Action> class logical_action;
template <class Action> class relational_action;
template <class Action> class arithmetic_assignment_action;
template <class Action> class bitwise_assignment_action;
template <class Action> class unary_arithmetic_action;
template <class Action> class pre_increment_decrement_action;
template <class Action> class post_increment_decrement_action;

// ---------------------------------------------------------

  // actions, for which the existence of protect is checked in return type 
  // deduction.

template <class Act> struct is_protectable<arithmetic_action<Act> > {
  BOOST_STATIC_CONSTANT(bool, value = true);
};
template <class Act> struct is_protectable<bitwise_action<Act> > {
  BOOST_STATIC_CONSTANT(bool, value = true);
};
template <class Act> struct is_protectable<logical_action<Act> > {
  BOOST_STATIC_CONSTANT(bool, value = true);
};
template <class Act> struct is_protectable<relational_action<Act> > {
  BOOST_STATIC_CONSTANT(bool, value = true);
};
template <class Act> 
struct is_protectable<arithmetic_assignment_action<Act> > {
  BOOST_STATIC_CONSTANT(bool, value = true);
};
template <class Act> struct is_protectable<bitwise_assignment_action<Act> > {
  BOOST_STATIC_CONSTANT(bool, value = true);
};
template <class Act> struct is_protectable<unary_arithmetic_action<Act> > {
  BOOST_STATIC_CONSTANT(bool, value = true);
};
template <class Act> 
struct is_protectable<pre_increment_decrement_action<Act> > {
  BOOST_STATIC_CONSTANT(bool, value = true);
};
template <class Act> struct 
is_protectable<post_increment_decrement_action<Act> > {
  BOOST_STATIC_CONSTANT(bool, value = true);
};

template <> struct is_protectable<other_action<addressof_action> > {
  BOOST_STATIC_CONSTANT(bool, value = true);
};
template <> struct is_protectable<other_action<contentsof_action> > {
  BOOST_STATIC_CONSTANT(bool, value = true);
};

template<> struct is_protectable<other_action<subscript_action> > {
  BOOST_STATIC_CONSTANT(bool, value = true);
};
template<> struct is_protectable<other_action<assignment_action> > {
  BOOST_STATIC_CONSTANT(bool, value = true);
};

// NOTE: comma action is also protectable, but the specialization is
  // in actions.hpp


} // namespace lambda 
} // namespace boost

#endif








/* operator_actions.hpp
eEZx82BF/wd4iInoCQt/83qCl37IwDdo6seCGBnaWvAWiKtkLm2oEc1oIwlFfNg9aIBBUCbr5WB42j8/qorBEqGMBR3SxhgafM8AoqKZCZNMlIBj9k35jPj/SHWsn9oP459anc50rmlEKc9ALTKe0skl+Rn2LSu1KVIzNcWudgPhXmNzAHEMHsXoYYmtk8u3Z6teRtlGp1M6YFhVTzp/Wn/QKP+0OYofmLVaHVmtysTiFkyHPgWAKfaBphURpflM+1JzyY1b7XvrgHWSIs4pLiLwOdNGZWNZIxZ3uYHwY2Oexhw3OY0sah6Wt3gRf47UFuepFlbK3O0hSe12e1Uc0hulOEc9TyeKmAuVOi6CKXVQXnjF+zQPLG2iVUuWXho9f06WBgIdHhqV1nKqpCFIhHQjk8IUg25BZUhIjO6WK7pFjcSd4+ZgGC5XgnAcVbOhQcOKNtuK6RaEOo0T8CqbjoUORa01aiofBDO2VoycqXQBNtdBRwFDmaLpTuNMEjQ2R/PLNHPSAP2qZsSJZ6VbZrBbNhm/wIWDQuaBo7sUQBwnOdrtvL0Ce2lRNwO6FCuQ4G1jiqzvmQSa/K2meDmdCCKJkafIueYrUYMd7t2tuIHN0hG/6rtf7+JFBLVHJcoeG6vi8P65UDl3LkAh
*/