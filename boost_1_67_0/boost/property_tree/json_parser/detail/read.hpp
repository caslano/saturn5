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