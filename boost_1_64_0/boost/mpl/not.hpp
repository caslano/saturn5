
#ifndef BOOST_MPL_NOT_HPP_INCLUDED
#define BOOST_MPL_NOT_HPP_INCLUDED

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

#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>
#include <boost/mpl/aux_/nested_type_wknd.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

namespace aux {

template< BOOST_MPL_AUX_NTTP_DECL(long, C_) > // 'long' is intentional here
struct not_impl
    : bool_<!C_>
{
};

} // namespace aux


template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct not_
    : aux::not_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T)::value
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,not_,(T))
};

BOOST_MPL_AUX_NA_SPEC(1,not_)

}}

#endif // BOOST_MPL_NOT_HPP_INCLUDED

/* not.hpp
F+q5OLFAv5ab9sNQkT87YxMZums+FEmKv8crFTyy7LlCrldv7pzKqh8SeYd1Da2aaTpdwRbcQYRtKYSgt+NhEgGaJdO3lC0iBY3WJCYg4nQkGVTxqijyEiD/gtb/EXLDrmbwCL+03A060VPf61nhvFpg5BBnqgo4WkXROX7LOjqoDZD6JxTbYv3sfbJYjsKAovrSXwxbGI9jhkRM28D/+hsMnldciVx4TtINdNL/grmGGMQ8ZZBYYZWB684Cwzx9p/RCGaRNXJeMwjy+QatMi3ABIWPy9g9YFDED6jw5Y3JZJbYa8qFMS+54PvVRnoYKKjRZiSs7VG8NM/Hqfei5zbCWxLPrJET05x7DivuLCniJ6Sy/K6UzK9B7jfS4Ca9M9ehsrsMESIJiLvl5K/+7Qe9NCSsCpZnOBwHk02TnvB2Skk7IL0cBN2Cx1zps9frcUP/W4RhOwQAIsSuzQTSrRy/mAElQOCENxdZQXo0CmNhXTQM5uwy4UqM0udEouYq7iWxhM5OPf71g8kdqmPVDUMWj6XhoKn0dCNjdQS2OvYOu2duxLNyyLL6yLA==
*/