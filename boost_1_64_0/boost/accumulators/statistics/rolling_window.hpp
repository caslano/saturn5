///////////////////////////////////////////////////////////////////////////////
// rolling_window.hpp
//
// Copyright 2008 Eric Niebler. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_ROLLING_WINDOW_HPP_EAN_26_12_2008
#define BOOST_ACCUMULATORS_STATISTICS_ROLLING_WINDOW_HPP_EAN_26_12_2008

#include <cstddef>
#include <boost/version.hpp>
#include <boost/assert.hpp>
#include <boost/circular_buffer.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/accumulators/accumulators_fwd.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/parameters/accumulator.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/statistics_fwd.hpp>
#include <boost/serialization/split_free.hpp>

namespace boost { namespace serialization {

// implement serialization for boost::circular_buffer
template <class Archive, class T>
void save(Archive& ar, const circular_buffer<T>& b, const unsigned int /* version */)
{
    typename circular_buffer<T>::size_type size = b.size();
    ar << b.capacity();
    ar << size;
    const typename circular_buffer<T>::const_array_range one = b.array_one();
    const typename circular_buffer<T>::const_array_range two = b.array_two();
    ar.save_binary(one.first, one.second*sizeof(T));
    ar.save_binary(two.first, two.second*sizeof(T));
}

template <class Archive, class T>
void load(Archive& ar, circular_buffer<T>& b, const unsigned int /* version */)
{
    typename circular_buffer<T>::capacity_type capacity;
    typename circular_buffer<T>::size_type size;
    ar >> capacity;
    b.set_capacity(capacity);
    ar >> size;
    b.clear();
    const typename circular_buffer<T>::pointer buff = new T[size*sizeof(T)];
    ar.load_binary(buff, size*sizeof(T));
    b.insert(b.begin(), buff, buff+size);
    delete[] buff;
}

template<class Archive, class T>
inline void serialize(Archive & ar, circular_buffer<T>& b, const unsigned int version)
{
    split_free(ar, b, version);
}

} } // end namespace boost::serialization

namespace boost { namespace accumulators
{

///////////////////////////////////////////////////////////////////////////////
// tag::rolling_window::size named parameter
BOOST_PARAMETER_NESTED_KEYWORD(tag, rolling_window_size, window_size)

BOOST_ACCUMULATORS_IGNORE_GLOBAL(rolling_window_size)

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // rolling_window_plus1_impl
    //    stores the latest N+1 samples, where N is specified at construction time
    //    with the rolling_window_size named parameter
    template<typename Sample>
    struct rolling_window_plus1_impl
      : accumulator_base
    {
        typedef typename circular_buffer<Sample>::const_iterator const_iterator;
        typedef iterator_range<const_iterator> result_type;

        template<typename Args>
        rolling_window_plus1_impl(Args const & args)
          : buffer_(args[rolling_window_size] + 1)
        {}

        #if BOOST_VERSION < 103600
        // Before Boost 1.36, copying a circular buffer didn't copy
        // it's capacity, and we need that behavior.
        rolling_window_plus1_impl(rolling_window_plus1_impl const &that)
          : buffer_(that.buffer_)
        {
            this->buffer_.set_capacity(that.buffer_.capacity());
        }

        rolling_window_plus1_impl &operator =(rolling_window_plus1_impl const &that)
        {
            this->buffer_ = that.buffer_;
            this->buffer_.set_capacity(that.buffer_.capacity());
        }
        #endif

        template<typename Args>
        void operator ()(Args const &args)
        {
            this->buffer_.push_back(args[sample]);
        }

        bool full() const
        {
            return this->buffer_.full();
        }

        // The result of a shifted rolling window is the range including
        // everything except the most recently added element.
        result_type result(dont_care) const
        {
            return result_type(this->buffer_.begin(), this->buffer_.end());
        }

        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & buffer_;
        }

    private:
        circular_buffer<Sample> buffer_;
    };

    template<typename Args>
    bool is_rolling_window_plus1_full(Args const &args)
    {
        return find_accumulator<tag::rolling_window_plus1>(args[accumulator]).full();
    }

    ///////////////////////////////////////////////////////////////////////////////
    // rolling_window_impl
    //    stores the latest N samples, where N is specified at construction type
    //    with the rolling_window_size named parameter
    template<typename Sample>
    struct rolling_window_impl
      : accumulator_base
    {
        typedef typename circular_buffer<Sample>::const_iterator const_iterator;
        typedef iterator_range<const_iterator> result_type;

        rolling_window_impl(dont_care)
        {}

        template<typename Args>
        result_type result(Args const &args) const
        {
            return rolling_window_plus1(args).advance_begin(is_rolling_window_plus1_full(args));
        }
        
        // serialization is done by accumulators it depends on
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version) {}
    };

} // namespace impl

///////////////////////////////////////////////////////////////////////////////
// tag::rolling_window_plus1
// tag::rolling_window
//
namespace tag
{
    struct rolling_window_plus1
      : depends_on<>
      , tag::rolling_window_size
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::rolling_window_plus1_impl< mpl::_1 > impl;

