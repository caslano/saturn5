#ifndef BOOST_SERIALIZATION_SPLIT_MEMBER_HPP
#define BOOST_SERIALIZATION_SPLIT_MEMBER_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// split_member.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

#include <boost/serialization/access.hpp>

namespace boost {
namespace archive {
    namespace detail {
        template<class Archive> class interface_oarchive;
        template<class Archive> class interface_iarchive;
    } // namespace detail
} // namespace archive

namespace serialization {
namespace detail {

    template<class Archive, class T>
    struct member_saver {
        static void invoke(
            Archive & ar,
            const T & t,
            const unsigned int file_version
        ){
            access::member_save(ar, t, file_version);
        }
    };

    template<class Archive, class T>
    struct member_loader {
        static void invoke(
            Archive & ar,
            T & t,
            const unsigned int file_version
        ){
            access::member_load(ar, t, file_version);
        }
    };

} // detail

template<class Archive, class T>
inline void split_member(
    Archive & ar, T & t, const unsigned int file_version
){
    typedef typename mpl::eval_if<
        typename Archive::is_saving,
        mpl::identity<detail::member_saver<Archive, T> >,
        mpl::identity<detail::member_loader<Archive, T> >
    >::type typex;
    typex::invoke(ar, t, file_version);
}

} // namespace serialization
} // namespace boost

// split member function serialize funcition into save/load
#define BOOST_SERIALIZATION_SPLIT_MEMBER()                       \
template<class Archive>                                          \
void serialize(                                                  \
    Archive &ar,                                                 \
    const unsigned int file_version                              \
){                                                               \
    boost::serialization::split_member(ar, *this, file_version); \
}                                                                \
/**/

#endif // BOOST_SERIALIZATION_SPLIT_MEMBER_HPP

/* split_member.hpp
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
*/