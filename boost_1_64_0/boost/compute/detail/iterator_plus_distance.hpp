//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_ITERATOR_PLUS_DISTANCE_HPP
#define BOOST_COMPUTE_DETAIL_ITERATOR_PLUS_DISTANCE_HPP

#include <iterator>

namespace boost {
namespace compute {
namespace detail {

template<class Iterator, class Distance, class Tag>
inline Iterator iterator_plus_distance(Iterator i, Distance n, Tag)
{
    while(n--){ i++; }

    return i;
}

template<class Iterator, class Distance>
inline Iterator iterator_plus_distance(Iterator i,
                                       Distance n,
                                       std::random_access_iterator_tag)
{
    typedef typename
        std::iterator_traits<Iterator>::difference_type difference_type;

    return i + static_cast<difference_type>(n);
}

// similar to std::advance() except returns the advanced iterator and
// also works with iterators that don't define difference_type
template<class Iterator, class Distance>
inline Iterator iterator_plus_distance(Iterator i, Distance n)
{
    typedef typename std::iterator_traits<Iterator>::iterator_category tag;

    return iterator_plus_distance(i, n, tag());
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_ITERATOR_PLUS_DISTANCE_HPP

/* iterator_plus_distance.hpp
xsQOBRqMCL9IbGyQpUyHFePb5IAqfRakXmKe2CHyfPexyUZOu841GRHOi4O7sEuRFmM2zFWGIk0GzDjHvJZfpn8mRF+ufc6wzxFN+syIF+Sbs+So0GJE+BWe25xmlzx1+syJvdKaYZMsZTpM/m+fhgOq9AiKxs85nCVDkSZD5pwS9yYZelfXni/ClF4t3wxZkHiNeN4tN5R/4vnNlIO3GwObH1OfI2bfkcefMtYvW+TY/4XrbLzRmqTLnJ03mQdaLL1Z7shM3EubCbFfGTtnyVKhhz0Ogj1Oi6H0XnXf7zGr33UvG0NtkP+e9tn+vrlj+0f6Zv3HxkluZI0zJPiJnNES64jIL431y2LqycOxMbHLER3mFKyDiDiWybP6Nn2TpUKfBf2PK0l+wpha7mOLPC0mpOWvSEK86z80DnJU6DHj8F3iZUj43fpllzp9ZuzVxUWDY0IfcB93IUuV9qetybZ8kKdJ73Ni/O93rdfZ5oAafRakvqQdMlTpsyAlT6fZp0yH+FeMkw0ylOkyJyWnZ6jQZUb8q9Yk2xRoMSbyNfGzwT4981yQy/UPu5c8DY4Jf8TzkLO0CP13v4E9jmgyItJ0H2c5oMqAwDpucmTue77nsviefHxfX5z+gflhTt7aGbIgOdLmWN8/dw9NhgS/ME7m2hq+8zxBUewNhixIfl27bHNIjR7loRxPxPxOa5tYVV7Ypk/wLmNi9ivtTK2X33pt4Sw5atTf4tynrDEOqDEg/Gnn2aLAhFNteSb2GcfsUqJP8Fm5Z4MD6oyJ/c/+ASWCjpg4wz5HdJmR+O/eAHuU6LNg6QvaJUuFAaEvOs8GWSr0GA71YS7i8r0+MlY5zfDv7wp/9DzB6b5+KdNjQeob5oN9KgwIfVMdNjmkwTHhb1mrbJKjxpDQwP1sckiTMbFvi4M9SnSZs/dWY6fNhNjbzHPFvRRoMqbjdWvK+jucZ0bUXB98Qo4ZceaTYqFqHcbf4152GRGpyQ9lusxJvFcu2KNJ8n3ao8qA0PvllvHH1P/vnhnZC8gNM7IR8X7XY2WX1J3l8i3uFWdDfH1G2s15Xm2ou0edNfOyNZKHsRit901iE2P8sxxwl7+4l9N/FT81etT8TdzlrPdsDmnQpxXyNxUJf2+d4ogWoZP+bqbOgHPO73dEdi6gPqGI3+NYv5jzdJnSifl7jSW/E57mdML9VOjTu6znOenLqcvy5f39zSE1Iknn2KNI6gr6ppESB8Mrq8+eecqTeaPcvclcMCbs51red/oC98bM59mynJGlRJsxU7mO/Hd/ntPsVKy9tyuJv0PJ8ju1a21ss6KtyPnFTdX4M9ovkhBDvirv7u0ypebxgfuqzN2TEO9qzVq1llpsOg5ZI+tsUbRO6kzZqJsv9SacUm+T1Q86zz5FWhwTfMi64+D7YjXnBfNcNpcF8xUVY/ViSnMQk9eQHGa1Ffqwug05U5atrTEpa/QUy+qcpuS+JiF5Gr1ZH8qN7zkm+IH7fygnP/7P/gixn1rnP/d8lvM6UypXMm/GfZaZ/GS1UabNOd+xLqnTpyb2XW1uaStH27pu/nePgp62Tmlj+vDzBKlHn8f+i+cJyg9UsqPfIm2mJH6mHY7oEmgn/gj11Bm7v8264y3CnFbn9M/EflI+T8hDyGuAsq2MKJfZ54gRYfedJvZr64ktDqjSY0b8N/LIFoccL8zz36wxTrN5CbmgTIe8fwO4zoDOn6yHi7juc5Qb9nNf/M7adZy9mvmgRd53N/ct7WPu4rvKG8oiDUIeL7HLnvuqNMUwJjq1ftkgS5kuiZmxsEVO/4ULmkOGBGLxbxMHC7Gdo4zOzblzm+JYS/Ma9TikTvK1rnPIgDk=
*/