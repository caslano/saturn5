// Boost Lambda Library  - operator_lambda_func_base.hpp -----------------
//
// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org

// ------------------------------------------------------------

#ifndef BOOST_LAMBDA_OPERATOR_LAMBDA_FUNC_BASE_HPP
#define BOOST_LAMBDA_OPERATOR_LAMBDA_FUNC_BASE_HPP

namespace boost { 
namespace lambda {


// These operators cannot be implemented as apply functions of action 
// templates


// Specialization for comma.
template<class Args>
class lambda_functor_base<other_action<comma_action>, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const {
    return detail::select(boost::tuples::get<0>(args), CALL_ACTUAL_ARGS), 
           detail::select(boost::tuples::get<1>(args), CALL_ACTUAL_ARGS); 
  }


  template<class SigArgs> struct sig { 
  private:
    typedef typename
      detail::deduce_argument_types<Args, SigArgs>::type rets_t;      
  public:
    typedef typename return_type_2_comma< // comma needs special handling
      typename detail::element_or_null<0, rets_t>::type,
      typename detail::element_or_null<1, rets_t>::type
    >::type type;
  };

};  

namespace detail {

// helper traits to make the expression shorter, takes binary action
// bound argument tuple, open argument tuple and gives the return type

template<class Action, class Bound, class Open> class binary_rt {
  private:
    typedef typename
      detail::deduce_argument_types<Bound, Open>::type rets_t;      
  public:
    typedef typename return_type_2_prot<
      Action,  
      typename detail::element_or_null<0, rets_t>::type,
      typename detail::element_or_null<1, rets_t>::type
    >::type type;
};


  // same for unary actions
template<class Action, class Bound, class Open> class unary_rt {
  private:
    typedef typename
      detail::deduce_argument_types<Bound, Open>::type rets_t;      
  public:
    typedef typename return_type_1_prot<
      Action,  
      typename detail::element_or_null<0, rets_t>::type
    >::type type;
};


} // end detail

// Specialization for logical and (to preserve shortcircuiting)
// this could be done with a macro as the others, code used to be different
template<class Args>
class lambda_functor_base<logical_action<and_action>, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const {
    return detail::select(boost::tuples::get<0>(args), CALL_ACTUAL_ARGS) && 
           detail::select(boost::tuples::get<1>(args), CALL_ACTUAL_ARGS); 
  }
  template<class SigArgs> struct sig { 
    typedef typename
      detail::binary_rt<logical_action<and_action>, Args, SigArgs>::type type;
  };      
};  

// Specialization for logical or (to preserve shortcircuiting)
// this could be done with a macro as the others, code used to be different
template<class Args>
class lambda_functor_base<logical_action< or_action>, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const {
    return detail::select(boost::tuples::get<0>(args), CALL_ACTUAL_ARGS) || 
           detail::select(boost::tuples::get<1>(args), CALL_ACTUAL_ARGS); 
  }

  template<class SigArgs> struct sig { 
    typedef typename
      detail::binary_rt<logical_action<or_action>, Args, SigArgs>::type type;
  };      
};  

// Specialization for subscript
template<class Args>
class lambda_functor_base<other_action<subscript_action>, Args> {
public:
  Args args;
public:
  explicit lambda_functor_base(const Args& a) : args(a) {}

  template<class RET, CALL_TEMPLATE_ARGS>
  RET call(CALL_FORMAL_ARGS) const {
    return detail::select(boost::tuples::get<0>(args), CALL_ACTUAL_ARGS) 
           [detail::select(boost::tuples::get<1>(args), CALL_ACTUAL_ARGS)]; 
  }

  template<class SigArgs> struct sig { 
    typedef typename
      detail::binary_rt<other_action<subscript_action>, Args, SigArgs>::type 
        type;
  };      
};  


#define BOOST_LAMBDA_BINARY_ACTION(SYMBOL, ACTION_CLASS)  \
template<class Args>                                                      \
class lambda_functor_base<ACTION_CLASS, Args> {                           \
public:                                                                   \
  Args args;                                                              \
public:                                                                   \
  explicit lambda_functor_base(const Args& a) : args(a) {}                \
                                                                          \
  template<class RET, CALL_TEMPLATE_ARGS>                                 \
  RET call(CALL_FORMAL_ARGS) const {                                      \
    return detail::select(boost::tuples::get<0>(args), CALL_ACTUAL_ARGS)  \
           SYMBOL                                                         \
           detail::select(boost::tuples::get<1>(args), CALL_ACTUAL_ARGS); \
  }                                                                       \
  template<class SigArgs> struct sig {                                    \
    typedef typename                                                      \
      detail::binary_rt<ACTION_CLASS, Args, SigArgs>::type type;          \
  };                                                                      \
};  

#define BOOST_LAMBDA_PREFIX_UNARY_ACTION(SYMBOL, ACTION_CLASS)            \
template<class Args>                                                      \
class lambda_functor_base<ACTION_CLASS, Args> {                           \
public:                                                                   \
  Args args;                                                              \
public:                                                                   \
  explicit lambda_functor_base(const Args& a) : args(a) {}                \
                                                                          \
  template<class RET, CALL_TEMPLATE_ARGS>                                 \
  RET call(CALL_FORMAL_ARGS) const {                                      \
    return SYMBOL                                                         \
           detail::select(boost::tuples::get<0>(args), CALL_ACTUAL_ARGS); \
  }                                                                       \
  template<class SigArgs> struct sig {                                    \
    typedef typename                                                      \
      detail::unary_rt<ACTION_CLASS, Args, SigArgs>::type type;           \
  };                                                                      \
};  

