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
ShqR4xYfzVa44KfZMZMyO2byB8put8sFkZXn9DFOt0SHNr2idxeZ5jZfSwX1M743Ie8aecwHBumXfT1eRRn0KmJTPsBvhxA4E4p1yd4fLCXytCPW4ku36PNViPvyhbj7F8nIl+CScEg6E+sLy2pxEMVBeg1bw8nrZwebfynLCpHEE0r50NcbHvK1pAXvG6yw+3Gj351dFzMDzaqP320rld73Hz3+a848hSko8u7HxYWAHxyextHoLr5GszwtEE/MlFupjvDP1fmZQgCsiXWXEMAgSsUA/vxnEgTkgL5Mp6Xs3K0Fgk/b7eUkbhW3+wwBffYNX1+aK9FSfXF6XBfHR8eP6mL/9TP43X59elwzO72qMCO4q5/xbjr3fW0g/QK2etRCZY2+vI8UTx6scF4Neqtv8YXfm59dNvi/4rP7KhB8kTYaTRsIIDKGFOfuXzCJLGCp+QQjEHvHQIXv96nZYOL2fWXU94EVkuDwiA3u7hAblPvDBv/t7rD5rjAl45X5szLb6PH+4cvjo8OX+liNJaZZtYoH5GTrf6g/7M/sBxv8QW6wvPLq8IEtZrMZOBxdbhp4xqeDETu9KMY8nlxLHT9aMhuIfU9UxlJr+f7zSZbkGl4sEInGDMLUYwrI3LZlHsaK+pWz1Kp6s6pl
*/