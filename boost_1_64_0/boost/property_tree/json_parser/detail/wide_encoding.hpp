#ifndef BOOST_PROPERTY_TREE_DETAIL_JSON_PARSER_WIDE_ENCODING_HPP
#define BOOST_PROPERTY_TREE_DETAIL_JSON_PARSER_WIDE_ENCODING_HPP

#include <boost/assert.hpp>
#include <boost/range/iterator_range_core.hpp>

#include <utility>

namespace boost { namespace property_tree {
    namespace json_parser { namespace detail
{

    struct external_wide_encoding
    {
        typedef wchar_t external_char;

        bool is_nl(wchar_t c) const { return c == L'\n'; }
        bool is_ws(wchar_t c) const {
            return c == L' ' || c == L'\t' || c == L'\n' || c == L'\r';
        }

        bool is_minus(wchar_t c) const { return c == L'-'; }
        bool is_plusminus(wchar_t c) const { return c == L'+' || c == L'-'; }
        bool is_dot(wchar_t c) const { return c == L'.'; }
        bool is_eE(wchar_t c) const { return c == L'e' || c == L'E'; }
        bool is_0(wchar_t c) const { return c == L'0'; }
        bool is_digit(wchar_t c) const { return c >= L'0' && c <= L'9'; }
        bool is_digit0(wchar_t c) const { return c >= L'1' && c <= L'9'; }

        bool is_quote(wchar_t c) const { return c == L'"'; }
        bool is_backslash(wchar_t c) const { return c == L'\\'; }
        bool is_slash(wchar_t c) const { return c == L'/'; }

        bool is_comma(wchar_t c) const { return c == L','; }
        bool is_open_bracket(wchar_t c) const { return c == L'['; }
        bool is_close_bracket(wchar_t c) const { return c == L']'; }
        bool is_colon(wchar_t c) const { return c == L':'; }
        bool is_open_brace(wchar_t c) const { return c == L'{'; }
        bool is_close_brace(wchar_t c) const { return c == L'}'; }

        bool is_a(wchar_t c) const { return c == L'a'; }
        bool is_b(wchar_t c) const { return c == L'b'; }
        bool is_e(wchar_t c) const { return c == L'e'; }
        bool is_f(wchar_t c) const { return c == L'f'; }
        bool is_l(wchar_t c) const { return c == L'l'; }
        bool is_n(wchar_t c) const { return c == L'n'; }
        bool is_r(wchar_t c) const { return c == L'r'; }
        bool is_s(wchar_t c) const { return c == L's'; }
        bool is_t(wchar_t c) const { return c == L't'; }
        bool is_u(wchar_t c) const { return c == L'u'; }

        int decode_hexdigit(wchar_t c) {
            if (c >= L'0' && c <= L'9') return c - L'0';
            if (c >= L'A' && c <= L'F') return c - L'A' + 10;
            if (c >= L'a' && c <= L'f') return c - L'a' + 10;
            return -1;
        }
    };

    template <bool B> struct is_utf16 {};

    class wide_wide_encoding : public external_wide_encoding
    {
        typedef is_utf16<sizeof(wchar_t) == 2> test_utf16;
    public:
        typedef wchar_t internal_char;

        template <typename Iterator>
        boost::iterator_range<Iterator>
        to_internal(Iterator first, Iterator last) const {
            return boost::make_iterator_range(first, last);
        }

        wchar_t to_internal_trivial(wchar_t c) const {
            BOOST_ASSERT(!is_surrogate_high(c) && !is_surrogate_low(c));
            return c;
        }

        template <typename Iterator, typename Sentinel,
                  typename EncodingErrorFn>
        void skip_codepoint(Iterator& cur, Sentinel end,
                            EncodingErrorFn error_fn) const {
            transcode_codepoint(cur, end, DoNothing(), error_fn);
        }

        template <typename Iterator, typename Sentinel, typename TranscodedFn,
                  typename EncodingErrorFn>
        void transcode_codepoint(Iterator& cur, Sentinel end,
                TranscodedFn transcoded_fn, EncodingErrorFn error_fn) const {
            return transcode_codepoint(cur, end, transcoded_fn, error_fn,
                                       test_utf16());
        }

        template <typename TranscodedFn>
        void feed_codepoint(unsigned codepoint,
                            TranscodedFn transcoded_fn) const {
            feed_codepoint(codepoint, transcoded_fn, test_utf16());
        }

        template <typename Iterator, typename Sentinel>
        void skip_introduction(Iterator& cur, Sentinel end) const {
            // Endianness is already decoded at this level.
            if (cur != end && *cur == 0xfeff) {
                ++cur;
            }
        }

    private:
        struct DoNothing {
            void operator ()(wchar_t) const {}
        };

        template <typename Iterator, typename Sentinel, typename TranscodedFn,
                  typename EncodingErrorFn>
        void transcode_codepoint(Iterator& cur, Sentinel,
                                 TranscodedFn transcoded_fn,
                                 EncodingErrorFn error_fn,
                                 is_utf16<false>) const {
            wchar_t c = *cur;
            if (c < 0x20) {
                error_fn();
            }
            transcoded_fn(c);
            ++cur;
        }
        template <typename Iterator, typename Sentinel, typename TranscodedFn,
                  typename EncodingErrorFn>
        void transcode_codepoint(Iterator& cur, Sentinel end,
                                 TranscodedFn transcoded_fn,
                                 EncodingErrorFn error_fn,
                                 is_utf16<true>) const {
            wchar_t c = *cur;
            if (c < 0x20) {
                error_fn();
            }
            if (is_surrogate_low(c)) {
                error_fn();
            }
            transcoded_fn(c);
            ++cur;
            if (is_surrogate_high(c)) {
                if (cur == end) {
                    error_fn();
                }
                c = *cur;
                if (!is_surrogate_low(c)) {
                    error_fn();
                }
                transcoded_fn(c);
                ++cur;
            }
        }

