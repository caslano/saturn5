// Copyright (C) 2007 Douglas Gregor and Matthias Troyer
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//
// This file contains helper data structures for use in transmitting
// properties. The basic idea is to optimize away any storage for the
// properties when no properties are specified.
#ifndef BOOST_PARALLEL_DETAIL_PROPERTY_HOLDERS_HPP
#define BOOST_PARALLEL_DETAIL_PROPERTY_HOLDERS_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/mpi/datatype.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/mpl/and.hpp>
#include <boost/graph/parallel/detail/untracked_pair.hpp>

namespace boost { namespace detail { namespace parallel {

/**
 * This structure contains an instance of @c Property, unless @c
 * Property is a placeholder for "no property". Always access the
 * property through @c get_property. Typically used as a base class.
 */
template<typename Property>
struct maybe_store_property
{
  maybe_store_property() {}
  maybe_store_property(const Property& p) : p(p) {}

  Property&       get_property()       { return p; }
  const Property& get_property() const { return p; }

private:
  Property p;

  friend class boost::serialization::access;

  template<typename Archiver>
  void serialize(Archiver& ar, const unsigned int /*version*/)
  {
    ar & p;
  }
};

template<>
struct maybe_store_property<no_property>
{
  maybe_store_property() {}
  maybe_store_property(no_property) {}

  no_property get_property() const { return no_property(); }

private:
  friend class boost::serialization::access;

  template<typename Archiver>
  void serialize(Archiver&, const unsigned int /*version*/) { }
};

/**
 * This structure is a simple pair that also contains a property.
 */
template<typename T, typename U, typename Property>
class pair_with_property
  : public boost::parallel::detail::untracked_pair<T, U>
  , public maybe_store_property<Property>
{
public:
  typedef boost::parallel::detail::untracked_pair<T, U>           pair_base;
  typedef maybe_store_property<Property> property_base;

  pair_with_property() { }

  pair_with_property(const T& t, const U& u, const Property& property)
    : pair_base(t, u), property_base(property) { }

private:
  friend class boost::serialization::access;

  template<typename Archiver>
  void serialize(Archiver& ar, const unsigned int /*version*/) 
  { 
    ar & boost::serialization::base_object<pair_base>(*this)
       & boost::serialization::base_object<property_base>(*this);
  }
};

template<typename T, typename U, typename Property>
inline pair_with_property<T, U, Property>
make_pair_with_property(const T& t, const U& u, const Property& property)
{
  return pair_with_property<T, U, Property>(t, u, property);
}

} } } // end namespace boost::parallel::detail

namespace boost { namespace mpi {

template<> 
struct is_mpi_datatype<boost::detail::parallel::maybe_store_property<no_property> > : mpl::true_ { };

template<typename Property>
struct is_mpi_datatype<boost::detail::parallel::maybe_store_property<Property> >
  : is_mpi_datatype<Property> { };

template<typename T, typename U, typename Property>
struct is_mpi_datatype<boost::detail::parallel::pair_with_property<T, U, Property> >
  : boost::mpl::and_<is_mpi_datatype<boost::parallel::detail::untracked_pair<T, U> >,
                     is_mpi_datatype<Property> > { };

} } // end namespace boost::mpi

BOOST_IS_BITWISE_SERIALIZABLE(boost::detail::parallel::maybe_store_property<no_property>)

namespace boost { namespace serialization {

template<typename Property>
struct is_bitwise_serializable<boost::detail::parallel::maybe_store_property<Property> >
  : is_bitwise_serializable<Property> { };

template<typename Property>
struct implementation_level<boost::detail::parallel::maybe_store_property<Property> >
 : mpl::int_<object_serializable> {} ;

template<typename Property>
struct tracking_level<boost::detail::parallel::maybe_store_property<Property> >
 : mpl::int_<track_never> {} ;

template<typename T, typename U, typename Property>
struct is_bitwise_serializable<
        boost::detail::parallel::pair_with_property<T, U, Property> >
  : boost::mpl::and_<is_bitwise_serializable<boost::parallel::detail::untracked_pair<T, U> >,
                     is_bitwise_serializable<Property> > { };

template<typename T, typename U, typename Property>
struct implementation_level<
        boost::detail::parallel::pair_with_property<T, U, Property> >
 : mpl::int_<object_serializable> {} ;

template<typename T, typename U, typename Property>
struct tracking_level<
        boost::detail::parallel::pair_with_property<T, U, Property> >
 : mpl::int_<track_never> {} ;

} } // end namespace boost::serialization

#endif // BOOST_PARALLEL_DETAIL_PROPERTY_HOLDERS_HPP

