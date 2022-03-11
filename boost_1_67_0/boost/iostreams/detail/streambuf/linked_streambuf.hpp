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