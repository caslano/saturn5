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
Gy8l09sSs3zYYuJPurG0dLL5sXt77TRWjoctvHjUfu5isfwrPCfAHIUNe9xSqTA3U7heUEisBfbUzcG3XZDC1obCnV7m2xG9YotI/Ig6fZLUZML43GVtveaKWndvfUsXC0TCYE3XDztkeOgficoH3razjuy7W0/ok71E6TyzVfRTJES9l3L1sngfsGHvGArUNvjRYlZBocV6O0jq+cJV41OalK/Bh6HQlN8BbMOxNBO4sQLo8slob/XRFAT33QGtfuh+fq1GRkbqzc3mRkKg/j4KVNn4U7z+3juH84QjQ+ljZaCeQV2DWYlkoTbo+0i0cjWg79fz7fnQUJT9EPOB64G8mq61uLcprCwLC8JejY2NC3Nz6cNqlpasAXlKNBSb0KI/j+i3WMqom661n8NK7vXAd8fmATrgIn6eQs3CY60SVdIXX7mZhd0r+14UTERFTsn3Q81vaLO13mvprmuZOQtlXl5ezuDtU9YXcUtLOxz+Do3EVhTGlCW0QH9B94KvPN5/kleTm3N8auf3N4u9k9k955TUI42f+AkCzEo48hEHd4TlAGdZ8481DIzaXhKG5BSlCwUk6WPJhSwsoouiJS265XLpDEnJKiwKIXJHQMgUzRd6TL6Z1wce+66uvi+UI+TMVTQqpm1+1ompqqjUK3zWL43auVjpfRugFs3Kp037IsNnJxx6Zj7WsYrHwpJ8fy/PNu2mGc7Hd1v8
*/