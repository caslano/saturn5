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
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
*/