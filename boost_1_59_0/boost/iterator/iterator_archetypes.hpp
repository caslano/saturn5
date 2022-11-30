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
+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
*/