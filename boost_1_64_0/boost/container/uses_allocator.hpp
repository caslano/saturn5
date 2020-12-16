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
Z5+lkVnReO/VkhKTybIVlm9GxQ1kDoWlzPtprZhPNC2zNu7js8keoPE1KpR7fRMyGOFv6zd/PZUsGq0gs9bWCn3JDGi8vwqhqdFkRjReS+j5gV+TmRU5X/xZuQNZpiJu81cnxn+ydMhGo3OlJp4758+/GUP7rgvN6X3vqIUNPTqwti3Z7pG+8wENik21TyA7obD8oE0ky0HLy+zh0tBxZA8Uljpl4VSy12gRzC63OuS9Z+4GYaMAzN73gNpQAaqujbhGNhqN3qvQwJE6qgFZFhrtPWhwcEbfPz7ZYMhGo+sJI/63jbu2nfjJMsGFZg36NF4d6AX5WjccRLZkjG9fQoNDZdcYyVah5WZ27kmTCmSbFHGbWlRVk+1QxO2feq0b2X6FJS8JPk52Ao36Q4NbwZv/IbuoiGv7Zs4CMrciblvvGqvJPGgJzP7tvuYuWamx/j3kOt39LFmiwurlmnyeLAktF7ORF38vQZassJpx1WrTsWtEo3WvC+Ug7K/jw8h2oNF7DhokTExZTLbfWwvZ3q2dq5CdQKN1R4Pezn8ekL1X5NzTw336kw2DsG99cfXAAsN7RWg+WU8wotF9XH2ME/dxaCfQaB3Q4IUnoh+ZC43eO9Bg8bVq3vOoHLjRwHs/1gDKwypL27FkmnG+nGigurA9jEyPRucmGqifVSpHZkCLZHZoT9IpsvpooSznuWGTfyAzKXK+/lwzicyssPdjPxjILGj5mX1/5nCxTzYIrGg0Zw2hu2/O0MLG+3KiQVCH6ZfIotHyMEvtPsRNFq+wayvgFe0FyWi0fo2hArSp8aj3J6sCFjSqswmuy+SNoy+SWdGimF0fd/kpWbYirmeHtRFk69DUzObH/dyJzIlWgFni1vXtyHIUcS/qX3CSedAKMrsXmuUiC5sAUIjZ4uVxg8ji0SKYdf4quAXZf7m687iY8z8O4J9ydTedptOQI4Rx93OOZckdQu6KCKmpHKEl18oddskd62gRYZE7d47IPa6VO3K0rnL/3tTr23s+f+xjfB/Px/vzeR/f+c53pqn1JeP1RVR7XZxLXeFPVqfYOokYoapf6o7ynoQMtXehxxW+N6vBksn8VEWz7SaEOLdrbDOYdqkQmuLndHd6jN1stRoWSIbPusjE5tp2UbC5ZLhvJRMpNcq3hCWSebK4WQXVmsPSyXCt60GPn8av6QA7QYZrD5mIy/psDcskK8cs/MLxlbBsslLMfgk5kwq7KlnkwV56mIFMzXKp1nBfC9g7srIsLvDQkDzYF5ZLAD3eDX/cGlY6ifZjFuFc8l0HMzKcZ2Ti+oGe62EaMktmXocqn4NpyWowez/4qDksjKwhs3d/zmoASyGryqxeYhOlBgOZFzOX3MvzlDyX0X/MmuT1GwpTS3bpX3UuzFuy+PO31sF8JWuU3GAmzE+yxvr4IbAgMvxsgkxETns5BxZLhvOzJz3OWbpxNCyNzIXZs996u8CyyTBbMpH3fNARmIEMve5Fj6/rte4FUy0v+Qy+Nz1W2PNsBExPhnOCTNT/+MJdyZMMa5KJ315vj1byZGsG0uNT8yHflP1WlJwTZGJN1QnDYBqyGsy6dSzlBgsiw5p96HHX8E/zYRlk+KyETOwclt8bllu8JiwqcnqAst/KkjX70uPG/+4ugsWT4XpGJpYUftoHSySzKLZ+gvbOPWQPSyazZHZsXpvzsDQyF2b/SzeYw7LJHJj1yAytotRA5srsXhvfsjCzVUI4MluUMq+vUh+ZNbNdqdGlYVoyFbPPvarugPlJNnVo07ewIDI7Zn2Xz/8NFktmz8yqvFDDEqW444F5z2Epko2cZtsUliHbXP1xmIGsErPDY1vUhYnVJXPoT48=
*/