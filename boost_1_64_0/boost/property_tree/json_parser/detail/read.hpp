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
29Sh+xvAntj0du0hFCZ8Jqhrf6ERvmeOvYRZMxnU9mL0Gb9W5ntXT3uwFSip28HsLZQhFTF3wRUwpRq2r3m4ppRw0Aw8tkjhbIms5LneQpOU0H4u8WWDs7CuSwmkOZnQt9ujj4NSjVwgfrI6m0n7daI4dF9jApPQxFK8F0IXAc6pHn2Wom4tYbqkbZqRWHy7m4ZGPU2Rs3hZ9CbptsOxjGBKdiRkmxZLf/OsS5o+ZA/0zC3bqAdviMiEvqftCz+5qMyyQN75EGQcGaTxIUN2+CFXtxnozdZp9KqYCpkxtuu++U4xW6jFSbq493NOOfxaLn93JlLNFZzzPM+CBI2vD6rRye1o89y1G3tTf133W2E9YGXp1MIfZSGDVjBALSyr5k/Psen5dxHNt5vNrGLAP3fwdBmOLnZ6eF8sLRdad7BDNv2fqLwKdwevpk0L0k2mK8pEyecQGgcT8ZkkFAe3HRrpWNvsERpLk7ggl8WdczStCqBHGhWFyhy0/nshk4OiJOnsGON9I44dXS1JyM7trMxcDKUNwQJE4b4EYbAiw2GbuAIBdxUKGBcQFg==
*/