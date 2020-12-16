#ifndef BOOST_PROPERTY_TREE_DETAIL_JSON_PARSER_PARSER_HPP
#define BOOST_PROPERTY_TREE_DETAIL_JSON_PARSER_PARSER_HPP

#include <boost/property_tree/json_parser/error.hpp>

#include <boost/ref.hpp>
#include <boost/bind.hpp>
#include <boost/format.hpp>

#include <iterator>
#include <sstream>
#include <string>

namespace boost { namespace property_tree {
    namespace json_parser { namespace detail
{

    template <typename Encoding, typename Iterator, typename Sentinel>
    class source
    {
    public:
        typedef typename std::iterator_traits<Iterator>::value_type
            code_unit;
        typedef bool (Encoding::*encoding_predicate)(code_unit c) const;

        explicit source(Encoding& encoding) : encoding(encoding) {}

        template <typename Range>
        void set_input(const std::string& filename, const Range& r)
        {
            this->filename = filename;
            cur = r.begin();
            end = r.end();
            // Note that there is no backtracking, so if e.g. a UTF-8 file
            // starts with something that initially looks like a BOM but isn't,
            // there's trouble.
            // However, no valid JSON file can start with a UTF-8 EF byte.
            encoding.skip_introduction(cur, end);
            line = 1;
            offset = 0;
        }

        bool done() const { return cur == end; }

        void parse_error(const char* msg) {
            BOOST_PROPERTY_TREE_THROW(
                json_parser_error(msg, filename, line));
        }

        void next() {
            if (encoding.is_nl(*cur)) {
                ++line;
                offset = 0;
            } else {
                ++offset;
            }
            ++cur;
        }

        template <typename Action>
        bool have(encoding_predicate p, Action& a) {
            bool found = cur != end && (encoding.*p)(*cur);
            if (found) {
                a(*cur);
                next();
            }
            return found;
        }

        bool have(encoding_predicate p) {
            DoNothing n;
            return have(p, n);
        }

        template <typename Action>
        void expect(encoding_predicate p, const char* msg, Action& a) {
            if (!have(p, a)) {
                parse_error(msg);
            }
        }

        void expect(encoding_predicate p, const char* msg) {
            DoNothing n;
            expect(p, msg, n);
        }

        code_unit need_cur(const char* msg) {
            if (cur == end) {
                parse_error(msg);
            }
            return *cur;
        }

        Iterator& raw_cur() { return cur; }
        Sentinel raw_end() { return end; }

    private:
        struct DoNothing {
            void operator ()(code_unit) const {}
        };

        Encoding& encoding;
        Iterator cur;
        Sentinel end;
        std::string filename;
        int line;
        int offset;
    };

    template <typename Callbacks, typename Encoding, typename Iterator,
        typename = typename std::iterator_traits<Iterator>
            ::iterator_category>
    class number_callback_adapter
    {
    public:
        number_callback_adapter(Callbacks& callbacks, Encoding& encoding,
                                Iterator& cur)
            : callbacks(callbacks), encoding(encoding), first(cur), cur(cur)
        {}

        void operator ()(typename Encoding::external_char) {}

        void finish() const {
            callbacks.on_number(encoding.to_internal(first, cur));
        }

    private:
        number_callback_adapter(const number_callback_adapter&);

        Callbacks& callbacks;
        Encoding& encoding;
        Iterator first;
        Iterator& cur;
    };

    template <typename Callbacks, typename Encoding, typename Iterator>
    class number_callback_adapter<Callbacks, Encoding, Iterator,
                                  std::input_iterator_tag>
    {
    public:
        number_callback_adapter(Callbacks& callbacks, Encoding& encoding,
                                Iterator&)
            : callbacks(callbacks), encoding(encoding), first(true)
        {}

        void operator ()(typename Encoding::external_char c) {
            if (first) {
                callbacks.on_begin_number();
                first = false;
            }
            callbacks.on_digit(encoding.to_internal_trivial(c));
        }

        void finish() const {
            callbacks.on_end_number();
        }
    private:
        number_callback_adapter(const number_callback_adapter&);

        Callbacks& callbacks;
        Encoding& encoding;
        bool first;
    };

    template <typename Callbacks, typename Encoding, typename Iterator,
        typename = typename std::iterator_traits<Iterator>
            ::iterator_category>
    class string_callback_adapter
    {
    public:
        string_callback_adapter(Callbacks& callbacks, Encoding& encoding,
                                Iterator& cur)
            : callbacks(callbacks), encoding(encoding), cur(cur),
              run_begin(cur)
        {}

        void start_run() {
            run_begin = cur;
        }

        void finish_run() {
            callbacks.on_code_units(encoding.to_internal(run_begin, cur));
        }

