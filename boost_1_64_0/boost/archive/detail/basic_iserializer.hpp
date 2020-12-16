#ifndef BOOST_ARCHIVE_DETAIL_BASIC_ISERIALIZER_HPP
#define BOOST_ARCHIVE_DETAIL_BASIC_ISERIALIZER_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_iserializer.hpp: extenstion of type_info required for serialization.

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <cstdlib> // NULL
#include <boost/config.hpp>

#include <boost/archive/basic_archive.hpp>
#include <boost/archive/detail/decl.hpp>
#include <boost/archive/detail/basic_serializer.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace serialization {
    class extended_type_info;
} // namespace serialization

// forward declarations
namespace archive {
namespace detail {

class basic_iarchive;
class basic_pointer_iserializer;

class BOOST_SYMBOL_VISIBLE basic_iserializer :
    public basic_serializer
{
private:
    basic_pointer_iserializer *m_bpis;
protected:
    explicit BOOST_ARCHIVE_DECL basic_iserializer(
        const boost::serialization::extended_type_info & type
    );
    virtual BOOST_ARCHIVE_DECL ~basic_iserializer();
public:
    bool serialized_as_pointer() const {
        return m_bpis != NULL;
    }
    void set_bpis(basic_pointer_iserializer *bpis){
        m_bpis = bpis;
    }
    const basic_pointer_iserializer * get_bpis_ptr() const {
        return m_bpis;
    }
    virtual void load_object_data(
        basic_iarchive & ar,
        void *x,
        const unsigned int file_version
    ) const = 0;
    // returns true if class_info should be saved
    virtual bool class_info() const = 0 ;
    // returns true if objects should be tracked
    virtual bool tracking(const unsigned int) const = 0 ;
    // returns class version
    virtual version_type version() const = 0 ;
    // returns true if this class is polymorphic
    virtual bool is_polymorphic() const = 0;
    virtual void destroy(/*const*/ void *address) const = 0 ;
};

} // namespae detail
} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_DETAIL_BASIC_ISERIALIZER_HPP

/* basic_iserializer.hpp
vHqbm3R6vc1Ufz5e1KilxTzW7phbdP7PRO/59MRczn2HO/835/fzS1fnGr8vPp5r+Lz7E86L6H/tPs39s35FfxevQm/igLzn5h0UEBKmZ6/SD8cswm/uh5YmjYvka8i8398/Q1l7rU0msTfufAIDdDv7fBmh5PWfgnWKWDm39n97HRvofHHC5i9Avkpgr3VLirEv0Et/TQnttW5LCfOjHVPsKaG91uZECfOjTf9SCe21NvkL/qz9lsShM2vjRD+rkR9EbudMZOZHb0ZPXG/GiPlNwrV6IvxZu8KbqkW/B4VdS4yvIT4ka/rX7zgwRfkw7A8n9ZuF8imBvdbtIfbGXVAI01f2pn+U/Lro1yKK8EJvxvqDcqHnoYqdRDS6XsXtbxcaX6/yWvj7/jaPhP/aMe9NsP1aeGDAr+yq5zDp7PT4xfw/Gz6uht78fTH5cyDxDJ0fq7dryp7Psuj5QnOMl1ct7fiUDZ9iWTQ/odnG1/co7f0g5+/ziCk+3cynUDurRwvc9SvML3r7smtFigSBsHBfUZGXz7W7YozFDzT22LmIyXcLL+P1U4sTzi2PtJxi1rtIvF87vPLjI8bLOeJC2TuWMw9P2hW+0FYyXlJlQuZfA16Ilv6siO77Hb2Cfcmb81HqePp1+yJ2A+QxXDtsJMG8EK3VS0+lxs6mKO7CD7Fn9Vx7ZhcHZnPJW2MKvC1soE8WKCj29fDCfNM5ZLeAEJmdWiMpUPTejz8rl6hkgYSzIkHWRZJjJap4G4VayZ1WyRzQsenFcovT7f9Ru5qfSlGqsUv5JXmOC21nf7EvN1Ya/PxhIxt+crU8l3OxEfukFZ84b7ddc+BW6JCTWy+P7lizfMDWa5drTK37NXXssgqO59dsvTP7hvJ76+136uS9WH93x8xhzQbwJw/ZNWd4q9cBc3KafpRO2XzvjUm5Gt8mpl+l8LZzcI+Bi3/0XDLMY9q7SeoZlXpum6jseWbcwJedrUbWXxIxeGuv3oc6XHaYXy36TYsmG84fLUiPtqmV6n3qlcuNHRtupk6sXMs1elzlLKnnPxpsOJhs9VfzLo57r7denxLdNzryrXXkw+mrI1fFzO7Uw6v6Y+GADqcit1mubuHcN3fL2cfeVdZnRORMe6IcUqX6y80t9siF/Y6ubPnBsZa6hmffsw2mjZnXZteV9X3PNZWOCHcalJwxw2Z2p0lu63d2Saj7eP+RaY1sYnPLXxVMWdnoa/SaIZ2c0p7369dv9KuNmvQnpk2a3cysK342wnNsk6NrZl58K0+06ODzbtRIvwr2ZtToJZ0LTkj6z2uY5RN/rNFc6ZMPgvkV4woyL66+kN1tQHzriKs2yy1mLm7TbbW0wivZA7dB1UIL3HbNbvF1WH3x65wkk/UdPHudis2s7DuydsbL8VsWyvmHl44euq//OLerGnm+ijqYvtCvjteyAQe7x6y6GFwmuWM75Z0fdT1M5/k0/Suvfaeq5nkXn1rcmHfgdeBJZXjZwXXnpF1NvWT98fbjD3VCf9x3C0rdtjdfOmtXmQNm20JWHjwSvdDrUFbf/sKmA2qvl3+N3xou9Xy2qUM1+fMwt4bdviW2muEwz48/Irf83v7rzfLu7/veuc3tsjYWsZu72NfuseL0AQv1CX6HqAoXbny9uHPvgdRIc6foOsd4OVdSla28flgvjMtd3PDrpydLJ35q7HTjTg2Nu1WC4PuJBqGtV4eVXvtlq4dT9Jgm3zsNdgwfeYfnubtH36zs8fJT9t3H1LkhqXnnwwqfy4d/DrM55hS3RhUZMn5D8z6SEz1P7e63+Ofd7CoFO2Z7fLHcMarRd+nWb537XDxvl/ogfK6Y/2nbnsCJFybP+to=
*/