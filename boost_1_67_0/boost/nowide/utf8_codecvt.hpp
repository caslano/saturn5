//
//  Copyright (c) 2015 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NOWIDE_UTF8_CODECVT_HPP_INCLUDED
#define BOOST_NOWIDE_UTF8_CODECVT_HPP_INCLUDED

#include <boost/nowide/detail/utf.hpp>
#include <boost/nowide/replacement.hpp>
#include <boost/cstdint.hpp>
#include <boost/static_assert.hpp>
#include <locale>

namespace boost {
namespace nowide {

    // Make sure that mbstate can keep 16 bit of UTF-16 sequence
    BOOST_STATIC_ASSERT(sizeof(std::mbstate_t) >= 2);
    namespace detail {
        // Avoid including cstring for std::memcpy
        inline void copy_uint16_t(void* dst, const void* src)
        {
            unsigned char* cdst = static_cast<unsigned char*>(dst);
            const unsigned char* csrc = static_cast<const unsigned char*>(src);
            cdst[0] = csrc[0];
            cdst[1] = csrc[1];
        }
        inline boost::uint16_t read_state(const std::mbstate_t& src)
        {
            boost::uint16_t dst;
            copy_uint16_t(&dst, &src);
            return dst;
        }
        inline void write_state(std::mbstate_t& dst, const boost::uint16_t src)
        {
            copy_uint16_t(&dst, &src);
        }
    } // namespace detail

#if defined _MSC_VER && _MSC_VER < 1700
// MSVC do_length is non-standard it counts wide characters instead of narrow and does not change mbstate
#define BOOST_NOWIDE_DO_LENGTH_MBSTATE_CONST
#endif

    /// std::codecvt implementation that converts between UTF-8 and UTF-16 or UTF-32
    ///
    /// @tparam CharSize Determines the encoding: 2 for UTF-16, 4 for UTF-32
    ///
    /// Invalid sequences are replaced by #BOOST_NOWIDE_REPLACEMENT_CHARACTER
    /// A trailing incomplete sequence will result in a return value of std::codecvt::partial
    template<typename CharType, int CharSize = sizeof(CharType)>
    class utf8_codecvt;

    /// Specialization for the UTF-8 <-> UTF-16 variant of the std::codecvt implementation
    template<typename CharType>
    class BOOST_SYMBOL_VISIBLE utf8_codecvt<CharType, 2> : public std::codecvt<CharType, char, std::mbstate_t>
    {
    public:
        BOOST_STATIC_ASSERT_MSG(sizeof(CharType) >= 2, "CharType must be able to store UTF16 code point");

        utf8_codecvt(size_t refs = 0) : std::codecvt<CharType, char, std::mbstate_t>(refs)
        {}

    protected:
        typedef CharType uchar;

        virtual std::codecvt_base::result do_unshift(std::mbstate_t& s, char* from, char* /*to*/, char*& next) const
        {
            if(detail::read_state(s) != 0)
                return std::codecvt_base::error;
            next = from;
            return std::codecvt_base::ok;
        }
        virtual int do_encoding() const throw()
        {
            return 0;
        }
        virtual int do_max_length() const throw()
        {
            return 4;
        }
        virtual bool do_always_noconv() const throw()
        {
            return false;
        }

        virtual int do_length(std::mbstate_t
#ifdef BOOST_NOWIDE_DO_LENGTH_MBSTATE_CONST
                              const
#endif
                                & std_state,
                              const char* from,
                              const char* from_end,
                              size_t max) const
        {
            boost::uint16_t state = detail::read_state(std_state);
#ifndef BOOST_NOWIDE_DO_LENGTH_MBSTATE_CONST
            const char* save_from = from;
#else
            size_t save_max = max;
#endif
            while(max > 0 && from < from_end)
            {
                const char* prev_from = from;
                boost::uint32_t ch = detail::utf::utf_traits<char>::decode(from, from_end);
                if(ch == detail::utf::illegal)
                {
                    ch = BOOST_NOWIDE_REPLACEMENT_CHARACTER;
                } else if(ch == detail::utf::incomplete)
                {
                    from = prev_from;
                    break;
                }
                max--;
                if(ch > 0xFFFF)
                {
                    if(state == 0)
                    {
                        from = prev_from;
                        state = 1;
                    } else
                    {
                        state = 0;
                    }
                }
            }
#ifndef BOOST_NOWIDE_DO_LENGTH_MBSTATE_CONST
            detail::write_state(std_state, state);
            return static_cast<int>(from - save_from);
#else
            return static_cast<int>(save_max - max);
#endif
        }

