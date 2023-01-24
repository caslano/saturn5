//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_UNIQUE_HPP
#define BOOST_COMPUTE_ALGORITHM_UNIQUE_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/unique_copy.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/functional/operator.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Removes all consecutive duplicate elements (determined by \p op) from the
/// range [first, last). If \p op is not provided, the equality operator is
/// used.
///
/// \param first first element in the input range
/// \param last last element in the input range
/// \param op binary operator used to check for uniqueness
/// \param queue command queue to perform the operation
///
/// \return \c InputIterator to the new logical end of the range
///
/// Space complexity: \Omega(4n)
///
/// \see unique_copy()
template<class InputIterator, class BinaryPredicate>
inline InputIterator unique(InputIterator first,
                            InputIterator last,
                            BinaryPredicate op,
                            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    vector<value_type> temp(first, last, queue);

    return ::boost::compute::unique_copy(
        temp.begin(), temp.end(), first, op, queue
    );
}

/// \overload
template<class InputIterator>
inline InputIterator unique(InputIterator first,
                            InputIterator last,
                            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    return ::boost::compute::unique(
        first, last, ::boost::compute::equal_to<value_type>(), queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_UNIQUE_HPP

/* unique.hpp
GWhLarZknJwFv2GrjbeHf5NzZgqlLnIRojuQJLdrtpd/Y+R5V/GAx+IlaPSjCJfcfZh8QT6BxPMWnJx/0+Toezn7PoYrsUln4v/ZzgT0QafK1N+45ZOa7fLfYF9iaUcUTuFgPzcmE/Gh/wdWBfChSDIYOUS3vJsVPN2KrBjaY/DTJb+hHMB89l9YyGcfrZUr2Y6KG1vpDO4KJnEmiCmbKWt1ebVPPuCRPxEFTxvZd/phONf8FpDFHv4KBSy5JdQOOAis9MMf429h7UCvVld2iBmA4FlknIa69saS0yWL+5Jl6Bl4gKfUwuhj2KQVX68WHt6Pr1dmu4Fzgh7gtltwN1TWZR4dczToE0NtWqCbByB4+HVq1xfaYPa5TFfJV2OFdXXFNUfTSj4f6xLWflDco0FYW1tccywNrrC2/UJ8G05UTRTce9WL8bULS74YQm+u3YkN4bWtscbyXkmrx/QAzmbhocGYG8D5ySqzp3zfajOqvGz4fk+8Z/HOr8USei5ojNNsF/FwJ7GMKhGuzKQdRnAegYZ56gGWk163FRVQ9PhLuEdCrR0gF+Bk9GC228EngKqxGja/H5notxgzQfY7bT4PW+mFrRiYcP3qCzrbSl8mTw5mKyVImPy6kBFuhKeA4LkqwXQqYkhTXaLx9I2vDGcaTxnYjdlInW/6HqmzPu751Rsn0qDfuK+rQV/6fWzQj+Lbu1zTbkoY8cXt
*/