/*
Copyright 2015 NumScale SAS
Copyright 2015 LRI UMR 8623 CNRS/University Paris Sud XI

Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ASSUME_ALIGNED_GCC_HPP
#define BOOST_ALIGN_DETAIL_ASSUME_ALIGNED_GCC_HPP

#define BOOST_ALIGN_ASSUME_ALIGNED(p, n) \
(p) = static_cast<__typeof__(p)>(__builtin_assume_aligned((p), (n)))

#endif

/* assume_aligned_gcc.hpp
7EGGFZQfDByZqdfrybRNq/t85zEx0xv9lrxNfeuoowB7TVbYgTaVTnKE/157LZyoTA2ykYvyPZBvdZ3aKR+TE1zTY1ouEYsvXvi4kzA+eLUJvauE2USvlIbqr5l3s5ISrlUMaERTLtQCmfeGKbQIqJFYiGZXeWmau1/KJ7YVqeOxgW39tKK6TAWGiZ/8p2FE+BiEinIaTehmc1x4jnrQ/SZPYSknEK9yyB5lnFTmjfrB2kG98mF53x2uWzCWL+wyAmpzV/1oVZiUgsyJcrikqUOkcCVJt/31Rubzacy+TbyI0+zCNxrAH9CusD8LQ6P2hQfV0UFa5O0EhbV4+CSTyzHthROe2wjRqRAhyA1BRQadsxVrOin0JrABZI9s+MQ7zFKe+WhiTPpxA9DkuER/ULbjAzegRRuZGWpVQ9Md3y13aehRUei2KOQzdGfmBa2gD6CX7lwQVn8ttBdcslxEpvNLUoX91UXckz4+wHaQkpgblmuRmBCbh2fNut+BQKB7WMkEAKywE50tOf/K0+ZDVsfzlt6v4PXs9Y7fSjAHtd7YBnkDha7uPDMIS6vKNPMeY29uZye/B9sWJ/RC21w5cZ3TdLUfDLBdt8tkDX6781BaYY4gkNIU2XEf9PWjp1SmLjAWp+H6DkdClzuCRob2qjaCj4GkAb7ye7JvHQKpBNF7DDFFUuKhYP34fYFigCT8nT++lDXWdFQuAZ02
*/