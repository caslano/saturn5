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
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
*/