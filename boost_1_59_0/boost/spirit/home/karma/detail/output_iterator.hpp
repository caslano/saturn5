//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_OUTPUT_ITERATOR_MAY_26_2007_0506PM)
#define BOOST_SPIRIT_KARMA_OUTPUT_ITERATOR_MAY_26_2007_0506PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <iterator>
#include <vector>
#include <algorithm>

#include <boost/config.hpp>
#include <boost/noncopyable.hpp>
#include <boost/mpl/if.hpp>

#include <boost/spirit/home/karma/generator.hpp>
#include <boost/spirit/home/support/iterators/ostream_iterator.hpp>
#include <boost/spirit/home/support/unused.hpp>

#if defined(BOOST_MSVC) && defined(BOOST_SPIRIT_UNICODE)
#include <boost/spirit/home/support/char_encoding/unicode.hpp>
#endif

namespace boost { namespace spirit { namespace karma { namespace detail 
{
    ///////////////////////////////////////////////////////////////////////////
    //  This class is used to keep track of the current position in the output.
    ///////////////////////////////////////////////////////////////////////////
    class position_sink 
    {
    public:
        position_sink() : count(0), line(1), column(1) {}
        void tidy() { count = 0; line = 1; column = 1; }

        template <typename T>
        void output(T const& value) 
        {
            ++count; 
            if (value == '\n') {
                ++line;
                column = 1;
            }
            else {
                ++column;
            }
        }
        std::size_t get_count() const { return count; }
        std::size_t get_line() const { return line; }
        std::size_t get_column() const { return column; }

    private:
        std::size_t count;
        std::size_t line;
        std::size_t column;
    };

    ///////////////////////////////////////////////////////////////////////////
    struct position_policy
    {
        position_policy() {}
        position_policy(position_policy const& rhs) 
          : track_position_data(rhs.track_position_data) {}

        template <typename T>
        void output(T const& value) 
        {
            // track position in the output 
            track_position_data.output(value);
        }

        // return the current count in the output
        std::size_t get_out_count() const
        {
            return track_position_data.get_count();
        }

	// return the current line in the output
	std::size_t get_line() const
	{
	    return track_position_data.get_line();
	}

	// return the current column in the output
	std::size_t get_column() const
	{
	    return track_position_data.get_column();
	}

    private:
        position_sink track_position_data;            // for position tracking
    };

    struct no_position_policy
    {
        no_position_policy() {}
        no_position_policy(no_position_policy const&) {}

        template <typename T>
        void output(T const& /*value*/) {}
    };

    ///////////////////////////////////////////////////////////////////////////
    //  This class is used to count the number of characters streamed into the 
    //  output.
    ///////////////////////////////////////////////////////////////////////////
    template <typename OutputIterator>
    class counting_sink : boost::noncopyable
    {
    public:
        counting_sink(OutputIterator& sink_, std::size_t count_ = 0
              , bool enabled = true) 
          : count(count_), initial_count(count), prev_count(0), sink(sink_)
        {
            prev_count = sink.chain_counting(enabled ? this : NULL);
        }
        ~counting_sink() 
        {
            if (prev_count)           // propagate count 
                prev_count->update_count(count-initial_count);
            sink.chain_counting(prev_count);
        }

        void output() 
        {
            ++count; 
        }
        std::size_t get_count() const { return count; }

        // propagate count from embedded counters
        void update_count(std::size_t c)
        {
            count += c;
        }

    private:
        std::size_t count;
        std::size_t initial_count;
        counting_sink* prev_count;                // previous counter in chain
        OutputIterator& sink;
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename OutputIterator>
    struct counting_policy
    {
    public:
        counting_policy() : count(NULL) {}
        counting_policy(counting_policy const& rhs) : count(rhs.count) {}

        // functions related to counting
        counting_sink<OutputIterator>* chain_counting(
            counting_sink<OutputIterator>* count_data)
        {
            counting_sink<OutputIterator>* prev_count = count;
            count = count_data;
            return prev_count;
        }

        template <typename T>
        void output(T const&) 
        {
            // count characters, if appropriate
            if (NULL != count)
                count->output();
        }

    private:
        counting_sink<OutputIterator>* count;      // for counting
    };

    struct no_counting_policy
    {
        no_counting_policy() {}
        no_counting_policy(no_counting_policy const&) {}

        template <typename T>
        void output(T const& /*value*/) {}
    };

