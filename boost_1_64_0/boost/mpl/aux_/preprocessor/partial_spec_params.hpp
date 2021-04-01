
#ifndef BOOST_MPL_AUX_PREPROCESSOR_PARTIAL_SPEC_PARAMS_HPP_INCLUDED
#define BOOST_MPL_AUX_PREPROCESSOR_PARTIAL_SPEC_PARAMS_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/limits/arity.hpp>
#include <boost/mpl/aux_/preprocessor/params.hpp>
#include <boost/mpl/aux_/preprocessor/enum.hpp>
#include <boost/mpl/aux_/preprocessor/sub.hpp>
#include <boost/preprocessor/comma_if.hpp>

#define BOOST_MPL_PP_PARTIAL_SPEC_PARAMS(n, param, def) \
BOOST_MPL_PP_PARAMS(n, param) \
BOOST_PP_COMMA_IF(BOOST_MPL_PP_SUB(BOOST_MPL_LIMIT_METAFUNCTION_ARITY,n)) \
BOOST_MPL_PP_ENUM( \
      BOOST_MPL_PP_SUB(BOOST_MPL_LIMIT_METAFUNCTION_ARITY,n) \
    , def \
    ) \
/**/

#endif // BOOST_MPL_AUX_PREPROCESSOR_PARTIAL_SPEC_PARAMS_HPP_INCLUDED

/* partial_spec_params.hpp
tl3CvT9EnQpAl/Rdhvg654kXROcMsK3JHsI6a5AP8CfQPpJCEXx8b1prbHnzFgyu9hSvx7WpB1fK6bHl1zwWh8dcWWMu5lM09Tp0eYcwDJ6zXsQjesnTPp2uoaWV5/XU9GDp11lcEFP9FWSSiz7fG2ZnuO4uKunt6KoBzakDD5dMmbN7KInXKWmuQsD3yI2TtclUsCggJFm8k7zqi7MuT78CG91yJUZCNDc1M3TVYOprwHdbI1U/6/AC2y+NesM0FHQRGjXs8qSxG440Kc+stDJGpJoxese5SRoHYQQce2n5FLu42OdFSXFTsFGTTYy+peGWQsVKs1XuEvBTBjsdXPI/3CSV2JKI/izicMJHzHzDt6BGzcwO/mHWAXN+PnBIymk6ow57HwoKuaK1bLLe5IaSdrUlNoOyHZqcFUUhqS9Y4zEE2XAEx1X17S5sXsJS+PauHi5vb/Sumz5hkoVkkeicejEgjqg9zyFxUL3Ol7sQSWUqF5YyEm+DvgdQBULFdH/Jne7jZq8X4yXLOfaY8I5Aa4/82JWAkRFarv87fNXkt7C63m0NqtBqwA==
*/