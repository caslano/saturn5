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
      BOOST_STATIC_ASSERT(( !::boost::move_upmu::missing_virtual_destructor
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
      BOOST_STATIC_ASSERT(( !::boost::move_upmu::missing_virtual_destructor
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
      BOOST_STATIC_ASSERT(( !::boost::move_upmu::missing_virtual_destructor
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
      BOOST_STATIC_ASSERT(( !::boost::move_upmu::missing_virtual_destructor
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
      BOOST_STATIC_ASSERT(( !::boost::move_upmu::missing_virtual_destructor
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
+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
*/