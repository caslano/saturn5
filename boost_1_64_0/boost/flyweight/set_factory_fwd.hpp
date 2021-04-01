/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_SET_FACTORY_FWD_HPP
#define BOOST_FLYWEIGHT_SET_FACTORY_FWD_HPP

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
  typename Compare=mpl::na,typename Allocator=mpl::na
>
class set_factory_class;

template<
  typename Compare=mpl::na,typename Allocator=mpl::na
  BOOST_FLYWEIGHT_NOT_A_PLACEHOLDER_EXPRESSION
>
struct set_factory;

} /* namespace flyweights */

} /* namespace boost */

#endif

/* set_factory_fwd.hpp
4kUgN0XTkXOfDDMkJKZI7O+E6KmVHNNqRnwG8qfs2LtDG/prXjDBWs6kBXrMkWGiIIeea/hPABd8BZtFHZxiTfqjvkvdrHGgb7NUsujLxujGaJzYr0nuLD6sKMhc57KjJXea+5T1iPC0Yafa2lv6RH05vArvSgyDcUbbF0ISGKIBEdqj5EpFLiqsWns0618zDTof8RdPlUqd8Zr1r4tdU1iZ+YFMoVed0Gnv2Rk2YZlw+qKHkqwToOZBiVlTElcqEwluZDp2UO70nn+cIHdCSV9fuzgzwZryPTKhC+1TMXsbekU+BBqPsNcZrHgW4iP9Zu2OjM7ImAZIKMjiudbGS+DLe48gOK1OwXMpaMyI+GYa2ztEaRrEKKTYjM69EEMP7XeE4x0UMMjn3gup8zbcXwkGFNFLLYK9VLkt0RW8ufOpOAkwRML7Kq++LM9kkLW5UH/YgFeefQi7RrGuKTVJEUgd5NvCoKGXlUp/AGrmxrCyLYf/us3s8no7oUsp5ukPbfJHM+BazGmKaRJ5Kv7yUrqwem2hXX9iJpn4rrgcAMH/Tj/O4h/Dx/0O9A==
*/