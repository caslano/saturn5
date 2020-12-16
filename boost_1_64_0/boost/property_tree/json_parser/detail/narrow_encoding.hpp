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
lFSPEyP0Vn2s71mXl9p6ZPRBnoiNo171iMfJvSN8AjVdfmX0tWEgyy0RX2Yq1ddryJCxhQxFsw5Cq+F4T86/06P7qmarm/WT+2i6dd02Q767vcZG5GO3scvYAUfL5hA4DcVNffaAUX1W6/eH7m34KCAaRgc83PRfQ5/GdnuOqf3j1QAn0x2/Y628Kvqi9IQSk326B3Um40L06aP37uLzqOmUJ44aS9SWnxM/bZfxqfvmn9WU2ca52A5+CjsuIFl6bpN/Q+++aG/93M/ei18G8NqGt+aPzEruQ395g55uijxbAl9sQ/Qack2xRvfgZhQtIvl+NeuTus3xesBqCXBMwiEq/yZWXjeYZOAtgG0O1vrq+h+K6TOvVLSE+uUdXBZtOUS9bylzBePPntYirgcvgK/8tueS+NOi+zaUtUHhI/U/YNXVXo3/usvgWxXnRzcnzoE/wXoXaRi/a4x23LyCP/3KBKcrv+pO0zbPIYc4eG8D91XXl1LccD7ujLXuf3vCO1vDC9bPrOAWzhoyFB2bB6uFVeAfGNd093F8XF5YCle2htvhikCbarXmFd6D6nj54KxGA56KOz3J8bxVdFiMaq6KG71TOqcyxzm+sjTwlue3ehsZLkKutM9tD5yD4y2F+8hGu9eHG6sDmWnQK9F0lsOY4842cSdYTr7fclwhTxANBfsDh9FN8RsS7C8ctjWQQIi7uqu89qTqrjIilJHvEf2i7qZvxtX3+6+sHxzvI+n/FDIDnEE5BX+yLNevCM5DyDYWBv0Dh1qPJr6v6pjY4APIuYjbOXGG+wSOCPstxF+l+CsQf+Xir1n9Vyr+6ou/jou/Eo1SXcsb19A58VdP/BWKv6bwl46Xvr+KC77E6LjgHPGabgrEQ8D78DVaqCvUeZm6dxNWSRL1Z2FuQPcHfbi3gsqKgJ4X3iJPnR9dBF2HMfy0iDEVV+0xjTfl9218f3z1HVmb0G+LhP831OfJ5jv6EzqT2bVKd3wC9Tme5Oh4xNv5lc/nuNKvnlwXvJidteF3uFWkzkCbR7ZYld+udIzYFdrloXWq8p+5xi7nhgdl3b4AeFo2a3cxYJ8CTISr6r0J6RA8JYu4WpGCZX0HXaT1zvnqO0RnEQt1//TqxoKBXXQZAatug0M2+1Vv3ZB0zsnLClhdNM19yuvfjN+nzDyMdIybYfP6whrhPT25BL9L2w2SDFnZ287s8sb9KSMvmFMxRv9lKGfoF50iLwIE9C8Q4qqi/6rEvqOWIew+SLOEGCzsrKwugYW6pabp/3aB1x/XR+PA7yIHLdFfCAnvvEU/d5BQGM8rJF2iL9OU7GzRveSllS3cv8MdsUZ7XvRgzq8b4YYAbv05A0Jc1O+nWPxixw+QjjQLQ+In81cMG5ymdbusfsMrAm0P/zmniI9+e+IPFp+OE2XtdhKigdQurOVQ5LhHIVLOgd/OcKD6xlG8rtrhvHDFBumZo8TZqN912dux77okkRviJQXFa7gh7jtiAR1src+TPOBOKL6JiHjH9OHbrD7stNu47IRk35vEz+Sd7th5p9te5iVJoPpwG7I82NaygVdpzHsrRr4DS74hHb4fu84Z4rWt7+GBl/Xejd9OU9ymI16rKwtb8xikScp3pu+VqrVj+S3VnQwC6zsArlo7nH8K/arzjm7clL6/ROYQKnCLEltMXR5ZJ0yuufc+fBSOyUXyQQlv55qtyek35gGm6yXtDgW77SMr2Iw3oQtq2PsfUcFgLDdhHVkOz9a4Cqhh2xLWDjXE5LRY7dTeM4i8jpuXmUMtm57Ud0hx+XYcf7L5c/jH2IHDjbwdj7Foecjhi/uz7TBSdzXxI0lp0PR1YLpLw+/uP69j544=
*/