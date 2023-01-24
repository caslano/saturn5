// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_FILTERING_STREAMBUF_HPP_INCLUDED
#define BOOST_IOSTREAMS_FILTERING_STREAMBUF_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <exception>
#include <memory>                               // allocator.
#include <boost/iostreams/chain.hpp>
#include <boost/iostreams/detail/access_control.hpp>
#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/push.hpp>
#include <boost/iostreams/detail/streambuf.hpp> // pubsync.
#include <boost/iostreams/detail/streambuf/chainbuf.hpp>
#include <boost/mpl/if.hpp>                    

namespace boost { namespace iostreams {

//
// Macro: BOOST_IOSTREAMS_DEFINE_FILTERBUF(name_, chain_type_, default_char_)
// Description: Defines a template derived from std::basic_streambuf which uses
//      a chain to perform i/o. The template has the following parameters:
//      Ch - The character type.
//      Tr - The character traits type.
//      Alloc - The allocator type.
//      Access - Indicates accessibility of the chain interface; must be either
//          public_ or protected_; defaults to public_.
//
#define BOOST_IOSTREAMS_DEFINE_FILTER_STREAMBUF(name_, chain_type_, default_char_) \
    template< typename Mode, \
              typename Ch = default_char_, \
              typename Tr = BOOST_IOSTREAMS_CHAR_TRAITS(Ch), \
              typename Alloc = std::allocator<Ch>, \
              typename Access = public_ > \
    class name_ : public boost::iostreams::detail::chainbuf< \
                             chain_type_<Mode, Ch, Tr, Alloc>, Mode, Access \
                         > \
    { \
    public: \
        typedef Ch                                             char_type; \
        struct category \
            : Mode, closable_tag, streambuf_tag \
            { }; \
        BOOST_IOSTREAMS_STREAMBUF_TYPEDEFS(Tr) \
        typedef Mode                                           mode; \
        typedef chain_type_<Mode, Ch, Tr, Alloc>               chain_type; \
        name_() { } \
        BOOST_IOSTREAMS_DEFINE_PUSH_CONSTRUCTOR(name_, mode, Ch, push_impl) \
        ~name_() { if (this->is_complete()) this->BOOST_IOSTREAMS_PUBSYNC(); } \
    }; \
    /**/ 
BOOST_IOSTREAMS_DEFINE_FILTER_STREAMBUF(filtering_streambuf, boost::iostreams::chain, char)
BOOST_IOSTREAMS_DEFINE_FILTER_STREAMBUF(filtering_wstreambuf, boost::iostreams::chain, wchar_t)

typedef filtering_streambuf<input>    filtering_istreambuf;
typedef filtering_streambuf<output>   filtering_ostreambuf;
typedef filtering_wstreambuf<input>   filtering_wistreambuf;
typedef filtering_wstreambuf<output>  filtering_wostreambuf;

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_FILTERING_STREAMBUF_HPP_INCLUDED

/* filtering_streambuf.hpp
9SPjcWtDcxouE2XT0WltMQjvyy/tTltTvKGlktCmITs63CpmJ8OQ4XNjwCbnwJ0dNDiF0OM0IYtbFYC6DusqJLclhzgShXeJmG2ItZm+3JApBo9K0syeRf+K+jWITZ3Rsx8kcZFGVO/TjvNcKmZBE28A4T22eo4PXrDuw6WGeGZSh72zf0OlG+6lGb54lOSD9f3LYNR7fkudMfH2KxK+aModiWus+7jkSVIXN2FsZjuCByTq8AIthrvRRGmmQwKgdAVMU+KUNzR0fIb7e357udTlj3RZ8aw//SKW8MxHKrlhEpH8CoB04ZDv85gziAXMAAafyoIUY3znUWU2V5Ms+8xfZF0Z7KIGw4Mx2yrjS4i4HhSr9mOEunCJVAb1nQu63qBnRcGLcZANBokEPKhspSrw5j7FYKFshYtJMEV8fg615CsbXrCvcDblS3jHTE13ZBBkxPqSveQJ9zHw5LrlQQkahQhmBmJCxJw1hseyVx2X/jAvgz3jT+8mTSeTAlgUbeG+TG1RTykgklaETFYKk8DMyNxcYritPzQ0ZXe3CSw55ODshEE8UbCwOp4dkc1hLrM0U72UX2kje7oyBDHAukVMF720Zd+OcfOlbuYVF6nGjkxH07Ud/+gKluKWWYpUMF/OWuz+2QzwOpa9XV19XoGsSLMsLEU3ute5yAAlnM2de/Vk6CDlIl8yOla1eAl6SE3LXpbGyb9+A3Hg
*/