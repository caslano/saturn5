// boost heap
//
// Copyright (C) 2010-2011 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HEAP_POLICIES_HPP
#define BOOST_HEAP_POLICIES_HPP

#include <boost/concept_check.hpp>
#include <boost/parameter/name.hpp>
#include <boost/parameter/template_keyword.hpp>
#include <boost/parameter/aux_/void.hpp>
#include <boost/parameter/binding.hpp>
#include <boost/parameter/parameters.hpp>
#include <boost/type_traits/conditional.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/is_void.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace heap {

#ifndef BOOST_DOXYGEN_INVOKED
BOOST_PARAMETER_TEMPLATE_KEYWORD(allocator)
BOOST_PARAMETER_TEMPLATE_KEYWORD(compare)

namespace tag { struct stable; }

template <bool T>
struct stable:
    boost::parameter::template_keyword<tag::stable, boost::integral_constant<bool, T> >
{};

namespace tag { struct mutable_; }

template <bool T>
struct mutable_:
    boost::parameter::template_keyword<tag::mutable_, boost::integral_constant<bool, T> >
{};


namespace tag { struct constant_time_size; }

template <bool T>
struct constant_time_size:
    boost::parameter::template_keyword<tag::constant_time_size, boost::integral_constant<bool, T> >
{};

namespace tag { struct store_parent_pointer; }

template <bool T>
struct store_parent_pointer:
    boost::parameter::template_keyword<tag::store_parent_pointer, boost::integral_constant<bool, T> >
{};

namespace tag { struct arity; }

template <unsigned int T>
struct arity:
    boost::parameter::template_keyword<tag::arity, boost::integral_constant<int, T> >
{};

namespace tag { struct objects_per_page; }

template <unsigned int T>
struct objects_per_page:
    boost::parameter::template_keyword<tag::objects_per_page, boost::integral_constant<int, T> >
{};

BOOST_PARAMETER_TEMPLATE_KEYWORD(stability_counter_type)

namespace detail {

template <typename bound_args, typename tag_type>
struct has_arg
{
    typedef typename boost::parameter::binding<bound_args, tag_type, void>::type type;
    static const bool value = !boost::is_void<type>::value;
};

template <typename bound_args>
struct extract_stable
{
    static const bool has_stable = has_arg<bound_args, tag::stable>::value;

    typedef typename boost::conditional<has_stable,
                               typename has_arg<bound_args, tag::stable>::type,
                               boost::false_type
                              >::type stable_t;

    static const bool value = stable_t::value;
};

template <typename bound_args>
struct extract_mutable
{
    static const bool has_mutable = has_arg<bound_args, tag::mutable_>::value;

    typedef typename boost::conditional<has_mutable,
                               typename has_arg<bound_args, tag::mutable_>::type,
                               boost::false_type
                              >::type mutable_t;

    static const bool value = mutable_t::value;
};

}

#else

/** \brief Specifies the predicate for the heap order
 */
template <typename T>
struct compare{};

/** \brief Configure heap as mutable
 *
 *  Certain heaps need to be configured specifically do be mutable.
 *
 * */
template <bool T>
struct mutable_{};

/** \brief Specifies allocator for the internal memory management
 */
template <typename T>
struct allocator{};

/** \brief Configure a heap as \b stable
 *
 * A priority queue is stable, if elements with the same priority are popped from the heap, in the same order as
 * they are inserted.
 * */
template <bool T>
struct stable{};

/** \brief Specifies the type for stability counter
 *
 * */
template <typename IntType>
struct stability_counter_type{};

/** \brief Configures complexity of <tt> size() </tt>
 *
 * Specifies, whether size() should have linear or constant complexity.
 * */
template <bool T>
struct constant_time_size{};

/** \brief Store parent pointer in heap node.
 *
 * Maintaining a parent pointer adds some maintenance and size overhead, but iterating a heap is more efficient.
 * */
template <bool T>
struct store_parent_pointer{};

/** \brief Specify arity.
 *
 * Specifies the arity of a D-ary heap
 * */
template <unsigned int T>
struct arity{};
#endif

} /* namespace heap */
} /* namespace boost */

#endif /* BOOST_HEAP_POLICIES_HPP */

/* policies.hpp
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
*/