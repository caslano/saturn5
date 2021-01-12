//  disable_warnings.hpp  --------------------------------------------------------------//

//  Copyright Beman Dawes 2011

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//--------------------------------------------------------------------------------------//

#ifdef  _MSC_VER

#ifndef _SCL_SECURE_NO_WARNINGS
# define _SCL_SECURE_NO_WARNINGS
#endif

#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif

# pragma warning(push)

// triggered by boost/detail/lightweight_test.hpp
# pragma warning( disable : 4640 )  // ... construction of local static object is not thread-safe

// triggered by Microsoft's own headers, so disable
# pragma warning( disable : 4820 )  // padding added after data member
# pragma warning( disable : 4548 )  // expression before comma has no effect
# pragma warning( disable : 4668 )  // ... is not defined as a preprocessor macro
# pragma warning( disable : 4514 )  // ... unreferenced inline function has been removed
# pragma warning( disable : 4710 )  // ... function not inlined
# pragma warning( disable : 4986 )  // ... exception specification does not match previous declaration
# pragma warning( disable : 4711 )  // ... selected for automatic inline expansion
#endif

/* disable_warnings.hpp
R+/Zb90SC59+B8qu/964N3P5q2r4jefgmpQbxwYmjiE9utwbe723zrfryb0Iq1H4GtGzfrNvy+iC8pM3mRF5U8CnwRzNm28kbygt1PfmLAh9RyJX/Axlb5jfvgfApFfyl9+ssqWe72FOleuTyRtCQZLJl4B+sxshb6r/Tkgwb76RvDFxlDzYqHkQF5EHiZrBTTWgJkgUebDvSl9YHpSX5KH0vPL6UQ/uFz9J1vQTnkn/ZSmu
*/