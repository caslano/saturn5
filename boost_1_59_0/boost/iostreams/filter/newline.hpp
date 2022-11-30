// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// NOTE: I hope to replace the current implementation with a much simpler
// one.

#ifndef BOOST_IOSTREAMS_NEWLINE_FILTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_NEWLINE_FILTER_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assert.hpp>
#include <cstdio>
#include <stdexcept>                       // logic_error.
#include <boost/config.hpp>                // BOOST_STATIC_CONSTANT.
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/ios.hpp>  // BOOST_IOSTREAMS_FAILURE 
#include <boost/iostreams/read.hpp>        // get 
#include <boost/iostreams/write.hpp>       // put 
#include <boost/iostreams/pipeline.hpp>
#include <boost/iostreams/putback.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type_traits/is_convertible.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>

#define BOOST_IOSTREAMS_ASSERT_UNREACHABLE(val) \
    (BOOST_ASSERT("unreachable code" == 0), val) \
    /**/

namespace boost { namespace iostreams {

namespace newline {

const char CR                   = 0x0D;
const char LF                   = 0x0A;

    // Flags for configuring newline_filter.

// Exactly one of the following three flags must be present.

const int posix             = 1;    // Use CR as line separator.
const int mac               = 2;    // Use LF as line separator.
const int dos               = 4;    // Use CRLF as line separator.
const int mixed             = 8;    // Mixed line endings.
const int final_newline     = 16;
const int platform_mask     = posix | dos | mac;

} // End namespace newline.

namespace detail {

class newline_base {
public:
    bool is_posix() const
    {
        return !is_mixed() && (flags_ & newline::posix) != 0;
    }
    bool is_dos() const
    {
        return !is_mixed() && (flags_ & newline::dos) != 0;
    }
    bool is_mac() const
    {
        return !is_mixed() && (flags_ & newline::mac) != 0;
    }
    bool is_mixed_posix() const { return (flags_ & newline::posix) != 0; }
    bool is_mixed_dos() const { return (flags_ & newline::dos) != 0; }
    bool is_mixed_mac() const { return (flags_ & newline::mac) != 0; }
    bool is_mixed() const
    {
        int platform =
            (flags_ & newline::posix) != 0 ?
                newline::posix :
                (flags_ & newline::dos) != 0 ?
                    newline::dos :
                    (flags_ & newline::mac) != 0 ?
                        newline::mac :
                        0;
        return (flags_ & ~platform & newline::platform_mask) != 0;
    }
    bool has_final_newline() const
    {
        return (flags_ & newline::final_newline) != 0;
    }
protected:
    newline_base(int flags) : flags_(flags) { }
    int flags_;
};

} // End namespace detail.

class newline_error
    : public BOOST_IOSTREAMS_FAILURE, public detail::newline_base
{
private:
    friend class newline_checker;
    newline_error(int flags)
        : BOOST_IOSTREAMS_FAILURE("bad line endings"),
          detail::newline_base(flags)
        { }
};

class newline_filter {
public:
    typedef char char_type;
    struct category
        : dual_use,
          filter_tag,
          closable_tag
        { };

    explicit newline_filter(int target) : flags_(target)
    {
        if ( target != iostreams::newline::posix &&
             target != iostreams::newline::dos &&
             target != iostreams::newline::mac )
        {
            boost::throw_exception(std::logic_error("bad flags"));
        }
    }

    template<typename Source>
    int get(Source& src)
    {
        using iostreams::newline::CR;
        using iostreams::newline::LF;

        BOOST_ASSERT((flags_ & f_write) == 0);
        flags_ |= f_read;

        if (flags_ & (f_has_LF | f_has_EOF)) {
            if (flags_ & f_has_LF)
                return newline();
            else
                return EOF;
        }

        int c =
            (flags_ & f_has_CR) == 0 ?
                iostreams::get(src) :
                CR;

        if (c == WOULD_BLOCK )
            return WOULD_BLOCK;

        if (c == CR) {
            flags_ |= f_has_CR;

            int d;
            if ((d = iostreams::get(src)) == WOULD_BLOCK)
                return WOULD_BLOCK;

            if (d == LF) {
                flags_ &= ~f_has_CR;
                return newline();
            }

            if (d == EOF) {
                flags_ |= f_has_EOF;
            } else {
                iostreams::putback(src, d);
            }

            flags_ &= ~f_has_CR;
            return newline();
        }

        if (c == LF)
            return newline();

        return c;
    }

    template<typename Sink>
    bool put(Sink& dest, char c)
    {
        using iostreams::newline::CR;
        using iostreams::newline::LF;

        BOOST_ASSERT((flags_ & f_read) == 0);
        flags_ |= f_write;

        if ((flags_ & f_has_LF) != 0)
            return c == LF ?
                newline(dest) :
                newline(dest) && this->put(dest, c);

        if (c == LF)
           return newline(dest);

        if ((flags_ & f_has_CR) != 0)
            return newline(dest) ?
                this->put(dest, c) :
                false;

        if (c == CR) {
            flags_ |= f_has_CR;
            return true;
        }

        return iostreams::put(dest, c);
    }

    template<typename Sink>
    void close(Sink& dest, BOOST_IOS::openmode)
    {
        if ((flags_ & f_write) != 0 && (flags_ & f_has_CR) != 0)
            newline_if_sink(dest);
        flags_ &= ~f_has_LF; // Restore original flags.
    }
private:

