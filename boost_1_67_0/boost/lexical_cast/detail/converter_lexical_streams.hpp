// Copyright Kevlin Henney, 2000-2005.
// Copyright Alexander Nasonov, 2006-2010.
// Copyright Antony Polukhin, 2011-2020.
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