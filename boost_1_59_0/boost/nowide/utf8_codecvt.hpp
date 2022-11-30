//
//  Copyright (c) 2015 Artyom Beilis (Tonkikh)
//  Copyright (c) 2020 Alexander Grund
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NOWIDE_UTF8_CODECVT_HPP_INCLUDED
#define BOOST_NOWIDE_UTF8_CODECVT_HPP_INCLUDED

#include <boost/nowide/replacement.hpp>
#include <boost/nowide/utf/utf.hpp>
#include <cassert>
#include <cstdint>
#include <locale>

namespace boost {
namespace nowide {

    static_assert(sizeof(std::mbstate_t) >= 2, "mbstate_t is to small to store an UTF-16 codepoint");
    namespace detail {
        // Avoid including cstring for std::memcpy
        inline void copy_uint16_t(void* dst, const void* src)
        {
            unsigned char* cdst = static_cast<unsigned char*>(dst);
            const unsigned char* csrc = static_cast<const unsigned char*>(src);
            cdst[0] = csrc[0];
            cdst[1] = csrc[1];
        }
        inline std::uint16_t read_state(const std::mbstate_t& src)
        {
            std::uint16_t dst;
            copy_uint16_t(&dst, &src);
            return dst;
        }
        inline void write_state(std::mbstate_t& dst, const std::uint16_t src)
        {
            copy_uint16_t(&dst, &src);
        }
    } // namespace detail

    /// std::codecvt implementation that converts between UTF-8 and UTF-16 or UTF-32
    ///
    /// @tparam CharSize Determines the encoding: 2 for UTF-16, 4 for UTF-32
    ///
    /// Invalid sequences are replaced by #BOOST_NOWIDE_REPLACEMENT_CHARACTER
    /// A trailing incomplete sequence will result in a return value of std::codecvt::partial
    template<typename CharType, int CharSize = sizeof(CharType)>
    class utf8_codecvt;

    BOOST_NOWIDE_SUPPRESS_UTF_CODECVT_DEPRECATION_BEGIN
    /// Specialization for the UTF-8 <-> UTF-16 variant of the std::codecvt implementation
    template<typename CharType>
    class BOOST_SYMBOL_VISIBLE utf8_codecvt<CharType, 2> : public std::codecvt<CharType, char, std::mbstate_t>
    {
    public:
        static_assert(sizeof(CharType) >= 2, "CharType must be able to store UTF16 code point");

        utf8_codecvt(size_t refs = 0) : std::codecvt<CharType, char, std::mbstate_t>(refs)
        {}
        BOOST_NOWIDE_SUPPRESS_UTF_CODECVT_DEPRECATION_END

    protected:
        using uchar = CharType;

        std::codecvt_base::result do_unshift(std::mbstate_t& s, char* from, char* /*to*/, char*& next) const override
        {
            if(detail::read_state(s) != 0)
                return std::codecvt_base::error;
            next = from;
            return std::codecvt_base::ok;
        }
        int do_encoding() const noexcept override
        {
            return 0;
        }
        int do_max_length() const noexcept override
        {
            return 4;
        }
        bool do_always_noconv() const noexcept override
        {
            return false;
        }

        // LCOV_EXCL_START
        int do_length(std::mbstate_t& std_state, const char* from, const char* from_end, size_t max) const override
        {
            // LCOV_EXCL_STOP
            using utf16_traits = utf::utf_traits<uchar, 2>;
            std::uint16_t state = detail::read_state(std_state);
            const char* save_from = from;
            if(state && max > 0)
            {
                max--;
                state = 0;
            }
            while(max > 0 && from < from_end)
            {
                const char* prev_from = from;
                std::uint32_t ch = utf::utf_traits<char>::decode(from, from_end);
                if(ch == utf::illegal)
                {
                    ch = BOOST_NOWIDE_REPLACEMENT_CHARACTER;
                } else if(ch == utf::incomplete)
                {
                    from = prev_from;
                    break;
                }
                // If we can't write the char, we have to save the low surrogate in state
                if(BOOST_LIKELY(static_cast<size_t>(utf16_traits::width(ch)) <= max))
                {
                    max -= utf16_traits::width(ch);
                } else
                {
                    static_assert(utf16_traits::max_width == 2, "Required for below");
                    std::uint16_t tmpOut[2]{};
                    utf16_traits::encode(ch, tmpOut);
                    state = tmpOut[1];
                    break;
                }
            }
            detail::write_state(std_state, state);
            return static_cast<int>(from - save_from);
        }

