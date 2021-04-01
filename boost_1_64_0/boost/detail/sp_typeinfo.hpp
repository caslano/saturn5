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
a4joXjq1OieJIbF1KDcky9/Tf4rlff33lr0gVvLYT7GAQ98gnbgKwgao1SJ5TdYoFA+GbrI3JnPLPxyUhV4jc57Wu41ltHspu0tpdbwnRkZYWvpaQiht+Euo2SIVjmcvuAI2Gd6y0qi6ijB3LaOSgCYU3qmveosaDGejkVK5wcVUCv2MIVVy1YSbhtN21DYLY2j0WUPot5FB/O34IiwKoRxNPpglfUdZxgxsTO5df1/JFCq0Bcx7juK61UbnqR5d6g5Dgy2fWqJixGbzSPvNpWa06xExH4BNRsPhD4uWegiNuZC+czDaGimfotc4mrkOo8s2rSJ3afdFipeiU6sTWIYnTeQRmJhaYtt8cqMysCq/FIarIir2/dC+EHS8zmI+oi+rI5IKCsjsokK2WviwxGCUSt5HY01jyVaMwJ786MyY2IXadKKNhZCNOuHkv4GSFcYh0iUXexT6jAnAdOBk0RwAQh+dov327hy+SQmE35ogfWTViGkKtMWfymTVA79OJsCvIc5FmQfxXni0Jm9k2fQWtpytgqOq+/fls9OiPNBCH2AOkF7lVP3Hww==
*/