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
vh+UzX19/x4vOK02dvzF9f2ANxyXx0eB3tDo+ru50KWmCdfEqRuAJN8Lq1s9mPYT6RXRbYBD2zol0lFyWNXKpYLbJe8CFOloSmel4MCA5KJQuQL8AytVrFbRPyB4yIDkovULixgY1r9ihf++bK3ULKFsho00tAL+z5VFzUKb0/Sh9vrvy9RarC9sbPD/VVhQQOXkCqNcqIApQ/h/KFtGVbJC6hN41Kd9dj+XCkSs3cekL+v4LF+st2hvC4t7vtHeb+kUXPJiMtIqbJzFfZ1m8vE8ql18vqGzuNyGddSet3DfTfuY1ZtabsnxZFZlTW+3T9L2UD7LN7VPzjtvd58DHSH1eUB0py7jQe/zQ+MB2kmr+tv+mUGZUvY5Q5kbGMr8vsqR/m/L7NNTgVa+26x8DQ3la0l7Xv5t+XxyOjCl7BmIcjUylOsDNS7d35bLp6eE1N8Y6vslj6+QxobytVE7Gvx1+VZp+0g5mvUZSC3hoB8zym3zf+g1L7wDSnsZuO9vJq+F6rbMjDUh/XBe1qzb5lbfPsbanhbBVAzYgLZqFu4v0g+SPdLo1j7z5a24zqGbqDNZuto/F8qEdHQzcg2zxq/TPkJZAumdbGb1R7++i/tjZGlhKfdaUE6yZcxGfnkfx4utQGOeWcx7u1+mmnYT6ktm8bXOoSwBleidemb3y783DOWkK+woZnW6Hs2J9yjIWjLDO3ba/0c3HYowa93h/bW4jicb7jbtvz8amfQUz7eSlWCmvdOHPKvQXeosunU5Mu86YmhCdYh0Kc8EoU+QtWRW4dh9tLt2mZ0ZlvJMFY7X1Jhn9hqHruK+LFlDWMqzCVijN/V+PFczeqeG2fezz2dAXTf3bgnNjcersrtFF8Tewmh+y/vp70S3EGJ/n/o8sxerDrdFfyFryqxtrtll0T/JWjHr27xHKMriojHHrGtMtWpIRzaZ2dSGq29hHFEhmzPLnHNoAcROlgVGeXw7og36C9kTZmevHI1HWeh5mE0m1n479xdEfJRDGZbOmr47xl8sWQSztE8PP0GebblRHst+Qp7xZNnZ8Urvy/E7+hJdRNtZOu19RuRJxsfDF8XPVUDsZAuYRdVJ2oNy0u76fdjxIldc/wr12YnGJ0t3rte+BeiDwcZ2Tx9bG20UR5aD2doHZUagLGT1eRu9t38OYuisVBgry47AxExooy7UZsxGntmBdk+k2aEUyzP3kjpPUWfdlLrG+1JQHbS7szu1LbNNO+rOQFl6UN0wu7WpMdIp7duKzHK96pQ22QhcZD3c5wfa7UVtrDupMawX5aN0i9z++djUvSiie+v1YqH/B3MPWaKHYQ4hc/ahccsMcwhZrNEw3slowNGYZoYxTRZO1oAZxjRZAllvZhibZCH9aPwxw/gjiyfLwkwbf4iPrBKzTRvNK1ItoD89kcdszItczVPNRdaHWcS8hnWRZ39jno7IqumR5wBj7No5B3VGNoNZ1oeH7yK+gdTuzNDuZHFkZZjhXWqyJLLCzPDON5ljEPUfZnh3m8w5yHu68EHejxdHVoqZ9h45ykIWb9KtVZ4pn6AsEbTSY1Zm2IlbaPdIGsfMAu7fNSPPIdTPzLqlKbd6M9LRKuA4S1ctduVUjM2R+hrF6rFGCRDMKZiLLBczrT4xnwkWI1icYAmCJQnm95H3GByCBQjmJPN2vBDBogWLFSxesETB1MfezSGYU7AQMm/1Ei5YtGAxgsUKFidYvGAJgiUKliSYGuXd/ARzCBYgmFMwl1ej/QPI/N1m0/YrOHi1Kd71J/uIWaFXefummpM2NdnFrO+az6ywaGOeZ4d2qJRq0WQ2k24fzr9RDHsEjMG8S2bco0Pb+KIis5GXc68=
*/