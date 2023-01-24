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
OfZMuvyuzJbkMz6r45vPlLuYx5vDY0J7Pl6vL5RWpNcJ26YsOS7iVkaVz6yUjZzyfsoPZgFV25XTrXeagu++/XD3j16epuJX205wfvjrdahEXNUSH6T9K6uYbxtNEmtLxWTmaJTZ2uW+iEvpTG8Xn92CHx63rrcQz+9Eph/IAu4jPWthhpS9DCVgno2jV47KCv10tlu2IdOFf5qsElhphb2x8t7OPSlWiZrxrdh3vHyYbuLVftiJrUctRzajOYjsMobbhMOlfHtGo8Du7wvX6KdSqIgAYtiEk0QvAowFMOIoSIGCAcshyxP9BHMBtXC5lO3wZEasRmR5WDMhy3GPDHlEV9S7f+RvAaLvyD0xfOBFKP3hKc0JZovusCkp74h7H9l24XfpjP5wQGYPdyd0IMZIaqdlJ004NoxWpsoSyxDLSDrAjU7wpqepBQEFw8LlN+mjLUQUKIswWIevsQdpKPUob5QMyQGFmeExgw35I1fOukgnte6Ou/1n9bgyg3NqETnJhJy3FmrKNM+DYAIZmkEXOckGvFltIwUiroS5NMNJ1Gzhwrj0RAzF7BSuF4W5aeBcUTJ/rh5Hn/a4AtHqMLuxLudtf7C+cn/0SncB4L5dxMOCDlc5v7H0+Lu4fAqVz6CkJyJWxgrLOVlTotjG9OB4AbuA47d0kujUxOUvczKDUkvA77bf/8AB1j/Wj6+9NZ6YELeGUz5RxSul
*/