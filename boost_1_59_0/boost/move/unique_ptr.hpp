//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2014. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_MOVE_UNIQUE_PTR_HPP_INCLUDED
#define BOOST_MOVE_UNIQUE_PTR_HPP_INCLUDED

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/move/detail/config_begin.hpp>
#include <boost/move/detail/workaround.hpp>  //forceinline
#include <boost/move/detail/unique_ptr_meta_utils.hpp>
#include <boost/move/default_delete.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/move/adl_move_swap.hpp>
#include <boost/static_assert.hpp>
#include <boost/assert.hpp>

#include <cstddef>   //For std::nullptr_t and std::size_t

//!\file
//! Describes the smart pointer unique_ptr, a drop-in replacement for std::unique_ptr,
//! usable also from C++03 compilers.
//!
//! Main differences from std::unique_ptr to avoid heavy dependencies,
//! specially in C++03 compilers:
//!   - <tt>operator < </tt> uses pointer <tt>operator < </tt>instead of <tt>std::less<common_type></tt>. 
//!      This avoids dependencies on <tt>std::common_type</tt> and <tt>std::less</tt>
//!      (<tt><type_traits>/<functional></tt> headers). In C++03 this avoid pulling Boost.Typeof and other
//!      cascading dependencies. As in all Boost platforms <tt>operator <</tt> on raw pointers and
//!      other smart pointers provides strict weak ordering in practice this should not be a problem for users.
//!   - assignable from literal 0 for compilers without nullptr
//!   - <tt>unique_ptr<T[]></tt> is constructible and assignable from <tt>unique_ptr<U[]></tt> if
//!      cv-less T and cv-less U are the same type and T is more CV qualified than U.

namespace boost{
// @cond
namespace move_upd {

////////////////////////////////////////////
//          deleter types
////////////////////////////////////////////
#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
template <class T>
class is_noncopyable
{
   typedef char true_t;
   class false_t { char dummy[2]; };
   template<class U> static false_t dispatch(...);
   template<class U> static true_t  dispatch(typename U::boost_move_no_copy_constructor_or_assign*);
   public:
   static const bool value = sizeof(dispatch<T>(0)) == sizeof(true_t);
};
#endif   //defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

template <class D>
struct deleter_types
{
   typedef typename bmupmu::add_lvalue_reference<D>::type            del_ref;
   typedef typename bmupmu::add_const_lvalue_reference<D>::type      del_cref;
   #ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
   typedef typename bmupmu::if_c
      < bmupmu::is_lvalue_reference<D>::value, D, del_cref >::type   deleter_arg_type1;
   typedef typename bmupmu::remove_reference<D>::type &&             deleter_arg_type2;
   #else
   typedef typename bmupmu::if_c
      < is_noncopyable<D>::value, bmupmu::nat, del_cref>::type       non_ref_deleter_arg1;
   typedef typename bmupmu::if_c< bmupmu::is_lvalue_reference<D>::value
                       , D, non_ref_deleter_arg1 >::type          deleter_arg_type1;
   typedef ::boost::rv<D> &                                       deleter_arg_type2;
   #endif
};

////////////////////////////////////////////
//          unique_ptr_data
////////////////////////////////////////////
template <class P, class D, bool = bmupmu::is_unary_function<D>::value || bmupmu::is_reference<D>::value >
struct unique_ptr_data
{
   typedef typename deleter_types<D>::deleter_arg_type1  deleter_arg_type1;
   typedef typename deleter_types<D>::del_ref            del_ref;
   typedef typename deleter_types<D>::del_cref           del_cref;

   BOOST_MOVE_FORCEINLINE unique_ptr_data() BOOST_NOEXCEPT
      : m_p(), d()
   {}

   BOOST_MOVE_FORCEINLINE explicit unique_ptr_data(P p) BOOST_NOEXCEPT
      : m_p(p), d()
   {}

   BOOST_MOVE_FORCEINLINE unique_ptr_data(P p, deleter_arg_type1 d1) BOOST_NOEXCEPT
      : m_p(p), d(d1)
   {}

   template <class U>
   BOOST_MOVE_FORCEINLINE unique_ptr_data(P p, BOOST_FWD_REF(U) d1) BOOST_NOEXCEPT
      : m_p(p), d(::boost::forward<U>(d1))
   {}

   BOOST_MOVE_FORCEINLINE del_ref deleter()       { return d; }
   BOOST_MOVE_FORCEINLINE del_cref deleter() const{ return d; }

   P m_p;
   D d;

