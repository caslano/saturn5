//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_FLAT_STATIC_BUFFER_HPP
#define BOOST_BEAST_FLAT_STATIC_BUFFER_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/asio/buffer.hpp>
#include <algorithm>
#include <cstddef>
#include <cstring>

namespace boost {
namespace beast {

/** A dynamic buffer using a fixed size internal buffer.

    A dynamic buffer encapsulates memory storage that may be
    automatically resized as required, where the memory is
    divided into two regions: readable bytes followed by
    writable bytes. These memory regions are internal to
    the dynamic buffer, but direct access to the elements
    is provided to permit them to be efficiently used with
    I/O operations.

    Objects of this type meet the requirements of <em>DynamicBuffer</em>
    and have the following additional properties:

    @li A mutable buffer sequence representing the readable
    bytes is returned by @ref data when `this` is non-const.

    @li Buffer sequences representing the readable and writable
    bytes, returned by @ref data and @ref prepare, will have
    length one.

    @li Ownership of the underlying storage belongs to the
    derived class.

    @note Variables are usually declared using the template class
    @ref flat_static_buffer; however, to reduce the number of template
    instantiations, objects should be passed `flat_static_buffer_base&`.

    @see flat_static_buffer
*/
class flat_static_buffer_base
{
    char* begin_;
    char* in_;
    char* out_;
    char* last_;
    char* end_;

    flat_static_buffer_base(
        flat_static_buffer_base const& other) = delete;
    flat_static_buffer_base& operator=(
        flat_static_buffer_base const&) = delete;

public:
    /** Constructor

        This creates a dynamic buffer using the provided storage area.

        @param p A pointer to valid storage of at least `n` bytes.

        @param n The number of valid bytes pointed to by `p`.
    */
    flat_static_buffer_base(
        void* p, std::size_t n) noexcept
    {
        reset(p, n);
    }

    /** Clear the readable and writable bytes to zero.

        This function causes the readable and writable bytes
        to become empty. The capacity is not changed.

        Buffer sequences previously obtained using @ref data or
        @ref prepare become invalid.

        @esafe

        No-throw guarantee.
    */
    BOOST_BEAST_DECL
    void
    clear() noexcept;

#ifdef BOOST_BEAST_ALLOW_DEPRECATED
    /// Change the number of readable and writable bytes to zero.
    void
    reset() noexcept
    {
        clear();
    }
#elif ! BOOST_BEAST_DOXYGEN
    template<std::size_t I = 0>
    void
    reset() noexcept
    {
        static_assert(I != 0,
            BOOST_BEAST_DEPRECATION_STRING);
    }
#endif

    //--------------------------------------------------------------------------

    /// The ConstBufferSequence used to represent the readable bytes.
    using const_buffers_type = net::const_buffer;

#ifdef BOOST_BEAST_ALLOW_DEPRECATED
    using mutable_data_type = net::mutable_buffer;
#endif

    /// The MutableBufferSequence used to represent the writable bytes.
    using mutable_buffers_type = net::mutable_buffer;

    /// Returns the number of readable bytes.
    std::size_t
    size() const noexcept
    {
        return out_ - in_;
    }

    /// Return the maximum number of bytes, both readable and writable, that can ever be held.
    std::size_t
    max_size() const noexcept
    {
        return dist(begin_, end_);
    }

    /// Return the maximum number of bytes, both readable and writable, that can be held without requiring an allocation.
    std::size_t
    capacity() const noexcept
    {
        return max_size();
    }

    /// Returns a constant buffer sequence representing the readable bytes
    const_buffers_type
    data() const noexcept
    {
        return {in_, dist(in_, out_)};
    }

    /// Returns a constant buffer sequence representing the readable bytes
    const_buffers_type
    cdata() const noexcept
    {
        return data();
    }

    /// Returns a mutable buffer sequence representing the readable bytes
    mutable_buffers_type
    data() noexcept
    {
        return {in_, dist(in_, out_)};
    }

