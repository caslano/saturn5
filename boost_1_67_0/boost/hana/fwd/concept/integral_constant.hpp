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
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
*/