   private:
   unique_ptr_data& operator=(const unique_ptr_data&);
   unique_ptr_data(const unique_ptr_data&);
};

template <class P, class D>
struct unique_ptr_data<P, D, false>
   : private D
{
   typedef typename deleter_types<D>::deleter_arg_type1  deleter_arg_type1;
   typedef typename deleter_types<D>::del_ref            del_ref;
   typedef typename deleter_types<D>::del_cref           del_cref;

   BOOST_MOVE_FORCEINLINE unique_ptr_data() BOOST_NOEXCEPT
      : D(), m_p()
   {}

   BOOST_MOVE_FORCEINLINE explicit unique_ptr_data(P p) BOOST_NOEXCEPT
      : D(), m_p(p)
   {}

   BOOST_MOVE_FORCEINLINE unique_ptr_data(P p, deleter_arg_type1 d1) BOOST_NOEXCEPT
      : D(d1), m_p(p)
   {}

   template <class U>
   BOOST_MOVE_FORCEINLINE unique_ptr_data(P p, BOOST_FWD_REF(U) d) BOOST_NOEXCEPT
      : D(::boost::forward<U>(d)), m_p(p)
   {}

   BOOST_MOVE_FORCEINLINE del_ref deleter()        BOOST_NOEXCEPT   {  return static_cast<del_ref>(*this);   }
   BOOST_MOVE_FORCEINLINE del_cref deleter() const BOOST_NOEXCEPT   {  return static_cast<del_cref>(*this);  }

   P m_p;

   private:
   unique_ptr_data& operator=(const unique_ptr_data&);
   unique_ptr_data(const unique_ptr_data&);
};

////////////////////////////////////////////
//          is_unique_ptr_convertible
////////////////////////////////////////////

//Although non-standard, we avoid using pointer_traits
//to avoid heavy dependencies
template <typename T>
struct get_element_type
{
   struct DefaultWrap { typedef bmupmu::natify<T> element_type; };
   template <typename X>   static char test(int, typename X::element_type*);
   template <typename X>   static int test(...);
   static const bool value = (1 == sizeof(test<T>(0, 0)));
   typedef typename bmupmu::if_c<value, T, DefaultWrap>::type::element_type type;
};

template<class T>
struct get_element_type<T*>
{
   typedef T type;
};

template<class T>
struct get_cvelement
   : bmupmu::remove_cv<typename get_element_type<T>::type>
{};

template <class P1, class P2>
struct is_same_cvelement_and_convertible
{
   typedef typename bmupmu::remove_reference<P1>::type arg1;
   typedef typename bmupmu::remove_reference<P2>::type arg2;
   static const bool same_cvless =
      bmupmu::is_same<typename get_cvelement<arg1>::type,typename get_cvelement<arg2>::type>::value;
   static const bool value = same_cvless && bmupmu::is_convertible<arg1, arg2>::value;
};

template<bool IsArray, class FromPointer, class ThisPointer>
struct is_unique_ptr_convertible
   : is_same_cvelement_and_convertible<FromPointer, ThisPointer>
{};

template<class FromPointer, class ThisPointer>
struct is_unique_ptr_convertible<false, FromPointer, ThisPointer>
   : bmupmu::is_convertible<FromPointer, ThisPointer>
{};

////////////////////////////////////////
////     enable_up_moveconv_assign
////////////////////////////////////////

template<class T, class FromPointer, class ThisPointer, class Type = bmupmu::nat>
struct enable_up_ptr
   : bmupmu::enable_if_c< is_unique_ptr_convertible
      < bmupmu::is_array<T>::value, FromPointer, ThisPointer>::value, Type>
{};

////////////////////////////////////////
////     enable_up_moveconv_assign
////////////////////////////////////////

template<class T, class D, class U, class E>
struct unique_moveconvert_assignable
{
   static const bool t_is_array = bmupmu::is_array<T>::value;
   static const bool value =
      t_is_array == bmupmu::is_array<U>::value &&
      bmupmu::extent<T>::value == bmupmu::extent<U>::value &&
      is_unique_ptr_convertible
         < t_is_array
         , typename bmupmu::pointer_type<U, E>::type, typename bmupmu::pointer_type<T, D>::type
         >::value;
};

template<class T, class D, class U, class E, std::size_t N>
struct unique_moveconvert_assignable<T[], D, U[N], E>
   : unique_moveconvert_assignable<T[], D, U[], E>
{};

template<class T, class D, class U, class E, class Type = bmupmu::nat>
struct enable_up_moveconv_assign
   : bmupmu::enable_if_c<unique_moveconvert_assignable<T, D, U, E>::value, Type>
{};

////////////////////////////////////////
////     enable_up_moveconv_constr
////////////////////////////////////////

template<class D, class E, bool IsReference = bmupmu::is_reference<D>::value>
struct unique_deleter_is_initializable
   : bmupmu::is_same<D, E>
{};

template <class T, class U>
class is_rvalue_convertible
{
   #ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
   typedef typename bmupmu::remove_reference<T>::type&& t_from;
   #else
   typedef typename bmupmu::if_c
      < ::boost::has_move_emulation_enabled<T>::value && !bmupmu::is_reference<T>::value
      , ::boost::rv<T>&
      , typename bmupmu::add_lvalue_reference<T>::type
      >::type t_from;
   #endif

   typedef char true_t;
   class false_t { char dummy[2]; };
   static false_t dispatch(...);
   static true_t  dispatch(U);
   static t_from trigger();
   public:
   static const bool value = sizeof(dispatch(trigger())) == sizeof(true_t);
};

template<class D, class E>
struct unique_deleter_is_initializable<D, E, false>
{
   #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
   //Clang has some problems with is_rvalue_convertible with non-copyable types
   //so use intrinsic if available
   #if defined(BOOST_CLANG)
      #if __has_feature(is_convertible_to)
      static const bool value = __is_convertible_to(E, D);
      #else
      static const bool value = is_rvalue_convertible<E, D>::value;
      #endif
   #else
   static const bool value = is_rvalue_convertible<E, D>::value;
   #endif

