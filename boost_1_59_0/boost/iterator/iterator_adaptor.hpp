// (C) Copyright David Abrahams 2002.
// (C) Copyright Jeremy Siek    2002.
// (C) Copyright Thomas Witt    2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_ITERATOR_ADAPTOR_23022003THW_HPP
#define BOOST_ITERATOR_ADAPTOR_23022003THW_HPP

#include <boost/static_assert.hpp>

#include <boost/core/use_default.hpp>

#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/detail/enable_if.hpp>

#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_convertible.hpp>

#ifdef BOOST_ITERATOR_REF_CONSTNESS_KILLS_WRITABILITY
# include <boost/type_traits/remove_reference.hpp>
#endif

#include <boost/type_traits/add_reference.hpp>
#include <boost/iterator/detail/config_def.hpp>

#include <boost/iterator/iterator_traits.hpp>

namespace boost {
namespace iterators {

  // Used as a default template argument internally, merely to
  // indicate "use the default", this can also be passed by users
  // explicitly in order to specify that the default should be used.
  using boost::use_default;

} // namespace iterators

// the incompleteness of use_default causes massive problems for
// is_convertible (naturally).  This workaround is fortunately not
// needed for vc6/vc7.
template<class To>
struct is_convertible<use_default,To>
  : mpl::false_ {};

namespace iterators {

  namespace detail
  {

    //
    // Result type used in enable_if_convertible meta function.
    // This can be an incomplete type, as only pointers to
    // enable_if_convertible< ... >::type are used.
    // We could have used void for this, but conversion to
    // void* is just to easy.
    //
    struct enable_type;
  }


  //
  // enable_if for use in adapted iterators constructors.
  //
  // In order to provide interoperability between adapted constant and
  // mutable iterators, adapted iterators will usually provide templated
  // conversion constructors of the following form
  //
  // template <class BaseIterator>
  // class adapted_iterator :
  //   public iterator_adaptor< adapted_iterator<Iterator>, Iterator >
  // {
  // public:
  //
  //   ...
  //
  //   template <class OtherIterator>
  //   adapted_iterator(
  //       OtherIterator const& it
  //     , typename enable_if_convertible<OtherIterator, Iterator>::type* = 0);
  //
  //   ...
  // };
  //
  // enable_if_convertible is used to remove those overloads from the overload
  // set that cannot be instantiated. For all practical purposes only overloads
  // for constant/mutable interaction will remain. This has the advantage that
  // meta functions like boost::is_convertible do not return false positives,
  // as they can only look at the signature of the conversion constructor
  // and not at the actual instantiation.
  //
  // enable_if_interoperable can be safely used in user code. It falls back to
  // always enabled for compilers that don't support enable_if or is_convertible.
  // There is no need for compiler specific workarounds in user code.
  //
  // The operators implementation relies on boost::is_convertible not returning
  // false positives for user/library defined iterator types. See comments
  // on operator implementation for consequences.
  //
#  if defined(BOOST_NO_IS_CONVERTIBLE) || defined(BOOST_NO_SFINAE)

  template <class From, class To>
  struct enable_if_convertible
  {
      typedef boost::iterators::detail::enable_type type;
  };

#  elif BOOST_WORKAROUND(_MSC_FULL_VER, BOOST_TESTED_AT(13102292))

  // For some reason vc7.1 needs us to "cut off" instantiation
  // of is_convertible in a few cases.
  template<typename From, typename To>
  struct enable_if_convertible
    : iterators::enable_if<
        mpl::or_<
            is_same<From,To>
          , is_convertible<From, To>
        >
      , boost::iterators::detail::enable_type
    >
  {};

#  else

  template<typename From, typename To>
  struct enable_if_convertible
    : iterators::enable_if<
          is_convertible<From, To>
        , boost::iterators::detail::enable_type
      >
  {};

# endif

  //
  // Default template argument handling for iterator_adaptor
  //
  namespace detail
  {
    // If T is use_default, return the result of invoking
    // DefaultNullaryFn, otherwise return T.
    template <class T, class DefaultNullaryFn>
    struct ia_dflt_help
      : mpl::eval_if<
            is_same<T, use_default>
          , DefaultNullaryFn
          , mpl::identity<T>
        >
    {
    };

    // A metafunction which computes an iterator_adaptor's base class,
    // a specialization of iterator_facade.
    template <
        class Derived
      , class Base
      , class Value
      , class Traversal
      , class Reference
      , class Difference
    >
    struct iterator_adaptor_base
    {
        typedef iterator_facade<
            Derived

# ifdef BOOST_ITERATOR_REF_CONSTNESS_KILLS_WRITABILITY
          , typename boost::iterators::detail::ia_dflt_help<
                Value
              , mpl::eval_if<
                    is_same<Reference,use_default>
                  , iterator_value<Base>
                  , remove_reference<Reference>
                >
            >::type
# else
          , typename boost::iterators::detail::ia_dflt_help<
                Value, iterator_value<Base>
            >::type
# endif

          , typename boost::iterators::detail::ia_dflt_help<
                Traversal
              , iterator_traversal<Base>
            >::type

