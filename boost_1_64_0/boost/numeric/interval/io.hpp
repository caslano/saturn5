/* Boost interval/io.hpp header file
 *
 * This file is only meant to provide a quick
 * implementation of the output operator. It is
 * provided for test programs that aren't even
 * interested in the precision of the results.
 * A real progam should define its own operators
 * and never include this header.
 *
 * Copyright 2003 Guillaume Melquiond
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_IO_HPP
#define BOOST_NUMERIC_INTERVAL_IO_HPP

#include <boost/numeric/interval/interval.hpp>
#include <boost/numeric/interval/utility.hpp>
#include <ostream>

namespace boost {
namespace numeric {

template<class CharType, class CharTraits, class T, class Policies>
std::basic_ostream<CharType, CharTraits> &operator<<
  (std::basic_ostream<CharType, CharTraits> &stream,
   interval<T, Policies> const &value)
{
  if (empty(value))
    return stream << "[]";
  else
    return stream << '[' << lower(value) << ',' << upper(value) << ']';
}

} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_IO_HPP

/* io.hpp
MzTMVNbytSfGMg4wM2EuhlF3uHfAdIWdcg2/yzu6Mj7Ly93W8nwN08icGBPImpWtzNkXB4/5XCvK+4x1sjvy3ANzFOa9zpd7jsZDeww9H+6vz/oJk3O236g015gnTOZE+jvHUlwrMNmXc2GPRrC2whyEOfS69JZ7DsxKWEFBYDvGDybz02T61oqMkdLPV91NMllbPZRzQc6PgVwrSl/2uoRN43pQ2t1Imdqe+5FiXWvcYtzzYXrCvuZFv+RaUdplFFTdzDh4au/FzXo+MeFagWlkfn4s/AbhDTOVtefydY6hEsxCmPnPZrzLhMDkXJtOOJDFO4LSznhmpblcKzAZ90NPin1iHJR2hzx6WfBeBXMTVvbr2xDOtdKu971pQ7l3KP0c7XSSte4FzFLYhWIDR7L2KP182zX3MufTS7vdubb2/F7uC5NxaJwYP4BnU5iJsKwtHr7Ma5gcQ8TrPO5VLZV25c9p3nCuYUbCKqV/tuU9QGn3qEvvWbyPKe0yisWwL3Ewb2Fn2jQ6zdqjtCsa0LYq93dYSRm/b1t2cK6VdpOPnDNlXsOKCRuRP1HDGlJMT8dH2KjPLfyZgzD5m+4lcuy4p8Lk2O+8W3WdeypMxi+6gT77Gav85uf1PbpxXmAyJ5xPV0pnLYfZCGvYsWMFnpdgxsIOtr2VyHqt2PhSBrt5T4VZC9u2tyCB5x6l3eCdBsms5TBDYTktNOM410q7SzVGMQ46xbXn5Va/nnOZ8zDZ7pW/LfvpCZPvWx/Z5SzXg9Lu65bbzLNKMHOZS52ecI3VV9rd3ZOxhOsBZir78sLeibFV2hWdVmw29wCYjG2d9zlGvJMUV+6GlR7znpqgtOvUpYM56xLMStbdB8viGXel3cvPMZUZd5jMpQ2fum5izVLaxfz8VppxV9o9+TzPimdapd29vufs+X3CW3v/u/jUNJzxg8l2V+sGRPNMC5Pz0lu/ZCZjpLTrcd21I2MEsxHW9367haxLMD1hg3TDmjNGMLnercLjHLjGlHaaS0n1GAeYpzDbVz1/8m6h9HN11Wp7+H0C5iYs0MnpPNeKMmfr3hw34DdHH+2adaHslzieX2AaYWm13xVnzYK5yfF51V7DsSvtLn9bfZHneZiclyrlupXhWVGxqm3j9jKXYGZyHf1O4feJPKXdl5nmwzm+EtpzdnBhHGuIK0y2i11VuTPHp7SrqeNahzUZVlpYo+/dBvGcBTMWNmJqGtstU9pN936Vzvgp7cIXZf3mvQPmJyzr92Anjq+k9j59PKTLIn5fgskY3Utr6s19Gibns8KRGiN4f4DJedk3YZA960tJ5TvKjmUeHLvSbr/TAtaQfYqNOuXanPGDmQvrYDekJHNXafftWkmuaU9f7Tzr7FLRjGcUmK8w3c0TmrG2+ir/eeijDfdz31TaFT26mvvtRpi1sF95K4awDirtjnvY2HEfg9nKuNfXL8d65qf9370a8erIe9YsmLuww5a3Q1mXYCWFDaqhW/j9xU/JpaX7TRgjpd3gjrlTOQblfd5xoyewXivt0icPqM8cLKV9RmmxrTPj7gorJSzx3KlHHANMjt3mk44X80xpty7FeyTPbjBTYU98d2VzDDAZo4CY6COsITAb2c9ZRzIZI5idsGOTVvDMbuSvnWcVtjwJ5BqDyfe9rd5kEXNQadesezzPBcEw+T6rrzVCeBaGmQmb2T/Fh7UVJsdwdtUXzucUpV3DXodZXxbBvIRZfO3nyzlT+jnLsTJrQTZM5pJh8eM8n+Uo7T7di1jBczLMUdiamXsqM+cDtPtZ/upo3kVtYTK2u3s25L3DW2n363bv7zyDwZxlXtetcZP1GuYjc8J+40yuFVhZYZM=
*/