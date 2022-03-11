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
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
*/