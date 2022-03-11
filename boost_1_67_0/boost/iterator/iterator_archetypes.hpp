// (C) Copyright Jeremy Siek 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ITERATOR_ARCHETYPES_HPP
#define BOOST_ITERATOR_ARCHETYPES_HPP

#include <boost/iterator/iterator_categories.hpp>
#include <boost/operators.hpp>
#include <boost/static_assert.hpp>

#include <boost/iterator/detail/facade_iterator_category.hpp>

#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_cv.hpp>

#include <boost/concept_archetype.hpp>

#include <boost/mpl/bitand.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/identity.hpp>

#include <cstddef>

namespace boost {
namespace iterators {

template <class Value, class AccessCategory>
struct access_archetype;

template <class Derived, class Value, class AccessCategory, class TraversalCategory>
struct traversal_archetype;

namespace archetypes
{
  enum {
      readable_iterator_bit = 1
    , writable_iterator_bit = 2
    , swappable_iterator_bit = 4
    , lvalue_iterator_bit = 8
  };

  // Not quite tags, since dispatching wouldn't work.
  typedef mpl::int_<readable_iterator_bit>::type readable_iterator_t;
  typedef mpl::int_<writable_iterator_bit>::type writable_iterator_t;

  typedef mpl::int_<
      (readable_iterator_bit|writable_iterator_bit)
          >::type readable_writable_iterator_t;

  typedef mpl::int_<
      (readable_iterator_bit|lvalue_iterator_bit)
          >::type readable_lvalue_iterator_t;

  typedef mpl::int_<
      (lvalue_iterator_bit|writable_iterator_bit)
          >::type writable_lvalue_iterator_t;

  typedef mpl::int_<swappable_iterator_bit>::type swappable_iterator_t;
  typedef mpl::int_<lvalue_iterator_bit>::type lvalue_iterator_t;

  template <class Derived, class Base>
  struct has_access
    : mpl::equal_to<
          mpl::bitand_<Derived,Base>
        , Base
      >
  {};
}

namespace detail
{
  template <class T>
  struct assign_proxy
  {
      assign_proxy& operator=(T) { return *this; }
  };

  template <class T>
  struct read_proxy
  {
      operator T() { return static_object<T>::get(); }
  };

  template <class T>
  struct read_write_proxy
    : read_proxy<T> // Use to inherit from assign_proxy, but that doesn't work. -JGS
  {
      read_write_proxy& operator=(T) { return *this; }
  };

  template <class T>
  struct arrow_proxy
  {
      T const* operator->() const { return 0; }
  };

  struct no_operator_brackets {};

  template <class ValueType>
  struct readable_operator_brackets
  {
      read_proxy<ValueType> operator[](std::ptrdiff_t n) const { return read_proxy<ValueType>(); }
  };

  template <class ValueType>
  struct writable_operator_brackets
  {
      read_write_proxy<ValueType> operator[](std::ptrdiff_t n) const { return read_write_proxy<ValueType>(); }
  };

  template <class Value, class AccessCategory, class TraversalCategory>
  struct operator_brackets
    : mpl::eval_if<
          is_convertible<TraversalCategory, random_access_traversal_tag>
        , mpl::eval_if<
              archetypes::has_access<
                  AccessCategory
                , archetypes::writable_iterator_t
              >
            , mpl::identity<writable_operator_brackets<Value> >
            , mpl::if_<
                  archetypes::has_access<
                      AccessCategory
                    , archetypes::readable_iterator_t
                  >
                , readable_operator_brackets<Value>
                , no_operator_brackets
              >
          >
        , mpl::identity<no_operator_brackets>
      >::type
  {};

  template <class TraversalCategory>
  struct traversal_archetype_impl
  {
      template <class Derived,class Value> struct archetype;
  };

  // Constructor argument for those iterators that
  // are not default constructible
  struct ctor_arg {};

  template <class Derived, class Value, class TraversalCategory>
  struct traversal_archetype_
    : traversal_archetype_impl<TraversalCategory>::template archetype<Derived,Value>
  {
      typedef typename
        traversal_archetype_impl<TraversalCategory>::template archetype<Derived,Value>
      base;

      traversal_archetype_() {}

      traversal_archetype_(ctor_arg arg)
        : base(arg)
      {}
  };

  template <>
  struct traversal_archetype_impl<incrementable_traversal_tag>
  {
      template<class Derived, class Value>
      struct archetype
      {
          explicit archetype(ctor_arg) {}

          struct bogus { }; // This use to be void, but that causes trouble for iterator_facade. Need more research. -JGS
          typedef bogus difference_type;

          Derived& operator++() { return (Derived&)static_object<Derived>::get(); }
          Derived  operator++(int) const { return (Derived&)static_object<Derived>::get(); }
      };
  };

