//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_UTILITY_SOURCE_HPP
#define BOOST_COMPUTE_UTILITY_SOURCE_HPP

/// Stringizes OpenCL source code.
///
/// For example, to create a simple kernel which squares each input value:
/// \code
/// const char source[] = BOOST_COMPUTE_STRINGIZE_SOURCE(
///     __kernel void square(const float *input, float *output)
///     {
///         const uint i = get_global_id(0);
///         const float x = input[i];
///         output[i] = x * x;
///     }
/// );
///
/// // create and build square program
/// program square_program = program::build_with_source(source, context);
///
/// // create square kernel
/// kernel square_kernel(square_program, "square");
/// \endcode
#ifdef BOOST_COMPUTE_DOXYGEN_INVOKED
#define BOOST_COMPUTE_STRINGIZE_SOURCE(source)
#else
#define BOOST_COMPUTE_STRINGIZE_SOURCE(...) #__VA_ARGS__
#endif

#endif // BOOST_COMPUTE_UTILITY_SOURCE_HPP

/* source.hpp
0+eoxjWkKmtm7gKVBf7VOjnq64F0rk8RB2NL349/z/BPeYLw5ttCvGW59hvo/KWThK8szfSH9OeSMprxnTOOVh94S0938/QHALw90908qR06hwTv9hCePrqDv6lXT3Xz6EslJweXVB9ofMv6u6Xvr/5m4MwGWdhI1udop2Qdb/PcjFqczYtgDeI659k8NLaFhiPCFqcntTYnm8ECzTm2PCX1pr6z8jSnT1Bzkb0Tsl7UGcz85oUL8ku/PK/Ov/4t+3B/TTPjJ1Fw+szpmfrMcyMK+8+71dlYHzYO556U2MhhE/PywCk/Vs8kZ4ICJ2wqju9KjVokz9Vnb2OHgfWNznXadC94H7A+92H8myWmsP0sLzjEU9gBE0PWZFuV2O9RdvWSsLKzUlmgOpH4Hy2cFromifTw1uF6gMKId3A4DxnG/Wdar45qKnUfubthft/XRi18fmFxdnMFPIwZBg+tUpNwv2RLF0eucTQP9ye3GrxeO0/3bLydJ33WafA2L5q5Qj89vo04uo1Ljp2rx3Q7P6vaOR0i9Bu6FEVbv8zbOsrxN/n7A0y3Tukb5dgYNXGUAzz4OgKP6ZZIiOvKFs5BKTQPd4C3GrxeO0//5TjyZPNeHgOP6ZZozJ/eNsnr1i+4eFds1hhv1MPMZJ/RwxwcdjRj3M6ndLworpz8vtetMgVB7U3XbazqFgmiguGPiGxBzXoCVZYT/i2HcWb6BWJriGHcHu7pvLgVHF6fJhnzazqf7+J3c3+3DVxWxwYdeZU2J4xrcBDfL8BhbcGkot0sjRN3eB2/v7lHuhM8u92weJvv0HR/bdhUHvrmM/Z3yBj33mfWQeChzGujJgb9MM5tk4PcSQIb7zgHJdC8xzDeGbwez8s9jvG8YJwDh+lfUjDOTW4jDvRp5wZ6PNzXY+t7Pt0e46DHI6aufPv7wXHk329/P8BD7nz7+8E5KIHf+n6A12vn6R7H23mCXsFjevXZ90NymF55rmATbo1ZUZ07jhvfv4/J/piF79EBVU99Y2BdVSj/r+Xv9zKdKxrKn2/pxDFQwX9cN68ZS3BnFBxWepCR7vWxDq7Bw3iyDTxWP6Ca71Vut7ngIN3v7wCH1aOm4luVj0ser0u7NOgn453jDbWt7vHmz1Q+1k9ilGFl1MRQXsb5HTisf8RmOS9vsTloibE53kxuNXg9npd/Mqw7Ly+NgcP7RTwYb45sk5xh/SI2bHa3Wt/yui4rp3zgb3nTL+79iOqlbzvd1S+eMvXcp7F+0YG3+0U3z+oX4PC6AJn3izYXPEoX/QK8XitdbXMDDqs/cHm/ABd1hJR5v3iK16VdGqwrb7XXlfOrkqjyqDlrtT3Po/MjNhHAnPDGOySX9nw1nbae2Z5Fc3bzV6r3z62snp9dMbkS6r1NczZU27AjGvkCzoYJt9Ky945he221WzeNkzQL4wdtt0/odntHpc2UoccW4uxV+/DDyyjbuOQ8MrSMUvcS37jPMtJ69R9yDdmuRWWfi/bzO7J9NvsBzz7mss9vGcZjE2S0YXn0+3p82i0Cd2L763JZe3/F5IJHL1WqDSzcTz8wDh7vu+3IUUZ/Z4dMm480NnaBz/tpWwRl/e5uS6bNRX6W9oDL+rYtAlvxvcTH3ifS/IkKf/2+OtXMhR4C1x4nbNGBnxwls7K6+gVKW7UvYC8/Qhh2MujEaHAXZj/D8L4n1pJPYIzBzhYdx8jaXu9tGPtgbyUe8kzdQT/bN7LexHXl8Q6OfuDUXJfW1piQR16a1/7932cxvmWbNGdQfVV1v77nB22r/i/sT/XdNTd3+O4OwuskD9Se1D0eNuNXTp6Tnoxv4rvN/sOTA2961OD1WjzUyy3iob0=
*/