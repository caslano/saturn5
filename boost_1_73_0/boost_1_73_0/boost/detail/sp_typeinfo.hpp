#ifndef BOOST_DETAIL_SP_TYPEINFO_HPP_INCLUDED
#define BOOST_DETAIL_SP_TYPEINFO_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//  detail/sp_typeinfo.hpp
//
//  Deprecated, please use boost/core/typeinfo.hpp
//
//  Copyright 2007 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/core/typeinfo.hpp>
#include <boost/config/header_deprecated.hpp>

BOOST_HEADER_DEPRECATED( "<boost/core/typeinfo.hpp>" )

namespace boost
{

namespace detail
{

typedef boost::core::typeinfo sp_typeinfo;

} // namespace detail

} // namespace boost

#define BOOST_SP_TYPEID(T) BOOST_CORE_TYPEID(T)

#endif  // #ifndef BOOST_DETAIL_SP_TYPEINFO_HPP_INCLUDED

/* sp_typeinfo.hpp
WybLV7kaHu2ZtFNUMtbaqG5eTNdqKbRIRQmqpinLWdrlZvW52aAa5Am5M2mjkrE8aZZQg89IWNpVVlEkGQexghtGcFhW8cUnP54vBih7q3vcH3Tj/Uh5mwbSkAr+veFpC3SLQ9OGelLJKpqGRn5dEX1myLFZdaTGkeqTyASuFC50ty+xvr8prVuwvl1ECtwNgAxSs410128c/h+YnYJm7moeW/5qPm8PlmEQB5NgHlkBL+/BW7hLG5bB8qitJ1rEqIemroV8MQMd3PQvd7GcTy2H51an6nbsPj3RPONMD1G/LB+awz34x4L/j4Q5eBwFvNgwMM3HNU7vCK4W6qSiGg8Q6E3vF4O061DrKlEVT7PDRWwk3KX2HDtF4fKm3r3613Jy1hbtfnO9ufvFm3vx2nKzrGs0rppj56A1CKfxKvThmztfTa2Qalzjqs1umgSXwLqN3fFoFnLPL83s3mjlX/rB1a4E44CNt43aepBVnASzZDFdBOG6x8NpvEUhM66aHIXOUL9QUFKj9ElKu24NoukU3HkU4Nb7EsJLCcIARYh8/XixdKPoKgjPdy+s/wBQSwMECgAAAAgALWdKUi7TSVjmAwAAnQgAADcACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9D
*/