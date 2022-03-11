// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_STREAM_HPP_INCLUDED
#define BOOST_IOSTREAMS_STREAM_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/iostreams/constants.hpp>
#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/config/overload_resolution.hpp>
#include <boost/iostreams/detail/forward.hpp>
#include <boost/iostreams/detail/iostream.hpp>  // standard streams.
#include <boost/iostreams/detail/select.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/mpl/and.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/base_from_member.hpp>

namespace boost { namespace iostreams { namespace detail {

template<typename Device, typename Tr>
struct stream_traits {
    typedef typename char_type_of<Device>::type                char_type;
    typedef Tr                                                 traits_type;
    typedef typename category_of<Device>::type                 mode;
    typedef typename
            iostreams::select< // Disambiguation required for Tru64.
                mpl::and_<
                    is_convertible<mode, input>,
                    is_convertible<mode, output>
                >,
                BOOST_IOSTREAMS_BASIC_IOSTREAM(char_type, traits_type),
                is_convertible<mode, input>,
                BOOST_IOSTREAMS_BASIC_ISTREAM(char_type, traits_type),
                else_,
                BOOST_IOSTREAMS_BASIC_OSTREAM(char_type, traits_type)
            >::type stream_type;
    typedef typename
            iostreams::select< // Disambiguation required for Tru64.
                mpl::and_<
                    is_convertible<mode, input>,
                    is_convertible<mode, output>
                >,
                iostream_tag,
                is_convertible<mode, input>,
                istream_tag,
                else_,
                ostream_tag
            >::type stream_tag;
};

#if defined(BOOST_MSVC) && (BOOST_MSVC == 1700)
# pragma warning(push)
// https://connect.microsoft.com/VisualStudio/feedback/details/733720/
# pragma warning(disable: 4250)
#endif

// By encapsulating initialization in a base, we can define the macro
// BOOST_IOSTREAMS_DEFINE_FORWARDING_FUNCTIONS to generate constructors
// without base member initializer lists.
template< typename Device,
          typename Tr =
              BOOST_IOSTREAMS_CHAR_TRAITS(
                  BOOST_DEDUCED_TYPENAME char_type_of<Device>::type
              ),
          typename Alloc =
              std::allocator<
                  BOOST_DEDUCED_TYPENAME char_type_of<Device>::type
              >,
          typename Base = // VC6 Workaround.
              BOOST_DEDUCED_TYPENAME
              detail::stream_traits<Device, Tr>::stream_type >
class stream_base
    : protected base_from_member< stream_buffer<Device, Tr, Alloc> >,
      public Base
{
private:
    typedef base_from_member< stream_buffer<Device, Tr, Alloc> >  pbase_type;
    typedef typename stream_traits<Device, Tr>::stream_type       stream_type;
protected:
    using pbase_type::member; // Avoid warning about 'this' in initializer list.
public:
    stream_base() : pbase_type(), stream_type(&member) { }
};

#if defined(BOOST_MSVC) && (BOOST_MSVC == 1700)
# pragma warning(pop)
#endif

} } } // End namespaces detail, iostreams, boost.

#ifdef BOOST_IOSTREAMS_BROKEN_OVERLOAD_RESOLUTION
# include <boost/iostreams/detail/broken_overload_resolution/stream.hpp>
#else

namespace boost { namespace iostreams {

#if defined(BOOST_MSVC) && (BOOST_MSVC == 1700)
# pragma warning(push)
// https://connect.microsoft.com/VisualStudio/feedback/details/733720/
# pragma warning(disable: 4250)
#endif

//
// Template name: stream.
// Description: A iostream which reads from and writes to an instance of a
//      designated device type.
// Template parameters:
//      Device - A device type.
//      Alloc - The allocator type.
//
template< typename Device,
          typename Tr =
              BOOST_IOSTREAMS_CHAR_TRAITS(
                  BOOST_DEDUCED_TYPENAME char_type_of<Device>::type
              ),
          typename Alloc =
              std::allocator<
                  BOOST_DEDUCED_TYPENAME char_type_of<Device>::type
              > >
struct stream : detail::stream_base<Device, Tr, Alloc> {
public:
    typedef typename char_type_of<Device>::type  char_type;
    struct category 
        : mode_of<Device>::type,
          closable_tag,
          detail::stream_traits<Device, Tr>::stream_tag
        { };
    BOOST_IOSTREAMS_STREAMBUF_TYPEDEFS(Tr)
private:
    typedef typename
            detail::stream_traits<
                Device, Tr
            >::stream_type                       stream_type;
public:
    stream() { }
    BOOST_IOSTREAMS_FORWARD( stream, open_impl, Device,
                             BOOST_IOSTREAMS_PUSH_PARAMS,
                             BOOST_IOSTREAMS_PUSH_ARGS )
    bool is_open() const { return this->member.is_open(); }
    void close() { this->member.close(); }
    bool auto_close() const { return this->member.auto_close(); }
    void set_auto_close(bool close) { this->member.set_auto_close(close); }
    bool strict_sync() { return this->member.strict_sync(); }
    Device& operator*() { return *this->member; }
    Device* operator->() { return &*this->member; }
    Device* component() { return this->member.component(); }
private:
    void open_impl(const Device& dev BOOST_IOSTREAMS_PUSH_PARAMS()) // For forwarding.
    { 
        this->clear(); 
        this->member.open(dev BOOST_IOSTREAMS_PUSH_ARGS()); 
    }
};

#if defined(BOOST_MSVC) && (BOOST_MSVC == 1700)
# pragma warning(pop)
#endif

} } // End namespaces iostreams, boost.

#endif // #ifdef BOOST_IOSTREAMS_BROKEN_OVERLOAD_RESOLUTION

#endif // #ifndef BOOST_IOSTREAMS_stream_HPP_INCLUDED

/* stream.hpp
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
*/