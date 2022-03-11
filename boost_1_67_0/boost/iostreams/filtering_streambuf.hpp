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