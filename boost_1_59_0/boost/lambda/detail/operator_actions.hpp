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
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
*/