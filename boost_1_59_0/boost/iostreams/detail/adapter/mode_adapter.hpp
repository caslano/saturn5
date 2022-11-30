// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_MODE_ADAPTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_MODE_ADAPTER_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

// Contains the definition of the class template mode_adapter, which allows
// a filter or device to function as if it has a different i/o mode than that
// deduced by the metafunction mode_of.

#include <boost/config.hpp>                // BOOST_MSVC.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/ios.hpp>  // openmode, seekdir, int types. 
#include <boost/iostreams/traits.hpp>
#include <boost/iostreams/operations.hpp> 
#include <boost/mpl/if.hpp> 

namespace boost { namespace iostreams { namespace detail {

template<typename Mode, typename T>
class mode_adapter {
private:
    struct empty_base { };
public:
    typedef typename wrapped_type<T>::type  component_type;
    typedef typename char_type_of<T>::type  char_type;
    struct category 
        : Mode, 
          device_tag,
          mpl::if_<is_filter<T>, filter_tag, device_tag>,
          mpl::if_<is_filter<T>, multichar_tag, empty_base>,
          closable_tag,
          localizable_tag
        { };
    explicit mode_adapter(const component_type& t) : t_(t) { }

        // Device member functions.

    std::streamsize read(char_type* s, std::streamsize n);
    std::streamsize write(const char_type* s, std::streamsize n);
    std::streampos seek( stream_offset off, BOOST_IOS::seekdir way,
                         BOOST_IOS::openmode which = 
                             BOOST_IOS::in | BOOST_IOS::out );
    void close();
    void close(BOOST_IOS::openmode which);

        // Filter member functions.

    template<typename Source>
    std::streamsize read(Source& src, char_type* s, std::streamsize n)
    { return iostreams::read(t_, src, s, n); }

    template<typename Sink>
    std::streamsize write(Sink& snk, const char_type* s, std::streamsize n)
    { return iostreams::write(t_, snk, s, n); }

    template<typename Device>
    std::streampos seek(Device& dev, stream_offset off, BOOST_IOS::seekdir way)
    { return iostreams::seek(t_, dev, off, way); }

    template<typename Device>
    std::streampos seek( Device& dev, stream_offset off, 
                         BOOST_IOS::seekdir way, BOOST_IOS::openmode which  )
    { return iostreams::seek(t_, dev, off, way, which); }

    template<typename Device>
    void close(Device& dev)
    { detail::close_all(t_, dev); }

    template<typename Device>
    void close(Device& dev, BOOST_IOS::openmode which)
    { iostreams::close(t_, dev, which); }

    template<typename Locale>
    void imbue(const Locale& loc)
    { iostreams::imbue(t_, loc); }
private:
    component_type t_;
};
                    
//------------------Implementation of mode_adapter----------------------------//

template<typename Mode, typename T>
std::streamsize mode_adapter<Mode, T>::read
    (char_type* s, std::streamsize n)
{ return boost::iostreams::read(t_, s, n); }

template<typename Mode, typename T>
std::streamsize mode_adapter<Mode, T>::write
    (const char_type* s, std::streamsize n)
{ return boost::iostreams::write(t_, s, n); }

template<typename Mode, typename T>
std::streampos mode_adapter<Mode, T>::seek
    (stream_offset off, BOOST_IOS::seekdir way, BOOST_IOS::openmode which)
{ return boost::iostreams::seek(t_, off, way, which); }

template<typename Mode, typename T>
void mode_adapter<Mode, T>::close()
{ detail::close_all(t_); }

template<typename Mode, typename T>
void mode_adapter<Mode, T>::close(BOOST_IOS::openmode which)
{ iostreams::close(t_, which); }

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_MODE_ADAPTER_HPP_INCLUDED //-----//

/* mode_adapter.hpp
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
*/