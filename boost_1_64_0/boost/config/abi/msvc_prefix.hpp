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
Xgcu8LoPrSLOXccfWLP2JZfQFp/JxSIKSystooyvAwfaTuhx5BKVf6Af24kdlJFY1+MI2iAuGLYLdpKUSVbCDOYa5RM4R+c64sZpENmpVRcvQcMWLNvfWJqJiJPcijMbyjbk2JTvl+xuM9sQu6jW5JBjGIkibacwr3XyAOU/yMkzyy3KRPONPYY2/4ZnsjKctICBq+GYlo8FPSp7KM6j0A6CUCzgx57Yj76szXUrifzcK2WCw91roW7h3JrGMZO7uROWZbUEhExiPbTxnl6b2wqkaVqUUQBr4sZHdsyE8W39Nm+/0iutyHZLnnfP1ACUnzxlrEOsPIhDVccNLstMe5UpJm+JILMCr4ySalcLxVHwGbrOQyZXCC8IgkQtLYa+Z2Tcp+rQOFKR5n4qcx6QJUYlgN/zs5T/QDuIUk8qhdh46gqvk5exvIWijKOw9ANXrDfVZz0uoq0Yk0+En8WpnyRm05pdysL5LpUv4KphGIdJKJ46qIGr6JeBpemIzPayKPFAh41HwXg/uUrlDudhkIVhGciknoqXCVbR9pCl4YvcDmWt5IlOo6lMuJ4/zeu0CFy7SAIok9uGSz5saOPtMcNkE5HYpVNYKejoELfOvIwnqPyDfCvzwywtQE1gpmncvafcGadMndKxEuCSVaocz3Adb5TLS/0yT3OPzlvMjFGfUuepvJMKJ3HSpPRv+NwP3vTbvB285QLxDR56zm5sjtxDcr66W7b5EM78Yqsn99iRd8nWPH7O320/DYgV752Sd84BHt1MRRrGNyd5wtU87D+MeG/Je89eObdCHtmU5FyMc58PXLpW5kSwd7oEb7hWPFlb+ilpAFXe3gtpAj7gn3h2Ya43tyxpWL/fsjgPa1fF9RAoZ9jAwZxDOVWekDf4tk17RZIJdyRCrrn5pdmYfolcugGFzYt1dwl5fDNHZ/Wuqn3LmPOQAPWi4hpJgMN3NTTt/ipf55DTuEGh6cgfSYE/fKNAC9xb6WsH+YOrZ136e+s2yjTXXK3W9TStuBeRyxeOZttSPdkd8vhRTRTnfVLn9uWcQ6LCtKcKxRm+CBqotwso07SQkeUjeX2/zMdkyfKB/Yfq1MgjgcO/zqyNlR50kId9vLGigP9OiPdRwB862SRjg2oL5A9MAEk9qLHhGHCHT+LMur6I/MGvtKke91btvO84yAydbEGTY7t0rs0daMcryDcnYshGPYXylo9G/rAZlG58zH+IaTTOTDD/X4X8YPzNXHNsvvgY5NMJCGtT0AHxWMLDKJv15Spy6Yd/uL5cOMH0pYmM5+lXpc3Ku4aMx8x/4gTymt8a076lkTf4HQMenuPv0LzmdwDQRgt5xrcOOPq9jJ3I4d8xYofxiyYOREI4x2+iOdyehdrefQ85w8bFJWZLV94U+U1jA7NZu2xwSQaQE+5CjmErTN7AQM7Q9yKw7sTNFJfrK2urz1GOaU5M/IQfurnk/d+xRNWP9rHeKMMTQJuOSeQOs23GdvoCcoeOC7webjHI15FiXjmHj02s3cH+BLnN3/Glug9eolw+vrO+9bBbMZ5Z+LrsyBv6/WT1Km6t+Nd6L0bnFbl8/gSkvbqdbmNwAKTvWiHO5mpAqu2Qb4ucpu8Gy9OHkDtcd/bdDjnDfIcj933IHfr2CKa9fzdw+RxQ3UlD2+KROwxyaH1tIs7f/MN3lji+znNN3jO4I+epdPC9m18B3n/vYY76nX7fnSAcfVgDiFjvzgoDZ6d9COMbuQtiIIXhe+6mw7sQjuu+RYuu+yLhp26RFeUNvF04Oy+UT+A3VO8WW07LOX5C+VJGW8N3IqKfaK/9JXe2MBxuwCL2ylGGgX9Y7KPlGMPAlky/tgaXBjA=
*/