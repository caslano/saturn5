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
9gvfniBcbDee3cJ2w/NusIGVzTh6Nhb0MXj2emwsY0GlZWW5tO/ZmdJ2uM4We1Ke57zkw/j1oKUIe0KXIboOfYZ7jQd4MhGWh12exN7mnl3i3weWffE/Fj+66PfQP8t9pyCd+dD5HdHZUesclxzYU/oa0Xt8EFw7hIw5aX/eb/In6jRybZNK2wTZOoVzbym0AvQ7+J/7A4utp87xB94B+outyyqrjLycJzKP2GxPfY6RTpUVUynbHThUnn/Xlrch27Ly3F/iKmFjfmT86acZ/6X8OF0B6gSaDTqC+KsXLfGfjl1RldmGy6iOLb6U57v3QD0WpdOvWJ531PmkXO4x14v2QQkSvbXsB3YTN/k0K+5Lg/qHPOuIugeKru5a9zi5T5R8vxHpXYdAPuLmv4zmffhrmf8CPIfAs0z24R9qO3dKeOJhu0el/DSXjTEtzMe9JGxdJW39UaSt1Cu0O/otYh9JWzwBj9ilm9zDVp609vUI3YP+YvDWWtKagw7M67pe0eFe+mLY81eg7+T39+9vlFOz3dnMD+29KHQ66DPYt84SdnlhZw+sm+5D+SUBpA/K8rrrxbDvRtTrmPLTy0tvQso1y+8Tnk62Mkt5s7xLlHR5r5fnabb2CbLRlXfuHc3+mI6fuMdrd4Zbt0OsCxges5+2lucGdKEniaBjsHFjGBsHjlNQlnxi3bvUsOlfBwovNYTZvzRKO1jyjrYB/IGb9icoTy3sGRrfL8CftNUeX6n/o4yr6GD6/41xhbQtnuA9+XgG6nfXj1T6YcbxkIx7yjdvXX7+Bd7cMHHkhxlruZc5lyLXw97GGXE+zjhDmy4vQ+V5ssUGlGXe+AdlOUyv5cdsDT8+ntsKNjxOG8Jf/V7zD7oxLEHlpfD0UNu2G4R3jHC2LZvG5bPh7TsjvH2p15H919UgkaVGOchD26ksgp1LDDs7QTqMswIj2LnkFOzck3Z2w54aHHZtbyfoWXB5resVau8O4K8Nb++KmbdNC2vrZRFsXWuxtWiT4DbbamkEW9cato41dahm+Scj2Lq2NW3dHHZt61jzmXe8NMuet+vC2Xra7BPm7foI9q4Ltbdo9ObtXRHsbepwgnRMn2222+9HsHld69k8KPw9zfztCZeZxzPPDG2T4iHTGMbuoj3KNqlR18/axiJtbXtPwQ7dTDvQj6B2t3do3uoM3qRt9jhyTC1svkrfFj5fQac3XzVp85TjFPDZ8xV1sBx3NHUYeaoveKx5SuRP3pbBeYr+espxR/OZpxyrPnZb54ezNY4gKZ0lesLae3xYe1OvvBloe1MjQ22OgUaweb7H5oYeLX9tBJvnn4LNe5k2t4TfY3cdLjOPl/W115/+cHavnHlTJJtXR7C5PzSPQ1uovasi2Js6xH+nWYeWnR/B1v5TsLUnf+twm+8rTvOzoLy9r1+ojbuCd2UkG8swXXg7b4hg55WGnROabESNwW3U2gh2Xmnk68QgHUrLb4lg65WtYOsE2tMIu87TiUHPgtum/OxQe3cD/95w9r4NPYvpXwtr6/0RbL03NE83afPU2/si2HqvYeskU4dRJj6JYOu9rWBr5msz7NrWSXzGMAV9d9p3tr3+UC9FtHVxxbSpc3AZ1ubxkLfbXHQzvl6bU6vH9rHgt9ueutgOODZdRhqkgteaBqLn5NOgtycNbHHpZdYxljAGve8NCE2TVMjlRk4TlKMI79MR0iNX21DXN1ojg9/8bh02LaiHZam7R48ydIyJkA65p5AOvcx6JzQOum/c3fNcecYvS3KUYnLqc/XTcFNis7+cRRfd92bIe74zyZCZ1Zbk1empGMeADSvleYYe+1zXgrFP/U3a+x2J4dF5kd/cvN8=
*/