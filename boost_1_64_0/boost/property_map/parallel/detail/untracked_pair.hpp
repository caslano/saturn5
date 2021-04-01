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
3RVc3NTev3sase5eNqPvHHGxPeYQNWDtplnq9AM7dDvt8eQWe7pLGKH+OV/gPrftgWMS4sOM9bucy8XvtaO6lSxmMKhaOOwIYV416LrBhlN9pO72+WIrhqsj75D+8x8Ln9cQJjry59bZC7YHlahl0PAEHN6Ou7U0wbtGevBHt8abNxeUhn1LDeCO3hKidzwSRnVbsiyUTzL57cLTGm+Zb8JSZh6xa+OSwao6uN0jcK2GZHKOto0xpigqB8A9/ak8xjGUCHZzcZgQujie4OLt8ITGZl6RlO15W40D27acuH1lpwBX+CuAU7crItW0kUuI0By1Pigj2h3zmU9B714tu/bqgQDSdmJ4FE4KzGnMBcI60tfxaozwA4L2Q6XqtLknJkdRR3UuvZVVFGeWLZ8gzzpgwmftfwgvsiRt5OKhIqsy8nLmsbixt0ocotTKYyA73ts0M/MLa8ro4QvBpBwRTojxYkv/PGDmsh2awrXk4eA99DduT9MhGMDfZxciX67701chyPdhRxYKQEox5oI4c/tktpQ5S7xGzL+P8KaBfJG92A30CpNhjR0ZhQ==
*/