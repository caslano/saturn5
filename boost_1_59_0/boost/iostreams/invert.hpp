// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_INVERT_HPP_INCLUDED
#define BOOST_IOSTREAMS_INVERT_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <algorithm>                             // copy, min.  
#include <boost/assert.hpp>
#include <boost/config.hpp>                      // BOOST_DEDUCED_TYPENAME.       
#include <boost/detail/workaround.hpp>           // default_filter_buffer_size.
#include <boost/iostreams/char_traits.hpp>
#include <boost/iostreams/compose.hpp>
#include <boost/iostreams/constants.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/detail/buffer.hpp>
#include <boost/iostreams/detail/counted_array.hpp>
#include <boost/iostreams/detail/execute.hpp>
#include <boost/iostreams/detail/functional.hpp> // clear_flags, call_reset
#include <boost/mpl/if.hpp>
#include <boost/ref.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/type_traits/is_convertible.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>  // MSVC.

namespace boost { namespace iostreams {

//
// Template name: inverse.
// Template parameters:
//      Filter - A model of InputFilter or OutputFilter.
// Description: Generates an InputFilter from an OutputFilter or
//      vice versa.
//
template<typename Filter>
class inverse {
private:
    BOOST_STATIC_ASSERT(is_filter<Filter>::value);
    typedef typename category_of<Filter>::type   base_category;
    typedef reference_wrapper<Filter>            filter_ref;
public:
    typedef typename char_type_of<Filter>::type  char_type;
    typedef typename int_type_of<Filter>::type   int_type;
    typedef char_traits<char_type>               traits_type;
    typedef typename 
            mpl::if_<
                is_convertible<
                    base_category,
                    input
                >,
                output,
                input
            >::type                              mode;
    struct category 
        : mode, 
          filter_tag, 
          multichar_tag, 
          closable_tag 
        { };
    explicit inverse( const Filter& filter, 
                      std::streamsize buffer_size = 
                          default_filter_buffer_size) 
        : pimpl_(new impl(filter, buffer_size))
        { }

    template<typename Source>
    std::streamsize read(Source& src, char_type* s, std::streamsize n)
    {
        typedef detail::counted_array_sink<char_type>  array_sink;
        typedef composite<filter_ref, array_sink>      filtered_array_sink;

        BOOST_ASSERT((flags() & f_write) == 0);
        if (flags() == 0) {
            flags() = f_read;
            buf().set(0, 0);
        }

        filtered_array_sink snk(filter(), array_sink(s, n));
        int_type status;
        for ( status = traits_type::good();
              snk.second().count() < n && status == traits_type::good(); )
        {
            status = buf().fill(src);
            buf().flush(snk);
        }
        return snk.second().count() == 0 &&
               status == traits_type::eof() 
                   ? 
               -1
                   : 
               snk.second().count();
    }

    template<typename Sink>
    std::streamsize write(Sink& dest, const char_type* s, std::streamsize n)
    {
        typedef detail::counted_array_source<char_type>  array_source;
        typedef composite<filter_ref, array_source>      filtered_array_source;

        BOOST_ASSERT((flags() & f_read) == 0);
        if (flags() == 0) {
            flags() = f_write;
            buf().set(0, 0);
        }
        
        filtered_array_source src(filter(), array_source(s, n));
        for (bool good = true; src.second().count() < n && good; ) {
            buf().fill(src);
            good = buf().flush(dest);
        }
        return src.second().count();
    }

    template<typename Device>
    void close(Device& dev)
    {
        detail::execute_all(
            detail::flush_buffer(buf(), dev, (flags() & f_write) != 0),
            detail::call_close_all(pimpl_->filter_, dev),
            detail::clear_flags(flags())
        );
    }
private:
    filter_ref filter() { return boost::ref(pimpl_->filter_); }
    detail::buffer<char_type>& buf() { return pimpl_->buf_; }
    int& flags() { return pimpl_->flags_; }
    
    enum flags_ {
        f_read = 1, f_write = 2
    };

    struct impl {
        impl(const Filter& filter, std::streamsize n) 
            : filter_(filter), buf_(n), flags_(0)
        { buf_.set(0, 0); }
        Filter                     filter_;
        detail::buffer<char_type>  buf_;
        int                        flags_;
    };
    shared_ptr<impl> pimpl_;
};

//
// Template name: invert.
// Template parameters:
//      Filter - A model of InputFilter or OutputFilter.
// Description: Returns an instance of an appropriate specialization of inverse.
//
template<typename Filter>
inverse<Filter> invert(const Filter& f) { return inverse<Filter>(f); }
                    
//----------------------------------------------------------------------------//

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>  // MSVC.

#endif // #ifndef BOOST_IOSTREAMS_INVERT_HPP_INCLUDED

/* invert.hpp
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
*/