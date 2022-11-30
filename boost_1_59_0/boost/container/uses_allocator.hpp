//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2011-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_USES_ALLOCATOR_HPP
#define BOOST_CONTAINER_USES_ALLOCATOR_HPP

#include <boost/container/uses_allocator_fwd.hpp>
#include <boost/container/detail/type_traits.hpp>

namespace boost {
namespace container {

//! <b>Remark</b>: if a specialization constructible_with_allocator_suffix<X>::value is true, indicates that T may be constructed
//! with an allocator as its last constructor argument.  Ideally, all constructors of T (including the
//! copy and move constructors) should have a variant that accepts a final argument of
//! allocator_type.
//!
//! <b>Requires</b>: if a specialization constructible_with_allocator_suffix<X>::value is true, T must have a nested type,
//! allocator_type and at least one constructor for which allocator_type is the last
//! parameter.  If not all constructors of T can be called with a final allocator_type argument,
//! and if T is used in a context where a container must call such a constructor, then the program is
//! ill-formed.
//!
//! <code>
//!  template <class T, class Allocator = allocator<T> >
//!  class Z {
//!    public:
//!      typedef Allocator allocator_type;
//!
//!    // Default constructor with optional allocator suffix
//!    Z(const allocator_type& a = allocator_type());
//!
//!    // Copy constructor and allocator-extended copy constructor
//!    Z(const Z& zz);
//!    Z(const Z& zz, const allocator_type& a);
//! };
//!
//! // Specialize trait for class template Z
//! template <class T, class Allocator = allocator<T> >
//! struct constructible_with_allocator_suffix<Z<T,Allocator> >
//! { static const bool value = true;  };
//! </code>
//!
//! <b>Note</b>: This trait is a workaround inspired by "N2554: The Scoped A Model (Rev 2)"
//! (Pablo Halpern, 2008-02-29) to backport the scoped allocator model to C++03, as
//! in C++03 there is no mechanism to detect if a type can be constructed from arbitrary arguments.
//! Applications aiming portability with several compilers should always define this trait.
//!
//! In conforming C++11 compilers or compilers supporting SFINAE expressions
//! (when BOOST_NO_SFINAE_EXPR is NOT defined), this trait is ignored and C++11 rules will be used
//! to detect if a type should be constructed with suffix or prefix allocator arguments.
template <class T>
struct constructible_with_allocator_suffix
{  static const bool value = false; };

//! <b>Remark</b>: if a specialization constructible_with_allocator_prefix<X>::value is true, indicates that T may be constructed
//! with allocator_arg and T::allocator_type as its first two constructor arguments.
//! Ideally, all constructors of T (including the copy and move constructors) should have a variant
//! that accepts these two initial arguments.
//!
//! <b>Requires</b>: specialization constructible_with_allocator_prefix<X>::value is true, T must have a nested type,
//! allocator_type and at least one constructor for which allocator_arg_t is the first
//! parameter and allocator_type is the second parameter.  If not all constructors of T can be
//! called with these initial arguments, and if T is used in a context where a container must call such
//! a constructor, then the program is ill-formed.
//!
//! <code>
//! template <class T, class Allocator = allocator<T> >
//! class Y {
//!    public:
//!       typedef Allocator allocator_type;
//!
//!       // Default constructor with and allocator-extended default constructor
//!       Y();
//!       Y(allocator_arg_t, const allocator_type& a);
//!
//!       // Copy constructor and allocator-extended copy constructor
//!       Y(const Y& yy);
//!       Y(allocator_arg_t, const allocator_type& a, const Y& yy);
//!
//!       // Variadic constructor and allocator-extended variadic constructor
//!       template<class ...Args> Y(Args&& args...);
//!       template<class ...Args>
//!       Y(allocator_arg_t, const allocator_type& a, BOOST_FWD_REF(Args)... args);
//! };
//!
//! // Specialize trait for class template Y
//! template <class T, class Allocator = allocator<T> >
//! struct constructible_with_allocator_prefix<Y<T,Allocator> >
//! { static const bool value = true;  };
//!
//! </code>
//!
//! <b>Note</b>: This trait is a workaround inspired by "N2554: The Scoped Allocator Model (Rev 2)"
//! (Pablo Halpern, 2008-02-29) to backport the scoped allocator model to C++03, as
//! in C++03 there is no mechanism to detect if a type can be constructed from arbitrary arguments.
//! Applications aiming portability with several compilers should always define this trait.
//!
//! In conforming C++11 compilers or compilers supporting SFINAE expressions
//! (when BOOST_NO_SFINAE_EXPR is NOT defined), this trait is ignored and C++11 rules will be used
//! to detect if a type should be constructed with suffix or prefix allocator arguments.
template <class T>
struct constructible_with_allocator_prefix
{  static const bool value = false; };

#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

namespace dtl {

template<typename T, typename Allocator>
struct uses_allocator_imp
{
   // Use SFINAE (Substitution Failure Is Not An Error) to detect the
   // presence of an 'allocator_type' nested type convertilble from Allocator.
   private:
   typedef char yes_type;
   struct no_type{ char dummy[2]; };

   // Match this function if T::allocator_type exists and is
   // implicitly convertible from Allocator
   template <class U>
   static yes_type test(typename U::allocator_type);

   // Match this function if T::allocator_type exists and it's type is `erased_type`.
   template <class U, class V>
   static typename dtl::enable_if
      < dtl::is_same<typename U::allocator_type, erased_type>
      , yes_type
      >::type  test(const V&);

   // Match this function if TypeT::allocator_type does not exist or is
   // not convertible from Allocator.
   template <typename U>
   static no_type test(...);
   static Allocator alloc;  // Declared but not defined

   public:
   static const bool value = sizeof(test<T>(alloc)) == sizeof(yes_type);
};

}  //namespace dtl {

#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

//! <b>Remark</b>: Automatically detects whether T has a nested allocator_type that is convertible from
//! Allocator. Meets the BinaryTypeTrait requirements ([meta.rqmts] 20.4.1). A program may
//! specialize this type to define uses_allocator<X>::value as true for a T of user-defined type if T does not
//! have a nested allocator_type but is nonetheless constructible using the specified Allocator where either:
//! the first argument of a constructor has type allocator_arg_t and the second argument has type Alloc or
//! the last argument of a constructor has type Alloc.
//!
//! <b>Result</b>: uses_allocator<T, Allocator>::value== true if a type T::allocator_type
//! exists and either is_convertible<Alloc, T::allocator_type>::value != false or T::allocator_type
//! is an alias `erased_type`. False otherwise.
template <typename T, typename Allocator>
struct uses_allocator
   : dtl::uses_allocator_imp<T, Allocator>
{};

}} //namespace boost::container

#endif   //BOOST_CONTAINER_USES_ALLOCATOR_HPP

/* uses_allocator.hpp
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
*/