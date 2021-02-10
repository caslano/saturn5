/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNMENT_OF_CLANG_HPP
#define BOOST_ALIGN_DETAIL_ALIGNMENT_OF_CLANG_HPP

#include <boost/align/detail/integral_constant.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

template<class T>
struct alignment_of
    : integral_constant<std::size_t, __alignof(T)> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* alignment_of_clang.hpp
TxKErTfGuDwkYDePv5Yh3fFs69ZcQw+KMULPOdP5GpRD2tIySW751vKkyfqTRlWGV1bD0Cbc1umRamaQhrVq2/3Q+4+/GD2S/9sf983eYE7LkK6N7h6z2JCEpNf05eD/1bCZoXUvwZUyNzgLvEKCIauldWFSVHL/Xe/TOoW8tdH5rdX0sA5rDhSSqkhDNKUuxiRq5IQnGEyYOQJzTx8m3lplAxoHXz46CIBwyGw8Yxfy5/U5g0CE1FFLs4T9j9VTYSvSuvVEsoujM21H5PZQ2jJhTEyal5BCh4yEpF6EolTqlY3DGCcKqdrJOiFI++CDJBa8MJE8EHd9xOOQo8mWQSBuIXsQAIMYKtoLCWjw/VaWFCk3OwyjqgEVNfCy+mXUIntn+S4b0v3QHHjh/KxVWpoe2v8Zs9Zad8esLhZowRQCbw33NYtO1MSC6wJRB+Xdv51y+uMz/sI2dzC3goNjHrOnhLA8p8iyEFbwVx0M5H7m96lIbKepD3EzxjudXq9VYnO9zU2D0H5UCyTNXNNa6RoO5baJuYR6Jirzd81YMkV5YeI2Uz3WTH95OucPr3S3HIncqWU0rmtNB1MbDwmKhbYjDKB1M7tgav4xamEYlxZuuSqlSrv3BaPZKKTKqIcqJMswSMJta84t4ARF
*/