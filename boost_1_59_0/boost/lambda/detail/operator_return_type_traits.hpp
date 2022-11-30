//  operator_return_type_traits.hpp -- Boost Lambda Library ------------------

// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org

#ifndef BOOST_LAMBDA_OPERATOR_RETURN_TYPE_TRAITS_HPP
#define BOOST_LAMBDA_OPERATOR_RETURN_TYPE_TRAITS_HPP

#include "boost/lambda/detail/is_instance_of.hpp"
#include "boost/type_traits/is_same.hpp"
#include "boost/type_traits/is_pointer.hpp"
#include "boost/type_traits/is_float.hpp"
#include "boost/type_traits/is_convertible.hpp"
#include "boost/type_traits/remove_pointer.hpp"
#include "boost/type_traits/remove_const.hpp"
#include "boost/type_traits/remove_reference.hpp"

#include "boost/indirect_reference.hpp"
#include "boost/detail/container_fwd.hpp"

#include <cstddef> // needed for the ptrdiff_t
#include <iosfwd>  // for istream and ostream

#include <iterator> // needed for operator&

namespace boost { 
namespace lambda {
namespace detail {

// -- general helper templates for type deduction ------------------

// Much of the type deduction code for standard arithmetic types from Gary Powell

template <class A> struct promote_code { static const int value = -1; };
// this means that a code is not defined for A

// -- the next 5 types are needed in if_then_else_return 
// the promotion order is not important, but they must have distinct values.
template <> struct promote_code<bool> { static const int value = 10; };
template <> struct promote_code<char> { static const int value = 20; };
template <> struct promote_code<unsigned char> { static const int value = 30; };
template <> struct promote_code<signed char> { static const int value = 40; };
template <> struct promote_code<short int> { static const int value = 50; };
// ----------

template <> struct promote_code<int> { static const int value = 100; };
template <> struct promote_code<unsigned int> { static const int value = 200; };
template <> struct promote_code<long> { static const int value = 300; };
template <> struct promote_code<unsigned long> { static const int value = 400; };

template <> struct promote_code<float> { static const int value = 500; };
template <> struct promote_code<double> { static const int value = 600; };
template <> struct promote_code<long double> { static const int value = 700; };

// TODO: wchar_t

// forward delcaration of complex.

} // namespace detail
} // namespace lambda 
} // namespace boost

namespace boost { 
namespace lambda {
namespace detail {

template <> struct promote_code< std::complex<float> > { static const int value = 800; };
template <> struct promote_code< std::complex<double> > { static const int value = 900; };
template <> struct promote_code< std::complex<long double> > { static const int value = 1000; };

// -- int promotion -------------------------------------------
template <class T> struct promote_to_int { typedef T type; };

template <> struct promote_to_int<bool> { typedef int type; };
template <> struct promote_to_int<char> { typedef int type; };
template <> struct promote_to_int<unsigned char> { typedef int type; };
template <> struct promote_to_int<signed char> { typedef int type; };
template <> struct promote_to_int<short int> { typedef int type; };

// The unsigned short int promotion rule is this:
// unsigned short int to signed int if a signed int can hold all values 
// of unsigned short int, otherwise go to unsigned int.
template <> struct promote_to_int<unsigned short int>
{ 
        typedef
                detail::IF<sizeof(int) <= sizeof(unsigned short int),        
// I had the logic reversed but ">" messes up the parsing.
                unsigned int,
                int>::RET type; 
};


// TODO: think, should there be default behaviour for non-standard types?

} // namespace detail

// ------------------------------------------ 
// Unary actions ----------------------------
// ------------------------------------------ 

template<class Act, class A>
struct plain_return_type_1 {
  typedef detail::unspecified type;
};



template<class Act, class A>
struct plain_return_type_1<unary_arithmetic_action<Act>, A> {
  typedef A type;
};

template<class Act, class A> 
struct return_type_1<unary_arithmetic_action<Act>, A> { 
  typedef 
    typename plain_return_type_1<
      unary_arithmetic_action<Act>,
      typename detail::remove_reference_and_cv<A>::type
    >::type type;
};


template<class A>
struct plain_return_type_1<bitwise_action<not_action>, A> {
  typedef A type;
};

// bitwise not, operator~()
template<class A> struct return_type_1<bitwise_action<not_action>, A> {
  typedef 
    typename plain_return_type_1<
      bitwise_action<not_action>,
      typename detail::remove_reference_and_cv<A>::type
    >::type type;
};


// prefix increment and decrement operators return 
// their argument by default as a non-const reference
template<class Act, class A> 
struct plain_return_type_1<pre_increment_decrement_action<Act>, A> {
  typedef A& type;
};

template<class Act, class A> 
struct return_type_1<pre_increment_decrement_action<Act>, A> {
  typedef 
    typename plain_return_type_1<
      pre_increment_decrement_action<Act>,
      typename detail::remove_reference_and_cv<A>::type
    >::type type;
};

// post decrement just returns the same plain type.
template<class Act, class A>
struct plain_return_type_1<post_increment_decrement_action<Act>, A> {
  typedef A type;
};

template<class Act, class A> 
struct return_type_1<post_increment_decrement_action<Act>, A> 
{ 
  typedef 
    typename plain_return_type_1<
      post_increment_decrement_action<Act>,
      typename detail::remove_reference_and_cv<A>::type
    >::type type;
};

// logical not, operator!()
template<class A> 
struct plain_return_type_1<logical_action<not_action>, A> {
  typedef bool type;
};

template<class A>
struct return_type_1<logical_action<not_action>, A> {
  typedef 
    typename plain_return_type_1<
      logical_action<not_action>,
      typename detail::remove_reference_and_cv<A>::type
    >::type type;
};

// address of action ---------------------------------------


template<class A> 
struct return_type_1<other_action<addressof_action>, A> { 
  typedef 
    typename plain_return_type_1<
      other_action<addressof_action>, 
      typename detail::remove_reference_and_cv<A>::type
    >::type type1;