        template <typename TranscodedFn>
        void feed_codepoint(unsigned codepoint, TranscodedFn transcoded_fn,
                            is_utf16<false>) const {
            transcoded_fn(static_cast<wchar_t>(codepoint));
        }
        template <typename TranscodedFn>
        void feed_codepoint(unsigned codepoint, TranscodedFn transcoded_fn,
                            is_utf16<true>) const {
            if (codepoint < 0x10000) {
                transcoded_fn(static_cast<wchar_t>(codepoint));
            } else {
                codepoint -= 0x10000;
                transcoded_fn(static_cast<wchar_t>((codepoint >> 10) | 0xd800));
                transcoded_fn(static_cast<wchar_t>(
                    (codepoint & 0x3ff) | 0xdc00));
            }
        }

        static bool is_surrogate_high(unsigned codepoint) {
            return (codepoint & 0xfc00) == 0xd800;
        }
        static bool is_surrogate_low(unsigned codepoint) {
            return (codepoint & 0xfc00) == 0xdc00;
        }
    };

}}}}

#endif

/* wide_encoding.hpp
RzFEySn9oPru/VbfQT9EkQsfYU69J9WA6SEYmc2KVEYsYj1U3/3Wal+J8ztfzKfsAu3TurdJfXMe9c2Vr+XGHq8vRBWWXYGHWy5AW8387eF8Xwf1Up/Nq364p0XXw1zAEz9ucqE6V1qEZkVfyhQIO61cjfOTa3WF/MR4U+V/HWdlZ1CVjRx90rN9YGmae7hbeqG+EEsxpy3vf2ClX8Lv9JLQJdTc/qVVfwTjue2g3S1jh09g/ItCW6vAYPkrjSTOlZVM3MpntCAKUelhgfdq86k+o7B7MP1hzzOn5SqZ6Pn1scNLWnkUg/b/KnEYAKel6D7Goutiv5fCzQBZuwBd/NkYpfccdi/wq6+t4tkhNYSK8x51jnNGnlupq/5Sl4zjZRnMWXXOsblZ4eAetTj1qkRPv3f7GAMT76zqM5ZPP1J8Z3lQULLFzqEuludQ8/U3rRV84SyVNzAcxZg3hH++Levd7vTXV5bG8QaoefN5v4EtolK4GgYwdMaQtemLsn4ifWDm94c4FGkt6POhh3AYzgdl5bcV/BZ1eHWKZuC3NXC5A5zbXEItdNu+/sgaPMEjN/iu4N+tw8MVXCyCb0P17VkNFyeBUj4Xzlnv/t/9fvVzTvGoj/T9AjytaJ0kPHMPWr4Uj6ml63OqiQMZMO1ZbcIXt7dWNXzmoRV8CWMt7zrjyY8Wa++ybM/K+JIF12P9AAk396Rb5o7Qj6u+4nloMFaM9mMeWoMTAUX7ng8UcPnu9wLu6UJGtlTfADD67fChoe9c3n73G0ESO0DQ8JOXknB0vkiDQP6XlnlvewL8xdyUjqKhqtcvZbt6s9Wr+mgTu9v0Ow6T7VlR/P4CGPU1wdGZrD/+CTj1tQVXbd7zKEU7m8V91qxyOgr+DOcKo3Bq/XpVjSNyZ1QEcgW7pg0TBTXt6wOmx3p7A0j4v3y0hdqAegCHtxE0RCMSBb8V4KaNBq543F7zRzrG3txsRb3WxolRONRGxeeOhGOqaLfFAdyME7SXvsIGHUU44Ug+wMXxM2KshkCZVnM6bdBbG57GrW06vx4qvJmR4yPw5/FqpcE7sSse6IKease9G3wpkm3F6PulOk7lxzF9cR8ON8+xw4Vi+nPTwqlaVQ2cqu8ZW25MJ/XFHQVT3wc18DC/tiWSwnm4jXMaOJXdA5DGeUwdx9DRdX6ijUOLhZmPT6/DabG4PcGf04SL+kobklQ70KaVvLyoiV/vh22F+4omrtBD9KabQDZ9+zobl9ZN2lFCvyi8t9h45OQ2eKrvzo/Coy5WOO/VOOTJp97jY/DBETg0DXXdPz4KBy2l0CZd98/W8HTvCbsP+lX125d3wTNTzfD+5m641Tm5iU/6fgMP/1TTYGjwfsrnAPrLptzaVv3ya6t/zWQByFO0/tDQTxzP0PqbxhOJDaxYmw1Fq/VojkNzYV6tZ4bWZWw8tJDSgbD+vaiBA3k7t4nGLg3OIMEy79+La7hmbogatgaK77WbeNSE1kDRuuGutOCHAp6q374aXn0+8vrtb+IiMJUUJOvjsQaejj/Ssn6ogUMM0QqFc7SJg6hJHAWBm4rNa4/oC2TguC9GHxsEsQAJuisga+zAuFkGWWcGEJfTmndewyEZgN1p9FmviYNw5WossFyYuD1l/4w/s8LHy7SLm+gv6HC6V36+2rPQzce+dAVIs7Ov42eX+V3GyMGDzsiHBgcHEmdU7tEx9VT6zuIyXVtV5x7YPDogsaho/fS47SvtwGuJB0Bl5Aqu2SP0eW0F/gkqXJmK8q6kCe9oE63zvu1vy7wIjqV896f9JxSF1pLyD3zRr+218Rpj0YmK/+4NYmyYJxaJpLlj+AeLJnwZeYyrQEnhLFI=
*/