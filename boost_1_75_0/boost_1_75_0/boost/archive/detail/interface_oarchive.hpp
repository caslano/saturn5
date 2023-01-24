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
+PGP3kv/GAfz10To4+K7Vankra85VDr5rQJFrcjvNVJi8yvyV+Vl20EEKu3ieyztgRJd8l1UqLMDLvkPIEkoi7/FlYn5+HlDqU34+1ypHKpdpQA5wkW79pXF3+k6DFIWf7tr355wwEuxg2GZAnguhasg3YHQQpzB+EgZQGv3BoXy/QG0DsBzI1wpNhmhhTiD0cJyavC3EAd9t8Fw0J+zp+0Oz2125fy2DF6uGfLR36MGyUuwo4llLw9okwnKVYzsL+8aeK6Fy2tkX92IN5i87cviP+SxeUA7WgfQss/rAZh8VJ9eS4doI/qqu4fIQz/VnqYWnr3saGbZpVuHoFE5gEYCPO+GywRXtVLg29swuAxoyK94enC6+5T95eMGeM0DYK0ACweY0jA4jdwB+OGA347+r6vAF/q81CDl0A+W4EjX17W/novhudq1f7/aN0Qbs1z784DtxbYh74PhY3vchsgb2H6UK63sz9sOkHv4EDLFtks6saeD8ssdQCcBnve79tejlI+8lSoHtP/pwWW5W9lflt7K/vZySDl4HchDK8DOQB1ug/BN5DN66DwPyJsxuo8/9H8Hkwn6xIeGyEN/3p5m8Nj+zxWQv92uDvTxB6ODfj/GH4PlHRpQBwU+8J4hcNsH4DYDP3vs6ncf05d2G4IGxmj2NBTwHDwEbsoA3DPjBrQf8rfb1Yk+/KDtB5x9dngtQ/TX5gH17YHn
*/