//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_IS_SUBRANGED_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_IS_SUBRANGED_FLC_12NOV2002_HPP

#include "boost/numeric/conversion/detail/is_subranged.hpp"

namespace boost { namespace numeric {

template<class T, class S>
struct is_subranged
  : convdetail::get_is_subranged<  BOOST_DEDUCED_TYPENAME remove_cv<T>::type
                                  ,BOOST_DEDUCED_TYPENAME remove_cv<S>::type
                                >::type {} ;

} } // namespace boost::numeric

#endif



/* is_subranged.hpp
wgiZHWNsDoarVJMPCs8SLYHdMpGwOQZiBmJjcn3qeUGhEkTvhTLQXtCkfxybdJXJNYJI2RJkbsBIKDR3gTRdSGUoIlqxILiZF/NE6Nhdo8FQWehJBZonCflCO8F1BZvDtC6PS2qQI2JhaNEy0xTqLpbpliLWkbxEhcowENYBlUKJZXahyEKuSuUy8yZEXdOywE+2Zo03BJkhGLC7UxhMbZgzLbQLHwazi/HVDD50J5PuaHYN43Pojq7J2fvB6AxbLzCYAn6fK64xuAKR5ongYR3zyz2e9Z3IgqQIOdiGa2yVbW1spTwN+bxYlNse5ooq0LuaDAej87E/7V30f+sDOrFEht1EYSuImYI2ajjWnxaUutAmWrjQDoucw1sYXQ2HHZRVqjqIecrpM/nAfFGDrPr++H3Hwu1FIucs8UUmTIsE/rvh+Nfu0O8Oh06pwJleVmKKU+01WE2M7KxCUGtyJZEQyRJIXbBE/FH1iAz9lR+scpkU1HDW0gU3Iotkq0roUSFc+L6K5JTZRC20doCqABDlCtOLWtogr5QL9pE+PQp3eHYgwnOFqO6QA0hw7ALqtY60c5PZrrU9F88HWCbfxTfEUb5hSHfDKxIRw0lVQilhYT0l0px65QcJZ1mR0/bHCnFdqWdVk/aAb8qK
*/