// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Contains the definitions of the class templates symmetric_filter,
// which models DualUseFilter based on a model of the Symmetric Filter.

//
// Roughly, a Symmetric Filter is a class type with the following interface:
//
//   struct symmetric_filter {
//       typedef xxx char_type;
//
//       bool filter( const char*& begin_in, const char* end_in,
//                    char*& begin_out, char* end_out, bool flush )
//       {
//          // Consume as many characters as possible from the interval
//          // [begin_in, end_in), without exhausting the output range
//          // [begin_out, end_out). If flush is true, write as mush output
//          // as possible. 
//          // A return value of true indicates that filter should be called 
//          // again. More precisely, if flush is false, a return value of 
//          // false indicates that the natural end of stream has been reached
//          // and that all filtered data has been forwarded; if flush is
//          // true, a return value of false indicates that all filtered data 
//          // has been forwarded.
//       }
//       void close() { /* Reset filter's state. */ }
//   };
//
// Symmetric Filter filters need not be CopyConstructable.
//

#ifndef BOOST_IOSTREAMS_SYMMETRIC_FILTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_SYMMETRIC_FILTER_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assert.hpp>
#include <memory>                               // allocator.
#include <boost/config.hpp>                     // BOOST_DEDUCED_TYPENAME.
#include <boost/iostreams/char_traits.hpp>
#include <boost/iostreams/constants.hpp>        // buffer size.
#include <boost/iostreams/detail/buffer.hpp>
#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/config/limits.hpp>
#include <boost/iostreams/detail/ios.hpp>  // streamsize.
#include <boost/iostreams/detail/template_params.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/iostreams/operations.hpp>       // read, write.
#include <boost/iostreams/pipeline.hpp>
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/shared_ptr.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>  // MSVC.

namespace boost { namespace iostreams {

template< typename SymmetricFilter,
          typename Alloc =
              std::allocator<
                  BOOST_DEDUCED_TYPENAME char_type_of<SymmetricFilter>::type
              > >
class symmetric_filter {
public:
    typedef typename char_type_of<SymmetricFilter>::type      char_type;
    typedef BOOST_IOSTREAMS_CHAR_TRAITS(char_type)            traits_type;
    typedef std::basic_string<char_type, traits_type, Alloc>  string_type;
    struct category
        : dual_use,
          filter_tag,
          multichar_tag,
          closable_tag
        { };

    // Expands to a sequence of ctors which forward to impl.
    #define BOOST_PP_LOCAL_MACRO(n) \
        BOOST_IOSTREAMS_TEMPLATE_PARAMS(n, T) \
        explicit symmetric_filter( \
              std::streamsize buffer_size BOOST_PP_COMMA_IF(n) \
              BOOST_PP_ENUM_BINARY_PARAMS(n, const T, &t) ) \
            : pimpl_(new impl(buffer_size BOOST_PP_COMMA_IF(n) \
                     BOOST_PP_ENUM_PARAMS(n, t))) \
            { BOOST_ASSERT(buffer_size > 0); } \
        /**/
    #define BOOST_PP_LOCAL_LIMITS (0, BOOST_IOSTREAMS_MAX_FORWARDING_ARITY)
    #include BOOST_PP_LOCAL_ITERATE()
    #undef BOOST_PP_LOCAL_MACRO

    template<typename Source>
    std::streamsize read(Source& src, char_type* s, std::streamsize n)
    {
        using namespace std;
        if (!(state() & f_read))
            begin_read();

        buffer_type&  buf = pimpl_->buf_;
        int           status = (state() & f_eof) != 0 ? f_eof : f_good;
        char_type    *next_s = s,
                     *end_s = s + n;
        while (true)
        {
            // Invoke filter if there are unconsumed characters in buffer or if
            // filter must be flushed.
            bool flush = status == f_eof;
            if (buf.ptr() != buf.eptr() || flush) {
                const char_type* next = buf.ptr();
                bool done =
                    !filter().filter(next, buf.eptr(), next_s, end_s, flush);
                buf.ptr() = buf.data() + (next - buf.data());
                if (done)
                    return detail::check_eof(
                               static_cast<std::streamsize>(next_s - s)
                           );
            }

            // If no more characters are available without blocking, or
            // if read request has been satisfied, return.
            if ( (status == f_would_block && buf.ptr() == buf.eptr()) ||
                 next_s == end_s )
            {
                return static_cast<std::streamsize>(next_s - s);
            }

            // Fill buffer.
            if (status == f_good)
                status = fill(src);
        }
    }

    template<typename Sink>
    std::streamsize write(Sink& snk, const char_type* s, std::streamsize n)
    {
        if (!(state() & f_write))
            begin_write();

        buffer_type&     buf = pimpl_->buf_;
        const char_type *next_s, *end_s;
        for (next_s = s, end_s = s + n; next_s != end_s; ) {
            if (buf.ptr() == buf.eptr() && !flush(snk))
                break;
            if(!filter().filter(next_s, end_s, buf.ptr(), buf.eptr(), false)) {
                flush(snk);
                break;
            }
        }
        return static_cast<std::streamsize>(next_s - s);
    }