  template <>
  struct traversal_archetype_impl<single_pass_traversal_tag>
  {
      template<class Derived, class Value>
      struct archetype
        : public equality_comparable< traversal_archetype_<Derived, Value, single_pass_traversal_tag> >,
          public traversal_archetype_<Derived, Value, incrementable_traversal_tag>
      {
          explicit archetype(ctor_arg arg)
            : traversal_archetype_<Derived, Value, incrementable_traversal_tag>(arg)
          {}

          typedef std::ptrdiff_t difference_type;
      };
  };

  template <class Derived, class Value>
  bool operator==(traversal_archetype_<Derived, Value, single_pass_traversal_tag> const&,
                  traversal_archetype_<Derived, Value, single_pass_traversal_tag> const&) { return true; }

  template <>
  struct traversal_archetype_impl<forward_traversal_tag>
  {
      template<class Derived, class Value>
      struct archetype
        : public traversal_archetype_<Derived, Value, single_pass_traversal_tag>
      {
          archetype()
            : traversal_archetype_<Derived, Value, single_pass_traversal_tag>(ctor_arg())
          {}
      };
  };

  template <>
  struct traversal_archetype_impl<bidirectional_traversal_tag>
  {
      template<class Derived, class Value>
      struct archetype
        : public traversal_archetype_<Derived, Value, forward_traversal_tag>
      {
          Derived& operator--() { return static_object<Derived>::get(); }
          Derived  operator--(int) const { return static_object<Derived>::get(); }
      };
  };

  template <>
  struct traversal_archetype_impl<random_access_traversal_tag>
  {
      template<class Derived, class Value>
      struct archetype
        : public traversal_archetype_<Derived, Value, bidirectional_traversal_tag>
      {
          Derived& operator+=(std::ptrdiff_t) { return static_object<Derived>::get(); }
          Derived& operator-=(std::ptrdiff_t) { return static_object<Derived>::get(); }
      };
  };

  template <class Derived, class Value>
  Derived& operator+(traversal_archetype_<Derived, Value, random_access_traversal_tag> const&,
                     std::ptrdiff_t) { return static_object<Derived>::get(); }

  template <class Derived, class Value>
  Derived& operator+(std::ptrdiff_t,
                     traversal_archetype_<Derived, Value, random_access_traversal_tag> const&)
      { return static_object<Derived>::get(); }

  template <class Derived, class Value>
  Derived& operator-(traversal_archetype_<Derived, Value, random_access_traversal_tag> const&,
                     std::ptrdiff_t)
      { return static_object<Derived>::get(); }

  template <class Derived, class Value>
  std::ptrdiff_t operator-(traversal_archetype_<Derived, Value, random_access_traversal_tag> const&,
                           traversal_archetype_<Derived, Value, random_access_traversal_tag> const&)
      { return 0; }

  template <class Derived, class Value>
  bool operator<(traversal_archetype_<Derived, Value, random_access_traversal_tag> const&,
                 traversal_archetype_<Derived, Value, random_access_traversal_tag> const&)
      { return true; }

  template <class Derived, class Value>
  bool operator>(traversal_archetype_<Derived, Value, random_access_traversal_tag> const&,
                 traversal_archetype_<Derived, Value, random_access_traversal_tag> const&)
      { return true; }

  template <class Derived, class Value>
  bool operator<=(traversal_archetype_<Derived, Value, random_access_traversal_tag> const&,
                 traversal_archetype_<Derived, Value, random_access_traversal_tag> const&)
      { return true; }

  template <class Derived, class Value>
  bool operator>=(traversal_archetype_<Derived, Value, random_access_traversal_tag> const&,
                 traversal_archetype_<Derived, Value, random_access_traversal_tag> const&)
      { return true; }

  struct bogus_type;

