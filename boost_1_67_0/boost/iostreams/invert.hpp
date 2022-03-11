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