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
BMiCcSNxYKYIpuLFt3lefBsMW0D99S8bxPWoHw2AtJ2A1HtBmFI6QEzLkmgvzcgoG3jlxmYIMiiIIJjydlaFHfMXNsGOyxY2xY74ZIkdKLbD0GX9zMCQJKO8gSBdFjZBkNYSogsQxLHiAZYzcg7dKkA/bYok1dMVkvyyxkCSnNlBBNlyV4ywTk/aXOXqbLU40cW4LhJBMCPOQLX+8yMNAVdqvWPlTkOx4dUwjzIOC4V6Qrznxc/BxtSbi9RXLlL69KA2rEHf4xAy8DUb/13+lP+j80L4lcPNz7PYkPz65NPEP+ht0CuvfGl4rfhoVzVN0Ssw4C3TK+MVsMG0G/EfZaXJAS/DBm0M4G4vI3VscPl/Lywytb3aIe0YjE/0U/2E+zv6+yTLOPAC8ZOYxsetvJTd1s2UiOVi8V3aMb3kkNwFB7Cw5nt2GX/t3GQho8aAzp0mGGCajAo7kNXhPIydI1z2gKNwuVBbfh3u02lmKthfMNSB2Inze1vgxE/EAMGlAUatVqKOtDUp/UBhyDUSQ66fGurzcw0YdvrbZyLv3sKa88fiZjGW0Xb+jAwaUAkT+JpCaRCJft6CdEfPRv3zDRF9+7xx316+obfFL01ezf4V0p9izSaLUVlfVCb4j8b1XYD6Ioz67heroScnS8kE4zsOlyvkWNGB1eWZ1e2dwr5h7I3rk6IE1NmK8zc9GpB/ASTKGPLPJu1HATbS93nxpSdq+4B/AfwDrHl12zBcz5wjvBZU+XNWySDlevHMk7T5hnpy80FsY+oneyDTpQLmObXtLo3zwK+bxevl7YATSHQh7XQnSz3WzcaSGXqsTm1xTYrxKnOUQegBzGn0B6ECoXFMfYOwLo/qGAysr1VTqv3faWeh9n+PIH24+vPm9OOdkPwjMaeJfxKS/+Cg5vkPhOTf0xX5ofxaPiEW9TBPz68vMk/PGvD23CgedYYlle41jBPl3juYZRyhb+kXt1H+BFghz9BnFb1Zx2N0CY/RBSBG/mt4kN7IJzaHhE9InqpZ+vxaSUz2hRGf3mHrm0D0nAWbSLhoFOuOOoVvNJelQ/JDHnHGpkXjZEQXpZ3TYH0YuABQDhIyHpnXDhA/ucFylR1Pmv5MJ5OU3YjewUbhiwOycbqYlgRs8kBxzU9+26ul2T2gyxgo6ZcTuyUaT6VHeKMDvtsRC17Qh0mCPqQI+vDTub1FOyk4qnHjgA2+oDHoXFPC9eKkUMJlaS0IV1SWQbjoFr9AlB1HwnUK0F5YktfkIi15PVJeQwr6E27HBh/hahPwDSS9atqfsGB/6tmfwgUkLlstqpI7UUnQX0Hj+kj/Ioz67hdTrxcMlPSqPyV9cjkwxm6sc5lR56BJgl41rc9ReDSEXs0gvWoHyOT1c7+ZXiUklwH804lNydVjTcgVqFUvMCskVsmKWLGLbq0aJxOJFN35DwAESPhTUo6dyncaE1sgVjdEglh1JqFPo+0/wIQpHUD1T9EA0mZ8JSnWpeAgCySmWnImC4dlzsBa4vEqvSHwBpNdqbpjZc+GICvEuHTYCQxOR6aIBj3cKRp3DgGwMcz9ZG69BIk9CzNDsaeilWCMntn4P/5nxMNu8lTw/s6G11ThcewItVJgUlPoj3ioft4pLmG94ZnvKa9Eho5EhqoQZJgVIaTeDO6MPSHe4QMUKkkm0JOy3n+QDFlTPc4uvSXNsJN5mgD2yh+J6tuz3l7SkduC2lhPQR4c66UysY943OWUa9sX1bJlLjDFIeHS+rGVpyDV4uPNQr8ZXCbWuwOTW4tkm8efKoQSOaa7vBu/z5eHZ9a3Jcep88Np94LB1Kzi6Q2oAUmzfk2iaQ50HoY3boKc4JGc4OoQw50=
*/