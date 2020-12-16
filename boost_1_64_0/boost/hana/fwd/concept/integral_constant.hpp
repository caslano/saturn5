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
RGIJ0MmnjMl58tbAwBRKXZBARrl48GUptGZEkzUt0fogXZUekWAC9nKeQiRytELrHiuLBJ9jj7xS6nLxRUVLqe+wydbkXKDjUzeCi0QHGa/Pzhllz2C9WIconUgerr8h+RqFjygrzMKuW4EmjvlNAyUHVybdmN1byrVuLNea0PlsS3OnQ6JAs5FVwYLitXMsBF62Yhl5P2IfSsVuIhJ3MkVOAHk5isdET0yOMkqKlhLXT5UtHUJ0V+pRYaqQHEqMsBqELVRhXup0hLRoX9rnE8go6wYg1h5ZgEhmLhvHc61adGYvitSiD3vEt0x8ZZPntu7l7WmpLqMBKmonWfX9rYpDcESUH2JxoHer8Ii8JTguleOKNIWgfdDElxGvwhoPgaAt2GBstVK9LeIUsgsXYi37iPioSsv3iiJiRlCPA08IcV2O1ayWn2aKiJZLzsnVgnPKlzeysnI4L+/uxuYxPS7EtyId//b0+N/9T+rPeiLcsLksU4kEQ9p1gV4xRPdBFv9kotflXO1QbJ+r8siGVfHkYlDUajHwysUgG69uZq72DeTFIGBjrvzEXC06gxaDNYfKxWAZP4VYeKheAM7FG4acNhW5T9K2oihP1omgiTyKc9TgfjddDfuwKO5tTYZnVGgY49E8y5oJ92lSt6AswvcsExdPgG0sut6IWR+2w12TbhGd0jAVKsam4MRaRfL68/JEK/7EdDW5IwwzX1MKCytR38vCtZ8VyvcsW1dwn8Oq4JRUJuFIVfDOOVbBLzlUY7WuDnVfNNwi6BYKQkuEW+B4mVVcWFSlAC9SgBXFnIdD5fGT7RQTIXYwE1I0uyiCeHFdTwv3PMWURhvLeGhRK8p1K9eOXwddF2pd1cj2IsC+6iL8sXQsCr/OtdB9RsVJWhjQZbO+myybus1e2jVpNoThMhLwHCdrIreEcbB1S/wcShvLiPBCODZXJ5xMsClKLd0R8etKi1JGI2FbG8VzdXEMGw0gNlRKSultQSlzo+K9/uquRWAwz+R8ybL+XzGWzfGwiYNIVFT218duA8koyyz+dOKzB6zrBJMLc3A3qS+PhPa6F6XzUBeNXp+E1bB/+roxCH6chwJRz8TvkhGLsm7upylrx+r68ekzmH5mEiEubEU/4aWCPbvJq601fcTjyMpqf2+SFva0aihDc3bcDh1WTSeD4/y0Ld4jSunJ0rVj1Vu+yPVrIppDo/tmNeVCGJfRCI9BOexNFUHz2rOqG76QhA1q2FOdSeHaYos9otIewSwGIvNQsBYnscTsJJUiwEzxFd1S11GRguK0CRJMurdPsybxp2kyln5RWFyEXKh5SAhSMFWY317YEy0T/ygF5vY0W92jOo+2usCXYCEJawkvXqthNR9L/6NQAB2tgcaj+wMYHy2TjkPSXlbSPJXU1bJR4z7eBouMPvJ4V+x+u++O8SGxCxwdE5Vhck2WXjT+Uyb65gDffzpZymvyWLIQDYW1wxZc3hG3HqJnRB/aaYTF1TKA/YXz9fsAu08rxYJ3kU5bM7x4rDc+qrjcC92TWiddS7klV8cdgtmOXb+40gpxVStAePI85w9zfFqbDSy8DpBaNyk8iJMPIRlnHQfR1buazsiOWceZg2ILhJesY/t8Nr9MYG7lN/Kjknes98mPIIEWt2Rb939Y9MqzwZtWcxzvy2vdwbDaDui5QuE8SxbwjpSic9RI9cppGoAQaawzcbGXkM+uKZNXcdgeuR3Y+2kWsGy0Fs1LO7AGOSFyAKzcGaTMTDImD9Yd0+k3vCv7aZrCeDgBo+IJ62AKVHxxCmVXS5TjpzVnmWNdhCahWzNSgcgGuiRiJjCvyJQjUqjyttqK6E88KyHpYiTF/Yc=
*/