/*!
@file
Forward declares `boost::hana::fill`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FILL_HPP
#define BOOST_HANA_FWD_FILL_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Replace all the elements of a structure with a fixed value.
    //! @ingroup group-Functor
    //!
    //!
    //! Signature
    //! ---------
    //! Given `F` a Functor, the signature is
    //! \f$
    //!     \mathtt{fill} : F(T) \times U \to F(U)
    //! \f$
    //!
    //! @param xs
    //! The structure to fill with a `value`.
    //!
    //! @param value
    //! A value by which every element `x` of the structure is replaced,
    //! unconditionally.
    //!
    //!
    //! Example
    //! -------
    //! @include example/fill.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto fill = [](auto&& xs, auto&& value) {
        return tag-dispatched;
    };
#else
    template <typename Xs, typename = void>
    struct fill_impl : fill_impl<Xs, when<true>> { };

    struct fill_t {
        template <typename Xs, typename Value>
        constexpr auto operator()(Xs&& xs, Value&& value) const;
    };

    constexpr fill_t fill{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_FILL_HPP

/* fill.hpp
8b6yd4NgQK5B74bIWOGzvFARwq6e51cRClx1KnqGXRWtYYknLmRf2QF++q/X2ueab/VqOjrZ25Vl6Yx0bwjLFl5B9tqdlHVR9hzLLqDsbyxLpxp7Tyz0H8fuPcSyG6nBh6wBnQvs3cVK6cwT75Y7xffg1qyhd2FWDw31rExHc01FzeDt13yeB+qR64tcUYhcpvD+su8anc3mXUjIRh7xPsLSzd4XWVrjTWHpJu+TLD3lHdMS/QMbgPGbbX7cu5ErimwH3CsY7kqvhfWt8HYTcXZk6XFvsIjzWm9KD3j/YmmV98wCOh+u3PsLu97oPdGb0/gDUs/ILd5vWbrBu1ss38Ou13s/F8v/2bsljWuJ/0Ya+xKNlR2J/woS4mk6+HU+hr1RcgcamOTO0nfjHmhA7jfkitaFouf7FXz0Kb05V8aW3R84gB6ffOIf9X3qG0Z9sys451KR46u9OI7zLC321vbiEvq5Fx/j+14tOdoCjJMacY8m3L3bAnfXCo7zHRHHayKOl3rxMZ8Rx1o+vyW95cAU3Ijz6lbg3Ewz+cVejusRsW9CK30r0GPfVn/fL6hvFdFTsJePq2uFh0q0fKGxj4f6RHdGn9HieBJxvO97chyHe3JN+bIn16wyMf20Z0vcxcBoasR9H+GO7Arc5/dwXG+10ofmK7ixz9WPiX8F8U99VtOR394x88jUKiib2/OaPzurKTu5Jd6VdGI+
*/