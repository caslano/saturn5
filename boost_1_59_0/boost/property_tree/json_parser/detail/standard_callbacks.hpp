#ifndef BOOST_PROPERTY_TREE_DETAIL_JSON_PARSER_STANDARD_CALLBACKS_HPP
#define BOOST_PROPERTY_TREE_DETAIL_JSON_PARSER_STANDARD_CALLBACKS_HPP

#include <boost/assert.hpp>
#include <boost/property_tree/ptree.hpp>
#include <vector>

namespace boost { namespace property_tree {
    namespace json_parser { namespace detail
{

    namespace constants
    {
        template <typename Ch> const Ch* null_value();
        template <> inline const char* null_value() { return "null"; }
        template <> inline const wchar_t* null_value() { return L"null"; }

        template <typename Ch> const Ch* true_value();
        template <> inline const char* true_value() { return "true"; }
        template <> inline const wchar_t* true_value() { return L"true"; }

        template <typename Ch> const Ch* false_value();
        template <> inline const char* false_value() { return "false"; }
        template <> inline const wchar_t* false_value() { return L"false"; }
    }

    template <typename Ptree>
    class standard_callbacks {
    public:
        typedef typename Ptree::data_type string;
        typedef typename string::value_type char_type;

        void on_null() {
            new_value() = constants::null_value<char_type>();
        }

        void on_boolean(bool b) {
            new_value() = b ? constants::true_value<char_type>()
                            : constants::false_value<char_type>();
        }

        template <typename Range>
        void on_number(Range code_units) {
            new_value().assign(code_units.begin(), code_units.end());
        }
        void on_begin_number() {
            new_value();
        }
        void on_digit(char_type d) {
            current_value() += d;
        }
        void on_end_number() {}

        void on_begin_string() {
            new_value();
        }
        template <typename Range>
        void on_code_units(Range code_units) {
            current_value().append(code_units.begin(), code_units.end());
        }
        void on_code_unit(char_type c) {
            current_value() += c;
        }
        void on_end_string() {}

        void on_begin_array() {
            new_tree();
            stack.back().k = array;
        }
        void on_end_array() {
            if (stack.back().k == leaf) stack.pop_back();
            stack.pop_back();
        }

        void on_begin_object() {
            new_tree();
            stack.back().k = object;
        }
        void on_end_object() {
            if (stack.back().k == leaf) stack.pop_back();
            stack.pop_back();
        }

        Ptree& output() { return root; }

    protected:
        bool is_key() const {
            return stack.back().k == key;
        }
        string& current_value() {
            layer& l = stack.back();
            switch (l.k) {
            case key: return key_buffer;
            default: return l.t->data();
            }
        }

    private:
        Ptree root;
        string key_buffer;
        enum kind { array, object, key, leaf };
        struct layer { kind k; Ptree* t; };
        std::vector<layer> stack;

        Ptree& new_tree() {
            if (stack.empty()) {
                layer l = {leaf, &root};
                stack.push_back(l);
                return root;
            }
            layer& l = stack.back();
            switch (l.k) {
            case array: {
                l.t->push_back(std::make_pair(string(), Ptree()));
                layer nl = {leaf, &l.t->back().second};
                stack.push_back(nl);
                return *stack.back().t;
            }
            case object:
            default:
                BOOST_ASSERT(false); // must start with string, i.e. call new_value
            case key: {
                l.t->push_back(std::make_pair(key_buffer, Ptree()));
                l.k = object;
                layer nl = {leaf, &l.t->back().second};
                stack.push_back(nl);
                return *stack.back().t;
            }
            case leaf:
                stack.pop_back();
                return new_tree();
            }
        }
        string& new_value() {
            if (stack.empty()) return new_tree().data();
            layer& l = stack.back();
            switch (l.k) {
            case leaf:
                stack.pop_back();
                return new_value();
            case object:
                l.k = key;
                key_buffer.clear();
                return key_buffer;
            default:
                return new_tree().data();
            }
        }
    };

}}}}

#endif

/* standard_callbacks.hpp
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
*/