        std::codecvt_base::result do_in(std::mbstate_t& std_state, // LCOV_EXCL_LINE
                                        const char* from,
                                        const char* from_end,
                                        const char*& from_next,
                                        uchar* to,
                                        uchar* to_end,
                                        uchar*& to_next) const override
        {
            std::codecvt_base::result r = std::codecvt_base::ok;
            using utf16_traits = utf::utf_traits<uchar, 2>;

            // mbstate_t is POD type and should be initialized to 0 (i.e. state = stateT())
            // according to standard.
            // We use it to store a low surrogate if it was not yet written, else state is 0
            std::uint16_t state = detail::read_state(std_state);
            // Write low surrogate if present
            if(state && to < to_end)
            {
                *to++ = static_cast<CharType>(state);
                state = 0;
            }
            while(to < to_end && from < from_end)
            {
                const char* from_saved = from;

                uint32_t ch = utf::utf_traits<char>::decode(from, from_end);

                if(ch == utf::illegal)
                {
                    ch = BOOST_NOWIDE_REPLACEMENT_CHARACTER;
                } else if(ch == utf::incomplete)
                {
                    from = from_saved;
                    r = std::codecvt_base::partial;
                    break;
                }
                // If the encoded char fits, write directly, else safe the low surrogate in state
                if(BOOST_LIKELY(utf16_traits::width(ch) <= to_end - to))
                {
                    to = utf16_traits::encode(ch, to);
                } else
                {
                    static_assert(utf16_traits::max_width == 2, "Required for below");
                    std::uint16_t tmpOut[2]{};
                    utf16_traits::encode(ch, tmpOut);
                    *to++ = static_cast<CharType>(tmpOut[0]);
                    state = tmpOut[1];
                    break;
                }
            }
            from_next = from;
            to_next = to;
            if(r == std::codecvt_base::ok && (from != from_end || state != 0))
                r = std::codecvt_base::partial;
            detail::write_state(std_state, state);
            return r;
        }

        std::codecvt_base::result do_out(std::mbstate_t& std_state,
                                         const uchar* from,
                                         const uchar* from_end,
                                         const uchar*& from_next,
                                         char* to,
                                         char* to_end,
                                         char*& to_next) const override
        {
            std::codecvt_base::result r = std::codecvt_base::ok;
            using utf16_traits = utf::utf_traits<uchar, 2>;
            // mbstate_t is POD type and should be initialized to 0
            // (i.e. state = stateT()) according to standard.
            // We use it to store the first observed surrogate pair, or 0 if there is none yet
            std::uint16_t state = detail::read_state(std_state);
            for(; to < to_end && from < from_end; ++from)
            {
                std::uint32_t ch = 0;
                if(state != 0)
                {
                    // We have a high surrogate, so now there should be a low surrogate
                    std::uint16_t w1 = state;
                    std::uint16_t w2 = *from;
                    if(BOOST_LIKELY(utf16_traits::is_trail(w2)))
                    {
                        ch = utf16_traits::combine_surrogate(w1, w2);
                    } else
                    {
                        ch = BOOST_NOWIDE_REPLACEMENT_CHARACTER;
                    }
                } else
                {
                    std::uint16_t w1 = *from;
                    if(BOOST_LIKELY(utf16_traits::is_single_codepoint(w1)))
                    {
                        ch = w1;
                    } else if(BOOST_LIKELY(utf16_traits::is_first_surrogate(w1)))
                    {
                        // Store into state and continue at next character
                        state = w1;
                        continue;
                    } else
                    {
                        // Neither a single codepoint nor a high surrogate so must be low surrogate.
                        // This is an error -> Replace character
                        ch = BOOST_NOWIDE_REPLACEMENT_CHARACTER;
                    }
                }
                assert(utf::is_valid_codepoint(ch)); // Any valid UTF16 sequence is a valid codepoint
                int len = utf::utf_traits<char>::width(ch);
                if(to_end - to < len)
                {
                    r = std::codecvt_base::partial;
                    break;
                }
                to = utf::utf_traits<char>::encode(ch, to);
                state = 0;
            }
            from_next = from;
            to_next = to;
            if(r == std::codecvt_base::ok && (from != from_end || state != 0))
                r = std::codecvt_base::partial;
            detail::write_state(std_state, state);
            return r;
        }
    };