  // If no user defined specialization for A, then return the
  // cv qualified pointer to A
  typedef typename detail::IF<
    boost::is_same<type1, detail::unspecified>::value, 
    typename boost::remove_reference<A>::type*,
    type1
  >::RET type;
};

// contentsof action ------------------------------------

// TODO: this deduction may lead to fail directly, 
// (if A has no specialization for iterator_traits and has no
// typedef A::reference.
// There is no easy way around this, cause there doesn't seem to be a way
// to test whether a class is an iterator or not.
 
// The default works with std::iterators.

namespace detail {

  // A is a nonreference type
template <class A> struct contentsof_type {
  typedef typename boost::indirect_reference<A>::type type; 
};

  // this is since the nullary () in lambda_functor is always instantiated
template <> struct contentsof_type<null_type> {
  typedef detail::unspecified type;
};


template <class A> struct contentsof_type<const A> {
  typedef typename contentsof_type<A>::type type;
};

template <class A> struct contentsof_type<volatile A> {
  typedef typename contentsof_type<A>::type type;
};

template <class A> struct contentsof_type<const volatile A> {
  typedef typename contentsof_type<A>::type type;
};

  // standard iterator traits should take care of the pointer types 
  // but just to be on the safe side, we have the specializations here:
  // these work even if A is cv-qualified.
template <class A> struct contentsof_type<A*> {
  typedef A& type;
};
template <class A> struct contentsof_type<A* const> {
  typedef A& type;
};
template <class A> struct contentsof_type<A* volatile> {
  typedef A& type;
};
template <class A> struct contentsof_type<A* const volatile> {
  typedef A& type;
};

template<class A, int N> struct contentsof_type<A[N]> { 
  typedef A& type; 
};
template<class A, int N> struct contentsof_type<const A[N]> { 
  typedef const A& type; 
};
template<class A, int N> struct contentsof_type<volatile A[N]> { 
  typedef volatile A& type; 
};
template<class A, int N> struct contentsof_type<const volatile A[N]> { 
  typedef const volatile A& type; 
};





} // end detail

template<class A> 
struct return_type_1<other_action<contentsof_action>, A> { 

  typedef 
    typename plain_return_type_1<
      other_action<contentsof_action>, 
      typename detail::remove_reference_and_cv<A>::type
    >::type type1;

  // If no user defined specialization for A, then return the
  // cv qualified pointer to A
  typedef typename 
  detail::IF_type<
    boost::is_same<type1, detail::unspecified>::value, 
    detail::contentsof_type<
      typename boost::remove_reference<A>::type
    >,
    detail::identity_mapping<type1>
  >::type type;
};


// ------------------------------------------------------------------
// binary actions ---------------------------------------------------
// ------------------------------------------------------------------

// here the default case is: no user defined versions:
template <class Act, class A, class B>
struct plain_return_type_2 {
  typedef detail::unspecified type; 
};

namespace detail {

// error classes
class illegal_pointer_arithmetic{};

// pointer arithmetic type deductions ----------------------
// value = false means that this is not a pointer arithmetic case
// value = true means, that this can be a pointer arithmetic case, but not necessarily is
// This means, that for user defined operators for pointer types, say for some operator+(X, *Y),
// the deductions must be coded at an earliel level (return_type_2).

template<class Act, class A, class B> 
struct pointer_arithmetic_traits { static const bool value = false; };

template<class A, class B> 
struct pointer_arithmetic_traits<plus_action, A, B> { 

  typedef typename 
    array_to_pointer<typename boost::remove_reference<A>::type>::type AP;
  typedef typename 
    array_to_pointer<typename boost::remove_reference<B>::type>::type BP;

  static const bool is_pointer_A = boost::is_pointer<AP>::value;
  static const bool is_pointer_B = boost::is_pointer<BP>::value;  

  static const bool value = is_pointer_A || is_pointer_B;

  // can't add two pointers.
  // note, that we do not check wether the other type is valid for 
  // addition with a pointer.
  // the compiler will catch it in the apply function

  typedef typename 
  detail::IF<
    is_pointer_A && is_pointer_B, 
      detail::return_type_deduction_failure<
        detail::illegal_pointer_arithmetic
      >,
      typename detail::IF<is_pointer_A, AP, BP>::RET
  >::RET type; 

};

template<class A, class B> 
struct pointer_arithmetic_traits<minus_action, A, B> { 
  typedef typename 
    array_to_pointer<typename boost::remove_reference<A>::type>::type AP;
  typedef typename 
    array_to_pointer<typename boost::remove_reference<B>::type>::type BP;

  static const bool is_pointer_A = boost::is_pointer<AP>::value;
  static const bool is_pointer_B = boost::is_pointer<BP>::value;  

  static const bool value = is_pointer_A || is_pointer_B;

  static const bool same_pointer_type =
    is_pointer_A && is_pointer_B && 
    boost::is_same<
      typename boost::remove_const<
        typename boost::remove_pointer<
          typename boost::remove_const<AP>::type
        >::type
      >::type,
      typename boost::remove_const<
        typename boost::remove_pointer<
          typename boost::remove_const<BP>::type
        >::type
      >::type
    >::value;

  // ptr - ptr has type ptrdiff_t
  // note, that we do not check if, in ptr - B, B is 
  // valid for subtraction with a pointer.
  // the compiler will catch it in the apply function

