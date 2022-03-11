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