    ///////////////////////////////////////////////////////////////////////////
    //  The following classes are used to intercept the output into a buffer
    //  allowing to do things like alignment, character escaping etc.
    ///////////////////////////////////////////////////////////////////////////
    class buffer_sink : boost::noncopyable
    {
       // wchar_t is only 16-bits on Windows. If BOOST_SPIRIT_UNICODE is
       // defined, the character type is 32-bits wide so we need to make
       // sure the buffer is at least that wide.
#if (defined(_MSC_VER) || defined(__SIZEOF_WCHAR_T__) && __SIZEOF_WCHAR_T__ == 2) && defined(BOOST_SPIRIT_UNICODE)
       typedef spirit::char_encoding::unicode::char_type buffer_char_type;
#else
       typedef wchar_t buffer_char_type;
#endif

    public:
        buffer_sink()
          : width(0) {}

        ~buffer_sink() 
        {
            tidy(); 
        }

        void enable(std::size_t width_) 
        {
            tidy();             // release existing buffer
            width = (width_ == std::size_t(-1)) ? 0 : width_;
            buffer.reserve(width); 
        }

        void tidy() 
        {
            buffer.clear(); 
            width = 0; 
        }

        template <typename T>
        void output(T const& value)
        {
            BOOST_STATIC_ASSERT(sizeof(T) <= sizeof(buffer_char_type));
            buffer.push_back(value);
        }

        template <typename OutputIterator_>
        bool copy(OutputIterator_& sink, std::size_t maxwidth) const 
        {
#if defined(BOOST_MSVC)
#pragma warning(push)
#pragma warning(disable: 4267)
#endif
            typename std::basic_string<buffer_char_type>::const_iterator end = 
                buffer.begin() + (std::min)(buffer.size(), maxwidth);

#if defined(BOOST_MSVC)
#pragma warning(disable: 4244) // conversion from 'x' to 'y', possible loss of data
#endif
            std::copy(buffer.begin(), end, sink);
#if defined(BOOST_MSVC)
#pragma warning(pop)
#endif
            return true;
        }
        template <typename RestIterator>
        bool copy_rest(RestIterator& sink, std::size_t start_at) const 
        {
#if defined(BOOST_MSVC)
#pragma warning(push)
#pragma warning(disable: 4267)
#endif
            typename std::basic_string<buffer_char_type>::const_iterator begin = 
                buffer.begin() + (std::min)(buffer.size(), start_at);

#if defined(BOOST_MSVC)
#pragma warning(disable: 4244) // conversion from 'x' to 'y', possible loss of data
#endif
            std::copy(begin, buffer.end(), sink);
#if defined(BOOST_MSVC)
#pragma warning(pop)
#endif
            return true;
        }

        std::size_t buffer_size() const 
        {
            return buffer.size();
        }

    private:
        std::size_t width;
        std::basic_string<buffer_char_type> buffer;
    };

    ///////////////////////////////////////////////////////////////////////////
    struct buffering_policy
    {
    public:
        buffering_policy() : buffer(NULL) {}
        buffering_policy(buffering_policy const& rhs) : buffer(rhs.buffer) {}

        // functions related to buffering
        buffer_sink* chain_buffering(buffer_sink* buffer_data)
        {
            buffer_sink* prev_buffer = buffer;
            buffer = buffer_data;
            return prev_buffer;
        }

        template <typename T>
        bool output(T const& value) 
        { 
            // buffer characters, if appropriate
            if (NULL != buffer) {
                buffer->output(value);
                return false;
            }
            return true;
        }

        bool has_buffer() const { return NULL != buffer; }

    private:
        buffer_sink* buffer;
    };

    struct no_buffering_policy
    {
        no_buffering_policy() {}
        no_buffering_policy(no_buffering_policy const&) {}

        template <typename T>
        bool output(T const& /*value*/) 
        {
            return true;
        }

        bool has_buffer() const { return false; }
    };

    ///////////////////////////////////////////////////////////////////////////
    //  forward declaration only
    template <typename OutputIterator> 
    struct enable_buffering;

    template <typename OutputIterator, typename Properties
      , typename Derived = unused_type>
    class output_iterator;

    ///////////////////////////////////////////////////////////////////////////
    template <typename Buffering, typename Counting, typename Tracking>
    struct output_iterator_base : Buffering, Counting, Tracking
    {
        typedef Buffering buffering_policy;
        typedef Counting counting_policy;
        typedef Tracking tracking_policy;

        output_iterator_base() {}
        output_iterator_base(output_iterator_base const& rhs) 
          : buffering_policy(rhs), counting_policy(rhs), tracking_policy(rhs)
        {}

