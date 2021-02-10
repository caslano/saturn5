//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_ITERATOR_TRAITS_HPP
#define BOOST_COMPUTE_DETAIL_ITERATOR_TRAITS_HPP

#include <iterator>

#include <boost/compute/detail/is_contiguous_iterator.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class Iterator>
struct iterator_traits : public std::iterator_traits<Iterator>
{
    static const bool is_contiguous = is_contiguous_iterator<Iterator>::value;
    static const bool is_on_device = is_device_iterator<Iterator>::value;
    static const bool is_on_host = !is_on_device;
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ITERATOR_TRAITS_HPP

/* iterator_traits.hpp
DOTju5RlJGkPSB4iwyJF7c7MDpeK1yHevtoVxB4Oz15Z98/oonGfNDf6X567/0/IsnvsfpS4pvEFVCM8ZN1nQ7wo6x6DLivruY79PMteQLf2Iv1t5JPXmZ/Syi6zzz/RzdaI68phcDLEu8+fP+EA7w/fH0Y4ZUpwidRxteHmOsJx0a18rdjdXWz5lwjcgcn4CeCyEhZWl+6WGQ6aS5FzZXkBZlFwmxuxoQeh4CqOUkiOk9l8lUy/R7itRF71OFvdwla6lQUqdsNheM7FzQ6mYcZBl4RA+IWwjjBbJ7SKiZ7DcVPbHsaLYNJqsBsmJNsQHXOonGvsn6NR3hpJlYwKndtRvrcirlz9S1UrUlOzLXTj4DRayyP4+Ai1LkTpR7KIFpt2I4WtogdZRKiKkTawXMoejlIFt7sSONLerchHoiH1wvnBamU9222l6yeBZGsPVLZGER3ZQnGFJuMjtKrgpovvjNiz9C53lj+zZQ/aC2hFqhCOUyRpiA2zwka4SpZns8slrsaLxXi6XGH2N8bTVY/3I5meUm8IYjXgd43hllQYiLqRghdPyF/xpC/P4PczuyHnqBdwhPADLpjJK2row3chQik2PgIf48NHTxdMtUyGQZyeYTq+mARPUA6o8xy5bDsT9zn7t94ndd2l
*/