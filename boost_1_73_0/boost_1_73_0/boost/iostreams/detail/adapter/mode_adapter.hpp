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
hynke2MqO0wD5Bur40VsktuiW54VBJb1AJ3Oe4+hBxfE/eLF6JeEfvli9Ed1b9Fn+KuqecZTewnrytRZz6HTwWVO9xdF0ew9SYGYKlodDbNM6KpuXoUxE4mNq1wH1HHwyLTMJV5ay5kBCnOlOEqK1dII40XCCHGlrHaYWSVLZeVLZC0H8rkO+Ig+1q2FYhb9iVvLtX7BfQvu+QVHWPe/IsMKrIu5om3Rop6XWDirMvWh832L6hB9/nRlPhTshzQPCWtlGKj2Ka1ttSK37xDVrgV3d7AMK1iO8J+40bOEG6f1ruUsxHauYtXgVaJ6pDtVtcXTOGs4A+KsS+7nQuKVWhPmkEeMxhy6h67LwpIwq0uc47TFxJTHmgsb4XyIcx7OiQmTlgCGVwKaPKGJMZVdhab0wGYoSOTtQjtUvdS++Nq/3HC8nuqcOQJhfXuh8wwfwxpqrBkaem0sExtPHNjBYWi2Z05rt9aCxpzlzNdM9OWm7xV9N1Euwa0SSbeLSNKR7Kk1dUIcgTbv8H/d88a9KQM8vO8p4nnJrmDR2fyZWFHPbrIHF+L0ItSw9bKRVUPe/WaqedEEwvrWIqhC34N+HzrbixWOlzOYB+ojqCgl1E2h2i3ezq90y531CZuE8Ekqw6iMObl9D3Z34Y0D
*/