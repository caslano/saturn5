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
pLlwwLuiK3vCtCBDiZMQcJdCjkKqfX1bLWXz8Pb1PRc81MI/7sBChPBkX5rqTiAzW8iTvVzPZJh2s5SPFTcj6N3VwyJXyOd9vaplFx2GNlQJAPWy6XmzWYk8mSRblchj27LkSjYW97/J/CAVc5A3p26kju8BQ0QG6XTO/vJXv9D1kzx/3eSPH51cy5birc06y1dCe8KT5OZLYUnANR+r6PvNStYlLKjK2y5fVn2fv3l9efGfioV10cwqw/pieCD40LQyriz2f23qrlqBbtLJJnO83tRL3TFgiU512QrXks8Pi7oricqyHa3IHd0cAP6uEGqQucsIHYRmk883zUwlj+4gxi2uffUC+l7JZlkIPjj0ZaaH7bJMLggUBJGGWrCDE8KihLywHuK1YAOvCyMibuPbg/zv6Icse2YYPBM5mp0k/6iXvZabELX8983kr5PvcfXnZnP14lIv5o8nDycPv8Hl3wVEuf+Ti5MnuCoX+37xyK/ySZVh4cnv9Ko8WZeNPflo8o1evWuX8zCFcLWViUEX8au49vLiKnelR0Z9pN//+fJXgbn9+/u3bx+/5MOvLn0BuoYnk8+4/EtVr0rZDv77D1xpbqBhhfk/tI+Jvnkpcsun9Uj2pMldCf3rt//GffPfZ+f5RFSu/Mnk
*/