        template <typename Sentinel, typename EncodingErrorFn>
        void process_codepoint(Sentinel end, EncodingErrorFn error_fn) {
            encoding.skip_codepoint(cur, end, error_fn);
        }

    private:
        string_callback_adapter(const string_callback_adapter&);

        Callbacks& callbacks;
        Encoding& encoding;
        Iterator& cur;
        Iterator run_begin;
    };

    template <typename Callbacks, typename Encoding, typename Iterator>
    class string_callback_adapter<Callbacks, Encoding, Iterator,
                                  std::input_iterator_tag>
    {
    public:
        string_callback_adapter(Callbacks& callbacks, Encoding& encoding,
                                Iterator& cur)
            : callbacks(callbacks), encoding(encoding), cur(cur)
        {}

        void start_run() {}

        void finish_run() {}

        template <typename Sentinel, typename EncodingErrorFn>
        void process_codepoint(Sentinel end, EncodingErrorFn error_fn) {
            encoding.transcode_codepoint(cur, end,
                boost::bind(&Callbacks::on_code_unit,
                            boost::ref(callbacks), _1),
                error_fn);
        }

    private:
        string_callback_adapter(const string_callback_adapter&);

        Callbacks& callbacks;
        Encoding& encoding;
        Iterator& cur;
    };

    template <typename Callbacks, typename Encoding, typename Iterator,
              typename Sentinel>
    class parser
    {
        typedef detail::number_callback_adapter<Callbacks, Encoding, Iterator>
            number_adapter;
        typedef detail::string_callback_adapter<Callbacks, Encoding, Iterator>
            string_adapter;
        typedef detail::source<Encoding, Iterator, Sentinel> source;
        typedef typename source::code_unit code_unit;

    public:
        parser(Callbacks& callbacks, Encoding& encoding)
            : callbacks(callbacks), encoding(encoding), src(encoding)
        {}

        template <typename Range>
        void set_input(const std::string& filename, const Range& r) {
            src.set_input(filename, r);
        }

        void finish() {
            skip_ws();
            if (!src.done()) {
                parse_error("garbage after data");
            }
        }

        void parse_value() {
            if (parse_object()) return;
            if (parse_array()) return;
            if (parse_string()) return;
            if (parse_boolean()) return;
            if (parse_null()) return;
            if (parse_number()) return;
            parse_error("expected value");
        }

        bool parse_null() {
            skip_ws();
            if (!have(&Encoding::is_n)) {
                return false;
            }
            expect(&Encoding::is_u, "expected 'null'");
            expect(&Encoding::is_l, "expected 'null'");
            expect(&Encoding::is_l, "expected 'null'");
            callbacks.on_null();
            return true;
        }

        bool parse_boolean() {
            skip_ws();
            if (have(&Encoding::is_t)) {
                expect(&Encoding::is_r, "expected 'true'");
                expect(&Encoding::is_u, "expected 'true'");
                expect(&Encoding::is_e, "expected 'true'");
                callbacks.on_boolean(true);
                return true;
            }
            if (have(&Encoding::is_f)) {
                expect(&Encoding::is_a, "expected 'false'");
                expect(&Encoding::is_l, "expected 'false'");
                expect(&Encoding::is_s, "expected 'false'");
                expect(&Encoding::is_e, "expected 'false'");
                callbacks.on_boolean(false);
                return true;
            }
            return false;
        }

        bool parse_number() {
            skip_ws();

            number_adapter adapter(callbacks, encoding, src.raw_cur());
            bool started = false;
            if (have(&Encoding::is_minus, adapter)) {
                started = true;
            }
            if (!have(&Encoding::is_0, adapter) && !parse_int_part(adapter)) {
                if (started) {
                    parse_error("expected digits after -");
                }
                return false;
            }
            parse_frac_part(adapter);
            parse_exp_part(adapter);
            adapter.finish();
            return true;
        }

        bool parse_string() {
            skip_ws();

            if (!have(&Encoding::is_quote)) {
                return false;
            }

            callbacks.on_begin_string();
            string_adapter adapter(callbacks, encoding, src.raw_cur());
            while (!encoding.is_quote(need_cur("unterminated string"))) {
                if (encoding.is_backslash(*src.raw_cur())) {
                    adapter.finish_run();
                    next();
                    parse_escape();
                    adapter.start_run();
                } else {
                    adapter.process_codepoint(src.raw_end(),
                        boost::bind(&parser::parse_error,
                                    this, "invalid code sequence"));
                }
            }
            adapter.finish_run();
            callbacks.on_end_string();
            next();
            return true;
        }

