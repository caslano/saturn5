#ifndef BOOST_ARCHIVE_DETAIL_INTERFACE_IARCHIVE_HPP
#define BOOST_ARCHIVE_DETAIL_INTERFACE_IARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// interface_iarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.
#include <cstddef> // NULL
#include <boost/cstdint.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/iserializer.hpp>
#include <boost/archive/detail/helper_collection.hpp>
#include <boost/serialization/singleton.hpp>
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {
namespace archive {
namespace detail {

class basic_pointer_iserializer;

template<class Archive>
class interface_iarchive
{
protected:
    interface_iarchive(){};
public:
    /////////////////////////////////////////////////////////
    // archive public interface
    typedef mpl::bool_<true> is_loading;
    typedef mpl::bool_<false> is_saving;

    // return a pointer to the most derived class
    Archive * This(){
        return static_cast<Archive *>(this);
    }

    template<class T>
    const basic_pointer_iserializer *
    register_type(T * = NULL){
        const basic_pointer_iserializer & bpis =
            boost::serialization::singleton<
                pointer_iserializer<Archive, T>
            >::get_const_instance();
        this->This()->register_basic_serializer(bpis.get_basic_serializer());
        return & bpis;
    }
    template<class Helper>
    Helper &
    get_helper(void * const id = 0){
        helper_collection & hc = this->This()->get_helper_collection();
        return hc.template find_helper<Helper>(id);
    }

    template<class T>
    Archive & operator>>(T & t){
        this->This()->load_override(t);
        return * this->This();
    }

    // the & operator
    template<class T>
    Archive & operator&(T & t){
        return *(this->This()) >> t;
    }
};

} // namespace detail
} // namespace archive
} // namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_DETAIL_INTERFACE_IARCHIVE_HPP

/* interface_iarchive.hpp
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
*/