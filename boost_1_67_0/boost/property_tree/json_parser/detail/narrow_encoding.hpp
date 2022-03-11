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