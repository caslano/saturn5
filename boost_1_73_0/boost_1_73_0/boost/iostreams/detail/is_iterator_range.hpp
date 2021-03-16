// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_IS_ITERATOR_RANGE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_IS_ITERATOR_RANGE_HPP_INCLUDED       
 
#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/detail/bool_trait_def.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>

namespace boost { 

// We avoid dependence on Boost.Range by using a forward declaration.
template<typename Iterator>
class iterator_range;
    
namespace iostreams {

BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_iterator_range, boost::iterator_range, 1)

} // End namespace iostreams.

} // End namespace boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_IS_ITERATOR_RANGE_HPP_INCLUDED

/* is_iterator_range.hpp
JKPpTblyl9ALuWKB8CKQDKdfypXdi5eB5JPjlVyxQHgVSCdKX8sVTyCbc+X88+tA8mTyBpDOqL8JpPXQt3LlbiF0D3yn0J+AHwHfy5XzNu8D6caZD4BkPYLvOkNbyh8CTwJ+DBwD/BRIp6E/yxWvWfg8M/cA/5YrdwPh+8r8CNwKbIf6bAHuAfxHrlgifJkrY9g3ETOGUUjOW58dNeetKZSme3p0uh9tuoKIoXWMGJqMV6SJ2vFKb5maT9lMq4U=
*/