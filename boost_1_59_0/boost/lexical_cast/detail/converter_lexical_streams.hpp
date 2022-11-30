// Copyright Kevlin Henney, 2000-2005.
// Copyright Alexander Nasonov, 2006-2010.
// Copyright Antony Polukhin, 2011-2022.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// what:  lexical_cast custom keyword cast
// who:   contributed by Kevlin Henney,
//        enhanced with contributions from Terje Slettebo,
//        with additional fixes and suggestions from Gennaro Prota,
//        Beman Dawes, Dave Abrahams, Daryle Walker, Peter Dimov,
//        Alexander Nasonov, Antony Polukhin, Justin Viiret, Michael Hofmann,
//        Cheng Yang, Matthew Bradbury, David W. Birdsall, Pavel Korzh and other Boosters
// when:  November 2000, March 2003, June 2005, June 2006, March 2011 - 2014, Nowember 2016

#ifndef BOOST_LEXICAL_CAST_DETAIL_CONVERTER_LEXICAL_STREAMS_HPP
#define BOOST_LEXICAL_CAST_DETAIL_CONVERTER_LEXICAL_STREAMS_HPP

#include <boost/config.hpp>
#ifdef BOOST_HAS_PRAGMA_ONCE
#   pragma once
#endif


#if defined(BOOST_NO_STRINGSTREAM) || defined(BOOST_NO_STD_WSTRING)
#define BOOST_LCAST_NO_WCHAR_T
#endif

#include <cstddef>
#include <string>
#include <cstring>
#include <cstdio>
#include <boost/limits.hpp>
#include <boost/type_traits/conditional.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/static_assert.hpp>
#include <boost/detail/lcast_precision.hpp>
#include <boost/detail/workaround.hpp>

#ifndef BOOST_NO_STD_LOCALE
#   include <locale>
#else
#   ifndef BOOST_LEXICAL_CAST_ASSUME_C_LOCALE
        // Getting error at this point means, that your STL library is old/lame/misconfigured.
        // If nothing can be done with STL library, define BOOST_LEXICAL_CAST_ASSUME_C_LOCALE,
        // but beware: lexical_cast will understand only 'C' locale delimeters and thousands
        // separators.
#       error "Unable to use <locale> header. Define BOOST_LEXICAL_CAST_ASSUME_C_LOCALE to force "
#       error "boost::lexical_cast to use only 'C' locale during conversions."
#   endif
#endif

#ifdef BOOST_NO_STRINGSTREAM
#include <strstream>
#else
#include <sstream>
#endif

#include <boost/lexical_cast/detail/lcast_char_constants.hpp>
#include <boost/lexical_cast/detail/lcast_unsigned_converters.hpp>
#include <boost/lexical_cast/detail/inf_nan.hpp>

#include <istream>

#ifndef BOOST_NO_CXX11_HDR_ARRAY
#include <array>
#endif

#include <boost/array.hpp>
#include <boost/type_traits/make_unsigned.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_float.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <boost/container/container_fwd.hpp>
#include <boost/integer.hpp>
#include <boost/detail/basic_pointerbuf.hpp>
#include <boost/noncopyable.hpp>
#ifndef BOOST_NO_CWCHAR
#   include <cwchar>
#endif

namespace boost {

    namespace detail // basic_unlockedbuf
    {
        // acts as a stream buffer which wraps around a pair of pointers
        // and gives acces to internals
        template <class BufferType, class CharT>
        class basic_unlockedbuf : public basic_pointerbuf<CharT, BufferType> {
        public:
           typedef basic_pointerbuf<CharT, BufferType> base_type;
           typedef BOOST_DEDUCED_TYPENAME base_type::streamsize streamsize;

#ifndef BOOST_NO_USING_TEMPLATE
            using base_type::pptr;
            using base_type::pbase;
            using base_type::setbuf;
#else
            charT* pptr() const { return base_type::pptr(); }
            charT* pbase() const { return base_type::pbase(); }
            BufferType* setbuf(char_type* s, streamsize n) { return base_type::setbuf(s, n); }
#endif
        };
    }