  template <class Value>
  struct convertible_type
    : mpl::if_< is_const<Value>,
                typename remove_const<Value>::type,
                bogus_type >
  {};

} // namespace detail


template <class> struct undefined;

template <class AccessCategory>
struct iterator_access_archetype_impl
{
    template <class Value> struct archetype;
};

template <class Value, class AccessCategory>
struct iterator_access_archetype
  : iterator_access_archetype_impl<
        AccessCategory
    >::template archetype<Value>
{
};

template <>
struct iterator_access_archetype_impl<
    archetypes::readable_iterator_t
>
{
    template <class Value>
    struct archetype
    {
        typedef typename remove_cv<Value>::type value_type;
        typedef Value                           reference;
        typedef Value*                          pointer;

        value_type operator*() const { return static_object<value_type>::get(); }

        detail::arrow_proxy<Value> operator->() const { return detail::arrow_proxy<Value>(); }
    };
};

template <>
struct iterator_access_archetype_impl<
    archetypes::writable_iterator_t
>
{
    template <class Value>
    struct archetype
    {
        BOOST_STATIC_ASSERT(!is_const<Value>::value);
        typedef void value_type;
        typedef void reference;
        typedef void pointer;

        detail::assign_proxy<Value> operator*() const { return detail::assign_proxy<Value>(); }
    };
};

template <>
struct iterator_access_archetype_impl<
    archetypes::readable_writable_iterator_t
>
{
    template <class Value>
    struct archetype
      : public virtual iterator_access_archetype<
            Value, archetypes::readable_iterator_t
        >
    {
        typedef detail::read_write_proxy<Value>    reference;

        detail::read_write_proxy<Value> operator*() const { return detail::read_write_proxy<Value>(); }
    };
};

template <>
struct iterator_access_archetype_impl<archetypes::readable_lvalue_iterator_t>
{
    template <class Value>
    struct archetype
      : public virtual iterator_access_archetype<
            Value, archetypes::readable_iterator_t
        >
    {
        typedef Value&    reference;

        Value& operator*() const { return static_object<Value>::get(); }
        Value* operator->() const { return 0; }
    };
};

template <>
struct iterator_access_archetype_impl<archetypes::writable_lvalue_iterator_t>
{
    template <class Value>
    struct archetype
      : public virtual iterator_access_archetype<
            Value, archetypes::readable_lvalue_iterator_t
        >
    {
        BOOST_STATIC_ASSERT((!is_const<Value>::value));
    };
};


template <class Value, class AccessCategory, class TraversalCategory>
struct iterator_archetype;

template <class Value, class AccessCategory, class TraversalCategory>
struct traversal_archetype_base
  : detail::operator_brackets<
        typename remove_cv<Value>::type
      , AccessCategory
      , TraversalCategory
    >
  , detail::traversal_archetype_<
        iterator_archetype<Value, AccessCategory, TraversalCategory>
      , Value
      , TraversalCategory
    >
{
};

namespace detail
{
  template <class Value, class AccessCategory, class TraversalCategory>
  struct iterator_archetype_base
    : iterator_access_archetype<Value, AccessCategory>
    , traversal_archetype_base<Value, AccessCategory, TraversalCategory>
  {
      typedef iterator_access_archetype<Value, AccessCategory> access;

      typedef typename detail::facade_iterator_category<
          TraversalCategory
        , typename mpl::eval_if<
              archetypes::has_access<
                  AccessCategory, archetypes::writable_iterator_t
              >
            , remove_const<Value>
            , add_const<Value>
          >::type
        , typename access::reference
      >::type iterator_category;

      // Needed for some broken libraries (see below)
      struct workaround_iterator_base
      {
        typedef typename iterator_archetype_base::iterator_category iterator_category;
        typedef Value value_type;
        typedef typename traversal_archetype_base<
              Value, AccessCategory, TraversalCategory
          >::difference_type difference_type;
        typedef typename access::pointer pointer;
        typedef typename access::reference reference;
      };
  };
}

template <class Value, class AccessCategory, class TraversalCategory>
struct iterator_archetype
  : public detail::iterator_archetype_base<Value, AccessCategory, TraversalCategory>

    // These broken libraries require derivation from std::iterator
    // (or related magic) in order to handle iter_swap and other
    // iterator operations
# if BOOST_WORKAROUND(BOOST_DINKUMWARE_STDLIB, < 310)           \
    || BOOST_WORKAROUND(_RWSTD_VER, BOOST_TESTED_AT(0x20101))
  , public detail::iterator_archetype_base<
        Value, AccessCategory, TraversalCategory
    >::workaround_iterator_base
# endif
{
    // Derivation from std::iterator above caused references to nested
    // types to be ambiguous, so now we have to redeclare them all
    // here.
# if BOOST_WORKAROUND(BOOST_DINKUMWARE_STDLIB, < 310)           \
    || BOOST_WORKAROUND(_RWSTD_VER, BOOST_TESTED_AT(0x20101))

    typedef detail::iterator_archetype_base<
        Value,AccessCategory,TraversalCategory
    > base;

    typedef typename base::value_type value_type;
    typedef typename base::reference reference;
    typedef typename base::pointer pointer;
    typedef typename base::difference_type difference_type;
    typedef typename base::iterator_category iterator_category;
# endif

    iterator_archetype() { }
    iterator_archetype(iterator_archetype const& x)
      : detail::iterator_archetype_base<
            Value
          , AccessCategory
          , TraversalCategory
        >(x)
    {}

    iterator_archetype& operator=(iterator_archetype const&)
        { return *this; }

# if 0
    // Optional conversion from mutable
    iterator_archetype(
        iterator_archetype<
        typename detail::convertible_type<Value>::type
      , AccessCategory
      , TraversalCategory> const&
    );
# endif
};

} // namespace iterators

// Backward compatibility names
namespace iterator_archetypes = iterators::archetypes;
using iterators::access_archetype;
using iterators::traversal_archetype;
using iterators::iterator_archetype;
using iterators::undefined;
using iterators::iterator_access_archetype_impl;
using iterators::traversal_archetype_base;

} // namespace boost

#endif // BOOST_ITERATOR_ARCHETYPES_HPP

/* iterator_archetypes.hpp
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
*/