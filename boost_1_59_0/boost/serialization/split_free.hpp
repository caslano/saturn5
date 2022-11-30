#ifndef BOOST_SERIALIZATION_SPLIT_FREE_HPP
#define BOOST_SERIALIZATION_SPLIT_FREE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// split_free.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/serialization/serialization.hpp>

namespace boost {
namespace archive {
    namespace detail {
        template<class Archive> class interface_oarchive;
        template<class Archive> class interface_iarchive;
    } // namespace detail
} // namespace archive

namespace serialization {

//namespace detail {
template<class Archive, class T>
struct free_saver {
    static void invoke(
        Archive & ar,
        const  T & t,
        const unsigned int file_version
    ){
        // use function overload (version_type) to workaround
        // two-phase lookup issue
        const version_type v(file_version);
        save(ar, t, v);
    }
};
template<class Archive, class T>
struct free_loader {
    static void invoke(
        Archive & ar,
        T & t,
        const unsigned int file_version
    ){
        // use function overload (version_type) to workaround
        // two-phase lookup issue
        const version_type v(file_version);
        load(ar, t, v);
    }
};
//} // namespace detail

template<class Archive, class T>
inline void split_free(
    Archive & ar,
    T & t,
    const unsigned int file_version
){
    typedef typename mpl::eval_if<
        typename Archive::is_saving,
        mpl::identity</* detail:: */ free_saver<Archive, T> >,
        mpl::identity</* detail:: */ free_loader<Archive, T> >
    >::type typex;
    typex::invoke(ar, t, file_version);
}

} // namespace serialization
} // namespace boost

#define BOOST_SERIALIZATION_SPLIT_FREE(T)       \
namespace boost { namespace serialization {     \
template<class Archive>                         \
inline void serialize(                          \
        Archive & ar,                               \
        T & t,                                      \
        const unsigned int file_version             \
){                                              \
        split_free(ar, t, file_version);            \
}                                               \
}}
/**/

#endif // BOOST_SERIALIZATION_SPLIT_FREE_HPP

/* split_free.hpp
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
*/