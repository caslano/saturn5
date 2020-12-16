#ifndef BOOST_ARCHIVE_DETAIL_BASIC_IARCHIVE_HPP
#define BOOST_ARCHIVE_DETAIL_BASIC_IARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_iarchive.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// can't use this - much as I'd like to as borland doesn't support it

#include <boost/config.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

#include <boost/serialization/tracking_enum.hpp>
#include <boost/archive/basic_archive.hpp>
#include <boost/archive/detail/decl.hpp>
#include <boost/archive/detail/helper_collection.hpp>
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {
namespace serialization {
    class extended_type_info;
} // namespace serialization

namespace archive {
namespace detail {

class basic_iarchive_impl;
class basic_iserializer;
class basic_pointer_iserializer;

//////////////////////////////////////////////////////////////////////
// class basic_iarchive - read serialized objects from a input stream
class BOOST_SYMBOL_VISIBLE basic_iarchive :
    private boost::noncopyable,
    public boost::archive::detail::helper_collection
{
    friend class basic_iarchive_impl;
    // hide implementation of this class to minimize header conclusion
    boost::scoped_ptr<basic_iarchive_impl> pimpl;

    virtual void vload(version_type &t) =  0;
    virtual void vload(object_id_type &t) =  0;
    virtual void vload(class_id_type &t) =  0;
    virtual void vload(class_id_optional_type &t) = 0;
    virtual void vload(class_name_type &t) = 0;
    virtual void vload(tracking_type &t) = 0;
protected:
    BOOST_ARCHIVE_DECL basic_iarchive(unsigned int flags);
    boost::archive::detail::helper_collection &
    get_helper_collection(){
        return *this;
    }
public:
    // some msvc versions require that the following function be public
    // otherwise it should really protected.
    virtual BOOST_ARCHIVE_DECL ~basic_iarchive();
    // note: NOT part of the public API.
    BOOST_ARCHIVE_DECL void next_object_pointer(void *t);
    BOOST_ARCHIVE_DECL void register_basic_serializer(
        const basic_iserializer & bis
    );
    BOOST_ARCHIVE_DECL void load_object(
        void *t,
        const basic_iserializer & bis
    );
    BOOST_ARCHIVE_DECL const basic_pointer_iserializer *
    load_pointer(
        void * & t,
        const basic_pointer_iserializer * bpis_ptr,
        const basic_pointer_iserializer * (*finder)(
            const boost::serialization::extended_type_info & eti
        )
    );
    // real public API starts here
    BOOST_ARCHIVE_DECL void
    set_library_version(library_version_type archive_library_version);
    BOOST_ARCHIVE_DECL library_version_type
    get_library_version() const;
    BOOST_ARCHIVE_DECL unsigned int
    get_flags() const;
    BOOST_ARCHIVE_DECL void
    reset_object_address(const void * new_address, const void * old_address);
    BOOST_ARCHIVE_DECL void
    delete_created_pointers();
};

} // namespace detail
} // namespace archive
} // namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif //BOOST_ARCHIVE_DETAIL_BASIC_IARCHIVE_HPP

/* basic_iarchive.hpp
/+S66A0jvxgf1jBl/Pw0dtzV1pQZZ7U3ZWQXxlewfh7rZ7sxfpo74zt40L6ho/NQonzS6+b0D3thMe8DYEuMnSeWH4E95e6hE+nd0bAvcX3T55NhVulP95nRGwEU2K79p/vpSDwN4v3eZY5k6mFSM16R8izH+uPZ8M51mXAy1qYDoDfck0nCiJtMwn/tMFHMw+4SUl/a7Sglui5xksJIvRndB93XvATpxRruo3coST5i2f0of1qf2FDxt+oT8X5Xn2a8v+fc07X1a7z+vdhwtY1e/Y8uWv95oyBz6r8TiWfo4tN/397UbLiNPSeck25auvH2qGDzU+oX+2Ynp//95zJd36wi6/iYncV8AWZPfL1D+do3j/h+ZJeFzpaeJNf24ZzNKeQ5h96xRRLhcdIhsX/tovuZlij/0RnMdeZSTPnM0CvfeDZ8cLOi5ZeXXrQ+s1nZUpvvjJKVHz0G0I2vuNfnyw+LiOLOqhh3tcb8vj1SbPiGLkXzPznj9/2RDYn3a4cVDdL/SPDoRuaZfPih3mHeXUvMp4LsRiq2v83L1LZv49eXzw3ntu8xv7++Ajreb8rzZnTJy5ObLm+sYTiXq4pjjec3n6Rr2C9R2vTHlqw9FefAUaxGpit18EkqhaDH1qMTtyJhzzyqExZjEd7Fz5+x+JN6TnIqtqZL1p6j/8EtX9ZxuTMeriv/tH8Yrx9Ky/E/jPMSzZZ/ab382pB/Yf+Pv1c/Qjyvh2o3M9DPG/SG7/DCsZICYdgaIpUMImN/nSmnPoO4K4nhpHeNIhUUXsL6URG5hBXEOktlyfrX+HTj9VFOm87439+/6iGc2x7G6dWnjTa+uGh9OYzT44mWOfXsMv7v1ZcCBY77k+63Vo9HdSX2xarF5PmS2U/pEoXZ9+5RuFGRnYrM82cLFT03lYLnUPpdDAfmAYv8xpOqVEPZWKscUqylKbbmJeNLHUVnw6DyKJtgdmcVM4NFPwbTKQZjf7JQgDXs8NAuga7Q6NYtugSH9AgujE+FMmurXbC26q1dEqaf1Ekcjl2kjOypUdPr6gLuIq95UTvMokvprgSnJgNBkhYnPFz7fFz0dNrnUoo43m+dmV6Hb2nkoPRk0mKMf2SE+cII92MjnAbGGBXriq8/+gEQuye5NUieK/Ekzz5F+rPPldCU/LmSpIve/U/H2yRerFL8t+Jhz6xePMqIo/XV/1Y5KZT6b7S6e/uEY6nOU9uSXLUT+xS9Kb+wifHDwkLCXLEVht6VjpntPtaiftqNLtq41GBzms+htBwpw8SkkExwMZtUrXVmWo6BbIg/zoBoenpwxZHd+V1DI3qxOaT5pol0pQrXNSnmGpi6xhoAWasLi+Qz3DIxtA6SlN6tpkHGyA4+0k8w7wqbl7gcVUKDN4PJenzxrtOswn6zNK94F82xL8Mr3ik49t/odyWLcWla+5LhyJtM7Jm81/RgYv7u/cFsjn2oDa9Y+x0c+zK2xduf4OT/d/ejn3BkvFtCe21YQQntdW427EvyjFyOLXNib2jrMNtwHP0Tzmbab++7iGd83N7pF+mlFJNep5JeD+t66uxL9v6sgmNvzivepXHsS/GKd7M59hV5xbsNHPtqvOLdCY59dV7x7jHHvgavBG5OoX1dXvGuFse+Jq9450Db65gq3nlx7OvwinfRHPt6vOJdypy/N678X3fk3SvuphaunvOhC/13xIjsHdyLa8+dFiEyd5ML6/wCw0ODvHtFYDjAyljtxvJ/L70MkPic9WQiR+gUjOyvJ5NNBuxbdOybeEbzx2Scq48gKmPpcO0469RE5q5TE2fwfnNRvf6mBYNy4gRyw7mbg7h6bFoyqtfbtKDT6zZZGX8P2eA=
*/