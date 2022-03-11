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