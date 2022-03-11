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