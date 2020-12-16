/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_IS_ACCEPTABLE_HPP
#define BOOST_POLY_COLLECTION_DETAIL_IS_ACCEPTABLE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <type_traits>

namespace boost{

namespace poly_collection{

namespace detail{

/* This can be further specialized by Model when the std type trait classes
 * fail to give the right info (as it can happen with class templates whose
 * nominally existing operators do not compile for certain instantiations).
 */

template<typename T,typename Model,typename=void>
struct is_acceptable:std::integral_constant<
  bool,
  Model::template is_implementation<T>::value&&
  std::is_move_constructible<typename std::decay<T>::type>::value&&
  (std::is_move_assignable<typename std::decay<T>::type>::value||
   std::is_nothrow_move_constructible<typename std::decay<T>::type>::value)
>{};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* is_acceptable.hpp
Aq7uhbnvhXw6S/dkamhqqd2U8/qR9iF5GInPjE3Sh9+9+bLVVhtcNtIcf+bsGbzdw7Rt5R1O5jY5+vhmoXbs9xO1l8ECrUNobz8z5VVx1i7fW+japaGrZbDVXUX19i/n6Cz8+o/e/4mUI1evJy298fbppvAe9j97dMts+XuV/wKmrhYXaW3fBiP++3mPemUt1nNtVrQoyu7CiL/iReE6xL/scMYi2w5Sgco+AZqRTS6RY6fF0G3fVgN5enzyojxdt4Xfbzh/kXStuWrYJ5ZJjpoaYk6itq6tprUh3k4oCum7YlGEH4f60Uowlt80VLZ5ffuSsC5UzPWhOmjNLewAwgfWief6RSHbh/ZuNnn02gZ283gRVHTZvSWXj+a6LV4/ay+g17Ac28D5oJrugZ5OxlfuX7Eooq9L2265ET+OvHATbwKxDcarrzOXn7bKBk+O7jw/yPXDAY+eW2Vof3vGxrj0kK72h3UVerf2moL2VzvS6ZvCtt3s7d1ZusiNAa4ePR29I69f5Mant0DPb8zj9X2WfvEHfCVXv1XQLUFcf8/e/2Aub7XoN3v/Q7YdPRazej1SoH/bfH7dLitJjH9cj53tTmf64535/TFv39p3FkWPSeH3Ur4HbhPvKXh9w9PPD/P0kxsz77F9IcJXfhWKBWH9Ljd7f9marKEhe/9e5PUY3tQab2mrM7LcW0CWsMz3LSo07sgVJfNEjn09/+rXu/dG9x8AExr0s7LdH9GX7L3r04sixovQntCHIuJpeA/Y58DkCSLePhHuI9rr+vcIv7b7+T8jYqulw6gY0oqPZ8vOWhwll0RXH3/c4si4Z7cBn4xZiyP8Q3xWah90ooYfn60ZzDQP9Le5c9VUWyrJgmUbD0draJR1h3XA3X0VXp1nLQ7HzFyfXbA4FOtD712/F98LHNqT+ezF0XmQrdMnL47KD3P9/aOLzHu2vPmPWuPqx2WLI/wglIstXRwRm0P+dJGHsbpO/pj5mbDPtHpllxXg35ZxeRQPof2tqxeH4n8orn8qt/3N+FXWZ56/uMC4EJIxFiFjOE+pzddn3n7v9RH1hPvAX+E1FLSzPvJO7re01xMsqVm+vNHWTUgvz9S+GY4Ddx5n9tUkh/TI1F0/29mzjwXTCifA9s6aGVvptits+WwLyw+felN49Cr6EZvOY6kMqzzej01lN/6oHmJhsY2Dfe0LOkf04zZdkzFDi5VYNNbeHYt2Uw5tz3Cy1+L9cRZNe4nssjeLHrkH6rRcmtj1dXhriB6lcIM9MGdmLAqnXcl6egjbzwX9fNEnwnTOZUp426UkF33gDAujbRKG9qhoUXu3Djw+RJPQxtalc0N025CWz9wUxkkIU8+yM0N0Swi7ntuFK7RXrPwsi262e1j7i8ezdLIAe1XU2rsbf4LoET+Rb9fTXmrjBLD8qHGeSydSZJeq3d3eAe1ElqZyA4PZFeLFou2bD411Gv2cj+SivQXcj9gDZ8pNZunUp3JGr/ct5H5o1Au24gQ+1LgoCseWH7tfR2HMlh2rrvrFUTi27ViYoxEYbSFCZtVzNpjQW+WwRB3qbxF0VeH3s9VLhAk9ebbYpj3xJKz1lJbmAp5XPDFMV3OW3W+xMVKgoZ17jkVTUbPf+DqPNsPjI2QSdtlThC3w+MiWae75whp/T3rPtytFHw/T1XL4MYm9dzl9wWOW6fX27cl3l+bicV/W7ncmB3sCO2UuzMFESnW+2r/lacKGl9Gt/ln7dGHsxxaWL8cuEt0+QUpvjqYsXU8KV/jxW4DtfkYONlIG6ZBCws7w+MvW+YEQPrJ2y+8fNngOs0r2R1RuYeMX29iIii293lwubOhxj+In56xG0hVng74=
*/