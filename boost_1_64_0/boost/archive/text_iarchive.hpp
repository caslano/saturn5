#ifndef BOOST_ARCHIVE_TEXT_IARCHIVE_HPP
#define BOOST_ARCHIVE_TEXT_IARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// text_iarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <istream>

#include <boost/config.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/basic_text_iprimitive.hpp>
#include <boost/archive/basic_text_iarchive.hpp>
#include <boost/archive/detail/register_archive.hpp>
#include <boost/serialization/item_version_type.hpp>

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

namespace detail {
    template<class Archive> class interface_iarchive;
} // namespace detail

template<class Archive>
class BOOST_SYMBOL_VISIBLE text_iarchive_impl :
    public basic_text_iprimitive<std::istream>,
    public basic_text_iarchive<Archive>
{
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
protected:
    friend class detail::interface_iarchive<Archive>;
    friend class load_access;
#endif
    template<class T>
    void load(T & t){
        basic_text_iprimitive<std::istream>::load(t);
    }
    void load(version_type & t){
        unsigned int v;
        load(v);
        t = version_type(v);
    }
    void load(boost::serialization::item_version_type & t){
        unsigned int v;
        load(v);
        t = boost::serialization::item_version_type(v);
    }
    BOOST_ARCHIVE_DECL void
    load(char * t);
    #ifndef BOOST_NO_INTRINSIC_WCHAR_T
    BOOST_ARCHIVE_DECL void
    load(wchar_t * t);
    #endif
    BOOST_ARCHIVE_DECL void
    load(std::string &s);
    #ifndef BOOST_NO_STD_WSTRING
    BOOST_ARCHIVE_DECL void
    load(std::wstring &ws);
    #endif
    template<class T>
    void load_override(T & t){
        basic_text_iarchive<Archive>::load_override(t);
    }
    BOOST_ARCHIVE_DECL void
    load_override(class_name_type & t);
    BOOST_ARCHIVE_DECL void
    init();
    BOOST_ARCHIVE_DECL
    text_iarchive_impl(std::istream & is, unsigned int flags);
    // don't import inline definitions! leave this as a reminder.
    //BOOST_ARCHIVE_DECL
    ~text_iarchive_impl(){};
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE text_iarchive :
    public text_iarchive_impl<text_iarchive>{
public:
    text_iarchive(std::istream & is_, unsigned int flags = 0) :
        // note: added _ to suppress useless gcc warning
        text_iarchive_impl<text_iarchive>(is_, flags)
    {
        if(0 == (flags & no_header))
             init();
    }
    ~text_iarchive(){}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::text_iarchive)

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_ARCHIVE_TEXT_IARCHIVE_HPP

/* text_iarchive.hpp
/VKJ5BloynaWE/zpeY51opcg74LWx7gOl8T0CDKuwl829W4/xiWmR33jAhWV9Np0paTnM6mkqdOt6tNIUZ/8/JX65ClPuG/k0R1PLx5l6RYsNUV/53io6P9WdaBcMwJjevhmBEjq6eakJ3HSkdPFQ5jGD0FZuXy0hjPyE52X4khcbDa8EV9LqmJDlRG4d4jBuqSoZgVUi/B/QPMCqqn4fwX/v8DxM/z9LqyAahv+r8NxU/xtif+/4rd/8wL/97b1zP2vVW+MokucSPv6cKN6Qd77xETKvoiRyi5AVatTXWrihPNHQGGszPwqxKFNKbSLCCVcHThUT6EhIrQaQh9Uo9BQCq2KUF1cM/xE+Jlq3KsRe3ZpvT92dd+fmy9/5rVR6Deqi+RHI/lYvZ+sxXdMaTefRSmVMfMBVUYZh/H9lHpeE1fRDrTVlHp+WV4ApZ6yix/6nx3r4rwgscghRq9PCQpyUFGIlx3/CVAl2OEPJnn+9fn4772P9sr4l7gDfSyNUsd089XHRGJ+zqRqYTGRQFz9oBV1Kw7oY0JcIH5gF9QQ6SDr7fdBH4EbvoMGRFb9ZsLsFM30xTxaQra8xIKFZBrlw236H4KepRFsIaTSd50UETBy4YAFkTqNHrMzXPVxmSZ2Gr3heqY89RUXidKhNA5BssKLhu4cyZGcY9I2RGJUX6Zgf11FOZVJ6yNiw1W0oKJVQ+4j9NJL4liPY11cP/GK0qqI4dvVKeZPQmSkpG49VXlLze7TW2qEw/j+ylsaIN7S0irKW7okP8CgMVqhnpK6kPm6fHydq/V1PcR1vc3X2cnbcJ3cKNtEF5fGd4jqeuMqVFMHOyna3zjxsnv4BMeM8cUNuOj9j8kBPESKlyPh5Uh4OVIkmtx+Xv+CeW9/jee0F0bRTzksDIzgu6EnpCcWopE0u9ypNsESopWPh57H81+bhLofD6FBZcvH47w8GW38X9W0KfYPRO6QFSZOhohQ4zLLDWPxG/tl9cMfcvJCmp4cGBqOQwR34GAhXXbGb2T/KBQXL0LLJHnoRUjl5giZjpAUtWc4SZcfs0feu/05MfWCJoHqpftilvfq50qB1QvClQ57SE4YLyeC3TzpBcwGjqSejTYMRaKR5jmoMtQ/wAOiw68fmRD5aagQ7u49EXVYtDSxk5S6+KWR6uJkHMaPVOriLQeui2crKXXxN7nCHe6hRdvjPZm8I3B9uPn6Jnx9A+vrZXH9IvP1rrLxNl+vx/WifQ45iLfLvJONXUdouExaz/rc7Q+S1JkTlcSNMiV+Y6JV4g9F4nXMiT+Wv0LiciE0K8jhLgvW4ZQ6OmmYoWgPPVU9TreBpF5sTncepxtjne5Tke6Nikq6T+SalG5iFjo7kUqqKHcCz29H8vidmhKSQDVLauuDu0AENTcBltwqmnMrzbkVsc7ttchtlDm313LyLeTWlnJzpm7mYnue6CDP5b/n2aTpVfOefWd4zCA8FTOINNtDbsV70ySB8FsIOhkdkoqgm9HhN3F0KjrkJI5uRIffwFFadMgpHF2PDr+Oo9PRIWk4uhYdfg1HZ6JDTuPoanT4VRydjQ45g6Mr0eFXcHQuOuQsji5Hh1/G0fnokHM4uhQdfglHF6JDzuPoYnQ4RLrw1OiQC/LpBNH39NfFebPY2P42Vb/FNXm0v5iccNA8YyfCS6xTo7q6D8q2DC/qnxnSEY8LJuBvPD1eSljuchiheAUm7bU6JHMk4yCHJNBQx9wp9rSRXwCm2P9rZvn++5z1+POUp9xISNqWIbylnWzKtIgvdfTY1duknRHgydjR520Q/3YjiwhOJm3zOvSxq+gk5J/yQolTyQ1NqlaF5FCr6Y3M5DqIbyo=
*/