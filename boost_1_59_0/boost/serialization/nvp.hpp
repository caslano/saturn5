#ifndef BOOST_SERIALIZATION_NVP_HPP
#define BOOST_SERIALIZATION_NVP_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// nvp.hpp: interface for serialization system.

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/core/nvp.hpp>
#include <boost/preprocessor/stringize.hpp>

#define BOOST_SERIALIZATION_NVP(name)                       \
    boost::serialization::make_nvp(BOOST_PP_STRINGIZE(name), name)
/**/

#define BOOST_SERIALIZATION_BASE_OBJECT_NVP(name)           \
    boost::serialization::make_nvp(                         \
        BOOST_PP_STRINGIZE(name),                           \
        boost::serialization::base_object<name >(*this)     \
    )
/**/

#include <boost/serialization/level.hpp>
#include <boost/serialization/tracking.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/wrapper.hpp>
#include <boost/serialization/base_object.hpp>

namespace boost {
namespace serialization {

template<class Archive, class T>
void save(
    Archive & ar,
    const nvp<T> & t,
    const unsigned int /* file_version */
){
    ar << t.const_value();
}
template<class Archive, class T>
void load(
    Archive & ar,
    nvp<T> & t ,
    const unsigned int /* file_version */
){
    ar >> t.value();
}

template<class Archive, class T>
inline void serialize(
    Archive & ar,
    nvp<T> & t,
    const unsigned int file_version
){
    split_free(ar, t, file_version);
}

template <class T>
struct implementation_level<nvp< T > >
{
    typedef mpl::integral_c_tag tag;
    typedef mpl::int_<object_serializable> type;
    BOOST_STATIC_CONSTANT(int, value = implementation_level::type::value);
};
template <class T>
struct implementation_level<const nvp< T > >
{
    typedef mpl::integral_c_tag tag;
    typedef mpl::int_<object_serializable> type;
    BOOST_STATIC_CONSTANT(int, value = implementation_level::type::value);
};

// nvp objects are generally created on the stack and are never tracked
template<class T>
struct tracking_level<nvp< T > >
{
    typedef mpl::integral_c_tag tag;
    typedef mpl::int_<track_never> type;
    BOOST_STATIC_CONSTANT(int, value = tracking_level::type::value);
};
template<class T>
struct tracking_level<const nvp< T > >
{
    typedef mpl::integral_c_tag tag;
    typedef mpl::int_<track_never> type;
    BOOST_STATIC_CONSTANT(int, value = tracking_level::type::value);
};

// these traits aren't used by nvp so they don't need to be defined
#if 0
template<class T>
struct version<const nvp< T > > {
    typedef mpl::integral_c_tag tag;
    typedef mpl::int_<0> type;
    BOOST_STATIC_CONSTANT(int, value = 0);
};
struct version<const nvp< T > > {
    typedef mpl::integral_c_tag tag;
    typedef mpl::int_<0> type;
    BOOST_STATIC_CONSTANT(int, value = 0);
};

template<class T>
struct extended_type_info_impl<const nvp< T > > {
    typedef extended_type_info_impl< T > type;
};
#endif

template<class T>
struct is_wrapper<const nvp<T> > {
    typedef boost::mpl::true_ type;
};
template<class T>
struct is_wrapper<nvp<T> > {
    typedef boost::mpl::true_ type;
};


} // seralization
} // boost


#endif // BOOST_SERIALIZATION_NVP_HPP

/* nvp.hpp
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
*/