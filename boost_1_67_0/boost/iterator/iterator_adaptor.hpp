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