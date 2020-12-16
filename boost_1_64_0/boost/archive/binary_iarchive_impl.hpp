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
u09t7r8oy/13kc39Z8nPrG5j/2DJD2AE5e4/S/5TO23uP0v+cbxH29L7cip7CigozgwQ+xrFEOKIV/rsL2gLeHN7ETttxH0n529xaav0l8HeKrIoi/VOUi9o9szxRxrRUtMRSyh7CZooyIxLW8MdTkfd57efS+XxS3lsALyLcqd3SKePfc74Ihd8OOTatKdHeFUUek9cGpDBdi/Qwzd7eKNcSo83DT3a1QDGnh9by8/h5kfgrCzHokIT95oz+G9ZGfPUnzHa0vqTuyO419Q/OB/InLya+ufJwJsuZN1eUKq9zH59If3y0LbeV1P65UG/Wkm/Fp+mfl3Izi233tdFnGe95+9U6z3CZr3nfP2r1nt/eOn1HmFd72tQt5VeKhVV4m0p6aXunsrQNtHV0eiIeXXEYVmskRbE8YD4TfLAnHn/JprRcbeZ9Iuo2qXhzGVwJDkvYjyQwxZ9fTXz/frP7uxuYb4K/Gy3CQdEYjTHsXG22OtO+FQUMf62hXEyxb9BQ52PjH2pjIFume7596/7lZ9y6/lo2HnW8ztci9hUlpXUi6r6f+4qljt/fRj/lWnULY0m6veiUfo2msqN1sdVcDj4J/Zsd7iT4hBCDTCBE9mM6mrAwd5Jlqs+xWfNrASm72LC0qNVhLu1fDGlyQAqR8vkKtJR3Z19fnIUIey9ezoNeYd2DIHFE1diACRPzZ+irtd5cr32Ko4Wo4/up/QmB+molDXDhpdn+CSnDbKqTFbRvAjHBVoZsj8bZu2DRmizHeoMHJXFpZF/rjeMlbkdAdWtb/Ed+xKT24jRWRrN6kp+W9JPV5A5G2ixRMOm1L/AHcbTCP/1aRz4kwOoEwM+O9JhmCF3y59pqNfLPPQoMuZB1y+GrAFJzZJEAlFfXGC0xs/cXhH608BbSjdxmbUDv4p5Nvdj2Ul6KFCsJgkP1GqSTutnXcFJWhJjbECcXAd4MZ4qYwOOlSCP6zCTZF+DiwOTgi3J2095RJuKZTQug184HLFP3HZOdTYjMZMUbKE70IzDKBAqyiTnEBnaarJSzAh8nf+4WoAHRTVs6XfRDjJ4z+05XZ/FZBqbM4Zs7xajvb6JFHy8jtFeVa/mQgeouTXS3J78qaq5e6S5/tJcZG7Pp/TWP9ncOpIUNhGkf+QsN0ptYVg1aVjRHozYHdhEeH/Zee23ulXCduqbCD2X8kC0Ms2QU18jE2kn4EAdurEZMmouO099za31hehvaqn+xl9Yf3+5vx11wa35UbV6lF7vXLhYcM9Ygut+Aj6RfYB0Yz0r4W+WbkQifSNzoXE/ymUUv06VFQ3zh1XBMet+jV4U4yO+lBlHXxt0H1zF6LjbBesuelITC6Kj6dqRNNKWOUU77AFm2QKbWMJ3NTNveiWcPQ58l0O4Jf8RteHeEASzdx/xMc9jz+Xri/CSzKFHgVbWIN2d9yY1Pb2K2Ixd7jIsJ0fICwYFn6ZrTW5bfrkMXNvMM0wXTzu4qkmvChXpMwtQMz0hsThztDLVT2T+SErpmyEsNNRIrwUAdwT2uaQKl66tNIectBr6IDnN9FE7g8ZflwKeejidkWxh0cDfi5Eq61XjgdO8KunQJZaIwVgPCrSJic35RljsPzGLfau4beqnD/yWDnUZxytubQMLmfT6nxiT4Ls0/xm1Uv1kpZK/Ma6CYr0q11K0VV7iPCKRRphfQPLSTHjQkeqrjEDiTtoBQwHtdxEldphV/Y4odcBV+mWFTLC19xr+kAL9PVQWE5sVR8Jk8HhUw0K2MYBJI5nEFZEDGrN3N0jvnttL+0hD77boWftxNFAqNopddstlhbiPAFkQIdLiUa3CHPo32FjUGqLRO+UxWTXnRXNFops=
*/