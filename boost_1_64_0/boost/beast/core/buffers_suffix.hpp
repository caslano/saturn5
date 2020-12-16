//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_BUFFERS_SUFFIX_HPP
#define BOOST_BEAST_BUFFERS_SUFFIX_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/buffer_traits.hpp>
#include <boost/optional.hpp>
#include <cstdint>
#include <iterator>
#include <utility>

namespace boost {
namespace beast {

/** Adaptor to progressively trim the front of a <em>BufferSequence</em>.

    This adaptor wraps a buffer sequence to create a new sequence
    which may be incrementally consumed. Bytes consumed are removed
    from the front of the buffer. The underlying memory is not changed,
    instead the adaptor efficiently iterates through a subset of
    the buffers wrapped.

    The wrapped buffer is not modified, a copy is made instead.
    Ownership of the underlying memory is not transferred, the application
    is still responsible for managing its lifetime.

    @tparam BufferSequence The buffer sequence to wrap.

    @par Example

    This function writes the entire contents of a buffer sequence
    to the specified stream.

    @code
    template<class SyncWriteStream, class ConstBufferSequence>
    void send(SyncWriteStream& stream, ConstBufferSequence const& buffers)
    {
        buffers_suffix<ConstBufferSequence> bs{buffers};
        while(buffer_bytes(bs) > 0)
            bs.consume(stream.write_some(bs));
    }
    @endcode
*/
template<class BufferSequence>
class buffers_suffix
{
    using iter_type =
        buffers_iterator_type<BufferSequence>;

    BufferSequence bs_;
    iter_type begin_{};
    std::size_t skip_ = 0;

    template<class Deduced>
    buffers_suffix(Deduced&& other, std::size_t dist)
        : bs_(std::forward<Deduced>(other).bs_)
        , begin_(std::next(
            net::buffer_sequence_begin(bs_),
                dist))
        , skip_(other.skip_)
    {
    }

public:
    /** The type for each element in the list of buffers.

        If <em>BufferSequence</em> meets the requirements of
        <em>MutableBufferSequence</em>, then this type will be
        `net::mutable_buffer`, otherwise this type will be
        `net::const_buffer`.
    */
#if BOOST_BEAST_DOXYGEN
    using value_type = __see_below__;
#else
    using value_type = buffers_type<BufferSequence>;
#endif

#if BOOST_BEAST_DOXYGEN
    /// A bidirectional iterator type that may be used to read elements.
    using const_iterator = __implementation_defined__;

#else
    class const_iterator;

#endif

    /// Constructor
    buffers_suffix();

    /// Copy Constructor
    buffers_suffix(buffers_suffix const&);

    /** Constructor

        A copy of the buffer sequence is made. Ownership of the
        underlying memory is not transferred or copied.
    */
    explicit
    buffers_suffix(BufferSequence const& buffers);

    /** Constructor

        This constructs the buffer sequence in-place from
        a list of arguments.

        @param args Arguments forwarded to the buffers constructor.
    */
    template<class... Args>
    explicit
    buffers_suffix(boost::in_place_init_t, Args&&... args);

    /// Copy Assignment
    buffers_suffix& operator=(buffers_suffix const&);

    /// Get a bidirectional iterator to the first element.
    const_iterator
    begin() const;

    /// Get a bidirectional iterator to one past the last element.
    const_iterator
    end() const;

    /** Remove bytes from the beginning of the sequence.

        @param amount The number of bytes to remove. If this is
        larger than the number of bytes remaining, all the
        bytes remaining are removed.
    */
    void
    consume(std::size_t amount);
};

} // beast
} // boost

#include <boost/beast/core/impl/buffers_suffix.hpp>

#endif

