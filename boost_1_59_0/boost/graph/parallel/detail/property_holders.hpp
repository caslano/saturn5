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
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
*/