  typedef typename 
  detail::IF<
    same_pointer_type, const std::ptrdiff_t,
    typename detail::IF<
      is_pointer_A, 
      AP, 
      detail::return_type_deduction_failure<detail::illegal_pointer_arithmetic>
    >::RET
  >::RET type; 
};

} // namespace detail
   
// -- arithmetic actions ---------------------------------------------

namespace detail {
   
template<bool is_pointer_arithmetic, class Act, class A, class B> 
struct return_type_2_arithmetic_phase_1;

template<class A, class B> struct return_type_2_arithmetic_phase_2;
template<class A, class B> struct return_type_2_arithmetic_phase_3;

} // namespace detail
  

// drop any qualifiers from the argument types within arithmetic_action
template<class A, class B, class Act> 
struct return_type_2<arithmetic_action<Act>, A, B>
{
  typedef typename detail::remove_reference_and_cv<A>::type plain_A;
  typedef typename detail::remove_reference_and_cv<B>::type plain_B;

  typedef typename 
    plain_return_type_2<arithmetic_action<Act>, plain_A, plain_B>::type type1;
  
  // if user defined return type, do not enter the whole arithmetic deductions
  typedef typename 
    detail::IF_type<
      boost::is_same<type1, detail::unspecified>::value, 
      detail::return_type_2_arithmetic_phase_1<
         detail::pointer_arithmetic_traits<Act, A, B>::value, Act, A, B
      >,
      plain_return_type_2<arithmetic_action<Act>, plain_A, plain_B>
    >::type type;
};

namespace detail {
   
// perform integral promotion, no pointer arithmetic
template<bool is_pointer_arithmetic, class Act, class A, class B> 
struct return_type_2_arithmetic_phase_1
{
  typedef typename 
    return_type_2_arithmetic_phase_2<
      typename remove_reference_and_cv<A>::type,
      typename remove_reference_and_cv<B>::type
    >::type type;
};

// pointer_arithmetic
template<class Act, class A, class B> 
struct return_type_2_arithmetic_phase_1<true, Act, A, B>
{
  typedef typename 
    pointer_arithmetic_traits<Act, A, B>::type type;
};

template<class A, class B>
struct return_type_2_arithmetic_phase_2 {
  typedef typename
    return_type_2_arithmetic_phase_3<
      typename promote_to_int<A>::type, 
      typename promote_to_int<B>::type
    >::type type;
};

// specialization for unsigned int.
// We only have to do these two specialization because the value promotion will
// take care of the other cases.
// The unsigned int promotion rule is this:
// unsigned int to long if a long can hold all values of unsigned int,
// otherwise go to unsigned long.

// struct so I don't have to type this twice.
struct promotion_of_unsigned_int
{
        typedef
        detail::IF<sizeof(long) <= sizeof(unsigned int),        
                unsigned long,
                long>::RET type; 
};

template<>
struct return_type_2_arithmetic_phase_2<unsigned int, long>
{
        typedef promotion_of_unsigned_int::type type;
};
template<>
struct return_type_2_arithmetic_phase_2<long, unsigned int>
{
        typedef promotion_of_unsigned_int::type type;
};


template<class A, class B> struct return_type_2_arithmetic_phase_3 { 
   enum { promote_code_A_value = promote_code<A>::value,
         promote_code_B_value = promote_code<B>::value }; // enums for KCC
  typedef typename
    detail::IF<
      promote_code_A_value == -1 || promote_code_B_value == -1,
      detail::return_type_deduction_failure<return_type_2_arithmetic_phase_3>,
      typename detail::IF<
        ((int)promote_code_A_value > (int)promote_code_B_value), 
        A, 
        B
      >::RET
    >::RET type;                    
};

} // namespace detail

// --  bitwise actions -------------------------------------------
// note: for integral types deuduction is similar to arithmetic actions. 

// drop any qualifiers from the argument types within arithmetic action
template<class A, class B, class Act> 
struct return_type_2<bitwise_action<Act>, A, B>
{

  typedef typename detail::remove_reference_and_cv<A>::type plain_A;
  typedef typename detail::remove_reference_and_cv<B>::type plain_B;

  typedef typename 
    plain_return_type_2<bitwise_action<Act>, plain_A, plain_B>::type type1;
  
  // if user defined return type, do not enter type deductions
  typedef typename 
    detail::IF_type<
      boost::is_same<type1, detail::unspecified>::value, 
      return_type_2<arithmetic_action<plus_action>, A, B>,
      plain_return_type_2<bitwise_action<Act>, plain_A, plain_B>
    >::type type;

  // plus_action is just a random pick, has to be a concrete instance

  // TODO: This check is only valid for built-in types, overloaded types might
  // accept floating point operators

  // bitwise operators not defined for floating point types
  // these test are not strictly needed here, since the error will be caught in
  // the apply function
  BOOST_STATIC_ASSERT(!(boost::is_float<plain_A>::value && boost::is_float<plain_B>::value));

};

namespace detail {


template <class T> struct get_ostream_type {
  typedef std::basic_ostream<typename T::char_type, 
                             typename T::traits_type>& type;
};

template <class T> struct get_istream_type {
  typedef std::basic_istream<typename T::char_type, 
                             typename T::traits_type>& type;
};

template<class A, class B>
struct leftshift_type {
private:
  typedef typename boost::remove_reference<A>::type plainA;
public:
  typedef typename detail::IF_type<
    is_instance_of_2<plainA, std::basic_ostream>::value, 
    get_ostream_type<plainA>, //reference to the stream 
    detail::remove_reference_and_cv<A>
  >::type type;
};

template<class A, class B>
struct rightshift_type {
private:
  typedef typename boost::remove_reference<A>::type plainA;
public:
  typedef typename detail::IF_type<
    is_instance_of_2<plainA, std::basic_istream>::value, 
    get_istream_type<plainA>, //reference to the stream 
    detail::remove_reference_and_cv<A>
  >::type type;
};



} // end detail

// ostream
template<class A, class B> 
struct return_type_2<bitwise_action<leftshift_action>, A, B>
{
  typedef typename detail::remove_reference_and_cv<A>::type plain_A;
  typedef typename detail::remove_reference_and_cv<B>::type plain_B;

