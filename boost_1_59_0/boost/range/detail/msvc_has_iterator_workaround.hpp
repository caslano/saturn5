// Boost.Range library
//
//  Copyright Eric Niebler 2014. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_DETAIL_MSVC_HAS_ITERATOR_WORKAROUND_HPP
#define BOOST_RANGE_DETAIL_MSVC_HAS_ITERATOR_WORKAROUND_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#ifndef BOOST_RANGE_MUTABLE_ITERATOR_HPP
# error This file should only be included from <boost/range/mutable_iterator.hpp>
#endif

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1600)
namespace boost
{
namespace cb_details
{
    template <class Buff, class Traits>
    struct iterator;
}

namespace python
{
    template <class Container
              , class NextPolicies /*= objects::default_iterator_call_policies*/>
    struct iterator;
}

namespace type_erasure
{
    template<
        class Traversal,
        class T                 /*= _self*/,
        class Reference         /*= ::boost::use_default*/,
        class DifferenceType    /*= ::std::ptrdiff_t*/,
        class ValueType         /*= typename deduced<iterator_value_type<T> >::type*/
    >
    struct iterator;
}

namespace unordered { namespace iterator_detail
{
    template <typename Node>
    struct iterator;
}}

namespace container { namespace container_detail
{
    template<class IIterator, bool IsConst>
    class iterator;
}}

namespace spirit { namespace lex { namespace lexertl
{
    template <typename Functor>
    class iterator;
}}}

namespace range_detail
{
    template <class Buff, class Traits>
    struct has_iterator< ::boost::cb_details::iterator<Buff, Traits> >
      : mpl::false_
    {};

    template <class Buff, class Traits>
    struct has_iterator< ::boost::cb_details::iterator<Buff, Traits> const>
      : mpl::false_
    {};

    template <class Container, class NextPolicies>
    struct has_iterator< ::boost::python::iterator<Container, NextPolicies> >
      : mpl::false_
    {};

    template <class Container, class NextPolicies>
    struct has_iterator< ::boost::python::iterator<Container, NextPolicies> const>
      : mpl::false_
    {};

    template<class Traversal, class T, class Reference, class DifferenceType, class ValueType>
    struct has_iterator< ::boost::type_erasure::iterator<Traversal, T, Reference, DifferenceType, ValueType> >
      : mpl::false_
    {};

    template<class Traversal, class T, class Reference, class DifferenceType, class ValueType>
    struct has_iterator< ::boost::type_erasure::iterator<Traversal, T, Reference, DifferenceType, ValueType> const>
      : mpl::false_
    {};

    template <typename Node>
    struct has_iterator< ::boost::unordered::iterator_detail::iterator<Node> >
      : mpl::false_
    {};

    template <typename Node>
    struct has_iterator< ::boost::unordered::iterator_detail::iterator<Node> const>
      : mpl::false_
    {};

    template<class IIterator, bool IsConst>
    struct has_iterator< ::boost::container::container_detail::iterator<IIterator, IsConst> >
      : mpl::false_
    {};

    template<class IIterator, bool IsConst>
    struct has_iterator< ::boost::container::container_detail::iterator<IIterator, IsConst> const>
      : mpl::false_
    {};

    template <typename Functor>
    struct has_iterator< ::boost::spirit::lex::lexertl::iterator<Functor> >
      : mpl::false_
    {};

    template <typename Functor>
    struct has_iterator< ::boost::spirit::lex::lexertl::iterator<Functor> const>
      : mpl::false_
    {};
}
}
#endif
#endif

/* msvc_has_iterator_workaround.hpp
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
*/