        virtual std::codecvt_base::result do_in(std::mbstate_t& std_state,
                                                const char* from,
                                                const char* from_end,
                                                const char*& from_next,
                                                uchar* to,
                                                uchar* to_end,
                                                uchar*& to_next) const
        {
            std::codecvt_base::result r = std::codecvt_base::ok;

            // mbstate_t is POD type and should be initialized to 0 (i.a. state = stateT())
            // according to standard. We use it to keep a flag 0/1 for surrogate pair writing
            //
            // if 0 no code above >0xFFFF observed, of 1 a code above 0xFFFF observed
            // and first pair is written, but no input consumed
            boost::uint16_t state = detail::read_state(std_state);
            while(to < to_end && from < from_end)
            {
                const char* from_saved = from;

                uint32_t ch = detail::utf::utf_traits<char>::decode(from, from_end);

                if(ch == detail::utf::illegal)
                {
                    ch = BOOST_NOWIDE_REPLACEMENT_CHARACTER;
                } else if(ch == detail::utf::incomplete)
                {
                    from = from_saved;
                    r = std::codecvt_base::partial;
                    break;
                }
                // Normal codepoints go directly to stream
                if(ch <= 0xFFFF)
                {
                    *to++ = static_cast<CharType>(ch);
                } else
                {
                    // for  other codepoints we do following
                    //
                    // 1. We can't consume our input as we may find ourself
                    //    in state where all input consumed but not all output written,i.e. only
                    //    1st pair is written
                    // 2. We only write first pair and mark this in the state, we also revert back
                    //    the from pointer in order to make sure this codepoint would be read
                    //    once again and then we would consume our input together with writing
                    //    second surrogate pair
                    ch -= 0x10000;
                    boost::uint16_t vh = static_cast<boost::uint16_t>(ch >> 10);
                    boost::uint16_t vl = ch & 0x3FF;
                    boost::uint16_t w1 = vh + 0xD800;
                    boost::uint16_t w2 = vl + 0xDC00;
                    if(state == 0)
                    {
                        from = from_saved;
                        *to++ = static_cast<CharType>(w1);
                        state = 1;
                    } else
                    {
                        *to++ = static_cast<CharType>(w2);
                        state = 0;
                    }
                }
            }
            from_next = from;
            to_next = to;
            if(r == std::codecvt_base::ok && (from != from_end || state != 0))
                r = std::codecvt_base::partial;
            detail::write_state(std_state, state);
            return r;
        }

        virtual std::codecvt_base::result do_out(std::mbstate_t& std_state,
                                                 const uchar* from,
                                                 const uchar* from_end,
                                                 const uchar*& from_next,
                                                 char* to,
                                                 char* to_end,
                                                 char*& to_next) const
        {
            std::codecvt_base::result r = std::codecvt_base::ok;
            // mbstate_t is POD type and should be initialized to 0 (i.a. state = stateT())
            // according to standard. We assume that sizeof(mbstate_t) >=2 in order
            // to be able to store first observed surrogate pair
            //
            // State: state!=0 - a first surrogate pair was observed (state = first pair),
            // we expect the second one to come and then zero the state
            ///
            boost::uint16_t state = detail::read_state(std_state);
            while(to < to_end && from < from_end)
            {
                boost::uint32_t ch = 0;
                if(state != 0)
                {
                    // if the state indicates that 1st surrogate pair was written
                    // we should make sure that the second one that comes is actually
                    // second surrogate
                    boost::uint16_t w1 = state;
                    boost::uint16_t w2 = *from;
                    // we don't forward from as writing may fail to incomplete or
                    // partial conversion
                    if(0xDC00 <= w2 && w2 <= 0xDFFF)
                    {
                        boost::uint16_t vh = w1 - 0xD800;
                        boost::uint16_t vl = w2 - 0xDC00;
                        ch = ((uint32_t(vh) << 10) | vl) + 0x10000;
                    } else
                    {
                        ch = BOOST_NOWIDE_REPLACEMENT_CHARACTER;
                    }
                } else
                {
                    ch = *from;
                    if(0xD800 <= ch && ch <= 0xDBFF)
                    {
                        // if this is a first surrogate pair we put
                        // it into the state and consume it, note we don't
                        // go forward as it should be illegal so we increase
                        // the from pointer manually
                        state = static_cast<boost::uint16_t>(ch);
                        from++;
                        continue;
                    } else if(0xDC00 <= ch && ch <= 0xDFFF)
                    {
                        // if we observe second surrogate pair and
                        // first only may be expected we should break from the loop with error
                        // as it is illegal input
                        ch = BOOST_NOWIDE_REPLACEMENT_CHARACTER;
                    }
                }
                if(!detail::utf::is_valid_codepoint(ch))
                {
                    r = std::codecvt_base::error;
                    break;
                }
                int len = detail::utf::utf_traits<char>::width(ch);
                if(to_end - to < len)
                {
                    r = std::codecvt_base::partial;
                    break;
                }
                to = detail::utf::utf_traits<char>::encode(ch, to);
                state = 0;
                from++;
            }
            from_next = from;
            to_next = to;
            if(r == std::codecvt_base::ok && (from != from_end || state != 0))
                r = std::codecvt_base::partial;
            detail::write_state(std_state, state);
            return r;
        }
    };

