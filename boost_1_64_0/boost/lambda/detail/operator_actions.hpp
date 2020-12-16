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
0c6pnIeYDtwF7An8ETCDdsoE/opnPnSCkjOAqcAsYB/gmbRXb+AlwHOAzwMHAH8IzAHWA3OBpyNcX+J8q8GufYHDgN8Gng/8LjAPuAZ4AfAl4HCgg3BfBIwDuvcjgBcDLwOO0GcQ832V7+bVnnnWI3k2whjgbOA45ofxwHd5JsMnvP8tz2YYBj1fBhYC3fuv8H4V0JXfBLwc+CrwCoajPtDWsr8la7tB2xmOq5lPi4A+4CTOc54MrKH7EmCxq59nMLzv3jN8U4AdobwMeBVwOrAUeBNwBnAGsBY4E/gs77cCbwYepVxnhGsW8CzgbGB/YAXQR/frgFXAPPDbz3Iwz3EIPsNhP4jnNvCshtBzGg676Gua37bIcw7DUlAK57IdxnXZ1aHnK+SAAmcqxHJ+2jzPnDSek+A9I0GfjTB8onEWgv0cBJ57AL4w5xwUgWZsazrToBFzwZJWYU4YaPKqtnlhLf39h8//c7//+92z/4rLZ05pjfP/eqmE5PfdcT9MOG7n7gs2u6wUX0RcL+aUVSp5/gGer5V9/Uv9fjnRTT+XOQQPGfv5+3km3G84T/UwaFNftxJonkPw5TGTikcXFjUducexxd9nyF4SVdW478l3j3kicwB1U7y6E7RU5dje5ajbPIsMQaz6mn8ax/O6A9cJz/moz+Mt72E2HXP8VKF1fCg8F6k+kLCMM1KHue5x6qwy21wEK6//SwDr/AHymmtJB8PZ+v5FXvPbJtfgcx/N593nZ+s9NWqSTDrxflaBd343vVKZXmnm2ktte++5arSnd78S2oj7ldBNbBG8XwnjLPsoP8/2cWDwXq/pXMTawLn+H4G6ZiL/PW/Pe8WVVRXW/EdbbRG5n6sa7k262b6PCfU7xnyY2Tif0zK/xcrLdf/M84nfl2/T1vxlyk6VQVAxnZbtIbKn8R6jBnKfodN6CQxc1CN8WsdHkdZcZ8vvxxJPfiemG+PjptMU8R/fBZlOgXlGWdwA7D3O2X8X9HPw7AW/N52wHZiRPn4Eovl98X3h36NG4O9We9pQp0MdUh6go3mcP/sF9/ltqgwhDOwrvpw2egxU0b2JVqe31F4SVrFDjfiBPjXtEKgrj9EOlxprRo5CtgH8Xjtw2yxvXtXl+hORGW2zAfU5Oh/c2r2JHoXg8pMs8268Pme8DjJeoxgvTifX9nFvJ/VTKn9zaLywqVBusX/atApUG5b42eIDPdHtq2QLt1lfFMTbw+kLG04EMsow+k4xjAFbHrGEcZXbXtvDWIwWWrZBitaWJacYzoAtazvaw+m3h7NFYfSfYhgDtszrFBrGP4K3JkwY0SurkCkhUYaz5hTDOcJzHsBEUGeuwfPBlrWWcM6YVj3Y2o8y2oVtIpdkCzN02vos1raLvGbbBd/te1qQ1xynnTJztnFuwPfk+QUqnufxdFPkaZ6HJ98ZbHO0egD3i3xnvSflAuPsh9io62ijTbP0R3SbhniynyNh6iZ8DCvrwjclPAiXp607xLQMjAvLGHV/t3MRmpbYeCaqc3pFlmPl58gc2WnW9CKf/tb67Yzo91g1zszVY5bwC27Tgtqw+sTQ+DXABln2+BXPhHHNfUHC7nkTZRyzTiGOkt4MgyWOel/ZhK6hcfwV4phviWOl207AajdNm43946bPCVcuXR0FIt/VFn/qZrmUPj9qTGu5JK9+dyFv+LOYwX/y9ZQuK7FwkzB5+/n021P3HqUNpTiwXlvjtmM2G55MO7bF+44k0vb5Ja0Qf3knoR9m3b0/yR5Pvy2eLW0HWxBH/38wjsP5IWYoFQ1h+1Rji2NVBdun8OXgCZFLtsUZOqNvn8hrtE/w3V4GTF5+8+E81sDYgzzvcEo=
*/