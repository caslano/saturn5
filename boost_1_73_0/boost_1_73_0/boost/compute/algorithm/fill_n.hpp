//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_FILL_N_HPP
#define BOOST_COMPUTE_ALGORITHM_FILL_N_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/fill.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Fills the range [\p first, \p first + count) with \p value.
///
/// Space complexity: \Omega(1)
///
/// \see fill()
template<class BufferIterator, class Size, class T>
inline void fill_n(BufferIterator first,
                   Size count,
                   const T &value,
                   command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<BufferIterator>::value);
    ::boost::compute::fill(first, first + count, value, queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_FILL_N_HPP

/* fill_n.hpp
X2dsb2JhbF9pbml0X21lbS4zVVQFAAG2SCRgrVZtb9s2EP6uX3HTvtiBKjvpgK1ZUExxskZYYhu2syKAAYGmKIsrJQokZcdDfvyOlBy/1GvzoQoSKeTdc8fnnjspnPtw9sMuL7Rw8N0rcb8JXnjfOo2V/IdRc9ohSV6g+UHHOd7fEKoHO6+XpAtv8nqBjvNK2lhX9jlJ3hBubpO0f3rWeZ7YR1xpPFv/gaw2ii9zA51BF84/fPgN3sFF/6IfwA0pORMwNaxcMLUM4Cp1K3/k5Pk51OxjAMwAEeEB4CznGrTMzJooBvgsOGWlZikQDSnTVPEF/sNLMDmDjAsGg9H4KR5+CmCdc5q3OBtZg85lLVLIyYqBYpTxVQNTEWVAZoiA+CnXBjFrw2UZYngGhqlCtzA2CSK0BLIiXJAFhiMGcmMqfdnr0VoJPEkvlVT36JaKMDfF0ameMJuCbEBWBoyEWrMArH0AhUx5Zu9IES5W9UJwnQe7tDBgmfakAs2EaOHQlTPdHIHBtGUrsJZQYfbc2JuWpbbR1rksDgyR1hYoq1WJ4ZAWtEslEh9AXaZMOXtHxDZKy7Kj/Dsl2+WegiwxK/CjKcRTHxZEcx3A53h2N3qcwedoMomGsycY/QnR8KnF+yse3qA2OEZVwJ4r
*/