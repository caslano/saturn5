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