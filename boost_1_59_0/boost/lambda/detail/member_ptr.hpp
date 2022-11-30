// Boost Lambda Library -- member_ptr.hpp ---------------------

// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
// Copyright (C) 2000 Gary Powell (gary.powell@sierra.com)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org

// --------------------------------------------------------------------------

#if !defined(BOOST_LAMBDA_MEMBER_PTR_HPP)
#define BOOST_LAMBDA_MEMBER_PTR_HPP

namespace boost { 
namespace lambda {


class member_pointer_action {};


namespace detail {

// the boost type_traits member_pointer traits are not enough, 
// need to know more details.
template<class T>
struct member_pointer {
  typedef typename boost::add_reference<T>::type type;
  typedef detail::unspecified class_type;
  typedef detail::unspecified qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = false);
};

template<class T, class U>
struct member_pointer<T U::*> {
  typedef typename boost::add_reference<T>::type type;
  typedef U class_type;
  typedef U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = true);
  BOOST_STATIC_CONSTANT(bool, is_function_member = false);
};

template<class T, class U>
struct member_pointer<const T U::*> {
  typedef typename boost::add_reference<const T>::type type;
  typedef U class_type;
  typedef const U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = true);
  BOOST_STATIC_CONSTANT(bool, is_function_member = false);
};

template<class T, class U>
struct member_pointer<volatile T U::*> {
  typedef typename boost::add_reference<volatile T>::type type;
  typedef U class_type;
  typedef volatile U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = true);
  BOOST_STATIC_CONSTANT(bool, is_function_member = false);
};

template<class T, class U>
struct member_pointer<const volatile T U::*> {
  typedef typename boost::add_reference<const volatile T>::type type;
  typedef U class_type;
  typedef const volatile U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = true);
  BOOST_STATIC_CONSTANT(bool, is_function_member = false);
};