        bool parse_array() {
            skip_ws();

            if (!have(&Encoding::is_open_bracket)) {
                return false;
            }

            callbacks.on_begin_array();
            skip_ws();
            if (have(&Encoding::is_close_bracket)) {
                callbacks.on_end_array();
                return true;
            }
            do {
                parse_value();
                skip_ws();
            } while (have(&Encoding::is_comma));
            expect(&Encoding::is_close_bracket, "expected ']' or ','");
            callbacks.on_end_array();
            return true;
        }

        bool parse_object() {
            skip_ws();

            if (!have(&Encoding::is_open_brace)) {
                return false;
            }

            callbacks.on_begin_object();
            skip_ws();
            if (have(&Encoding::is_close_brace)) {
                callbacks.on_end_object();
                return true;
            }
            do {
                if (!parse_string()) {
                    parse_error("expected key string");
                }
                skip_ws();
                expect(&Encoding::is_colon, "expected ':'");
                parse_value();
                skip_ws();
            } while (have(&Encoding::is_comma));
            expect(&Encoding::is_close_brace, "expected '}' or ','");
            callbacks.on_end_object();
            return true;
        }

    private:
        typedef typename source::encoding_predicate encoding_predicate;

        void parse_error(const char* msg) { src.parse_error(msg); }
        void next() { src.next(); }
        template <typename Action>
        bool have(encoding_predicate p, Action& a) { return src.have(p, a); }
        bool have(encoding_predicate p) { return src.have(p); }
        template <typename Action>
        void expect(encoding_predicate p, const char* msg, Action& a) {
            src.expect(p, msg, a);
        }
        void expect(encoding_predicate p, const char* msg) {
            src.expect(p, msg);
        }
        code_unit need_cur(const char* msg) { return src.need_cur(msg); }

        void skip_ws() {
            while (have(&Encoding::is_ws)) {
            }
        }

        bool parse_int_part(number_adapter& action) {
            if (!have(&Encoding::is_digit0, action)) {
                return false;
            }
            parse_digits(action);
            return true;
        }

        void parse_frac_part(number_adapter& action) {
            if (!have(&Encoding::is_dot, action)) {
                return;
            }
            expect(&Encoding::is_digit, "need at least one digit after '.'",
                   action);
            parse_digits(action);
        }

        void parse_exp_part(number_adapter& action) {
            if (!have(&Encoding::is_eE, action)) {
                return;
            }
            have(&Encoding::is_plusminus, action);
            expect(&Encoding::is_digit, "need at least one digit in exponent",
                   action);
            parse_digits(action);
        }

        void parse_digits(number_adapter& action) {
            while (have(&Encoding::is_digit, action)) {
            }
        }

        void parse_escape() {
            if (have(&Encoding::is_quote)) {
                feed(0x22);
            } else if (have(&Encoding::is_backslash)) {
                feed(0x5c);
            } else if (have(&Encoding::is_slash)) {
                feed(0x2f);
            } else if (have(&Encoding::is_b)) {
                feed(0x08); // backspace
            } else if (have(&Encoding::is_f)) {
                feed(0x0c); // formfeed
            } else if (have(&Encoding::is_n)) {
                feed(0x0a); // line feed
            } else if (have(&Encoding::is_r)) {
                feed(0x0d); // carriage return
            } else if (have(&Encoding::is_t)) {
                feed(0x09); // horizontal tab
            } else if (have(&Encoding::is_u)) {
                parse_codepoint_ref();
            } else {
                parse_error("invalid escape sequence");
            }
        }

        unsigned parse_hex_quad() {
            unsigned codepoint = 0;
            for (int i = 0; i < 4; ++i) {
                int value = encoding.decode_hexdigit(
                    need_cur("invalid escape sequence"));
                if (value < 0) {
                    parse_error("invalid escape sequence");
                }
                codepoint *= 16;
                codepoint += value;
                next();
            }
            return codepoint;
        }

        static bool is_surrogate_high(unsigned codepoint) {
            return (codepoint & 0xfc00) == 0xd800;
        }
        static bool is_surrogate_low(unsigned codepoint) {
            return (codepoint & 0xfc00) == 0xdc00;
        }
        static unsigned combine_surrogates(unsigned high, unsigned low) {
            return 0x010000 + (((high & 0x3ff) << 10) | (low & 0x3ff));
        }

        void parse_codepoint_ref() {
            unsigned codepoint = parse_hex_quad();
            if (is_surrogate_low(codepoint)) {
                parse_error("invalid codepoint, stray low surrogate");
            }
            if (is_surrogate_high(codepoint)) {
                expect(&Encoding::is_backslash,
                    "invalid codepoint, stray high surrogate");
                expect(&Encoding::is_u,
                    "expected codepoint reference after high surrogate");
                int low = parse_hex_quad();
                if (!is_surrogate_low(low)) {
                    parse_error("expected low surrogate after high surrogate");
                }
                codepoint = combine_surrogates(codepoint, low);
            }
            feed(codepoint);
        }

