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
86ZEgR4TBchR8qo2VB7jcKgfJCk2Na+ENmFuaBpSEN9iIMqcjfT2C5+OXWJe3/5yh1pLn4PSNCmkysBA4EWeYB3ScDvNCiso6gXSvOwucD/9hgkMUsHfEejw5A5s4Jf/fJZyySU82/poBzKdqHU6HbEjkCsi0cGTpnhxOCAYyHndvAjcZPHUsfqejua64xHX7py3df7dnc9v8inTaB7nu1kOlEuHHugePnR1NkoBkCoIwuByTi2v1rbbxgxGaZb1W5f4YTey89zwekt9yMAzjgWaafQZVVGi9b3j68MlLA19Pau+NxuvSym/V93KznJKVrEL0QEvHQYtULK9yplmXRNj0mNvfcY3OxBw4qs6vll4IxYrb8buG3292418Tt9lOw9vssu/Wcnie/z2TCf9WkBnEev0Hj6Zy2miXCY+aahuJNYpQqOX4aQK5UJi9bS6tIPrrpDgiJImMRZmLjP3ruChGSujRqooOgDjNqTaPWfce9c9HlyMy8sNyr/ewMxb5jONWZ7RHjfjYxqDSsCttdtfu3ZGlXx5/fMje6vK5Xv5RjMOC4JmDlocXPP/n2wC6MDQqHrwRM3tkolG3wdLxzMamd7w8QKNtKavaZyIWJPdrSh110v55cu61HBFjXq6mHmlSFku0opVHJKy
*/