        #ifdef BOOST_ACCUMULATORS_DOXYGEN_INVOKED
        /// tag::rolling_window::size named parameter
        static boost::parameter::keyword<tag::rolling_window_size> const window_size;
        #endif
    };

    struct rolling_window
      : depends_on< rolling_window_plus1 >
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::rolling_window_impl< mpl::_1 > impl;

        #ifdef BOOST_ACCUMULATORS_DOXYGEN_INVOKED
        /// tag::rolling_window::size named parameter
        static boost::parameter::keyword<tag::rolling_window_size> const window_size;
        #endif
    };

} // namespace tag

///////////////////////////////////////////////////////////////////////////////
// extract::rolling_window_plus1
// extract::rolling_window
//
namespace extract
{
    extractor<tag::rolling_window_plus1> const rolling_window_plus1 = {};
    extractor<tag::rolling_window> const rolling_window = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(rolling_window_plus1)
    BOOST_ACCUMULATORS_IGNORE_GLOBAL(rolling_window)
}

using extract::rolling_window_plus1;
using extract::rolling_window;

}} // namespace boost::accumulators

#endif

/* rolling_window.hpp
nWijrZ4ojcnjo6sBN8lfvxL2mq4zpEkGpJRx6WLevevENmbp3ysuHbdTSkfqDDXN0nWQgjWaEn8IkcQSvogoKmnh+68yryX7uZj6xm694zberc+YBAJa19Tcrd+MMNmkgrkFF9EDDEnQTmJ/YZGwnTu/BSv/CgJe2e/RLH3uTzJLO6ubf+ZZegnqIHr0k+ndyKIO80PgIi0ura4NCr3/rWfAf/PnDP/Siag5yg//YoSt8C8y4P9Y4P9gP+BvXg7+vX804F98jOGfMbEi/B8hi7r0vOA37X85TNmQ5q/t9gtDfJtXhV6m/OO0AKllRt3/aPDCWgzlImFrVigbE5TzG4l56amEqfMQ3hjw7rNXhPeOb7R6BMObZsD76aly8M5/2oB32FGGd0kAvDc9TSKKGIF3ueP84LWu153s1vVarztF+wTsQwx2fwPs+gC7ou7PxqcA2DNlsn6H1TDX79m6iqNcxUxj/d6AjTSv3wupXCQ6pOUl1emH0HdONEMOmPn63a4bHEk6DnRVbZy4rj1pUjB2uvFPyU7XKTtdbWqzBJRQpaOYPu+H8qqXqle9VL3qpepVL1Wveql61UvVq16qXvVS9aqXqle9VL3qpepVL1Wveql61UvVq949llUPIeuqd89Cc1N7TvArlTdeFCUnxOVECiIpnE4oTaEx7E/0/NqeaNZdV7VOGBQ8grA6cXys6I0/QvYl6TVuuteGTUdG++X2FsH2G5nevALWYoF+2mPLMxG1hjRW8Ey0DaqiFa9xRvI8ypID5C4s4K7msqLLnQTSUPqVXDhdL8VpwrEi99BS/GcsxT+qccf9ELqTwzeOiw3xJLCmJ436dCnwxW6jwDHVxVogj3WIwDQFyRfkobiqCbmqzMgCm0TfgWh3cS7A48+vFZhU82OMV3ak5jfhB8YCDt4p8KY6ZSFNrp9kUpKeN3DbHN0t/brcpKQZiYmpuvFaFBVOpaYzLwx/0qww581q94rnJ9QlGDrzDDBZz8lSjHJMMte/EsIS6Oe7U1aQB6HZBVqb5kfKnsPb+JtosGbIYHX8mgZrsfIeMyc0dRi2JedQyUxxMMoDl543m74yELKkFHCKNJOyKceIwtnttTEAJznqdXzlcB0S/RTCcGGzvmF1uMO5P8H1jV6sHeC/Uh3DNMvQ9qAztD+XCF/M60Mah1RD8cY8/0sLQH+7UFYOVXUPywXtV6I105SjP1MvbpfoYjmwrw0VfZdnT0s0q9eduEiMGyDeVV+2g2w9ZGBNM/76en5HJmr55jIjvqbo1kxWU2ubeQ/+yHHD1eYNZr69F/I1cxpA+NQmIJTIVfQliHpXQ/WqRDVHVFiYRP0UH2BB4nz0byqVf9USfYXsreY+vTNtzefztvgzMjIqYh4Wt128VeZjKAIS/dL2qkmVTP0f3V6Yv72G1F4ztIfG2DnOCyzPNJ8HV6V6sV/BRoEy6OXl4KGaIhtIe+SqOB9e+4lgxoFV4DjAhnvFOgATZJPBjcXKXJWes5nyj5rG3T0JTaPSvasFL7tIOZ3MIDRQc2rQRAyzDCQSrkeCO6xigrs4lHhwFQZa6z8ZrUd9P4rsg2Dxw+8C/IZobSu+6KN6NOToVyX6CSO6tWYJFJk3qmpmQgL7Hx68/8uk/05089aav6KbVn2RgdJGvnsvmvHFbBrUOET0GmL5oLdarcaJGMF759QN4YPhxjLDZGqkRVtDtK3kLvXqWqZnracYO0XVVOso5/+mhtxx9bjhOmARZ+C++CbJrUfNRUdNHbd6pOM2JiYZqXk1fu9bmRfzO/xULpvkaUZ5Dv7MeWL8eergZ2lNb0woVTpmZXH4iZGxfGNSXON+wiJWoLwUC/TemO0=
*/