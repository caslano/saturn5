/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_SIMPLE_LOCKING_HPP
#define BOOST_FLYWEIGHT_SIMPLE_LOCKING_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/flyweight/detail/recursive_lw_mutex.hpp>
#include <boost/flyweight/simple_locking_fwd.hpp>
#include <boost/flyweight/locking_tag.hpp>

/* simple locking policy based on native recursive mutexes */

namespace boost{

namespace flyweights{

struct simple_locking:locking_marker
{
  typedef detail::recursive_lightweight_mutex mutex_type;
  typedef mutex_type::scoped_lock             lock_type;
};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* simple_locking.hpp
k/TjCpkZbSakvQ+tGGVO3x4T1TMdj65IEy+vce6ncq+3HsIum8O4ukqX/wRVRYJD/9cbeZY1MyY36scEtR3Od4jlOEi05chCJHoZ+9FTlCUBripb1WNayW1zIK6fOqqnPAbKc80gStCQZoapeNBK/S0ML+BaXs4Gg2934zDZ7tIJIWHgj7xqWxQD5ZK3/idDn6RnfKv3adqdAdVqIyoqbc4yIg1dOTw2iucyHH0Bz2skAOcyUA0B33tgVmqX3VjEfIpMqP11pwGAfKQ0FZGXNuAmN4ZxGuu9p5lnWVG211zsCUUDAg8+SlvxrcdbVuRzjX7AMCRdQfrXet4VC7UZnvJBpIojGa+1324WBebLOz/Dc+asM6SJ3Ec8c0+dX23EohbjBGkkgKG9hAaK7VLKIHXmypDqKA44AnC3BLC+GcL8io+FIVA1kr3Y/9iVpaiugb973RrXb5rKmcAW+4uKeDuD8ZHZmAvaszIf+HIvSHZkxJ25zv2Mv+sqG/BYp3d4NFDaoo3yv0UBqa+frSKd39IAZMalqUyRJVobJl51glsfKV2OOO67MCbrlw==
*/