   #else //!defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
   //No hope for compilers with move emulation for now. In several compilers is_convertible
   // leads to errors, so just move the Deleter and see if the conversion works
   static const bool value = true;  /*is_rvalue_convertible<E, D>::value*/
   #endif
};

template<class T, class D, class U, class E, class Type = bmupmu::nat>
struct enable_up_moveconv_constr
   : bmupmu::enable_if_c
      < unique_moveconvert_assignable<T, D, U, E>::value && unique_deleter_is_initializable<D, E>::value
      , Type>
{};

}  //namespace move_upd {
// @endcond

namespace movelib {

//! A unique pointer is an object that owns another object and
//! manages that other object through a pointer.
//! 
//! More precisely, a unique pointer is an object u that stores a pointer to a second object p and will dispose
//! of p when u is itself destroyed (e.g., when leaving block scope). In this context, u is said to own p.
//! 
//! The mechanism by which u disposes of p is known as p's associated deleter, a function object whose correct
//! invocation results in p's appropriate disposition (typically its deletion).
//! 
//! Let the notation u.p denote the pointer stored by u, and let u.d denote the associated deleter. Upon request,
//! u can reset (replace) u.p and u.d with another pointer and deleter, but must properly dispose of its owned
//! object via the associated deleter before such replacement is considered completed.
//! 
//! Additionally, u can, upon request, transfer ownership to another unique pointer u2. Upon completion of
//! such a transfer, the following postconditions hold:
//!   - u2.p is equal to the pre-transfer u.p,
//!   - u.p is equal to nullptr, and
//!   - if the pre-transfer u.d maintained state, such state has been transferred to u2.d.
//! 
//! As in the case of a reset, u2 must properly dispose of its pre-transfer owned object via the pre-transfer
//! associated deleter before the ownership transfer is considered complete.
//! 
//! Each object of a type U instantiated from the unique_ptr template specified in this subclause has the strict
//! ownership semantics, specified above, of a unique pointer. In partial satisfaction of these semantics, each
//! such U is MoveConstructible and MoveAssignable, but is not CopyConstructible nor CopyAssignable.
//! The template parameter T of unique_ptr may be an incomplete type.
//! 
//! The uses of unique_ptr include providing exception safety for dynamically allocated memory, passing
//! ownership of dynamically allocated memory to a function, and returning dynamically allocated memory from
//! a function.
//!
//! If T is an array type (e.g. unique_ptr<MyType[]>) the interface is slightly altered:
//!   - Pointers to types derived from T are rejected by the constructors, and by reset.
//!   - The observers <tt>operator*</tt> and <tt>operator-></tt> are not provided.
//!   - The indexing observer <tt>operator[]</tt> is provided.
//!
//! \tparam T Provides the type of the stored pointer.
//! \tparam D The deleter type:
//!   -  The default type for the template parameter D is default_delete. A client-supplied template argument
//!      D shall be a function object type, lvalue-reference to function, or lvalue-reference to function object type
//!      for which, given a value d of type D and a value ptr of type unique_ptr<T, D>::pointer, the expression
//!      d(ptr) is valid and has the effect of disposing of the pointer as appropriate for that deleter.
//!   -  If the deleter's type D is not a reference type, D shall satisfy the requirements of Destructible.
//!   -  If the type <tt>remove_reference<D>::type::pointer</tt> exists, it shall satisfy the requirements of NullablePointer.
template <class T, class D = default_delete<T> >
class unique_ptr
{
   #if defined(BOOST_MOVE_DOXYGEN_INVOKED)
   public:
   unique_ptr(const unique_ptr&) = delete;
   unique_ptr& operator=(const unique_ptr&) = delete;
   private:
   #else
   BOOST_MOVABLE_BUT_NOT_COPYABLE(unique_ptr)

   typedef bmupmu::pointer_type<T, D >                            pointer_type_obtainer;
   typedef bmupd::unique_ptr_data
      <typename pointer_type_obtainer::type, D>                data_type;
   typedef typename bmupd::deleter_types<D>::deleter_arg_type1 deleter_arg_type1;
   typedef typename bmupd::deleter_types<D>::deleter_arg_type2 deleter_arg_type2;
   data_type m_data;
   #endif

   public:
   //! If the type <tt>remove_reference<D>::type::pointer</tt> exists, then it shall be a
   //! synonym for <tt>remove_reference<D>::type::pointer</tt>. Otherwise it shall be a
   //! synonym for T*.
   typedef typename BOOST_MOVE_SEEDOC(pointer_type_obtainer::type) pointer;
   //! If T is an array type, then element_type is equal to T. Otherwise, if T is a type
   //! in the form U[], element_type is equal to U.
   typedef typename BOOST_MOVE_SEEDOC(bmupmu::remove_extent<T>::type) element_type;
   typedef D deleter_type;

   //! <b>Requires</b>: D shall satisfy the requirements of DefaultConstructible, and
   //!   that construction shall not throw an exception.
   //!
   //! <b>Effects</b>: Constructs a unique_ptr object that owns nothing, value-initializing the
   //!   stored pointer and the stored deleter.
   //!
   //! <b>Postconditions</b>: <tt>get() == nullptr</tt>. <tt>get_deleter()</tt> returns a reference to the stored deleter.
   //!
   //! <b>Remarks</b>: If this constructor is instantiated with a pointer type or reference type
   //!   for the template argument D, the program is ill-formed.   
   BOOST_MOVE_FORCEINLINE BOOST_CONSTEXPR unique_ptr() BOOST_NOEXCEPT
      : m_data()
   {
      //If this constructor is instantiated with a pointer type or reference type
      //for the template argument D, the program is ill-formed.
      BOOST_STATIC_ASSERT(!bmupmu::is_pointer<D>::value);
      BOOST_STATIC_ASSERT(!bmupmu::is_reference<D>::value);
   }