    /** Returns a mutable buffer sequence representing writable bytes.
    
        Returns a mutable buffer sequence representing the writable
        bytes containing exactly `n` bytes of storage.

        All buffers sequences previously obtained using
        @ref data or @ref prepare are invalidated.

        @param n The desired number of bytes in the returned buffer
        sequence.

        @throws std::length_error if `size() + n` exceeds `max_size()`.

        @esafe

        Strong guarantee.
    */
    BOOST_BEAST_DECL
    mutable_buffers_type
    prepare(std::size_t n);

    /** Append writable bytes to the readable bytes.

        Appends n bytes from the start of the writable bytes to the
        end of the readable bytes. The remainder of the writable bytes
        are discarded. If n is greater than the number of writable
        bytes, all writable bytes are appended to the readable bytes.

        All buffers sequences previously obtained using
        @ref data or @ref prepare are invalidated.

        @param n The number of bytes to append. If this number
        is greater than the number of writable bytes, all
        writable bytes are appended.

        @esafe

        No-throw guarantee.
    */
    void
    commit(std::size_t n) noexcept
    {
        out_ += (std::min<std::size_t>)(n, last_ - out_);
    }

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
    BOOST_BEAST_DECL
    void
    consume(std::size_t n) noexcept;

protected:
    /** Constructor

        The buffer will be in an undefined state. It is necessary
        for the derived class to call @ref reset with a pointer
        and size in order to initialize the object.
    */
    flat_static_buffer_base() = default;

    /** Reset the pointed-to buffer.

        This function resets the internal state to the buffer provided.
        All input and output sequences are invalidated. This function
        allows the derived class to construct its members before
        initializing the static buffer.

        @param p A pointer to valid storage of at least `n` bytes.

        @param n The number of valid bytes pointed to by `p`.

        @esafe

        No-throw guarantee.
    */
    BOOST_BEAST_DECL
    void
    reset(void* p, std::size_t n) noexcept;

private:
    static
    std::size_t
    dist(char const* first, char const* last) noexcept
    {
        return static_cast<std::size_t>(last - first);
    }
};

//------------------------------------------------------------------------------

/** A <em>DynamicBuffer</em> with a fixed size internal buffer.

    Buffer sequences returned by @ref data and @ref prepare
    will always be of length one.
    This implements a dynamic buffer using no memory allocations.

    @tparam N The number of bytes in the internal buffer.

    @note To reduce the number of template instantiations when passing
    objects of this type in a deduced context, the signature of the
    receiving function should use @ref flat_static_buffer_base instead.

    @see flat_static_buffer_base
*/
template<std::size_t N>
class flat_static_buffer : public flat_static_buffer_base
{
    char buf_[N];

public:
    /// Constructor
    flat_static_buffer(flat_static_buffer const&);

    /// Constructor
    flat_static_buffer()
        : flat_static_buffer_base(buf_, N)
    {
    }

    /// Assignment
    flat_static_buffer& operator=(flat_static_buffer const&);

    /// Returns the @ref flat_static_buffer_base portion of this object
    flat_static_buffer_base&
    base()
    {
        return *this;
    }

    /// Returns the @ref flat_static_buffer_base portion of this object
    flat_static_buffer_base const&
    base() const
    {
        return *this;
    }

    /// Return the maximum sum of the input and output sequence sizes.
    std::size_t constexpr
    max_size() const
    {
        return N;
    }

    /// Return the maximum sum of input and output sizes that can be held without an allocation.
    std::size_t constexpr
    capacity() const
    {
        return N;
    }
};

} // beast
} // boost

#include <boost/beast/core/impl/flat_static_buffer.hpp>
#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/core/impl/flat_static_buffer.ipp>
#endif

