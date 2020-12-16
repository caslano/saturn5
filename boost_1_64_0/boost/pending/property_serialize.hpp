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
8cny5hXelF9SGs57VO9OmveVPKVH+3HSPDeXW1be0X6cNN/K3BX5gbxwWd0nzYMiBr3AqLIC74nMV1iyLBdNCQRWXRzu56g8V12ZuSw3Lw+nsqJ4jT5F1aav1v3e4/NTc1KoeYGScJn9J+Y5SZlhW+Av4/j8Sq84XOekyOthiVDnnLCvichTQrtOWil/YTn2f3TUPe9717J3LsnCa+Tnrll2Y1EutnpUjh87MR9aWlhSECg6mqfiJHnW5AfbWBTuZ+WJeYKO/pjNnHg92I/Zy+jEjYXl5LOvt580n60+NlZpp8gX9DNHdemUeZhcSsuZt9Txjx+fb/mKY/6u/RMnXFuWu+amWwKj5oKcyhPz3JJbVJa/rPS24vzAMb/3xFjzBZsS8i+K8miemt6T5gn60MDR+s6NGp0nqNZOCO9cEODv4rAsrxl7inzLy0pKV61Yll9eGhil2zUn5HcSiMgfbms/PjUiv9N1oOzoeH7uuLYuzy0quiF3+c3If00wzlgR9knFEfkK8slUvKbwllx89c35t432N4Hq4/KG1HrVK943qCK3HZ0Ph4/LR7xxY+FNo8qJiyinNOhD8lfm3lCUnxcsJ6wfaRH5aPoxO/vCcdfyclfmn9zOak7IZ1WBoqPtOUmeFUEVCmrtKNtOOjHfSW0k87h8VkfzuXRTuKz2GaPHkCLKSgrCo1gyOka8+7iygjpre/j70nHXbnrFPeWvKS28sXA5w0c++3eyfKVFq25ahnatCdqA/TsxnzPwsbFLO0ke1QVtOWYDOSfmo3vLy4gBbkOfEV5pblCnw+VWnpD/la7YwsCyo3YamS882ZYE1hzV6XMj8xyz02B4xkDkmpfveRyHiLxWv/wG8ob71HJi3Xn5N+aWFZUippKSW/PIHuzTZeEx/jfyLyvD1BXG0fnwxPvCEis+2scT2o2vunHVUUMnyw1H/cWJ5YWttihc3uCJeVaXFfLfcJRPecqBB7aReY8N7aj688Nlx71K/qL8W/JxSDcf1a+IvE4bhgzH1jWVJ/a/tHBF/qoy1jXhejOPL8uApvDGUa2kXvXgVHkZsuLSgmNx7ynzrViVh6Ie1ZXjfXpBbslJ54D8cP6a48sNxvgWzL+xZt1C/hvC5R+fnyk/OC9a1vGyWZO/YtUt+WHnMsqWW47PF8wQ7BAEFf9YvvZT5KPSV/KF5d198nw2gKyj7L3/JHlLjtW9PJxv8BT5rHt5uO7AuSfJF1H3OeH+1B0nu7DXPRa/RFyP9JdH7eCeiHwn83GjdDbO/K/81qPE38z528YNAf+fRy+Gzk99OJRuKg6lWy8w32BUKP18KN375tD1Q4mhdG5LKF9Uj7+tfNeYUL64UDpxcuj8xvaoULn5ofOH20PnV0SFzk+tDKVl5/pb6cdC6aL9ofPzngql28f425bxoXT160P92NMZFapnXOj8rlTv7wulz4+ErhceDqXPXx5Kl270t3/2d9aHQ+nmYo9f8DdDV4aOZ3/V3yzant2fC6UPFimf8cr5Q6H84/tD6a6fhNIVt4auT/9IKH1+fuj89XeH7l98X+h4z/ctt9HfBM213j2h84d3B0L9GR4Tum9M6PxtpaHz+Z8IHV+ZFEqv+24o3zrrvXPa2FB7fuo42d+pf/LYfs5ts/0xofSOH4XSR23v5nuU9yWh87ePHRuqb0Xo/J45oTT3nFB61y715z3+Vsz795Z4fFqo3BXfUv4fCx3vGwzlW7RGPTvT34jmKseGUPrAr+yH+nbXM6F04sWB0HiZb9fTtjffcq9QvurFrK+aPqR8C0LpnerVRdGh61Efc/zabc9rQucfaLCdyaHj3Imh451jlUda6Pyu/lD6Ypl6MV4=
*/