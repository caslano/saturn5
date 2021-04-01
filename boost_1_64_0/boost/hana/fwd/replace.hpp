/*!
@file
Forward declares `boost::hana::replace`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_REPLACE_HPP
#define BOOST_HANA_FWD_REPLACE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Replace all the elements of a structure that compare equal
    //! to some `value` with some new fixed value.
    //! @ingroup group-Functor
    //!
    //!
    //! Signature
    //! ---------
    //! Given `F` a Functor and `U` a type that can be compared with `T`,
    //! the signature is
    //! \f$
    //!     \mathtt{replace} : F(T) \times U \times T \to F(T)
    //! \f$
    //!
    //! @param xs
    //! The structure to replace elements of.
    //!
    //! @param oldval
    //! An object compared with each element of the structure. Elements
    //! of the structure that compare equal to `oldval` are replaced
    //! by `newval` in the new structure.
    //!
    //! @param newval
    //! A value by which every element `x` of the structure that compares
    //! equal to `oldval` is replaced.
    //!
    //!
    //! Example
    //! -------
    //! @include example/replace.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto replace = [](auto&& xs, auto&& oldval, auto&& newval) {
        return tag-dispatched;
    };
#else
    template <typename Xs, typename = void>
    struct replace_impl : replace_impl<Xs, when<true>> { };

    struct replace_t {
        template <typename Xs, typename OldVal, typename NewVal>
        constexpr auto operator()(Xs&& xs, OldVal&& oldval, NewVal&& newval) const;
    };

    constexpr replace_t replace{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_REPLACE_HPP

/* replace.hpp
G5c6RTHw6ppaCSDeABtwbL88ilujIUUpGD9mvSsWhJ0dep96MDeQNZO+tBaqEKCVvPdT9SGcxXQ7650zmBGm69H4p6ZvzeO9qKPGw4wn6HFI17NxgRHiXmDoug8AOBUCYwP1j+nnmT5h7iBFzlgtKZ4UVRqnRcAnNbiZw1jUMHVfnhp+59EVhSOz4YYziKQVkozSecE6TIyFokxw5j2s2IZBw+YRJceNSk2fH8ULpvSoa86hTx4i9f96cu3VA2RzV+Qj8ZntaLACHUsBpimmc3Kogz0rZGgKl3+zbPMsJ/b+ASfzAP+xMOecNOkCdZ90t2xyWelO6GAfRZvRZt4yILx8zurnVab7r9DkkrtmMHudErAZIjRrg4I8QT8F/fZfvX2fJmiL6u6oaDHu/MQdpQ/EoV31rF3DOWFdc8IWIV7FUDjW51VL8GukUIRzRKilPIAjb3ShQ/Ebp0NlmWUe4fOdZ0lRVF/w+CGqRVnvUlnIlWUb4I5sPpDxTy3x8t2skRlmp/p8v+nnHz9cmWo6EICYuzfF5Jk0a3oY0dE9QYYglXmX1Rd2F/7Hgw==
*/