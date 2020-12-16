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
xs9etjqf7CMAZma2Z75/Tn6ngD3z/fP0ndZJzeML9J3WdCy1iI8m2BdtmB+Udj9/ieC4s5mgmC73ZbucyI1l0f2KDaccWabdX7XhSdkytL9GMATNVsYV4oqwZ041/OsEp5uLVaKtWUb7GwRHj0sgo/3NOqyPCCQG/5bVt1Scwb9NcERYAyHpEaLm/R1VtxwOeYDd3MC+W4PhxoKGfY9gZFTOJF5P8/y+5tkLcMzho/JWX/6A4LinhwFMe+6sqe8P7fZQSjUD/5GEU18gxBehyhz+Y4KTtJMoGvhPJBzxsgg8l9vjIk9Nm3/agJt6/8yGYa9o6P5c1RtJT3AnlSaHgf+C4HmBAexJ8CyD/1LDqWkULHZTgv/Klj93rhf30wCXBxjOrwkHElIcR9cVJyAQuN8CPnp+/EbN0dRFv5jvv62+g3pbzEQTR4ulEnoFgbjs29FLiW/V1tHEFlxOfONmoTm//OQt+ZlIHGDxwmvrjozDIk2v8/NP2/nf8dh/3HFLrIw8aotZFNDlis+beNnD7TwKEVjWduhJDXt/eR643IfdDTtIdp8iBoiwcRZHNpAwfFbwgeorWBs75puczmS768IBg+090j/rgLINZSv+cNq2jwu8HZIhyajKIw1e8K71ZqcneXHzBvvTv8nfYC87BTwPyD7MY/HmlU3yF/DiPscAL2IgSzkd7Yq2icfxajaZw9/tTzpl7saeI18OJQbzHcK9qlOLRUNUJDxPqeMDXbmr5odoETgNzsKGqt6g43aG5vvDjLcrhh0b+V3P2cI5icL1lE3yS47rezjz6sJgDl0nVaEDJBtgP6y4wVrTx6qC5Maa5R/l7Zjyci9rxyGs76Hlgm8NlHxOWe2G3HRwapGjREnOShzNa9mh/YXi9ZfHtxivEi5K3GGr3DDrG+uLhA15aRN+6th7C6ROR+rxINdxC2ja4urOkpQbi8ZA9e3qfktmcLruwmqqrHPCNWfUSxa/zIFo4gqUh7btUByGyWxOvWoElcnerSLLL1ci7W6EZ2/omXcanlosycOscYjCovByzKPtDTxV1NdbArPfe3ytb9LYjQucxdTekhf3DCAF/mHOVu/3eD0zbN0g8m63pOfveQlTz5dxvkeyqIMHYDo51XNjp+HjfhPw+Rkv3qTp+HEUCib/saLoU9Xej1p0Iqed4eAnizUZbExo0lWCgdhs/Ltjz+/vchqTSe52w26WIfX95uq5eozkTx1bVyF9NXRbljZ1FRWvvZXyd6ufoMLxVkrXl3qRNXBW9dPlXDv+Mw3zNlLjN2NRRuvIee033G/79UM80RR12lz25PtS+Ht5a36I34YbO1tq5syrvvp73uJ6HUcmsdcJcE5l3geYVrpwH6+750IXJkGeIbgBdaf1o/48E44LrZ5bU3xPcL6HfL8NXy0iAnD8gG6vvWFxErhctnKxP8NjRHj0CNhg8B/24Cdew9sYRmWO4LPAYe7r1paSP98any4OpEMo6iKx2ki1rI5NiArn99uItw3xvR0vjNU5fr1tbt0vEmeuj0Yek9hG+qCp15WqNW+NnXXt9SlG4EjiQhnNo6LQz/hDO1/Utuocc3amaDy9JpOIAEAIAG9yjYrxY2sa76n1WxAgdAFRjJxIPQRMVUTJ11c5DWxfuzlaE4biJaRC7lj16wyLsm3TUyACX43sWpBa0/74thXbj+gUnHsHqdM7tylDEbBsYU+v16IZtd7zcj4CGsuogOUi2VRTUYZ3Th8RayxJ20T1Hzb0CiZMKKd1d3VmyGnCBYVnyLCW4zwG6PX/iAAZI8KkIIOCURe24L3V+gDaPN4qT3y/W/jlBWivkFnJSUKjm4/c1jzP6U/gakC7xIQ=
*/