  typedef typename 
    plain_return_type_2<bitwise_action<leftshift_action>, plain_A, plain_B>::type type1;
  
  // if user defined return type, do not enter type deductions
  typedef typename 
    detail::IF_type<
      boost::is_same<type1, detail::unspecified>::value, 
      detail::leftshift_type<A, B>,
      plain_return_type_2<bitwise_action<leftshift_action>, plain_A, plain_B>
    >::type type;
};

// istream
template<class A, class B> 
struct return_type_2<bitwise_action<rightshift_action>, A, B>
{
  typedef typename detail::remove_reference_and_cv<A>::type plain_A;
  typedef typename detail::remove_reference_and_cv<B>::type plain_B;

  typedef typename 
    plain_return_type_2<bitwise_action<rightshift_action>, plain_A, plain_B>::type type1;
  
  // if user defined return type, do not enter type deductions
  typedef typename 
    detail::IF_type<
      boost::is_same<type1, detail::unspecified>::value, 
      detail::rightshift_type<A, B>,
      plain_return_type_2<bitwise_action<rightshift_action>, plain_A, plain_B>
    >::type type;
};

// -- logical actions ----------------------------------------
// always bool
// NOTE: this may not be true for some weird user-defined types,
template<class A, class B, class Act> 
struct plain_return_type_2<logical_action<Act>, A, B> { 
  typedef bool type; 
};

template<class A, class B, class Act> 
struct return_type_2<logical_action<Act>, A, B> { 

  typedef typename detail::remove_reference_and_cv<A>::type plain_A;
  typedef typename detail::remove_reference_and_cv<B>::type plain_B;

  typedef typename 
    plain_return_type_2<logical_action<Act>, plain_A, plain_B>::type type;
  
};


// -- relational actions ----------------------------------------
// always bool
// NOTE: this may not be true for some weird user-defined types,
template<class A, class B, class Act> 
struct plain_return_type_2<relational_action<Act>, A, B> { 
  typedef bool type; 
};

template<class A, class B, class Act> 
struct return_type_2<relational_action<Act>, A, B> { 

  typedef typename detail::remove_reference_and_cv<A>::type plain_A;
  typedef typename detail::remove_reference_and_cv<B>::type plain_B;

  typedef typename 
    plain_return_type_2<relational_action<Act>, plain_A, plain_B>::type type; 
};

// Assingment actions -----------------------------------------------
// return type is the type of the first argument as reference

// note that cv-qualifiers are preserved.
// Yes, assignment operator can be const!

// NOTE: this may not be true for some weird user-defined types,

template<class A, class B, class Act> 
struct return_type_2<arithmetic_assignment_action<Act>, A, B> { 

  typedef typename detail::remove_reference_and_cv<A>::type plain_A;
  typedef typename detail::remove_reference_and_cv<B>::type plain_B;

  typedef typename 
    plain_return_type_2<
      arithmetic_assignment_action<Act>, plain_A, plain_B
    >::type type1;
  
  typedef typename 
    detail::IF<
      boost::is_same<type1, detail::unspecified>::value, 
      typename boost::add_reference<A>::type,
      type1
    >::RET type;
};

template<class A, class B, class Act> 
struct return_type_2<bitwise_assignment_action<Act>, A, B> { 

  typedef typename detail::remove_reference_and_cv<A>::type plain_A;
  typedef typename detail::remove_reference_and_cv<B>::type plain_B;

  typedef typename 
    plain_return_type_2<
      bitwise_assignment_action<Act>, plain_A, plain_B
    >::type type1;
  
  typedef typename 
    detail::IF<
      boost::is_same<type1, detail::unspecified>::value, 
      typename boost::add_reference<A>::type,
      type1
    >::RET type;
};

template<class A, class B> 
struct return_type_2<other_action<assignment_action>, A, B> { 
  typedef typename detail::remove_reference_and_cv<A>::type plain_A;
  typedef typename detail::remove_reference_and_cv<B>::type plain_B;

  typedef typename 
    plain_return_type_2<
      other_action<assignment_action>, plain_A, plain_B
    >::type type1;
  
  typedef typename 
    detail::IF<
      boost::is_same<type1, detail::unspecified>::value, 
      typename boost::add_reference<A>::type,
      type1
    >::RET type;
};

// -- other actions ----------------------------------------

// comma action ----------------------------------
// Note: this may not be true for some weird user-defined types,

// NOTE! This only tries the plain_return_type_2 layer and gives
// detail::unspecified as default. If no such specialization is found, the 
// type rule in the spcecialization of the return_type_2_prot is used
// to give the type of the right argument (which can be a reference too)
// (The built in operator, can return a l- or rvalue).
template<class A, class B> 
struct return_type_2<other_action<comma_action>, A, B> { 

  typedef typename detail::remove_reference_and_cv<A>::type plain_A;
  typedef typename detail::remove_reference_and_cv<B>::type plain_B;

  typedef typename 
    plain_return_type_2<
      other_action<comma_action>, plain_A, plain_B
    >::type type;
  };

// subscript action -----------------------------------------------


namespace detail {
  // A and B are nonreference types
template <class A, class B> struct subscript_type {
  typedef detail::unspecified type; 
};

template <class A, class B> struct subscript_type<A*, B> {
  typedef A& type;
};
template <class A, class B> struct subscript_type<A* const, B> {
  typedef A& type;
};
template <class A, class B> struct subscript_type<A* volatile, B> {
  typedef A& type;
};
template <class A, class B> struct subscript_type<A* const volatile, B> {
  typedef A& type;
};


template<class A, class B, int N> struct subscript_type<A[N], B> { 
  typedef A& type; 
};

