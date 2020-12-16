/*
   Copyright (c) Marshall Clow 2017.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  transform_reduce.hpp
/// \brief Combine the (transformed) elements of a sequence (or two) into a single value.
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_TRANSFORM_REDUCE_HPP
#define BOOST_ALGORITHM_TRANSFORM_REDUCE_HPP

#include <functional>     // for std::plus
#include <iterator>       // for std::iterator_traits

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>

namespace boost { namespace algorithm {

template<class InputIterator, class OutputIterator, class T, class BinaryOperation>
OutputIterator inclusive_scan(InputIterator first, InputIterator last,
                              OutputIterator result, BinaryOperation bOp, T init)
{
    for (; first != last; ++first, (void) ++result) {
        init = bOp(init, *first);
        *result = init;
        }
    return result;
}


template<class InputIterator, class OutputIterator, class BinaryOperation>
OutputIterator inclusive_scan(InputIterator first, InputIterator last,
                              OutputIterator result, BinaryOperation bOp)
{
    if (first != last) {
        typename std::iterator_traits<InputIterator>::value_type init = *first;
        *result++ = init;
        if (++first != last)
            return boost::algorithm::inclusive_scan(first, last, result, bOp, init);
        }

    return result;
}

template<class InputIterator, class OutputIterator>
OutputIterator inclusive_scan(InputIterator first, InputIterator last,
                   OutputIterator result)
{
    typedef typename std::iterator_traits<InputIterator>::value_type VT;
    return boost::algorithm::inclusive_scan(first, last, result, std::plus<VT>());
}

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_TRANSFORM_REDUCE_HPP

/* inclusive_scan.hpp
bGwST4/g2egsXrpV1yC1haGKHgYXOp9l072BVu93cyQqS1UkzYTuwKUPruShHz84Pf5jgdeWYqN4/iG5j7ixUGZcSHkf+yefvYsxYPDT/8s2sIh2zR+vlagYw3oteuQrwP5ksJ30R9UTedq+oFXvVuxLwyGQL7df7wUb7Wy0ZAn3hx6/qbOq9hQn7b1uTHQ1Fp3RLQdiu7H89CZftEpTP93sDMtAIWRz48QedIqTH1aTZ5Gg0wgakQTxjszLv5tdWW6SmkI76/JM6jPNc80lfSHmRhceNeYjZLfRNVi0QUHk2mHmlt8Hxwh+NeTAzTwP1+J8X9PNXrgwaZLBlb36NvVsPU8eoB+cTwfoMmiBG4g/T5fqxjbj9TdgWIPLylsnvo2Vp44K8afBKInGVBu4jRw0lyjrzP2y+6XWwrNw2psN1Z3480hvhLpnrdK8cQyLn9VDf3LV3jnOu6OsKk2+vEied4FepLPd6lC25SjV0CGJ6izG436YpNvmSc+j19nzaJpUjt4pFv+C5qm+iRgmax4RmNQOVBxfllSMakbXbPWsGDOOlwUWUK+wBojUgu+LpwexuOZUPqBf4URPhUsI7WvhWLpVzqDdLp0Mh9rJ3C1sgpQs7/F4GEkGYotDXU+FyB3EDmmvfy+bNkBmzG9GreM9IdHXJqtloVrN1RixOPgAEy9r5wY/JnPbI7dqoJlqa1Dww9WUjIAR2dNSqGLwGYrJ+uQgksuHZmIfTaUw+qlYYXosgTdfjrH+eJYEuwXF5amq8uxPvfLB/5wK3snOKdrBj9CQU1QDhxIGBzZ+osDh7g80MUIC4u/J8LLKUdMzHSVG7rkv+wjBv50eMLYm4vXiCj//hwWavXwc76m/s9fzf6iX/w/lnPb0h+7R7jNxpo54QLdLxXHLDCZwZDhj20hcZbpwH1lV/z5SbF3kpc7r3qJzsCicpV4Rl2DrnmgWGRJBnHiGmxBNWKV7018Im++a8uPuJ1X55x4f+WdgEPnHJ188EET+me9j/zgsiPzjk7/xxiDyj0/+rUHqF/nkHxsQJP6vT/70IPCzffKT/fpPb7UnjMKNkjSkvVIWpFWeBxW2vGl0DzMTOWValTp+axrGBk6lGkd5GeIAnGkWEShspMWZKDqxfUaL2cDqXhxWk5x5vBLxvQfwM1A5dod7lFns0QvhVQdkvGukprtk6pYDVxCzuw6JYHPWarrRLPSEuaIsq7+Kmmsq3BIHmOGuG/FGofiGGJWs1IQq9eRj7r1E4W8TKi3GZOUo2Zlol7gCc4McMLgWOWq0d67Vm2u5qNbLqAXwcZaiN+Q3s2tEjuKyk7H8ILJ1zyZdzOEs5nVQR8Am/JZsZp2d2Z5C8s/3ihljqej+MUwAuZI1ds/WPI1/zcw3h96be4+44J9szO7TqT/D5NBjVv9CbpLPzKFNco1w50Ei3eqpbomuUTm7ro+u+ZCtqwhQ8951HvqsKuZP6C3eu1taNc+COFDkWTKIcmc56jz6w57jZDPpaEbZg4b4TjYRjWEzPpGvKT2erIwyyFvZpyGlspIcK2KeG83rV12Ef+gNFAz/TVz00ey68jGBia47aVPPsPHm7s5FxGVs0mDNq1+Xan2+EiKrkzepL3fz2AfO0sb+wmw59kcgg8K+vF2ah0p1kqXu0kotUkvNuFUOvjJDGmjPQr/vRXNixu3IKFxkN/Br4vxGDd6t0QUMoHt+LC2vmdbs6sH0UB0ZW+Ny83K/YPPv/buQ/r2VS77UTDES+BBNOvfefH+oU+Zwo0qZ9+MLSXvYvCT5jeGYIYTY1TM4b6B0WsglHVw6jFwHsmZtrJm4Au3mjgSSFBvM1Lwq8Dyv9Hb/9k5O0ts=
*/