// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/detail/key_extractor.hpp
/// \brief Key extractor for a pair<Key,Data>.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_KEY_EXTRACTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_KEY_EXTRACTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {
namespace detail {

/// \brief Key Extractor

template < class T >
struct key_from_pair_extractor 
{
    typedef T argument_type;
    typedef BOOST_DEDUCED_TYPENAME T::first_type result_type;

    result_type operator()( const T & p ) { return p.first; }
};

} // namespace detail
} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_KEY_EXTRACTOR_HPP



/* key_extractor.hpp
WcFafcFYLjm8vNFsUP0AvrDRjM7qGo80syhZizTDeMGUZM5k79sUgHux6SD8O9P1kWYOoAv2qqRalnUJw/8SaL3bRjMpsSCijBvExotOuUAdgVeMhvrBXwuMYgQgEHpMcCB0a8GDRtp7x0oCj0cKTWpkoQz2Bb5mM/Ss/NYswnoeJpeESI7ATz8yQBibG635b3EpyjZ3g3YTGCx/Af7h8A4Krp7OpSXbY1/BrucPxhk/LrngJ3Nmd/+xRYmazAHPlI1OeZ/HrBSyTNVh/l3pPndcGJtUN7ivx7rwYAXmSfUXcNASCzvUVJdM16JdovRQKB1h9+/SKUVXl5pBUhEUlqpccSwCqait1lsuKjRBRYgqOP9TC6pno5mlREPJgIWMUjMF5pgugmgHqdR4YI6sGzQqSq23VCvGVCbv633e36FbIs8P1YJsOMA9+N8h3MXvXK9NZ2BkfyTfF2stKGO9S158NWhUzUmlVQvoDp37Xpdv5UQ05S+TfC/F+znj2iL13OpKOeuxFC6GqDfVlmR8eq6GJfCVEUaDdz2o2yPd3ZIXnwPdufWFUrbLgqvnlcqibQZD2Rx4bQQakOcnoxp8Tio8EjZIG+rCXSk1U+KGylGn+QAYHfJXGCEnhhxwXwa2UP6y6o2NgmcteJtvFlP9NmUdHoy//+8oA9F79XUGAz+5IHfiqas3fo8nBwWlOeljvYw5tPI44Cn53Tej
*/