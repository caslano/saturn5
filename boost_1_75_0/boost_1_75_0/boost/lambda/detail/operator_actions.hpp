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
39C4IrWqi9vW0ibi7HFFrUsMIpGk/w2FeictNt5fUTgAfetnoBUywdpXWleUkWnLp1t6KXBkxFPF/CWB0pLk9X4oylMSJvugdXUaRglvjw5B78DiQOBb49o7YKSA2QyqUegp4NdcJcAOkVnCY3xXbF/FUXlq0kBF86F78kPyY4/Y0D+W5Quoj/Dt5dJgH3KXbxCaFqvnRxkQKxeS1upraFilHkL1NxJ5oPGAmA3sfMo68YMOA4F7pwvm0UjyrE35MmSHnAw2wEUTLM2OMHxCMczK28FDBIrqfp7YFGo+x9DdQ9Vuc1yPH4DbPSJXKUKhUaOHBTLElTiIUKtzrmMA21XLFThGpvamh5N1q+cVSga0CQaPPwA4YXo7LpGTuxK7DdGhhibNbyGHoAlnWAH6V3VoQz/q2yZOAFYP45LSQLlQPOrlVf4Eivbv0LaglsIl+b/745n+E9p87wT4/p717D7Zutn9S9m4gRbKftI+bcGmSb/an+NpV7y5NpqYL+tJVWOfvxv1TFSvJjZ9IX6n1J9eX6b5tyzNwPnzk6H1+qwraQUf98jk12V3p1g1IhXc1FIndXOz9R/S6GWzwhHHxDiqj2Zs9BuoqSnLuoM016pQqyJaAXBXwMVUlliSmIDPzFn/38qPF7Bz3GZVbupEmzZ72qXGwVlJTGFbzfix8nLFpytXP+/JC56sBsZ6k9lxEEyjfv1bjBfL4AUH
*/