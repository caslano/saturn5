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
8CvX1RyaG8sJ/HjunV9O/Uj9fX3EdzZ8Q8Vfi3K7eg9DFeTTpjNtjCKmjZEPrBkw5E32KNMDyiO5Q9wzB+wFvH3a6r5XviPN0wEdsdUC2AqzKpebYRi/s9T0tMUVk/n1jlJTILn5vljBnfS02R0XTCnCk2U0z+Bpt3gOBd1HzXubJLt8VxZkv3bnQuvO1syYWRq3pfm+cQJO9+PKUlhoph9u/vDyjoVWyJWFuU5Bqz4ITUjXwL1vTlHG/I7ekLsQMBEnMjr4LipxfBtxdKnasrI4vLelObxNVod3vsrhtOBVWH6m5DmvMd//e+LuTjJtaodvvknRpWL5ZNBjpUk1A6yMQfGEbAPg9mVR30GNK0bpOoeWdpQngdeT5E6gaEvsso727+Tyam+VBY0QNI9GPMXIfHwGOGeffT6wGvjMkf9QqVYjF+sn4jrqLU2GJTOh3luatrM4fkcpULF4ucqiHM3AkT8QcSKZj8QqtHdgHVK2CRvOQTVF2hlqudj9NWo2dxAVMUnyAbvsMMHae4cRftbp5VPKHyfRrgVemvoDkbj5pjJ6ixvijk5kATjffkZc9Ay7b9bLdvkOPIbrNznlWYrouc+k3zzJLif0i54F+qAsWkTvXJMoH8pu9cK3bNRI/cn7EpETn6vBKVdqcvgW6B0eRe/wVemV24qxEsy9kOcuhdztPHcM5maVefOUnqXQbTDxmLXZUaPYLvzn
*/