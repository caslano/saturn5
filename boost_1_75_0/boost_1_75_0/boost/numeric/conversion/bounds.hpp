//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_BOUNDS_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_BOUNDS_12NOV2002_HPP

#include "boost/numeric/conversion/detail/bounds.hpp"

namespace boost { namespace numeric 
{

template<class N>
struct bounds : boundsdetail::get_impl<N>::type
{} ;

} } // namespace boost::numeric

#endif

/* bounds.hpp
kBZYNt/XK+yZzdTD5HR5IFtzyhrspwK3kr9Os7ZdZQyHDvCYgRXsD2phPcqIf96D5uJXuXP+Su58v129FPVgGDlAQSsnnMo8g8P2u6iM4WEBRfIu5C5YVoBqsXIgHG82KXVOcqaUihnh0bTzMz0xkFudHSAxqKFDDAvhjhyOccCnF5NjHmdbFOv+BqPAhb1IVIQU9QbaADBCFGavFUihB9fBuIWSII9hkTGhKo/FkPRoGAonp8iGeidF5hALTRGpFN2qV6YoRfTFJKQgSTjWYwZaIAn7JhiFDSadD89yym0U+xXlch1OHBqjo3CYWlswH1aoV7YGYM+52yggTDFIpYDblOWvqloXPaAzcGhDAlKZvbNdQw/lq+TtMfBGIt01vB8ROLyVuIZQCrq/sfgKh9aExuaogAHTl7YvFzwWXn3d9xtaWLnnokPeG/FbDPHIGUI3wN8dT7KiFBRaKc+wd676bUZNwvEhWFWNLr8fgqjdIUaQ5zF/UYyUgDSwyBkyhZbSiYU6NJi+xSjwiAAMmaAfDCY62k+T+IAQtso8zMOkWX+9Au0JtamezFb/T/pueCeyDXgYEizLy3ey3bCK74ZVNLWd6lDMtgvSOdI9/FyJI+jCYK3VjGgVOmGH2I6JyoVY4d6Ru1AQK4cY2UYpd7Cd8o6+cj+fdad8fs6dUs53ytMddsrTbKe8vSVqpzwds1P0VZ2IchRR4pXp
*/