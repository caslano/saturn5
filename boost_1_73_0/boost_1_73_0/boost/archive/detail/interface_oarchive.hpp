#ifndef BOOST_ARCHIVE_DETAIL_INTERFACE_OARCHIVE_HPP
#define BOOST_ARCHIVE_DETAIL_INTERFACE_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// interface_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.
#include <cstddef> // NULL
#include <boost/cstdint.hpp>
#include <boost/mpl/bool.hpp>

#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/oserializer.hpp>
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

#include <boost/serialization/singleton.hpp>

namespace boost {
namespace archive {
namespace detail {

class basic_pointer_oserializer;

template<class Archive>
class interface_oarchive
{
protected:
    interface_oarchive(){};
public:
    /////////////////////////////////////////////////////////
    // archive public interface
    typedef mpl::bool_<false> is_loading;
    typedef mpl::bool_<true> is_saving;

    // return a pointer to the most derived class
    Archive * This(){
        return static_cast<Archive *>(this);
    }

    template<class T>
    const basic_pointer_oserializer *
    register_type(const T * = NULL){
        const basic_pointer_oserializer & bpos =
            boost::serialization::singleton<
                pointer_oserializer<Archive, T>
            >::get_const_instance();
        this->This()->register_basic_serializer(bpos.get_basic_serializer());
        return & bpos;
    }

    template<class Helper>
    Helper &
    get_helper(void * const id = 0){
        helper_collection & hc = this->This()->get_helper_collection();
        return hc.template find_helper<Helper>(id);
    }

    template<class T>
    Archive & operator<<(const T & t){
        this->This()->save_override(t);
        return * this->This();
    }

    // the & operator
    template<class T>
    Archive & operator&(const T & t){
        return * this ->This() << t;
    }
};

} // namespace detail
} // namespace archive
} // namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_DETAIL_INTERFACE_IARCHIVE_HPP

/* interface_oarchive.hpp
4b8JqxeodsI9haQv70X7WY0B79AXZO/1tuxiRd7WzOubjfzVbRrBK9nWol7l2GDZXQzXkqGuwKxlivWcLE62/Vawr8h7UTyIXWeBqCbpV8iwRBt9MOAD8XP8kshg4SDAnk9VJYRHWpDHGnx31nadyCRhZ23zQ2bg4cr5769/waWnl6dPvvlmZyOgqAkt2pOTh+nbAjfbhas3z+N2/UeW/UQSJIFlY7D9tqgakqxOTATP4UpYg8xNFL1c9VLe64fNfC4MerbclMLbhBydZQ5Fdy0ghMJxR24rwJsLGz24jl89MLIWYvok0MGuDEZru8QNcs6Mnp1oFU4/v3qXi8qKIYFdTyaP/OrTzdBiCwS5vv0+vcgPPpyEay+fBEIiwgtyLQOovp188w2vdqIPBjr4ZvItrt3gYgBqflg094HFczH9Zr0WNt7nU3305Grd56L3N/n7uvmQv283w4cpFbd1/2hdzvPDm/6I+xMEQ7DCTCxs2WlbxqBqOUB2CHOFelnP53KlgZASsC5EDREsFDXopitWiocQUhhNWOw9cVveLqmZ4I5/Um5OcrFFFsVadZ+5iL4cyAFWScooK+GLS6oS2J+Hk/yZfX0I+8mF9cQm1VzBjDrVhiAxcrEpOK1jCIOeihqU+VK5elnNIbCI
*/