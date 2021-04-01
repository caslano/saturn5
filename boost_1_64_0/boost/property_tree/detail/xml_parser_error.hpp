// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_ERROR_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_ERROR_HPP_INCLUDED

#include <boost/property_tree/detail/file_parser_error.hpp>
#include <string>

namespace boost { namespace property_tree { namespace xml_parser
{

    //! Xml parser error
    class xml_parser_error: public file_parser_error
    {
    public:
        xml_parser_error(const std::string &msg,
                         const std::string &file,
                         unsigned long l):
            file_parser_error(msg, file, l)
        {
        }
    };

} } }

#endif

/* xml_parser_error.hpp
9AhmlX09TpFWr1GhRicVdp6SwdzVW4CkMrOSrBzHjbm48QIN3IIXFRCcdCVP/Tw5Ljr1YBNor2bRc4goHwYvRNwTLCodElDoK997nLILuGhFiMjJDtxrk2G04Wloj/T0q1QG3w7O7T5smAs6LsRexPQzoGRQeDDeCcysO+tHCtbx12voUJNNpFZ3WCDm/vrqBrno6Zl+Pmfl0yxRipz+t3TOY6R9URx5GavYgJrQdnvCJqQT9J5wjk63U8OBmwErdPD02/ujOzf1QpRjpSjtXw9rPc9O1HsgAOqIhrAJ93xNnf/7KxNEV3uJryD/zv9rVYFKRXGUbMlO66ChlAIaIm2oD0+wix1sRRTHkCmVceHtvUQnS5PKyEgIH/xhRjLKC8bp43aVKA2++wMp4wIPE3y/aemXo39dGP4tanQFxeAgkr42FKvj/ieuW35TshZG//AWjCTfneAVaacosqXEydTVYdAfUag3BFQppamWYA4JJMknPHcMT2z647hXWqv1+/ECVN1i5UgpK1zopEY4IJfKfR5pyCfmNzXlfB6Ii2/bbEN/R6SvkCHOzw==
*/