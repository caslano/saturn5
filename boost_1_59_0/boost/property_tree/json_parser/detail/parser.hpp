#ifndef BOOST_PROPERTY_TREE_DETAIL_JSON_PARSER_PARSER_HPP
#define BOOST_PROPERTY_TREE_DETAIL_JSON_PARSER_PARSER_HPP

#include <boost/property_tree/json_parser/error.hpp>

#include <boost/core/ref.hpp>
#include <boost/bind/bind.hpp>
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
                            boost::ref(callbacks), boost::placeholders::_1),
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
                                                boost::ref(callbacks), boost::placeholders::_1));
        }

        Callbacks& callbacks;
        Encoding& encoding;
        source src;
    };

}}}}

#endif

/* parser.hpp
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
*/