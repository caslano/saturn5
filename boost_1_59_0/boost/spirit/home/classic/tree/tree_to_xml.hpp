/*=============================================================================
    Copyright (c) 2001-2007 Hartmut Kaiser
    Copyright (c) 2001-2003 Daniel Nuffer
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#ifndef BOOST_SPIRIT_CLASSIC_TREE_TREE_TO_XML_HPP
#define BOOST_SPIRIT_CLASSIC_TREE_TREE_TO_XML_HPP

#include <boost/spirit/home/classic/namespace.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    namespace impl {
        template <typename CharT> struct default_string;
    }
    
///////////////////////////////////////////////////////////////////////////////
//
//  Dump a parse tree as a xml stream
//
//      The functions 'tree_to_xml' can be used to output a parse tree as a xml
//      stream into the given ostream. The parameters have the following
//      meaning:
//
//  mandatory parameters:
//      ostrm       The output stream used for streaming the parse tree.
//      tree        The parse tree to output.
//
//  optional parameters:
//      input_line  The input line from which the parse tree was
//                  generated (if given, it is used to output a comment
//                  containing this line).
//      id_to_name  A map, which is used for converting the rule id's contained
//                  in the parse tree to readable strings. Here a auxiliary
//                  associative container can be used, which maps a rule_id to
//                  a std::string (i.e. a std::map<rule_id, std::string>).
//      get_token_id
//                  A function or functor, which takes an instance of a token
//                  and which should return a token id (i.e. something like
//                  'int f(char const c)').
//      get_token_value
//                  A function or functor, which takes an instance of a token
//                  and which should return a readable representation of this
//                  token (i.e. something like 'std::string f(char const c)').
//
//  The structure of the generated xml stream conforms to the DTD given in the
//  file 'parsetree.dtd'. This file is located in the spirit/tree directory.
//
///////////////////////////////////////////////////////////////////////////////

    template <
        typename CharT, typename TreeNodeT, typename AssocContainerT,
        typename GetIdT, typename GetValueT
    >
    inline void 
    basic_tree_to_xml (std::basic_ostream<CharT> &ostrm, TreeNodeT const &tree,
        std::basic_string<CharT> const &input_line, 
        AssocContainerT const& id_to_name, GetIdT const &get_token_id, 
        GetValueT const &get_token_value);

    template <typename CharT, typename TreeNodeT, typename AssocContainerT>
    inline void 
    basic_tree_to_xml (std::basic_ostream<CharT> &ostrm, TreeNodeT const &tree,
        std::basic_string<CharT> const &input_line, 
        AssocContainerT const& id_to_name);

    template <typename CharT, typename TreeNodeT>
    inline void 
    basic_tree_to_xml (std::basic_ostream<CharT> &ostrm, TreeNodeT const &tree,
        std::basic_string<CharT> const &input_line = 
            impl::default_string<CharT>::get());

    ///////////////////////////////////////////////////////////////////////////
    template <
        typename TreeNodeT, typename AssocContainerT,
        typename GetIdT, typename GetValueT
    >
    inline void 
    tree_to_xml (std::ostream &ostrm, TreeNodeT const &tree,
        std::string const &input_line, AssocContainerT const& id_to_name, 
        GetIdT const &get_token_id, GetValueT const &get_token_value)
    {
        basic_tree_to_xml<char>(ostrm, tree, input_line, id_to_name, 
            get_token_id, get_token_value);
    }

    template <typename TreeNodeT, typename AssocContainerT>
    inline void 
    tree_to_xml (std::ostream &ostrm, TreeNodeT const &tree,
        std::string const &input_line, AssocContainerT const& id_to_name)
    {
        basic_tree_to_xml<char>(ostrm, tree, input_line, id_to_name);
    }
    
    template <typename TreeNodeT>
    inline void 
    tree_to_xml (std::ostream &ostrm, TreeNodeT const &tree,
        std::string const &input_line = "")
    {
        basic_tree_to_xml<char>(ostrm, tree, input_line);
    }

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#include <boost/spirit/home/classic/tree/impl/tree_to_xml.ipp>

#endif


/* tree_to_xml.hpp
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
*/