   //! <b>Effects</b>: Same as <tt>unique_ptr()</tt> (default constructor).
   //! 
   BOOST_MOVE_FORCEINLINE BOOST_CONSTEXPR unique_ptr(BOOST_MOVE_DOC0PTR(bmupd::nullptr_type)) BOOST_NOEXCEPT
      : m_data()
   {
      //If this constructor is instantiated with a pointer type or reference type
      //for the template argument D, the program is ill-formed.
      BOOST_STATIC_ASSERT(!bmupmu::is_pointer<D>::value);
      BOOST_STATIC_ASSERT(!bmupmu::is_reference<D>::value);
   }

   //! <b>Requires</b>: D shall satisfy the requirements of DefaultConstructible, and
   //!   that construction shall not throw an exception.
   //!
   //! <b>Effects</b>: Constructs a unique_ptr which owns p, initializing the stored pointer 
   //!   with p and value initializing the stored deleter.
   //!
   //! <b>Postconditions</b>: <tt>get() == p</tt>. <tt>get_deleter()</tt> returns a reference to the stored deleter.
   //!
   //! <b>Remarks</b>: If this constructor is instantiated with a pointer type or reference type
   //!   for the template argument D, the program is ill-formed.
   //!   This constructor shall not participate in overload resolution unless:
   //!      - If T is not an array type and Pointer is implicitly convertible to pointer.
   //!      - If T is an array type and Pointer is a more CV qualified pointer to element_type.
   template<class Pointer>
   BOOST_MOVE_FORCEINLINE explicit unique_ptr(Pointer p
      BOOST_MOVE_DOCIGN(BOOST_MOVE_I typename bmupd::enable_up_ptr<T BOOST_MOVE_I Pointer BOOST_MOVE_I pointer>::type* =0)
                 ) BOOST_NOEXCEPT
      : m_data(p)
   {
      //If T is not an array type, element_type_t<Pointer> derives from T
      //it uses the default deleter and T has no virtual destructor, then you have a problem
      BOOST_STATIC_ASSERT(( !bmupd::missing_virtual_destructor
                            <D, typename bmupd::get_element_type<Pointer>::type>::value ));
      //If this constructor is instantiated with a pointer type or reference type
      //for the template argument D, the program is ill-formed.
      BOOST_STATIC_ASSERT(!bmupmu::is_pointer<D>::value);
      BOOST_STATIC_ASSERT(!bmupmu::is_reference<D>::value);
   }

   //!The signature of this constructor depends upon whether D is a reference type.
   //!   - If D is non-reference type A, then the signature is <tt>unique_ptr(pointer p, const A& d)</tt>.
   //!   - If D is an lvalue-reference type A&, then the signature is <tt>unique_ptr(pointer p, A& d)</tt>.
   //!   - If D is an lvalue-reference type const A&, then the signature is <tt>unique_ptr(pointer p, const A& d)</tt>.
   //!
   //!
   //! <b>Requires</b>: Either
   //!   - D is not an lvalue-reference type and d is an lvalue or const rvalue. 
   //!         D shall satisfy the requirements of CopyConstructible, and the copy constructor of D
   //!         shall not throw an exception. This unique_ptr will hold a copy of d.
   //!   - D is an lvalue-reference type and d is an lvalue. the type which D references need not be CopyConstructible nor
   //!      MoveConstructible. This unique_ptr will hold a D which refers to the lvalue d.
   //!
   //! <b>Effects</b>: Constructs a unique_ptr object which owns p, initializing the stored pointer with p and
   //!   initializing the deleter as described above.
   //! 
   //! <b>Postconditions</b>: <tt>get() == p</tt>. <tt>get_deleter()</tt> returns a reference to the stored deleter. If D is a
   //!   reference type then <tt>get_deleter()</tt> returns a reference to the lvalue d.
   //!
   //! <b>Remarks</b>: This constructor shall not participate in overload resolution unless:
   //!      - If T is not an array type and Pointer is implicitly convertible to pointer.
   //!      - If T is an array type and Pointer is a more CV qualified pointer to element_type.
   template<class Pointer>
   BOOST_MOVE_FORCEINLINE unique_ptr(Pointer p, BOOST_MOVE_SEEDOC(deleter_arg_type1) d1
      BOOST_MOVE_DOCIGN(BOOST_MOVE_I typename bmupd::enable_up_ptr<T BOOST_MOVE_I Pointer BOOST_MOVE_I pointer>::type* =0)
              ) BOOST_NOEXCEPT
      : m_data(p, d1)
   {
      //If T is not an array type, element_type_t<Pointer> derives from T
      //it uses the default deleter and T has no virtual destructor, then you have a problem
      BOOST_STATIC_ASSERT(( !bmupd::missing_virtual_destructor
                            <D, typename bmupd::get_element_type<Pointer>::type>::value ));
   }

   //! <b>Effects</b>: Same effects as <tt>template<class Pointer> unique_ptr(Pointer p, deleter_arg_type1 d1)</tt>
   //!   and additionally <tt>get() == nullptr</tt>
   BOOST_MOVE_FORCEINLINE unique_ptr(BOOST_MOVE_DOC0PTR(bmupd::nullptr_type), BOOST_MOVE_SEEDOC(deleter_arg_type1) d1) BOOST_NOEXCEPT
      : m_data(pointer(), d1)
   {}

