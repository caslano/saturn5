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