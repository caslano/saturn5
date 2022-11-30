//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_CONTAINER_DYNAMIC_BITSET_HPP
#define BOOST_COMPUTE_CONTAINER_DYNAMIC_BITSET_HPP

#include <boost/compute/lambda.hpp>
#include <boost/compute/algorithm/any_of.hpp>
#include <boost/compute/algorithm/fill.hpp>
#include <boost/compute/algorithm/transform_reduce.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/functional/integer.hpp>
#include <boost/compute/types/fundamental.hpp>

namespace boost {
namespace compute {

/// \class dynamic_bitset
/// \brief The dynamic_bitset class contains a resizable bit array.
///
/// For example, to create a dynamic-bitset with space for 1000 bits on the
/// device:
/// \code
/// boost::compute::dynamic_bitset<> bits(1000, queue);
/// \endcode
///
/// The Boost.Compute \c dynamic_bitset class provides a STL-like API and is
/// modeled after the \c boost::dynamic_bitset class from Boost.
///
/// \see \ref vector "vector<T>"
template<class Block = ulong_, class Alloc = buffer_allocator<Block> >
class dynamic_bitset
{
public:
    typedef Block block_type;
    typedef Alloc allocator_type;
    typedef vector<Block, Alloc> container_type;
    typedef typename container_type::size_type size_type;

    BOOST_STATIC_CONSTANT(size_type, bits_per_block = sizeof(block_type) * CHAR_BIT);
    BOOST_STATIC_CONSTANT(size_type, npos = static_cast<size_type>(-1));

    /// Creates a new dynamic bitset with storage for \p size bits. Initializes
    /// all bits to zero.
    dynamic_bitset(size_type size, command_queue &queue)
        : m_bits(size / sizeof(block_type), queue.get_context()),
          m_size(size)
    {
        // initialize all bits to zero
        reset(queue);
    }

    /// Creates a new dynamic bitset as a copy of \p other.
    dynamic_bitset(const dynamic_bitset &other)
        : m_bits(other.m_bits),
          m_size(other.m_size)
    {
    }

    /// Copies the data from \p other to \c *this.
    dynamic_bitset& operator=(const dynamic_bitset &other)
    {
        if(this != &other){
            m_bits = other.m_bits;
            m_size = other.m_size;
        }

        return *this;
    }

    /// Destroys the dynamic bitset.
    ~dynamic_bitset()
    {
    }

    /// Returns the size of the dynamic bitset.
    size_type size() const
    {
        return m_size;
    }

    /// Returns the number of blocks to store the bits in the dynamic bitset.
    size_type num_blocks() const
    {
        return m_bits.size();
    }

    /// Returns the maximum possible size for the dynamic bitset.
    size_type max_size() const
    {
        return m_bits.max_size() * bits_per_block;
    }

    /// Returns \c true if the dynamic bitset is empty (i.e. \c size() == \c 0).
    bool empty() const
    {
        return size() == 0;
    }

    /// Returns the number of set bits (i.e. '1') in the bitset.
    size_type count(command_queue &queue) const
    {
        ulong_ count = 0;
        transform_reduce(
            m_bits.begin(),
            m_bits.end(),
            &count,
            popcount<block_type>(),
            plus<ulong_>(),
            queue
        );
        return static_cast<size_type>(count);
    }

    /// Resizes the bitset to contain \p num_bits. If the new size is greater
    /// than the current size the new bits are set to zero.
    void resize(size_type num_bits, command_queue &queue)
    {
        // resize bits
        const size_type current_block_count = m_bits.size();
        m_bits.resize(num_bits * bits_per_block, queue);

        // fill new block with zeros (if new blocks were added)
        const size_type new_block_count = m_bits.size();
        if(new_block_count > current_block_count){
            fill_n(
                m_bits.begin() + current_block_count,
                new_block_count - current_block_count,
                block_type(0),
                queue
            );
        }

        // store new size
        m_size = num_bits;
    }

    /// Sets the bit at position \p n to \c true.
    void set(size_type n, command_queue &queue)
    {
        set(n, true, queue);
    }

    /// Sets the bit at position \p n to \p value.
    void set(size_type n, bool value, command_queue &queue)
    {
        const size_type bit = n % bits_per_block;
        const size_type block = n / bits_per_block;

        // load current block
        block_type block_value;
        copy_n(m_bits.begin() + block, 1, &block_value, queue);

        // update block value
        if(value){
            block_value |= (size_type(1) << bit);
        }
        else {
            block_value &= ~(size_type(1) << bit);
        }

        // store new block
        copy_n(&block_value, 1, m_bits.begin() + block, queue);
    }

    /// Returns \c true if the bit at position \p n is set (i.e. '1').
    bool test(size_type n, command_queue &queue)
    {
        const size_type bit = n % (sizeof(block_type) * CHAR_BIT);
        const size_type block = n / (sizeof(block_type) * CHAR_BIT);

        block_type block_value;
        copy_n(m_bits.begin() + block, 1, &block_value, queue);

        return block_value & (size_type(1) << bit);
    }

    /// Flips the value of the bit at position \p n.
    void flip(size_type n, command_queue &queue)
    {
        set(n, !test(n, queue), queue);
    }

    /// Returns \c true if any bit in the bitset is set (i.e. '1').
    bool any(command_queue &queue) const
    {
        return any_of(
            m_bits.begin(), m_bits.end(), lambda::_1 != block_type(0), queue
        );
    }

    /// Returns \c true if all of the bits in the bitset are set to zero.
    bool none(command_queue &queue) const
    {
        return !any(queue);
    }

    /// Sets all of the bits in the bitset to zero.
    void reset(command_queue &queue)
    {
        fill(m_bits.begin(), m_bits.end(), block_type(0), queue);
    }

    /// Sets the bit at position \p n to zero.
    void reset(size_type n, command_queue &queue)
    {
        set(n, false, queue);
    }

    /// Empties the bitset (e.g. \c resize(0)).
    void clear()
    {
        m_bits.clear();
    }

    /// Returns the allocator used to allocate storage for the bitset.
    allocator_type get_allocator() const
    {
        return m_bits.get_allocator();
    }

private:
    container_type m_bits;
    size_type m_size;
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_CONTAINER_DYNAMIC_BITSET_HPP

/* dynamic_bitset.hpp
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
*/