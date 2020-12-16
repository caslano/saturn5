/*
   Copyright (c) Marshall Clow 2014.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  is_permutation.hpp
/// \brief Is a sequence a permutation of another sequence (four iterator versions)
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_IS_PERMUTATION14_HPP
#define BOOST_ALGORITHM_IS_PERMUTATION14_HPP

#include <utility>      // for std::pair
#include <functional>   // for std::equal_to
#include <iterator>

#include <boost/config.hpp>
#include <boost/algorithm/cxx11/is_permutation.hpp>
#include <boost/algorithm/cxx14/mismatch.hpp>

namespace boost { namespace algorithm {

/// \fn is_permutation ( ForwardIterator1 first, ForwardIterator1 last, 
///                      ForwardIterator2 first2, ForwardIterator2 last2 )
/// \brief Tests to see if the sequence [first,last) is a permutation of the sequence starting at first2
///
/// \param first1   The start of the input sequence
/// \param last2    One past the end of the input sequence
/// \param first2   The start of the second sequence
/// \param last1    One past the end of the second sequence
/// \note           This function is part of the C++2014 standard library.
template< class ForwardIterator1, class ForwardIterator2 >
bool is_permutation ( ForwardIterator1 first1, ForwardIterator1 last1, 
                      ForwardIterator2 first2, ForwardIterator2 last2 )
{
//  How should I deal with the idea that ForwardIterator1::value_type
//  and ForwardIterator2::value_type could be different? Define my own comparison predicate?
    std::pair<ForwardIterator1, ForwardIterator2> eq = boost::algorithm::mismatch
        ( first1, last1, first2, last2 );
    if ( eq.first == last1 && eq.second == last2)
        return true;
    return boost::algorithm::detail::is_permutation_tag (
        eq.first, last1, eq.second, last2, 
        std::equal_to<typename std::iterator_traits<ForwardIterator1>::value_type> (),
        typename std::iterator_traits<ForwardIterator1>::iterator_category (),
        typename std::iterator_traits<ForwardIterator2>::iterator_category ());
}

/// \fn is_permutation ( ForwardIterator1 first, ForwardIterator1 last, 
///                      ForwardIterator2 first2, ForwardIterator2 last2, 
///                      BinaryPredicate p )
/// \brief Tests to see if the sequence [first,last) is a permutation of the sequence starting at first2
///
/// \param first1   The start of the input sequence
/// \param last1    One past the end of the input sequence
/// \param first2   The start of the second sequence
/// \param last2    One past the end of the second sequence
/// \param pred     The predicate to compare elements with
///
/// \note           This function is part of the C++2014 standard library.
template< class ForwardIterator1, class ForwardIterator2, class BinaryPredicate >
bool is_permutation ( ForwardIterator1 first1, ForwardIterator1 last1,
                      ForwardIterator2 first2, ForwardIterator2 last2, 
                      BinaryPredicate pred )
{
    std::pair<ForwardIterator1, ForwardIterator2> eq = boost::algorithm::mismatch
        ( first1, last1, first2, last2, pred );
    if ( eq.first == last1 && eq.second == last2)
        return true;
    return boost::algorithm::detail::is_permutation_tag (
        first1, last1, first2, last2, pred, 
        typename std::iterator_traits<ForwardIterator1>::iterator_category (),
        typename std::iterator_traits<ForwardIterator2>::iterator_category ());
}

}}

#endif  // BOOST_ALGORITHM_IS_PERMUTATION14_HPP

/* is_permutation.hpp
Sdq0M+dxB54Ni2bdkrnDs6RzaxZCiR9/8si61fPwZ95k1DiSpbiy5klQ7ielFXsoGpkOtYsnucl9M0L0IlfxPWkmTzul20MMyqrb3aTcpQB+I6Egw/t6Gqvnsaz/zJi1zfrzqzfC+/PNGUZ/QvvpstKF4LtruP/Ooo77amZLHVdliWWkrrIq6wHAOQJP72jryeHaSry4XNb/6ag2IJAorOY5uuBXyi3v0idryGL+nSB3llOxk/oMcQGpIb/n6fRnxpCtna6awQ3Kr7hDI/lJJnbDAqpfB/bmc52vfPYs1XllurJkETe46gp0luj3wTQPhrv4sgTFjxFTAUQzKl25DyYPbnkQyK7aDfQznShKhlHkQ4Mv27/Hny58XlziycccJLQL5nLqg2yEh4mGod50H7OcDBTE2+8qjSb+nmFtJaPYkegWNag8C9CcXTN2cI/Xjvh13bJp699rPBLQOIafyeelC0kZ+DTzV1mslRDX5xNQKMxbpYRIVmg2O6yUp6XDgAAts+XtUiqLqGn3ni96oQe0HBxk1a50fYF77GzRA88w2Izdegy0MGeV/KhN6VNwX9ns/kbI2+DKv3OLOJhtvUv3zlDYi1ogxtBaxGOoYT/pXQP7sYsY+wsE9vtmC+xBK+HkFXLuBzeWe6bug41nOrjZBVzNA1o8n51urANT3TIF2PW6RSzEVx9uUMmgzCJ52zBN1L246ZR/tPX/VW6rdmu96XDPw5xrct7vCu9iaMnpXhyS7Xle3ZF7DM2lICxCOAM9G6NFrmQFbmu+/PT604JN33ODLZzHna5hLI+wEtc9D3O79llxzvYEn7NdjnW0j891WGnEAhg6qEpUGrDe9r0d+BR2q5ioMYinxQL6ImrAgnjEN7BcCYQVU0YExCVezFFOqc2YfoI3JDT5Z6WGbQJ36aPQXYXoLyK0ai8ByyzwqHbemMJEf0PTUJ9sW0FcSM4s/tHsgcjgspIDwTZ0Id/LXsbohJMPBROUdHzTG1/XpioGDITpJx4tsueRByOKcVy6jRPAkdvyl4QrysyfG1tUa/+KkH741rkt2D+E5b96bwv677B8a6AF/XdY/to5Lei/l4fyr2mh/nVh+RseakH/HZZf5m9B/7083F/Z1OOppoj2L9fPt1fjfDt9Qdj59mo+0S5cxufbndfw29hlJ36+Le6/6t8PdKPDttqRWKeatP8VkW+pVpyzyUCmNcsYnf9r8HJeN27zfLw3kf8j8qc92zTfE5H/SFHT/CER+YOBVJP9b0R+74j81Ij8Y4Gm+Qdfbpq/Yhryw/prx8t6f1m5vzLQ4U3aH8pXUmY177Bm4298z8rfmxDR/7dE5OctaJrvjMi/KaK950bkpwOnJvQfkd82Iv+LZU3zyflME/qPyJ89tWl/LVqm90ca99exl5qWLw3lK5/f+9P9NUTAG/YXORH9f2lE/pnPRIx/RP4lEe09uLRpfj1waqL/iMj/MCL/9Yj8+e9E0H9E/uC7m/aXZ6neH+ncXxuXRNB/KF95bcZP99e5At5YkxOXRox/RH7t0xHj/1LT/JiZEeMfke8HTk34X0T+SxH5pRH5E96OoP+I/PS7kN/K/k8H3Y3bnIeKDP9zV9CZds+5mgXLecoXEM+QfAYEou9AHQSSiOWZ5bI/4704aPVQGG049J/ETsgW88UCMFk7KiWwRhTTdjqVpxyBthn+05fomxjc+LXca2y3ztYcr+/E/lZzxQ7UJhNq7Rm1Rtp//bPCwKnqhHDSxn+Jzt+5e+/Gdq0V+VYguWNx2KaQqLiCPJlKkDKUddN5Z9SNXjgV7qtXIk3eVfrNtNPIqSl7LK8bXG6hP3nwdBcH0LpcbA/T5B3Ki/c=
*/