   //! The signature of this constructor depends upon whether D is a reference type.
   //!   - If D is non-reference type A, then the signature is <tt>unique_ptr(pointer p, A&& d)</tt>.
   //!   - If D is an lvalue-reference type A&, then the signature is <tt>unique_ptr(pointer p, A&& d)</tt>.
   //!   - If D is an lvalue-reference type const A&, then the signature is <tt>unique_ptr(pointer p, const A&& d)</tt>.
   //!
   //! <b>Requires</b>: Either
   //!   - D is not an lvalue-reference type and d is a non-const rvalue. D
   //!      shall satisfy the requirements of MoveConstructible, and the move constructor
   //!      of D shall not throw an exception. This unique_ptr will hold a value move constructed from d.
   //!   - D is an lvalue-reference type and d is an rvalue, the program is ill-formed.
   //!
   //! <b>Effects</b>: Constructs a unique_ptr object which owns p, initializing the stored pointer with p and
   //!   initializing the deleter as described above.
   //! 
   //! <b>Postconditions</b>: <tt>get() == p</tt>. <tt>get_deleter()</tt> returns a reference to the stored deleter. If D is a
   //!   reference type then <tt>get_deleter()</tt> returns a reference to the lvalue d.
   //!
   //! <b>Remarks</b>: This constructor shall not participate in overload resolution unless:
   //!      - If T is not an array type and Pointer is implicitly convertible to pointer.
   //!      - If T is an array type and Pointer is a more CV qualified pointer to element_type.
   template<class Pointer>
   BOOST_MOVE_FORCEINLINE unique_ptr(Pointer p, BOOST_MOVE_SEEDOC(deleter_arg_type2) d2
      BOOST_MOVE_DOCIGN(BOOST_MOVE_I typename bmupd::enable_up_ptr<T BOOST_MOVE_I Pointer BOOST_MOVE_I pointer>::type* =0)
             ) BOOST_NOEXCEPT
      : m_data(p, ::boost::move(d2))
   {
      //If T is not an array type, element_type_t<Pointer> derives from T
      //it uses the default deleter and T has no virtual destructor, then you have a problem
      BOOST_STATIC_ASSERT(( !bmupd::missing_virtual_destructor
                            <D, typename bmupd::get_element_type<Pointer>::type>::value ));
   }

   //! <b>Effects</b>: Same effects as <tt>template<class Pointer> unique_ptr(Pointer p, deleter_arg_type2 d2)</tt>
   //!   and additionally <tt>get() == nullptr</tt>
   BOOST_MOVE_FORCEINLINE unique_ptr(BOOST_MOVE_DOC0PTR(bmupd::nullptr_type), BOOST_MOVE_SEEDOC(deleter_arg_type2) d2) BOOST_NOEXCEPT
      : m_data(pointer(), ::boost::move(d2))
   {}

   //! <b>Requires</b>: If D is not a reference type, D shall satisfy the requirements of MoveConstructible.
   //! Construction of the deleter from an rvalue of type D shall not throw an exception.
   //! 
   //! <b>Effects</b>: Constructs a unique_ptr by transferring ownership from u to *this. If D is a reference type,
   //! this deleter is copy constructed from u's deleter; otherwise, this deleter is move constructed from u's
   //! deleter.
   //! 
   //! <b>Postconditions</b>: <tt>get()</tt> yields the value u.get() yielded before the construction. <tt>get_deleter()</tt>
   //! returns a reference to the stored deleter that was constructed from u.get_deleter(). If D is a
   //! reference type then <tt>get_deleter()</tt> and <tt>u.get_deleter()</tt> both reference the same lvalue deleter.
   BOOST_MOVE_FORCEINLINE unique_ptr(BOOST_RV_REF(unique_ptr) u) BOOST_NOEXCEPT
      : m_data(u.release(), ::boost::move_if_not_lvalue_reference<D>(u.get_deleter()))
   {}

   //! <b>Requires</b>: If E is not a reference type, construction of the deleter from an rvalue of type E shall be
   //!   well formed and shall not throw an exception. Otherwise, E is a reference type and construction of the
   //!   deleter from an lvalue of type E shall be well formed and shall not throw an exception.
   //!
   //! <b>Remarks</b>: This constructor shall not participate in overload resolution unless:
   //!   - <tt>unique_ptr<U, E>::pointer</tt> is implicitly convertible to pointer,
   //!   - U is not an array type, and
   //!   - either D is a reference type and E is the same type as D, or D is not a reference type and E is
   //!      implicitly convertible to D.
   //!
   //! <b>Effects</b>: Constructs a unique_ptr by transferring ownership from u to *this. If E is a reference type,
   //!   this deleter is copy constructed from u's deleter; otherwise, this deleter is move constructed from u's deleter.
   //!
   //! <b>Postconditions</b>: <tt>get()</tt> yields the value <tt>u.get()</tt> yielded before the construction. <tt>get_deleter()</tt>
   //!   returns a reference to the stored deleter that was constructed from <tt>u.get_deleter()</tt>.
   template <class U, class E>
   BOOST_MOVE_FORCEINLINE unique_ptr( BOOST_RV_REF_BEG_IF_CXX11 unique_ptr<U, E> BOOST_RV_REF_END_IF_CXX11 u
      BOOST_MOVE_DOCIGN(BOOST_MOVE_I typename bmupd::enable_up_moveconv_constr<T BOOST_MOVE_I D BOOST_MOVE_I U BOOST_MOVE_I E>::type* =0)
      ) BOOST_NOEXCEPT
      : m_data(u.release(), ::boost::move_if_not_lvalue_reference<E>(u.get_deleter()))
   {
      //If T is not an array type, U derives from T
      //it uses the default deleter and T has no virtual destructor, then you have a problem
      BOOST_STATIC_ASSERT(( !bmupd::missing_virtual_destructor
                            <D, typename unique_ptr<U, E>::pointer>::value ));
   }

