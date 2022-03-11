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
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
*/