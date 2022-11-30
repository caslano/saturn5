// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_LINKED_STREAMBUF_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_LINKED_STREAMBUF_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp>                        // member template friends.
#include <boost/core/typeinfo.hpp>
#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/ios.hpp>          // openmode.
#include <boost/iostreams/detail/streambuf.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp> // MSVC.

namespace boost { namespace iostreams { namespace detail {

template<typename Self, typename Ch, typename Tr, typename Alloc, typename Mode>
class chain_base;

template<typename Chain, typename Access, typename Mode> class chainbuf;

#define BOOST_IOSTREAMS_USING_PROTECTED_STREAMBUF_MEMBERS(base) \
    using base::eback; using base::gptr; using base::egptr; \
    using base::setg; using base::gbump; using base::pbase; \
    using base::pptr; using base::epptr; using base::setp; \
    using base::pbump; using base::underflow; using base::pbackfail; \
    using base::xsgetn; using base::overflow; using base::xsputn; \
    using base::sync; using base::seekoff; using base::seekpos; \
    /**/

template<typename Ch, typename Tr = BOOST_IOSTREAMS_CHAR_TRAITS(Ch) >
class linked_streambuf : public BOOST_IOSTREAMS_BASIC_STREAMBUF(Ch, Tr) {
protected:
    linked_streambuf() : flags_(0) { }
    void set_true_eof(bool eof) 
    { 
        flags_ = (flags_ & ~f_true_eof) | (eof ? f_true_eof : 0); 
    }
public:

    // Should be called only after receiving an ordinary EOF indication,
    // to confirm that it represents EOF rather than WOULD_BLOCK.
    bool true_eof() const { return (flags_ & f_true_eof) != 0; }
protected:

    //----------grant friendship to chain_base and chainbuf-------------------//

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
    template< typename Self, typename ChT, typename TrT,
              typename Alloc, typename Mode >
    friend class chain_base;
    template<typename Chain, typename Mode, typename Access>
    friend class chainbuf;
    template<typename U>
    friend class member_close_operation; 
#else
    public:
        typedef BOOST_IOSTREAMS_BASIC_STREAMBUF(Ch, Tr) base;
        BOOST_IOSTREAMS_USING_PROTECTED_STREAMBUF_MEMBERS(base)
#endif
    void close(BOOST_IOS::openmode which)
    {
        if ( which == BOOST_IOS::in && 
            (flags_ & f_input_closed) == 0 )
        {
            flags_ |= f_input_closed;
            close_impl(which);
        }
        if ( which == BOOST_IOS::out && 
            (flags_ & f_output_closed) == 0 )
        {
            flags_ |= f_output_closed;
            close_impl(which);
        }
    }
    void set_needs_close()
    {
        flags_ &= ~(f_input_closed | f_output_closed);
    }
    virtual void set_next(linked_streambuf<Ch, Tr>* /* next */) { }
    virtual void close_impl(BOOST_IOS::openmode) = 0;
    virtual bool auto_close() const = 0;
    virtual void set_auto_close(bool) = 0;
    virtual bool strict_sync() = 0;
    virtual const boost::core::typeinfo& component_type() const = 0;
    virtual void* component_impl() = 0;
#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
    private:
#else
    public:
#endif
private:
    enum flag_type {
        f_true_eof       = 1,
        f_input_closed   = f_true_eof << 1,
        f_output_closed  = f_input_closed << 1
    };
    int flags_;
};

} } } // End namespaces detail, iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp> // MSVC.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_LINKED_STREAMBUF_HPP_INCLUDED

/* linked_streambuf.hpp
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
*/