        template <typename T>
        bool output(T const& value) 
        { 
            this->counting_policy::output(value);
            this->tracking_policy::output(value);
            return this->buffering_policy::output(value);
        }
    };

    template <typename Buffering, typename Counting, typename Tracking>
    struct disabling_output_iterator : Buffering, Counting, Tracking
    {
        typedef Buffering buffering_policy;
        typedef Counting counting_policy;
        typedef Tracking tracking_policy;

        disabling_output_iterator() : do_output(true) {}
        disabling_output_iterator(disabling_output_iterator const& rhs) 
          : buffering_policy(rhs), counting_policy(rhs), tracking_policy(rhs)
          , do_output(rhs.do_output)
        {}

        template <typename T>
        bool output(T const& value) 
        { 
            if (!do_output) 
                return false;

            this->counting_policy::output(value);
            this->tracking_policy::output(value);
            return this->buffering_policy::output(value);
        }

        bool do_output;
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename OutputIterator, typename Properties, typename Derived>
    struct make_output_iterator
    {
        // get the most derived type of this class
        typedef typename mpl::if_<
            traits::not_is_unused<Derived>, Derived
          , output_iterator<OutputIterator, Properties, Derived>
        >::type most_derived_type;

        static const generator_properties::enum_type properties = static_cast<generator_properties::enum_type>(Properties::value);

        typedef typename mpl::if_c<
            (properties & generator_properties::tracking) ? true : false
          , position_policy, no_position_policy
        >::type tracking_type;

        typedef typename mpl::if_c<
            (properties & generator_properties::buffering) ? true : false
          , buffering_policy, no_buffering_policy
        >::type buffering_type;

        typedef typename mpl::if_c<
            (properties & generator_properties::counting) ? true : false
          , counting_policy<most_derived_type>, no_counting_policy
        >::type counting_type;

        typedef typename mpl::if_c<
            (properties & generator_properties::disabling) ? true : false
          , disabling_output_iterator<buffering_type, counting_type, tracking_type>
          , output_iterator_base<buffering_type, counting_type, tracking_type>
        >::type type;
    };

