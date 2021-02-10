//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_CONCEPTS_PIXEL_DEREFERENCE_HPP
#define BOOST_GIL_CONCEPTS_PIXEL_DEREFERENCE_HPP

#include <boost/gil/concepts/basic.hpp>
#include <boost/gil/concepts/concept_check.hpp>
#include <boost/gil/concepts/fwd.hpp>
#include <boost/gil/concepts/pixel.hpp>
#include <boost/gil/concepts/detail/type_traits.hpp>

#include <boost/concept_check.hpp>

#include <cstddef>
#include <type_traits>

#if defined(BOOST_CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic ignored "-Wunused-local-typedefs"
#endif

#if defined(BOOST_GCC) && (BOOST_GCC >= 40900)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#endif

namespace boost { namespace gil {

/// \ingroup PixelDereferenceAdaptorConcept
/// \brief Represents a unary function object that can be invoked upon dereferencing a pixel iterator.
///
/// This can perform an arbitrary computation, such as color conversion or table lookup.
/// \code
/// concept PixelDereferenceAdaptorConcept<boost::UnaryFunctionConcept D>
///     : DefaultConstructibleConcept<D>, CopyConstructibleConcept<D>, AssignableConcept<D>
/// {
///     typename const_t; where PixelDereferenceAdaptorConcept<const_t>;
///     typename value_type; where PixelValueConcept<value_type>;
///     typename reference;         // may be mutable
///     typename const_reference;   // must not be mutable
///     static const bool D::is_mutable;
///
///     where Convertible<value_type,result_type>;
/// };
/// \endcode
template <typename D>
struct PixelDereferenceAdaptorConcept
{
    void constraints()
    {
        gil_function_requires
        <
            boost::UnaryFunctionConcept
            <
                D,
                typename detail::remove_const_and_reference<typename D::result_type>::type,
                typename D::argument_type
            >
        >();
        gil_function_requires<boost::DefaultConstructibleConcept<D>>();
        gil_function_requires<boost::CopyConstructibleConcept<D>>();
        gil_function_requires<boost::AssignableConcept<D>>();

        gil_function_requires<PixelConcept
            <
                typename detail::remove_const_and_reference<typename D::result_type>::type
            >>();

        using const_t = typename D::const_t;
        gil_function_requires<PixelDereferenceAdaptorConcept<const_t>>();

        using value_type = typename D::value_type;
        gil_function_requires<PixelValueConcept<value_type>>();

        // TODO: Should this be concept-checked after "if you remove const and reference"? --mloskot
        using reference = typename D::reference; // == PixelConcept (if you remove const and reference)
        using const_reference = typename D::const_reference; // == PixelConcept (if you remove const and reference)

        bool const is_mutable = D::is_mutable;
        ignore_unused_variable_warning(is_mutable);
    }
    D d;
};

template <typename P>
struct PixelDereferenceAdaptorArchetype
{
    using argument_type = P;
    using result_type = P;
    using const_t = PixelDereferenceAdaptorArchetype;
    using value_type = typename std::remove_reference<P>::type;
    using reference = typename std::add_lvalue_reference<P>::type;
    using const_reference = reference;

    static const bool is_mutable = false;
    P operator()(P) const { throw; }
};

}} // namespace boost::gil

#if defined(BOOST_CLANG)
#pragma clang diagnostic pop
#endif

#if defined(BOOST_GCC) && (BOOST_GCC >= 40900)
#pragma GCC diagnostic pop
#endif

#endif

/* pixel_dereference.hpp
vwgCV+fvn4QClanVmc8LIbGwtg8NfmTggf14RX/U5yrv8ZOOU1kV/f77XNkuQhjge5wAXwHoAQ9GGpdJESA4EWSvYfFXbXGWAi4iR4KvOzIJ0yEAEBlLcpe3EW7weQYS8zXiJ9QR/4Q5heMA8DoPx3IiD8x34LGZ/TYN8vwBKMCW8FbmB7jxxx96Z8C14sdDHEPXGKd5Yev/I01kNKTqI9jHZAYcOwphMcdn99+LYDhErgWE53QwTbPCnUIxtt/+eyazR/t1lAV3EwDIwZqzoCwowjGNWMgJdBZkj0KVokgK3LGwBo3gV8ciMUWoMu0LEafJncCZwQq4MvAQu5p7EB24J1D3K0xG4+lR/03v6v3l4OL1u/6HvqiR7AMWkOMWhuI+jYZilEk5gI0ZgySKZaO8VVuz5hpuF1ZrzHZe8YY1D5wi3DOvQG+bV6h2zivDvfIKeLv8zmDRpd6LsVdAm+KV6H3xCtUeeGUa/lD4lZB9kgLfIL1kFscgtGEHkoJkKsxMMIzgI+B6kKQk+aAIKQx7pIYp6BERkgvhvYXz5H4ZlEdZOmmtLVTe5uoXqd0Wp18oxuXBY/GSOzWrxS96mSi+3wDDpAnnEhSqoADqAO0IC2Qy1EoEbpBIggkoKinrGPXDOgmFAKkmjj5L
*/