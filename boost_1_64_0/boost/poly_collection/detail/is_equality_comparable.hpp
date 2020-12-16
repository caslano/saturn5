/* Copyright 2017-2018 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_IS_EQUALITY_COMPARABLE_HPP
#define BOOST_POLY_COLLECTION_DETAIL_IS_EQUALITY_COMPARABLE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/type_traits/has_equal_to.hpp>
#include <type_traits>

namespace boost{

namespace poly_collection{

namespace detail{

template<typename T>
using is_equality_comparable=std::integral_constant<
  bool,
  has_equal_to<T,T,bool>::value
>;

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* is_equality_comparable.hpp
+NVhnqLwlgzLIsZ1m8/rQvXJ0ZWKBr753micX8+GyDEdcbxzrH1+Dl+e+/6WHmkOGZ1msvV4NOUodX4/f1HO+2F+29upU2VyDp7S+zrB2VPvys8TOAWHoe/KSg3V1Klx+u1gacuNpkomSCPcBf0dmC84x6njibNd3ACVeENGHzidx2Of9zQdjTPn2XYav5z4Y867SZjKP9Ov32BGHsrBpAmUBgT/qme6yMZoUNvBCiqzZpuvW32cfijEXq4N+JoKvTNFZ8quGdpnFo7+dHaormRvcrBPdrDOvtrnt8nZYL1abdMZ2lab0wfyz+5Rm7xbprquNBi5nPVO3fTegNadyAyo8H5/Tp0O8rb0cFhJFr/rfFzuKcLuiG7rss/H6YDzPfaLY+Cky0n0JByLZDRtKd2Sv7zRyj+7BzizUixaZ++Wft/U5S1bZDcnDMoZqMv4ftndBqeFEb0ulnBP89s1mCQpCs6F/6GPVbOaV6uMPXcb+SpY9RPvxFDaTu4yPwURxMOmoD/pjb4hpt86NzWIb+MP+/XhEXvlG3InFDrMkGW3P3Z1tI9oWWiP8ZOyp7n1qusxJ+RpJDmu7FFUHOqbEtibb2QG3SQ34wmuMuw/KFBGcw67kNHryL9mFyiDxdzfCbDON00/WhDL8a4e2OflkULYThaLOVay0zcLZaSPfxQqw7uEBq1R1ZQZcwrJrOVOlaOIft+HfzPKkV8QP9D5orP17o3BhPNzfsWGOODHpz+E8X4vpU71lZ8bjKWYiFqNvOk7PF98zALW+9sdEW0EnATnw6WnDE7UYLqHvyjuzC8O16VI4WpymGll8H5w2bbisPz2swx0IB9caXAyQATYjhvTT43gQRYUeMBgJ86OwCq4q+cO+Lr9W4Ruo3t70vA+WlaQF3vcx37S34WF8YQIklrPlq79VIZ9FAV0rsoNV/a50/HCOiK89rv17/H9uq2QnWwJnIzBx3cXwOdKkDH8l14SZd/oQv64RZlwGzAjOzi7/bGmPw9nH+C+2/BcviRCH1Ymo+VxrSHjuzlrFi2x6nhzvKm2tvqU1iy8oLK2kjUL9wyzx5/t8K+pbb3764TZvX28Qs6PbT9TtFk5NLZl8pPhbMrUDZ1HJezsSCz5Y1UtQOaz4NaUOt7pJhvVEP/O0/0i7/66huaGtvq6WvenoOMu/XzRZ4XopgUgqhsePExTS2tdosq6X2zdr3Y82c+EZ3jhUDaOUeDUSMPReaIVWTSrMdHhx6YbrtTmMtrUr5q2J6rr1tGuM1/3i8z9Fn7fXfcWmHttWxL1dY2NLaiNR1s+faFPZ9WzsbndAzFWir7IqQ1XoCNVqGcTP/dr1bU4aIvqNreaus4R/WyLrr3WftklFo15CzuEaupt+hNDZSWG6LQRbruWXcBO0PaTLDnDbZ9r0aLafnKobGJz67ptFv08i97M1ibXVdstuZ9il+cHdNfXBWXLLJplaud80Z8ayBX6HVtTB9iwbtwzxjZx3pzoF1j0cPtLLZrVPnTt7eI6PbzH1KLXFkGfae+o6JF7R2eJFrE/9KhohfaH1s4WPWJ/6IRohfaHxouhn+L+0IUlYE9xf+jxMLafy6JvfVwEfTn2M+VFn2n/aPo0MKH9o6b+hXMsmruvUMYyZUdEj9hfCoH/z7C/9FqXfgr7S5edEcJJCYY+Hklf7rez4vHQT2H/6THhCv5W4VzokftP5ddZOsMi41a/t08CF7T2wpwZRU+stvdh3hKN6eFvcEFdq8/Kx+nUX7+umwtjqCzgu+wJ+bi+oR1+W6P5dIb7XtZbA76XlhbAiG/zDP9IFncqqWGwTt7Lfykz47TR1M+5XWBPabrkl3n3ArfMKU2XnFU=
*/