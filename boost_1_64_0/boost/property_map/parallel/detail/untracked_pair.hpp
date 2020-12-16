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
5/HvU+BLrnxJvjUvyS+z+FlHeUczdhefdz1PPO9Ebx2sd7T3LVGnwH83d2GfT+AL++zX5eKVPHb5g+ycHkouw5PjcyJwfSlenucca2Ym/fPzpjdF47oD4lU/PGe+/K2lffjd+uJzD5vwePGlbJo8+2t511h42F/cXo8n5aufOI+cc7u6xdfs59/ytKIkXMPTc9WX8qOx8j/6NH3oAS71zE2qS/OnKnwA/q773j68Lf5Mhhv15Cnv4WG3yXflx8WvwiHxpw57yk6P+5T0I/52foJdfeR6O+g1lx3Sc/5kftoL734KPi+Qv42hf/OYPkrcbqlPlOH9D2REr38rDrcSd/5ivnhRdTq7nCf/6IU3xf3AO9jfOn5dAI++oye4W2DdI96AFxewy8p4HfKm78VBfD51vfxQPaqzcwKbT+LX7LH1Hvzq7/KiL/Cqa/ip9zVvzQ7w0wb2f0G234r9DM5Ot45hzu0diXfE622LH30KF9VxG1Sb39vwhV8vHwXn9FeydphfPf53hfMu+jTFLeDUMvbaVZx7n99n2edc64BP1Q/jW6fjMf9lZ0fit5+z4+3i6lo4Oky9Cd8vfjAak4fEy03i7lbzO8H6DrD7xfwkId+4Fq/sR/9x/3GcftPsZDTCpzn6ZqnacOt0/iu+p7rCkbHs4y08e5Q496a+eqF58IN2DfDLbfjxdPxtBn31k6d0os9P4j4dXGgKd/z/1JfgzxT8kJ+Ux32qz6KxcqH3n8ov+ogjmbE/6sv0g7f1U/wuHS6r16yI/s75Eb++id5miBN18Y+XzOdR78cT1x8j3uCJMzfBp478Pg8uON+xFq4UvsxejuCH4tTSjfKubHzb+5e/Iv5lwd/d+Jl5psSD/CLjtXjyPvevx46OlD9URmP2e/jJ+/LIUnH8OLz9RvHjaXnTkfKV6/jTRfhkBf44Fq71N8/h4voE89EvLZOH7lWXnHgb/r1RfiWedsVjVz8uXp4HH1rAoQ+cg7oTL1OXqpyCJ09TR9suz3se7zkuGrPqqgedDp/w393p/PQ5ftvWvuBDc5az20v8bf+a6uMXdJE3ii+5bfCo/urK+/nDaPH1V3jlfHheGj6WxY7Mb2/MH460Xy+IZ6PhtPP+pRfC1efY8Zn6kNXqMQ0yovfhM+NeSFOnUJfSD2uIj60fHI2d/81e1GMH89/di/RZ9ssn2UnzC9nNAby12OfG8LcT8C9+3aBzCu/Tf9ssH7NvpdaRW2Reh6Jx+VH6i0PEqdX4Wnzell10nyu/PgKf/0t8Htq69KPLXodbQ/np0/hY2yTccX7kCji+H46PNP/OzuXl4iP2ox68TDVhv43dZwx/70Nv49j1xXhdkGSQih9cpxNe/Ap9NmQHP4tjH0Zj8l754Ez6qNEvZT/DpvHvLeqa+ELPDOu7GX//q7wk33WWOqf2Mjx+1rzx9c3Z9Ho9PqzuuZ4+54hjxd/z6y38fhn7OY5dnQXPxLfkTvn4Hnh4vTy5SXxeVb/RdUp+g8viaedd4vcV+O2Z6mtXwPl34z4j/vMGe3oZf3zFfiXgwr/w1K72uZx+1elHNLDOGfwqPuePR69UL246Ge52Un/FF3LE1XpTnRtto7/xPByVDxWfKP+50r7rW5ReDcenwZ2v3Ic/TrwZnyiQfyTdt8L/z4GjE/GosfSET65fJp+oSagr4RvT+K0+dvfL8doR8mT5wLgYDx6Rp9+Ych4KD7H/FfQ+c6D1PgI/L01Enxcvyt83T3a/42p2/VBKv8a5BX6yW/+67Ab7B7eqfV+14jd1hp784UXrbq7u3BY/9bmC1uLjHn73E9z/St6YLs6MTUX/f3x83hEP/QAO1MF37rOfD9PTP/g=
*/