    namespace detail
    {
        struct do_not_construct_out_buffer_t{};
        struct do_not_construct_out_stream_t{
            do_not_construct_out_stream_t(do_not_construct_out_buffer_t*){}
        };

        template <class CharT, class Traits>
        struct out_stream_helper_trait {
#if defined(BOOST_NO_STRINGSTREAM)
            typedef std::ostream                                                    out_stream_t;
            typedef basic_unlockedbuf<std::strstreambuf, char>                      stringbuffer_t;
#elif defined(BOOST_NO_STD_LOCALE)
            typedef std::ostream                                                    out_stream_t;
            typedef basic_unlockedbuf<std::stringbuf, char>                         stringbuffer_t;
            typedef basic_unlockedbuf<std::streambuf, char>                         buffer_t;
#else
            typedef std::basic_ostream<CharT, Traits>                               out_stream_t;
            typedef basic_unlockedbuf<std::basic_stringbuf<CharT, Traits>, CharT>   stringbuffer_t;
            typedef basic_unlockedbuf<std::basic_streambuf<CharT, Traits>, CharT>   buffer_t;
#endif
        };
    }

    namespace detail // optimized stream wrappers
    {
        template< class CharT // a result of widest_char transformation
                , class Traits
                , bool RequiresStringbuffer
                , std::size_t CharacterBufferSize
                >
        class lexical_istream_limited_src: boost::noncopyable {
            typedef BOOST_DEDUCED_TYPENAME boost::conditional<
                RequiresStringbuffer,
                BOOST_DEDUCED_TYPENAME out_stream_helper_trait<CharT, Traits>::out_stream_t,
                do_not_construct_out_stream_t
            >::type deduced_out_stream_t;

            typedef BOOST_DEDUCED_TYPENAME boost::conditional<
                RequiresStringbuffer,
                BOOST_DEDUCED_TYPENAME out_stream_helper_trait<CharT, Traits>::stringbuffer_t,
                do_not_construct_out_buffer_t
            >::type deduced_out_buffer_t;

            deduced_out_buffer_t out_buffer;
            deduced_out_stream_t out_stream;
            CharT   buffer[CharacterBufferSize];

            // After the `operator <<`  finishes, `[start, finish)` is
            // the range to output by `operator >>`
            const CharT*  start;
            const CharT*  finish;

        public:
            lexical_istream_limited_src() BOOST_NOEXCEPT
              : out_buffer()
              , out_stream(&out_buffer)
              , start(buffer)
              , finish(buffer + CharacterBufferSize)
            {}

            const CharT* cbegin() const BOOST_NOEXCEPT {
                return start;
            }

            const CharT* cend() const BOOST_NOEXCEPT {
                return finish;
            }

        private:
/************************************ HELPER FUNCTIONS FOR OPERATORS << ( ... ) ********************************/
            bool shl_char(CharT ch) BOOST_NOEXCEPT {
                Traits::assign(buffer[0], ch);
                finish = start + 1;
                return true;
            }

#ifndef BOOST_LCAST_NO_WCHAR_T
            template <class T>
            bool shl_char(T ch) {
                BOOST_STATIC_ASSERT_MSG(( sizeof(T) <= sizeof(CharT)) ,
                    "boost::lexical_cast does not support narrowing of char types."
                    "Use boost::locale instead" );
#ifndef BOOST_LEXICAL_CAST_ASSUME_C_LOCALE
                std::locale loc;
                CharT const w = BOOST_USE_FACET(std::ctype<CharT>, loc).widen(ch);
#else
                CharT const w = static_cast<CharT>(ch);
#endif
                Traits::assign(buffer[0], w);
                finish = start + 1;
                return true;
            }
#endif

            bool shl_char_array(CharT const* str_value) BOOST_NOEXCEPT {
                start = str_value;
                finish = start + Traits::length(str_value);
                return true;
            }