/* buffers_suffix.hpp
fWoMflcBFvI+kcBl1ns93yNGAAea5eB8MAc4HDgGmG2WhfOwccA8uqfTfTbdVvl3qvsFXm/IA0XXB67vTNb3MNb3cLPcdI+jW61vqHT8r1vkBLvODmyfEW68CDoCOgGKnhne6XmC6eAZNzP8v/pcwSLkP9DZglUzw7t8vmDLzPCTOmNwx8zw/8tzBvfPDO/SWYOHwXcCFDcr3MgBFYOaQdeB2kGHQMdAjnzUI2g6qBy0CbQDtA90EHQUFHF2uJEOmggqBbWAdoD2gw6DjoMSZkOWQctAm0A7Qa+A3gNFzME9QHmgGlArqPvqvrqv7qv76r5O5/Wvsv8veiNNp8f+f0EW5rpin18SLTN3//WnPf+jq9z+zRsbqsvEJI4rvBDx8lQ8OTSwCYonFZVr3OcB5Eu4uctXoos9/5B0Q+lJRdBmu7mOkUDsjQnygWk9DepJFU45Z4a5B1vTYzHvp/aWkDdD2bZ4X9x/FZ2C50Fuu0KSBe6TtOINMmKpx/QbcTcY/fBX/IC7ppt+kzDnHqzdXyybUdcY64MS7wsjCaU7CKJOP9NPk3iNqCvqQyg7AAsl7a/Bgmc8/XzvB35cFXW1FU1qj1Oe8MRq6a6rbzDcuhmpEn4A7/3Rsmc9A377MGUMRb07Itc4IlINH1v/seQ7DL4wky+09R6L56EYT57heOcIl32CrXvJgxDdflNtVQvQque1kp9opXv2dXFHeaRZhDQjXGl+ZqWJxSPhsWzt9UB4mceZAwtEBj+WPYA+Mqjko0LuF9mpnkCshz6fmR73dCl9LZEfL9uMIgtiL+8KuQ/WkbI892MeCcUfrif1MuscdKIv3l1neMo4N2X6k1fUk8Ufo2yWTBH3VcYmUxqUzo3aQazkukb4Vhh5kAazvh2ozAOgSNl/eZbP/ksned4H2U2eHlmiJK/2YHrxRYeCR2QmA8YK3HyXsP2se+aEMr3w1qv0tHSeUvBESb7KVTolMZ73awVPT0mnSOVL36tq2gIrUHKhxjQlD/lSH/Fdlge97fV2zQh3742LAo0CvTkMf2Z6tmvVujJR3AjUruBX+vs/Q3zYSNLtrDI8XcKDw2RvXeMqhhdZ4dSFKsoSGVC62kmmHjbqaz/i9ZI6izFNx0Q6DHe93aXprWBNr1O7y959oRRu5Bt+km9ldxl5hR/zSr3gIm2P/CTLnm0PQ64wPgM+ZT0W+a3HsqZ1jc3Y7RuwPhkvSdkzWS3uW+mGNZdZpntYoPpGfIbzeXKhuA/61j/H/xYJP8z2YHyev1Dp1R4e9lbYj1MkP5HqXJhocUPK4Cf64eGoc3NvnrRffxzV4m67y9jHMsn3HvjKU1H3Jfbz7XVhoY7QUJi8DXGEh4b1CLZDsz40xEdOsiknLYh7JMKSkxJsusQRMthq6y0nJlEHyxqPO7X5Q5nwkZ0aP7LTEEB2Kik75lh7QuoYZ8EkGuJONuuMael62Jvshlw/AiUQ3wLPTvDrsgWDpYHmF+QdoOYXz4j7ISMG97kTFGB+wXjJytbN0+LeayTi7/0gr3mB8OXbgPliE0fuONGI97atq+ymPCnpPYp82I07Oc/5wTDXfECz1+A9j1DPhSi5TznW2qOl/bf1gPxgATVGxvJFjtAkhyPdEaraeneil400PpMDjbexrL+3JZ/jIXf2TvWlOcb4PINLfWVHyobywk/K6zE2RzsMuco5NiNrote3M9+z3U0FPwRJPzM/jrwFipXnzzBHeIKPbp+qi51pJnXtnGrLFnNLL9ojNue4xJtRbylne+RJDGLWwroN5lDyXK8SHSBTIVfmN5ZcIh5tSNA21Rhxf8c2E3ddbguSuNVZPJdGonKMU3HTJG4J3NPE3W4=
*/