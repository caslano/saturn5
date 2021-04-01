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
Ea59DECJQ6l07+d/B2kU9HhOxwpicCcsZcL/SJNnYHXiUELpkeOLfiSw/1vp4qkVMjPtEcyHelAUwDRV0LXOVQZinRoWEha7DtGgC56hBo4eWY6L1xxRJyFQVg6V5GOeEZszeCXwOp9cQwEzSZ6pKeYps/MEc2Ea3vGwDBdEIfbjOH7e1xGG2A58Euf4+qE7xL+8/mK6E1oo/5Ph7AxUIu+cLjJ9p7JIFqFEfycDhARP4nAvp7C3PiCD3IYL7rukJuOApmFODPhGruv7b1PdptZvbV28w8/gzMb05Y+8Gur0MLeLA3Rpouho+qUoxVpQSKMDiz6JMdHUJxnquny+Ok/2GzZC2zFHZnkSXJeDm/0pp0pKr/iXTMURnuSi7LEdtQqWmAU4ncMdW0r6D0shTK2FAFsJ1iu5ucJMl9qtDTBMHL20HVrhmgGqFCbl6ZKZ2hExee6cRK4y40/bxghXgBRMAlumXcCWpx5sTFvvJlyiaKOwMTKxa57NxPWm/GY+KJc/+RsalWidnY4GAiwbvM9f2giwSqmahEPyOLsjrkit5xSN9FBX7RI9mA==
*/