//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_UTF_HPP_INCLUDED
#define BOOST_LOCALE_UTF_HPP_INCLUDED

#include <boost/cstdint.hpp>

namespace boost {
namespace locale {
///
/// \brief Namespace that holds basic operations on UTF encoded sequences 
///
/// All functions defined in this namespace do not require linking with Boost.Locale library
///
namespace utf {
    /// \cond INTERNAL
    #ifdef __GNUC__
    #   define BOOST_LOCALE_LIKELY(x)   __builtin_expect((x),1)
    #   define BOOST_LOCALE_UNLIKELY(x) __builtin_expect((x),0)
    #else
    #   define BOOST_LOCALE_LIKELY(x)   (x)
    #   define BOOST_LOCALE_UNLIKELY(x) (x)
    #endif
    /// \endcond

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
        if(v>0x10FFFF)
            return false;
        if(0xD800 <=v && v<= 0xDFFF) // surragates
            return false;
        return true;
    }

    #ifdef BOOST_LOCALE_DOXYGEN
    ///
    /// \brief UTF Traits class - functions to convert UTF sequences to and from Unicode code points
    ///
    template<typename CharType,int size=sizeof(CharType)>
    struct utf_traits {
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
        static code_point decode(Iterator &p,Iterator e);

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
        static Iterator encode(code_point value,Iterator out);
        ///
        /// Decodes valid UTF sequence that is pointed by p into code point.
        ///
        /// If the sequence is invalid or points to end the behavior is undefined
        ///
        template<typename Iterator>
        static code_point decode_valid(Iterator &p);
    };
    
    #else

    template<typename CharType,int size=sizeof(CharType)>
    struct utf_traits;

    template<typename CharType>
    struct utf_traits<CharType,1> {

        typedef CharType char_type;
        
        static int trail_length(char_type ci) 
        {
            unsigned char c = ci;
            if(c < 128)
                return 0;
            if(BOOST_LOCALE_UNLIKELY(c < 194))
                return -1;
            if(c < 224)
                return 1;
            if(c < 240)
                return 2;
            if(BOOST_LOCALE_LIKELY(c <=244))
                return 3;
            return -1;
        }
        
        static const int max_width = 4;

        static int width(code_point value)
        {
            if(value <=0x7F) {
                return 1;
            }
            else if(value <=0x7FF) {
                return 2;
            }
            else if(BOOST_LOCALE_LIKELY(value <=0xFFFF)) {
                return 3;
            }
            else {
                return 4;
            }
        }

        static bool is_trail(char_type ci)
        {
            unsigned char c=ci;
            return (c & 0xC0)==0x80;
        }

        static bool is_lead(char_type ci)
        {
            return !is_trail(ci);
        }
        
        template<typename Iterator>
        static code_point decode(Iterator &p,Iterator e)
        {
            if(BOOST_LOCALE_UNLIKELY(p==e))
                return incomplete;

            unsigned char lead = *p++;

            // First byte is fully validated here
            int trail_size = trail_length(lead);

            if(BOOST_LOCALE_UNLIKELY(trail_size < 0))
                return illegal;

            //
            // Ok as only ASCII may be of size = 0
            // also optimize for ASCII text
            //
            if(trail_size == 0)
                return lead;
            
            code_point c = lead & ((1<<(6-trail_size))-1);

            // Read the rest
            unsigned char tmp;
            switch(trail_size) {
            case 3:
                if(BOOST_LOCALE_UNLIKELY(p==e))
                    return incomplete;
                tmp = *p++;
                if (!is_trail(tmp))
                    return illegal;
                c = (c << 6) | ( tmp & 0x3F);
            case 2:
                if(BOOST_LOCALE_UNLIKELY(p==e))
                    return incomplete;
                tmp = *p++;
                if (!is_trail(tmp))
                    return illegal;
                c = (c << 6) | ( tmp & 0x3F);
            case 1:
                if(BOOST_LOCALE_UNLIKELY(p==e))
                    return incomplete;
                tmp = *p++;
                if (!is_trail(tmp))
                    return illegal;
                c = (c << 6) | ( tmp & 0x3F);
            }

            // Check code point validity: no surrogates and
            // valid range
            if(BOOST_LOCALE_UNLIKELY(!is_valid_codepoint(c)))
                return illegal;

            // make sure it is the most compact representation
            if(BOOST_LOCALE_UNLIKELY(width(c)!=trail_size + 1))
                return illegal;

            return c;

        }
        
