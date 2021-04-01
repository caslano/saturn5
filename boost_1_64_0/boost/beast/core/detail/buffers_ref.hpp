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
ctqrSk8xZacc1F0LgNkmjpOjAwye7SUduxn9kppGWTdZGEYcNePXYjV5mG1GrYyuLkGmdI5COE215HpfvapPeRCNMm//LAumIdV68IbVnHnDnfCDcMco6THumbDro2mBXrVT/oyn0VcsmySJun8qdKJgP4UTAAKMh/0xIXwGD2GRmexC5Cth8Qj6v996madFj/fTX3CBLAcYrRfgAUVKOoMA4K0ej/OLnWEA1/C75sogbQpnBm4JDE05arpprdY6yPpfnHBC2PpmfG98zBUJzLryaZ25XVNiU48JluGfPMGNHnfvtCeGpr1JB6nZAtx//+fZEhSAfE+LNR2pYwjrfadjpzKNqlNGGMpMJ/PcdTAoHV7reQRjjt8oJj6AWbf2zUA1OvhzpKaEk91oSNh0tAtiVA1AndyfeBLDUya+JWavR/g17udSCUhERsmLrSR4T769Q21o17e9OssKgs4/Fgm8VrAF5nUN7mshG03u4xr5QfZcKC3zNp03h2f01xcjQF0rdHMXiYymyjgfWdzNPPapIAieW0BbC9JruiXQgPVN9RJgaObJjlT49Q==
*/