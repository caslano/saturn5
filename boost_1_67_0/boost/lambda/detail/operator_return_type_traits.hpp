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
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
*/