//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_BUFFERS_REF_HPP
#define BOOST_BEAST_DETAIL_BUFFERS_REF_HPP

#include <boost/beast/core/buffer_traits.hpp>
#include <iterator>
#include <memory>

namespace boost {
namespace beast {
namespace detail {

// A very lightweight reference to a buffer sequence
template<class BufferSequence>
class buffers_ref
{
    BufferSequence const* buffers_;

public:
    using const_iterator =
        buffers_iterator_type<BufferSequence>;

    using value_type = typename
        std::iterator_traits<const_iterator>::value_type;

    buffers_ref(buffers_ref const&) = default;
    buffers_ref& operator=(buffers_ref const&) = default;

    explicit
    buffers_ref(BufferSequence const& buffers)
        : buffers_(std::addressof(buffers))
    {
    }

    const_iterator
    begin() const
    {
        return net::buffer_sequence_begin(*buffers_);
    }

    const_iterator
    end() const
    {
        return net::buffer_sequence_end(*buffers_);
    }
};

// Return a reference to a buffer sequence
template<class BufferSequence>
buffers_ref<BufferSequence>
make_buffers_ref(BufferSequence const& buffers)
{
    static_assert(
        is_const_buffer_sequence<BufferSequence>::value,
        "BufferSequence type requirements not met");
    return buffers_ref<BufferSequence>(buffers);
}

} // detail
} // beast
} // boost

#endif

/* buffers_ref.hpp
L4+1DDS16+0rbhrn2srHn7z4+i++X3KNjql1i0++h8K0SatOqZHhl6yv/wJQSwMECgAAAAgALWdKUgVtTg97BwAA6BEAACUACQBjdXJsLW1hc3Rlci9kb2NzL2V4YW1wbGVzL2Z0cHVwbG9hZC5jVVQFAAG2SCRgrVdtb9vIEf6uXzGnIrVk0FLifunFTlBVllLhFMmVZARpUxArcmnxQnGJ3aVl9XL/vc/skhLlJIgLnIKE5L7M2zPzzKR//sf9WnROP/yF7m+IH57uxq1Wv8rIfvt0GH4h/we3PuH5IyV9Ol75Enbpx1e+UMddCSst1/wehj9S9Ilt43/6fPNTyK9YwTW+OVTFXqf3G0udYZde/fzzX+mCLl9evgzoRuSpzGhpZb6W+j6g69it/G0jHh97Rr4NSFoSWa8StdqkhoxK7E5oSXjP0kjmRsYkDMXSRDpd4yPNyW4kJWkmaTi//TiZvQtot0mjDQvZq5LMRpVZTBvxIEnLSKYPXkYhtCWV4DqEx6mxEFjaVOU96JZkpd4alsHqRWYUiQeRZmINRcLSxtrCvO73o1JnsL4fq8j0o9r93sZuD558hBFbsSdVWLKKSiMD4pMBbVWcJvxEQLBYlOssNZvgaA1U5XFfaTIyy1gW7qXSeLMlLavw
*/