   //! <b>Requires</b>: The expression <tt>get_deleter()(get())</tt> shall be well formed, shall have well-defined behavior,
   //!   and shall not throw exceptions.
   //!
   //! <b>Effects</b>: If <tt>get() == nullpt1r</tt> there are no effects. Otherwise <tt>get_deleter()(get())</tt>.
   //!
   //! <b>Note</b>: The use of default_delete requires T to be a complete type
   ~unique_ptr()
   {  if(m_data.m_p) m_data.deleter()(m_data.m_p);   }

   //! <b>Requires</b>: If D is not a reference type, D shall satisfy the requirements of MoveAssignable
   //!   and assignment of the deleter from an rvalue of type D shall not throw an exception. Otherwise, D
   //!   is a reference type; <tt>remove_reference<D>::type</tt> shall satisfy the CopyAssignable requirements and
   //!   assignment of the deleter from an lvalue of type D shall not throw an exception.
   //!
   //! <b>Effects</b>: Transfers ownership from u to *this as if by calling <tt>reset(u.release())</tt> followed
   //!   by <tt>get_deleter() = std::forward<D>(u.get_deleter())</tt>.
   //!
   //! <b>Returns</b>: *this.
   unique_ptr& operator=(BOOST_RV_REF(unique_ptr) u) BOOST_NOEXCEPT
   {
      this->reset(u.release());
      m_data.deleter() = ::boost::move_if_not_lvalue_reference<D>(u.get_deleter());
      return *this;
   }

   //! <b>Requires</b>: If E is not a reference type, assignment of the deleter from an rvalue of type E shall be
   //!   well-formed and shall not throw an exception. Otherwise, E is a reference type and assignment of the
   //!   deleter from an lvalue of type E shall be well-formed and shall not throw an exception.
   //!
   //! <b>Remarks</b>: This operator shall not participate in overload resolution unless:
   //!   - <tt>unique_ptr<U, E>::pointer</tt> is implicitly convertible to pointer and
   //!   - U is not an array type.
   //!
   //! <b>Effects</b>: Transfers ownership from u to *this as if by calling <tt>reset(u.release())</tt> followed by
   //!   <tt>get_deleter() = std::forward<E>(u.get_deleter())</tt>.
   //!
   //! <b>Returns</b>: *this.
   template <class U, class E>
   BOOST_MOVE_DOC1ST(unique_ptr&, typename bmupd::enable_up_moveconv_assign
         <T BOOST_MOVE_I D BOOST_MOVE_I U BOOST_MOVE_I E BOOST_MOVE_I unique_ptr &>::type)
      operator=(BOOST_RV_REF_BEG unique_ptr<U, E> BOOST_RV_REF_END u) BOOST_NOEXCEPT
   {
      this->reset(u.release());
      m_data.deleter() = ::boost::move_if_not_lvalue_reference<E>(u.get_deleter());
      return *this;
   }

   //! <b>Effects</b>: <tt>reset()</tt>.
   //!
   //! <b>Postcondition</b>: <tt>get() == nullptr</tt>
   //!
   //! <b>Returns</b>: *this.
   unique_ptr& operator=(BOOST_MOVE_DOC0PTR(bmupd::nullptr_type)) BOOST_NOEXCEPT
   {  this->reset(); return *this;  }

   //! <b>Requires</b>: <tt>get() != nullptr</tt>.
   //!
   //! <b>Returns</b>: <tt>*get()</tt>.
   //!
   //! <b>Remarks</b: If T is an array type, the program is ill-formed.
   BOOST_MOVE_DOC1ST(element_type&, typename bmupmu::add_lvalue_reference<element_type>::type)
      operator*() const BOOST_NOEXCEPT
   {
      BOOST_STATIC_ASSERT((!bmupmu::is_array<T>::value));
      return *m_data.m_p;
   }

   //! <b>Requires</b>: i < the number of elements in the array to which the stored pointer points.
   //!
   //! <b>Returns</b>: <tt>get()[i]</tt>.
   //!
   //! <b>Remarks</b: If T is not an array type, the program is ill-formed.
   BOOST_MOVE_FORCEINLINE BOOST_MOVE_DOC1ST(element_type&, typename bmupmu::add_lvalue_reference<element_type>::type)
      operator[](std::size_t i) const BOOST_NOEXCEPT
   {
      BOOST_ASSERT( bmupmu::extent<T>::value == 0 || i < bmupmu::extent<T>::value );
      BOOST_ASSERT(m_data.m_p);
      return m_data.m_p[i];
   }

   //! <b>Requires</b>: <tt>get() != nullptr</tt>.
   //!
   //! <b>Returns</b>: <tt>get()</tt>.
   //!
   //! <b>Note</b>: use typically requires that T be a complete type.
   //!
   //! <b>Remarks</b: If T is an array type, the program is ill-formed.
   BOOST_MOVE_FORCEINLINE pointer operator->() const BOOST_NOEXCEPT
   {
      BOOST_STATIC_ASSERT((!bmupmu::is_array<T>::value));
      BOOST_ASSERT(m_data.m_p);
      return m_data.m_p;
   }

   //! <b>Returns</b>: The stored pointer.
   //!
   BOOST_MOVE_FORCEINLINE pointer get() const BOOST_NOEXCEPT
   {  return m_data.m_p;  }

   //! <b>Returns</b>: A reference to the stored deleter.
   //!
   BOOST_MOVE_FORCEINLINE BOOST_MOVE_DOC1ST(D&, typename bmupmu::add_lvalue_reference<D>::type)
      get_deleter() BOOST_NOEXCEPT
   {  return m_data.deleter();  }   

