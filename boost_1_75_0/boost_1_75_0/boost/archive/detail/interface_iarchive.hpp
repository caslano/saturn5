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
0h527u2T9IA6wvPTnlCl5uKrgyUqXeoTGXlUTVq+Pg+ZLyiIFV6KFd+Syy9ckZ+vK6J85c5K50OD9/t/d/WT2zqFMtjPQdkrtuXZebiZG5FaDNJL0xcWZuSllVA1Edl5/Z5Xphauy9BFbcgoLNKvFd5GzM7PC0nFdyNR3vgKYq4o/6BUIB6T/RS+MCiCYnSpaU+IIAmmLczOL8zWlVAiL9l566DBuvy0/FyqJlh4BRQA6wpBBCEZGelrgQQVl523YuVS6Z1R4b1B4F2bn5udVqLJJW/FLs8oIccaYsPxcFUV2htc3nD5UcJmBL65ju+ix2NfgQv32HHTvBj7Bpo3XLhpjV/drqVw8w7GRAp/To3bEOCUwNUMVwtcrXDxcOGnHbpRyDKoGy78tpe3DLchoC64UuAqkOH2A9CGqxauvTLcdgBacOGhAO1w4S9FVQ64vQBlHHA7AXAdcPsAcPDDmY6Q74jbA5DviNsBkO+Iy/+Q7ygYm5rGZXxcsodnJ1yKJz+upkxw4XFhamdcJsclcQpP0KXULrisjUvYFP6qlapAAQ7DpWK4D8clXbiPwKVXuCtwiZTCHz1QFfiBpVG45Ah3V1waFAS/d7izcsEsl362575NofRyd1a2Df+f9006XaEshX7jMcJZec7bpZ99l4rP9vhZUFe1u0BDLeoE5ZIgls/IdFYOW+esnD3XRekDV/G6/vWZoPwhKF8K
*/