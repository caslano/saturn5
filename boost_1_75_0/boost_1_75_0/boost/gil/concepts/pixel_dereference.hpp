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
/IwXcSlGhHQV83jK2aAAlY88u4yuJ6+oP4N3gPNgLBfPCSfK8qcZ7Fl/1sUhRzTuu41yiFfeKZ/n+w6AmIM22h+F70gVqv1YBGxLgTK89D0yZCxeQYRJdSpDFnuAHn3tM6PQkBZTEyUIDIiXCBBTQIAjhKMp3FXeCbzSg+RC7PrrggWK7feIiSRxuhthDJBD48P22RrB/W0UEO5O8Gp0F86+Fyfx8bMU+/kDLPI+dcqXRVPVcPzq9C0s644PtJC4Hd+k6zAUmaSCFTMXw3V5ek+8FpPRsU/dJ6GLqr0ZoVyX0GCRbbJLq5aYrIAcCV80Q63K7A2uE0k//eu3/aDOWcbAgrr/Hm7Bdu+QFodPt3R1ubwn8Fmc/Ys3UJCvcKa2ng1PUsNFB4B5ocoYRyGzCKafJpNHKCTMaad5pl3HkRI5cp5OiSBSbkIGLpc0NWnuxjg+7Z4CaRGJ2hcR2K6tDkHNXi9Hy1Yez5piNSifdkIPmPRPQT8Opn3HMuo3QvFRcXDmnRrqsvDpAyQz0QNCAaK2gPCBJLQYGmp8clUaTJm3t5jPMPBQ302cN1VGFbkP4gVlrdn3NNeaWGcHG5om4dpYlpBmqscJulARu4uxgrfe7zVs5VYz4PSW4Pn+8sXSTIEQRMDhk5/OQRi0FfjaNBGnfsb8/u3YQHMOvRIwQ4qC2XvXTk/TebUw9U51cuebCFV02+xEL5Iw0EL3
*/