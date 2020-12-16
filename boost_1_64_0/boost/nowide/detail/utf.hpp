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
W/6D81Qy/b0cSdwM93KYT9IYmaQV6HC/Ccb2FPqTzHBthqwZs/blneswtomUO8zwTSWy2+HSmsVveIT6LrL6DM/n+MnCYfrfUxPJrDD9+yCSLso5OM0wB2MvyXsrptJy1eHOHVAfWQyzHx+dv40+u2wT55il+aUlxs95RR/3a4cMMZiDZGWY/Ty8RXPUR7aXWbNBY/qiX67axBhmR19PRDtd12j/ztvy4m5XxJH1YVZ+9zUv5tJ1GiOY4VtoZM2YeQsF7qKvWdxkWva6d6kk+pqsjklaQsmd8r3uNzG2ZPptj5dsMrNxgS/yfcYBmyivrWPJJ6gZvytUAPPsDl27Z1Zx9NBKWP/u2cQVk7StOQ90QtwDG74bOPF/x/41k7D+vbGJ+BBpjvIXMD/N7+k8jlnFHWFT0C8f6bhVs+SNwP4aKeT1+S/yvCN5B/bXkVtZkLvJjm8Rjks+x/tj2AH0Z0o7vin4G/2/NC6ffFYvrV0U/+pf+zW5nCiPfJd6lB3r+9jkXUnqPvtQJtkXkzRvnV/k/MxkFydD/7Xk+dbiW4G5FJPNLuoIaT/M61UKOZBFwfTbFz/ZXJO0Z4s/Z0c7s9tF/sLSHn+IO4X58oMd7xIanbw9u53OivFracfvFr/Q8lXvvsMwXwzW7lyXOSiTbBuzeZPSrUJ/trKLGJO0PMPjJmPc29hFWxb3uPWxxSiT7A2zrDNrdUR+LsqBmcf9N3KPb2sXY5jVGFoec8LZzi7qM3OX9c5FfWRtmB1p3MWNdra3iwww/ftmosnmMDuX51ZBzAmy6swylusi333TwS7sMMM7ZciimD18XH0U2qmI8ykskYzmJ6zmZMtMtOVHu+jM4qrln3gY6zvZlBBpF2cNf4P+7GoXTZjVytZf3u/dwy6uC2lbO8TtRZ/1tIvZzO7EfRqDPiPbx9p5rXWLRojrbRe1Wdymd3mrol/IrjIrVKyZfKdMH7uowOxEiclpsF3qS+sms+svT7VDDv3soiGzsddmXcK8VlgS2V8h0kImTv4F7RxkF0OZFS03qQDaOVSW+TMtI/6Onoa+HkZzAqa/lh5DFgHTH0/EKuLiFXFuHmf8jUER5yOzwfTX7hMVZSYpyhTDg5fpJMsGM1wvV5hbYT6FBcgywwzXy0cEtxiFxSvMO0LmPspwD7mfrHK4tOrbeyXKZ73ktmCk4f09brJKzBY5okthjMgGMQuf7zSjnWPtogizwbsee9BnZHmZ9Zi9aj36zGARu/ZgfTD/qrekjS8F+sxge1f80BRtIcscIu1C5yd/Y06Mtwsni9uV7fBHzAmyJGbpOspvaLsn2HFt1E3LXjEptiO/iXYc744wHO+aJ9nxXYzhtKz08bc8aCdZhRTS0g/Iuhz5zbTjmtwwWuZb3Egef5KNMUkrfezlG+Qw2y5Ks7jGI7fLZzHIUsP078TzkeVlNjWsl3yvg6HM+gWypMB293e7yMosT639HrSTLAOzriF7RqA/ydAWw32qHrLszL7/+6L8DYVsE8v9VN3N7dDOudq6qdngjDvke57n2cUMZvfblO+DeU3WmdmDzZ/9yGE+9TWzp/3aZESZC+wiLbOUK2/JZ0bIsjA7PLAeco8lszOz/LRYnjOT9WI28JcOAWzrFtpFOmbT4pdtRH1kQ5jN2TQ7DfqMbIpmQ5M3mRVKV8Y4eO2iGLPB9bLNRBxZambLTpZrjj4ji4Dp77cJGOJKFIgdhm05N8O7F8UiZoZ3PZoN9vDn5oORu8E2TE9ZF/PTYA3O1O6LdYyb4V1XsdwM64qLm2Huxhsse69undHXBhvUqWhrzHmDdS+frg7WW7IxzPKnNXvQzsW0D2DWTqTxoy1kXZnFNP8=
*/