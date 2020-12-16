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
VTbnX+Gw8PymNDEx1OPfd4kkOjVAogAxNPTFC+jIdh/e4usTOb8KBhJq9Qty4dLDRx9c6hew5Pc9nNvT7jeof8d7Oy596ny8/w3hPGrfMwNNGuCJN0BoLaS9FqXacbt27KYWT3zKxqe7aJoI4ZxbKACixm4HqVubEccCMEhVe+bRU/3bWmgB4TTcu1Yc21KDB4ors/weX3F/kGEA/6i/qNcYqB0RXhHxOEXcJCJqInwtIVTcZLwCg5Wn2VjZ16he10TGt+T5sNrIy3Wvuv0fnIfoZTa+sb6f+KHSUBLCA3TeA5TJVl7krviAnnoEUkdWOmjdT6TrVWdF487QbuFF7iy/Bflc0bh0xLFOUQNp269H0cbxi9T+Q1ZyQ86dwvsPQFR4rR8RxfVlRMfgtTMa86ghHv6fW2UUizpjnAL2nEdBVXYSZwK9SBftXBPIxMomddl488DazmOKgy3GipZQgG8dzkOkgxbAmj+VI9J+LdLm0JoW6XsQd+bWvV2vXM1DGI0tdvbDv7tJWjCgUn+EOEqokj3Un0ChODiFQjS1tUPef9TCPfifPUz1X9G6uuJretoHZ9C/tlFHqKFiVXDct1nqm+jAdn2T1tHKRP3zl3tizrsZ8KlMedxhTRLn3XLwxB56RWbVMCrVUCfKblJ2qqFVguoremo2Ycs5N5r11zirtuhlgo5rCO9x5OKlLgICXHSAEtgu2+SOrOSvZdybIzbyhIxjdnn4Zgj0KKN4B97Zto3TNLzKs7tXvRPaai9KT1rH/ZvtI5Au9dXnuIsBlNfMTZpNmV3D5Jh7QR35gXCIy6X8jtqg0T/R5aOXyCmT7uQjr03JtyEoC9L3A6HaaIyGMak1xsfLoNDX4Ztl34bTS6ZEP8fDK7Y0xoevSAhPjwvDbrAxER9r41HiiyclpgeGsfGuBPj2+PTkT2CcwAmcgMPKiOmhS6JoHVHfNNQ2Pj/K0Mub0hdJOCz1mXlY6aaEEIh8ohTbH6FL8wPns7qGdUDzTg1k4t7pOacGW1Pn9hpmxKeWTmL+GWZCIJBGebfejP0Ccj1z9P6m3osPR+vrxikX7xAMs0AZaQ6wqTAfZqX2uVn+y31baPbIOguzx7DnmFeFR9q1a2p3Q7/L7jed+wKpPHRIcqvM9CIJDkxD83PqeSxJ0FVuk4+JX2L/WRPClnbpjfsnXSnBggDtiUBki1KitedlMe15rmjPc6k9zxft2XfRkL1kKQ8+409mPXynR7ma8e0MmFt/uJXbuQPjj/XHgcFu9gUE2WuSNXiAWvNq0ZrF1Jo76rgYN6nOWJrfupo/lE9uPOZ+AtXfrWQvOvAgkLwlL1ASHnlg2APAd54bO92OWew6NQuPun4sVdYl8yMc9GKOGfYVJTwLCT8QCddSQkCihI+Ix5/E4zTORtfPz3idWKRXvRaWcvs2eXvu7btbLYDaUNx8jM69fcW16fYv8fcI/rbjz2Bq52cUj6R2o4/9MySZvvsvaebt7wHPLfjbSLhLvM1ms9H8P/zDSMD/1AKv/6f+eHxbQvRvSXZki/zc5vxiaWx3fjM2gkm0z0/sjUfyb0sC/86KyW8h/h0TzkqA52iXf7mFLtYHlmNgFqBUmpXT/IXqis808S/QM5Qdmg8DoBQ2ABrDBkB4sgEQxtfRGYJvogTMu3xvNUuTnzh88hqPzm9zEsIFCeFsDneoPUV7HJV/x7ZftGHQJvd8Ktskg/olZBE9IWev+P7Ji1mOtRWfe4z4nGPEFxwjPvsY8dZjxNuPEe84RrzlGPFZIr4D8gDGSx9foewHsfn0O6HD2b2BZW+a+2QvtgEv9jzXDPZ/+kHseng6Es0nReFsWhMvpBERwOcseUA=
*/