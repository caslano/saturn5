//  (C) Copyright John Maddock 2003. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//
// Boost binaries are built with the compiler's default ABI settings,
// if the user changes their default alignment in the VS IDE then their
// code will no longer be binary compatible with the bjam built binaries
// unless this header is included to force Boost code into a consistent ABI.
//
// Note that inclusion of this header is only necessary for libraries with 
// separate source, header only libraries DO NOT need this as long as all
// translation units are built with the same options.
//
#if defined(_M_X64)
#  pragma pack(push,16)
#else
#  pragma pack(push,8)
#endif



/* msvc_prefix.hpp
xOr44yMR8YrrHmqC5z1j7MN/DjxaVkyjtO1SK61omqR48cDdnYvsluCsMj8TaxcTYTgSfYKBx1Mu5LoFsB6I9gt6tWj4rtvD0deSZPq5vvYG1qXVLzp8tC34YI3fA+0m4oHuC5Pwxs6ACe9YwJs3gLaOC5h2VjrvuU/1+ZtaLivXg/vob077fd64bp/fHD/ntg/DL8NgMjwNJkGycIaUtu+0I//YP7Trs3Eyn4XwZTiZj50Z03hQK0t/nEYXSNNWpT1izEB1emW0fQm0jvPwIoyuwjSyM22CKqFbcbjxeAzDSRzh8XQ6e14vcFFr2NFnfd8tOP8DUEsDBAoAAAAIAC1nSlL/mKEM8QQAADYLAAAzAAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTElORk9fQ09PS0lFTElTVC4zVVQFAAG2SCRgrVVhT+NGEP3uXzFNVUhQcOCgul7hUHMhFIucHcXmKFIka2Ov8R7OruVdE1Dv/ntnd23S3KWFD2cENrszb97OvJl15x3Y+2GP42o4ePGJzW+MD75bp2klPtNEbXeI4y9gf9Bxju9XhBrA2utL3INXeX2BrvGKm1in+juOXxFurknqPwPtPI/1J65Yz8Z/JMqnit3lCrqjHhy+e/cb
*/