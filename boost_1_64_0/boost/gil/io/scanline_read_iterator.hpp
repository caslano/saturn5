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
TIRuLBczhACyr0LUgYra0JjTmma2BPkElH0N3zdiSYr81/yuQn5Je8zP/AL0AmhO7qUEWH6/biFeP4RNHJ2g7Cth6M329iMjINBxD5CAPKWXra3GU59XXsZSeblQv1NSVMe3fMBqOGe0I5u0lGlugqZKOoKyveCvYKkY3ekkst7wComZStYb91dIzBix7tuIue0tte0YB4DAQCwuksYWdLsF7SpR8kgzDj6s0BVWaHMrdFaV0NetUKeEQjwA517peARK+zCftjD2kRPgyBT+YtulNlnx633oUeojOWo7TfFewaeNi+Y3r0p+qVbobIGus6Dt71fhqoC0VcjDFZBmChlcAYlXSHoFJFohHSogZfcJpE0F5LBCGqarWN6CT21/2bUpMzMzuVXHENd9Kj1xPmLwBn/2q6MrlEkiRaSSQhF9SvloSk1SoUeih4t0UIlQeZz0Gz9DUnzGaR4Yz9+l9HTnb+MqAWmzVnutTh8x/41m/zsjJcwap2tuXw+ThkfIAwp5L9NWsb09uVudKL8H5lJjM4UH5BllnkpgjNmXazLa0EYhnHGay+WWnDc3Nx8nTIPv0uBsYXVrEmYPSXTuDm05KcPsFjOAhCFNEiL9yzqMBn41g8Pscn3uWdXdoYss3XiX6BLxe+BZdQ9J9A9Jsox4z1uZFzEqJ97XyUL7NjMfOMHH+UG/CU34wr0UBnXO0NlHhsb1rLqDieZFUjhULlPj6/R6vSFBaOtn0pFYG6Sx5YLxqcWzjPusFn3azJ5UsW+d69D771dISg+t0nvAuyIx+hfHpy5yPkOWURC5Fv+2av1Z6fbQvB6SmI8kzJ2AhS5hDa7zq6ZfQEiMuRw/TGjTBF3ERoRHGOEtwqtsYqLc1eWP+ikBuomTpKczI5169Gf2oCpBJklB9GZhc6qkqfX7WEXv5FuqQH/02hr+OrMV8Dj/10v1ZkKdcpfLA5SC/k4WdkGGtKzHQhM8n+l2Wir3Gr+VuSwiWyYVb2kCq951SAIOJBDqqnS7zKZRVjt+H/aqzG0r6O00O/kk+QZABaGCXim1LZ5rBJViOcSrpJzrtTfAEqxpyqFhegk4CMNLwLF0/BDGXv9oiyvAQckL9TtHAxU6vtswbcUnMXtimtSjaMnYVPQZZ4xy449U46Sxl22oVWpBj+iPHzdfmUrB0a59GbC1qcbfi/r24HLgZWkFPYFH4GNTKyxAuANLLS7pb+FaBE7C2Y34e6gk9TrGZqy0GkT7jRmiabEvuQA/WQlq5WA2ZRm0Aba3rBpqsgBY/JKbz8qm2OGNrPDswULnGKzLqd/v5RC863paYwr8UimW9VABLe2hxG4/WJVkprGB6nEM9cEo1ZHajVanr+xve/ppe9s/RKm7XUZYUJXYc+tr670hLNfZQbbW85sH+KHlTjH/5IeSIkmJfHqQqn1WiXKlVWriY+m+k1E1IFTHqQXZTtFp1mhgGSLC7F1lKncQZUpkCW+sUke78ckeNQ2QRekNZTusNv/LkPmfVTMcsv4GXFJDpZ+ME8Z5ykpX7rG8xxsT0oBmSUBPp6gM8LKQvIwz14oC2xWcKlJknhoolQ9lc51jkYjFZjHm4jfZz48UfszTD5abPb9+JPLDPr+ED+3TRaqailTFOT912TrhA9UJt/4Ctdk7VXaCdLyoUldEqVvZuoQl7WZJ3etUmcqQSZ3UniyrMSn6BkuuxjPRIGkoneqBMyPAQ10smRxRETulSuxhFbE7+xChjhX7yADt0sUXWIg7fu8cQGHfvl3v/cAyszk61eqzUsXyu5P+3Kw/7fDDdFrhl/kYAyLCvF7lmBINPmdUUbfV+K2S3GSwpW8P6ViwO/Q/pHn27bbAXgM=
*/