    /// Specialization for the UTF-8 <-> UTF-32 variant of the std::codecvt implementation
    template<typename CharType>
    class BOOST_SYMBOL_VISIBLE utf8_codecvt<CharType, 4> : public std::codecvt<CharType, char, std::mbstate_t>
    {
    public:
        utf8_codecvt(size_t refs = 0) : std::codecvt<CharType, char, std::mbstate_t>(refs)
        {}

    protected:
        typedef CharType uchar;

        virtual std::codecvt_base::result do_unshift(std::mbstate_t& /*s*/, char* from, char* /*to*/, char*& next) const
        {
            next = from;
            return std::codecvt_base::ok;
        }
        virtual int do_encoding() const throw()
        {
            return 0;
        }
        virtual int do_max_length() const throw()
        {
            return 4;
        }
        virtual bool do_always_noconv() const throw()
        {
            return false;
        }

        virtual int do_length(std::mbstate_t
#ifdef BOOST_NOWIDE_DO_LENGTH_MBSTATE_CONST
                              const
#endif
                                & /*state*/,
                              const char* from,
                              const char* from_end,
                              size_t max) const
        {
#ifndef BOOST_NOWIDE_DO_LENGTH_MBSTATE_CONST
            const char* start_from = from;
#else
            size_t save_max = max;
#endif

            while(max > 0 && from < from_end)
            {
                const char* save_from = from;
                boost::uint32_t ch = detail::utf::utf_traits<char>::decode(from, from_end);
                if(ch == detail::utf::incomplete)
                {
                    from = save_from;
                    break;
                } else if(ch == detail::utf::illegal)
                {
                    ch = BOOST_NOWIDE_REPLACEMENT_CHARACTER;
                }
                max--;
            }
#ifndef BOOST_NOWIDE_DO_LENGTH_MBSTATE_CONST
            return from - start_from;
#else
            return save_max - max;
#endif
        }

