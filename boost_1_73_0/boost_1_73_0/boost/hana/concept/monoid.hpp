/*!
@file
Defines `boost::hana::Monoid`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_MONOID_HPP
#define BOOST_HANA_CONCEPT_MONOID_HPP

#include <boost/hana/fwd/concept/monoid.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/plus.hpp>
#include <boost/hana/zero.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename M>
    struct Monoid
        : hana::integral_constant<bool,
            !is_default<zero_impl<typename tag_of<M>::type>>::value &&
            !is_default<plus_impl<typename tag_of<M>::type,
                                  typename tag_of<M>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_MONOID_HPP

/* monoid.hpp
25fwEB75gcfa7/s97YXT6Y7ag27z0hmOBtet0ZCqB7L+O0Bx793QGQ77na2/MeatVgDTdssNvo9hBIslokC2xaL1chnC0riDKQlhWFhrb3vrb14AxKoDHAlkIbjJU8KC8QRoY+JGXuohNDczH01CaG0Ca2eb7e8onIunLPYXHoIDSDOapsGk255n24nCyUdgcivPnQIGgcaMhuBR7CxjWPxJrU6fudPpig27HTa59SYfzSo0X4v1PPbH93FqdLAwgjl0Yj79/PzgZzcKDlPDxnaWKz+IU/igtv3UQ6CqCMjHufOD4yMilP0d4ldzN4qZKkdULShx7L20Qe4twtV9qkdvMfXG6xvZbvOy3wWM/e/ah1XJRNfsxd6h5A7v/GAa3kVsePZWcF125wKLYdC3v1wCO0AqYr/50drF/Wc99UPcDY6BY310mXM1bDm/tQfs8MXBwcstrCf5auxNbmFO9hb+ZBUir8G9Yd8LdtfR/twfr9zV/f7t7Yvjw59+Ovzu6MWn07to7xC+/bznRsvPWzTeGePLZVqTHdXZ06dM/WKvTqlnevpElb0eAsNzfjs8PHBgXD8dOnVcNGLlXTSHDqHlUFsRYql1O8O+021etZ2mWqn6Q7Z9JUfDrgNgL4CfoQez4cf3KJPE4SSc
*/