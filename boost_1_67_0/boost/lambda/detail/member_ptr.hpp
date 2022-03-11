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