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