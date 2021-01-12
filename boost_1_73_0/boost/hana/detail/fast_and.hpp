/*!
@file
Defines `boost::hana::detail::fast_and`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_FAST_AND_HPP
#define BOOST_HANA_DETAIL_FAST_AND_HPP

#include <boost/hana/config.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <bool ...b>
    struct fast_and
        : std::is_same<fast_and<b...>, fast_and<(b, true)...>>
    { };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_FAST_AND_HPP

/* fast_and.hpp
ek4PA0zckE3Rtjtzp5g954wKdZaZmbQgGV3lyM2n0xvj9EkjJ9k+Pdy9rWPhAy8BoqjgNKECZ/GU9BVq5PXDXAJuucYUGZX3SHARutYg8QPPNj+UGvJPQQ2d+PLWcH/FMGebXNYgNP0XaHqiFsezFQaGM/lUMxhzYwaRbAju2Ttn7F4cln9aoQdrPU7PrtDjtJwIViHZ+g6uQ9i5dnnsKxXXLC5/f/9DFBMfReYK+JuB5Llk
*/