   //! <b>Returns</b>: A reference to the stored deleter.
   //!
   BOOST_MOVE_FORCEINLINE BOOST_MOVE_DOC1ST(const D&, typename bmupmu::add_const_lvalue_reference<D>::type)
      get_deleter() const BOOST_NOEXCEPT
   {  return m_data.deleter();  }

   #ifdef BOOST_MOVE_DOXYGEN_INVOKED
   //! <b>Returns</b>: Returns: get() != nullptr.
   //!
   BOOST_MOVE_FORCEINLINE explicit operator bool
   #else
   BOOST_MOVE_FORCEINLINE operator bmupd::explicit_bool_arg
   #endif
      ()const BOOST_NOEXCEPT
   {
      return m_data.m_p
         ? &bmupd::bool_conversion::for_bool
         : bmupd::explicit_bool_arg(0);
   }

   //! <b>Postcondition</b>: <tt>get() == nullptr</tt>.
   //!
   //! <b>Returns</b>: The value <tt>get()</tt> had at the start of the call to release.   
   BOOST_MOVE_FORCEINLINE pointer release() BOOST_NOEXCEPT
   {
      const pointer tmp = m_data.m_p;
      m_data.m_p = pointer();
      return tmp;
   }

   //! <b>Requires</b>: The expression <tt>get_deleter()(get())</tt> shall be well formed, shall have well-defined behavior,
   //!   and shall not throw exceptions.
   //!
   //! <b>Effects</b>: assigns p to the stored pointer, and then if the old value of the stored pointer, old_p, was not
   //!   equal to nullptr, calls <tt>get_deleter()(old_p)</tt>. Note: The order of these operations is significant
   //!   because the call to <tt>get_deleter()</tt> may destroy *this.
   //!
   //! <b>Postconditions</b>: <tt>get() == p</tt>. Note: The postcondition does not hold if the call to <tt>get_deleter()</tt>
   //!   destroys *this since <tt>this->get()</tt> is no longer a valid expression.
   //!
   //! <b>Remarks</b>: This constructor shall not participate in overload resolution unless:
   //!      - If T is not an array type and Pointer is implicitly convertible to pointer.
   //!      - If T is an array type and Pointer is a more CV qualified pointer to element_type.
   template<class Pointer>
   BOOST_MOVE_DOC1ST(void, typename bmupd::enable_up_ptr<T BOOST_MOVE_I Pointer BOOST_MOVE_I pointer BOOST_MOVE_I void>::type)
      reset(Pointer p) BOOST_NOEXCEPT
   {
      //If T is not an array type, element_type_t<Pointer> derives from T
      //it uses the default deleter and T has no virtual destructor, then you have a problem
      BOOST_STATIC_ASSERT(( !bmupd::missing_virtual_destructor
                            <D, typename bmupd::get_element_type<Pointer>::type>::value ));
      pointer tmp = m_data.m_p;
      m_data.m_p = p;
      if(tmp) m_data.deleter()(tmp);
   }

   //! <b>Requires</b>: The expression <tt>get_deleter()(get())</tt> shall be well formed, shall have well-defined behavior,
   //!   and shall not throw exceptions.
   //!
   //! <b>Effects</b>: assigns nullptr to the stored pointer, and then if the old value of the stored pointer, old_p, was not
   //!   equal to nullptr, calls <tt>get_deleter()(old_p)</tt>. Note: The order of these operations is significant
   //!   because the call to <tt>get_deleter()</tt> may destroy *this.
   //!
   //! <b>Postconditions</b>: <tt>get() == p</tt>. Note: The postcondition does not hold if the call to <tt>get_deleter()</tt>
   //!   destroys *this since <tt>this->get()</tt> is no longer a valid expression.
   void reset() BOOST_NOEXCEPT
   {  this->reset(pointer());  }

   //! <b>Effects</b>: Same as <tt>reset()</tt>
   //! 
   void reset(BOOST_MOVE_DOC0PTR(bmupd::nullptr_type)) BOOST_NOEXCEPT
   {  this->reset(); }

