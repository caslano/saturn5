// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
// Copyright 2015 John Fletcher.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler

#ifndef BOOST_PHOENIX_ALGORITHM_DETAIL_BEGIN_HPP
#define BOOST_PHOENIX_ALGORITHM_DETAIL_BEGIN_HPP

//#include <boost/range/result_iterator.hpp> is deprecated
#include <boost/range/iterator.hpp>
#include <boost/range/begin.hpp>

namespace boost { namespace phoenix {
namespace detail
{
  template<class R>
  typename range_iterator<R>::type
  begin_(R& r)
  {
      return boost::begin(r);
  }
}
}}

#endif

/* begin.hpp
kNQ6+zRROP/i0yjkxVkK4v/YsUGghamrkhg55t1Pl0FUGJpDhgoH+de/CNRz+Ey0/34Hn9RYSW6eJQaIdg0lFHNF0D8sg8woOI+j8B7CcS7zI9TXs1MUWD9epqQymOQKAVZK2yVQh2fnep7QNgji5lRXhZCeLFlHmDKqJWHtjcofMkHvstM46hAkBYVOAMCyAIICUB83Dylj0GzvpNk91kHEPJFm28ahi0iukZKyUaFJnSUiRlYF48GD0z/+PhmO9k5OHgbO0GGCu9Yoco0VRtgGkPnTsA407msAw8sPbw8qQIjxIhAxVgFm7/SIQECUneZjlswx1W3WlQTP7xWv0R+PwA08R+qBfdyF1Ks5DeOxEr2WeQ7uZre3e329O+2bEeJX00l81ktZ7y/YzWmpx0JhHooqo1fMWSeZqHOqRaQ4iNI04RS6Nus2VupUbUjqohYg9+tIrIsXPGoeymGqvHDxQAblLw9fGUSQDD0JqWfj54VxypuHLYNfAiE0pKzbJZRqq7PlzBd9hUGIQUqJJ2ArBmV+4KA5xCIJIBV2VOltVyy6jpwSfQj6KF24Hve/dpPraGWb1Y3m90BL2GH9BnQU5tC4XO3NwN1Tao0+1/OpPInqiv49ToJpELkhS+KYigo1c05MxkEDRMpt
*/