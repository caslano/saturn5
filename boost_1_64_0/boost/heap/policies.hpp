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
g8Yh75vW6N4dOFU0Qud9e6VgA9OblGDgsYeknVNNMc0hHqozw39YU0521/7GUC2mhKAOvtoFsRFsVOyX1tt13VtUFRkvCueeOU4UUTp3+KOnrY1vl26SKmdDZ+rI80v6gq1u8Yfv4DZHUyPNlih7pSuDpBF7CijaxPV05j6kq9jRRiakfzyter3vw2YSbpxr2E3Zy5OC0aj21n39RkrXTeziUuLdxoKT3IQDd4atAgi9KAL+DFYDJydIpHdeJ38neI+3RHLNfZ7jLuPVQ+BwfBFWS1h51/XtznpJit4xov7aS5RnaGgfw3M/jNjdLujN00iGpnw6cn8xRqeoe0Ydo2qKMQB5NXHnVJKHdbWqM4bkR+RIVUozPMO4VAzxZ4pCl9dWuquTz4h2dEQxZPyZlbSKMobwEWwjdIDDQKdM8X0imtumUGIpMs4hvjFneczDUDLXiQdnd9c/zXX9BLEUy8FFMOPxSvbVVKbNsL6p99MjM3gAKAHO7CtrECVWos1aUuz29Mg5ehxzkf1OZLALziVTxNUDgbbCodZ2TjkBwdACHbFUIGqNKYI5gg==
*/