// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_STREAM_BUFFER_HPP_INCLUDED
#define BOOST_IOSTREAMS_STREAM_BUFFER_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <memory>            // allocator.
#include <boost/config.hpp>  // BOOST_DEDUCED_TYPENAME.
#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/config/overload_resolution.hpp>
#include <boost/iostreams/detail/forward.hpp>
#include <boost/iostreams/detail/ios.hpp>  // failure, streamsize.
#include <boost/iostreams/detail/streambuf/direct_streambuf.hpp>
#include <boost/iostreams/detail/streambuf/indirect_streambuf.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type_traits/is_convertible.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>  // MSVC.

namespace boost { namespace iostreams { namespace detail {

template<typename T, typename Tr, typename Alloc, typename Mode>
struct stream_buffer_traits {
    typedef typename
            mpl::if_<
                is_convertible<
                    BOOST_DEDUCED_TYPENAME category_of<T>::type,
                    direct_tag
                >,
                direct_streambuf<T, Tr>,
                indirect_streambuf<T, Tr, Alloc, Mode>
            >::type type;
};

} } } // End namespaces detail, iostreams, boost

#ifdef BOOST_IOSTREAMS_BROKEN_OVERLOAD_RESOLUTION
# include <boost/iostreams/detail/broken_overload_resolution/stream_buffer.hpp>
#else

namespace boost { namespace iostreams {

template< typename T,
          typename Tr =
              BOOST_IOSTREAMS_CHAR_TRAITS(
                  BOOST_DEDUCED_TYPENAME char_type_of<T>::type
              ),
          typename Alloc =
              std::allocator<
                  BOOST_DEDUCED_TYPENAME char_type_of<T>::type
              >,
          typename Mode = BOOST_DEDUCED_TYPENAME mode_of<T>::type >
class stream_buffer
    : public detail::stream_buffer_traits<T, Tr, Alloc, Mode>::type
{
private:
    BOOST_STATIC_ASSERT((
        is_convertible<
            BOOST_DEDUCED_TYPENAME iostreams::category_of<T>::type, Mode
        >::value
    ));
    typedef typename
            detail::stream_buffer_traits<
                T, Tr, Alloc, Mode
            >::type                           base_type;
public:
    typedef typename char_type_of<T>::type    char_type;
    struct category 
        : Mode,
          closable_tag,
          streambuf_tag
        { };
    BOOST_IOSTREAMS_STREAMBUF_TYPEDEFS(Tr)
public:
    stream_buffer() { }
    ~stream_buffer()
    { 
        try { 
            if (this->is_open() && this->auto_close()) 
                this->close(); 
        } catch (...) { } 
    }
    BOOST_IOSTREAMS_FORWARD( stream_buffer, open_impl, T,
                             BOOST_IOSTREAMS_PUSH_PARAMS,
                             BOOST_IOSTREAMS_PUSH_ARGS )
    T& operator*() { return *this->component(); }
    T* operator->() { return this->component(); }
private:
    void open_impl(const T& t BOOST_IOSTREAMS_PUSH_PARAMS())
        {   // Used for forwarding.
            if (this->is_open())
                boost::throw_exception(
                    BOOST_IOSTREAMS_FAILURE("already open")
                );
            base_type::open(t BOOST_IOSTREAMS_PUSH_ARGS());
        }
};

} } // End namespaces iostreams, boost.

#endif // #ifdef BOOST_IOSTREAMS_BROKEN_OVERLOAD_RESOLUTION

#include <boost/iostreams/detail/config/enable_warnings.hpp>  // MSVC.

#endif // #ifndef BOOST_IOSTREAMS_STREAM_BUFFER_HPP_INCLUDED

/* stream_buffer.hpp
jtCzj5pz2ETn6kUjTGA7UkF93+kg+61G68xZpXXd2/qDo1LhzzZ0+SGINXloaKQ85zK0LIqFNGISScQXmtlaBEh4FscM6fs3OawOcJu/Z387NlGEt9+fg1gRBTsZ3e+So9EDe7QvlU8YAyo+lD0NcHfzzoKAsWISZmxusz1tXkCRithXvx9FQhaXql22Rb+P6nbOzF3JvVJFwnCkLNDOdPPonWWJ+iJAZahwvmLZMkTshKFnYp5cJiemaXKxtGa9ssYMgyjBHfCD4ylcBA+hufPNNZ6WbmbkxPCe3npUlrxnZFcw6hcy2cV1dtTbx18fXDwCfcrcqs3c4H7UcEy8EDiPXt2myAbx0x4meel0p5JGWBYdtFMFyNDZL/tZL7sBUS9I+OYFHN1Jr9y9H8GXHko0g+HKRCLTJPEIynQ/cCuBib+818nNUJkmsqmgSKhz+souk9k8baQvfL/fnjcxzGNKNwwvS0XraYQUB6vsT+2okcWlptU7+MVre5YWLhHqd/OkkMacGrsWMyPxDhriMKdm27alBZdRf20I8YTkMuMdMbNOyu8Ob4PimJUaUGp0M7RBGXK7w6+bqDoZQ4A5R4es691hkvZM6qo5dt+FHwKYRAu7v6aySCLv44hjYiVpG3htOa4Q4tzchuBn5VH7HEFpSkmHehsXV87ZbLOrUMpuvLjKFnD8kVUFxc7rvBmTX+SaOc8KUSEuyFou
*/