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