  // these 3 specializations are needed to make gcc <3 happy
template<class A, class B, int N> struct subscript_type<const A[N], B> { 
  typedef const A& type; 
};
template<class A, class B, int N> struct subscript_type<volatile A[N], B> { 
  typedef volatile A& type; 
};
template<class A, class B, int N> struct subscript_type<const volatile A[N], B> { 
  typedef const volatile A& type; 
};

} // end detail

template<class A, class B>
struct return_type_2<other_action<subscript_action>, A, B> {

  typedef typename detail::remove_reference_and_cv<A>::type plain_A;
  typedef typename detail::remove_reference_and_cv<B>::type plain_B;

  typedef typename boost::remove_reference<A>::type nonref_A;
  typedef typename boost::remove_reference<B>::type nonref_B;

  typedef typename 
    plain_return_type_2<
      other_action<subscript_action>, plain_A, plain_B
    >::type type1;
  
  typedef typename 
    detail::IF_type<
      boost::is_same<type1, detail::unspecified>::value, 
      detail::subscript_type<nonref_A, nonref_B>,
      plain_return_type_2<other_action<subscript_action>, plain_A, plain_B>
    >::type type;

};

template<class Key, class T, class Cmp, class Allocator, class B> 
struct plain_return_type_2<other_action<subscript_action>, std::map<Key, T, Cmp, Allocator>, B> { 
  typedef T& type;
  // T == std::map<Key, T, Cmp, Allocator>::mapped_type; 
};

template<class Key, class T, class Cmp, class Allocator, class B> 
struct plain_return_type_2<other_action<subscript_action>, std::multimap<Key, T, Cmp, Allocator>, B> { 
  typedef T& type;
  // T == std::map<Key, T, Cmp, Allocator>::mapped_type; 
};

  // deque
template<class T, class Allocator, class B> 
struct plain_return_type_2<other_action<subscript_action>, std::deque<T, Allocator>, B> { 
  typedef typename std::deque<T, Allocator>::reference type;
};
template<class T, class Allocator, class B> 
struct plain_return_type_2<other_action<subscript_action>, const std::deque<T, Allocator>, B> { 
  typedef typename std::deque<T, Allocator>::const_reference type;
};

  // vector
template<class T, class Allocator, class B> 
struct plain_return_type_2<other_action<subscript_action>, std::vector<T, Allocator>, B> { 
  typedef typename std::vector<T, Allocator>::reference type;
};
template<class T, class Allocator, class B> 
struct plain_return_type_2<other_action<subscript_action>, const std::vector<T, Allocator>, B> { 
  typedef typename std::vector<T, Allocator>::const_reference type;
};

  // basic_string
template<class Char, class Traits, class Allocator, class B> 
struct plain_return_type_2<other_action<subscript_action>, std::basic_string<Char, Traits, Allocator>, B> { 
  typedef typename std::basic_string<Char, Traits, Allocator>::reference type;
};
template<class Char, class Traits, class Allocator, class B> 
struct plain_return_type_2<other_action<subscript_action>, const std::basic_string<Char, Traits, Allocator>, B> { 
  typedef typename std::basic_string<Char, Traits, Allocator>::const_reference type;
};

template<class Char, class Traits, class Allocator> 
struct plain_return_type_2<arithmetic_action<plus_action>,
                           std::basic_string<Char, Traits, Allocator>,
                           std::basic_string<Char, Traits, Allocator> > { 
  typedef std::basic_string<Char, Traits, Allocator> type;
};

template<class Char, class Traits, class Allocator> 
struct plain_return_type_2<arithmetic_action<plus_action>,
                           const Char*,
                           std::basic_string<Char, Traits, Allocator> > { 
  typedef std::basic_string<Char, Traits, Allocator> type;
};

template<class Char, class Traits, class Allocator> 
struct plain_return_type_2<arithmetic_action<plus_action>,
                           std::basic_string<Char, Traits, Allocator>,
                           const Char*> { 
  typedef std::basic_string<Char, Traits, Allocator> type;
};

template<class Char, class Traits, class Allocator, std::size_t N> 
struct plain_return_type_2<arithmetic_action<plus_action>,
                           Char[N],
                           std::basic_string<Char, Traits, Allocator> > { 
  typedef std::basic_string<Char, Traits, Allocator> type;
};

template<class Char, class Traits, class Allocator, std::size_t N> 
struct plain_return_type_2<arithmetic_action<plus_action>,
                           std::basic_string<Char, Traits, Allocator>,
                           Char[N]> { 
  typedef std::basic_string<Char, Traits, Allocator> type;
};


} // namespace lambda
} // namespace boost

#endif



