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
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
*/