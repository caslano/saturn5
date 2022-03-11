//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NOWIDE_UTF_HPP_INCLUDED
#define BOOST_NOWIDE_UTF_HPP_INCLUDED

#include <boost/nowide/config.hpp>
#include <boost/cstdint.hpp>

namespace boost {
namespace nowide {
    namespace detail {
        ///
        /// \brief Namespace that holds basic operations on UTF encoded sequences
        ///
        /// All functions defined in this namespace do not require linking with Boost.Nowide library
        /// Extracted from Boost.Locale
        ///
        namespace utf {

            ///
            /// \brief The integral type that can hold a Unicode code point
            ///
            typedef uint32_t code_point;

            ///
            /// \brief Special constant that defines illegal code point
            ///
            static const code_point illegal = 0xFFFFFFFFu;

            ///
            /// \brief Special constant that defines incomplete code point
            ///
            static const code_point incomplete = 0xFFFFFFFEu;

            ///
            /// \brief the function checks if \a v is a valid code point
            ///
            inline bool is_valid_codepoint(code_point v)
            {
                if(v > 0x10FFFF)
                    return false;
                if(0xD800 <= v && v <= 0xDFFF) // surrogates
                    return false;
                return true;
            }

#ifdef BOOST_NOWIDE_DOXYGEN
            ///
            /// \brief UTF Traits class - functions to convert UTF sequences to and from Unicode code points
            ///
            template<typename CharType, int size = sizeof(CharType)>
            struct utf_traits
            {
                ///
                /// The type of the character
                ///
                typedef CharType char_type;
                ///
                /// Read one code point from the range [p,e) and return it.
                ///
                /// - If the sequence that was read is incomplete sequence returns \ref incomplete,
                /// - If illegal sequence detected returns \ref illegal
                ///
                /// Requirements
                ///
                /// - Iterator is valid input iterator
                ///
                /// Postconditions
                ///
                /// - p points to the last consumed character
                ///
                template<typename Iterator>
                static code_point decode(Iterator& p, Iterator e);

                ///
                /// Maximal width of valid sequence in the code units:
                ///
                /// - UTF-8  - 4
                /// - UTF-16 - 2
                /// - UTF-32 - 1
                ///
                static const int max_width;
                ///
                /// The width of specific code point in the code units.
                ///
                /// Requirement: value is a valid Unicode code point
                /// Returns value in range [1..max_width]
                ///
                static int width(code_point value);

                ///
                /// Get the size of the trail part of variable length encoded sequence.
                ///
                /// Returns -1 if C is not valid lead character
                ///
                static int trail_length(char_type c);
                ///
                /// Returns true if c is trail code unit, always false for UTF-32
                ///
                static bool is_trail(char_type c);
                ///
                /// Returns true if c is lead code unit, always true of UTF-32
                ///
                static bool is_lead(char_type c);

                ///
                /// Convert valid Unicode code point \a value to the UTF sequence.
                ///
                /// Requirements:
                ///
                /// - \a value is valid code point
                /// - \a out is an output iterator should be able to accept at least width(value) units
                ///
                /// Returns the iterator past the last written code unit.
                ///
                template<typename Iterator>
                static Iterator encode(code_point value, Iterator out);
                ///
                /// Decodes valid UTF sequence that is pointed by p into code point.
                ///
                /// If the sequence is invalid or points to end the behavior is undefined
                ///
                template<typename Iterator>
                static code_point decode_valid(Iterator& p);
            };

#else

            template<typename CharType, int size = sizeof(CharType)>
            struct utf_traits;

            template<typename CharType>
            struct utf_traits<CharType, 1>
            {
                typedef CharType char_type;

                static int trail_length(char_type ci)
                {
                    unsigned char c = ci;
                    if(c < 128)
                        return 0;
                    if(BOOST_UNLIKELY(c < 194))
                        return -1;
                    if(c < 224)
                        return 1;
                    if(c < 240)
                        return 2;
                    if(BOOST_LIKELY(c <= 244))
                        return 3;
                    return -1;
                }

                static const int max_width = 4;

