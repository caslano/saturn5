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
kcjuvVFF9kFi4BX3KWrw6KiHDBfi0RMi+Q1iQb5rJgJ2nSinwfy/kZDaV8VIU/yNKr6DWFaa1POtEIZBecDBMK+LLx34BgxRTma8CCkoXmNH1Vd1pVIXSX/kIqkun/mRy2dO5PKZFVoKCXXLzkO3ICPhxOGrwaEqLTC6ShBTv7/IpxHwjxxRYeL8qRoRwbY8EgVLl6OZbECwVxERAgaOCtblkagwfjkyG+qaCmvpbVmwpqq3gNW+VnkiZ6ZJlQVo6Ptyv8QnTIm+YB9bcPBfQpGC4etSlAV2cDSsKfiJq9pe8CxJl64KSb4mmPLLZUgy3gyT4zvptBKb557AUXTjskgUvWOZOn++J4LwJhurj0rZAlIDJILYxDLkhE6RHrzy169Yf5q303zHvarfMFLgulWUk4KHPRc0m2tkMywiOr+zsLsp7lVk3X362MAsRNOWC6EZmKPuM1HP/z2YMu0mshtSFTkFj4JPjtH5vTGBTM81vP9HSXIMMZz8lWpbGRsUIh5yVeTI+apC87OxKrLxriqVNVyLk6KBbSwx3r/t7ei7XokxeKj+gIn2RbNhiVd+it/ymOs72HXrM65U4hVvsgZT5mONhWMyIMoNTHriOwcQF2cndBAniDe4JlWpcoHPcM9LpJxm9xq+hS9zlb/dUI9PRs83oP7vf71EeWvIMZwGx5t4E/0ufwmPQBfj84qCoP3WfB99exNXhNK0
*/