    // Returns the appropriate element of a newline sequence.
    int newline()
    {
        using iostreams::newline::CR;
        using iostreams::newline::LF;

        switch (flags_ & iostreams::newline::platform_mask) {
        case iostreams::newline::posix:
            return LF;
        case iostreams::newline::mac:
            return CR;
        case iostreams::newline::dos:
            if (flags_ & f_has_LF) {
                flags_ &= ~f_has_LF;
                return LF;
            } else {
                flags_ |= f_has_LF;
                return CR;
            }
        }
        return BOOST_IOSTREAMS_ASSERT_UNREACHABLE(0);
    }

    // Writes a newline sequence.
    template<typename Sink>
    bool newline(Sink& dest)
    {
        using iostreams::newline::CR;
        using iostreams::newline::LF;

        bool success = false;
        switch (flags_ & iostreams::newline::platform_mask) {
        case iostreams::newline::posix:
            success = boost::iostreams::put(dest, LF);
            break;
        case iostreams::newline::mac:
            success = boost::iostreams::put(dest, CR);
            break;
        case iostreams::newline::dos:
            if ((flags_ & f_has_LF) != 0) {
                if ((success = boost::iostreams::put(dest, LF)))
                    flags_ &= ~f_has_LF;
            } else if (boost::iostreams::put(dest, CR)) {
                if (!(success = boost::iostreams::put(dest, LF)))
                    flags_ |= f_has_LF;
            }
            break;
        }
        if (success)
            flags_ &= ~f_has_CR;
        return success;
    }

    // Writes a newline sequence if the given device is a Sink.
    template<typename Device>
    void newline_if_sink(Device& dest) 
    { 
        typedef typename iostreams::category_of<Device>::type category;
        newline_if_sink(dest, is_convertible<category, output>()); 
    }

    template<typename Sink>
    void newline_if_sink(Sink& dest, mpl::true_) { newline(dest); }

    template<typename Source>
    void newline_if_sink(Source&, mpl::false_) { }

    enum flags {
        f_has_LF         = 32768,
        f_has_CR         = f_has_LF << 1,
        f_has_newline    = f_has_CR << 1,
        f_has_EOF        = f_has_newline << 1,
        f_read           = f_has_EOF << 1,
        f_write          = f_read << 1
    };
    int       flags_;
};
BOOST_IOSTREAMS_PIPABLE(newline_filter, 0)

class newline_checker : public detail::newline_base {
public:
    typedef char                 char_type;
    struct category
        : dual_use_filter_tag,
          closable_tag
        { };
    explicit newline_checker(int target = newline::mixed)
        : detail::newline_base(0), target_(target), open_(false)
        { }
    template<typename Source>
    int get(Source& src)
    {
        using newline::CR;
        using newline::LF;

        if (!open_) {
            open_ = true;
            source() = 0;
        }

        int c;
        if ((c = iostreams::get(src)) == WOULD_BLOCK)
            return WOULD_BLOCK;

        // Update source flags.
        if (c != EOF)
            source() &= ~f_line_complete;
        if ((source() & f_has_CR) != 0) {
            if (c == LF) {
                source() |= newline::dos;
                source() |= f_line_complete;
            } else {
                source() |= newline::mac;
                if (c == EOF)
                    source() |= f_line_complete;
            }
        } else if (c == LF) {
            source() |= newline::posix;
            source() |= f_line_complete;
        }
        source() = (source() & ~f_has_CR) | (c == CR ? f_has_CR : 0);

        // Check for errors.
        if ( c == EOF &&
            (target_ & newline::final_newline) != 0 &&
            (source() & f_line_complete) == 0 )
        {
            fail();
        }
        if ( (target_ & newline::platform_mask) != 0 &&
             (source() & ~target_ & newline::platform_mask) != 0 )
        {
            fail();
        }

        return c;
    }

    template<typename Sink>
    bool put(Sink& dest, int c)
    {
        using iostreams::newline::CR;
        using iostreams::newline::LF;

        if (!open_) {
            open_ = true;
            source() = 0;
        }

        if (!iostreams::put(dest, c))
            return false;

         // Update source flags.
        source() &= ~f_line_complete;
        if ((source() & f_has_CR) != 0) {
            if (c == LF) {
                source() |= newline::dos;
                source() |= f_line_complete;
            } else {
                source() |= newline::mac;
            }
        } else if (c == LF) {
            source() |= newline::posix;
            source() |= f_line_complete;
        }
        source() = (source() & ~f_has_CR) | (c == CR ? f_has_CR : 0);

        // Check for errors.
        if ( (target_ & newline::platform_mask) != 0 &&
             (source() & ~target_ & newline::platform_mask) != 0 )
        {
            fail();
        }

        return true;
    }

    template<typename Sink>
    void close(Sink&, BOOST_IOS::openmode)
    {
        using iostreams::newline::final_newline;

        // Update final_newline flag.
        if ( (source() & f_has_CR) != 0 ||
             (source() & f_line_complete) != 0 )
        {
            source() |= final_newline;
        }

        // Clear non-sticky flags.
        source() &= ~(f_has_CR | f_line_complete);

        // Check for errors.
        if ( (target_ & final_newline) != 0 &&
             (source() & final_newline) == 0 )
        {
            fail();
        }
    }
private:
    void fail() { boost::throw_exception(newline_error(source())); }
    int& source() { return flags_; }
    int source() const { return flags_; }

    enum flags {
        f_has_CR = 32768,
        f_line_complete = f_has_CR << 1
    };

    int   target_;  // Represents expected input.
    bool  open_;
};
BOOST_IOSTREAMS_PIPABLE(newline_checker, 0)

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #ifndef BOOST_IOSTREAMS_NEWLINE_FILTER_HPP_INCLUDED

/* newline.hpp
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
*/