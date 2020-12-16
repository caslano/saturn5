/*
 * Distributed under the Boost Software License, Version 1.0.(See accompanying 
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
 * 
 * See http://www.boost.org/libs/iostreams for documentation.
 *
 * File:        boost/iostreams/detail/restrict.hpp
 * Date:        Sun Jan 06 12:57:30 MST 2008
 * Copyright:   2008 CodeRage, LLC
                2004-2007 Jonathan Turkanis
 * Author:      Jonathan Turkanis
 * Contact:     turkanis at coderage dot com
 *
 * Defines the class template boost::iostreams::restriction and the 
 * overloaded function template boost::iostreams::slice.
 *
 * This header is provided for platforms on which "restrict" is a keyword.
 */

#ifndef BOOST_IOSTREAMS_RESTRICT_HPP_INCLUDED
#define BOOST_IOSTREAMS_RESTRICT_HPP_INCLUDED

#include <boost/iostreams/detail/restrict_impl.hpp>
#define BOOST_IOSTREAMS_RESTRICT slice
#include <boost/iostreams/detail/restrict_impl.hpp>
#undef BOOST_IOSTREAMS_RESTRICT

#endif // #ifndef BOOST_IOSTREAMS_RESTRICT_HPP_INCLUDED

/* slice.hpp
XnxIx186DTa9kIseR+DtYxufIGxkX1T08/uiU+T6vk6+0Re9YTX7oq7eWaJ3xLiB6mc+N3J1LUI50fGNJdTZsogymWr28RJ8vxKHbycUlPEgPwJLGRE+yXo238fZmk/Swc9LJ7x9Dm7r21L436m/Jq+hT6Ly2kf7ijH743uITCdbvjW+QEQbsueZsH4ZVUiFVk2qkOAN41HdJcyOTjc3HG0j6NS3i+kx+vnNEygvbRdmWwlrF4XtotvF6VmkGVVWZr81sXZRHwftnLCniK2ZGYO1nJBZ/bbRWfNKWviZaYW3j7xQdJ7PRqY2Os/aD04sv7VGHZ8p+VVpa14JvwZ59e4D0sFP04nIZ/P20flc5vanI/OZbH/6k8Sfh/PWII+2Z5qZv8/b2+uxzpI/6Y8nmL86L39+PYq03fayEfIndahpmPmbnxGdv++oP2dRVP60P59Y/pD322luTzesStvbKeFXP49eOyUd/Lx0In63dIjO5wlZyFjyqbd0QvnMNfJ5nNSjSlvzSfhGyCfp4OelE/6svS4zOp9HEL7Qkk/v90WibbbQyOs0yasfg93WuxHyOk3y6qUTnteaLHteiy151d8pCee12JJXjcHeJ2vcvJJOxHeLbHtep1vyqr93Esrn9Kh8qnSsd2fj5VPTCc9ncUd7Pmvt+aSgEstnrTWfSMd6bzZqPiWd8N+vOdH5vJDw8yLzqb+/Em23yPvvlfMlnyJtf2+uQR699wpp4CdphPd/OkXnb7n7nSg6f/r7LbH81Rn1uI68VzzpGO/ONcijV4+kg5+mY9g7jQs03vpaeY+6/r0PemvFt/mf1k6o2PPon4//8e3Y9j92+6VYdj6NZzfVWOuz2e2FYto1qV2QjsPAEy12QRuqXU4+zIS9YQ7cGHaBm8IhsAAOh33gvrA/3A/2hWPhFvA4uCU8Qa9/Bwv98RHS0vSb4PpF2AV1gy1gd9gR9oB5sJdhZz9d42mu8Zh29gdw2bPvbwZHGXI1KtfMIreNyg2ATeG25nyAOOndp3JzNb37DbnZceTeVLm3VO5tcx5BHLkhKjdU5fY25ObHkXtO5Z5XuRfM9YjiyDUN1Ms1g81gc+jJLYsjd6Omd5Omd7ORnvNxbLlLVG6Gyl1qyIXiyJ2qcqep3OmGXG4cucNVrlrljvDlcHHkxqrcOJUbb8gVxpFbpHKLVe5TQ25oHLkfVe4nlVsBvfu6WOXGWe7rdnpfhfS+ztD7uoPe11mwH8yG/Q17v3XhANgJDoZdYCnsqvc513X+h34vgu01fXP+R5HqXQxbwRIYgqNVfpz37QXuq/ItcaOM+SsBuAPMhjvBznAg3AzuDDeHg+GWcJDquxvcC+4B9zHny/jfMOz6Pq76PqH6Pqn6PmXI18aRf1fl31P5hSr/viE/L478CJXfR+X3Vfn9zPk2ceRfVvlXVH6+yr9qyDuLYsu30fu9LWwF20GZ2ws9+dw48rdr+ndo+rM1/TvN+UZx5K9S+VqVv1rlrzHki+PIn6vyNSp/nsqfb9Z/HPnjVH66yh+v8ieY9R9HfrLKV6j8FJWvNOs/jvxSlf9a5b9R+WVm/ceR/0PlHak/oPWXBmchxNycpOZSmbaxC3BqD6s2sNH2r5+7HIr9aYR964W4TLVpxZ4VO9Zo21Wd4+TbraarfepJpk2qb48abYuqNqjYnxp2p3abU7UxJVwMm9KRYjuK+y3dKcVNx92EexG3HJfze7ozADcKNx13He5Z3BJc6A/mHeFG4KpxF+IewtXhmrs7D+CG4ipwF+Lm4hbinEATpwduEG4cLnWkjtSROlJH6kgdqSN1pI7U8c881pL9/8Txo8X8f43s/9d1Wout15JjHSc=
*/