   //! <b>Requires</b>: <tt>get_deleter()</tt> shall be swappable and shall not throw an exception under swap.
   //!
   //! <b>Effects</b>: Invokes swap on the stored pointers and on the stored deleters of *this and u.
   void swap(unique_ptr& u) BOOST_NOEXCEPT
   {
      ::boost::adl_move_swap(m_data.m_p, u.m_data.m_p);
      ::boost::adl_move_swap(m_data.deleter(), u.m_data.deleter());
   }
};

//! <b>Effects</b>: Calls <tt>x.swap(y)</tt>.
//!
template <class T, class D>
BOOST_MOVE_FORCEINLINE void swap(unique_ptr<T, D> &x, unique_ptr<T, D> &y) BOOST_NOEXCEPT
{  x.swap(y); }

//! <b>Returns</b>: <tt>x.get() == y.get()</tt>.
//!
template <class T1, class D1, class T2, class D2>
BOOST_MOVE_FORCEINLINE bool operator==(const unique_ptr<T1, D1> &x, const unique_ptr<T2, D2> &y)
{  return x.get() == y.get(); }

//! <b>Returns</b>: <tt>x.get() != y.get()</tt>.
//!
template <class T1, class D1, class T2, class D2>
BOOST_MOVE_FORCEINLINE bool operator!=(const unique_ptr<T1, D1> &x, const unique_ptr<T2, D2> &y)
{  return x.get() != y.get(); }

//! <b>Returns</b>: x.get() < y.get().
//!
//! <b>Remarks</b>: This comparison shall induce a
//!   strict weak ordering betwen pointers.
template <class T1, class D1, class T2, class D2>
BOOST_MOVE_FORCEINLINE bool operator<(const unique_ptr<T1, D1> &x, const unique_ptr<T2, D2> &y)
{  return x.get() < y.get();  }

//! <b>Returns</b>: !(y < x).
//!
template <class T1, class D1, class T2, class D2>
BOOST_MOVE_FORCEINLINE bool operator<=(const unique_ptr<T1, D1> &x, const unique_ptr<T2, D2> &y)
{  return !(y < x);  }

//! <b>Returns</b>: y < x.
//!
template <class T1, class D1, class T2, class D2>
BOOST_MOVE_FORCEINLINE bool operator>(const unique_ptr<T1, D1> &x, const unique_ptr<T2, D2> &y)
{  return y < x;  }

//! <b>Returns</b>:!(x < y).
//!
template <class T1, class D1, class T2, class D2>
BOOST_MOVE_FORCEINLINE bool operator>=(const unique_ptr<T1, D1> &x, const unique_ptr<T2, D2> &y)
{  return !(x < y);  }

//! <b>Returns</b>:!x.
//!
template <class T, class D>
BOOST_MOVE_FORCEINLINE bool operator==(const unique_ptr<T, D> &x, BOOST_MOVE_DOC0PTR(bmupd::nullptr_type)) BOOST_NOEXCEPT
{  return !x;  }

//! <b>Returns</b>:!x.
//!
template <class T, class D>
BOOST_MOVE_FORCEINLINE bool operator==(BOOST_MOVE_DOC0PTR(bmupd::nullptr_type), const unique_ptr<T, D> &x) BOOST_NOEXCEPT
{  return !x;  }

//! <b>Returns</b>: (bool)x.
//!
template <class T, class D>
BOOST_MOVE_FORCEINLINE bool operator!=(const unique_ptr<T, D> &x, BOOST_MOVE_DOC0PTR(bmupd::nullptr_type)) BOOST_NOEXCEPT
{  return !!x;  }

//! <b>Returns</b>: (bool)x.
//!
template <class T, class D>
BOOST_MOVE_FORCEINLINE bool operator!=(BOOST_MOVE_DOC0PTR(bmupd::nullptr_type), const unique_ptr<T, D> &x) BOOST_NOEXCEPT
{  return !!x;  }

//! <b>Requires</b>: <tt>operator </tt> shall induce a strict weak ordering on unique_ptr<T, D>::pointer values.
//!
//! <b>Returns</b>: Returns <tt>x.get() < pointer()</tt>.
template <class T, class D>
BOOST_MOVE_FORCEINLINE bool operator<(const unique_ptr<T, D> &x, BOOST_MOVE_DOC0PTR(bmupd::nullptr_type))
{  return x.get() < typename unique_ptr<T, D>::pointer();  }

//! <b>Requires</b>: <tt>operator </tt> shall induce a strict weak ordering on unique_ptr<T, D>::pointer values.
//!
//! <b>Returns</b>: Returns <tt>pointer() < x.get()</tt>.
template <class T, class D>
BOOST_MOVE_FORCEINLINE bool operator<(BOOST_MOVE_DOC0PTR(bmupd::nullptr_type), const unique_ptr<T, D> &x)
{  return typename unique_ptr<T, D>::pointer() < x.get();  }

//! <b>Returns</b>: <tt>nullptr < x</tt>.
//!
template <class T, class D>
BOOST_MOVE_FORCEINLINE bool operator>(const unique_ptr<T, D> &x, BOOST_MOVE_DOC0PTR(bmupd::nullptr_type))
{  return x.get() > typename unique_ptr<T, D>::pointer();  }

//! <b>Returns</b>: <tt>x < nullptr</tt>.
//!
template <class T, class D>
BOOST_MOVE_FORCEINLINE bool operator>(BOOST_MOVE_DOC0PTR(bmupd::nullptr_type), const unique_ptr<T, D> &x)
{  return typename unique_ptr<T, D>::pointer() > x.get();  }

//! <b>Returns</b>: <tt>!(nullptr < x)</tt>.
//!
template <class T, class D>
BOOST_MOVE_FORCEINLINE bool operator<=(const unique_ptr<T, D> &x, BOOST_MOVE_DOC0PTR(bmupd::nullptr_type))
{  return !(bmupd::nullptr_type() < x);  }

//! <b>Returns</b>: <tt>!(x < nullptr)</tt>.
//!
template <class T, class D>
BOOST_MOVE_FORCEINLINE bool operator<=(BOOST_MOVE_DOC0PTR(bmupd::nullptr_type), const unique_ptr<T, D> &x)
{  return !(x < bmupd::nullptr_type());  }

//! <b>Returns</b>: <tt>!(x < nullptr)</tt>.
//!
template <class T, class D>
BOOST_MOVE_FORCEINLINE bool operator>=(const unique_ptr<T, D> &x, BOOST_MOVE_DOC0PTR(bmupd::nullptr_type))
{  return !(x < bmupd::nullptr_type());  }

//! <b>Returns</b>: <tt>!(nullptr < x)</tt>.
//!
template <class T, class D>
BOOST_MOVE_FORCEINLINE bool operator>=(BOOST_MOVE_DOC0PTR(bmupd::nullptr_type), const unique_ptr<T, D> &x)
{  return !(bmupd::nullptr_type() < x);  }

}  //namespace movelib {
}  //namespace boost{

#include <boost/move/detail/config_end.hpp>

#endif   //#ifndef BOOST_MOVE_UNIQUE_PTR_HPP_INCLUDED

/* unique_ptr.hpp
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
*/