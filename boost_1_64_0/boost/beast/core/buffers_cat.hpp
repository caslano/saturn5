//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_BUFFERS_CAT_HPP
#define BOOST_BEAST_BUFFERS_CAT_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/buffer_traits.hpp>
#include <boost/beast/core/detail/tuple.hpp>
#include <boost/beast/core/detail/type_traits.hpp>

namespace boost {
namespace beast {

/** A buffer sequence representing a concatenation of buffer sequences.
    @see buffers_cat
*/
template<class... Buffers>
class buffers_cat_view
{
    detail::tuple<Buffers...> bn_;

public:
    /** The type of buffer returned when dereferencing an iterator.
        If every buffer sequence in the view is a <em>MutableBufferSequence</em>,
        then `value_type` will be `net::mutable_buffer`.
        Otherwise, `value_type` will be `net::const_buffer`.
    */
#if BOOST_BEAST_DOXYGEN
    using value_type = __see_below__;
#else
    using value_type = buffers_type<Buffers...>;
#endif

    /// The type of iterator used by the concatenated sequence
    class const_iterator;

    /// Copy Constructor
    buffers_cat_view(buffers_cat_view const&) = default;

    /// Copy Assignment
    buffers_cat_view& operator=(buffers_cat_view const&) = default;

    /** Constructor
        @param buffers The list of buffer sequences to concatenate.
        Copies of the arguments will be maintained for the lifetime
        of the concatenated sequence; however, the ownership of the
        memory buffers themselves is not transferred.
    */
    explicit
    buffers_cat_view(Buffers const&... buffers);

    /// Returns an iterator to the first buffer in the sequence
    const_iterator
    begin() const;

    /// Returns an iterator to one past the last buffer in the sequence
    const_iterator
    end() const;
};

/** Concatenate 1 or more buffer sequences.

    This function returns a constant or mutable buffer sequence which,
    when iterated, efficiently concatenates the input buffer sequences.
    Copies of the arguments passed will be made; however, the returned
    object does not take ownership of the underlying memory. The
    application is still responsible for managing the lifetime of the
    referenced memory.
    @param buffers The list of buffer sequences to concatenate.
    @return A new buffer sequence that represents the concatenation of
    the input buffer sequences. This buffer sequence will be a
    <em>MutableBufferSequence</em> if each of the passed buffer sequences is
    also a <em>MutableBufferSequence</em>; otherwise the returned buffer
    sequence will be a <em>ConstBufferSequence</em>.
    @see buffers_cat_view
*/
#if BOOST_BEAST_DOXYGEN
template<class... BufferSequence>
buffers_cat_view<BufferSequence...>
buffers_cat(BufferSequence const&... buffers)
#else
template<class B1, class... Bn>
buffers_cat_view<B1, Bn...>
buffers_cat(B1 const& b1, Bn const&... bn)
#endif
{
    static_assert(
        is_const_buffer_sequence<B1, Bn...>::value,
        "BufferSequence type requirements not met");
    return buffers_cat_view<B1, Bn...>{b1, bn...};
}

} // beast
} // boost

#include <boost/beast/core/impl/buffers_cat.hpp>

#endif

/* buffers_cat.hpp
fyfLvF74zwiaYmQbt9pm4R7+ylpke8HWJjKWK/PAZgiM556PEO1dYKFpP0LibwtajnxoayRqbip2haSelrPsbDvs5MhEeS7GKq073sraxqZmqV+zS6wWvlYJT4Sw4m518izhGL9Ywq8JWmEM0+7tku/+HKvmCU9bUAk08XfgK8BxIwRC1qrWYh6Q8Ai5J/qeqg81fmlrKf+gDCfxnSdbeJ8MciD+QmME0o+ReCkcL51sx8uFr4dtMGTgHaM/2xclM/0h+6Gou3zjqLEA7Wf1b5S1vqq6Uq0tviCyAPkRt6/8mGNowUCMH4OxDhltjm+td9vt9qHm/hm7xzppk8eZHRNZfqdeJpQEZUJOGyXeeq1erT4zmX0m1nSreIl4dofKOJrK/NzK/IThm8mlRchNSJg90p5h/oj0yRPHsjekrNPpxqgm/TXBNy+s39eFP83jvnFDtPt+JC/h9vBA9+UcYKPcJ1fNAV4Sd0TA+zZLeKrcdyaeI0hS1lEnQ/AmgdaDjsP9Kegj0Meg25yYL6BTVIAQLnuLdoDwW/hkrtXFfUbmmirk12NNdSfCGsK4jkabprvV3Ewb/+Hfrj2jTL79io9jsDZvw3gAfxkPPJ5dccMCrAdVue2vd7geVBVwPUiud6o814PMa3D1SawHVftZD6rufD0oIgP1CCMYWR7rQUM91oPeA08deObE+OfJNdMZihlaZuD1oOiTWQ+q7mA9qLqD9aBqr/Wg6g7Wg6q91oOqu7AeVO27HoR4aj1oOOqgKpPfnqLd60HZ8CsHnUn/gOtBbI8dmV9iPajqX7Me9Dn7w0QQouCp4OoPeStVf8A8TjqEv/5AviS4rW9GmPppY9QSCQ9T3/zKxd3X77M3Drhawh2WDqr61vNBF84uYtlVXejlXHYGbQSy36cCZ2FMa/MsJzLvWc4kysydwveZMQh/zwFdAGIdMI1YJUt3reI5Hz5zRDWPZZy+dGNHgrh76vXYoH93u0XSjPC+h95/1NzpV5LW64Yd5R8HcvOsVv0mROIHq31r4eK+B6NOlPCnhPFdCFVbbsqTpBll89duMSq8D91WeeLhZlrW/J9zoVy5H+a4ao5WaZZX7lej3e8MyEGk9u3vM/AeAxm4aRnQBjTdf9X2veZ1IiNFmow44S71fY6odyLkHf4Nap9aiMRDXr3OQog405ArmTfrC/oQ+Y2uEfkydavxIBs1wgwLMI8gb7Lf57eshUp4Ygdrpin6minLiHt47bO4LpvPKsseOOihLPRlV15lIDLf4MSyHPN7n8sue4X2/ZH8A9S8p1+tPPt0/hXq+7TiT6Pbze/xLsGyLhDeV/HUi8BzaShWqWYp2XpYwoK0feArDCfvUSlhD2KWmYI4Y2nrzorThK+Oq7R4mEewLGUS/pgxHaPgFu55mu0Zr1MdeGvugbKbMlKh7GorP9SHV1scHWHI9SRt7e4DPQDe8lqvtqipaKrxbQv1TGsU/ntRajUuMY1YiZPqx7Zf3Gqe4cA9LTcK/0XIn8OINuyohUh9LJB488H3lPDFI2W4UUcHxT0bdXSGer/W63aDhC8xhiA0B8S6VfGC0Yusc+oeTTSp87Heu66967V5JG2fMlJv0HfBWyRlbq2EMkf9+oYRZVXrKurqONe7x/PMD/LGdfoN0jqnA/Flbqrn43PmI4IRwpmPBo98jOwoH+SN+FL52DXKxTiZcjaa+Wj1yMco//mgjN0gvOnMlxXXqdrugy6eMcjntMqnPo6m5/DjD8emGbRXcdCVz9r62uYy6RRcP95tlivH0rEY6AiP13UsOj33aHaMl+3+Ezm+tvu/h3xmr5H719WUTZk+fcZ0sZchdcU+eYfUVV2NPj4=
*/