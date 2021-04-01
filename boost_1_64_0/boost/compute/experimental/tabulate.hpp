//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_EXPERIMENTAL_TABULATE_HPP
#define BOOST_COMPUTE_EXPERIMENTAL_TABULATE_HPP

#include <iterator>

#include <boost/compute/algorithm/transform.hpp>
#include <boost/compute/iterator/counting_iterator.hpp>

namespace boost {
namespace compute {
namespace experimental {

template<class Iterator, class UnaryFunction>
inline void tabulate(Iterator first,
                     Iterator last,
                     UnaryFunction function,
                     command_queue &queue)
{
    size_t n = detail::iterator_range_size(first, last);

    ::boost::compute::transform(
        ::boost::compute::make_counting_iterator<int>(0),
        ::boost::compute::make_counting_iterator<int>(n),
        first,
        function,
        queue
    );
}

} // end experimental namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_EXPERIMENTAL_TABULATE_HPP

/* tabulate.hpp
tRTwVowNNu9O0E52JbK/iiQFZYsVgJv8yq65yQnFnyAIXk7iDzHSaYmActLkJyJls+u0ZZVQ1L8WSi3JMnnkSz2USq+XtH5Hs92dWRVoXiqH/GdqHpDOCYdZ+zG1BAUBNaqi3n3y1xzKGwcAxzdBEU8jlwQppGUcQf+xgxaqad7+mftXczyYgETDZrBDHGM/AXRsDJMcnXV0XbShf5bna+OxxpOB1yeuChEQlqXs+ab5pURlK1UUwRYeDiSCpEMWlAKdhP2GCFI/OVSxIuU2B+LmhXn4XdqL9bCslKMQzB0nx9MVJFtrl8EAFq3UsS06Jq0yZcSaCYz4Dhfwi6s2Rp6nJGNr9Nh7SX7qUodHglfd7Net6fgJiIAIq3SAfH1pTpd5bAoE+YQQY/p1Y+zS6tzqbGZU9ek05+kUS5nI1iqShE8uWM2UANDYZo3jaUnEiVvVynR2Nx7lc4PpTlmLGRLsX1m21dA8F+bBt2rv8yMgMvC6iNICFBnPJikgsr8Vdf/xzuLTosyXctGs8CJ3f6/jmaf5wwZY71I4YM6/FzMUQ8k/sgT68RwGjg==
*/