        template<typename Iterator>
        static code_point decode_valid(Iterator &p)
        {
            unsigned char lead = *p++;
            if(lead < 192)
                return lead;

            int trail_size;

            if(lead < 224)
                trail_size = 1;
            else if(BOOST_LOCALE_LIKELY(lead < 240)) // non-BMP rare
                trail_size = 2;
            else
                trail_size = 3;
            
            code_point c = lead & ((1<<(6-trail_size))-1);

            switch(trail_size) {
            case 3:
                c = (c << 6) | ( static_cast<unsigned char>(*p++) & 0x3F);
            case 2:
                c = (c << 6) | ( static_cast<unsigned char>(*p++) & 0x3F);
            case 1:
                c = (c << 6) | ( static_cast<unsigned char>(*p++) & 0x3F);
            }

            return c;
        }



        template<typename Iterator>
        static Iterator encode(code_point value,Iterator out)
        {
            if(value <= 0x7F) {
                *out++ = static_cast<char_type>(value);
            }
            else if(value <= 0x7FF) {
                *out++ = static_cast<char_type>((value >> 6) | 0xC0);
                *out++ = static_cast<char_type>((value & 0x3F) | 0x80);
            }
            else if(BOOST_LOCALE_LIKELY(value <= 0xFFFF)) {
                *out++ = static_cast<char_type>((value >> 12) | 0xE0);
                *out++ = static_cast<char_type>(((value >> 6) & 0x3F) | 0x80);
                *out++ = static_cast<char_type>((value & 0x3F) | 0x80);
            }
            else {
                *out++ = static_cast<char_type>((value >> 18) | 0xF0);
                *out++ = static_cast<char_type>(((value >> 12) & 0x3F) | 0x80);
                *out++ = static_cast<char_type>(((value >> 6) & 0x3F) | 0x80);
                *out++ = static_cast<char_type>((value & 0x3F) | 0x80);
            }
            return out;
        }
    }; // utf8

    template<typename CharType>
    struct utf_traits<CharType,2> {
        typedef CharType char_type;

        // See RFC 2781
        static bool is_first_surrogate(uint16_t x)
        {
            return 0xD800 <=x && x<= 0xDBFF;
        }
        static bool is_second_surrogate(uint16_t x)
        {
            return 0xDC00 <=x && x<= 0xDFFF;
        }
        static code_point combine_surrogate(uint16_t w1,uint16_t w2)
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
        static code_point decode(It &current,It last)
        {
            if(BOOST_LOCALE_UNLIKELY(current == last))
                return incomplete;
            uint16_t w1=*current++;
            if(BOOST_LOCALE_LIKELY(w1 < 0xD800 || 0xDFFF < w1)) {
                return w1;
            }
            if(w1 > 0xDBFF)
                return illegal;
            if(current==last)
                return incomplete;
            uint16_t w2=*current++;
            if(w2 < 0xDC00 || 0xDFFF < w2)
                return illegal;
            return combine_surrogate(w1,w2);
        }
        template<typename It>
        static code_point decode_valid(It &current)
        {
            uint16_t w1=*current++;
            if(BOOST_LOCALE_LIKELY(w1 < 0xD800 || 0xDFFF < w1)) {
                return w1;
            }
            uint16_t w2=*current++;
            return combine_surrogate(w1,w2);
        }

        static const int max_width = 2;
        static int width(code_point u)
        {
            return u>=0x10000 ? 2 : 1;
        }
        template<typename It>
        static It encode(code_point u,It out)
        {
            if(BOOST_LOCALE_LIKELY(u<=0xFFFF)) {
                *out++ = static_cast<char_type>(u);
            }
            else {
                u -= 0x10000;
                *out++ = static_cast<char_type>(0xD800 | (u>>10));
                *out++ = static_cast<char_type>(0xDC00 | (u & 0x3FF));
            }
            return out;
        }
    }; // utf16;

        
    template<typename CharType>
    struct utf_traits<CharType,4> {
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
        static code_point decode_valid(It &current)
        {
            return *current++;
        }

        template<typename It>
        static code_point decode(It &current,It last)
        {
            if(BOOST_LOCALE_UNLIKELY(current == last))
                return boost::locale::utf::incomplete;
            code_point c=*current++;
            if(BOOST_LOCALE_UNLIKELY(!is_valid_codepoint(c)))
                return boost::locale::utf::illegal;
            return c;
        }
        static const int max_width = 1;
        static int width(code_point /*u*/)
        {
            return 1;
        }
        template<typename It>
        static It encode(code_point u,It out)
        {
            *out++ = static_cast<char_type>(u);
            return out;
        }

    }; // utf32

    #endif


} // utf
} // locale
} // boost


#endif

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4


/* utf.hpp
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
*/