//  (C) Copyright Jeremy Siek 2006
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROPERTY_SERIALIZE_HPP
#define BOOST_PROPERTY_SERIALIZE_HPP

#include <boost/pending/property.hpp>
#include <boost/serialization/is_bitwise_serializable.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/nvp.hpp>

namespace boost
{
template < class Archive >
inline void serialize(Archive&, no_property&, const unsigned int)
{
}

template < class Archive, class Tag, class T, class Base >
void serialize(
    Archive& ar, property< Tag, T, Base >& prop, const unsigned int /*version*/)
{
    ar& serialization::make_nvp("property_value", prop.m_value);
    ar& serialization::make_nvp("property_base", prop.m_base);
}

#ifdef BOOST_GRAPH_USE_MPI

// Setting the serialization properties of boost::property<> and
// boost::no_property to is_bitwise_serializable, object_serializable,
// track_never only when BOOST_GRAPH_USE_MPI is defined is dubious.
//
// This changes the serialization format of these classes, and hence
// of boost::adjacency_list, depending on whether BOOST_GRAPH_USE_MPI
// is defined.
//
// These serialization properties should probably be set in either case.
//
// Unfortunately, doing that now will change the serialization format
// of boost::adjacency_list in the non-MPI case, and could potentially
// break software that reads files serialized with an older release.

namespace mpi
{

    // forward declaration, to avoid including mpi
    template < typename T > struct is_mpi_datatype;

    template < typename Tag, typename T, typename Base >
    struct is_mpi_datatype< property< Tag, T, Base > >
    : mpl::and_< is_mpi_datatype< T >, is_mpi_datatype< Base > >
    {
    };
}

namespace serialization
{
    template < typename Tag, typename T, typename Base >
    struct is_bitwise_serializable< property< Tag, T, Base > >
    : mpl::and_< is_bitwise_serializable< T >, is_bitwise_serializable< Base > >
    {
    };

    template < typename Tag, typename T, typename Base >
    struct implementation_level< property< Tag, T, Base > >
    : mpl::int_< object_serializable >
    {
    };

    template < typename Tag, typename T, typename Base >
    struct tracking_level< property< Tag, T, Base > > : mpl::int_< track_never >
    {
    };

}
#endif // BOOST_GRAPH_USE_MPI

} // end namespace boost

#ifdef BOOST_GRAPH_USE_MPI
namespace boost
{
namespace mpi
{
    template <> struct is_mpi_datatype< boost::no_property > : mpl::true_
    {
    };

}
} // end namespace boost::mpi

BOOST_IS_BITWISE_SERIALIZABLE(boost::no_property)
BOOST_CLASS_IMPLEMENTATION(boost::no_property, object_serializable)
BOOST_CLASS_TRACKING(boost::no_property, track_never)
#endif // BOOST_GRAPH_USE_MPI

#endif // BOOST_PROPERTY_SERIALIZE_HPP

/* property_serialize.hpp
XdYjiPvJhEaR2eKuTJQVjYZJRY7OzU5CG1ayMMTeoPNEl1JMaLacd4AWDlON9DOvFPTDBxtDfoQ4rLhGRWi9ehMznG9yWkzLKf/8CMeMsyw/FuvxmXyoi0DBDlZg2gUR1AXBjahGOkkp3SbK7v3YyAgYMx5nOhCeQlXTjeg6jv22TnQUhHPg3ErZbI12tXmgekyXZLs66qOfPb6u+IP504mozf7fLAJRRDC116AV2nuzplCMThSHEmrUb9Nh0BH3Ctt1AxLIcM9FNm6DcqxL5HVUkl87EwA0yThRYK7lXcMJaeQsDCQGu9AnHB38ameilyBDNTGaqrs0fT4P/VviO3pbGA9Kz7K8ATMKdn8hwgZDccsO4b0jT75tP2YHRrhdO2e2Czb/iSw+pzEcCbPbLJSwW3EPDmi7117TN9yb3YLvWH/+CxBBMgq0lJu6UUWnyYqXkf/4m38sW+ttxLH7A1PoWaM/NHcL+3yw6+iQU5oGmdXLrShLbt252bDnvLO97QfgdRuOHSrVL9FwYWfXC1mFT4IIqMjdxef3e5d8llsYclckVYu00QBFCw==
*/