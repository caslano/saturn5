// ----------------------------------------------------------------------------
// Copyright (C) 2007 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_READ_RAPIDXML_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_READ_RAPIDXML_HPP_INCLUDED

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/detail/xml_parser_error.hpp>
#include <boost/property_tree/detail/xml_parser_flags.hpp>
#include <boost/property_tree/detail/xml_parser_utils.hpp>
#include <boost/property_tree/detail/rapidxml.hpp>
#include <vector>

namespace boost { namespace property_tree { namespace xml_parser
{

    template<class Ptree, class Ch>
    void read_xml_node(detail::rapidxml::xml_node<Ch> *node,
                       Ptree &pt, int flags)
    {
        using namespace detail::rapidxml;
        switch (node->type())
        {
            // Element nodes
            case node_element: 
            {
                // Create node
                Ptree &pt_node = pt.push_back(std::make_pair(node->name(),
                                                             Ptree()))->second;

                // Copy attributes
                if (node->first_attribute())
                {
                    Ptree &pt_attr_root = pt_node.push_back(
                        std::make_pair(xmlattr<typename Ptree::key_type>(), Ptree()))->second;
                    for (xml_attribute<Ch> *attr = node->first_attribute();
                         attr; attr = attr->next_attribute())
                    {
                        Ptree &pt_attr = pt_attr_root.push_back(
                            std::make_pair(attr->name(), Ptree()))->second;
                        pt_attr.data() = typename Ptree::key_type(attr->value(), attr->value_size());
                    }
                }

                // Copy children
                for (xml_node<Ch> *child = node->first_node();
                     child; child = child->next_sibling())
                    read_xml_node(child, pt_node, flags);
            }
            break;

            // Data nodes
            case node_data:
            case node_cdata:
            {
                if (flags & no_concat_text)
                    pt.push_back(std::make_pair(xmltext<typename Ptree::key_type>(),
                                                Ptree(node->value())));
                else
                    pt.data() += typename Ptree::key_type(node->value(), node->value_size());
            }
            break;

            // Comment nodes
            case node_comment:
            {
                if (!(flags & no_comments))
                    pt.push_back(std::make_pair(xmlcomment<typename Ptree::key_type>(),
                                    Ptree(typename Ptree::key_type(node->value(), node->value_size()))));
            }
            break;

            default:
                // Skip other node types
                break;
        }
    }

    template<class Ptree>
    void read_xml_internal(std::basic_istream<
                               typename Ptree::key_type::value_type> &stream,
                           Ptree &pt,
                           int flags,
                           const std::string &filename)
    {
        typedef typename Ptree::key_type::value_type Ch;
        using namespace detail::rapidxml;

        // Load data into vector
        stream.unsetf(std::ios::skipws);
        std::vector<Ch> v(std::istreambuf_iterator<Ch>(stream.rdbuf()),
                          std::istreambuf_iterator<Ch>());
        if (!stream.good())
            BOOST_PROPERTY_TREE_THROW(
                xml_parser_error("read error", filename, 0));
        v.push_back(0); // zero-terminate

        try {
            // Parse using appropriate flags
            const int f_tws = parse_normalize_whitespace
                            | parse_trim_whitespace;
            const int f_c = parse_comment_nodes;
            // Some compilers don't like the bitwise or in the template arg.
            const int f_tws_c = parse_normalize_whitespace
                              | parse_trim_whitespace
                              | parse_comment_nodes;
            xml_document<Ch> doc;
            if (flags & no_comments) {
                if (flags & trim_whitespace)
                    doc.BOOST_NESTED_TEMPLATE parse<f_tws>(&v.front());
                else
                    doc.BOOST_NESTED_TEMPLATE parse<0>(&v.front());
            } else {
                if (flags & trim_whitespace)
                    doc.BOOST_NESTED_TEMPLATE parse<f_tws_c>(&v.front());
                else
                    doc.BOOST_NESTED_TEMPLATE parse<f_c>(&v.front());
            }

            // Create ptree from nodes
            Ptree local;
            for (xml_node<Ch> *child = doc.first_node();
                 child; child = child->next_sibling())
                read_xml_node(child, local, flags);

            // Swap local and result ptrees
            pt.swap(local);
        } catch (parse_error &e) {
            long line = static_cast<long>(
                std::count(&v.front(), e.where<Ch>(), Ch('\n')) + 1);
            BOOST_PROPERTY_TREE_THROW(
                xml_parser_error(e.what(), filename, line));  
        }
    }

} } }

