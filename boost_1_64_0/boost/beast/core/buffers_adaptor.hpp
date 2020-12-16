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
+4Fc/ThpifRr4W/AwByB8STJWneR9ObYvgEty7fBM91mU2s42yWt+QjBmIBlB8s2yeviH26lh6tJyddkCfuF4aR8RYs713Ym/DJsrvfBs4aZcVasX8n1nRSgEzISAhwF+agEAUVPRto5qON1kJQg9zrIbClrdHpB4ehxqj0RjvrXzyqXeyIf8JN8yLvHcMkr3pV7u9zTvNy1Xu4LvNzXerkf8XK/oLn1d/6aeGV/Ry4HaA7y1r5EydSq6uZsc4Gywgi8Bkf+qE5t7ogNFn0tyGs8PO4nP0+aa4nu/OCA91XNNR3k5cBpyktIIs/JpK5RH+BuyMVBLS/1I11jRKR7XGU+LL7+EvZAb1P215myLPJt3vcdCQ81nOJnE7/BS02/5429+Mv1R309sapBs9XWS3j7GD3wj7baGP8MiXM34xiarKea7zCo43IMsEPkGbjUERbh6NnTkdnLnF+EjHTxHHJiTATPnBj/PLlmOuApTXDNP8IiwIVBWfjsc2XuEeN37hESqc071Nxi/FKfeYeak5whYc/4nWcsk7Br6MYqrrgdfucY35SwIK5xWLxXyxxjrdFXn2eoZ2ut8DQbixGLzy3Gc8o6bTIGpuIEvg/GtN6EqYT4p8CvCDRU81fzC42cbI9t4B1l8oZmO/BQU+uEuxMtG20LsPZuPZtk7V3J2Z9EjgZ2tG6r9Owa3M8cpXcH2YR7nRqbIDdwQ268+sMh9gc45IoGLUbcvGWqP6iHpp+5L8pg8cb4tKWZZr6E9ejwOdwbOFP4Iju1gcX+HXDuVdTXxfwox5uHQNvi0DdUecwbj5QHcaS7PCyLxbcK94Ebv/4s7hS8a4cG7LNvCk+S3mcZLxFu1zhhYDyz+mwe0F9fzuZ3gsNok+eSKDsRVY7QaF/ZoVvmOH7liHnbK/nIkHpt6USOWt31yvmNkiPknev7HcjSwWT8YZ1Hge4DPY34eed61D0GZY+6Z11bfCvxFtVD1f+Pz+28/vcLjxOxQlluM96p138xZGh6slX/lV+q/tvO/dfVf0F/Q669rP89lP2U5R713xRA9sm3UtX93uWd1/0O4UlE3UewzGa8U6/7Q6j3A/1OT903LP/X1X3+QEOukZxXDOd3T6NM1T3kXiYWum42x3vy4S5OvqvFinuA6DUv1r41ebWDKutCk18bf+rEPS7QnEG+VxZBXvbBkSnPqPMc4b0c4Q5HiMOxoIeERwzAHBDhc2J8wychPAPhe1I4V4gER1iE4sHykqzG2QdjtpDusRQXEuL5rUSttW2QPO/R5wtqne4sCfvQGIwyej9nEsy2kvBGum3GHWWB1+Iek7CRcCdw3mDxl2GVbRrswATp8wa1HvaU8NTRbcXpI3WVj7rYnWKtw7W2sqaCkxzpshZXjLBdKdZaHDnC7C4eVNYsbS3O75yC7fVWijWnmOoI7Xlyc4oxLpmiXdyO+0O5W3e/0zlECBcDzwvGyzHxWfObf7mH7De3NCNtvuPZ+L7GvJF3tHp3fUzcE4OzbCG0j8w45quCmjdY8TKNVK5J3y/uWcG5tiAjOAg7GkCtQdgfHhwkadeBp7FC1qGCGlEKrS+q99RHJI3JwQfAw7UQ3mck12ZtKg1z7bbJOG5z57F+XVl9xdpqjpG1VlzUSj0s859h+iF+ocS/NmgxZqrVmDs8ifHzFcj2b40YvNdGGhts1xlRQZs1+a1Xsj6+UtpR3OuQ/tkVfOeQcO+8vW8TPtzzQIW1fjRV2vNhydfU4Fh1j/X4LLdC3mmd7JMtEmdh0ChjAtr+Gvq77xEGTemlEAe9Tyaxz65aIX3S1h/lykQpP8KokWqGafF7o0eXGD/GuOkwKmyXG0FB1VLmVPY=
*/