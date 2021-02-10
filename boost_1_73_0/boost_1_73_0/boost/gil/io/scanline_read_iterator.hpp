//
// Copyright 2007-2008 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_SCANLINE_READ_ITERATOR_HPP
#define BOOST_GIL_IO_SCANLINE_READ_ITERATOR_HPP

#include <boost/gil/io/error.hpp>
#include <boost/gil/io/typedefs.hpp>

#include <boost/iterator/iterator_facade.hpp>

#include <iterator>
#include <memory>
#include <vector>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

/// Input iterator to read images.
template <typename Reader>
class scanline_read_iterator
    : public boost::iterator_facade<scanline_read_iterator<Reader>, byte_t*, std::input_iterator_tag>
{
private:
    using base_t = boost::iterator_facade
        <
            scanline_read_iterator<Reader>,
            byte_t*,
            std::input_iterator_tag
        >;
public:
    scanline_read_iterator(Reader& reader, int pos = 0)
        : reader_(reader), pos_(pos)
    {
        buffer_       = std::make_shared<buffer_t>(buffer_t(reader_._scanline_length));
        buffer_start_ = &buffer_->front();
    }

private:
    friend class boost::iterator_core_access;

    void increment()
    {
        if (skip_scanline_)
        {
            reader_.skip(buffer_start_, pos_);
        }

        ++pos_;

        skip_scanline_ = true;
        read_scanline_ = true;
    }

    bool equal(scanline_read_iterator const& rhs) const
    {
        return pos_ == rhs.pos_;
    }

    typename base_t::reference dereference() const
    {
        if (read_scanline_)
        {
            reader_.read(buffer_start_, pos_);
        }
        skip_scanline_ = false;
        read_scanline_ = false;

        return buffer_start_;
    }

private:
    Reader& reader_;

    mutable int pos_            = 0;
    mutable bool read_scanline_ = true;
    mutable bool skip_scanline_ = true;

    using buffer_t     = std::vector<byte_t>;
    using buffer_ptr_t = std::shared_ptr<buffer_t>;
    buffer_ptr_t buffer_;
    mutable byte_t* buffer_start_ = nullptr;
};

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

} // namespace gil
} // namespace boost

#endif

/* scanline_read_iterator.hpp
Z/0MRKCQMRhX1Leh0yhv6BShsjzKoCu6KXyMdhCQuLmWGZeTn9DIMkaRAhg8pL6uuPHo4AUP1GZONrLgG8oEFfKg5ujQZ69HldV1Dn2pJPer/PeSQ2KtiW6mGQ+pTxHyFXFyESsaOR15ivZKYK3BirFWYWqkbJLdpdepzCT08D7zDpkLowQiskgl6rdgd3EGLrBQ0DhXscas9PoGHctwdIPI/9YFVkaEXpBjkWOE9fbtQ7k+nFFohp3lBCIeJRq77+1z2kkumbCM2ULGaoqtiN8aqiEwa+osDmB+XGHW+V3PT/PVmNzzBOdj5m/v6UX+JMMentGRvsDmNgBf54qsF8jYc9SgDWsBhh9nNHb2Ai6fqEy5ZXC7/IR9kIPAnvZwjLMTMKntQU+QrLEqRLaSyXShI/FM9QZ6M3h1nkiSs4LxOcqlZXBRLxH4ZjAxwiwb1cxY3v0i1LJH49ZR+Ydrtlo59YR9CJdOTbUsx0YmqHGFpZ9iEaeS0RqCa7EQN1cisKw2oExfXISvJSzzR3sNjUEYLOA095rNW/car3pz21h5Zn3jGJ2O93n9RvuJ0cS2SbOBC4VqOegfDffDtjHROrsvF5uDhwnC3PGcc5GpBBXvEX3doKS9Spj/gbiqalTDbirjj7SQ4cuXuJad
*/