//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2008-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_CONTAINERS_ALLOCATION_TYPE_HPP
#define BOOST_INTERPROCESS_CONTAINERS_ALLOCATION_TYPE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/container/detail/allocation_type.hpp>

namespace boost {
namespace interprocess {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
typedef int allocation_type;
#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
static const allocation_type allocate_new       = boost::container::allocate_new;
static const allocation_type expand_fwd         = boost::container::expand_fwd;
static const allocation_type expand_bwd         = boost::container::expand_bwd;
static const allocation_type shrink_in_place    = boost::container::shrink_in_place;
static const allocation_type try_shrink_in_place= boost::container::try_shrink_in_place;
static const allocation_type nothrow_allocation = boost::container::nothrow_allocation;
static const allocation_type zero_memory        = boost::container::zero_memory;

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif //   #ifndef  BOOST_INTERPROCESS_CONTAINERS_ALLOCATION_TYPE_HPP

/* allocation_type.hpp
FlHap0F3o6SdoJBE0HIpnid6aCWBNbaUKuEKCbg3inEqUYchHtLusWsMjXJBviIK+8sdu+pxhTmipzJ3y6bUIfjFwOlYEhDR5gfjR4PoFEeRjahGR+aDRlzw9AAVGDtIvx5Un+skSRR3yfLC8RfhybzHmg1A7Lt+76HgqiTg2GsVq9ZcqrfFJmRqB13aZXJzjNZmon5Y0k9fTuXgL0/vCYJVKHlp+5VnCY45RJWlEn/jG/dbQJ835b4GJKi+vB60JRXnn+4wIUuPfmLAOVJ7LTEtl8pfmMdTfkaV2p09Oft0VEvMz/lwUEta9KHZggQxBs0BAaMae/Mjj1iPWNmUgNIkt3/JieQCxjWa0awKzCGPrafV4Cb0+XmlMakFxoltw8ehtzG3CrOyk3Ns9HFNj69+P2oewe1vX/BDfxnL6mIGhuUWlVrWhErIT41mQTgCvPPzEqRaIH0jt2/EVcBS3PkRshMqYJwKCHesQZDDornGc/Dzq9UP9s1HnbKjPV5wc0SK7T08teS4BIj5LBKYZYRxCC4Cf1rZuKXyoyrOY763RWVJqICkjPO5ZyGzkIKS7Ge6wl5OSEQttp/06D0zgjcQS6xmWvuY/oj+OO8o79g4+nFe2zTFSacY3VEoeOopEcGD8D5CcI4XsK2lTWWmHBSxnolciOSNUVKMKxK+yjodKdmyHX39UGjQB9+xXrPgKuxp7bE8zVDLejJ0
*/