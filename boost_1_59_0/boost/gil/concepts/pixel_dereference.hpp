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
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
*/