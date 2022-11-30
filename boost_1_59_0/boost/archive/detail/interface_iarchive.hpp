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
    interface_iarchive() {}
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