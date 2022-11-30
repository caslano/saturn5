//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//  Copyright (c) 2020 Alexander Grund
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NOWIDE_UTF_HPP_INCLUDED
#define BOOST_NOWIDE_UTF_HPP_INCLUDED

#include <boost/nowide/config.hpp>
#include <cstdint>

namespace boost {
namespace nowide {
    ///
    /// \brief Namespace that holds basic operations on UTF encoded sequences
    ///
    /// All functions defined in this namespace do not require linking with Boost.Nowide library.
    /// Extracted from Boost.Locale
    ///
    namespace utf {

        ///
        /// \brief The integral type that can hold a Unicode code point
        ///
        using code_point = uint32_t;

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
            using char_type = CharType;
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
            using char_type = CharType;

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

                // OK as only ASCII may be of size = 0
                // also optimize for ASCII text
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

                // Check code point validity:
                // - no surrogates and valid range
                // - most compact representation
                if(BOOST_UNLIKELY(!is_valid_codepoint(c)) || BOOST_UNLIKELY(width(c) != trail_size + 1))
                {
                    p -= trail_size;
                    return illegal;
                }

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
            using char_type = CharType;

            // See RFC 2781
            static bool is_single_codepoint(uint16_t x)
            {
                // Ranges [U+0000, 0+D7FF], [U+E000, U+FFFF] are numerically equal in UTF-16
                return x <= 0xD7FF || x >= 0xE000;
            }
            static bool is_first_surrogate(uint16_t x)
            {
                // Range [U+D800, 0+DBFF]: High surrogate
                return 0xD800 <= x && x <= 0xDBFF;
            }
            static bool is_second_surrogate(uint16_t x)
            {
                // Range [U+DC00, 0+DFFF]: Low surrogate
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
            /// Return true if c is trail code unit, always false for UTF-32
            static bool is_trail(char_type c)
            {
                return is_second_surrogate(c);
            }
            /// Return true if c is lead code unit, always true of UTF-32
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
                if(BOOST_LIKELY(is_single_codepoint(w1)))
                {
                    return w1;
                }
                // Now it's either a high or a low surrogate, the latter is invalid
                if(w1 >= 0xDC00)
                    return illegal;
                if(current == last)
                    return incomplete;
                uint16_t w2 = *current++;
                if(!is_second_surrogate(w2))
                    return illegal;
                return combine_surrogate(w1, w2);
            }
            template<typename It>
            static code_point decode_valid(It& current)
            {
                uint16_t w1 = *current++;
                if(BOOST_LIKELY(is_single_codepoint(w1)))
                {
                    return w1;
                }
                uint16_t w2 = *current++;
                return combine_surrogate(w1, w2);
            }

            static const int max_width = 2;
            static int width(code_point u) // LCOV_EXCL_LINE
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
            using char_type = CharType;
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
} // namespace nowide
} // namespace boost

#endif

/* utf.hpp
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
*/