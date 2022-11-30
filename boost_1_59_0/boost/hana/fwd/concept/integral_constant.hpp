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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_CONCEPT_INTEGRAL_CONSTANT_HPP

/* integral_constant.hpp
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
*/