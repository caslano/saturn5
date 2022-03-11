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