            template <class T>
            bool shl_char_array(T const* str_value) {
                BOOST_STATIC_ASSERT_MSG(( sizeof(T) <= sizeof(CharT)),
                    "boost::lexical_cast does not support narrowing of char types."
                    "Use boost::locale instead" );
                return shl_input_streamable(str_value);
            }

            bool shl_char_array_limited(CharT const* str, std::size_t max_size) BOOST_NOEXCEPT {
                start = str;
                finish = std::find(start, start + max_size, Traits::to_char_type(0));
                return true;
            }

            template<typename InputStreamable>
            bool shl_input_streamable(InputStreamable& input) {
#if defined(BOOST_NO_STRINGSTREAM) || defined(BOOST_NO_STD_LOCALE)
                // If you have compilation error at this point, than your STL library
                // does not support such conversions. Try updating it.
                BOOST_STATIC_ASSERT((boost::is_same<char, CharT>::value));
#endif

#ifndef BOOST_NO_EXCEPTIONS
                out_stream.exceptions(std::ios::badbit);
                try {
#endif
                bool const result = !(out_stream << input).fail();
                const deduced_out_buffer_t* const p = static_cast<deduced_out_buffer_t*>(
                    out_stream.rdbuf()
                );
                start = p->pbase();
                finish = p->pptr();
                return result;
#ifndef BOOST_NO_EXCEPTIONS
                } catch (const ::std::ios_base::failure& /*f*/) {
                    return false;
                }
#endif
            }

            template <class T>
            inline bool shl_unsigned(const T n) {
                CharT* tmp_finish = buffer + CharacterBufferSize;
                start = lcast_put_unsigned<Traits, T, CharT>(n, tmp_finish).convert();
                finish = tmp_finish;
                return true;
            }

            template <class T>
            inline bool shl_signed(const T n) {
                CharT* tmp_finish = buffer + CharacterBufferSize;
                typedef BOOST_DEDUCED_TYPENAME boost::make_unsigned<T>::type utype;
                CharT* tmp_start = lcast_put_unsigned<Traits, utype, CharT>(lcast_to_unsigned(n), tmp_finish).convert();
                if (n < 0) {
                    --tmp_start;
                    CharT const minus = lcast_char_constants<CharT>::minus;
                    Traits::assign(*tmp_start, minus);
                }
                start = tmp_start;
                finish = tmp_finish;
                return true;
            }

            template <class T, class SomeCharT>
            bool shl_real_type(const T& val, SomeCharT* /*begin*/) {
                lcast_set_precision(out_stream, &val);
                return shl_input_streamable(val);
            }

