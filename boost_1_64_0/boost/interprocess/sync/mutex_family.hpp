//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_MUTEX_FAMILY_HPP
#define BOOST_INTERPROCESS_MUTEX_FAMILY_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_recursive_mutex.hpp>
#include <boost/interprocess/sync/null_mutex.hpp>

//!\file
//!Describes a shared interprocess_mutex family fit algorithm used to allocate objects in shared memory.

namespace boost {

namespace interprocess {

//!Describes interprocess_mutex family to use with Interprocess framework
//!based on boost::interprocess synchronization objects.
struct mutex_family
{
   typedef boost::interprocess::interprocess_mutex                 mutex_type;
   typedef boost::interprocess::interprocess_recursive_mutex       recursive_mutex_type;
};

//!Describes interprocess_mutex family to use with Interprocess frameworks
//!based on null operation synchronization objects.
struct null_mutex_family
{
   typedef boost::interprocess::null_mutex                   mutex_type;
   typedef boost::interprocess::null_mutex                   recursive_mutex_type;
};

}  //namespace interprocess {

}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_MUTEX_FAMILY_HPP



/* mutex_family.hpp
DN29P7xJuA8w+oMa4n83wkcnDNfnx8nt9YjBOEE0GOmiei4kSmH0pDA+RRjfJ75XI3z1KshyeJPcH4z4GHI5ql/JbdCbloEa+UuivJQUwqPIvwhmIbnnwD0ChGeGn06eMuf8l5rWL666mfKPszUjOM+4Iz9J1nhY/gPIjwZJzeNy9MaTQXoZolFPT3eFrwB6Gbx8SefCniLxTVLy9WS+3HO9+hsWkeLYaHSt7wvt723awE6Gqp+QcVSc69Xj4N4AZtkHNOOrAZ+L0lKZjsRYdbQw32FvWtqtvYB5LHGelmF9wmGp838e66+NWjsMubLqr2W+TOaDnon3/PFcC54bSS9M5c7muij64769aH1wLwWls+4JoRe3TOqh8NFH4QyijwL1xEcfhagDrI/Chr1H7nt817K4L/HV6zKB9eMf4D5oP+gNUSdWU18oKucc1Gqqr/dQH1gMhWqlRntaQnxbtEsh3SVq3fgUlm/fSO3EaNszyH2fNptWJnVF3yjD8OkbuM1cQ273aZPAeRPb9h1GuSvAYqi0I7aO+Mq0NIQyFSlL4DbpoufDtES4+PQbZhujxNOe5iJJ3TBfP1/UU7aT0JbsJFzm104C+6k539tWUq1jJfMcBk8x6VcaLnUHNrMf3AfuN4PcVKfs6f6uXW3UH7r/22qrDmZRvslcvj71icrLdww9yTr303kMvQj4I7H+vYbqjedDu98xVM4p139H8HfXr9LuUNUdDk/qhaf5b2lZCdJjlP8s4vlRRKq2WH8BxaGoPwgntLGV+ZuNk3JsfYTSPcjo6/9G/MvQb8caend+STyr9Wiccvb2/30qPTb/VGPcNRTGjyP6aVfpP0A+vGPcUPKTZoy7+cT3pXWM47StJPdHI45i7jwA2uFU6ZFzbp5LcXueSH5jHe9HeNrR4HjiwZ4OqQetjniW64l4w6H2YYSdKMdC7oO88tlC7p30HJRzF2+7o3B+H5GE/D6M/D4d0ZbGuBz0SQ3dEUKAMa4780WnedvhhTR2tcHYtQZjF67U4xb7y0jztsUspS2oBObLA99ykQ6n+y1Le2SeVWne8dj9vHJsY74a8K0QfG3cT0mdbL48h434Ku+W8fnynDLCqdziLxwn2meF4Ildl9x8vJqMe1FEP8X9SlyUgPrQuIV7ti9wk9RLhjErANrUrzS20nc8QzsIOJ6l+PQ/ss2rxzTf9/Aa1g/fifUwngN8QfRNa002XzyzfL+2e64g3ghd2Set5b7EWJ/gwEz92hDiidWXaKVq29prA79vnwO8lHii9ana3eo+aq1/uz6byO1uYw45eh3lxzTvxMhuege9jPjb6XLsZL2p3vk3uWdw/qBtje7FvGCqSQ8ZzCiZ/PyKeC7QUnz87CM/pQhL1NVTqKd1PfGOLtpi9ECt+ZyvC/Oc8vI4rhaN3FHqjI5UjrXM7+wFaQh+p8vStll3GNsHk7ZsejHu5mfPBh5bJ6q/K8q6S+tGRt2wZ69oMOsN/0T3lPHHwN1Cd/E6U92lpYAFiwvRIvyt9bxE/D9Q1V8OS7esY3j76hpy/5XeR7vXOpayf3Xdle9Zh4jnJf0mra1+nx6trL8cjmqNw0jLG8SzVT+oPW/M1867RTyboKXin2ocfZD8vK9/BO0Bz+mRxrti1Xpqk8a74j7ie08XY8neXsJmAa+RRDqNseT5AGNJAvuruMi7VjLQUtfGMU9tumf9yOHeG3MDFqDOiYp0xl8UFeVIiOkf00MQHsbF9IuZENMrqqszLjEq1RmTBKsbMeOjIpzntA2lzir6JWPu4KkXL+vesbwnyeQLzBR+ripPfjf39Zcg5nvkr6PeVzvKNqdgIZfKJVG5/reO+H+p7dI=
*/