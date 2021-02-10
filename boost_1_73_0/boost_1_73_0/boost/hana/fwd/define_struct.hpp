/*!
@file
Documents the `BOOST_HANA_DEFINE_STRUCT` macro.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_DEFINE_STRUCT_HPP
#define BOOST_HANA_FWD_DEFINE_STRUCT_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note:
    // The weird definition as a variable seems to exploit a glitch in Doxygen
    // which makes the macro appear in the related objects of Struct (as we
    // want it to).

    //! Defines members of a structure, while at the same time
    //! modeling `Struct`.
    //! @ingroup group-Struct
    //!
    //! Using this macro in the body of a user-defined type will define the
    //! given members inside that type, and will also provide a model of the
    //! `Struct` concept for that user-defined type. This macro is often the
    //! easiest way to define a model of the `Struct` concept.
    //!
    //! @note
    //! This macro only works if the tag of the user-defined type `T` is `T`
    //! itself. This is the case unless you specifically asked for something
    //! different; see `tag_of`'s documentation.
    //!
    //!
    //! Example
    //! -------
    //! @include example/define_struct.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    auto BOOST_HANA_DEFINE_STRUCT(...) = ;
    #define BOOST_HANA_DEFINE_STRUCT(Name, ...) see documentation
#else
    // defined in <boost/hana/define_struct.hpp>
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_DEFINE_STRUCT_HPP

/* define_struct.hpp
KiBNUxnJAJCOgPMRLTcIkbNYQhSeOBQ9RbFEeNBGXBpza+DkSC4WUngz6X32gytoMQ9vUGIuI/wIeiO4ilEBxXeB1xTMWeJN+9eu0z4776NgqBkC/pcrH7gi8Rd6lsRVMoDhEBh3CDJKETzggABZIIWpeYIeaB4ABuF3ijeM1jIAkuhfiJ3u0z47G7x34K9fDx6EJzS6hh4BUi3FtUH8D2DCABYhljLAqbx6KQ6aL5ovRKxWy00A/s1MBrxycQIKWE4QEugPCz4sO8zFXc0TiwwlyOM7UTvrvdbvfu0ORyARzpvuB/GzaN22DlqtF/B/MIlgrmAwJtKkZpLw1wOnc9br9sfOuy4oquN6Qc6sIW2qZiI190H/siRlQg3sO3ETFyU6exhD36n9CEZLnGWCYmo+Jq1iPfks7+bhlf0MbBlYRpAr+zEITQCCBA8FrL1WY+opLXIIC0cUzjCbcw/zWRJ5bpyDffvn1k9uHOzlRkQVtgT5SHLTW8Bi+v5UKbaiEgLTDr/hv3ItVflCRlEY7eRfb6nXNBxqNZj23I0TkbZAtR9rZX0pD20q0DQWchFGd7lpyMVEXq6uNOC33e65c97tDp1OdzhGGXDFMgonKy/RFhQtmkQJgM8F6ULuH5x3+8hj3Q/jYVvcgCXE
*/