            bool shl_real_type(float val, char* begin) {
                using namespace std;
                const double val_as_double = val;
                finish = start +
#if defined(_MSC_VER) && (_MSC_VER >= 1400) && !defined(__SGI_STL_PORT) && !defined(_STLPORT_VERSION)
                    sprintf_s(begin, CharacterBufferSize,
#else
                    sprintf(begin,
#endif
                    "%.*g", static_cast<int>(boost::detail::lcast_get_precision<float>()), val_as_double);
                return finish > start;
            }

            bool shl_real_type(double val, char* begin) {
                using namespace std;
                finish = start +
#if defined(_MSC_VER) && (_MSC_VER >= 1400) && !defined(__SGI_STL_PORT) && !defined(_STLPORT_VERSION)
                    sprintf_s(begin, CharacterBufferSize,
#else
                    sprintf(begin,
#endif
                    "%.*g", static_cast<int>(boost::detail::lcast_get_precision<double>()), val);
                return finish > start;
            }

#ifndef __MINGW32__
            bool shl_real_type(long double val, char* begin) {
                using namespace std;
                finish = start +
#if defined(_MSC_VER) && (_MSC_VER >= 1400) && !defined(__SGI_STL_PORT) && !defined(_STLPORT_VERSION)
                    sprintf_s(begin, CharacterBufferSize,
#else
                    sprintf(begin,
#endif
                    "%.*Lg", static_cast<int>(boost::detail::lcast_get_precision<long double>()), val );
                return finish > start;
            }
#endif


#if !defined(BOOST_LCAST_NO_WCHAR_T) && !defined(BOOST_NO_SWPRINTF) && !defined(__MINGW32__)
            bool shl_real_type(float val, wchar_t* begin) {
                using namespace std;
                const double val_as_double = val;
                finish = start + swprintf(begin, CharacterBufferSize,
                                       L"%.*g",
                                       static_cast<int>(boost::detail::lcast_get_precision<float >()),
                                       val_as_double );
                return finish > start;
            }

            bool shl_real_type(double val, wchar_t* begin) {
                using namespace std;
                finish = start + swprintf(begin, CharacterBufferSize,
                                          L"%.*g", static_cast<int>(boost::detail::lcast_get_precision<double >()), val );
                return finish > start;
            }

            bool shl_real_type(long double val, wchar_t* begin) {
                using namespace std;
                finish = start + swprintf(begin, CharacterBufferSize,
                                          L"%.*Lg", static_cast<int>(boost::detail::lcast_get_precision<long double >()), val );
                return finish > start;
            }
#endif
            template <class T>
            bool shl_real(T val) {
                CharT* tmp_finish = buffer + CharacterBufferSize;
                if (put_inf_nan(buffer, tmp_finish, val)) {
                    finish = tmp_finish;
                    return true;
                }

                return shl_real_type(val, static_cast<CharT*>(buffer));
            }

/************************************ OPERATORS << ( ... ) ********************************/
        public:
            template<class Alloc>
            bool operator<<(std::basic_string<CharT,Traits,Alloc> const& str) BOOST_NOEXCEPT {
                start = str.data();
                finish = start + str.length();
                return true;
            }

            template<class Alloc>
            bool operator<<(boost::container::basic_string<CharT,Traits,Alloc> const& str) BOOST_NOEXCEPT {
                start = str.data();
                finish = start + str.length();
                return true;
            }

            bool operator<<(bool value) BOOST_NOEXCEPT {
                CharT const czero = lcast_char_constants<CharT>::zero;
                Traits::assign(buffer[0], Traits::to_char_type(czero + value));
                finish = start + 1;
                return true;
            }

            template <class C>
            BOOST_DEDUCED_TYPENAME boost::disable_if<boost::is_const<C>, bool>::type
            operator<<(const iterator_range<C*>& rng) BOOST_NOEXCEPT {
                return (*this) << iterator_range<const C*>(rng.begin(), rng.end());
            }

            bool operator<<(const iterator_range<const CharT*>& rng) BOOST_NOEXCEPT {
                start = rng.begin();
                finish = rng.end();
                return true;
            }

            bool operator<<(const iterator_range<const signed char*>& rng) BOOST_NOEXCEPT {
                return (*this) << iterator_range<const char*>(
                    reinterpret_cast<const char*>(rng.begin()),
                    reinterpret_cast<const char*>(rng.end())
                );
            }

            bool operator<<(const iterator_range<const unsigned char*>& rng) BOOST_NOEXCEPT {
                return (*this) << iterator_range<const char*>(
                    reinterpret_cast<const char*>(rng.begin()),
                    reinterpret_cast<const char*>(rng.end())
                );
            }

            bool operator<<(char ch)                    { return shl_char(ch); }
            bool operator<<(unsigned char ch)           { return ((*this) << static_cast<char>(ch)); }
            bool operator<<(signed char ch)             { return ((*this) << static_cast<char>(ch)); }
#if !defined(BOOST_LCAST_NO_WCHAR_T)
            bool operator<<(wchar_t const* str)         { return shl_char_array(str); }
            bool operator<<(wchar_t * str)              { return shl_char_array(str); }
#ifndef BOOST_NO_INTRINSIC_WCHAR_T
            bool operator<<(wchar_t ch)                 { return shl_char(ch); }
#endif
#endif
#if !defined(BOOST_NO_CXX11_CHAR16_T) && !defined(BOOST_NO_CXX11_UNICODE_LITERALS)
            bool operator<<(char16_t ch)                { return shl_char(ch); }
            bool operator<<(char16_t * str)             { return shl_char_array(str); }
            bool operator<<(char16_t const * str)       { return shl_char_array(str); }
#endif
#if !defined(BOOST_NO_CXX11_CHAR32_T) && !defined(BOOST_NO_CXX11_UNICODE_LITERALS)
            bool operator<<(char32_t ch)                { return shl_char(ch); }
            bool operator<<(char32_t * str)             { return shl_char_array(str); }
            bool operator<<(char32_t const * str)       { return shl_char_array(str); }
#endif
            bool operator<<(unsigned char const* ch)    { return ((*this) << reinterpret_cast<char const*>(ch)); }
            bool operator<<(unsigned char * ch)         { return ((*this) << reinterpret_cast<char *>(ch)); }
            bool operator<<(signed char const* ch)      { return ((*this) << reinterpret_cast<char const*>(ch)); }
            bool operator<<(signed char * ch)           { return ((*this) << reinterpret_cast<char *>(ch)); }
            bool operator<<(char const* str_value)      { return shl_char_array(str_value); }
            bool operator<<(char* str_value)            { return shl_char_array(str_value); }
            bool operator<<(short n)                    { return shl_signed(n); }
            bool operator<<(int n)                      { return shl_signed(n); }
            bool operator<<(long n)                     { return shl_signed(n); }
            bool operator<<(unsigned short n)           { return shl_unsigned(n); }
            bool operator<<(unsigned int n)             { return shl_unsigned(n); }
            bool operator<<(unsigned long n)            { return shl_unsigned(n); }

#if defined(BOOST_HAS_LONG_LONG)
            bool operator<<(boost::ulong_long_type n)   { return shl_unsigned(n); }
            bool operator<<(boost::long_long_type n)    { return shl_signed(n); }
#elif defined(BOOST_HAS_MS_INT64)
            bool operator<<(unsigned __int64 n)         { return shl_unsigned(n); }
            bool operator<<(         __int64 n)         { return shl_signed(n); }
#endif

#ifdef BOOST_HAS_INT128
            bool operator<<(const boost::uint128_type& n)   { return shl_unsigned(n); }
            bool operator<<(const boost::int128_type& n)    { return shl_signed(n); }
#endif
            bool operator<<(float val)                  { return shl_real(val); }
            bool operator<<(double val)                 { return shl_real(val); }
            bool operator<<(long double val)            {
#ifndef __MINGW32__
                return shl_real(val);
#else
                return shl_real(static_cast<double>(val));
#endif
            }

            // Adding constness to characters. Constness does not change layout
            template <class C, std::size_t N>
            BOOST_DEDUCED_TYPENAME boost::disable_if<boost::is_const<C>, bool>::type
            operator<<(boost::array<C, N> const& input) BOOST_NOEXCEPT {
                BOOST_STATIC_ASSERT_MSG(
                    (sizeof(boost::array<const C, N>) == sizeof(boost::array<C, N>)),
                    "boost::array<C, N> and boost::array<const C, N> must have exactly the same layout."
                );
                return ((*this) << reinterpret_cast<boost::array<const C, N> const& >(input));
            }

            template <std::size_t N>
            bool operator<<(boost::array<const CharT, N> const& input) BOOST_NOEXCEPT {
                return shl_char_array_limited(input.data(), N);
            }

            template <std::size_t N>
            bool operator<<(boost::array<const unsigned char, N> const& input) BOOST_NOEXCEPT {
                return ((*this) << reinterpret_cast<boost::array<const char, N> const& >(input));
            }

            template <std::size_t N>
            bool operator<<(boost::array<const signed char, N> const& input) BOOST_NOEXCEPT {
                return ((*this) << reinterpret_cast<boost::array<const char, N> const& >(input));
            }

#ifndef BOOST_NO_CXX11_HDR_ARRAY
            // Making a Boost.Array from std::array
            template <class C, std::size_t N>
            bool operator<<(std::array<C, N> const& input) BOOST_NOEXCEPT {
                BOOST_STATIC_ASSERT_MSG(
                    (sizeof(std::array<C, N>) == sizeof(boost::array<C, N>)),
                    "std::array and boost::array must have exactly the same layout. "
                    "Bug in implementation of std::array or boost::array."
                );
                return ((*this) << reinterpret_cast<boost::array<C, N> const& >(input));
            }
#endif
            template <class InStreamable>
            bool operator<<(const InStreamable& input)  { return shl_input_streamable(input); }
        };


        template <class CharT, class Traits>
        class lexical_ostream_limited_src: boost::noncopyable {
            //`[start, finish)` is the range to output by `operator >>`
            const CharT*        start;
            const CharT* const  finish;

        public:
            lexical_ostream_limited_src(const CharT* begin, const CharT* end) BOOST_NOEXCEPT
              : start(begin)
              , finish(end)
            {}

/************************************ HELPER FUNCTIONS FOR OPERATORS >> ( ... ) ********************************/
        private:
            template <typename Type>
            bool shr_unsigned(Type& output) {
                if (start == finish) return false;
                CharT const minus = lcast_char_constants<CharT>::minus;
                CharT const plus = lcast_char_constants<CharT>::plus;
                bool const has_minus = Traits::eq(minus, *start);

                /* We won`t use `start' any more, so no need in decrementing it after */
                if (has_minus || Traits::eq(plus, *start)) {
                    ++start;
                }

                bool const succeed = lcast_ret_unsigned<Traits, Type, CharT>(output, start, finish).convert();

                if (has_minus) {
                    output = static_cast<Type>(0u - output);
                }

                return succeed;
            }

            template <typename Type>
            bool shr_signed(Type& output) {
                if (start == finish) return false;
                CharT const minus = lcast_char_constants<CharT>::minus;
                CharT const plus = lcast_char_constants<CharT>::plus;
                typedef BOOST_DEDUCED_TYPENAME make_unsigned<Type>::type utype;
                utype out_tmp = 0;
                bool const has_minus = Traits::eq(minus, *start);

                /* We won`t use `start' any more, so no need in decrementing it after */
                if (has_minus || Traits::eq(plus, *start)) {
                    ++start;
                }

                bool succeed = lcast_ret_unsigned<Traits, utype, CharT>(out_tmp, start, finish).convert();
                if (has_minus) {
                    utype const comp_val = (static_cast<utype>(1) << std::numeric_limits<Type>::digits);
                    succeed = succeed && out_tmp<=comp_val;
                    output = static_cast<Type>(0u - out_tmp);
                } else {
                    utype const comp_val = static_cast<utype>((std::numeric_limits<Type>::max)());
                    succeed = succeed && out_tmp<=comp_val;
                    output = static_cast<Type>(out_tmp);
                }
                return succeed;
            }

            template<typename InputStreamable>
            bool shr_using_base_class(InputStreamable& output)
            {
                BOOST_STATIC_ASSERT_MSG(
                    (!boost::is_pointer<InputStreamable>::value),
                    "boost::lexical_cast can not convert to pointers"
                );

#if defined(BOOST_NO_STRINGSTREAM) || defined(BOOST_NO_STD_LOCALE)
                BOOST_STATIC_ASSERT_MSG((boost::is_same<char, CharT>::value),
                    "boost::lexical_cast can not convert, because your STL library does not "
                    "support such conversions. Try updating it."
                );
#endif

#if defined(BOOST_NO_STRINGSTREAM)
                std::istrstream stream(start, static_cast<std::istrstream::streamsize>(finish - start));
#else
                typedef BOOST_DEDUCED_TYPENAME out_stream_helper_trait<CharT, Traits>::buffer_t buffer_t;
                buffer_t buf;
                // Usually `istream` and `basic_istream` do not modify
                // content of buffer; `buffer_t` assures that this is true
                buf.setbuf(const_cast<CharT*>(start), static_cast<typename buffer_t::streamsize>(finish - start));
#if defined(BOOST_NO_STD_LOCALE)
                std::istream stream(&buf);
#else
                std::basic_istream<CharT, Traits> stream(&buf);
#endif // BOOST_NO_STD_LOCALE
#endif // BOOST_NO_STRINGSTREAM

#ifndef BOOST_NO_EXCEPTIONS
                stream.exceptions(std::ios::badbit);
                try {
#endif
                stream.unsetf(std::ios::skipws);
                lcast_set_precision(stream, static_cast<InputStreamable*>(0));

                return (stream >> output)
                    && (stream.get() == Traits::eof());

#ifndef BOOST_NO_EXCEPTIONS
                } catch (const ::std::ios_base::failure& /*f*/) {
                    return false;
                }
#endif
            }

            template<class T>
            inline bool shr_xchar(T& output) BOOST_NOEXCEPT {
                BOOST_STATIC_ASSERT_MSG(( sizeof(CharT) == sizeof(T) ),
                    "boost::lexical_cast does not support narrowing of character types."
                    "Use boost::locale instead" );
                bool const ok = (finish - start == 1);
                if (ok) {
                    CharT out;
                    Traits::assign(out, *start);
                    output = static_cast<T>(out);
                }
                return ok;
            }

            template <std::size_t N, class ArrayT>
            bool shr_std_array(ArrayT& output) BOOST_NOEXCEPT {
                using namespace std;
                const std::size_t size = static_cast<std::size_t>(finish - start);
                if (size > N - 1) { // `-1` because we need to store \0 at the end
                    return false;
                }

                memcpy(&output[0], start, size * sizeof(CharT));
                output[size] = Traits::to_char_type(0);
                return true;
            }

/************************************ OPERATORS >> ( ... ) ********************************/
        public:
            bool operator>>(unsigned short& output)             { return shr_unsigned(output); }
            bool operator>>(unsigned int& output)               { return shr_unsigned(output); }
            bool operator>>(unsigned long int& output)          { return shr_unsigned(output); }
            bool operator>>(short& output)                      { return shr_signed(output); }
            bool operator>>(int& output)                        { return shr_signed(output); }
            bool operator>>(long int& output)                   { return shr_signed(output); }
#if defined(BOOST_HAS_LONG_LONG)
            bool operator>>(boost::ulong_long_type& output)     { return shr_unsigned(output); }
            bool operator>>(boost::long_long_type& output)      { return shr_signed(output); }
#elif defined(BOOST_HAS_MS_INT64)
            bool operator>>(unsigned __int64& output)           { return shr_unsigned(output); }
            bool operator>>(__int64& output)                    { return shr_signed(output); }
#endif

#ifdef BOOST_HAS_INT128
            bool operator>>(boost::uint128_type& output)        { return shr_unsigned(output); }
            bool operator>>(boost::int128_type& output)         { return shr_signed(output); }
#endif

            bool operator>>(char& output)                       { return shr_xchar(output); }
            bool operator>>(unsigned char& output)              { return shr_xchar(output); }
            bool operator>>(signed char& output)                { return shr_xchar(output); }
#if !defined(BOOST_LCAST_NO_WCHAR_T) && !defined(BOOST_NO_INTRINSIC_WCHAR_T)
            bool operator>>(wchar_t& output)                    { return shr_xchar(output); }
#endif
#if !defined(BOOST_NO_CXX11_CHAR16_T) && !defined(BOOST_NO_CXX11_UNICODE_LITERALS)
            bool operator>>(char16_t& output)                   { return shr_xchar(output); }
#endif
#if !defined(BOOST_NO_CXX11_CHAR32_T) && !defined(BOOST_NO_CXX11_UNICODE_LITERALS)
            bool operator>>(char32_t& output)                   { return shr_xchar(output); }
#endif
            template<class Alloc>
            bool operator>>(std::basic_string<CharT,Traits,Alloc>& str) {
                str.assign(start, finish); return true;
            }

            template<class Alloc>
            bool operator>>(boost::container::basic_string<CharT,Traits,Alloc>& str) {
                str.assign(start, finish); return true;
            }

            template <std::size_t N>
            bool operator>>(boost::array<CharT, N>& output) BOOST_NOEXCEPT {
                return shr_std_array<N>(output);
            }

            template <std::size_t N>
            bool operator>>(boost::array<unsigned char, N>& output) BOOST_NOEXCEPT {
                return ((*this) >> reinterpret_cast<boost::array<char, N>& >(output));
            }

            template <std::size_t N>
            bool operator>>(boost::array<signed char, N>& output) BOOST_NOEXCEPT {
                return ((*this) >> reinterpret_cast<boost::array<char, N>& >(output));
            }

#ifndef BOOST_NO_CXX11_HDR_ARRAY
            template <class C, std::size_t N>
            bool operator>>(std::array<C, N>& output) BOOST_NOEXCEPT {
                BOOST_STATIC_ASSERT_MSG(
                    (sizeof(std::array<C, N>) == sizeof(boost::array<C, N>)),
                    "std::array<C, N> and boost::array<C, N> must have exactly the same layout."
                );
                return ((*this) >> reinterpret_cast<boost::array<C, N>& >(output));
            }
#endif

            bool operator>>(bool& output) BOOST_NOEXCEPT {
                output = false; // Suppress warning about uninitalized variable

                if (start == finish) return false;
                CharT const zero = lcast_char_constants<CharT>::zero;
                CharT const plus = lcast_char_constants<CharT>::plus;
                CharT const minus = lcast_char_constants<CharT>::minus;

                const CharT* const dec_finish = finish - 1;
                output = Traits::eq(*dec_finish, zero + 1);
                if (!output && !Traits::eq(*dec_finish, zero)) {
                    return false; // Does not ends on '0' or '1'
                }

                if (start == dec_finish) return true;

                // We may have sign at the beginning
                if (Traits::eq(plus, *start) || (Traits::eq(minus, *start) && !output)) {
                    ++ start;
                }

                // Skipping zeros
                while (start != dec_finish) {
                    if (!Traits::eq(zero, *start)) {
                        return false; // Not a zero => error
                    }

                    ++ start;
                }

                return true;
            }

        private:
            // Not optimised converter
            template <class T>
            bool float_types_converter_internal(T& output) {
                if (parse_inf_nan(start, finish, output)) return true;
                bool const return_value = shr_using_base_class(output);

                /* Some compilers and libraries successfully
                 * parse 'inf', 'INFINITY', '1.0E', '1.0E-'...
                 * We are trying to provide a unified behaviour,
                 * so we just forbid such conversions (as some
                 * of the most popular compilers/libraries do)
                 * */
                CharT const minus = lcast_char_constants<CharT>::minus;
                CharT const plus = lcast_char_constants<CharT>::plus;
                CharT const capital_e = lcast_char_constants<CharT>::capital_e;
                CharT const lowercase_e = lcast_char_constants<CharT>::lowercase_e;
                if ( return_value &&
                     (
                        Traits::eq(*(finish-1), lowercase_e)                   // 1.0e
                        || Traits::eq(*(finish-1), capital_e)                  // 1.0E
                        || Traits::eq(*(finish-1), minus)                      // 1.0e- or 1.0E-
                        || Traits::eq(*(finish-1), plus)                       // 1.0e+ or 1.0E+
                     )
                ) return false;

                return return_value;
            }

        public:
            bool operator>>(float& output) { return float_types_converter_internal(output); }
            bool operator>>(double& output) { return float_types_converter_internal(output); }
            bool operator>>(long double& output) { return float_types_converter_internal(output); }

            // Generic istream-based algorithm.
            // lcast_streambuf_for_target<InputStreamable>::value is true.
            template <typename InputStreamable>
            bool operator>>(InputStreamable& output) {
                return shr_using_base_class(output);
            }
        };
    }
} // namespace boost

#undef BOOST_LCAST_NO_WCHAR_T

#endif // BOOST_LEXICAL_CAST_DETAIL_CONVERTER_LEXICAL_HPP


/* converter_lexical_streams.hpp
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
*/