                static int width(code_point value)
                {
                    if(value <= 0x7F)
                    {
                        return 1;
                    } else if(value <= 0x7FF)
                    {
                        return 2;
                    } else if(BOOST_LIKELY(value <= 0xFFFF))
                    {
                        return 3;
                    } else
                    {
                        return 4;
                    }
                }

                static bool is_trail(char_type ci)
                {
                    unsigned char c = ci;
                    return (c & 0xC0) == 0x80;
                }

                static bool is_lead(char_type ci)
                {
                    return !is_trail(ci);
                }

                template<typename Iterator>
                static code_point decode(Iterator& p, Iterator e)
                {
                    if(BOOST_UNLIKELY(p == e))
                        return incomplete;

                    unsigned char lead = *p++;

                    // First byte is fully validated here
                    int trail_size = trail_length(lead);

                    if(BOOST_UNLIKELY(trail_size < 0))
                        return illegal;

                    //
                    // OK as only ASCII may be of size = 0
                    // also optimize for ASCII text
                    //
                    if(trail_size == 0)
                        return lead;

                    code_point c = lead & ((1 << (6 - trail_size)) - 1);

                    // Read the rest
                    unsigned char tmp;
                    switch(trail_size)
                    {
                    case 3:
                        if(BOOST_UNLIKELY(p == e))
                            return incomplete;
                        tmp = *p++;
                        if(!is_trail(tmp))
                            return illegal;
                        c = (c << 6) | (tmp & 0x3F);
                        BOOST_NOWIDE_FALLTHROUGH;
                    case 2:
                        if(BOOST_UNLIKELY(p == e))
                            return incomplete;
                        tmp = *p++;
                        if(!is_trail(tmp))
                            return illegal;
                        c = (c << 6) | (tmp & 0x3F);
                        BOOST_NOWIDE_FALLTHROUGH;
                    case 1:
                        if(BOOST_UNLIKELY(p == e))
                            return incomplete;
                        tmp = *p++;
                        if(!is_trail(tmp))
                            return illegal;
                        c = (c << 6) | (tmp & 0x3F);
                    }

                    // Check code point validity: no surrogates and
                    // valid range
                    if(BOOST_UNLIKELY(!is_valid_codepoint(c)))
                        return illegal;

                    // make sure it is the most compact representation
                    if(BOOST_UNLIKELY(width(c) != trail_size + 1))
                        return illegal;

                    return c;
                }

                template<typename Iterator>
                static code_point decode_valid(Iterator& p)
                {
                    unsigned char lead = *p++;
                    if(lead < 192)
                        return lead;

                    int trail_size;

                    if(lead < 224)
                        trail_size = 1;
                    else if(BOOST_LIKELY(lead < 240)) // non-BMP rare
                        trail_size = 2;
                    else
                        trail_size = 3;

                    code_point c = lead & ((1 << (6 - trail_size)) - 1);

                    switch(trail_size)
                    {
                    case 3: c = (c << 6) | (static_cast<unsigned char>(*p++) & 0x3F); BOOST_NOWIDE_FALLTHROUGH;
                    case 2: c = (c << 6) | (static_cast<unsigned char>(*p++) & 0x3F); BOOST_NOWIDE_FALLTHROUGH;
                    case 1: c = (c << 6) | (static_cast<unsigned char>(*p++) & 0x3F);
                    }

                    return c;
                }

                template<typename Iterator>
                static Iterator encode(code_point value, Iterator out)
                {
                    if(value <= 0x7F)
                    {
                        *out++ = static_cast<char_type>(value);
                    } else if(value <= 0x7FF)
                    {
                        *out++ = static_cast<char_type>((value >> 6) | 0xC0);
                        *out++ = static_cast<char_type>((value & 0x3F) | 0x80);
                    } else if(BOOST_LIKELY(value <= 0xFFFF))
                    {
                        *out++ = static_cast<char_type>((value >> 12) | 0xE0);
                        *out++ = static_cast<char_type>(((value >> 6) & 0x3F) | 0x80);
                        *out++ = static_cast<char_type>((value & 0x3F) | 0x80);
                    } else
                    {
                        *out++ = static_cast<char_type>((value >> 18) | 0xF0);
                        *out++ = static_cast<char_type>(((value >> 12) & 0x3F) | 0x80);
                        *out++ = static_cast<char_type>(((value >> 6) & 0x3F) | 0x80);
                        *out++ = static_cast<char_type>((value & 0x3F) | 0x80);
                    }
                    return out;
                }
            }; // utf8