/* property_holders.hpp
G36FYXgKy+BpLIdf4xUsCFfvl1bvtea7aLExPeqN2d9QrhF+i03xZ0zEP7Ar+lP5j2QYO07BAHweI1Cez8dNWBJfwdL4FkbhexiNH2JZ/BjL4WdYHk9iLH6HFfEHvAcvYWW8ilXxJlbDvzAe/Zn+GhiENTEca2FprIOxeB9WxrpYC+thXWyAbbAhdsTG2BubYDI2w1RsjunYEh/GVjgJE3EJBuNmDME92A4PYHv8CDviMeyEX+AD+C12wfPYDX/C7ngZk/AW9kSTfbg3BmIfjMB+eB8mYwMcgM1xICbiYOyID2FXTMF+OBQH4nAchqk4CkdiJo7C8ZiOj+JonIkZuBjH4jLMwk2Yja/gOHwPx+MBzMGjOAW/wKl4GqfhBXwUL+F0vIq5+BfOQH9/+nLDIJyFkfgElsXZGItz8F6ci/fhPGyO87ElLsD2+Ax2xIXYDRdhD1yCA/FZHIxLcSQuw7H4PGbhC5iDK/AxXIkzcBU+hatxIa7BxfgSrsB1+BKux/X4Mr6NdjyCYXgKS+BVnIh/4lYMsHMfDIbgdozHV7El7sD+uBs34R58C9/B9/BdPIDv4Ye4D0/ifvwaC/AsfoTn8V94ET/Gm/gJ+lPBHMFwPIoV8Ti2wM/xfjyB3fALfBC/xLH4FY7DUzgZz+JsPIcr8Tyuxe9xE36Nu/Ab/Bi/xW/wByxFHfgTJuBFbIg/Yxv8BdvhJeyMVzEdr+E4vIkz8HecjbdwEd7GtWjYWF6435/vxQN4DD/AL/FD/A8W4K/4Ef6F/8KgQJYXlsBDWBUPYx38BBvhEWyFR7Ejfoo98Bgm42eYiscxAz/HHDyBs/ALnI0nMR8Dmd7jGIInMRTPYhjewOIYHMT2hBUwEttiSeyNpXAalsYnsDxuwFg8iPfgt1gJz2NV/A2rYUAw9SyWxTqYiPdhe0zAB7AuDsP6mIMN8FFsiDOxES7HprgDm+NubIEF2BK/wVZ4GRPxKt6P17EN/oVtkQcBjA5YBjtheeyMtfABrI9dsCF2w6bYHZtjD0zEntgXe+MA7IOjsS8+jP1wEvbHR3AwTsch+IxKL1XpHZiCu3EofozD8RSOxX9jJhqh1JsYhNlYFidjQ8zBZvgIdsNp2A9zMRtn4OM4E5fjHHwVn8YDuBALcBH+govxN1yC1/FZ/B2XYlgY9RmWwpVYVaUTMBc7Ybo/xw1cT7oXbsDh+DI+iZtwOW7FDfgqbsLXcDfuwE9wF57E1/E7fAOv4m600259HMvjbKyNT2E7nId98UWciGtwNi7DlbgcX8EF+AE+gyfwTfwK38Jv8W28gnvwKr6DxUvQFsNauB/r4gHsiB/jADyEmfgJzsFP8Wk8hpvxBL6OX2ABnsRT+A2exzNoc/RJjqXwB2yN/8G++BOOxIs4BX/Gp/ASPotXcD1ex214A/PxDzyEf2JgBNdlMQxvY320+Rm5Q9GOIzEAp2EgLsQgXI6huA4jcBNG4rtYEvdjKSzAqvg5VsMrGI9/Yg00HNfB0Y5lMR5jsDGWwz5YHkdjHM5R5Z/DWrgJ6+C7mID7sS5+gvXxFDbAa9gQ/8BGeBtbYUBJrm9jbWyDjbAtdsb2+BA2wQxsio9hc1yCnXALdsZ38QH8DLvil9gNv8fu+AcmYYlS/BaCVbE3tsIHsScm4yjsj9NwED6Fg3ElPoSvYQruw2GYW5r2Fs7BdHwKx+BqzMAdmIkFOA4P43g8ghPwHObgjzjVUT6K/Rffxpn4Ds7Cz/EJ/AmfRKMM9QaG4TP4OS7GL/FZPIVL8TdchvZo9jeMwhewBq7AZrgaU3At1i1LPYFNcSM2x83YE7fgKNyG03A1zsPduArfxE34Fh7Ad/ArfA8=
*/