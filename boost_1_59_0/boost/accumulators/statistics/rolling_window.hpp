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
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
*/