// -- nonconst member functions --
template<class T, class U>
struct member_pointer<T (U::*)()> {
  typedef T type;
  typedef U class_type;
  typedef U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
template<class T, class U, class A1>
struct member_pointer<T (U::*)(A1)> {
  typedef T type;
  typedef U class_type;
  typedef U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
template<class T, class U, class A1, class A2>
struct member_pointer<T (U::*)(A1, A2)> {
  typedef T type;
  typedef U class_type;
  typedef U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
template<class T, class U, class A1, class A2, class A3>
struct member_pointer<T (U::*)(A1, A2, A3)> {
  typedef T type;
  typedef U class_type;
  typedef U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
template<class T, class U, class A1, class A2, class A3, class A4>
struct member_pointer<T (U::*)(A1, A2, A3, A4)> {
  typedef T type;
  typedef U class_type;
  typedef U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
template<class T, class U, class A1, class A2, class A3, class A4, class A5>
struct member_pointer<T (U::*)(A1, A2, A3, A4, A5)> {
  typedef T type;
  typedef U class_type;
  typedef U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
template<class T, class U, class A1, class A2, class A3, class A4, class A5,
         class A6>
struct member_pointer<T (U::*)(A1, A2, A3, A4, A5, A6)> {
  typedef T type;
  typedef U class_type;
  typedef U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
template<class T, class U, class A1, class A2, class A3, class A4, class A5,
         class A6, class A7>
struct member_pointer<T (U::*)(A1, A2, A3, A4, A5, A6, A7)> {
  typedef T type;
  typedef U class_type;
  typedef U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
template<class T, class U, class A1, class A2, class A3, class A4, class A5,
         class A6, class A7, class A8>
struct member_pointer<T (U::*)(A1, A2, A3, A4, A5, A6, A7, A8)> {
  typedef T type;
  typedef U class_type;
  typedef U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
template<class T, class U, class A1, class A2, class A3, class A4, class A5,
         class A6, class A7, class A8, class A9>
struct member_pointer<T (U::*)(A1, A2, A3, A4, A5, A6, A7, A8, A9)> {
  typedef T type;
  typedef U class_type;
  typedef U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
// -- const member functions --
template<class T, class U>
struct member_pointer<T (U::*)() const> {
  typedef T type;
  typedef U class_type;
  typedef const U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
template<class T, class U, class A1>
struct member_pointer<T (U::*)(A1) const> {
  typedef T type;
  typedef U class_type;
  typedef const U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
template<class T, class U, class A1, class A2>
struct member_pointer<T (U::*)(A1, A2) const> {
  typedef T type;
  typedef U class_type;
  typedef const U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
template<class T, class U, class A1, class A2, class A3>
struct member_pointer<T (U::*)(A1, A2, A3) const> {
  typedef T type;
  typedef U class_type;
  typedef const U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
template<class T, class U, class A1, class A2, class A3, class A4>
struct member_pointer<T (U::*)(A1, A2, A3, A4) const> {
  typedef T type;
  typedef U class_type;
  typedef const U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
template<class T, class U, class A1, class A2, class A3, class A4, class A5>
struct member_pointer<T (U::*)(A1, A2, A3, A4, A5) const> {
  typedef T type;
  typedef U class_type;
  typedef const U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
template<class T, class U, class A1, class A2, class A3, class A4, class A5,
         class A6>
struct member_pointer<T (U::*)(A1, A2, A3, A4, A5, A6) const> {
  typedef T type;
  typedef U class_type;
  typedef const U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
template<class T, class U, class A1, class A2, class A3, class A4, class A5,
         class A6, class A7>
struct member_pointer<T (U::*)(A1, A2, A3, A4, A5, A6, A7) const> {
  typedef T type;
  typedef U class_type;
  typedef const U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
template<class T, class U, class A1, class A2, class A3, class A4, class A5,
         class A6, class A7, class A8>
struct member_pointer<T (U::*)(A1, A2, A3, A4, A5, A6, A7, A8) const> {
  typedef T type;
  typedef U class_type;
  typedef const U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
template<class T, class U, class A1, class A2, class A3, class A4, class A5,
         class A6, class A7, class A8, class A9>
struct member_pointer<T (U::*)(A1, A2, A3, A4, A5, A6, A7, A8, A9) const> {
  typedef T type;
  typedef U class_type;
  typedef const U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
  // -- volatile --
template<class T, class U>
struct member_pointer<T (U::*)() volatile> {
  typedef T type;
  typedef U class_type;
  typedef volatile U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
template<class T, class U, class A1>
struct member_pointer<T (U::*)(A1) volatile> {
  typedef T type;
  typedef U class_type;
  typedef volatile U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
template<class T, class U, class A1, class A2>
struct member_pointer<T (U::*)(A1, A2) volatile> {
  typedef T type;
  typedef U class_type;
  typedef volatile U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
template<class T, class U, class A1, class A2, class A3>
struct member_pointer<T (U::*)(A1, A2, A3) volatile> {
  typedef T type;
  typedef U class_type;
  typedef volatile U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
template<class T, class U, class A1, class A2, class A3, class A4>
struct member_pointer<T (U::*)(A1, A2, A3, A4) volatile> {
  typedef T type;
  typedef U class_type;
  typedef volatile U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
template<class T, class U, class A1, class A2, class A3, class A4, class A5>
struct member_pointer<T (U::*)(A1, A2, A3, A4, A5) volatile> {
  typedef T type;
  typedef U class_type;
  typedef volatile U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
template<class T, class U, class A1, class A2, class A3, class A4, class A5,
         class A6>
struct member_pointer<T (U::*)(A1, A2, A3, A4, A5, A6) volatile> {
  typedef T type;
  typedef U class_type;
  typedef volatile U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
template<class T, class U, class A1, class A2, class A3, class A4, class A5,
         class A6, class A7>
struct member_pointer<T (U::*)(A1, A2, A3, A4, A5, A6, A7) volatile> {
  typedef T type;
  typedef U class_type;
  typedef volatile U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
template<class T, class U, class A1, class A2, class A3, class A4, class A5,
         class A6, class A7, class A8>
struct member_pointer<T (U::*)(A1, A2, A3, A4, A5, A6, A7, A8) volatile> {
  typedef T type;
  typedef U class_type;
  typedef volatile U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
template<class T, class U, class A1, class A2, class A3, class A4, class A5,
         class A6, class A7, class A8, class A9>
struct member_pointer<T (U::*)(A1, A2, A3, A4, A5, A6, A7, A8, A9) volatile> {
  typedef T type;
  typedef U class_type;
  typedef volatile U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
  // -- const volatile
template<class T, class U>
struct member_pointer<T (U::*)() const volatile> {
  typedef T type;
  typedef U class_type;
  typedef const volatile U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
template<class T, class U, class A1>
struct member_pointer<T (U::*)(A1) const volatile> {
  typedef T type;
  typedef U class_type;
  typedef const volatile U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
template<class T, class U, class A1, class A2>
struct member_pointer<T (U::*)(A1, A2) const volatile> {
  typedef T type;
  typedef U class_type;
  typedef const volatile U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
template<class T, class U, class A1, class A2, class A3>
struct member_pointer<T (U::*)(A1, A2, A3) const volatile> {
  typedef T type;
  typedef U class_type;
  typedef const volatile U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
template<class T, class U, class A1, class A2, class A3, class A4>
struct member_pointer<T (U::*)(A1, A2, A3, A4) const volatile> {
  typedef T type;
  typedef U class_type;
  typedef const volatile U qualified_class_type;
};
template<class T, class U, class A1, class A2, class A3, class A4, class A5>
struct member_pointer<T (U::*)(A1, A2, A3, A4, A5) const volatile> {
  typedef T type;
  typedef U class_type;
  typedef const volatile U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
template<class T, class U, class A1, class A2, class A3, class A4, class A5,
         class A6>
struct member_pointer<T (U::*)(A1, A2, A3, A4, A5, A6) const volatile> {
  typedef T type;
  typedef U class_type;
  typedef const volatile U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
template<class T, class U, class A1, class A2, class A3, class A4, class A5,
         class A6, class A7>
struct member_pointer<T (U::*)(A1, A2, A3, A4, A5, A6, A7) const volatile> {
  typedef T type;
  typedef U class_type;
  typedef const volatile U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
template<class T, class U, class A1, class A2, class A3, class A4, class A5,
         class A6, class A7, class A8>
struct member_pointer<T (U::*)(A1, A2, A3, A4, A5, A6, A7, A8) const volatile> {
  typedef T type;
  typedef U class_type;
  typedef const volatile U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};
template<class T, class U, class A1, class A2, class A3, class A4, class A5,
         class A6, class A7, class A8, class A9>
struct member_pointer<T (U::*)(A1, A2, A3, A4, A5, A6, A7, A8, A9) const volatile> {
  typedef T type;
  typedef U class_type;
  typedef const volatile U qualified_class_type;
  BOOST_STATIC_CONSTANT(bool, is_data_member = false);
  BOOST_STATIC_CONSTANT(bool, is_function_member = true);
};

} // detail

namespace detail {

