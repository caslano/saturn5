//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_GENERATE_HPP
#define BOOST_COMPUTE_ALGORITHM_GENERATE_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/iterator/function_input_iterator.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Stores the result of \p generator for each element in the range
/// [\p first, \p last).
///
/// Space complexity: \Omega(1)
template<class OutputIterator, class Generator>
inline void generate(OutputIterator first,
                     OutputIterator last,
                     Generator generator,
                     command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);
    size_t count = detail::iterator_range_size(first, last);
    if(count == 0){
        return;
    }

    ::boost::compute::copy(
        ::boost::compute::make_function_input_iterator(generator,
                                                       first.get_index()),
        ::boost::compute::make_function_input_iterator(generator,
                                                       last.get_index()),
        first,
        queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_GENERATE_HPP

/* generate.hpp
NOGSxqdwwfgUpxZ+3xAbSbam4achkzQ6PuSMF6VbksRgYQo8GW+oJh6N33h8IsN+ka3fKlq7aJZ3qZYP55qF3JYakz+RolzjJhiGg2YWdZlROQ6Cd0HjsvU3ipkHzA9NiveGnEk+mOKu7rId6GgsUBoiQ6foW9wzc3dHmB8cHfAeyqnFZ9Q17GfjYjQzpdxww0ebNWk4skHiPuYBRcWaFuMOrnC+awIemqA9S6WVkP6qBv6D201ajClUzJ2qM1hXwv4iP6iFWsPpylxquFa1z4Rm4exZfxwNYPHNEmpLIG691onpN4C+rtDezuJvZfvuqdjfWtJ37FV+/lgrMZKVIFGkE62x9ypf6C9To19mwstK/aWFAYON5wGBGzumKuFH6bliE9j5GDyRrrwAO4H9FimxBZTbJFgsywFEyhi2SxJe0WCz6ROEzQacalgvGzqZ6AqTWvkNTWrTnO2cttOz2v59VwR+XmknLSlUKwYHAvbYDwwnzNijuZpY5wHNitSs2aauvxXx1Q4m1CnNJuczysHWg2R0Wnnk/teITAtLVqe3fagFKiKr047tVGHzvnCBjV+2Bq6PE6AcdDUvyRvKTfGGxFQ4vDUTULkkBdCIcgDXC3o4AUHPM6yjXgdlXvFicIdJtd/vot2YiTlF6laciwEG1FZWhAI90imxrGp6HIXf7ow1xlHwSK2U4p20S+t88vh1aJ+bZ6bs1nLi
*/