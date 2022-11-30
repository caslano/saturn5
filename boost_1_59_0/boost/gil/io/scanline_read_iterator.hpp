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
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
*/