  // this class holds a pointer to a member function and the object.
  // when called, it just calls the member function with the parameters 
  // provided

  // It would have been possible to use existing lambda_functors to represent
  // a bound member function like this, but to have a separate template is 
  // safer, since now this functor doesn't mix and match with lambda_functors
  // only thing you can do with this is to call it

  // note that previously instantiated classes 
  // (other_action<member_pointer_action> and member_pointer_action_helper
  // guarantee, that A and B are 
  // such types, that for objects a and b of corresponding types, a->*b leads 
  // to the builtin ->* to be called. So types that would end in a  call to 
  // a user defined ->* do not create a member_pointer_caller object.

template<class RET, class A, class B>
class member_pointer_caller {
  A a; B b;

public:
  member_pointer_caller(const A& aa, const B& bb) : a(aa), b(bb) {}

  RET operator()() const { return (a->*b)(); } 

  template<class A1>
  RET operator()(const A1& a1) const { return (a->*b)(a1); } 

  template<class A1, class A2>
  RET operator()(const A1& a1, const A2& a2) const { return (a->*b)(a1, a2); } 

  template<class A1, class A2, class A3>
  RET operator()(const A1& a1, const A2& a2, const A3& a3) const { 
    return (a->*b)(a1, a2, a3); 
  } 

  template<class A1, class A2, class A3, class A4>
  RET operator()(const A1& a1, const A2& a2, const A3& a3, 
                 const A4& a4) const { 
    return (a->*b)(a1, a2, a3, a4); 
  } 

  template<class A1, class A2, class A3, class A4, class A5>
  RET operator()(const A1& a1, const A2& a2, const A3& a3, const A4& a4, 
                 const A5& a5) const { 
    return (a->*b)(a1, a2, a3, a4, a5); 
  } 

  template<class A1, class A2, class A3, class A4, class A5, class A6>
  RET operator()(const A1& a1, const A2& a2, const A3& a3, const A4& a4, 
                 const A5& a5, const A6& a6) const { 
    return (a->*b)(a1, a2, a3, a4, a5, a6); 
  } 

