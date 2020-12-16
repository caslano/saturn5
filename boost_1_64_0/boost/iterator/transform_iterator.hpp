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
68FrwA1gOrgRzAIfAqeAW8EbwW3gYvAR8G5VzuC94FPganA3WKTkGXwCfBbcBe4F9zJdz4H3gS/QrJ6z0OU8UM6zTQWb4bqe+z3MCfeu914GtgDvAruq5wX7qucEM8FVYL56LnCiSj+4HCwCi8CHwW3gFvAx9VzgU+q5wKfV84CHwe3gcfBPoErf02CMi+cAU8EDYAfwBfBi8BVwCHgYnAK+Ac4H3wLXgcfAIvBd8C/gcfB5ml8DPwDfAT8Ej4Hfgu3VnJ0yWE8PVgb7gFXAK8FEcByYDM4Ca4CFYE3wFjAFXAHWBx8CLwYfA+uBf6b9TtrvAe8OR/mImfsruJwnx/mQqdyLrC/LYxf8RYGHwIbg62B78E3wUvAtcDD4NpgBvg/OAD8Gl4CfgOvBT1X6wM/AzeCXoCqPr0Al79+AR8BvwU/Av4HfgD+BcWq/BLAe+HewDRhR1ruPQiQ4BCwH3gRGg4vAGPABMBn8E1gD3AWeA34KNgS/AhuD34FNQLWPR1OwItgCPBc8H2wJtgYvANuA7cC24OVgB7AveBE4EOwIDgUPI50jaGY+cy4QxhIt+fxCmFfuj4EtwHfBrio/WX8/BDPBk2A++AW4APye9fAHUMn7j+B2lW/gbvBn8CXwF/BN8B+gyt8oynlFMB6sDNYBq4CNwUSwq8o3MA2sBU4E64ALwbrgH8EG4JNgI8r3uZTvZuCHYDuwm8onFQ/YH8wAB4D54NXgDeA14B1gGrgWHAGuB9PBXeBoym0meACcCb4EHg/DfWlmPnP+A96aLfl8CeV5EOV5MOV5GOU5jfI8gvKcBd4E5oALwVzKcx7leRxYBOaDj4PjwQPgBPB1lQbK8zRQ5fcNYAo4HWwA3gheBBaCA8CbwZHgLeC14DxwLngreDt4G3g/eLu6P7gcfBm8F/wIXAl+C24AvwcfBMshHzaCsWARmApuo755BOwCPgoqud0BjgQfB7PAP4M54BAwn2aVz6v0d3D57i/5LGfDsb3qArn3gD3AimBPsA54BXgB2BvsBQ4CrwaHgEpOrwFVfqSBfcAR4EAwHUwHM8BpYCZ4K5gF3gOOBe8Dx4DrxEx58H235Hfa1ID9Y57jvikHwXjwZVDaXe4f9Q74IHgMbKD0ONgYbB2GfAMvBL37jPB7Gb/ZpQbsMzKxrPc+U8Ca4FSwOXg92FLJh0ovw61iPMk0h+Gqx3hmwJ/iTLA6OIvhEhHgIMO1odyn4Iqm3F8U5i2P7mAE2AecBF4JXqfyA1wE9gOXggPY3g8Et4KDwVfAQeBRmt8Dh4DfqHIDfwCHgmEu8gKMANPAyqocwQY0t6N5MM2jaC4A08GZYAY4D8wGlXzlgBvBceBL4ETwbfB60PUgH8A4cDaYCBaCrcH5LJ8L9PcG5A2vcFxNma+5LJ88sBI4juUznvmbp8e5UebMX3N/nKmud3+auWArcBHYHrwb3AneC+6RfcK9+fYgqD56bATvBpF2eb4UUKW7tt6fiWNWHINLNfcl4j5s5cFW3N/tArAm2AFsCHbhvlhdwXlgN3AV2BNcy/21HgX7g39T5c592kaAd4AjwS3gKPAAmAl+BeZwX6Ltuu/q7d+ncg7aQ0zfEe7f8y6YDH4LjlLPAt4O/hU8wn2UVPvzA9gK/BFM5/5J13K/pLXg38G94C9gOPLpH6B8fFb7KIEe8EUwDKyA9ISDbcEyYDewLLgYTAFVe7ktK0LvebMX+9bkgaH2vNmfdfb2vDmBuL7HlXhthNMeVyau+bi24zqKyxkT4aTg6oIrE1chrvW49o4p3fOm9Ff6K/2V/kp/v+H6//SC8Wdj/b9a5/90kqPnde3nOv8f+S52FNce/BGTZ84=
*/