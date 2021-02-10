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
T3hk0WyQoe9zfxINCe6474hHBZ0+zk4ZTbDrHrnxMfhCg2Fe90wDTk/BSEyHnb4BE4FU+8IRipLFSXoMJ2Uo4cGSnOaZog7FtCdsy0uu4ezy4uzb8Kr952m/e3tRbO11z0pa+xe9fq+k/eLv1l83VxfFLgwxPG93TzPT227027QdM21rdb8exo2/neAwIgsXlGItOVHJyA3z91E86GSoqJ1k/4Vccc2SIaNZk+cs658M2KcOiF3UzNfWEzUcAPMUW3ZwX+zAvOCFPh4fZR7l/C8q8KV11VvqiEUo7cp0yHpXQFHSXgGlNG5+NlQNBUXU6qVg1hBThnNjMOzJwoLAqsSznp0UbYInyZoseIeNuY9VIFlJaW9xeSF2M24vxkhmZej/9MWjn1hEqeI1o1w+1vAmWVPzRUdLsLjCFupWtAXeMOnRzklFJrC0S1YBtdXrD7hT4P4HHzq3V3D0kf4ef3xzlKxTJqWQHm7gHhylUCl8W2OZ9/c0Vn2wC6lw8+G+0pbn0Y6LOxKNnjYQykshyUBlxLEn3CpQ0t4M7xOm51RHzQHBNYr8GTet/uXpstlgxP0/TOo0jXJe1yV5/y6XZn2i9++WUy0ng7S+E7uZ0aKcJ7bwx3wSSpZVzWR+mGntzHHdwp0H2R0x2nrY
*/