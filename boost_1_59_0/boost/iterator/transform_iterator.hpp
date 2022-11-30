// (C) Copyright David Abrahams 2002.
// (C) Copyright Jeremy Siek    2002.
// (C) Copyright Thomas Witt    2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_TRANSFORM_ITERATOR_23022003THW_HPP
#define BOOST_TRANSFORM_ITERATOR_23022003THW_HPP

#include <boost/config.hpp>
#include <boost/config/workaround.hpp>
#include <boost/iterator/detail/enable_if.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
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
#include <boost/type_traits/is_base_and_derived.hpp>
#endif

#if !BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3003))
#include <boost/static_assert.hpp>
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

#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) && !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
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