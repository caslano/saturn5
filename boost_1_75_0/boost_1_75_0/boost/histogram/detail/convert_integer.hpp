// Copyright 2018-2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_CONVERT_INTEGER_HPP
#define BOOST_HISTOGRAM_DETAIL_CONVERT_INTEGER_HPP

#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {

template <class T, class U>
using convert_integer =
    std::conditional_t<std::is_integral<std::decay_t<T>>::value, U, T>;

}
} // namespace histogram
} // namespace boost

#endif

/* convert_integer.hpp
x1mYy6I3yxWGvZW+zUjLTNWr1PaB+p1Wr1uinYpAwNeJkRa1XPlV8aArTJbSlOiR0mLhPYrm4jS1xut8o5GlibtLcCyeNX292Gpi3XdiVWqtSCzCeak2OeY3i+G2MoalDi0Ss1onXqFNJ65JGlG6tRJJ2uaXAgbMxNaIr/xaS365EWV8qDYce6GTbBrfojtGgNmvxlELI5FMXEIs+aK4W9Ja/XZqGXfT9bnkhGzM1CO5irB6rcLIivYxKRxjqEG34o2HaVYLtgrrQuTzZxrS+/Fh+cNupB7AhA7NjO8iwumXNr7eG+KifVCdvhZVK21E+EZdkB+6+cXrYALnwmQdei/0XQM2XnSCGsOWUHV9nH4HPOxaVRkokms5uCTErA4qIBa8RMUbXBWLD0Y+n3o98rHg5U9n7b+AdH3irQSf9iJF2T4L2FlwQrPqeenowF7DvtTyroHMSkI3bDkTHbc7GQ92IoCiZyMJfvj5ritvRAVCDqC4YlXzoopNaEP2yZwzGCmWWS8GpM5lyVWqeDE45p0rPUms55DiHgN3tfLOdWLQPbqvalSeJtE9KNwMSwTT6ULbUn0MStqjfgwSzAGOMyYjfz3Zsoyy9Do7mdNbbhDEUNpjpE8ldXht+SVT92pTva7z6sPr7A1ft8P+RvWb9Otq8oE96PCIDw0pMhtk584hHTaIzDHLmj8nlPxzR7ATWTyEpHYooqWTBZcs
*/