/* operator_return_type_traits.hpp
pekMjQ9dAiI7HSqF3dPf7D43iyzuohGzn94MNHfKNmJHpwJm08+/FBqtxWXphKvPKyPwwKlEtli61CkAdfhQmIl+4DnTuTi8TZZWg+VVh3YySsRs+xZcHy+7OTVoqzZb1eeO0cIG60I86mOaccUIBP84oGXUSP7FbYj6Kz0pgzAq4Jh5wlSLBnkFA47SSIWpo34kz/3cFsfIWg6/Hd2zaQML4f8hafgJwyxZkdxTsIrcHduV1d1pqISz8u280tHYjPdTsbVmpOcsOMrBTE4nBMmp34McX+jkgyg7QXVri7YT0JGoWlIfMmZOSJ/HTv67/hmqJDD7By9Py/fpvYlkEh6fOBJJyHjqE4xGQ3dHO68mJa+0wwyQNQ+uMK5ONBVPrqyUVjf1g2cEFwvc60mGTk2K0ePzYUPm4uD2CjzGTv2SwNzuwjXIUlDUCUTpNYHHK2VW1Gpn3SspDbAZGolL6YixrTvqWlJp+oqOqjPuy2qnMBqc7LdcXZR/PQfGVkh2V+F+Y88/7vAuT3snKy3blm6LwDE3kCktryQYVqhIKabSyap8JukkWw15h/ufKrSoB6LPgkEgbjx7FS25VyOP12LWPI4EYZD2SYxLTUAnJcuz9vsavjpXmKFIGeMeiyno9TcyLvWrbS1i+d2bEJi7E3eKteCJYnINs19kDrTqnc0QMwr1V7WxOjLMeM0kls/CxEuKxM+pHHc7yg2CGebCUzPHaCayE4jyl7YqR2TsrJy/CA+VHdAqpaioDCxKM5nX3llqfERPpERPKI6l0NkRIpVPI6DTUSFyMFWwYCTyZc3NgepLI8hUQ6EAawpnZOsnCorRcLWgOPQm7ZnEjX+2vSMdbsAB88la/uADGfeDP3SaYd5AMrSwnui5OsFi4pf2yz74P/cG1RK3enQ3Cdvr07HM1WT8m1PUnqB8LUgLmHB5K+5HM+9/yi4O9VC3NQ3Ya9OSf5XsjPa0wj9ZAHT+2VfZIpcnydcs4sEpY+zxretJeUi4Vu8zNWrr7XzSWvgzKY+oXapS1ArVbohyRqmtWqZEu97BNCbZUq84VRFSllV46CM8GZD51i76CQHbzamv0VA657P/+tMdqEPCX/UYL/74Dt6uXHMNBSjcMbNf4FQEo5D1gMNRjO2SfM1Avk44Lz5xSrX4gC8PmTEgjKOWFnJ5iqTA3l26lvU8pfV4JH7khOv95sSqcsxkstgFDvtTYEAgeyF20Z6BJIbestivct/13yra3fWxQMb5QWXEKDBCNSJUowzOrLW853qXd8tPkASJHk3K92zHdZ79b/BdhPXiJA65rs+cSGIijZ5XtzlinCj9CRmkE1c+ertTwpl7/W7MnrDn1XXn1lbOzuUB9qDCq0jHEgy7cSiNQn0IiPE5H7odhHEAhIiTCkhLFAqBXjkW5yI6k0bLK/M0IEwkAPWyBGgdDJ60wJxY26eWW9NhqrJ8QNIDIpicQt6v/1x6VEmcK6dFP0JmEb/mLnXKcLutgr2UdruSKS3IFxXkgWryGP7SiximCwYpKujSAEADwLgzS8y5ko9F6WaElqUZfG1+Z1aJfApetd17dyAkvh7DPBH4giAJ0JaJa4bZalx2c822cKCH80I4rVI8v+V7SIMezjs1xXrDCLmjCgDAEWKhdDfHChpAxFmTMCKgARS3mKd2y5CCYF0ofPDvnjNfBxiDhRsttXdQD2VVenOCGN58vqXbVA9tSd2eYvUdNUQr4SO2tGMOkNBMa6M+K7S0Kdz5fWVx7a7b6kCLoej6Cwy/jYlTDXb4hrfVPC63F+AAVj9sDLXrzb1mzAv4LTwKJn0oslaTtWYXhJN2Fg2nn0y7zB1Ec0+AwN82vQI/yOodpG118ndZkAzDpQEgzrlRPPndDMeji3xF55WPnkPGceLKQIr0l2TlXF6pFfEzz37V74jHRe3tjqvzlCG5ugoQiAWQAYpd0RADKZhDEKYA22nKH8SNiL0qhDNUD4XycMTnFwOJQaPiUghDuVAU2Mc/DGiii/FnlVKo3X07aw0xes7XVbGcjB1tH0oOPLnUrFY7VRdEjYk9EAHtvSj8swm4FIoisCe3NLpsNNnSEkLrK4zre5na2yWAAmAaJOM4k+wAAADYAMyBUy2RtgMAJHsDn9F/mIG3CLWLtvYELsBifKj1TCe5L0YmNQTZiePYUJeENzwpcqoiJ3nPays1nqO//syG6cWmDeXznaWLXQWC9V4BvjWos5udUBqi//e34A5kHCNNMCP5FccrIiYMY5WBXqZ7whPbeZgi9RwUWWBjsRqxvCJnp0o1h5VuqLveJhP07CAd8+VBq5xzVC5YYX+vEb+lgpPQEAaXJyaw63Y8SdVdLATILjYFtazYgGTkMSwomVaKqFN/84D1Ia05HulezOtgq5CzqkCmZrDp+ayg6DfWhhqQAhHq5gIQRE/4BEDqVACAGxTIeCzYc/w4WeA0wZmWjcb8q8CfAsBoWPzV/OHe+0HrDETA8A2Ksts/UVYLcvuE+g/TUl6vNrVBpPTL0R32NVbiXDjgFIEMGEUn7pQ+9bD3mPwNjzHwWTS7BhYcTIOEicODkwLSp7sBbJBIFrJVk21hZ9FwIXWE8I+mX9q3kLhb+SYM730NWh2aSYrnX/5ycXPl616RR53usMfpYb814u//YbarWqVm7mdqQb56qUhNHUBBHEwCo63GZ2R4b6U3WBE3OGCpPc559nEBH7ysPwVpgwoqB4WYExGEABwEQPKnaHAMFq9490E9QXkGZUTJub6mWDLdv9a0LtxgL24LySRtuAaL9egDX7lhvaZLVh7HN9XUaimKuvwLUSdaSPiMy7NN0IscAFyU8Zr3jN6AUWDZg9YIifxpjF11qrhXMhzHvwOb/lVKMd+jmXSZVjoS+1bqC7j9EBTFvN+G+1/bmuZwEMGwtDIhjPCOTpLdiiXVbU2Xuq5KBnVljyQIrdRRVxR7Ef3Sz/t6nXfbE3RRAYtGIp0+e4qjv3GdiHCvCA99PoNv6RaAcRYIPa64RJKjBHTOkMGgbWGrruAhCrWqKusbIDUSaVUVK0ZRafOrQE4A7NVUmruUOq3hKntGmX/1wOYBCIPJhTui0+YfXFXRE4MYiyOZJoaNgIf2W5BFFC6u+bfAx/OKRDMKOGXSLQnUroeDUui4iUjumY+nVcvUISINo3YxUPGil8nS3IBkwgwpwgDgS139AcBSi560Ac6Wq/XHFZNnkSKOum601KHog3l40Bd4oKev5NEzNs8cRquW6riRoBR2uF3H3U/U8dF04hDQcTTTubpZ4z5FUQd3J7IIYVfS09rgivg+isKCxRjZNLBUNBztSNTShfUAACRETML8gQkAyO0GJcKpduwQFIEe0FOabJngsixn0DMbZupRcD4DiYKalnEBAID/t4eEBhmBGCDz3An1RzHDrla79fN47PCXIlBRG6iOsgYoK9sCv3UNaiwG5aw+JUnv5Q8hDyga0/ciVr9fBbi9KLPMKqK6RKqDvnFwc6gxyYKYEwlX/WkcZtB5tknoKALcfyGwuZQawCzXkZ24ph71wrYen0pqTHCOpxpaVOTXTavDEHfBkGjhh2b4eQSz7+1xzTOJNZldxN7yTDlyA7r0lI0yndECCpRNiw2K5Pk6RDVwByoDAICQRLgq2HNamT24UpLkMlJ6b9Lw/apuh0ARAkUiRo2zY7GMjyrZzTsflEwc8u/Tbo3lFEPG6bRupTJ+I2GmPWqkyKlxKeUunoL7gAgcP1reNkJeUIUBra5Dzn8yaXG7FIM240IrxbW4XbMcDdVJwiiX/ibVFopMl9Mv8gBUnI4N3IDTsHiXqN8bTKizJArqnTWeDDYpB/7eMFC3QIeN1u3ZpXD3pWCWnDkX8GCNz/RbaT0/pVk6WE6A4REt8sUn5e9+f+fJnrAfJ6pN6SjW2vKeHBTM5Z0ugrPK6S+LiJtvnb/fbKYU1HHymUrVErb5+Waqqpik/kheFahLvZ4JslNDtbR1Q76WtYwt5YUyQXXXWCZ4iCuzhO6/11Wc+Biot+2SpEtBiEp7STPt96diwcSLABkUdLpKMR3aRwlGx4FLkmlODMYJRjaBeS82r44u2MNyKU3HN+ixxYByu9sD8L/Wrp2jm5baDbAtq7tTUpAxRUYdbGTiP5ScwU4jVtY0ZC8bRvczcJ4MO7Pn5lyu1C1OuC1JketguTjHeeiz58YQKTavbd+bwm1PVsrvDgkDeWMbv3iuOATeczWiL0bVllu+70G02mhFgvymyOR1yC4nh4HU+S4CqXEHo35nHevGsZlMoTsEMe5bZod5/xZftqLXmpuqa33lEjuNy0xkdKzQTTdgs3WM9ZwrM9OS2ZcJsL+nf959C2ChPzS3WkI6evCYR9iVAlWfEaGjXnlBrmltFYOQ9uT+BxOrc2HBAL7mMZFWSDHkkZQboT34zG6nE00C1XW3uPb4w8HgACB0Xt3lMh0d4zvHj1uED1iHR3XS2HW/z1tKI6ttDi2/b+1RxwoEsE2zzuNScsIzx/3UMuUxbSrG79se6x+VZPOROn760pjkImbLjP6xHOyQ9OaIvHT0QlUFEAMcyovzx5/jWIzk2+PmFOnm+X1WzMVRiqmYJQMug0a1713JzvIVuq/w1IcBCsdAbC6E2rdm41XnMNYo2sFiyPMPktOyCeHda4Y1gz6eli3CH6SEsFH4CyfCW7WWeuOX0q6knY06xT+phD8vOYzXjrS9hs9HD1hhGMvOWAEyT30ahCB4VjxjOcfY8wFgQk3c2LXrTPFBLB+1uEvd2c/TaccSV1As3jswMU38NMwXqdddrmwTuV95vLmc3oCW8v3tFDsMjMBbROZamVJWM0d4ZnBz9j0j3LpShEhbyqJuzXzIuoot/vy7xiht9EhSvNraU3d1ZRpJt1GXExFhCmr28fKKf9CKHVvU4xIEDIgH6GbsKOtZ9HoIX80v0YQTdbTUGdyJap0yexJJ8YqBI2Xx0Dq3y30r3wjD/63s4P898k1xoJMtHEtbS0M89Zn52brA5qJP4Ib/kElA1DKznTXKYtVeDtznYE0mT8pEyz8nLedtl02sOhhKcpE2h80rWJYonNCVjaRFDUnzq/wjJiLaYTI+DJj78sdOI1VNMWdfBDA35h6TwNXPwQqBDTRm4o8WEggr4ngwjUefGtSoeHgamoUcdoBLn5rgxkudFSnNZq7ze1N/JXENFsbUwPEhX3Rz66XRdB60QTGN4/kfMDaGV4W6DLQxCi9BhmgUlU8g9qSs7Lmzs0Wvn3pSKzWPTwd+99XWoBqMJJ9VEwvaf3AIkdttfA+MlNf7wsXHjY08F5zHeIeW5UlF3K4mmE2I1cw+U/kj2RyH/HvYp9gT5s7TTX90tSkSDHzPxXQNwvPvEk8eY0CJp1Y5QNIJSjwXC5MqL0R0UIlDkdU19/whJwYqe34WBFeaI7R7EGQaT+9rNheFKjWf6CzrqJ2GyRzIAKXP0TkquKl5dPfGD9DgeV1Tr2zPqjLx7Itit40jwmX3iXi8ujMmUSGysq1q1QA5Kvw0ydrWOoz2pP2Yt9LTt9iCQ2Je7KFpiPTcAovfbor0YKUuuasm7BeJyPG0+Y9yF4y3o39Wi37weucA0UhoRnXfNkaQv2icT2BtYve+NuP2TxmFhJNz1iF8r3knt0UTJTwx9nBbfeu3O6zBm1nYRNTIiMmH2bGV+nPG0REBC1Pb9LCwpkuNuXA6a3Z6LofP/exyakRk+DA7R0xNsK4Ee+LmxiaYTY6Z1kwGfuuvu1l5Hhd3ZwYqx8IDw/osrGiLfVWnPD+z9HGMbyOBvSDtolGBnjw1XLXC2joYKwSb43iiaDjhtKLcKGeNQ6tdfiOGmAi0nLKxePI+gMjjBov6FyBQLwEZ9e6hPsX9hWquvZwi+q69DOJc/OypkU8DGIQ30wphkMomnmKxwwo+Wm+9oIlEDFVw5lHjAaoumHnKF+dLHbUuMyn7m6bDIehFbTxye+/FAMk/8kuyFzrIAJcLM4/hmIPx/fF0oR1dN19J0f6wLoh5t0R9DTvvqZ0jVdErPv2VQxwBMXaYh/tuou1ktZzR5FHMlpLFaRi3YwecumguwlAhFrGAO6nuIJwnVpTSJwWWahqZeDXOACCYb8D0GGfECU6V58kC/lBV0zpLZFQRmQ00IFYdMIJRElnliFEZASHAm2BkkbjqaYZzsxFi3lcehja4Z6ZALPenDRFth8YXStkDV9mPQQz6JIIrSE6qxszYmA9AsHXUA/G2sX/1lHaYrLi20Dd9jQ09OWuauUH+BmCWB3+O+56FKSveZoPshOHzs01pLFrkZiiB1sdwTAl8W2WrBslHuuLsxQtdDNLxPl6GzYwMp+v0D8y9RxR/MNhu0DPYqaD5wF8nrddKDe6/hVqZuv/4YrF3rBpkbMKv7vP9DC1vTmI/D0YuF6Xa8h7H2nhxrM9TTe48aKjXIdKXQJETiovZnfba/wzxhB5ox0su3z80iXpQnzP3Q8dwvY8Jf4NTeUcvcswCn0L7OP19ryxphIeClI2iNuqWK4rfMd59PtbHynLv6yo0xcc1EVMN+QP/wsBdPnGyn6kTDSCY1j4zYsBWQ3Abfvh8HTF7eP8UC04z3UKraVcrKET5UKvLuHkSGfsNR2uMswc2XROCtIeuJKaTLHiLO9ffeFdBaNiPLaI6XN7wzHKqovbCtQGXUOJCNqUqEMS0l1aO/cRqb1XF8Emwvek+GLzukhNqWhCWtH31pHmFsvidV8Klhqu5D9r+/rFfij1Un7gA1373bHVb7XYR2ZQwal57HvhnmnBj+d2zAAIs/dOWnGGDx0vsc+B8savZRl3UNeiG10+PQQ5uNxMdi+Dl8jsi9OoB69RLUsSEiXdkaJNoABMhLXJHjXT7TKDT5yntQYgHJIajrzRWYliPnHqvUz10nxIoxAGmMyiN5aMdjMPdX2kxurZZ4cZWblElK1KUZd7W46BcyyK3kMfUG/8jdtklALETBEGz2sHrjStCVv6NZ/qrBghpUi5UnAfn7bwRoRmkDR+i2WedQPqTr0OAHSmkX/BnZiBx0hxwCillhhs5Tz6NOm+X0vFtT+a4rGV4T8mlA6lHDx0/XdPazxJNjyUce3hqzqBG3XhzXTVatUuOH89qJv67NIrWyotVveRZlRkBekx95Dzti+JtG5U5nm50rwXdR0caVheLmqDP1CbRsKIv4SMp0uggD81xORLdcomvNhJ/Xi5gBqyL7BVN4vZf3e3BVHTdJQ/HO95VZrWJ/KbN8PtH0KNYogcpKpDGXOrl2p8HOqKGOlMIfdE+nBpIkMEiocwP3W5ex9g8I2wn7wqJpVK35lLYPJjZJ2xWpJnmZi8qykJTwo/Msp2AUdjr3skcScCEzPN3hC8Cpi+HXIP5UZxMXwk6GKnEYQYijRulmSgiunkZg0MbGKnL1aaN1X01N7Jke6Pm6MmUH6Qsb+s8oyjqwT3CTToMjCVRL4xlqrnWAWs1kU5eY/HjDRtpl5GRPBcE3h6dNaf0+KcKc8ZSrbf0kUhRJye+3IQOYLcgQ9J2jzt1Zq16iPxmIAOMf7i4ZeEqsihjcFlLSVZOT+xp4UpfvMJ/Kk//1Zt6S1nwThravT51TKk0cRnvV9D4nsu0x3NMrDJDzHPq
*/