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
maLXb2Y2GTj7oRKhj2vd/5OXAqa1Mf6VU/770tEThHPEA784LDw2QES9gENOGg0tz5AC/YGpkni4vBE5S4HOw+fdD06/6qfve6yl8FIkWLOlCviEqoROcJ8hht/oyIUmXiCqvPqs0XhcFl7fu8VVK38e+Atux9rwaXaA0VuvzML2u7uLFIqhls3G819PdRbaSaIqDrCbhu33vhEoZEohJqkISGaI4+SAfv56h5STofDUxOMr0+AcHFQcEfdQS53GS+kG97yR0cwfSf2A4TKct3Bz9ocRNmIcHGXTdT4g0vc3dgP+j2Xcb0h9lE4XZCdVTP2KqNNhiT5Jsly5QAsn/9zP7DBpbbQcG+mehsMi4KKdafPq8EQMW3mkxR0G4p3wslbcxGgNcsFPTTHctQox1ERG1Jza5vkqL3YaDq5/iXv8+7/eLmhnT+DmlkC8e69MQ3KY4aSixDPH0+uJVjtUI7zcRXMNkUapxzjMnI4Kb/X1uWVe9Me2AB3FTslYgjJGbXgRO0Fs8Ps1APJlm6yDExQTTbjyBzKkzls1vIrNvuG/3KklQdTyaxh3vg==
*/