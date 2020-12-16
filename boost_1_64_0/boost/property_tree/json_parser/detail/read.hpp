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
H0JIllaGgltNxuF/gfUJ7qsr26BjeP99xpI1H25KPO0TONWsX4KDFAJPzLcV74tmuYzk0COZD18x9OW6ZE2FlVl0aoAsd1Bk9Zxrt+V0UgcatwOb23PgG8Kiu7o9P7TXlCmOj+1BJvbIbgR88KwKVAwVn0nVxhjl+Jrgw/lXxoWaT/xxPle18cRsbc2FUJVeVjoCm40ueUJhiKIKK/NQwEN0sOnfB9m8Icxd7AlKR+oQuFBxrFOfS49HGT6X46wb59g6KT2ytbGxjZa6WOnFA0xHQGKd9bDm/TpOB3suz293Mr8g4xxnwDiGoYYPOkrvWe328V5u1vG6RRcyPb8llvqqsMr5MlmRkF4OuSkSOumQzm1Zz2MVuZ3Ih/G7g3w77f6B8Smk9l+lCW306G+tcl2n3fXaCSaFM4tyYNqenkTR6SPVXAIB+f6jtutW9drc4/IFdZwm7SKMGHt7z3Htnp3vUZzhpRGUT5MvcZwURyn3x+ADcsTaf6Y2707gem3ks9S8j4zbuuREz25zCDsWgUc5540y9TY31o7tnjXmUCNx2YEu2ZyHNphfZVsOs3Y80mo39GcAQy/FJlha+rRkDdHa9cVlDDvm9cI58rCuOWzNtHknsKPTTjvC7heL5bZkTSK6qMp80i4j+jvvdn2UoWVWm5ZmfnwTZax8cO0i8/KuS/ZPTfVV5xGVNQxSsIfNWteas234TieGcxuvoFaj2sfUPovVFrSG9ljtRTmuG3JMLKRJ8mU52iXtDGkPXZGxnCPK53r3+rss7E2WWxDOK86MwDkgX/MBGDpO4p3c7Y2XsT5Nd6wkyJ7awjyDjKIM/jGyzGmUAX28N0N57++7n/CPPWQX/ANybPn7Fau71wcrinlzZmuXOshU5Nr/oPvjPPVH414ajud4Tvz37oJH57Drqk1nH70LnkmgP1S4D7kALiXuHyr+j7wQ3ZZ5n+Xb9yM8di8SnzNF53Ggw99C0Q9D9E9ttkBHvxOwtQsetpuK1vN2eydgWLVzR/nOP2vyxNOTPuZNn+9ez861PuSwG2uYHGQOmzY51YmqydWPDgGsWlJXBkP1ZsWYqvf7nQpeLTlEgbtuTE73adE+ol75kM052F+iWr7NEjM9xpo6M1jcOL2OxAZLmLPwCfNkpxBPtUe8KEZ5tpaURSeMc7j5cSTghcg6OTbEP61kn47e86Es1+14fxpWVtdiXVWaHBSsBitKT05wGocjvx1HWdxl7A3fSdXmo7F99pcGcTvvovGQ1As4UV3V5l5sn0XhqcrAK3BOcoHSeo9o91cXJ4ewajvOBpTjlmWmmZzqZ1GGr79htx0WyPxi8nl78+vwiZJynT5C9VCp24SPldsf1z/B9TvWc78dljid4f4o8nZafsrLXY+Vm0TqNSzGhXhjfEktna2BqvPr6nWO2nCrd2KVVE5X/cT0hE6WRw5MmMlYU2Eyoc6K3ncteqEjLv0h/Dj/r+mtrFu+z2snXG5yZNcMSpjsmkzRNXkole1yY7tMt4y8yENVhI5nk8NV/Xwr4HNbp9v1ul3IGznOVAY5cLPz1k7wcthGRDHMY9j/0p40QmpeLG5tqH7yk/o76LDusrBo9JPtrzo1j9HmudtVXZY4vcyBnyGJXR8TDMdCEFYs43Dey4MhXRd1xrSJspbNHKdJ4iUkt6xCSxjubfqncREiZ97OpjqJEqpOnJn94xrq3Kt+7GXiVR706Qrep0Mj/f1h8rs0JCjfz7/0mR92824v5t/30HdKW0Z539S5Gj9WM2UuTbmDiJr+fhn6TtToO50XIui1ClkNfPquzg3VV8LX54foeZVLjb5fQX1HCPTxPC1cX8Mo/xoiMo/3Pfj8ct4=
*/