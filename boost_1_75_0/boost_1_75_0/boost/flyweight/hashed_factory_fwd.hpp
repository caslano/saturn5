/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_HASHED_FACTORY_FWD_HPP
#define BOOST_FLYWEIGHT_HASHED_FACTORY_FWD_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/flyweight/detail/not_placeholder_expr.hpp>
#include <boost/mpl/aux_/na.hpp>

namespace boost{

namespace flyweights{

template<
  typename Entry,typename Key,
  typename Hash=mpl::na,typename Pred=mpl::na,typename Allocator=mpl::na
>
class hashed_factory_class;

template<
  typename Hash=mpl::na,typename Pred=mpl::na,typename Allocator=mpl::na
  BOOST_FLYWEIGHT_NOT_A_PLACEHOLDER_EXPRESSION
>
struct hashed_factory;

} /* namespace flyweights */

} /* namespace boost */

#endif

/* hashed_factory_fwd.hpp
j/sWxbzP4tRXJJ+yf/lHYe9jlvl3mUHm/eVO5r2WNX5Lf4d8SvryD920n893mwE5gWV9DctL0ul414BWgLtBvTA7V9dr7J6fU+2flEKLypsUa5VEkcMBfgE2UorlzzB+rP8KthIs9F6PTPH2z/L2zy70VZwu6vJTUfWP7i6N/c/DAeId05X9dbcsZ+SVe/vnM7HiGl/ovTe3ZdSKbNg7t7aTeJBCKKHBhBvwljSTJc2WyjLBgVPovbOrJA9O5bnYkyCXREnun1rozYcLS1GRBeXUZ2Gh/fNB7GVL3nzD5tVBuzCmXRN68wrXJ1MSdZtXILTUdd3SUTBWYIQ8OgpHSO/xeOk5HkcOGyhzRsGKeotiHcKmAXo0aZSq46t6QI+PtT0VFWhHU/mcdpp8c7TJFw2Y50Mj8N3sQyiTWUm/9OOJ4cvWdu4XoNff1C2VhxMMakGgr+wjH+nV0eMOsQwNUFPesgXqZ2wZKsFY453Uc0ZxpwK9ox2+QVX+d5lS2FLCGHE1W5MCAowrQyxKQVDmo2CbDsbny1gmEl+JOuCdDd+NbWnf+5B7HHyZjDmWTcZDW4azTKm2aMwXD8YbnWUZ82aMRR5WjhXCbuUtoXxmq1bqFaZDdDwgYBg/fH0wrlpA2/Q+dleOGJ4YNIY1ckFHl5NVc6hal8LrA1YckaTTqrgglTweOutfN2O9Hi/jaw/PwXyw/65Qq5FT81WV
*/