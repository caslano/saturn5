#ifndef BOOST_PROPERTY_TREE_DETAIL_JSON_PARSER_NARROW_ENCODING_HPP
#define BOOST_PROPERTY_TREE_DETAIL_JSON_PARSER_NARROW_ENCODING_HPP

#include <boost/assert.hpp>
#include <boost/range/iterator_range_core.hpp>

#include <utility>

namespace boost { namespace property_tree {
    namespace json_parser { namespace detail
{

    struct external_ascii_superset_encoding
    {
        typedef char external_char;

        bool is_nl(char c) const { return c == '\n'; }
        bool is_ws(char c) const {
            return c == ' ' || c == '\t' || c == '\n' || c == '\r';
        }

        bool is_minus(char c) const { return c == '-'; }
        bool is_plusminus(char c) const { return c == '+' || c == '-'; }
        bool is_dot(char c) const { return c == '.'; }
        bool is_eE(char c) const { return c == 'e' || c == 'E'; }
        bool is_0(char c) const { return c == '0'; }
        bool is_digit(char c) const { return c >= '0' && c <= '9'; }
        bool is_digit0(char c) const { return c >= '1' && c <= '9'; }

        bool is_quote(char c) const { return c == '"'; }
        bool is_backslash(char c) const { return c == '\\'; }
        bool is_slash(char c) const { return c == '/'; }

        bool is_comma(char c) const { return c == ','; }
        bool is_open_bracket(char c) const { return c == '['; }
        bool is_close_bracket(char c) const { return c == ']'; }
        bool is_colon(char c) const { return c == ':'; }
        bool is_open_brace(char c) const { return c == '{'; }
        bool is_close_brace(char c) const { return c == '}'; }

        bool is_a(char c) const { return c == 'a'; }
        bool is_b(char c) const { return c == 'b'; }
        bool is_e(char c) const { return c == 'e'; }
        bool is_f(char c) const { return c == 'f'; }
        bool is_l(char c) const { return c == 'l'; }
        bool is_n(char c) const { return c == 'n'; }
        bool is_r(char c) const { return c == 'r'; }
        bool is_s(char c) const { return c == 's'; }
        bool is_t(char c) const { return c == 't'; }
        bool is_u(char c) const { return c == 'u'; }

        int decode_hexdigit(char c) {
            if (c >= '0' && c <= '9') return c - '0';
            if (c >= 'A' && c <= 'F') return c - 'A' + 10;
            if (c >= 'a' && c <= 'f') return c - 'a' + 10;
            return -1;
        }
    };

    struct utf8_utf8_encoding : external_ascii_superset_encoding
    {
        typedef char internal_char;

        template <typename Iterator>
        boost::iterator_range<Iterator>
        to_internal(Iterator first, Iterator last) const {
            return boost::make_iterator_range(first, last);
        }

        char to_internal_trivial(char c) const {
            BOOST_ASSERT(static_cast<unsigned char>(c) <= 0x7f);
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
            unsigned char c = *cur;
            ++cur;
            if (c <= 0x7f) {
                // Solo byte, filter out disallowed codepoints.
                if (c < 0x20) {
                    error_fn();
                }
                transcoded_fn(c);
                return;
            }
            int trailing = trail_table(c);
            if (trailing == -1) {
                // Standalone trailing byte or overly long sequence.
                error_fn();
            }
            transcoded_fn(c);
            for (int i = 0; i < trailing; ++i) {
                if (cur == end || !is_trail(*cur)) {
                    error_fn();
                }
                transcoded_fn(*cur);
                ++cur;
            }
        }

        template <typename TranscodedFn>
        void feed_codepoint(unsigned codepoint,
                            TranscodedFn transcoded_fn) const {
            if (codepoint <= 0x7f) {
                transcoded_fn(static_cast<char>(codepoint));
            } else if (codepoint <= 0x7ff) {
                transcoded_fn(static_cast<char>(0xc0 | (codepoint >> 6)));
                transcoded_fn(trail(codepoint));
            } else if (codepoint <= 0xffff) {
                transcoded_fn(static_cast<char>(0xe0 | (codepoint >> 12)));
                transcoded_fn(trail(codepoint >> 6));
                transcoded_fn(trail(codepoint));
            } else if (codepoint <= 0x10ffff) {
                transcoded_fn(static_cast<char>(0xf0 | (codepoint >> 18)));
                transcoded_fn(trail(codepoint >> 12));
                transcoded_fn(trail(codepoint >> 6));
                transcoded_fn(trail(codepoint));
            }
        }

        template <typename Iterator, typename Sentinel>
        void skip_introduction(Iterator& cur, Sentinel end) const {
            if (cur != end && static_cast<unsigned char>(*cur) == 0xef) {
                if (++cur == end) return;
                if (++cur == end) return;
                if (++cur == end) return;
            }
        }

    private:
        struct DoNothing {
            void operator ()(char) const {}
        };

        bool is_trail(unsigned char c) const {
            return (c & 0xc0) == 0x80;
        }

        int trail_table(unsigned char c) const {
            static const signed char table[] = {
                                 /* not a lead byte */
                /* 0x10???sss */ -1, -1, -1, -1, -1, -1, -1, -1,
                /* 0x110??sss */ 1, 1, 1, 1, /* 1 trailing byte */
                /* 0x1110?sss */ 2, 2, /* 2 trailing bytes */
                /* 0x11110sss */ 3, /* 3 trailing bytes */
                /* 0x11111sss */ -1 /* 4 or 5 trailing bytes, disallowed */
            };
            return table[(c & 0x7f) >> 3];
        }

        char trail(unsigned unmasked) const {
            return static_cast<char>(0x80 | (unmasked & 0x3f));
        }
    };

}}}}

#endif

/* narrow_encoding.hpp
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
*/