    template<typename Sink>
    void close(Sink& snk, BOOST_IOS::openmode mode)
    {
        if (mode == BOOST_IOS::out) {

            if (!(state() & f_write))
                begin_write();

            // Repeatedly invoke filter() with no input.
            try {
                buffer_type&     buf = pimpl_->buf_;
                char_type        dummy;
                const char_type* end = &dummy;
                bool             again = true;
                while (again) {
                    if (buf.ptr() != buf.eptr())
                        again = filter().filter( end, end, buf.ptr(),
                                                 buf.eptr(), true );
                    flush(snk);
                }
            } catch (...) {
                try { close_impl(); } catch (...) { }
                throw;
            }
            close_impl();
        } else {
            close_impl();
        }
    }
    SymmetricFilter& filter() { return *pimpl_; }
    string_type unconsumed_input() const;

// Give impl access to buffer_type on Tru64
#if !BOOST_WORKAROUND(__DECCXX_VER, BOOST_TESTED_AT(60590042)) 
    private:
#endif
    typedef detail::buffer<char_type, Alloc> buffer_type;
private:
    buffer_type& buf() { return pimpl_->buf_; }
    const buffer_type& buf() const { return pimpl_->buf_; }
    int& state() { return pimpl_->state_; }
    void begin_read();
    void begin_write();

    template<typename Source>
    int fill(Source& src)
    {
        std::streamsize amt = iostreams::read(src, buf().data(), buf().size());
        if (amt == -1) {
            state() |= f_eof;
            return f_eof;
        }
        buf().set(0, amt);
        return amt != 0 ? f_good : f_would_block;
    }

    // Attempts to write the contents of the buffer the given Sink.
    // Returns true if at least on character was written.
    template<typename Sink>
    bool flush(Sink& snk)
    {
        typedef typename iostreams::category_of<Sink>::type  category;
        typedef is_convertible<category, output>             can_write;
        return flush(snk, can_write());
    }

    template<typename Sink>
    bool flush(Sink& snk, mpl::true_)
    {
        std::streamsize amt =
            static_cast<std::streamsize>(buf().ptr() - buf().data());
        std::streamsize result =
            boost::iostreams::write(snk, buf().data(), amt);
        if (result < amt && result > 0)
            traits_type::move(buf().data(), buf().data() + result, amt - result);
        buf().set(amt - result, buf().size());
        return result != 0;
    }

    template<typename Sink>
    bool flush(Sink&, mpl::false_) { return true;}

    void close_impl();

    enum flag_type {
        f_read   = 1,
        f_write  = f_read << 1,
        f_eof    = f_write << 1,
        f_good,
        f_would_block
    };

    struct impl : SymmetricFilter {

    // Expands to a sequence of ctors which forward to SymmetricFilter.
    #define BOOST_PP_LOCAL_MACRO(n) \
        BOOST_IOSTREAMS_TEMPLATE_PARAMS(n, T) \
        impl( std::streamsize buffer_size BOOST_PP_COMMA_IF(n) \
              BOOST_PP_ENUM_BINARY_PARAMS(n, const T, &t) ) \
            : SymmetricFilter(BOOST_PP_ENUM_PARAMS(n, t)), \
              buf_(buffer_size), state_(0) \
            { } \
        /**/
    #define BOOST_PP_LOCAL_LIMITS (0, BOOST_IOSTREAMS_MAX_FORWARDING_ARITY)
    #include BOOST_PP_LOCAL_ITERATE()
    #undef BOOST_PP_LOCAL_MACRO

        buffer_type  buf_;
        int          state_;
    };

    shared_ptr<impl> pimpl_;
};
BOOST_IOSTREAMS_PIPABLE(symmetric_filter, 2)

//------------------Implementation of symmetric_filter----------------//

template<typename SymmetricFilter, typename Alloc>
void symmetric_filter<SymmetricFilter, Alloc>::begin_read()
{
    BOOST_ASSERT(!(state() & f_write));
    state() |= f_read;
    buf().set(0, 0);
}

template<typename SymmetricFilter, typename Alloc>
void symmetric_filter<SymmetricFilter, Alloc>::begin_write()
{
    BOOST_ASSERT(!(state() & f_read));
    state() |= f_write;
    buf().set(0, buf().size());
}

template<typename SymmetricFilter, typename Alloc>
void symmetric_filter<SymmetricFilter, Alloc>::close_impl()
{
    state() = 0;
    buf().set(0, 0);
    filter().close();
}

template<typename SymmetricFilter, typename Alloc>
typename symmetric_filter<SymmetricFilter, Alloc>::string_type
symmetric_filter<SymmetricFilter, Alloc>::unconsumed_input() const
{ return string_type(buf().ptr(), buf().eptr()); }

//----------------------------------------------------------------------------//

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>  // MSVC.

#endif // #ifndef BOOST_IOSTREAMS_SYMMETRIC_FILTER_HPP_INCLUDED

/* symmetric.hpp
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
*/