#define BOOST_LAMBDA_POSTFIX_UNARY_ACTION(SYMBOL, ACTION_CLASS)           \
template<class Args>                                                      \
class lambda_functor_base<ACTION_CLASS, Args> {                           \
public:                                                                   \
  Args args;                                                              \
public:                                                                   \
  explicit lambda_functor_base(const Args& a) : args(a) {}                \
                                                                          \
  template<class RET, CALL_TEMPLATE_ARGS>                                 \
  RET call(CALL_FORMAL_ARGS) const {                                      \
    return                                                                \
    detail::select(boost::tuples::get<0>(args), CALL_ACTUAL_ARGS) SYMBOL; \
  }                                                                       \
  template<class SigArgs> struct sig {                                    \
    typedef typename                                                      \
      detail::unary_rt<ACTION_CLASS, Args, SigArgs>::type type;           \
  };                                                                      \
};  

BOOST_LAMBDA_BINARY_ACTION(+,arithmetic_action<plus_action>)
BOOST_LAMBDA_BINARY_ACTION(-,arithmetic_action<minus_action>)
BOOST_LAMBDA_BINARY_ACTION(*,arithmetic_action<multiply_action>)
BOOST_LAMBDA_BINARY_ACTION(/,arithmetic_action<divide_action>)
BOOST_LAMBDA_BINARY_ACTION(%,arithmetic_action<remainder_action>)

BOOST_LAMBDA_BINARY_ACTION(<<,bitwise_action<leftshift_action>)
BOOST_LAMBDA_BINARY_ACTION(>>,bitwise_action<rightshift_action>)
BOOST_LAMBDA_BINARY_ACTION(&,bitwise_action<and_action>)
BOOST_LAMBDA_BINARY_ACTION(|,bitwise_action<or_action>)
BOOST_LAMBDA_BINARY_ACTION(^,bitwise_action<xor_action>)

BOOST_LAMBDA_BINARY_ACTION(<,relational_action<less_action>)
BOOST_LAMBDA_BINARY_ACTION(>,relational_action<greater_action>)
BOOST_LAMBDA_BINARY_ACTION(<=,relational_action<lessorequal_action>)
BOOST_LAMBDA_BINARY_ACTION(>=,relational_action<greaterorequal_action>)
BOOST_LAMBDA_BINARY_ACTION(==,relational_action<equal_action>)
BOOST_LAMBDA_BINARY_ACTION(!=,relational_action<notequal_action>)

BOOST_LAMBDA_BINARY_ACTION(+=,arithmetic_assignment_action<plus_action>)
BOOST_LAMBDA_BINARY_ACTION(-=,arithmetic_assignment_action<minus_action>)
BOOST_LAMBDA_BINARY_ACTION(*=,arithmetic_assignment_action<multiply_action>)
BOOST_LAMBDA_BINARY_ACTION(/=,arithmetic_assignment_action<divide_action>)
BOOST_LAMBDA_BINARY_ACTION(%=,arithmetic_assignment_action<remainder_action>)

BOOST_LAMBDA_BINARY_ACTION(<<=,bitwise_assignment_action<leftshift_action>)
BOOST_LAMBDA_BINARY_ACTION(>>=,bitwise_assignment_action<rightshift_action>)
BOOST_LAMBDA_BINARY_ACTION(&=,bitwise_assignment_action<and_action>)
BOOST_LAMBDA_BINARY_ACTION(|=,bitwise_assignment_action<or_action>)
BOOST_LAMBDA_BINARY_ACTION(^=,bitwise_assignment_action<xor_action>)

BOOST_LAMBDA_BINARY_ACTION(=,other_action< assignment_action>)


BOOST_LAMBDA_PREFIX_UNARY_ACTION(+, unary_arithmetic_action<plus_action>)
BOOST_LAMBDA_PREFIX_UNARY_ACTION(-, unary_arithmetic_action<minus_action>)
BOOST_LAMBDA_PREFIX_UNARY_ACTION(~, bitwise_action<not_action>)
BOOST_LAMBDA_PREFIX_UNARY_ACTION(!, logical_action<not_action>)
BOOST_LAMBDA_PREFIX_UNARY_ACTION(++, pre_increment_decrement_action<increment_action>)
BOOST_LAMBDA_PREFIX_UNARY_ACTION(--, pre_increment_decrement_action<decrement_action>)

BOOST_LAMBDA_PREFIX_UNARY_ACTION(&,other_action<addressof_action>)
BOOST_LAMBDA_PREFIX_UNARY_ACTION(*,other_action<contentsof_action>)

BOOST_LAMBDA_POSTFIX_UNARY_ACTION(++, post_increment_decrement_action<increment_action>)
BOOST_LAMBDA_POSTFIX_UNARY_ACTION(--, post_increment_decrement_action<decrement_action>)


#undef BOOST_LAMBDA_POSTFIX_UNARY_ACTION
#undef BOOST_LAMBDA_PREFIX_UNARY_ACTION
#undef BOOST_LAMBDA_BINARY_ACTION

} // namespace lambda
} // namespace boost

#endif











/* operator_lambda_func_base.hpp
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
*/