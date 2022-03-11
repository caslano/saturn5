// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2004-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_FILTER_STREAM_HPP_INCLUDED
#define BOOST_IOSTREAMS_FILTER_STREAM_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <memory>                                     // allocator.
#include <boost/iostreams/detail/access_control.hpp>
#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/iostream.hpp>        // standard streams.
#include <boost/iostreams/detail/push.hpp>
#include <boost/iostreams/detail/select.hpp>
#include <boost/iostreams/detail/streambuf.hpp>       // pubsync.
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>  // MSVC.

namespace boost { namespace iostreams {

//--------------Definition of filtered_istream--------------------------------//

namespace detail {

template<typename Mode, typename Ch, typename Tr>
struct filtering_stream_traits {
    typedef typename 
            iostreams::select<  // Disambiguation for Tru64  
                mpl::and_< 
                    is_convertible<Mode, input>, 
                    is_convertible<Mode, output> 
                >,          
                BOOST_IOSTREAMS_BASIC_IOSTREAM(Ch, Tr),
                is_convertible<Mode, input>, 
                BOOST_IOSTREAMS_BASIC_ISTREAM(Ch, Tr),
                else_,        
                BOOST_IOSTREAMS_BASIC_OSTREAM(Ch, Tr)
            >::type stream_type;
    typedef typename
            iostreams::select< // Dismbiguation required for Tru64.
                mpl::and_<
                    is_convertible<Mode, input>,
                    is_convertible<Mode, output>
                >,
                iostream_tag,
                is_convertible<Mode, input>,
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

template<typename Chain, typename Access>
class filtering_stream_base 
    : public access_control<
                 boost::iostreams::detail::chain_client<Chain>,
                 Access
             >,
      public filtering_stream_traits<
                 typename Chain::mode, 
                 typename Chain::char_type, 
                 typename Chain::traits_type
             >::stream_type
{
public:
    typedef Chain                                         chain_type;
    typedef access_control<
                 boost::iostreams::detail::chain_client<Chain>,
                 Access
             >                                            client_type;
protected:
    typedef typename 
            filtering_stream_traits<
                 typename Chain::mode, 
                 typename Chain::char_type, 
                 typename Chain::traits_type
            >::stream_type                                stream_type;
    filtering_stream_base() : stream_type(0) { this->set_chain(&chain_); }
private:
    void notify() { this->rdbuf(chain_.empty() ? 0 : &chain_.front()); }
    Chain chain_;
};

#if defined(BOOST_MSVC) && (BOOST_MSVC == 1700)
# pragma warning(pop)
#endif

} // End namespace detail.

//
// Macro: BOOST_IOSTREAMS_DEFINE_FILTER_STREAM(name_, chain_type_, default_char_)
// Description: Defines a template derived from std::basic_streambuf which uses
//      a chain to perform i/o. The template has the following parameters:
//      Mode - the i/o mode.
//      Ch - The character type.
//      Tr - The character traits type.
//      Alloc - The allocator type.
//      Access - Indicates accessibility of the chain interface; must be either
//          public_ or protected_; defaults to public_.
// Macro parameters:
//      name_ - The name of the template to be defined.
//      chain_type_ - The name of the chain template.
//      default_char_ - The default value for the char template parameter.
//
#define BOOST_IOSTREAMS_DEFINE_FILTER_STREAM(name_, chain_type_, default_char_) \
    template< typename Mode, \
              typename Ch = default_char_, \
              typename Tr = BOOST_IOSTREAMS_CHAR_TRAITS(Ch), \
              typename Alloc = std::allocator<Ch>, \
              typename Access = public_ > \
    class name_ \
        : public boost::iostreams::detail::filtering_stream_base< \
                     chain_type_<Mode, Ch, Tr, Alloc>, Access \
                 > \
    { \
    public: \
        typedef Ch                                char_type; \
        struct category \
            : Mode, \
              closable_tag, \
              detail::filtering_stream_traits<Mode, Ch, Tr>::stream_tag \
            { }; \
        BOOST_IOSTREAMS_STREAMBUF_TYPEDEFS(Tr) \
        typedef Mode                              mode; \
        typedef chain_type_<Mode, Ch, Tr, Alloc>  chain_type; \
        name_() { } \
        BOOST_IOSTREAMS_DEFINE_PUSH_CONSTRUCTOR(name_, mode, Ch, push_impl) \
        ~name_() { \
            if (this->is_complete()) \
                 this->rdbuf()->BOOST_IOSTREAMS_PUBSYNC(); \
        } \
    private: \
        typedef access_control< \
                    boost::iostreams::detail::chain_client< \
                        chain_type_<Mode, Ch, Tr, Alloc> \
                    >, \
                    Access \
                > client_type; \
        template<typename T> \
        void push_impl(const T& t BOOST_IOSTREAMS_PUSH_PARAMS()) \
        { client_type::push(t BOOST_IOSTREAMS_PUSH_ARGS()); } \
    }; \
    /**/    

#if defined(BOOST_MSVC) && (BOOST_MSVC == 1700)
# pragma warning(push)
// https://connect.microsoft.com/VisualStudio/feedback/details/733720/
# pragma warning(disable: 4250)
#endif

BOOST_IOSTREAMS_DEFINE_FILTER_STREAM(filtering_stream, boost::iostreams::chain, char)
BOOST_IOSTREAMS_DEFINE_FILTER_STREAM(wfiltering_stream, boost::iostreams::chain, wchar_t)

#if defined(BOOST_MSVC) && (BOOST_MSVC == 1700)
# pragma warning(pop)
#endif

typedef filtering_stream<input>    filtering_istream;
typedef filtering_stream<output>   filtering_ostream;
typedef wfiltering_stream<input>   filtering_wistream;
typedef wfiltering_stream<output>  filtering_wostream;

//----------------------------------------------------------------------------//

} } // End namespace iostreams, boost

#include <boost/iostreams/detail/config/enable_warnings.hpp> // MSVC

#endif // #ifndef BOOST_IOSTREAMS_FILTER_STREAM_HPP_INCLUDED

/* filtering_stream.hpp
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
*/