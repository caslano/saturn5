/*!
@file
Defines `boost::hana::Foldable`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_FOLDABLE_HPP
#define BOOST_HANA_CONCEPT_FOLDABLE_HPP

#include <boost/hana/fwd/concept/foldable.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/fold_left.hpp>
#include <boost/hana/unpack.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename T>
    struct Foldable
        : hana::integral_constant<bool,
            !is_default<fold_left_impl<typename tag_of<T>::type>>::value ||
            !is_default<unpack_impl<typename tag_of<T>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_FOLDABLE_HPP

/* foldable.hpp
6iIlHK3D0focnt4c6mt4aoeh055YG/IMOV/pf8DZ78pjkbIsSroMKdmAMuA8SnnZVnw5CP0w5GXgK1Sq5fkaJXpjGf7dmjLgbI23LPwyI845Rf4pXyqTMv0gk64Jid642ehrVGKiTuntbnrR/Vajr893rXe+0xPnOz1xvtETGLr3N81gTXO1vQrNUeNdYnFzCVY/9yRJ9R8D1wqfXuC49Uh1oq9aOSHaX8lc+qyjHJnHUWc1NsxCJ9kIlu+nXhU=
*/