    BOOST_NOWIDE_SUPPRESS_UTF_CODECVT_DEPRECATION_BEGIN
    /// Specialization for the UTF-8 <-> UTF-32 variant of the std::codecvt implementation
    template<typename CharType>
    class BOOST_SYMBOL_VISIBLE utf8_codecvt<CharType, 4> : public std::codecvt<CharType, char, std::mbstate_t>
    {
    public:
        utf8_codecvt(size_t refs = 0) : std::codecvt<CharType, char, std::mbstate_t>(refs)
        {}
        BOOST_NOWIDE_SUPPRESS_UTF_CODECVT_DEPRECATION_END

    protected:
        using uchar = CharType;

        std::codecvt_base::result
        do_unshift(std::mbstate_t& /*s*/, char* from, char* /*to*/, char*& next) const override
        {
            next = from;
            return std::codecvt_base::noconv;
        }
        int do_encoding() const noexcept override
        {
            return 0;
        }
        int do_max_length() const noexcept override
        {
            return 4;
        }
        bool do_always_noconv() const noexcept override
        {
            return false;
        }

        int do_length(std::mbstate_t& /*state*/, const char* from, const char* from_end, size_t max) const override
        {
            const char* start_from = from;

            while(max > 0 && from < from_end)
            {
                const char* save_from = from;
                std::uint32_t ch = utf::utf_traits<char>::decode(from, from_end);
                if(ch == utf::incomplete)
                {
                    from = save_from;
                    break;
                } else if(ch == utf::illegal)
                {
                    ch = BOOST_NOWIDE_REPLACEMENT_CHARACTER;
                }
                max--;
            }
            return static_cast<int>(from - start_from);
        }

        std::codecvt_base::result do_in(std::mbstate_t& /*state*/,
                                        const char* from,
                                        const char* from_end,
                                        const char*& from_next,
                                        uchar* to,
                                        uchar* to_end,
                                        uchar*& to_next) const override
        {
            std::codecvt_base::result r = std::codecvt_base::ok;

            while(to < to_end && from < from_end)
            {
                const char* from_saved = from;

                uint32_t ch = utf::utf_traits<char>::decode(from, from_end);

                if(ch == utf::illegal)
                {
                    ch = BOOST_NOWIDE_REPLACEMENT_CHARACTER;
                } else if(ch == utf::incomplete)
                {
                    r = std::codecvt_base::partial;
                    from = from_saved;
                    break;
                }
                *to++ = ch;
            }
            from_next = from;
            to_next = to;
            if(r == std::codecvt_base::ok && from != from_end)
                r = std::codecvt_base::partial;
            return r;
        }

        std::codecvt_base::result do_out(std::mbstate_t& /*std_state*/,
                                         const uchar* from,
                                         const uchar* from_end,
                                         const uchar*& from_next,
                                         char* to,
                                         char* to_end,
                                         char*& to_next) const override
        {
            std::codecvt_base::result r = std::codecvt_base::ok;
            while(to < to_end && from < from_end)
            {
                std::uint32_t ch = 0;
                ch = *from;
                if(!utf::is_valid_codepoint(ch))
                {
                    ch = BOOST_NOWIDE_REPLACEMENT_CHARACTER;
                }
                int len = utf::utf_traits<char>::width(ch);
                if(to_end - to < len)
                {
                    r = std::codecvt_base::partial;
                    break;
                }
                to = utf::utf_traits<char>::encode(ch, to);
                from++;
            }
            from_next = from;
            to_next = to;
            if(r == std::codecvt_base::ok && from != from_end)
                r = std::codecvt_base::partial;
            return r;
        }
    };

} // namespace nowide
} // namespace boost

#endif

/* utf8_codecvt.hpp
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
*/