            template<typename CharType>
            struct utf_traits<CharType, 2>
            {
                typedef CharType char_type;

                // See RFC 2781
                static bool is_first_surrogate(uint16_t x)
                {
                    return 0xD800 <= x && x <= 0xDBFF;
                }
                static bool is_second_surrogate(uint16_t x)
                {
                    return 0xDC00 <= x && x <= 0xDFFF;
                }
                static code_point combine_surrogate(uint16_t w1, uint16_t w2)
                {
                    return ((code_point(w1 & 0x3FF) << 10) | (w2 & 0x3FF)) + 0x10000;
                }
                static int trail_length(char_type c)
                {
                    if(is_first_surrogate(c))
                        return 1;
                    if(is_second_surrogate(c))
                        return -1;
                    return 0;
                }
                ///
                /// Returns true if c is trail code unit, always false for UTF-32
                ///
                static bool is_trail(char_type c)
                {
                    return is_second_surrogate(c);
                }
                ///
                /// Returns true if c is lead code unit, always true of UTF-32
                ///
                static bool is_lead(char_type c)
                {
                    return !is_second_surrogate(c);
                }

                template<typename It>
                static code_point decode(It& current, It last)
                {
                    if(BOOST_UNLIKELY(current == last))
                        return incomplete;
                    uint16_t w1 = *current++;
                    if(BOOST_LIKELY(w1 < 0xD800 || 0xDFFF < w1))
                    {
                        return w1;
                    }
                    if(w1 > 0xDBFF)
                        return illegal;
                    if(current == last)
                        return incomplete;
                    uint16_t w2 = *current++;
                    if(w2 < 0xDC00 || 0xDFFF < w2)
                        return illegal;
                    return combine_surrogate(w1, w2);
                }
                template<typename It>
                static code_point decode_valid(It& current)
                {
                    uint16_t w1 = *current++;
                    if(BOOST_LIKELY(w1 < 0xD800 || 0xDFFF < w1))
                    {
                        return w1;
                    }
                    uint16_t w2 = *current++;
                    return combine_surrogate(w1, w2);
                }

                static const int max_width = 2;
                static int width(code_point u)
                {
                    return u >= 0x10000 ? 2 : 1;
                }
                template<typename It>
                static It encode(code_point u, It out)
                {
                    if(BOOST_LIKELY(u <= 0xFFFF))
                    {
                        *out++ = static_cast<char_type>(u);
                    } else
                    {
                        u -= 0x10000;
                        *out++ = static_cast<char_type>(0xD800 | (u >> 10));
                        *out++ = static_cast<char_type>(0xDC00 | (u & 0x3FF));
                    }
                    return out;
                }
            }; // utf16;

            template<typename CharType>
            struct utf_traits<CharType, 4>
            {
                typedef CharType char_type;
                static int trail_length(char_type c)
                {
                    if(is_valid_codepoint(c))
                        return 0;
                    return -1;
                }
                static bool is_trail(char_type /*c*/)
                {
                    return false;
                }
                static bool is_lead(char_type /*c*/)
                {
                    return true;
                }

                template<typename It>
                static code_point decode_valid(It& current)
                {
                    return *current++;
                }

                template<typename It>
                static code_point decode(It& current, It last)
                {
                    if(BOOST_UNLIKELY(current == last))
                        return incomplete;
                    code_point c = *current++;
                    if(BOOST_UNLIKELY(!is_valid_codepoint(c)))
                        return illegal;
                    return c;
                }
                static const int max_width = 1;
                static int width(code_point /*u*/)
                {
                    return 1;
                }
                template<typename It>
                static It encode(code_point u, It out)
                {
                    *out++ = static_cast<char_type>(u);
                    return out;
                }

            }; // utf32

#endif

        } // namespace utf
    }     // namespace detail
} // namespace nowide
} // namespace boost

#endif

/* utf.hpp
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
*/