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
CJn3/jNzhiSDa1hLku7tuEfYKnqEvZDypA6hCsUkYodvULnCV7NpvMmZvjm4U0UriR/O6yFTuTPlv/usaRlMmnQ05z0f4nxhv/gSlsLyGalGbCEHVmis7bBInGmm/XaadNdDO7lu/yHIbNmZ0n2zMR12bMRR4VqMVaEVFQkGhTXzXH1lJ5+rb0Lmdzutvsb5+VHzOUdnNy4SAmKnVCsnBDf2oaQMqEpiZxP2XH42Ifq4yQbhJii4h7k2Lk61cVViQmoXN6IyEifxGhEt7NTRwugVaOEF1r7Ox/lZ1/sgM/w4WUuZs4jDbNTU9TgL08MSNTiKYpjJfNi6JrLYoNn+wOT7dPJxPhdeg8zZx4mOgJ45EHfhj0iAUbYmjVn1lNourqfMgcyKXalY7QNmA//6lPE+E0GyMw0ZYchSS4xa89Hdgm0whBExKnXLrUq3WqBtcHQ5C2lgrywiH9onl1PPq0HUoHKKQNI0w1njyKfz/0t0EUd3cV3ES5A5u4v7/9lFdRE3/Tili1jCdBEBCeBwvysXMvI65QmO73MgE4RU8QTB95JaDwDy+uCSbBewKP0Z3IY1Fn+CitrXwv2n7GavE/WC9I4wJp2ksnaT3qMZXkjeTd4a5jJDHekwL8wyw+EnUj6nIbMT0inehp2kDc+n2/Aj1oajmTZ8kWrD2GtQeixL+oVwQnqYOE2ZTZfwuydMuoTscRV9bZzpElzj
*/