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
/cvbVC2sE/aPJrF/kWLf9hLUUCTgDRsOM3HecHbIPvnb5X6fVlI9KVV6VyfzZwN1TEq0kq+/oPgzPgz+3O5EK3nwJSZAZsobknXJ0FPL7ML342nmh1N5emxfHzzN/XCCJ5/mqUZ4GpTEkzPBUzV5+vaQU/P0Vdf78BTsxdOovnjam8TTJ5WeMS3hKSeJp0Wqm8HMG1p1a6Ch4TCjv3r6qWswzfU+2qfwolTtE/l9MmcaaCaA
*/