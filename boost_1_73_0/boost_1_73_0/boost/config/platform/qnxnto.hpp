//  (C) Copyright Jim Douglas 2005. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  QNX specific config options:

#define BOOST_PLATFORM "QNX"

#define BOOST_HAS_UNISTD_H
#include <boost/config/detail/posix_features.hpp>

// QNX claims XOpen version 5 compatibility, but doesn't have an nl_types.h
// or log1p and expm1:
#undef  BOOST_HAS_NL_TYPES_H
#undef  BOOST_HAS_LOG1P
#undef  BOOST_HAS_EXPM1

#define BOOST_HAS_PTHREADS
#define BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE

#define BOOST_HAS_GETTIMEOFDAY
#define BOOST_HAS_CLOCK_GETTIME
#define BOOST_HAS_NANOSLEEP






/* qnxnto.hpp
WC2wxcBWAFsD7CFgjwD7PbBngb0BbA+wI8COA/sc2JfArqPXM+di9YvrrSVqgz5dbq9Pl+PowssmOMQT/mc5p7IZ6RsVaamQIYXu4Io3XewKqSusKZWBPKFIcYhnCm5w8YR9oYYyn5yqVk2NtLpx0RWvcvdpf0qxiPGJnDGtzCllxy3nwqkRwV03uOT8vBzoqILdIidIRamlotLinjOhSql4SPsnIrfxPLw8ejtys5xuZQi7K6a9xe69Qvc1rkU=
*/