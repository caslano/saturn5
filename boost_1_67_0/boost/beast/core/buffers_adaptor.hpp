//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_BUFFERS_ADAPTOR_HPP
#define BOOST_BEAST_BUFFERS_ADAPTOR_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/buffer_traits.hpp>
#include <boost/optional.hpp>
#include <type_traits>

namespace boost {
namespace beast {

/** Adapts a <em>MutableBufferSequence</em> into a <em>DynamicBuffer</em>.

    This class wraps a <em>MutableBufferSequence</em> to meet the requirements
    of <em>DynamicBuffer</em>. Upon construction the input and output sequences
    are empty. A copy of the mutable buffer sequence object is stored; however,
    ownership of the underlying memory is not transferred. The caller is
    responsible for making sure that referenced memory remains valid
    for the duration of any operations.

    The size of the mutable buffer sequence determines the maximum
    number of bytes which may be prepared and committed.

    @tparam MutableBufferSequence The type of mutable buffer sequence to adapt.
*/
template<class MutableBufferSequence>
class buffers_adaptor
{
    static_assert(net::is_mutable_buffer_sequence<
            MutableBufferSequence>::value,
        "MutableBufferSequence type requirements not met");

    using iter_type =
        buffers_iterator_type<MutableBufferSequence>;

    template<bool>
    class subrange;

    MutableBufferSequence bs_;
    iter_type begin_;
    iter_type out_;
    iter_type end_;
    std::size_t max_size_;
    std::size_t in_pos_ = 0;    // offset in *begin_
    std::size_t in_size_ = 0;   // size of input sequence
    std::size_t out_pos_ = 0;   // offset in *out_
    std::size_t out_end_ = 0;   // output end offset

    iter_type end_impl() const;

    buffers_adaptor(
        buffers_adaptor const& other,
        std::size_t nbegin,
        std::size_t nout,
        std::size_t nend);

public:
    /// The type of the underlying mutable buffer sequence
    using value_type = MutableBufferSequence;

    /** Construct a buffers adaptor.

        @param buffers The mutable buffer sequence to wrap. A copy of
        the object will be made, but ownership of the memory is not
        transferred.
    */
    explicit
    buffers_adaptor(MutableBufferSequence const& buffers);

    /** Constructor

        This constructs the buffer adaptor in-place from
        a list of arguments.

        @param args Arguments forwarded to the buffers constructor.
    */
    template<class... Args>
    explicit
    buffers_adaptor(boost::in_place_init_t, Args&&... args);

    /// Copy Constructor
    buffers_adaptor(buffers_adaptor const& other);

    /// Copy Assignment
    buffers_adaptor& operator=(buffers_adaptor const&);

    /// Returns the original mutable buffer sequence
    value_type const&
    value() const
    {
        return bs_;
    }

    //--------------------------------------------------------------------------

#if BOOST_BEAST_DOXYGEN
    /// The ConstBufferSequence used to represent the readable bytes.
    using const_buffers_type = __implementation_defined__;

    /// The MutableBufferSequence used to represent the writable bytes.
    using mutable_buffers_type = __implementation_defined__;

#else
    using const_buffers_type = subrange<false>;

#ifdef BOOST_BEAST_ALLOW_DEPRECATED
    using mutable_data_type = subrange<true>;
#endif

    using mutable_buffers_type = subrange<true>;
#endif

    /// Returns the number of readable bytes.
    std::size_t
    size() const noexcept
    {
        return in_size_;
    }

    /// Return the maximum number of bytes, both readable and writable, that can ever be held.
    std::size_t
    max_size() const noexcept
    {
        return max_size_;
    }
    
    /// Return the maximum number of bytes, both readable and writable, that can be held without requiring an allocation.
    std::size_t
    capacity() const noexcept
    {
        return max_size_;
    }

    /// Returns a constant buffer sequence representing the readable bytes
    const_buffers_type
    data() const noexcept;

    /// Returns a constant buffer sequence representing the readable bytes
    const_buffers_type
    cdata() const noexcept
    {
        return data();
    }

    /// Returns a mutable buffer sequence representing the readable bytes.
    mutable_buffers_type
    data() noexcept;

    /** Returns a mutable buffer sequence representing writable bytes.
    
        Returns a mutable buffer sequence representing the writable
        bytes containing exactly `n` bytes of storage. This function
        does not allocate memory. Instead, the storage comes from
        the underlying mutable buffer sequence.

        All buffer sequences previously obtained using @ref prepare are
        invalidated. Buffer sequences previously obtained using @ref data
        remain valid.

        @param n The desired number of bytes in the returned buffer
        sequence.

        @throws std::length_error if `size() + n` exceeds `max_size()`.

        @esafe

        Strong guarantee.
    */
    mutable_buffers_type
    prepare(std::size_t n);

    /** Append writable bytes to the readable bytes.

        Appends n bytes from the start of the writable bytes to the
        end of the readable bytes. The remainder of the writable bytes
        are discarded. If n is greater than the number of writable
        bytes, all writable bytes are appended to the readable bytes.

        All buffer sequences previously obtained using @ref prepare are
        invalidated. Buffer sequences previously obtained using @ref data
        remain valid.

        @param n The number of bytes to append. If this number
        is greater than the number of writable bytes, all
        writable bytes are appended.

        @esafe

        No-throw guarantee.
    */
    void
    commit(std::size_t n) noexcept;

    /** Remove bytes from beginning of the readable bytes.

        Removes n bytes from the beginning of the readable bytes.

        All buffers sequences previously obtained using
        @ref data or @ref prepare are invalidated.

        @param n The number of bytes to remove. If this number
        is greater than the number of readable bytes, all
        readable bytes are removed.

        @esafe

        No-throw guarantee.
    */
    void
    consume(std::size_t n) noexcept;

private:

    subrange<true>
    make_subrange(std::size_t pos, std::size_t n);

    subrange<false>
    make_subrange(std::size_t pos, std::size_t n) const;

    friend struct buffers_adaptor_test_hook;

};

} // beast
} // boost

#include <boost/beast/core/impl/buffers_adaptor.hpp>

#endif

/* buffers_adaptor.hpp
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
*/