//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_3_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_3_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T*, const V&, const boost::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V&, const boost::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[1] * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((a[2] * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_3.hpp
OVKhprUUE41zg/vNkmAs394JZfMc731/aRRD/suFza7BnCmK55dvTAw4C/kzsFnxpmmMrNFuXsbxDDrnNahusMFCVsHksi6f50MdXIZ1WVOjhMLpbsB/Ll8U3yRZLn3QsOCWsM5WMr8ix3VaLnuOEVNJ17YzD7twxFb6Ea/m/BYRpoWjjUFP908JTTe3uzG0lyLR73C5iOevjHJYJH9aGtD6Iz14kSG21xcvw/Kkdc0ctg4Cj4Lun4r757n8sia0qhvFkId87GQ9VfiN6C+d8zvEZVMxJiiAW1mFafzochGj3tKGcVnDM8ser+uNixhgy0X9V41yVDEIOo7FX84Bjj8c7rFKVhMb3hfYfZbPnk2fQTQ6e8c9tlzGIkm5s44RAE2KmPoPeHixp0Ix09Yw1ESg80sJ6llDPiEg16AGCyZYyyBY+UBEupf7lFz+YVRqY5UWaOWJvt00FNq1lfNqJEzduqrh2ZTKDrtSz4lvY4L0UeQMJZpQiVYOD/Z2L3br4YP13XCReYCroi8gxJO4JrWscl/AvWF3qolvYgI8jBplK6yMgneHFzv50qfjAxDPWMcbgds0jUr2nYv1tMh/hRtOlMPF3WGPhrcPPXAZa+H7EJM4i02b3N96E6Ev7++LusII16SVJrcROCtlNh57BMDTTMmmbdJMKZmY7kffMpfBAllSsVY3qrBx8SHAxGTjQyCmqVhFCU7+XsnINO6hRxS+W9hqbHRu4hnKVkYxiR1IK0Z11VBTEVO+q1gTPX5PPJclGHFiCKOuMPNMF6Jy1e9h70yG8NzprO8VBb6gWlW2lemtQujF6kXYYPNboM3CCmubGth82iOOY9kWmNZZzAR407H0a2UxvlJhsyHaSVaLwujTc4wGafh1kQanZdu22oze/kx20xhH+pFQlhvVukbX5X3/1GaT7C0LWaoMcRrjaHvyWou4eJh3AlmNqFW0MZrNbbvg9n+yWxX4pGklIbIe2X2YruTGNzGBbIW0wdroypR2p3acZA+BLEENkdYqx0q7Mwd0HPdZgKxCRBrZaGvG7bk0O9n9ngKfEaollqK0O3NKJ9G/Mpc9i3ltbFM14b4VXr/Yv78Tz86L/NUUOykUKN/CD5lEXy0gyxBTrWwqM3vh4dzK1sHeUdgQTrCZ7F8LXFNxIdoKlCvwTs7sO/GofEzlVGnSNN0lhrF9t30UxGFaGFrZurSPED3CeUAue7atOG60ssGbbIyzWOBwR7m1fPwWcWZPnNfmsss0TP1dw5B/1f1gkkxKcatWC6y2YbZRjYE2gTZJhj5wC8hWSFZSSYwJmq5fmJBZoMZpxEz18fkFZqOqmnMqoX2gHZI4z8hlDcI1104R7eNpbPut+p183nQ+zjMAHkFCKSYbq6GNoP2R6OuVyyqEiRbOVRbt9DFKGgr9Rz5eYClFakuUg7aBthbz8/tFfjJtuSWtQpf9PHp8J7KKcdaK/MRY4qahxbvIsN3Fs+lHQ0zMK4upFGjq36IdY6JB7o5ADiNiW143qUspncOHdvCQXO5hsrKsJVzOLDzYgXn5yAKjtaFHqQW0a357c7nsEnO6ohjz0FuvDL4Zp6PPfoHTmEZpbCpoTGxvAGcnlz1LWasdN9Lj6Ir0h3YR57DAYdJVklUa2gPbWoyHmssaJCtjq8blzwKlNyKiX2+Bx1vVCKkUtAu2s/g2Ry67rBtXC1nPIr0989CL7Bc+rx8EWAR1U2MuOLQNtrH41gaQ5Ug42UjpGjSEQ3iM38acOfguEbcy8l/+dYFNMFPWkRraCdocinERzsN1fcsFrwSLhh7t7vkTkMnoHYZb5nLLjcKaVIx3YtNup6aTSHsed835sUHSaSwZG5s=
*/