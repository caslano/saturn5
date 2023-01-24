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
b5QaHW+D08WFSuMK2bf5TBSLN5VmP8Pyi/XGMBM4Fdhpk/gHS72sI4cXaWEMVNuec90JcbxBesOh00ymSxbFMZZiGAZU35SG/fQPRjgYXqqAdUOACADNzjtLofwaW2V9tMna0WTMKz2niyiCWfKGROHjK9f3nAnqlfLgUXfM3ZC5Zv0tc+xv2XUzUhXuIyx5DvvxYbs1hA5cVu0HbjvnQgo1sSkb21A05zz7rwnTk6ReIqvySg3RTVuS8IS169qwUhL/G74VGeC0CsJ5i9p9o2jC2DgCPDfqZE3sLJgQQG9+K2OR9GLvhe2VxdbN7LacnT8M1yPSAYn1j7MPod7TEiGA5KQ7qgfnk82n7TkInn9G8Rdfih13CtPenaWuUrwabdw53wwIx4h0Vg866wj6Zz4/JsaAXrO21kzuQJudkVcOxU2hpc9tR50kWQ2WETKU2Vo8E7GAB9fr2xzCuUi0sgb8xcpFphMrx+gmYwPWsUn9z1jQudxqDEyoBefhwy8CR0LHGekSNRaJ6NKTOb9Fav1ibSSs69xv+u2J/a7LL8qsJcI8lkearfVwthPQIQh9jVzzseoBfKms38+r+PSMVG1kbP0EulR8OM7fPCM/xTS8wkLUv0kay8QFgXp5U3ZozzszByFGJ++Ej0Hc5/AKKNDlLvXPPBDeDjbuXTPt0xGQFRrcyfXCPZ5zC1hyK3q616DO7r96dV9SPiuv
*/