#endif
/* flat_static_buffer.hpp
8N7YI7a0bHr9OtRocX878D7aGCVU7MId+7sXxT0CZlnLir8qKiuKS8R9Ndyfl3RF+uwz+5bYhXjfDRmW74b4X38naJGFP0TuZd9TvjfqYWZhQAQz97z9ROK+z1MX+J4Q0RJ9QJJn/BEdU/NwdEiz6JDw6IUR0QnnRruTfNrO7Ryj1BzBGGWNzXvoen2PBLs9YCnPW5Qdy5R+U9R6WclPsStQdpJPak8f5BHsmEcMP0X5tfKHbWwr+zb2PB6sUo6rJa7xuFZnWIvBbOoMktnAXAbDdFRz0neIeZjRU+3VEzBGYZg09Y3odjEPxaglzLHe3Cp+BuHNM4r1xhtPsuqj41L/vX7QO7+MtPqMI/J8yo/7rXBdfkg7jgdwdcZ1jRXGWoPbRvIQmeeZTCgsZx201+Gl/wzVB/QV8yX1+aDV4RHK/ymqjZok5rMc958oEPdmzDNv+DwjUdVvib9QajnDTYS/8eJvhsSbmKXaAalnMDCfG64zsVqdybYZw+eq/JU0MM8Dx/XSd4jMSxp8yuGdZEN+n1l+yGbwu8e/HBZVzvXXpc6pLwf6b0UdZNSZtpb5VvWN6C0xm3THHKyYQ33i61Ev44zvM6fvqnR/gmYVn205jlL+/0Jzvf/I+rOz6r9HiFsJzcqvtMnxLKQosTvDSBI7Gdgz3DmIKxehY6WMI+zLWJ2NFKuVaw7tWmp2PVT7FjgmT/cra/0MqO0Urjx+OzseV1wW/LdT5Tqtcv7U8hLDcZxAvz1s39tHKPdWqq70adfw2Kq/uIdpY4IG68Fwvb3B/f1ln3aBz/5CmiG/OK5njgBjrHfg+mf3TPoVlju1y/TbxkjkO+wVYt5nHIc7TcBVL5eeucxEtrOXib/dRjTK/yzK+wgVXyt9PrdQTmtj2LHwc4n4OYi7uo1CXJ53bPbzhVXVc7U5yn+I32Fqv7KUZNmfHy1VX+nD30lBqDQ1TnzQGidGcJwYEmccdlxm5UFXiTNctZU9xdybZu89ox3Lu7e4h/m8L8Q08rtwnk0fk6/qAPKcZd6NZV7eXp11Jr8kXFEo87pkVeYV1ecYPnO0fE76aW07RxsHvprc8FlnlFXZtyNCpbFC0+c/cr3920Rvv8/Ou7dNnjfx+fUvX7eu+MzI04+9fr79uoMj19t3Wl9wAP65XkPm0OV9DNeb/Hskrjf49yR+899sUI+GOj/ZbNPWMp54FHA6mAT2574PBWAaOA9sD54HdgQvBDO4H0QmuA/sAR7gvhA/gL1Bg/s99AH7g3ngILAMzAMXgyeCF4O/A5eDw8C7wA7cHyLPoK4EdTCycYXi6sV0Q6W/xmIPMAHsCfay3MHBYG8Q8cATdQPAHxlPDM9C4Dx5TSvux3AVWAdey30ZVvHcs5vB17jvxDbujf86+DT4Bvh3nqf1Bs/b+pLnbH1j2ZOG+jYu3/IkHW1x7Wc68Ow1XcA/gUPBR1kOj4Gjwb9yH48nwFLwSXA++BTL52nwEfA58M/g38E6sI7l9ArL5zXwZ/AtsMDS3QIvAt8HbwM/Bu8AP2V5fG7FC34FvgzuBXEZ31rxggfAGDzPd2ACeBDMBA+B3cEfwV7gTyzXg7gK4n3zoQ2uL5gPpzEfJjIfzmI+FDIfSpgP05kPM5gPpcyHmcyH2cyHSubDfObDAubDIuZDDYi4jIv4/Jfz+X/P57+Kz7+Sz/8HPv8NfP7VfP4b+fw38flv5fPfxue/HeT5fPzOAdmjPOrn84VCblPAaHAyGAMuBJuCq8FYcC3YAtwAJoIPg3Gg9dytKPfLvPPY/G4g41hc5+EyuN9MB+43cwL3mSkC13M/kvvASvBPrA+Pgo+Bj4O7wVowyoRcgr3BJ6zw4JM=
*/