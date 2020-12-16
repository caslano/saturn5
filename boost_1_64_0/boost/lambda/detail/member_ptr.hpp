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
davbQYdBx0BqQchaVa5TDb9GdQPCXgVcBJqxsHld6vblcSe9NjV2ZPP603yQeU6Wd61p0jbbGlPb+tLo1pX63o3F2tLmdaX7EI9joMzH41Q+qAy0CLQJtA/UCMpagWegMtAdoGWgTaA9oKOg9CfwHFQGWgjaCKoHHQbFroQ8aPjKtrWqbb+2X9uv7df2a/udyk/OVf8Prv+/zT+5Uq7dLQBaYe+/xe7ef5w/eQe7Ab+NaZo38inwHXct/ivyLWDMRF+xb9SY4ib/lTLOlfFjuoT1WwBl+d1eBXhlgy3r9wDyi+7fdZfvDKXlVdbvJl7d5IVu6zwf8nPe71nyfnsFno9ODvShN8nz1eKWxvBvFLdt5HOE765XXbcO5HNUrHZrZ5kzZPO3QvWGbDr9XSDP3475G55c6HRUa5049X0nQfTDBE36hWeKSnPDQberxc8xCitfyGuEhW4pdGOYJXyZRvgyreHzS/h6MHzL5XnfmF+Bo68Trx50OqjHnc4Slh5BNvmpE4ORN9ePPoYffcy00n7MKq2eNW2WzLFgPN3fp6JnthqhEsW9G+N6RNxnqDy4u/pzDP05ot97vqRsRya8Qw3eodZ8A15j77o8gz/PY5+5sfJlQK+pK6uTtYqyTuIY5tfPkvvfG7yFmneOPEsW3sPgnSv3nzAc7q+0HLOXZDvBbuA5Dp4mux50OqlynT7xMl+9OX12ip6CoHy7Q9zGk88RvvY7ZW67+N8I3c8LzwLcB/SOcq0gMsnUfYn435G6m37btFtz+owUtzPNPEvZGNVbZM188oHTTk1Qz6r2ajtidYkzXuw9bC5WvCBcE4SnS0yT20h1BG5TxO00pzmsExnW5ryzQnjGB5XpR8SNZSkoDJ2M9TEV7qcNnU79xE7JvHfU+XKforrRbg9JfqiPOSNmgZHOE/Wcs1vFrl3Fzm7Yb5f7j4Q3S3hH6XXgE+WZcpruHV1O++F7aDzn+T8GuhjGP4YKY0lG8/VHQPdbaaZ9HYleH4bwe/ZE5FlbrLf1HCcVcBPT6m/HqIfhLvUw14aR16hvu3C+4VnifoXcZ+r7Crnvo+/9oidH37MuoJ9D9RmmUoaFN0/7ybJKP930aNIxU773jgrMweBCiKntZCxQXQZ8byD0viZtGQJeWTo4N6/4q3MqMAPAP23qzOkzp5ZWzZwzG3qZpvhuPXvO3CpJ963wJ19kR7d7Qjl635Ph4vZFzDBVHvNhTCfhjVX0B76/qhxdl9Bd1yUfwSDxCmu5jfL2xOt4jq8OF6BW6ynli+PoIjcwxs3JWepjR8oodXYQmRFB5XGd8PcXtxS6TRW+m3X5jgftF7eOTXUt3b4jsh+i1PxY9aJ7AmiBuM91EvAVMdkZoEY4Q3TYk0A/k+eZSIX2TWGhe6ddrnus8KbQ7Yj4ez30n6vD4z57U3QkaF6XsoR3rHOhOqZ500ErGEexE90KhfdNhVEqNUg9ovkzQUuoW+JEt6eF/1GEriNKbCVqw2QtkwW6izLiB92UyMx3YlQiuP06LfqAKoQ/vskPug0S/hng7wiJvs5QJ1fbLRv0ZXle4vjw1UXsRvebRVe68KaxnbtN3ObHzFT7JEwpHOPeKe5/dnqBq1Dd6Lgy6WzvdsizC2N6o46SNpvt2ja691M1ug0eDvq+uA+JGYg6S8LDerMB7ma/J0e7/YT5zJGwHDLyXjquhmq+a3V7lKfd7tZ183Dt9gu2BzvVPJQ7KTMowU1u9zgLDTfyOYtC3EbG1Ia4OTFLQ/WpZaF8anmoPmdlqGzM2lA+tSFUn7Mx1K3dZsPN7Xdsx31gHszznAdzh71u/7JnjSDrdZ7zzHoL9aPoRD0Dt+qgeT8+Npo=
*/