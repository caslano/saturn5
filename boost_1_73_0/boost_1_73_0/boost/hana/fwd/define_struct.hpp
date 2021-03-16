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
U973OLonL1NRcL6VisKM9unJcx65w4lbVNs9jGsfdGjkf4QRlmGMH36EeOXv5YOmD1UnUJ6VdwBcr7ir95LiUzBe1sltg+Jm1EbAfMBN+mNdIR/rCvowq4SrEe5vOler6J/VClflx2aZT8We77yyBloMyuY3qGy2/UL1VuFvU67cb3O+Yqc3uMmrUahshm8Dn6SHvOb/1QNeijq6/zQMH999feX7T9uq2AnNNp3Fofqk8hSqX1ol/qpiV3dQDdM=
*/