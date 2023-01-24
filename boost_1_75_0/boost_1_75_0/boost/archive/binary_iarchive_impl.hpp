#ifndef BOOST_ARCHIVE_BINARY_IARCHIVE_IMPL_HPP
#define BOOST_ARCHIVE_BINARY_IARCHIVE_IMPL_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// binary_iarchive_impl.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <istream>
#include <boost/archive/basic_binary_iprimitive.hpp>
#include <boost/archive/basic_binary_iarchive.hpp>

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

namespace detail {
    template<class Archive> class interface_iarchive;
} // namespace detail

template<class Archive, class Elem, class Tr>
class BOOST_SYMBOL_VISIBLE binary_iarchive_impl :
    public basic_binary_iprimitive<Archive, Elem, Tr>,
    public basic_binary_iarchive<Archive>
{
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
protected:
    #if BOOST_WORKAROUND(BOOST_MSVC, < 1500)
        // for some inexplicable reason insertion of "class" generates compile erro
        // on msvc 7.1
        friend detail::interface_iarchive<Archive>;
        friend basic_binary_iarchive<Archive>;
        friend load_access;
    #else
        friend class detail::interface_iarchive<Archive>;
        friend class basic_binary_iarchive<Archive>;
        friend class load_access;
    #endif
#endif
    template<class T>
    void load_override(T & t){
        this->basic_binary_iarchive<Archive>::load_override(t);
    }
    void init(unsigned int flags){
        if(0 != (flags & no_header)){
            return;
        }
        #if ! defined(__MWERKS__)
            this->basic_binary_iarchive<Archive>::init();
            this->basic_binary_iprimitive<Archive, Elem, Tr>::init();
        #else
            basic_binary_iarchive<Archive>::init();
            basic_binary_iprimitive<Archive, Elem, Tr>::init();
        #endif
    }
    binary_iarchive_impl(
        std::basic_streambuf<Elem, Tr> & bsb,
        unsigned int flags
    ) :
        basic_binary_iprimitive<Archive, Elem, Tr>(
            bsb,
            0 != (flags & no_codecvt)
        ),
        basic_binary_iarchive<Archive>(flags)
    {}
    binary_iarchive_impl(
        std::basic_istream<Elem, Tr> & is,
        unsigned int flags
    ) :
        basic_binary_iprimitive<Archive, Elem, Tr>(
            * is.rdbuf(),
            0 != (flags & no_codecvt)
        ),
        basic_binary_iarchive<Archive>(flags)
    {}
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_ARCHIVE_BINARY_IARCHIVE_IMPL_HPP

/* binary_iarchive_impl.hpp
slvUJSD6xDg++YlfXz4F76hoTGld2daIXmbzR/zW+K/OVlIuzha+khAVm2W0cH9HoejTStBltml0pXcsQzeX/IdRUOIT8UBIl/0QyHe4NQ81r1Fj10WAzCj7wcTyvvdniSCTy1B641t+1d2oyZzGKrPgLXrM9wDqrLgpAZLrFzSCQQT5Jt8Uz2Ab7RStOrIEQagu2T9d6CTeRwA0B9jHBOgLgBjaZiRXdIkIRIStFA/KI/97cXNUx+c24QGq2Pd1p3DWJuEUjsVANheChGf4FxnfKSouvArrDs9wUa7uGV6SGzVx9/cPH3zm7v4heYENa5Edgxrp1bWjFPzDcjdl+eg89A9j8jT/8FWffzggz98/bJMn/MNIbNI2r9k/fED4h311/9CxE0dvGOPYqQkfwvmZ3Ds9wwO5zZ7he7nNnuEbuc2e4Yu5zZ7hK2vxHHeun2f4VK6/Z2hS6rxFPiJLXiL3sLyYfnkm1NRAx0SFps+8FwVH0OEaAkPif0SD7tYS+X7HrRWS6/eoY2/g9zo/rAbmvUSm2/dP4fxS8mcif5ZS595Pgnc+0GfYo+OnegbREukp1AZOAuv/tk9SCcGTaLyhlaYR4Xy90GekCtfgzN3s5nOa3fzHAt1u/ssa3Jiimvtj//iLn2sQ0yhcgxx/1+A3cSc0454KuL1j1d1o17BDT6HcT1+tL4T3CTBlNS6E0bQQMleLhZC6utmj
*/