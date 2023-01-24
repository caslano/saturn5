///////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MP_DIGITS_HPP
#define BOOST_MP_DIGITS_HPP

namespace boost { namespace multiprecision { namespace detail {

inline unsigned long digits10_2_2(unsigned long d10)
{
   return (d10 * 1000uL) / 301uL + ((d10 * 1000uL) % 301 ? 2u : 1u);
}

inline unsigned long digits2_2_10(unsigned long d2)
{
   return (d2 * 301uL) / 1000uL;
}

}}} // namespace boost::multiprecision::detail

#endif

/* digits.hpp
kwHO+fdzbrsHOKfIw+gIvENdjb+a+9fVQHR7UGL06HJWc637SNQh3OfK/oh0SZYT6ZhKwrMBTVEZwSGt4bP/3GSX1DceQLX0nxgWJ93PDsbxD/Bv+sP0us7itC2/vSX/2OBnQ6Uda1Qupwt/8Bhd/JATfjT3DcbQSjs3ODQxqLMovKiQCgxrHA7rggdEPCTOAOpgenqHePqAK3tHo0/3wKe/FV8y/n49PixaD+b7fV4omA+ULc191XPoI1rkhXs7PnEaTBF7gPZConZf58CFzeJM2qg5eqVDBABP/Y6j3YDrjzyru4arLV6y1k8o0ub5+glFaKYPDClh7+jAItYSWUFpQeLJiHbFDj5bbW9G4YkTDj0dlv+DnAkVDeR6/mtuk/nI8leH5/dYOl8QbyjNM12pn+b5ytXNsXWPcISneTbXZnAMrzfCuub5D5/DAVZGco7C8PIY2ObF5xocSL1sITvseno0GkMDsNo+p0lY9XuuodxtN4Digit09fcXrOy6IEbVvuFR1QPP3+2NZcGeEgytF406k0jMF80xEzMsD78EPK4y6Pn0HhM9t7YSPWtDiJ63eYmeL0zU6fnpbw16vmCVQc8pa8Lo+ZpnzTnggJ61Gm1QiW+UHOSNIeVzddlqq1SjDS0xSLjds/quQjgJh9La9rXpeyGiwibQMXazAbep1YlLQvEndfLsdStpEldLn7E3UU8lk1PRndif
*/