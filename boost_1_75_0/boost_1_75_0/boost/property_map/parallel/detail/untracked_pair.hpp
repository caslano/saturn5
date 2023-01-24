// Copyright (C) 2007 Matthias Troyer
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//
// This file contains helper data structures for use in transmitting
// properties. The basic idea is to optimize away any storage for the
// properties when no properties are specified.
#ifndef BOOST_PARALLEL_DETAIL_UNTRACKED_PAIR_HPP
#define BOOST_PARALLEL_DETAIL_UNTRACKED_PAIR_HPP

#include <boost/mpi/datatype.hpp>
#include <utility> // for std::pair
#include <boost/serialization/utility.hpp>

namespace boost { namespace parallel { namespace detail {

/**
 * This structure is like std::pair, with the only difference
 * that tracking in the serialization library is turned off.
 */
 
template<typename T, typename U>
struct untracked_pair : public std::pair<T,U>
{
  untracked_pair() {}

  untracked_pair(const T& t, const U& u)
  : std::pair<T,U>(t,u) {}

  template<class T1, class U1>
  untracked_pair(std::pair<T1,U1> const& p)
  : std::pair<T,U>(p) {}  
};

template<typename T, typename U>
inline untracked_pair<T, U>
make_untracked_pair(const T& t, const U& u)
{
  return untracked_pair<T,U>(t,u);
}

} } } // end namespace boost::parallel::detail

namespace boost { namespace mpi {

template<typename T, typename U>
struct is_mpi_datatype<boost::parallel::detail::untracked_pair<T, U> >
  : is_mpi_datatype<std::pair<T,U> > {};

} } // end namespace boost::mpi

namespace boost { namespace serialization {

// pair
template<class Archive, class F, class S>
inline void serialize(
    Archive & ar,
    boost::parallel::detail::untracked_pair<F, S> & p,
    const unsigned int /* file_version */
){
    ar & boost::serialization::make_nvp("first", p.first);
    ar & boost::serialization::make_nvp("second", p.second);
}

template<typename T, typename U>
struct is_bitwise_serializable<
        boost::parallel::detail::untracked_pair<T, U> >
  : is_bitwise_serializable<std::pair<T, U> > {};

template<typename T, typename U>
struct implementation_level<boost::parallel::detail::untracked_pair<T, U> >
 : mpl::int_<object_serializable> {} ;

template<typename T, typename U>
struct tracking_level<boost::parallel::detail::untracked_pair<T, U> >
 : mpl::int_<track_never> {} ;

} } // end namespace boost::serialization

#endif // BOOST_PARALLEL_DETAIL_UNTRACKED_PAIR_HPP

/* untracked_pair.hpp
c2TUqRghB+eL2ddCJ7bCj2lFS/FonpB8D210mVWLnZkoucLlBgvxQ/EEuCtbLJk/id6ILKA8OeclJhY1cFSb7X1+Yg1tramcHYibR3vtiTgLjJb9bH+LNkwe9peg7Huxjt3oo9yIkz99i+2gnIxjwQnaDspxcqvX1N2SD8xjqQR5h5JKljdDag3t1Iy7T0O5IparFdOXFXP2T7WY7uzGQeXGaLmtUm4CO3VOLXe0vOpVdb/mYfPUGvTTanC/rlxRLffwn2q5RxdSMc9o5f7AbgzXyl27sJxyO2vlnp2rlntsrlru3rmGco17jeOEgTRaWgJFjfwT+/6vi15RdkhlsotV4NhltYoJ7MbOy2oV715YDgLL+fdr9bh/ropAMqZw/7/BimOzO0UqwOlcdNTmWNwoCHc0y96aNlz0NX/mN5RIt3TM6OUyh8ca1dEwtTRVuoabuQ5ys10M45TenQRn/JlUz4hl8tM56C0yh2G7fPUR5hmy6URgrddU45u50rERRT77l2fJkucuwmceNjfNrUxNo5n3u+QRQ5ix7xKiEJfSnX78kqDMMv33Df2OVb8VY7lsmhkeigM/bUtOR0a4bvG/GnDrJi1NlxXjkCLdDDTV9DF6XobP+aSms9X8lhruq6ZNauomEwiiJwy8HOBlG05r+hSex18peV3gFEVze8TEYHDvta2PwPMH89BG2/zoGliF0mi2+dHB/Ujr
*/