        virtual std::codecvt_base::result do_in(std::mbstate_t& /*state*/,
                                                const char* from,
                                                const char* from_end,
                                                const char*& from_next,
                                                uchar* to,
                                                uchar* to_end,
                                                uchar*& to_next) const
        {
            std::codecvt_base::result r = std::codecvt_base::ok;

            while(to < to_end && from < from_end)
            {
                const char* from_saved = from;

                uint32_t ch = detail::utf::utf_traits<char>::decode(from, from_end);

                if(ch == detail::utf::illegal)
                {
                    ch = BOOST_NOWIDE_REPLACEMENT_CHARACTER;
                } else if(ch == detail::utf::incomplete)
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

        virtual std::codecvt_base::result do_out(std::mbstate_t& /*std_state*/,
                                                 const uchar* from,
                                                 const uchar* from_end,
                                                 const uchar*& from_next,
                                                 char* to,
                                                 char* to_end,
                                                 char*& to_next) const
        {
            std::codecvt_base::result r = std::codecvt_base::ok;
            while(to < to_end && from < from_end)
            {
                boost::uint32_t ch = 0;
                ch = *from;
                if(!detail::utf::is_valid_codepoint(ch))
                {
                    ch = BOOST_NOWIDE_REPLACEMENT_CHARACTER;
                }
                int len = detail::utf::utf_traits<char>::width(ch);
                if(to_end - to < len)
                {
                    r = std::codecvt_base::partial;
                    break;
                }
                to = detail::utf::utf_traits<char>::encode(ch, to);
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
HrsVSiY9Rz9vvSSnKNZU9q476ygAfuIvwfqhsZVOVlaWAB0DQzW47QFKvCOo+u7T2wIGjWomLjb2NAB/QlAnGkvXs1Y6vrA8Rdf7pf2ksOiMGw8XN55Bp6OltLlZ7fV2jAELEtRPJjK0B9sBoA7uu8jGGv4SNIg4/vsO4R4vZbVrVu6pMSY0UoMykp0h4u5PrUGQ48PpQjO51KnQvyOrtp9oigXE0ERpkwO6LHFqqqrJdQ5HkxRq1Tp8StraFznW7gEBAbffF6HotT+MQoHihWYDMQ6qR1v5zyBCZuyIjhagrvXnUv2PBkbnil1WxgtuWtDccgft5Fk3wdJChVo1YXVFxRps7hFKPDzTUD6VyoxsR3dfQUHBF7fPp6eXsfHBtuPcnStvG7mU0JxHkClkCRXgvjydu5l8LPVKVeU3xcZ5CyFoLuNQYBp8Tb3bSsduBy4u7mRMZKQllpiiEO2mubScHtWacPEdt/u96VKT1do7AQFB9OzsrJ2dGdKZiD0nfhiRaTomZC4Yo+jALl9kefofoH8QF6KR70jdeWl5GUaVrhnH+LvYX2a3jJSJsf0iJCSkr/qaGkYoXxtu0L/sO6WYO0Xm6YtOL7cH+efnljajAdaznRVx6uNp8D0kpJgtxQy6rdJxLIIXe02eB9Q3r0nOC+NbsunfJp20vbC05FJQU2PLYiCU/xuTkYVYuRG2emdn51OPsWXg6E5sr7dGCn82nRgaxg8upB9ynDHZFS81OyGFQVrpEDA2MoYlx3HH/1vFCcOglvdkvIJytBGmqxm3WhewzNS7E4IhZtZIWr3WbPM0Pz/PmbAiVjCjLdqg72/+sBRPTiC9WqQRtDQ8PFwD3EN59/bJrzedyuZjQEdHt5R2+Td1xLO2uvoq5cmDDhuFxggGqKvHYjSKHakb33Xz8E262mjnqPRtbGgACHKD1JNWEyAAO6cKeZqsPLgADX/i1Dw83rartNsTEx8zER6A3HOwy60UNIBtBSXoBH0MHT9BvfkTx9NePcYbbW/vz+IS+mfcWQKPe6AbNh4eD3E4KYhv1VkitR75SLzvOHOvJzX/sfh1U0PDthDp4uzsLsR2FrE2zS33elMnvuaWTbf8wK/LMj7Q7RoVNzY2tqjOb2M1BLwmdPFsNnVqrb16vxVDXXODbcOjPOAEC4mCK6KH/OuzMDUN5Tya+VblHx2TVVVVcz6auqM5b8eLh/MBiF11+7IuLk9qR1M5S7sXRl5eXulphKgLkM1jg0wiO58CyHsnvLBiilVl5eHKKBERS/3lMZj7C+Xl1N/XMbhYzAKDwrPS8TJsVB6TNn42mkSD6kviEOaB173ESudqL1/Z1Hgy3kSuQ4FtCDTS+CzQx2aED3DUDunfwa6d/vjx/OF9+fSGpnLJZrH4frI7GPEekaMyLe/tVcTU9cVg83HcsHTG12m90faBvWVRQQEeGYoPGND9uERCDyvFERk7UQ4NRWepf+0XtYzfhYC7Cw9Tv/vLer75JLvWtZGAwkBz/UcPU1bNniTB+GUqvTiMIoMDDqH9ycpsrfkN3fA8kXbsDQVObSeSCVqY1r2PumOxWjfH62T2Rwkx9I05B0jPUBSegIWFhYPn55i5/tGmSAbi12MrS7P1hnlFdfWXMjI4VxrdkZbsY48RYBI4Nuq6lKUjUQygodEYR/G4YfdnjZobIWXHuQnfysA8/A+y1ceLIaOBMdgO+H5KMGQllYm03R/IvlP4iEKWa82axNv/CKO888WcKASNjiFjTrnh+aTd3NySd4ooR0kHxHvj4iHgAWysrJ7ep/NUO9M2znXR0dEOmk2WL+i1OwEtVLc38iFl2mE6kk+rq+b6rkbkv131rawaY5WJ59Kp/iwVp3YkuTWSegV0HrgGkcUZ79iCf8bF+c/XfnIeiYoCQbjFwRHzQUl9exC0OXLPuDngwcLzXb+VR08vd6ADuOsv/5Qp34cmz2sH3UPi8MXJMGEJRjaUKioKA/IbpCVZNZGLmpBmwbPfO/2q5tbBYXk2nLn5ZHWqgcj6rs6ttgjD2HqSK4jsFHdrehpBLiJZTwsKOg2Seewn9DpAcACkfxohC28A4ReKirYpxH8mAv+lM+0+7LNf9tmUxkJtTqT5hb5qiL5ADxIRQPjiomrE0acdVyqI+RW79lS7JBEuo/Z//OE6oHBGUO+HHVkGE60CupnQv9gNPJpsQfxE5VeAdVexGGQK8bdVZKL5tdpdaQ9HHiysr2shh4neYhu6AFxnoZdFZfpExP5NKIZWbAN8gbC39hsV1CkONvI2rl191Aza59TDY9qmTXvw47NmljqYR2KimZx8xti8u86tMkNJDNKWg7CEKBzNXH7Q4JNhnHa/9GyhI1sZu4BMe64IiIh1YFCIyixDl+kqIumnBu66qAYM7TERA0uAe9BSrUfXVhkO+CtTPVruLT264cn4ZD4dHQNr5+1P6KM05oyUQbfvIaPLJ8cczQXRiMuiEjC+aU6YCJWxdldPvB7gpAAFl4rHXD85eXEREgKJfzZBrzZlHdXx+XiIFySOBWLjZQb63rC+/SClJiftvXCGApiOBJh7gOyzDI2q0pap25dcVbk40mKncdTU8U7Gi4kdRDJB1DLVd9Z7SmekiLmhzECW5HeIi+qz6NDoyMgSDgaQabQMYcn+AnDAky1vbGw0tdbeCAj4XLClLpEUuKLE1be2tl5v9wasAe6RZ04TqUl8etyZGVI3schIR4w6bk9Kcj5xBdVOCwlBfcUHIH/v7dgWtvtML71R4igaacSTKzpy4ueTh4eltDv2TztqLxUoaquxXcRl0w9CvERo05uknag+gjzDxjDOX6GPHxoz6WDRa03j4uEtmLJykwkVDw4Oup4UpVxP8lwJKibuYQvQTnUcPeyEEB123AzhZThpp/wFpGQnJR2sdXm9RX28PW05tm8ACVkr0wF6ZL7UgO3Mt4K2TSL4IChH7RxGQ/qSXRSxmR/cA5a9JC0QQ5iMQ+SROQhBJEUhfr6Udvx/bfn/Yosz4i4EoKgg/GIVj6UMjwdeUCeK1qojB+I7PDkBsA5LGVc7/gEt0OvnZNYClml5hDKW5l3lWGutuHzlALd7aWT5KKS4O6JCkJKRTCh6sIa2zEOYBu+8jjduu32HQTBk7DfG63XIZ3KhDE8LPhNMq2Si6D/9hUTTiRmRDC1JDGkpqOiIfOsdFBDSazpn/7P4dpugY2APW2lQTRtTWre4l4g3p+h+98CqJUz0duhESsArmw1avpcZPDSJO2GXP/4F2hKmjnzK9m47/r8ax9VSyUJRglCKWma38Q7km+1R84cvo/9msRIDYJKyl5VY8v/wPGyFRM4AeQ4x/15Sp0xYJF98gQEgeSMbbGgFd/7fYyLA//EMpI+y4v3/1tH9t47uv3V0/62j+28d3X/r6P5bR/ffOrr/1tH9t47u/zt1dAJI/yvd3tHplom+0Pr1xdXo8sDeOc7fDw/PE0rsr1kVTmqAyjhUut3liYGGECYUJUMeOoSdMjxFZ1710z2K5AYXXnwQ/EdGKGj4eT//OKOmi/xV4xJXt0C5Sao+wG6kcumso013Q/vjpPzJIfsu84hWDtvwmRe4OxghBiADsIIovHY2EvR8BsFh/b0h4h3SfjtWfGjuqNkWKN9ylK+H1tvXv28GWe5+61L8UvzY+Q7Syz+rEM4+C14jsBgQwbBB9Ry7UxAA7SDnWi22eR9Ehz7KH3QMtDVf/e8eD0B8cR/g5Zv4ypf+p8TCt8FsHM1SAE8BmAw6nuy+K/jALA1t7ax/VVX00P7bj10+2z1+Csxp8GdtXSA91IBqBq0WhTfY3hwEvSZdpUk+w/HjW0WnJG+p/Vb+M5sTWsv1rfSVFOmOtYrugyCIVTVob27fFZCwDLdJSV1PraR/o6Anc1vL1uhLjekrnWYmxlI+K9/XYqZL8nwC+CsTb3OYqpiwy8b2UE4Z6vVaaUU3+FHJU1eWXcX/oY23aKarWKQG4gnXw5ozxcFEGGPyn2RN5xVPdL+LoyM4Nzf3buJsN5h6l+1On0u38KPXa1TtbT0FfBkD3pwCxrHXVp326vqiyjuw6SIs37gDTO8lGQuz4w2jTg1EC6C3Oh3K+DHgzsWbJ37z1GXDHWl9wtrYfTGdABFRBajxfPIqUPUOOn+7N5wZPRE5lQg+O8N9vbcCFl9cVK42HcrHJxdVf/9sKdiJphsVqsZ0Jj8CoGW/bgcc+V0sOzK/uAgbydR91gbryw+276Zz5LZ5fn4+32S1dqhb/1euwFjjC2F7RSwCc4YB/is9hAHUdqTjxCSHw1gr64/qz35WbXRYTEq+58beXFCxHUXK5eWFWUOBt8nyjzDPS0XAlPXLhJWuus+y9ho9JOORhIm4STbv+hUNXDijFZbYhJ8M0mZ7rG4g7Q3lMaJzA95j/JOSVRbEEwpg6tJNL/JtcEe+Fbsns36S1+fwWLHAc0cBUGxWUHpiu/G5VC0c9wM9nHt1FXHZx+MqqkmY5APa18TFSv0t6B6L7s8ASCqF1OwXz8t+wlMUDkuxuopKUVsVTXvV2dmT4uhdhxA0FSGnbY9Gu7PVSrFchizAR73BdKZC158PSk/HjbFBb7N1LhjeJjTczxe63zZuCs8rZ48T0c8XXOMwbiRVvb1IzsP5oN0G7Lk/eWv98TRFbwosVQ1j2+ZjR6O2LY4tHPsahpEOq3W3Nzj5CPq9HKCxHzeypl5fUfp1e8VHA6DduOtJFfCGeeT1dfMT3F90mExXUVNTo4F858cuDvL8zLU5ckP0XoDSwIybwKjpbNXwubry0QHRO6lCsPh6DsLv6QuCw8MxVIvG57qd16j/+0NZpbLGiueS8xe2r20hw74bPxm0MK7g0tbXp4vZRDobGWVRM51Oh+vgUetzrdpHPkqkttuJT5b32ZI8EQErPFTl25ytNiEogy8TJKQvky+yL4A4sMcOQVkFAiWibLmmcc77fMrmok7rSEJT9/3maJbIHXiYp3c/evYrbOO1kmrGV79teUsRYAwOCnwwY7k394hpOsulvhThzd/e03Z768II2ygW8Wl46r2x8aF/BsoTwG6P/v6V7X1GVZKJygiPBoXo2MtKEMvvFUNAUngPDQ1eWhpKgotQ0OpW8nH4vVxy1n6TaOf/OHY4+TZz259AO6Qcz9sRnineO1k4waI9TpQlp7Fo+/RvoVXRBwuLzTZsOm7EX6IJeFTRhHX+dLjedE2N+BQPwHV3HLxXI+VwNknLFrE6Oh+SXI8qLvNsu2E9iJAqoIPYfDh4fCb5fNyhIN/OLmL5dFw53ArIY7bobrLUd5wE7ggxpbFPp82T3PahrPAk+pPBi5SDKRgRVldfUPF+CZ2iIF8WdSJFb71xveQA73YZuu02xeQKxKOQPdzrji9/9epnsyPuyAMYpUnGQM0taPIomfmftwP6oCxU+UG3i7RzvBueUgl65L1vE8zwgXzeO0FY1oQc1pkG2OKBStTeVV0QJFW0YyuO3Fkeny9HEubpj/sfT1tfu7WZPIe3OfIJrjtlUNU5LOW0/2x5XMiJI6i1hraVIEOUWiIRfHtQQLPJkKUHm2jn56HyykkvvbxfNpONnjrXdLruUu/xbD4c02lt5b/XtrGKcb6CzucTwsmiLei2ONsKvnW94j1ogtsdBlyIp+XKpfwgzZ113cYus38aruL2fDxkSY5uKOT23G5OaBhyOKjRYeMPCd4EOQkbntJxwIyvB3Y+fDe3vs8vDFAIf32lLi33T9F1y/uRdPqn4W0OKUbqi0LgZUSlvHzTc8Np6SJUlJRkjrU/kunz7vqIc1IV/Uen8RjmXuOSDp48VZbP18dTNbf4pxrbAI3369zZX6QFVryLSrfQePAQZs75epA/9qBQV51HqW7RvhTgxZX6A8P2RnWQnXtLMhl0S61ma2MuVf9pzjFYJIaky10oNEfQ4GQeCw6C+LDcHqI/lbR8B77N1dNgGYmPK962XXP1MfX5dy5va+1p+KYiOu5roVb9IH+MobNJaA6+ockZFB9qyHYakjFWQEI6OtcILLINm60OpVUru/P+tn6iysLH5qmEqOpVFsr2KMslmzR8t9q6ZSd44sZVq9Yq44riwQ2p747XSXvJ87L16BQtbOAO6VshFKNs74sEeIrGiVxveq8mceKk0fUy8PFH9drRVW3sSo/AKXt6Xqm7hx1i3RDjt/nCeaHGFpk8lSGyPR6ItC2cLTsN366uuMq9+5EE+NlOsXQ8D78Q8LIlT2pkkdrkQNYgaLEYtdl7YGwzoQR3AVLEsW6CuyBxYLRLQ6X6KO/2L36XPuwml6YvX7/eJ2Z2cjzLT+G6XC+ctr67uCfOoPNn9k2O3CyCIujpxQQQExdtCfXYgePfCP/OhhKPMu87q/4q85i6nHA533zeUXy4atmLrhgbG6tu3wnG++OWnaK9dNAF76OIvmHEbMb7tO6wZ7X2eTnl83mHFD3qc+mllsNrfx7AoeUoflB1aC2Zj9Qko5/ckkEfdDHLTyEo2OPg2+O2/mOThnRKaBtaNI1UlbCHoPtPG8tvWq3Gj6T2mPKt6wCnpUz+8vNeoomqStPNhOCBiBozBpcee+x/qB7SUKreaRSET6gefmDkOJQxL7Z7PlcrC78dq8w17PtOC25zbGfZ+tOHBJ4rbbza81vdOLSwiiz4TMEavi1FJQV59gjwLGJJjP9Y0MEbjpXt455SfFS9+nGSviDhCGje8vbIZHqcy7Buo/qjoTGiteQUDZnDJA5Nco79B2zTSftmRoKIoMpsdQOJ735aF+mpVTGFNjpgJoff7iyKw4lwGDU6lJEAdswpT4OedS1Iv33aEipZZEcJdrQjAtMNsa6nnwFG4QdhOWUPxW0sBGKyscHysT3v9ZnAhdXJZUftCxIcUoXA/mHMrp7jDE1zZPeJoAlI4I3XNluGkAugX3/aCnLsAb4nyARAKkEM56sLrhwniAGDDhLr1uNMG2kevt20dWm+smG1XvM1UubD53kgwIY4hOn1VLxmzT29CNN/fwtPb2yr7XzNZaiDvX416RDoGh0rQYVK3RjMC6KPbgiM6ZHp/nCSKS95C97IqeL/93nRvMUvorKQQ6deo4c1dcdedM/iAAXUAws8csurqIjgfZj/zRcY60Hkfpy3j/I8ZVpa6n5YddbN5zj1CE4uFXyicPzjMP0g35SLkaB5HxwQzXhdNFodDooeF0J9+w0C9eqmZFxcxSrV6yvOJBt059Lqs7/vfzoqV8j2eD7dQZhon0OGgCmGw44G6tbjhLPrcftqlyfydkB+a3yOZC40OH9vvd9msC8KVqMKiNbr8mGJYIvYW05mOi/oF06t6aCDmo6XV//iBE8v9BJww+IaW2spAtRU4Lmw+TYFt0/nsnMKQ0PQShvD+2G+X94vVqxdQDuL9x9Yy0Gyprf9t/f+lcpsLD1ph38hmbRlh9/rpO3H9BNVmFYIGT/7aGPKFtSeOwuR/3HZEI2yCCjwelwQgOpARt9xRPG0aTvRiY9tYub7t5VSHRG2OKDDrMCUe5oWSqw/0PjP9ZurERuWP7EwKsRwvq8vKTExHPQIqX/dNhd43HcoR302WrM9o2tTT+DxHv3V6RLr/fHw1XYUhgdk2N2xHyQNOASIReTpgbhFCNfzitSUYTlAGSGaTVywiGoQX8uAg8QRk6OBk/cwoJSCCoZGtK0SV70eFF8UywGb+T1Oc9/YHPvKnrS8VxAiBKFTJI22W/4pU1ousYACjb3ohG0EYn19bY/PQMN4ofwoinb5nkZIcYMXd05KCDcu2yaf+XK6BAR9ev0h8IF2OZv2Y3R4ZHGS2UrmhFElZ20de5yghrKkgcu8Uzz+xJwS9qD+xKUWS1UInY+rFnhEHue1b0gfPcNX74loEHZ3BXBVRHMLySD6oKxrFdduc0KTDYqMBOjwUMUXPXUEnNFRNaMFpe2xRjDeYsHUMNdjoP51ob60xArmyOQYucT3JVMfhyU8uu0233g6Fjpo7TN032fsCtYQ93uxBXx9Jo0ol+HFInod1XX70RTd0GVhGQX3U4/efxBT2oE9v32A07u+fpiwM5h/PPhscFDuuL6b8U7BZXS7zPnP0Hms5WY4E73p8NRory5BGBRR5nJ8zeHdwHQcvQ96n0Nk53Z0wOtFdr23H2FebLS0yXczRAj4fL6zlJeXF+c4zkpxLTm1w5C4CUvuTBu4QSmiF/EiQyuP1OEvOWURXtZ/wBn+oyCMKZEX+LjParLaYqQ8sfvUNvG0ei982SnNYQkX3HScLtA8nsQznTLjjJ2ZyZ6Zzh717xkIuCs2OOlzqDkulzoeMZ7O4phOmpuJW5jJXphJW5pRYfxuNJyGiI0WO3HSctIHF/zbosZ7Y6FiMpOp1tOb96fDC6jIJugst4hLXF6B4Ey2iSmDwn0qvHdQv7ZuzE5YK0bLwzolvnjsdMeU8wEVNyx6FkRw4KGXxCao1iiZZo3t02B/eqnZOmPLrc/FOFMBxUR1adkuahgtLRDODWEtyNoNRWHGNi+tCsvLV4QSHxQCaU6fEhdqa0kWqu2gr4GSNqPPmZK1XzyvdC+jnt7MIBJ+ttnqLXjue81iwksozzLkzh9RUnWmnHzgSoxcqoRetF5Ha6CR7BQ4daS9dMF/Uphgr6KiMnc0leMzlPc6X2fzPzKaOHB/C0xzc0WNfTzuIctTx91mz912B+luj0PbZo6aTM8LhTSZAQuKdlFGu8ryQ3PEbPPIEc5tzk8RvE9R4KnxJuEQSeCrqve12K5/AwvJYhSTtiXxai9n2nfS3wRM2y38klRE2NAWu7fySPxmYB12/eEB+x02hHCuPu6x4+nlkvRsL4eBccCQmcPQ4OW9rUIti4sznpTD02Hxh1xQPuJEjT4PIc9cPqHPnN/fNq9MuRA/f4YVANSY2NZb+sFKpH67l3OipJGi4u/BKBw+s89pGF0eh1iw3MTJLBaTSZAlJyRb/BI7/BKiP/D9ucVm4XkKpcLI4NHIBmH5lNe8DMtNF/iXmd5iBYk/v4Og5Djyk+Arn6+3056fQZMfr/cJuyuJfv4nxJWakujwjocIjsYIjkfwjkUOsRBQ8l/b8JEWkaCAX7i/w2D6DYYxHY2c4Pgg0EY6/Ko6/C79w4xmRIdqYjmsUsWC04NbsJEkbAj4zyZBXuftDif5StiTpXEpVwWHrgU=
*/