          , typename boost::iterators::detail::ia_dflt_help<
                Reference
              , mpl::eval_if<
                    is_same<Value,use_default>
                  , iterator_reference<Base>
                  , add_reference<Value>
                >
            >::type

          , typename boost::iterators::detail::ia_dflt_help<
                Difference, iterator_difference<Base>
            >::type
        >
        type;
    };

    // workaround for aC++ CR JAGaf33512
    template <class Tr1, class Tr2>
    inline void iterator_adaptor_assert_traversal ()
    {
      BOOST_STATIC_ASSERT((is_convertible<Tr1, Tr2>::value));
    }
  }

  //
  // Iterator Adaptor
  //
  // The parameter ordering changed slightly with respect to former
  // versions of iterator_adaptor The idea is that when the user needs
  // to fiddle with the reference type it is highly likely that the
  // iterator category has to be adjusted as well.  Any of the
  // following four template arguments may be ommitted or explicitly
  // replaced by use_default.
  //
  //   Value - if supplied, the value_type of the resulting iterator, unless
  //      const. If const, a conforming compiler strips constness for the
  //      value_type. If not supplied, iterator_traits<Base>::value_type is used
  //
  //   Category - the traversal category of the resulting iterator. If not
  //      supplied, iterator_traversal<Base>::type is used.
  //
  //   Reference - the reference type of the resulting iterator, and in
  //      particular, the result type of operator*(). If not supplied but
  //      Value is supplied, Value& is used. Otherwise
  //      iterator_traits<Base>::reference is used.
  //
  //   Difference - the difference_type of the resulting iterator. If not
  //      supplied, iterator_traits<Base>::difference_type is used.
  //
  template <
      class Derived
    , class Base
    , class Value        = use_default
    , class Traversal    = use_default
    , class Reference    = use_default
    , class Difference   = use_default
  >
  class iterator_adaptor
    : public boost::iterators::detail::iterator_adaptor_base<
        Derived, Base, Value, Traversal, Reference, Difference
      >::type
  {
      friend class iterator_core_access;

   protected:
      typedef typename boost::iterators::detail::iterator_adaptor_base<
          Derived, Base, Value, Traversal, Reference, Difference
      >::type super_t;
   public:
      iterator_adaptor() {}

      explicit iterator_adaptor(Base const &iter)
          : m_iterator(iter)
      {
      }

      typedef Base base_type;

      Base const& base() const
        { return m_iterator; }

   protected:
      // for convenience in derived classes
      typedef iterator_adaptor<Derived,Base,Value,Traversal,Reference,Difference> iterator_adaptor_;

      //
      // lvalue access to the Base object for Derived
      //
      Base const& base_reference() const
        { return m_iterator; }

      Base& base_reference()
        { return m_iterator; }

   private:
      //
      // Core iterator interface for iterator_facade.  This is private
      // to prevent temptation for Derived classes to use it, which
      // will often result in an error.  Derived classes should use
      // base_reference(), above, to get direct access to m_iterator.
      //
      typename super_t::reference dereference() const
        { return *m_iterator; }

      template <
      class OtherDerived, class OtherIterator, class V, class C, class R, class D
      >
      bool equal(iterator_adaptor<OtherDerived, OtherIterator, V, C, R, D> const& x) const
      {
        // Maybe readd with same_distance
        //           BOOST_STATIC_ASSERT(
        //               (detail::same_category_and_difference<Derived,OtherDerived>::value)
        //               );
          return m_iterator == x.base();
      }

      typedef typename iterator_category_to_traversal<
          typename super_t::iterator_category
      >::type my_traversal;

# define BOOST_ITERATOR_ADAPTOR_ASSERT_TRAVERSAL(cat) \
      boost::iterators::detail::iterator_adaptor_assert_traversal<my_traversal, cat>();

      void advance(typename super_t::difference_type n)
      {
          BOOST_ITERATOR_ADAPTOR_ASSERT_TRAVERSAL(random_access_traversal_tag)
          m_iterator += n;
      }

      void increment() { ++m_iterator; }

      void decrement()
      {
          BOOST_ITERATOR_ADAPTOR_ASSERT_TRAVERSAL(bidirectional_traversal_tag)
           --m_iterator;
      }

      template <
          class OtherDerived, class OtherIterator, class V, class C, class R, class D
      >
      typename super_t::difference_type distance_to(
          iterator_adaptor<OtherDerived, OtherIterator, V, C, R, D> const& y) const
      {
          BOOST_ITERATOR_ADAPTOR_ASSERT_TRAVERSAL(random_access_traversal_tag)
          // Maybe readd with same_distance
          //           BOOST_STATIC_ASSERT(
          //               (detail::same_category_and_difference<Derived,OtherDerived>::value)
          //               );
          return y.base() - m_iterator;
      }

# undef BOOST_ITERATOR_ADAPTOR_ASSERT_TRAVERSAL

   private: // data members
      Base m_iterator;
  };

} // namespace iterators

using iterators::iterator_adaptor;
using iterators::enable_if_convertible;

} // namespace boost

#include <boost/iterator/detail/config_undef.hpp>

#endif // BOOST_ITERATOR_ADAPTOR_23022003THW_HPP

/* iterator_adaptor.hpp
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
*/