        void feed(unsigned codepoint) {
            encoding.feed_codepoint(codepoint,
                                    boost::bind(&Callbacks::on_code_unit,
                                                boost::ref(callbacks), _1));
        }

        Callbacks& callbacks;
        Encoding& encoding;
        source src;
    };

}}}}

#endif

/* parser.hpp
SH0v8RyqO0qiEor3tLJFbnuQ3/vBCz4BFr/AcAZ6FTf/52uouxZt+l3dsfD173uq3wP6Xd2pCOl3dZ+ioN/VPYpS/345/I6tEf2u7k240P9XutpfrqHksi6WGEtaH5DiHzws8dD20LPeqGQaZq4pexVlS5X01hRdMKkuqBxTtmJov/+T51mSZ8huPzecPz0wQ4IfYUqk8c+cElpPwOafnqj+O+S0MHXUPH0b6PL7237aSSN4wp1jMhmKIoVc2OCiRruVq7F7kZWro4vrsqW4lYg2LjTe/Hh8yO+tYdFL8jjyvVjl+oeVvDUvNJ68Dgm+YLuwIV+tYHfWNlPrXnBcuFg0IlzHE+lNJcstxfOToa1j8SBJ1vU7mePytQK3mEel+mc8U4tnjlem3HZUgKe4DUs89f280L5LC98T/JBdV/AU6Luw40+NTN9eyQz4WrnvizQNY3Er9wjxttv7Mo6Pq/O49hrjmBGXzTfooiq2UmCKq+r6hShTBZN34rMW3zhpi7ewiK3pZvP213c5foDrx+jmsoxsvrXGoje2NtZEXQzfN7k8PwZW3gBWS4hbrtRddb5Xjew79UitnoawQ+y+RvFRve2Y/dAEp3M4ieMc3g/X4Vw17lELt0zcAL5C34Hb1gyIkgWf4/pd2GE4fChiPC4F1MpO0vdZN9ZFbWFa4DI9/gVy01PW/cujP2hZb1rhPkzYQZsXt1b7S0gPhB5W/bOh3yuy+Hcc6NaoG3fajru9PVjbFFMLA6RLC65mBjrmvaL3RLZe73S6yBpROkMs50g2hTbYc/2jFl8Xcz3O/Rzzjt67222aiz7h74a97NbWvOvgvwRzfXMDF37JxltXPL9Y2HetkSwgSPxcXDuGrFERtJf4zC8uInFxdXsaQPDU74CVtTd74m4m3idymOygmmg0as5fN4JqUv21j9NAq9t+iD5zSPebRBSK5xjwud2ZpG14XXBJmCf4MY0wBMBTyUdaWvKRlZi23bStmC6htWreLt5R3Qe3+Hp4GyQqoB8jh5onC8FeW1vZprJaN22WtfwTcbedYbWf39le7q8OzgxWbZl4EPCtHFx5ksBFFipeohx8L7qx6jou2EMkjEy8qOQykeXtpN2GZTmPhAeqV5Z1Doqylg/LKyFAcVzr18HmxiKaqQnofdr7eXkw8RMvy1wvVZ26vDHcZoOxovh+1ioX4w27jpd2S+xszuKOv3zYZTDAZK8RUGP5U3ssu1nkB7GbKLb8bbKhGsu/lPZaHvg53k8q8gZPVvr2+i0cru9zNw2ztu8pdiub9feXrg18Lq/imamwU/oNXklpXkOjvZbq2wmLhgulkvhlCEMWHkKowP4iBh8jpNq5pOTI5+Ww+Y2SqBO6GV4wHGxBTIW6X64caaiEpkE5nEDHUX28yukUTo6bviW2yJRdiZIMUp4MVecHoQwbFyyKXprKW/AJ5goMink0Hr917P59vNW/AQ4aInATqlvyoTbuU218ltVGPPuE5x4TsdOS2JgR86caCTHObFTyzNv4HruNRdEuu4mbGcbwolEHn9I2Ey+D4Yg8HKKWfqZ4n9pBEdJ/histAIz3T+2+SrA0+147J+VttXta8f6LxRuDgmfkshB7YoytWC/A8NTi5PjUmNGFfJwcNU7XnrFly8s6vniYScgniq1s96l4bU9+K17Oy5BPDlqqE/ri1R/D8ox0D1MWkhUs10cEXce0HaY71/+dJM270I14NHV5ZQHc59eJNfOpnLR4x04RwrQow85uvInW9BFB7IiRtcfYvJMyhAVaaNZr85u2Xn46x4dqK1K8TQtN/h/5ChDTWe+3+bZdeI9SGEbCQ1/lR17cbrT5kxbvEm82Zok=
*/