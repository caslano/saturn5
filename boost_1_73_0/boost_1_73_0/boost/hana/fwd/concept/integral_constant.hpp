/*!
@file
Forward declares `boost::hana::IntegralConstant`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONCEPT_INTEGRAL_CONSTANT_HPP
#define BOOST_HANA_FWD_CONCEPT_INTEGRAL_CONSTANT_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-concepts
    //! The `IntegralConstant` concept represents compile-time integral values.
    //!
    //! The `IntegralConstant` concept represents objects that hold a
    //! `constexpr` value of an integral type. In other words, it describes
    //! the essential functionality provided by `std::integral_constant`.
    //! An `IntegralConstant` is also just a special kind of `Constant`
    //! whose inner value is of an integral type.
    //!
    //!
    //! Minimal complete definition
    //! ---------------------------
    //! The requirements for being an `IntegralConstant` are quite simple.
    //! First, an `IntegralConstant` `C` must be a `Constant` such that
    //! `Tag::value_type` is an integral type, where `Tag` is the tag of `C`.
    //!
    //! Secondly, `C` must have a nested `static constexpr` member named
    //! `value`, such that the following code is valid:
    //! @code
    //!     constexpr auto v = C::value;
    //! @endcode
    //! Because of the requirement that `Tag::value_type` be an integral type,
    //! it follows that `C::value` must be an integral value.
    //!
    //! Finally, it is necessary to specialize the `IntegralConstant` template
    //! in the `boost::hana` namespace to tell Hana that a type is a model
    //! of `IntegralConstant`:
    //! @code
    //!     namespace boost { namespace hana {
    //!         template <>
    //!         struct IntegralConstant<your_custom_tag> {
    //!             static constexpr bool value = true;
    //!         };
    //!     }}
    //! @endcode
    //!
    //!
    //! Refined concept
    //! ---------------
    //! 1. `Constant` (free implementation of `value`)\n
    //! The `value` function required to be a `Constant` can be implemented
    //! as follows for `IntegralConstant`s:
    //! @code
    //!     value<C>() == C::value
    //! @endcode
    //! The `to` function must still be provided explicitly for the model
    //! of `Constant` to be complete.
    //!
    //!
    //! Concrete models
    //! ---------------
    //! `hana::integral_constant`
    template <typename C>
    struct IntegralConstant;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CONCEPT_INTEGRAL_CONSTANT_HPP

/* integral_constant.hpp
BYpq8Cqgb8C/PzwxUw2ujIVpWAq5v1sK5TGCaIawXBzL4I1gSUalJZpjVBUBFIOLQtfsxo09BEMM2PWx9mU2CyEYGihYfqFCA6EXoQit7OvrFXA2dsFVWCW5CLaBWh1OLYJsgCIWVQ8RvKKFCpJW6LD4WYUYKIxUaBjaOQVA0GgVO6Pwmg9OKPimAuUTAiAnndDMhmMTqs30V3ebe/QiSMTvi+F8ni6Sq+FoMaPDpB9ZyPKiTIdjSgvozlr3Q/hCKT6tURbJ0QHZg16f7Z19GJzunf+STGcj9tUEeiVMeUnWqMUyZxcXbiSTxeyq/hIBU16pWXEF2n7yZ5rOC4av1gFnMJfD/FNK17+8HFKSwHgH+5wB6ZGNok0bmhEIvpDMpuOfH+jtk59rP/r5QUvZnx6QulQ0/TKfLcqWkty28h2H1frbP3l/tk/+/WDrj3Wix4Nt8h+9h2dn3dgz6Sb5nn6YoZwtUu2l7ZPfemd7bwPtzg3fJ7iNLum3MGZz6r0F+1oEiS3ZnY0Xy2wqvnPyaTR6SPEeU954nS7Ismf5SITQii/XMiUjf6ebz6DfO6jIjVy2d/Z20Dvee33Uq0rVtYg6lNJ/UiznFHwmXv2wmibith3+w8FV8enn+3QdJu41vn/vHr9Ok938Rudz
*/