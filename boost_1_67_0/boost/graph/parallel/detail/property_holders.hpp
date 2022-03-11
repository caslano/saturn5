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