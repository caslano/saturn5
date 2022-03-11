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