//  static_assert.hpp  --------------------------------------------------------------//

//  Copyright 2009-2010 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt


#ifndef BOOST_CHRONO_DETAIL_STATIC_ASSERT_HPP
#define BOOST_CHRONO_DETAIL_STATIC_ASSERT_HPP

#include <boost/chrono/config.hpp>

#ifndef BOOST_NO_CXX11_STATIC_ASSERT
#define BOOST_CHRONO_STATIC_ASSERT(CND, MSG, TYPES) static_assert(CND,MSG)
#elif defined(BOOST_CHRONO_USES_STATIC_ASSERT)
#include <boost/static_assert.hpp>
#define BOOST_CHRONO_STATIC_ASSERT(CND, MSG, TYPES) BOOST_STATIC_ASSERT(CND)
#elif defined(BOOST_CHRONO_USES_MPL_ASSERT)
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#define BOOST_CHRONO_STATIC_ASSERT(CND, MSG, TYPES)                                 \
    BOOST_MPL_ASSERT_MSG(boost::mpl::bool_< (CND) >::type::value, MSG, TYPES)
#else
//~ #elif defined(BOOST_CHRONO_USES_ARRAY_ASSERT)
#define BOOST_CHRONO_STATIC_ASSERT(CND, MSG, TYPES) static char BOOST_JOIN(boost_chrono_test_,__LINE__)[(CND)?1:-1]
//~ #define BOOST_CHRONO_STATIC_ASSERT(CND, MSG, TYPES)
#endif

#endif // BOOST_CHRONO_DETAIL_STATIC_ASSERT_HPP

/* static_assert.hpp
3L7DJ/WgI31ootMvErac2FX1/VL7v0ryUoPzmubGt1PCpli1zXZ3jGokTb9VibWzz0n7VO9dKhS/1TSN6LCxnzOJ3iteVfw3idorvlzskqOeE2lm22FT5nkM99i6iXt3xtrNNG+WG09puRTnjywaJA80uOMEys/Jc4613aRJPxXPHKR1r/B67U016aeynI5E14zVz2D8OM9w143uZ9R9gbonxd1UznZOtDuapFP3M6mwWM5J
*/