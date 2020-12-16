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
5nf5wuLcPEtsvw7Ahuqo8A13eOzmPpNwpGMkZoolDqGol9z24FFIpb85+1zDyWt0BqJlCrIvKZNr1OEaTbcqvp4Or10TapKZqucumsv5lsK/H/xtJdxG+OtUoaTuluYvlvOttU3EJ+78tV1UnoSbGnZUZZeJLMnfRc4vhmV+J8SZabYi/ICkGyET34tFWKb/vAUREu9pDF2mm91ltlqiDnvB687vPVyhrczJJNvaxDiWtZTvhoPpcy8MbRutbTT0RaTs0dpmGoXScapcKKu7pPzW7pYf9s2MdYdPZ7iW4Qk+52f4nM9nOLuTO/yQD3+tT/h3DI9OcYe/ZHgMw9/qsPntv+Hf8gPNyQyVOaUNX7Sf+NybT/xt8aB3S4pqP4k+dXM19nMvgb79N3xup6G2AvZzNQ2fC7Kf62v4XJz9nNKpm6Nz+zphf8O+M93H10kLfu+K5XfaZOBK4CDu4TUYeC+/dz0D7Al8BZgKHOhwfw8b7HCfn8RwBsMbgJirOul8VvW4/4z5rEDfqvau+PfMa/0rvletDs1vhY7QETpCR+gIHf/zx08//s8vKTtF3/9vN77/R/D7fzjrEQbagJfWKnm3rTxnXMbUTA7lTvot37TT38B8u5IhGfSXeNhk+eQLf6/lVj1/z3Z7CjCdsYd0pevk5anvm7n0JxnrfShjvTs+O7227dbhlZuWRU9u/MnfV4TGev9LY71Ui/cD7xPf/R9dtDeIBYYB47UNJ/WW90G6jw1nG6ZrD1TxHYBO2is0A3YEdgYmAZMZXx3k2O8/edz3vzrmO4Yxnys3NO4LHaEjdISO0BE6Qkfo+H84fvLxf27+KfP/d5fx/X81x+mjQA7QSNAUfBc9/Fw9+//R46Zk5hXlur+pZ6SIn6TyCuMb9lHh72edbu/fjPk5gvajp64Rp67Bb8iNtrjHUdP4DbcZw81d7nAXhvlNV9dvXiOuFwxzr4VfBpwOngzhX2rWrzQvO9e2fgnAQuG/NCw9zGXWC/mYdg2mfQQaLC+nvLh0ifaPViG8ex3aZsEnPcZ+hv81pPfxv7ZeeKPpw0HbLejz/5Dzpzk8NgTjXlDhm1DOq8CjbQWQsdePwdLn3bYOLekXYbqEfwFZjcU4dqTsAbZG4mY5brG6Y11rY+P6+UW5eRU6r2nC145heA2ScKSt3UML4NVyfhTGzd21L7LhEjcQtexmxdMfUHOJ2+1o5ehuPVXv+jkl+Cd8R8B3TOr/haMn+N4BXyA5TRS55PvLhO00Tc7n+NeTMlol5+MZdlj3SDhZdNsVpF1FDO0qoGuiafGGPYXWHOp+pdZtd3grwzMkfBHDja1w8u/y4W/8fH37iFYM1zLc2+f8Gp/wbQib99omhM38DzE8m+HIF+rzt0XY5O/uEz6b4YsYvprhQ3Hu8Gsv+Ntr1DkCzyGtbKLi12wfcnWPLwo2vXvfhMkJS7edYA1QZLQD8c9/8PNOfV3Tnng6KffhkhmJKzEv01TxX1qR81jHefsiFg4Y++iK6R8Wop+X+E2HHr8w/eUHbnT87buJrX5W/QDWDEu866wHhvYvapyz+5Vn/nL/w08/EnhuyX5O69TNHTZ0LrChc58NnfP7IWt95nmeHXxGpfv4NXhLraPmuv7mwO1cD/wOsBvX96dwfX8f4E76N3gfmAbcARzJeHW9agf7ZD4z1PV6g9Y56IOV64XHcd39JK6vn8y9dzK43nwK179fwHXtM7i3zkzgauAs4Fquf74HeCmwlv4AvuAeRX/juvowXPt6oAt4A7ADw0nAClU/4BLgWODlwMnAK4GZwKuAlwDXqPI4uO4eeBNwKbAKqOr2M+DtwFuADwPvBz4FfAD4PPBB4Ds=
*/