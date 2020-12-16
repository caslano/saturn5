/*!
@file
Defines `boost::hana::Ring`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_RING_HPP
#define BOOST_HANA_CONCEPT_RING_HPP

#include <boost/hana/fwd/concept/ring.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/mult.hpp>
#include <boost/hana/one.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename R>
    struct Ring
        : hana::integral_constant<bool,
            !is_default<one_impl<typename tag_of<R>::type>>::value &&
            !is_default<mult_impl<typename tag_of<R>::type,
                                  typename tag_of<R>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_RING_HPP

/* ring.hpp
E1mVz6e+yh6tlfyybe+KM2WV+cJUb7PuO6epX27ZI5gPmf+LK3JGhsFKkZV9NS+/slhYYbLF4476KUuCFSTzSjh8U/LT4vzHfvlXZnDdn++XrO+RoddSvsgMwqzJpjRccEJmEGYg69V+XpzMoBZXaFqs7G0IzJksuG+fJJlBmCVZmfU/M5RFwsqSzdiwWPYhEWZFlvotYqb0HVaQrMfH9q6ym7B8ZB/zz2stfV+PX4eQHfryUO7nB6tGNvNJlYrSPxjX0/9BxTTZI+2afds8M5e5hvFzjtkRtlRZCsydbMK8PqbKMmH2ZE1vb6gpvd2Ac57sabDPD5lPmDfZ40SzY9I/GPdo4qE/P7cIg/GzfFq6bYbkB+P8+m/4cVzyg7lxzYrO/yb5wZzInidbFJYeafbk7ZHF0qM4zBbZs6qHHkh+MPXOyaqPX89+n6R/cfKdnG2D7/48IrsJy0lxU0yrX5a6wDwpLnLKLjnnh2lxPeuGyR6Fa3H2yRflPIuFlSXb3W3MBqkLzEA2tXDderLTsMJkR5aF55Vvoo1/3gFZ/f/rQffpypxgqp5ZVtVmcJLUBeZJNrvPp5fKgmHeZHv6/F1G9hamntMxK3ezlFCZCZgl2ddJsRuVxeDfVSI76d5hhOwtTJ2tWVY1KVVmKQVmS3Hni3laSV1g5hTntePRLZklWGGKu9LPxkeZwybjuDYWO/5R5gFzprgthqpzlQXAcpMVyjzWXuYFxvmlly4hexsJK0j2sl5+OZPjYLnoWQo+HherLB7mQnEjE137Ss1gVmTdFk5LV5YG8yCrMbiyhzKTzcb1nLN7q5wTBlgJsi6fu0s9A2A2ZFPGLAmX3GF+ZHFXlsi7IwLGz+n09+IcMi+wsmRD38yTWUqCOZAFzbgzUfKDeXEOV9+clHNiC74LyPoW7txG9gHmwRZiG6HMH8bP+Sx/5SBlgTA3sodhZpHKQrX7fWjZP0pZOKwcWdNrljHSW5gN71HQZqlLIsyfrLv54gbKMrW4ecmHfkruW/GtQVb+kPNk2XeYNdnz+pMCpLewqmRFjzjIs0TAapIF/wrdJM8J8yVrYzdoiewmjOvpmDYxTXKAuXJdJrQdLD3aZvycho3VTivzhXEfLNfVWqOsLoz3KNLnxJ/5hPG8dM6o8UjOcpgFxb259r2h5A7jM8QptccR2VtYEbLT5xdWlN3UrvnPPJdZylK0HCyKv2ktdYHx+eL54uB/pLfb8feyOIcXKcukf7A8fNatSvaT3GGlyPIfGC3v/ghYIc7BYZWHsliYgezqmm51ZXZh3HeXytEdJD8Y5/CXXZO1MhMwd7IznW2DJL94/JPs59WTLZUZYFzrJ83KyrnrD+NaR/YOWi51gfFzZrZ98F72Vruf/dJdVZSFwYqR9TY/MUHZMhi/O6Y3XyA7Fgfj3rZu6NdFWRLMnuyx86zrytJgjmRrUiu8lZmAFSCL/F57ndRlh/HM389T30H2CMa13lJ88t9SM1hOirvb5Ih8f1aDcX7DgipJHwJhfL6sfW/hJzWD8b5HDrWuI3MG43O+78D5j5Xt1nIo0eaxnPOJMN7bFSe7yjs8Hcb9c6367qiydzCe+QcvXsrMe+w0zu+25fX7ynxhnN/QbT3nyB7BeM6ufImQ79ZgWHGuy9KXRZRNhvG3zZkVcRHKImH8zTDww6cmkrt2v7Hx3eWsS4I5UVydbXnkTE6DlScbtL5RU5mJXThTyOrntawpuwLLT1ZvQalZkh+MZ/fdIKsP0ncYnyGxq/3clEXBSnLfx3pUl/xgvCupoWc3Sg7aswzc+SS37AOMe9Sqac1G0tvdxt9Z5reTO0p+ML7mWNs8tyU/mC/Z3cP/KS0=
*/