  template<class A1, class A2, class A3, class A4, class A5, class A6, 
           class A7>
  RET operator()(const A1& a1, const A2& a2, const A3& a3, const A4& a4, 
                 const A5& a5, const A6& a6, const A7& a7) const { 
    return (a->*b)(a1, a2, a3, a4, a5, a6, a7); 
  } 

  template<class A1, class A2, class A3, class A4, class A5, class A6, 
           class A7, class A8>
  RET operator()(const A1& a1, const A2& a2, const A3& a3, const A4& a4, 
                 const A5& a5, const A6& a6, const A7& a7,
                 const A8& a8) const { 
    return (a->*b)(a1, a2, a3, a4, a5, a6, a7, a8); 
  } 

  template<class A1, class A2, class A3, class A4, class A5, class A6, 
           class A7, class A8, class A9>
  RET operator()(const A1& a1, const A2& a2, const A3& a3, const A4& a4, 
                 const A5& a5, const A6& a6, const A7& a7,
                 const A8& a8, const A9& a9) const { 
    return (a->*b)(a1, a2, a3, a4, a5, a6, a7, a8, a9); 
  } 

};

// helper templates for return type deduction and action classes
// different cases for data member, function member, neither

// true-true case
template <bool Is_data_member, bool Is_function_member>
struct member_pointer_action_helper;
  // cannot be both, no body provided

  // data member case
  // this means, that B is a data member and A is a pointer type,
  // so either built-in ->* should be called, or there is an error
template <>
struct member_pointer_action_helper<true, false> {
public:

  template<class RET, class A, class B>
  static RET apply(A& a, B& b) { 
    return a->*b; 
  }

  template<class A, class B>
  struct return_type {
  private:
    typedef typename detail::remove_reference_and_cv<B>::type plainB;

    typedef typename detail::member_pointer<plainB>::type type0;
    // we remove the reference now, as we may have to add cv:s 
    typedef typename boost::remove_reference<type0>::type type1;

    // A is a reference to pointer
    // remove the top level cv qualifiers and reference
    typedef typename 
      detail::remove_reference_and_cv<A>::type non_ref_A;

    // A is a pointer type, so take the type pointed to
    typedef typename ::boost::remove_pointer<non_ref_A>::type non_pointer_A; 

  public:
    // For non-reference types, we must add const and/or volatile if
    // the pointer type has these qualifiers
    // If the member is a reference, these do not have any effect
    //   (cv T == T if T is a reference type)
    typedef typename detail::IF<
      ::boost::is_const<non_pointer_A>::value, 
      typename ::boost::add_const<type1>::type,
      type1
    >::RET type2;
    typedef typename detail::IF<
      ::boost::is_volatile<non_pointer_A>::value, 
      typename ::boost::add_volatile<type2>::type,
      type2
    >::RET type3;
    // add reference back
    typedef typename ::boost::add_reference<type3>::type type;
  };
};

  // neither case
template <>
struct member_pointer_action_helper<false, false> {
public:
  template<class RET, class A, class B>
  static RET apply(A& a, B& b) { 
// not a built in member pointer operator, just call ->*
    return a->*b; 
  }
  // an overloaded member pointer operators, user should have specified
  // the return type
  // At this point we know that there is no matching specialization for
  // return_type_2, so try return_type_2_plain
  template<class A, class B>
  struct return_type {

    typedef typename plain_return_type_2<
      other_action<member_pointer_action>, A, B
    >::type type;
  };
  
};


// member pointer function case
// This is a built in ->* call for a member function, 
// the only thing that you can do with that, is to give it some arguments
// note, it is guaranteed that A is a pointer type, and thus it cannot
// be a call to overloaded ->*
template <>
struct member_pointer_action_helper<false, true> {
  public:

  template<class RET, class A, class B>
  static RET apply(A& a, B& b) { 
    typedef typename ::boost::remove_cv<B>::type plainB;
    typedef typename detail::member_pointer<plainB>::type ret_t; 
    typedef typename ::boost::remove_cv<A>::type plainA;

    // we always strip cv:s to 
    // make the two routes (calling and type deduction)
    // to give the same results (and the const does not make any functional
    // difference)
    return detail::member_pointer_caller<ret_t, plainA, plainB>(a, b); 
  }

