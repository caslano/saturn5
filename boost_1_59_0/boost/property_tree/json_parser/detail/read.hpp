// ----------------------------------------------------------------------------
// Copyright (C) 2015 Sebastian Redl
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_JSON_PARSER_READ_HPP
#define BOOST_PROPERTY_TREE_DETAIL_JSON_PARSER_READ_HPP

#include <boost/property_tree/json_parser/detail/parser.hpp>
#include <boost/property_tree/json_parser/detail/narrow_encoding.hpp>
#include <boost/property_tree/json_parser/detail/wide_encoding.hpp>
#include <boost/property_tree/json_parser/detail/standard_callbacks.hpp>

#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

#include <istream>
#include <iterator>
#include <string>

namespace boost { namespace property_tree {
    namespace json_parser { namespace detail
{

    template <typename Iterator, typename Sentinel>
    class minirange
    {
    public:
        minirange(Iterator first, Sentinel last) : first(first), last(last) {}
        Iterator begin() const { return first; }
        Sentinel end() const { return last; }

    private:
        Iterator first;
        Sentinel last;
    };
    template <typename Iterator, typename Sentinel>
    minirange<Iterator, Sentinel> make_minirange(Iterator first, Sentinel last)
    {
        return minirange<Iterator, Sentinel>(first, last);
    }

    template <typename Iterator, typename Sentinel,
              typename Encoding, typename Callbacks>
    void read_json_internal(Iterator first, Sentinel last, Encoding& encoding,
        Callbacks& callbacks, const std::string& filename)
    {
        BOOST_STATIC_ASSERT_MSG((boost::is_same<
            typename std::iterator_traits<Iterator>::value_type,
            typename Encoding::external_char>::value),
            "Encoding is not capable of using the iterator's value type.");
        BOOST_STATIC_ASSERT_MSG((boost::is_same<
            typename Callbacks::char_type,
            typename Encoding::internal_char>::value),
            "Encoding is not capable of producing the needed character type.");

        detail::parser<Callbacks, Encoding, Iterator, Sentinel>
            parser(callbacks, encoding);
        parser.set_input(filename, make_minirange(first, last));
        parser.parse_value();
        parser.finish();
    }

    template <typename Ch> struct encoding;
    template <> struct encoding<char> : utf8_utf8_encoding {};
    template <> struct encoding<wchar_t> : wide_wide_encoding {};

    template <typename Ptree>
    void read_json_internal(
        std::basic_istream<typename Ptree::key_type::value_type> &stream,
        Ptree &pt, const std::string &filename)
    {
        typedef typename Ptree::key_type::value_type char_type;
        typedef standard_callbacks<Ptree> callbacks_type;
        typedef detail::encoding<char_type> encoding_type;
        typedef std::istreambuf_iterator<char_type> iterator;
        callbacks_type callbacks;
        encoding_type encoding;
        read_json_internal(iterator(stream), iterator(),
            encoding, callbacks, filename);
        pt.swap(callbacks.output());
    }

}}}}

#endif

/* read.hpp
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
*/