#endif

/* xml_parser_read_rapidxml.hpp
E5V3//vEzX37pjTq8re0vLGiJnwP7hr4QJVt6QpLDrzv33555vv+2vpS7/oVWV4avu9P1lnwkMw+WsZiTbWlTd6Dm/fhJLDNvjpVdWZ3DXicRJWmPm+Zx+ctze1nupubW/q62oOg9jZhWtbVM9Ka+9rPtN3nkJfrEumSgpt1+ywoaHZebXzIQ+qbe5/Y7B1iRnr+Zem7Z7Pg9mH67S/fvu0pyujoCPqSZRRdlufxPW1tQX+yjHtclt7d1b2bJ13Gocvz9PeeDnqS6fc/kN7X03Gq+1w6/WjfZekGNei5ZZhev7d9+ZWPiB9v2qv71M3CtGfvpZXVhAnJ11+bft086Q2SZb1tf/5m54pU2nZXepvE2frxXkumPbJvL62x2TLdnPhoIEjVtd4dpu01oSv5+ti58PW94oJkf8/ulVX6kMYrmp2iK8qP726YSv9rdzq9pvF4RVXFlYk9l9qvwZMuS98rIEjvk+y9PO33atmXL1VGnvS9tvV17cuhjGSe21xej9y2yahnJaMvx50Lw66WJcftT3vputnc2d56r95O54dk2tX7U2l9Z/vu1fW4J6TT7vqkVNqpnjaHWMZ2WXvbVTws3twQa+47190WtCfHfO0pqbTe0y1XpPZf4/nU6z6oeURze2vQnuznyQNpV7X1lTR7DxNkjMXE8/5Nnpg8GWNxg/59eZL7pPROYXrugfRTXd3nmrtbelrOtHlzlp6jRQO7+bRgrxoLfyptZm9OxTLTkvVX743ZCWu3z3V9urs7a9LHWePB9L0W9iTbN/nkg+kuDZqf7NOpx59rPvW41Nz501MO5is/fmKvrnPJPDv/Nk+ivnSeq5/9d3naO9v7gnN3DfO853n/rk3hR4EGr+90b5Bs//u1//LyrpK/raenqye4R5jv0c/6r/mU3t132vVXMn/Pk/5T/lP9PT1tnaJTQXAq2Y5pbb4sv3aH+TqT+T76H/M9vqPlqt50e5+RypfcGwpKttZy6d1noL3J/Vzcn85/ZcWDw22C5uQcmsuoN3GREGQcW5/LSGttv8ppNJ0W6w/XlNa99Me1d6Xm3mLGdqeczxJnMy83J9Pj6TZZQ1JtS23/9eftLzv+0DKHSJBKf/T+PoXHVjp95cD2jaUN7myn1+jTGdubqanjaSW9b5NlViS3+cH+MlPzfy3d172DMDGI3iH3WPuT7enM2Ge7F8eJ/XpF0J9M/+XzDqYnSgr6k3NjMzO9tfWK5t23JM3WSFf81pxkvj8dzLf7FiKZMb027aTzhUWdSrxZClLH4vNT6XtFJDN4f3n7ZJvTY2V8rfXuNnS0d7YF8iTreV56nJOrR+J9V+oYHT6/L53EZ9+Nu598Bxn9GurPHOPL8yXb9PID9YWfS3daU1N929TuVFn786TadfFAOeFnuHuZMsc7s6zL8qXbdfpZB+ZI6iPN9Hi+of9AnuTnkRnjOX6gXXsfkqXLyHr+/vZkHjzJMt55oJ5kIck1dmr/sfXv+nVVsr5PH8ybLi81ltsZeRJvulwP7t1caZZL35L5bpBue+Y+2f14PsjIl5vOl2xXOqN8yX7c8r+U19zV0RroRzJvwX8rM5FZ3uT4/SOjP90WWyvv2czj4k4ZZe19IrWXTVJvsozrPnnfuIUZ0vOl+MB+9ImF64N+eZSRrKcnY21u63DRIJvzSTL95f/+PBGk1u+97RvLmxor9xa79DnjYZlpGpA8rSTT57v3rl2uvHJvXQhPqan0L6bSk0Mk3TVNsn/16f4/7N7NFSeO715Hd57q6nx8qowT+/KY7QfSH3tZ+qm+s0G6DYMDu+m992r/99e893r+wXkZfhYlLbU+pddJh9GV8aaHVBiO1L7oSJY=
*/