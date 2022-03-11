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