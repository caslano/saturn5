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