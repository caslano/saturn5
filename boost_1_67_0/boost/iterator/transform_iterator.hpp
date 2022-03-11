// (C) Copyright David Abrahams 2002.
// (C) Copyright Jeremy Siek    2002.
// (C) Copyright Thomas Witt    2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_TRANSFORM_ITERATOR_23022003THW_HPP
#define BOOST_TRANSFORM_ITERATOR_23022003THW_HPP

#include <boost/iterator/detail/enable_if.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/function_traits.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_class.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/result_of.hpp>

#include <iterator>

#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1310))
# include <boost/type_traits/is_base_and_derived.hpp>
#endif

#include <boost/iterator/detail/config_def.hpp>


namespace boost {
namespace iterators {

  template <class UnaryFunction, class Iterator, class Reference = use_default, class Value = use_default>
  class transform_iterator;

  namespace detail
  {
    // Compute the iterator_adaptor instantiation to be used for transform_iterator
    template <class UnaryFunc, class Iterator, class Reference, class Value>
    struct transform_iterator_base
    {
     private:
        // By default, dereferencing the iterator yields the same as
        // the function.
        typedef typename ia_dflt_help<
            Reference
#ifdef BOOST_RESULT_OF_USE_TR1
          , result_of<const UnaryFunc(typename std::iterator_traits<Iterator>::reference)>
#else
          , result_of<const UnaryFunc&(typename std::iterator_traits<Iterator>::reference)>
#endif
        >::type reference;

        // To get the default for Value: remove any reference on the
        // result type, but retain any constness to signal
        // non-writability.  Note that if we adopt Thomas' suggestion
        // to key non-writability *only* on the Reference argument,
        // we'd need to strip constness here as well.
        typedef typename ia_dflt_help<
            Value
          , remove_reference<reference>
        >::type cv_value_type;

     public:
        typedef iterator_adaptor<
            transform_iterator<UnaryFunc, Iterator, Reference, Value>
          , Iterator
          , cv_value_type
          , use_default    // Leave the traversal category alone
          , reference
        > type;
    };
  }

  template <class UnaryFunc, class Iterator, class Reference, class Value>
  class transform_iterator
    : public boost::iterators::detail::transform_iterator_base<UnaryFunc, Iterator, Reference, Value>::type
  {
    typedef typename
    boost::iterators::detail::transform_iterator_base<UnaryFunc, Iterator, Reference, Value>::type
    super_t;

    friend class iterator_core_access;

  public:
    transform_iterator() { }

    transform_iterator(Iterator const& x, UnaryFunc f)
      : super_t(x), m_f(f) { }

    explicit transform_iterator(Iterator const& x)
      : super_t(x)
    {
        // Pro8 is a little too aggressive about instantiating the
        // body of this function.
#if !BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3003))
        // don't provide this constructor if UnaryFunc is a
        // function pointer type, since it will be 0.  Too dangerous.
        BOOST_STATIC_ASSERT(is_class<UnaryFunc>::value);
#endif
    }

    template <
        class OtherUnaryFunction
      , class OtherIterator
      , class OtherReference
      , class OtherValue>
    transform_iterator(
         transform_iterator<OtherUnaryFunction, OtherIterator, OtherReference, OtherValue> const& t
       , typename enable_if_convertible<OtherIterator, Iterator>::type* = 0
#if !BOOST_WORKAROUND(BOOST_MSVC, == 1310)
       , typename enable_if_convertible<OtherUnaryFunction, UnaryFunc>::type* = 0
#endif
    )
      : super_t(t.base()), m_f(t.functor())
   {}

    UnaryFunc functor() const
      { return m_f; }

  private:
    typename super_t::reference dereference() const
    { return m_f(*this->base()); }

    // Probably should be the initial base class so it can be
    // optimized away via EBO if it is an empty class.
    UnaryFunc m_f;
  };

  template <class UnaryFunc, class Iterator>
  inline transform_iterator<UnaryFunc, Iterator>
  make_transform_iterator(Iterator it, UnaryFunc fun)
  {
      return transform_iterator<UnaryFunc, Iterator>(it, fun);
  }

  // Version which allows explicit specification of the UnaryFunc
  // type.
  //
  // This generator is not provided if UnaryFunc is a function
  // pointer type, because it's too dangerous: the default-constructed
  // function pointer in the iterator be 0, leading to a runtime
  // crash.
  template <class UnaryFunc, class Iterator>
  inline typename iterators::enable_if<
      is_class<UnaryFunc>   // We should probably find a cheaper test than is_class<>
    , transform_iterator<UnaryFunc, Iterator>
  >::type
  make_transform_iterator(Iterator it)
  {
      return transform_iterator<UnaryFunc, Iterator>(it, UnaryFunc());
  }

#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION ) && !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
  template <class Return, class Argument, class Iterator>
  inline transform_iterator< Return (*)(Argument), Iterator, Return>
  make_transform_iterator(Iterator it, Return (*fun)(Argument))
  {
    return transform_iterator<Return (*)(Argument), Iterator, Return>(it, fun);
  }
#endif

} // namespace iterators

using iterators::transform_iterator;
using iterators::make_transform_iterator;

} // namespace boost

#include <boost/iterator/detail/config_undef.hpp>

#endif // BOOST_TRANSFORM_ITERATOR_23022003THW_HPP

/* transform_iterator.hpp
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
*/