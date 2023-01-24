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
Ww/KAqoC9Gh7Dxr+PnZR3dC9nCvMkciObrEFkA+V4EKwt0aIOzwuHqLClFs6SxRIPh9gXvl33PjZA0EE5RkyuGOxd7ASm0eiukbC71xM8E7zGWxnTIVU8FBoRHhIC3a5IhHkEb4bTbpU1xI3YrIqbsMZaphbwOc3XOhJrslsy0tYbq2ScIBXAaSlhMFP2M4GbA+3vA0rJJwpsTalIaJEMkr/8hncFX+GNF6ppGewJjU8cuoi3ioTCHciwofxVgM29FaBcCSCkO2yV8Gz63tSklXxFNFSSRf/Gfl4JLvqWHeppLUFlS9Z0OZFSRylOYUoTcJVB7YA/wuB26HQIzJ9Mh4ueZXIAkGOUWrPe6BVI2KSOXgt+lT5LwAOPQ+5g83AxZu87UWkxyeSsxX9dDvCRyFq1djZIruLXxAOKf8gbztKffcAPRN5lPLDZ8j3iUf5bD4vnHr8lA4nW1UUvCK4/Mdo1SlfJnftBImWkQCNBVsFmZJ047bvif69Wy7Kqpe9iT1YN6W3qZ1MdAL+6GlZ3p3a1XZS8Lfxy4apPmo3m54yGCnJnz6tdiLk/OX8Itms9z0LC6bKeWnACHVcYYRynKyww6/Al8LMRJ8/3YYoYSjWhk6kqUck60ustq8ttWf4NSldg+wJKCz9e0qm9gwfnrGKGLqTcOc5arCfeEQ1uCYuPIp6lULayDFkcK68DTsEyqrbXiK92pVdSICJ
*/