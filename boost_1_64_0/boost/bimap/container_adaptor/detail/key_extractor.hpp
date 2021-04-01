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
inmB1V5dt7t2JpQ/xrnXdQAgFNInpiFCRSy/NyTV4RHxq4DRsEPkivsP6kmMGaYSzI1Xw6S8a8wiboXaUscGhACQtTonLj/oXEpzkq0dmM1x3GcGTmR01IhydxliaIwiN8Le1NTZ4HQc5ilFUjsPnRH9g4p9uYSVw7KM2ogUPH0+AFKSbA81OuxNcJbof7QmCRkqtCOGG72Q8XYxmrLl4G1v0lc4SoYPzoMQg5iuxzgvDkSNFNo7LPgJIDq5JPEdF51A3G6r4tVeTwezvJKAuEhzR8955laVndnhahxgPB2FTbj+RKI/GMoLVrLonETwq1mycEu50bBxt0JTZAPehfJDWEZV4oONjVZwWWX8cJ5Uo1si2jf2aFZMLom4CypiDFA+OYFFU99zsOUBh8lWMZkB/H3CuTYJ+WAr/VHcKfzE1Weqm22B14UJQKPWiniPVnNa0T/KAe1e4AkubtKOnWOzOPyJVtjnN2PVAXlWa6n7tAXrKCHqWBHNRpagXsXFVcsr2V6WQa3D3ir0s1sEbae0nu2gU9i5s7S3RKemjVlN7KqQ5jyXtgqjlw==
*/