    ///////////////////////////////////////////////////////////////////////////
    //  Karma uses an output iterator wrapper for all output operations. This
    //  is necessary to avoid the dreaded 'scanner business' problem, i.e. the
    //  dependency of rules and grammars on the used output iterator. 
    //
    //  By default the user supplied output iterator is wrapped inside an 
    //  instance of this internal output_iterator class. 
    //
    //  This output_iterator class normally just forwards to the embedded user
    //  supplied iterator. But it is possible to enable additional functionality
    //  on demand, such as counting, buffering, and position tracking.
    ///////////////////////////////////////////////////////////////////////////
    template <typename OutputIterator, typename Properties, typename Derived>
    class output_iterator 
      : public make_output_iterator<OutputIterator, Properties, Derived>::type
    {
    private:
        // base iterator type
        typedef typename make_output_iterator<
            OutputIterator, Properties, Derived>::type base_iterator;

    public:
        typedef std::output_iterator_tag iterator_category;
        typedef void value_type;
        typedef void difference_type;
        typedef void pointer;
        typedef void reference;

        explicit output_iterator(OutputIterator& sink_)
          : sink(&sink_)
        {}
        output_iterator(output_iterator const& rhs)
          : base_iterator(rhs), sink(rhs.sink)
        {}

        output_iterator& operator*() { return *this; }
        output_iterator& operator++() 
        { 
            if (!this->base_iterator::has_buffer())
                ++(*sink);           // increment only if not buffering
            return *this; 
        } 
        output_iterator operator++(int) 
        {
            if (!this->base_iterator::has_buffer()) {
                output_iterator t(*this);
                ++(*sink); 
                return t; 
            }
            return *this;
        }

#if defined(BOOST_MSVC)
// 'argument' : conversion from '...' to '...', possible loss of data
#pragma warning (push)
#pragma warning (disable: 4244)
#endif
        template <typename T>
        void operator=(T const& value) 
        { 
            if (this->base_iterator::output(value))
                *(*sink) = value; 
        }
#if defined(BOOST_MSVC)
#pragma warning (pop)
#endif

        // plain output iterators are considered to be good all the time
        bool good() const { return true; }

        // allow to access underlying output iterator
        OutputIterator& base() { return *sink; }

    protected:
        // this is the wrapped user supplied output iterator
        OutputIterator* sink;
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename T, typename Elem, typename Traits, typename Properties>
    class output_iterator<karma::ostream_iterator<T, Elem, Traits>, Properties>
      : public output_iterator<karma::ostream_iterator<T, Elem, Traits>, Properties
          , output_iterator<karma::ostream_iterator<T, Elem, Traits>, Properties> >
    {
    private:
        typedef output_iterator<karma::ostream_iterator<T, Elem, Traits>, Properties
          , output_iterator<karma::ostream_iterator<T, Elem, Traits>, Properties> 
        > base_type;
        typedef karma::ostream_iterator<T, Elem, Traits> base_iterator_type;
        typedef std::basic_ostream<Elem, Traits> ostream_type;

    public:
        output_iterator(base_iterator_type& sink)
          : base_type(sink) {}

        ostream_type& get_ostream() { return (*this->sink).get_ostream(); }
        ostream_type const& get_ostream() const { return (*this->sink).get_ostream(); }

        // expose good bit of underlying stream object
        bool good() const { return (*this->sink).get_ostream().good(); }
    };

    ///////////////////////////////////////////////////////////////////////////
    //  Helper class for exception safe enabling of character counting in the
    //  output iterator
    ///////////////////////////////////////////////////////////////////////////
    template <typename OutputIterator>
    struct enable_counting
    {
        enable_counting(OutputIterator& sink_, std::size_t count = 0)
          : count_data(sink_, count) {}

        // get number of characters counted since last enable
        std::size_t count() const
        {
            return count_data.get_count();
        }

    private:
        counting_sink<OutputIterator> count_data;              // for counting
    };

    template <typename OutputIterator>
    struct disable_counting
    {
        disable_counting(OutputIterator& sink_)
          : count_data(sink_, 0, false) {}

    private:
        counting_sink<OutputIterator> count_data;
    };

    ///////////////////////////////////////////////////////////////////////////
    //  Helper class for exception safe enabling of character buffering in the
    //  output iterator
    ///////////////////////////////////////////////////////////////////////////
    template <typename OutputIterator>
    struct enable_buffering
    {
        enable_buffering(OutputIterator& sink_
              , std::size_t width = std::size_t(-1))
          : sink(sink_), prev_buffer(NULL), enabled(false)
        {
            buffer_data.enable(width);
            prev_buffer = sink.chain_buffering(&buffer_data);
            enabled = true;
        }
        ~enable_buffering()
        {
            disable();
        }

        // reset buffer chain to initial state
        void disable()
        {
            if (enabled) {
                BOOST_VERIFY(&buffer_data == sink.chain_buffering(prev_buffer));
                enabled = false;
            }
        }

        // copy to the underlying sink whatever is in the local buffer
        bool buffer_copy(std::size_t maxwidth = std::size_t(-1)
          , bool disable_ = true)
        {
            if (disable_)
                disable();
            return buffer_data.copy(sink, maxwidth) && sink.good();
        }

        // return number of characters stored in the buffer
        std::size_t buffer_size() const
        {
            return buffer_data.buffer_size();
        }

        // copy to the remaining characters to the specified sink
        template <typename RestIterator>
        bool buffer_copy_rest(RestIterator& sink, std::size_t start_at = 0) const
        {
            return buffer_data.copy_rest(sink, start_at);
        }

        // copy the contents to the given output iterator
        template <typename OutputIterator_>
        bool buffer_copy_to(OutputIterator_& sink
          , std::size_t maxwidth = std::size_t(-1)) const
        {
            return buffer_data.copy(sink, maxwidth);
        }

    private:
        OutputIterator& sink;
        buffer_sink buffer_data;    // for buffering
        buffer_sink* prev_buffer;   // previous buffer in chain
        bool enabled;
    };

    ///////////////////////////////////////////////////////////////////////////
    //  Helper class for exception safe disabling of output
    ///////////////////////////////////////////////////////////////////////////
    template <typename OutputIterator>
    struct disable_output
    {
        disable_output(OutputIterator& sink_)
          : sink(sink_), prev_do_output(sink.do_output)
        {
            sink.do_output = false;
        }
        ~disable_output()
        {
            sink.do_output = prev_do_output;
        }

        OutputIterator& sink;
        bool prev_do_output;
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename Sink>
    bool sink_is_good(Sink const&)
    {
        return true;      // the general case is always good
    }

    template <typename OutputIterator, typename Derived>
    bool sink_is_good(output_iterator<OutputIterator, Derived> const& sink)
    {
        return sink.good(); // our own output iterators are handled separately
    }

}}}}

#endif 


/* output_iterator.hpp
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
*/