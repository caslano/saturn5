//  boost cxx11_char_types.hpp  --------------------------------------------------------//

//  Copyright Beman Dawes 2011

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//--------------------------------------------------------------------------------------//
//                                                                                      //
//  The purpose of this header is to emulate the C++11 char16_t and char32_t            //
//  character and string types so that they can be used in both C++11 and C++03         //
//  programs.                                                                           //
//                                                                                      //
//  The emulation names use char16/char32 rather than char16_t/char32_t to avoid use    //
//  of names that are keywords in C++11.                                                //
//                                                                                      //
//  The emulation names are placed in namespace boost, as is usual for Boost C++11      //
//  emulation names such as those in header <boost/cstdint.hpp>.                        //
//                                                                                      //
//  An alternative would would have been to place the C++11 emulation names at global   //
//  scope, and put the C++11 string types in namespace std. That is the approach taken  //
//  by Microsoft Visual Studio 2010, but is controversion with some Boost users and     //
//  developers, and runs counter to usual Boost practice.                               //
//                                                                                      //
//  Thanks to Mathias Gaunard and others for discussions leading to the final form      //
//  of these typedefs.                                                                  //
//                                                                                      //
//   Boost               C++11            C++03                                         //
//   ----------------    --------------   --------------------------------              //
//   boost::char16       char16_t         uint16_t                                      //
//   boost::char32       char32_t         uint32_t                                      //
//   boost::u16string    std::u16string   std::basic_string<boost::char16>              //
//   boost::u32string    std::u32string   std::basic_string<boost::char32>              //
//                                                                                      //
//   Uses the typedefs provided by Microsoft Visual C++ 2010 if present                 //
//                                                                                      //
//   Thanks to Mathias Gaunard and others for discussions leading to the final form     //
//   of these typedefs.                                                                 //
//                                                                                      //
//--------------------------------------------------------------------------------------//

#if !defined(BOOST_CXX11_CHAR_TYPES_HPP)
# define BOOST_CXX11_CHAR_TYPES_HPP

# include <boost/config.hpp>
# include <boost/cstdint.hpp>
# include <string>

namespace boost
{

# if defined(BOOST_NO_CXX11_CHAR16_T) && (!defined(_MSC_VER) || _MSC_VER < 1600)  // 1600 == VC++10
    typedef boost::uint_least16_t             char16;
    typedef std::basic_string<boost::char16>  u16string;
# else
    typedef char16_t                          char16;
    typedef std::u16string                    u16string;
# endif

# if defined(BOOST_NO_CXX11_CHAR32_T) && (!defined(_MSC_VER) || _MSC_VER < 1600)  // 1600 == VC++10
    typedef  boost::uint_least32_t            char32;
    typedef std::basic_string<boost::char32>  u32string;
# else
    typedef char32_t                          char32;
    typedef std::u32string                    u32string;
# endif

}  // namespace boost

#endif  // !defined(BOOST_CXX11_CHAR_TYPES_HPP)

/* cxx11_char_types.hpp
zubXrhNO6pk0yMqzm34AIXddGgvpHB7GYnPQE/PUCQ1mKLET0SX0vZBY3U38aQER7UijjOeBh4zQDohk+2jmOsw9mwcCWWieskhsKgy80jWZvDb4HgoDO10d+voOXJuhE9bhQ994o70z4EN3NOoOjSvQzqE7vKLBfu4Pz9D1DjILgN/PAh4i8wCc6cx1uJ3wfL5Ps/a9M7b5GIz+2x4jwZh+pTO6qzVRN2fK4Q6lgfAhbEZ0F/EwAqRDQs9y5zaHV+LZw4yHjclPZTCSFKEppOZ4UW1qYsRKcu3PmjMGSUK7zTEJRFPYk6El1wIeoW+gdVIDoL/s/gvy5x7GSy1V4E33fY+dq0NjwDQ21IanA039uUZKTLiJzgxhjHYsIyzUWavNHGMksouwseVFLoGQS2xKnItjx+O2FM49zDufF/eMIYQxAftYo9yRPdHfDS9HGlNLBClYlWvfQ25ofPJ+tF8ePbjdx+ERMwHC5aBrnGujt0zXBt1RX8dH3A15Jca7oabvE4IwaWJZUkdacOj2fymxvHdV5CjD7i58l0fbb5MYZR74gL3vpGMvG6wkTIFXaZCSHKc9TReq8yBAF+/kvGv7mB48P4I7P/hEk1Gkt5lrRhgM051FDBVjMVlE9iA3UujPAyuL/hgFyWDs
*/