  template<class A, class B>
  struct return_type {
    typedef typename detail::remove_reference_and_cv<B>::type plainB;
    typedef typename detail::member_pointer<plainB>::type ret_t; 
    typedef typename detail::remove_reference_and_cv<A>::type plainA; 

    typedef detail::member_pointer_caller<ret_t, plainA, plainB> type; 
  };
};

} // detail

template<> class other_action<member_pointer_action>  {
public:
  template<class RET, class A, class B>
  static RET apply(A& a, B& b) {
    typedef typename 
      ::boost::remove_cv<B>::type plainB;

    return detail::member_pointer_action_helper<
        boost::is_pointer<A>::value && 
          detail::member_pointer<plainB>::is_data_member,
        boost::is_pointer<A>::value && 
          detail::member_pointer<plainB>::is_function_member
      >::template apply<RET>(a, b); 
    }
};

  // return type deduction --

  // If the right argument is a pointer to data member, 
  // and the left argument is of compatible pointer to class type
  // return type is a reference to the data member type

  // if right argument is a pointer to a member function, and the left 
  // argument is of a compatible type, the return type is a 
  // member_pointer_caller (see above)

  // Otherwise, return type deduction fails. There is either an error, 
  // or the user is trying to call an overloaded ->*
  // In such a case either ret<> must be used, or a return_type_2 user 
  // defined specialization must be provided


template<class A, class B>
struct return_type_2<other_action<member_pointer_action>, A, B> {
private:
  typedef typename 
    detail::remove_reference_and_cv<B>::type plainB;
public:
  typedef typename 
    detail::member_pointer_action_helper<
      detail::member_pointer<plainB>::is_data_member,
      detail::member_pointer<plainB>::is_function_member
    >::template return_type<A, B>::type type; 
};

  // this is the way the generic lambda_functor_base functions instantiate
  // return type deduction. We turn it into return_type_2, so that the 
  // user can provide specializations on that level.
template<class Args>
struct return_type_N<other_action<member_pointer_action>, Args> {
  typedef typename boost::tuples::element<0, Args>::type A;
  typedef typename boost::tuples::element<1, Args>::type B;
  typedef typename 
    return_type_2<other_action<member_pointer_action>, 
                  typename boost::remove_reference<A>::type, 
                  typename boost::remove_reference<B>::type
                 >::type type;
};


template<class Arg1, class Arg2>
inline const
lambda_functor<
  lambda_functor_base<
    action<2, other_action<member_pointer_action> >,
    tuple<lambda_functor<Arg1>, typename const_copy_argument<Arg2>::type>
  >
>
operator->*(const lambda_functor<Arg1>& a1, const Arg2& a2)
{
  return 
      lambda_functor_base<
        action<2, other_action<member_pointer_action> >,
        tuple<lambda_functor<Arg1>, typename const_copy_argument<Arg2>::type>
      >
      (tuple<lambda_functor<Arg1>, 
             typename const_copy_argument<Arg2>::type>(a1, a2));
}

template<class Arg1, class Arg2>
inline const
lambda_functor<
  lambda_functor_base<
    action<2, other_action<member_pointer_action> >,
    tuple<lambda_functor<Arg1>, lambda_functor<Arg2> >
  >
>
operator->*(const lambda_functor<Arg1>& a1, const lambda_functor<Arg2>& a2)
{
  return 
      lambda_functor_base<
        action<2, other_action<member_pointer_action> >,
        tuple<lambda_functor<Arg1>, lambda_functor<Arg2> >
      >
    (tuple<lambda_functor<Arg1>, lambda_functor<Arg2> >(a1, a2));
}

template<class Arg1, class Arg2>
inline const
lambda_functor<
  lambda_functor_base<
    action<2, other_action<member_pointer_action> >,
    tuple<typename const_copy_argument<Arg1>::type, lambda_functor<Arg2> >
  >
>
operator->*(const Arg1& a1, const lambda_functor<Arg2>& a2)
{
  return 
      lambda_functor_base<
        action<2, other_action<member_pointer_action> >,
        tuple<typename const_copy_argument<Arg1>::type, lambda_functor<Arg2> >
      >
      (tuple<typename const_copy_argument<Arg1>::type, 
             lambda_functor<Arg2> >(a1, a2));
}


} // namespace lambda 
} // namespace boost


#endif







/* member_ptr.hpp
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
*/