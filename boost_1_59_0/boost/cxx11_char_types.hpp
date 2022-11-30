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
fm9SfrwwBAUvOHxP1BEvT8OtP54LTMrKUoQYyxONeMphfBNZmVMR4tm7cl32c/TK3UII1p7rPK0+1zkj8Fzn7/Bq24DnOn/xJpQ97LlOydHtN0j53Un53fxLOYrQzbQY4aNt8UzlfDt202ko3JmVxQDoGcR7eL2yiamofwWzdGda+etkRxwGIp9KcvRaHt3KCh4bmtCH703J1b32czUzQwp/Kxbe7q0cTTrxK2+f/Rxf3BKFJRdbTP4rneTD/QMLH3jTeYYi9EIWXSG5oCxAVlZSfpxgzMryRypCHJVY7c3JwprR+zJQgxzymKTgk4ndZJOEB0m9eZ7CjsBTo480XOCpUXqnvA6gYfrwOLoQnYo8qP/JSehB6P74ix64hD0Vi12G9ofY0P4QG+wPcdgfoml/sAb7Qyz2B+gMeOdlY830OqUL9iOVU0N7wTP7z+8FP2s6j5Bt7hP8qx7jDGcJl0X63qVsBCmF1cG+EEsJOhwlfrOQvKO2MfplkawGjWzBF1qdj1yMbHc2INniKdkGEOwLeqIVe1GCMQ4FizW8ZLfOSG7Elz7Xmci11DaTq6htJaOpHU2GUTuGRKJ9K1F2oTeOnKZ2PPmG2pPIl9SeTD6h9hTyPrWnkneoHUtaqJ1I3qD2dLILD4T2pyjrUshLNGg2eZ7aGeQpas8lj1PbSTZTexGpp3Yu2UDtxYSn9jJSSu0CUkDtYrKY2qVkEbXLyFxq8/T4SllXRaZTewOZqhZhJ66wybUYurMenWOpswGdVupEyUQSQZ1b0HkWn7rdiVeXyDfUiZ83SQd1PoXOD6jzGXQeps7n0dlEndvQuZs6qUaBP1FnIzqfo05UJkB+QZ146Eg2UyeKUdPjK1pkVCZAKmgE6jggxdSJD+iRfOo8ic6F1Imch6RTZwc6p1MnQefN1NlJ60+dVNvAWOpE1S/ESp34IgKJoE58j4Wc3YFO+mDgN9SJK0nSQZ34uhf5gDpxkiWHd6hFRs1bpJFGoMgU2UGd0ej8I3XGoPO31BmLzsepMw6dEnXGo7OGOiehs4I68RVoUkydU9CZT51T0bmQOhPRmU6d09E5nTpT0Hkzdc5G57XUmYHOsVqR56JvKI1wolNPnShsS07jGe/OXHR2UudidH5KncvQ+d7LiCTmArrZ+Tw50h5BFVZEOcmfX8YdJ76fPVkNeYqFmOwRU9SQTSxkij0iVw2poiHrptqnLaYhLlKEIRfIzVKPOlhgHWOPmKomtjN0VntEohpyHQuJtkdMV0OuYCEx9ogUNSSChcTaI2arIaf+TkPi7BEZasinLCTeHjFXDXmHhSTaI5apIXtYyHR7RIEa8iILSbFHFKshv2Qhs+0RpWrIIywkwx5RpoYINGTdXPs0XiXBCgwJSr2g5gNjQuvYxtNHJrbK+6/hgK3bW8sHy968x2VOMsY33YDbUDfn9wWJJmei5NGBoOTR/Gc0ySPfbxWUPEqVs1F6LKJZx/k/lb+tvQP2UGnzhdNuhe9M+G6TvsE4emZ9Y1AOSceRIYhDlUPaHSKHFP6HTaY+OwB/crbZM4fbpB+Msvz7dJYXjfH+b6FFYf0D4aJXtymSRjXrLFuN8RVfy15xf5wmccHqsyjeiMIxp1FlMSdMl/W364QbIdG1ty/XCdcM7uDHeYn19lS9MAYCh9++3CBYRa9R3Gcc3CEckxVbY9OWsY1H28VGXdPpfThX8jGb9FAWQPMlFAASnTy9Dz8Q888XyRCB+A9DaDPifxPw7xG9en9DSP1y8JOUnGmVq02yVz5qaLb3rzPZey0PPQPo687UAq7yWE0yZmSOS/zSIn5hsfcvWSpE+H5xJWztW2hdor0+vfiZQTxjKr/u1AtK/BONI2Bt2/IqRoo+Y7lZbDcYWpV49/HhsEiN9xyB6C1gL0K7A8Ks4JgKZuLRTZENUZvSdA3puk1pekDbkK4Xmw1iC0V+KIAcaB6ApVA6sVkvtugR6ncBqC0MBhoFC9iiw9iGUBy7wHoezFNgHgezGUw9mA1geKzD7J92SLMf7QCbgE3A7gS7E+wusLvA7ga7G+xesHvB7gO7z2PE10g5Q5ehV6OGgpVuA9MBphdDHKYlS2FvhyUMdbPaqyHY50IpAuTQYD38zX2eDUl9ahvEB9tg6A+nXuiDfBdHY76nPwBKm6NpfbU2OcPaJAHbZNlI2iYIvKUM3I+DeR3MpjTDxKMN6Qbxa0q9byj1/haCGsumwgTb6muApK3QEAK5JQQOgIJt9rVB/AaLbHnIBZw6HLcVrBgwcWAmgZkCJhFMCpisaNo2sUDrWLBjwI4BOxrsaLCtYFvBNoNtBtsEtglsI9jG8LZhNCqFXx5MPZgno0PaJs0ApQ5pC+oPb4fQsLC2+0/xE1mhjMSsMZJvPWlKCCdhi2x6HxZVvOAa+UAT1flCNb5Y8UqrPLQWODB+HPWP8zj6qMyJCX7Z8tbdKBiudvShghfLrkzzRK+KmXS9To9XTSWjyWlw5vVEPANo9PzwEl3xKI5LKTGQzifpEhpcPfVhL1XLmeZnEVrONk3MNp8+OrF1yFvSUAwJ+5SLr6GNIpt/Fbz/DE56/zlMc+VLQZU7JXpyuD58Z0qlaPmxbI/1rd1hrrCQJIqSKTTJb7L8JdPskr+Fjb8uzdYo9rdXjnSVmEJ1CQERbhGTUY0Qx8e6iB/PMiDsGJVi5SMDulGGUvFiCNBhwHlqRYUh+PxIDKxE86gOXTNkORS/OBe/pKCuDX9mjn8KLYYrrILbNXVGmi6jFBdZycrAj4PyrjvoIjnoJ8t+GawYzlNkPgQEdXmehQbJkyL9n5HbwsI/Y+Fyi/+t0P6X5crJRimy4twrqBoJUhPDcfmaUoGB8p+3UNHUjD6U/3yAyn9aZeekhbIzfiGJRi6y33Se+CcKtc6Ot2Y7S/qLl0Em4bKsTs/seCPTjQBQk1CWFaVYFf52cUP8ZIWPtPPxk9fd4Jm6Tjb/XZobb0Yx1g1/N3LCFUyOdfbfTWQOpzqWgsO/C4utajtQBVltjQUy9detN2IZBKu8wCwvNCctMAkRtGpNWQte2w6d0z9EdciY110maZZRus+cvcCZm5efd88+I6ccYS1eZPmmcUEWPlljgW6yUd4nfrbRS6L421TdCEWWjTowqVb8icOfKfiTgj9O/FmGP2UeCafUDOGI+xh/m7zPS4y8xW8APoDpPXOsGUKP+JmFj5X32U54v9LzJmmMZ47xTqEXeDUf2TAmNUM4e09uk9x2+oTYZE1419a4UH4XmD7E6VLvFM56/ZgGMBnvEnrv9mUrmnqlwcqol6HPbcWZPEzZHQwmdrJzcMM99qEo31AB1URhxm/FL8Zr4h1R3i8imQjHreL0KQo/RXumfFzCQd46hzfNEUZmlXT7TVkl3/sNWSU9yqjd2MWjRHMkrFv8o8iT/xEQmXgBnBI+ej1A65kqeRFD6gEARU4KAmkoiwiTPl2mwqQE8X7whKL4/0GlT1U5DLxp3g4FN0HB35aN2ntPJebibVT+dQsMGVj54Huz9OXZ4KOzqm4d24mkJSZhWslgukmlCpLAP+a8914Fg5TfoaSZtDO3KZA2KR8WdBS3pmuaYvbMTsR0qOMIT0knQxmabCegGJBJN343DqfI+ZIlntk6RDBQDfMCMbkROnK/EEEiR8CAQw+eFTLZiQNNJRyKEcNUkGlaAMlfZwJNn6FsRNjUwh6hmvs2tFHgEaox5IPHA00xzxxHUfqSdeozVK/TyAk4Gj/dpuOvwKNYfIQKp9kBj1BBDH0Br0Qvtn9zz5AmCNZeonp/q8IURvNmcpC6Ay9RrThEWSO+RDUYncGXqPCsVX2JSq++RJVwUJpndCvaU1TcQTpl4VNU89hTVL5kBQ/Y/42nqEZlIdNcQJr2KUrgLaobMN98U5EU4x+H4qx9mJ18jgbl95GGt7R88U2qIQGy+aPkpmvQMeBRquAFsRy52mo/JQy3n1s3lF390ksxMIgeZB6DaFKofvmN60aS1Me03dCJn9PdEMwzMXgitVvQ7o9Z3HhGAu0c/QqqCCuye9fdaj/FWwD9kJwsF/lnIy0o6fm5dquL+BGXermLnVhRnUKQ6lr7uco4cvDnuH/CXAvBhXBu9RKYD3VnNESqN9ZaqHJNeolsOtJchaFKWDPNC7JyXNgfoxdkSflmekUMjy8hYXRSvtniLqHNZLIf5PdIOv8rbGoTex+wuFFbjv2UpR5VwNnPWR6+D2ysypWsKr57NL4XuAMWIl3+U3ogF62OnZ5U+hbYehPHxytzjFVD5OENekWH2mrNlr14T2EZVDFPPXaPbFIiwy5JXVZAB28ZSju24a8qoPMM/e2iv+cL6FCBHiag832Feklq8c8C66Xvt+BHI3oPFT8a4d1Y7ZLUoCFBAR0PHu3/DwjohIvnUDGkHXidMiikc/f5Qjo3hwvpBK5gUTU19OIru4ZlClzDWiK5MdjebKn/Br9pR+Wh4E7rIHoRK/l6dhGL3i+WqLCERkZGXkZYRnB6Y/9RvIjFRHfUi1jNfHxGhnoR6356rQrBfUVBMRvf3QG3zjdvUJjgzoxAlN5nG3RRwR33CYsUHcSoCu7o6b2pCwrufElvGtFb174TpotK7iDe1+mtKEoC33bTRSV3nqBYzpfcqTaFiYOsQbALS+7QO1Oq5E56wB3ns5suL7lzhelykjvfq5I7/1Ild/6pSu58pEru/EOV3Hlbldx5MwophH2DC4ju4Ihjojt7/kGnjRDRHRyHqmCOoQ9vCYeI7jxBRXdCID49ByVaESK685UOb1VUape4TnHorcM5URXdydNEdx65pOiOepP+IhI8Fo8jXHbnmf8Z2Z0X8GPXiUvL7lRoF7MOhcjuXKsw2R1UyPDvye7kn6Vf+pnszvNqJpeX3bkuXHYHkk9nF6+m/SjZnQ569Yr2Fl/bQOGdL/8GXcWHStDo1atO2uRtOvXq1V+0q1e3qMI7IVevHgsK7zCGeHHBnXeOsqtXEy4vuKNRxYdvvF1GcOc3AGj4WJ7VK2f1+d7S/ZcEd1btDBHcQZb+nxfcoQPyv09wh6K7lOCOBnB5wZ1heNuKlYfKCKg3rfarQjuPazetcM/YQifuiwjt8FRoBwEuLrTjDLlo5fr/itDObtTHcwGhHSTF5YV2VgSvWOWeJ7STMif4XtgBfC9Mk9qhTOqiUjtU81qY1A4Oof8hqZ3g7IFSO8/Qez9hUjsIcCGpnce8P0JqxxmG79+X2vka3++6hNTOMC/Ol5eU2vHDCvtHSu08131eaZGP0PtT6CCzfwkAL9Cw86V2LCHyOq/TetNZHu9PoSPK4v5n9wWXwgOkeJ5ayR4Iu2rCTG5s3EwuE8wfwHwPRnf1TC4dzHqICy7qqUoo8R1cekeTT92BpfcD4BzS4p8Na2yRT3SRm04oikvuJTONyC/H7sXZYzXOD/T+cARg8I+Q02Khiw9xklw8OC2K5fLEIjMXoguuxFzcikcR7bAGQq0XsAKmHwnVJ4buDWZ/rp6elPqH4hofyIB4HB2kExI2uUjtE9gu9NWh2xQlTEsrfRvlOH2k6X2EUjO2FhPMeCWkV1WCjCSn6kNVgTzLhakCGUGOB6LJanD6P7yoCpBIqgLkcBb52ddquVAFSKRRx9+cRSwY5lRGNbKjkyGq+hRHBz7a0MFRzcBjyMZ6bMUOyUTyg6W6gF4Qf42mF+TA14Ha5cjN9KTO4vYi2FHx043er6L4Qn+k59cQwBVZ1kaCmWeFH1cc/CzB47ooMPPxBC8HT/CWQtDaohT4WeOEn3XL4KemDCJW4qneWjzVq8RTvY1lHnpjwUPfF7hT2Aqjao581PsVKpq7IjS/jVGedVbPRuudwjfipxY+Xvai4rih8mjpCs86o2ejcQ6w3FZUODcIv/mkpc8RTucuWZrf9CrOMglHEt5aIO/TAEY3XEEBvCQMRYZwKs+HmmwoHajuKwP8LwYEKcVzE1BV6gag9lY8HmK00k6KeDNu/6KgYRKtmjLs4IBwkVx8NgrhnM/Ss7V+nTCopxYvaOiEIWK/XojtSZmt40eX6MkNAFqig7ERj2ny7C14xh7TyZodsUOzD2bNzu46uchaPx5fDNRfl9c8e4qRc0PZcsjDD2H+MAL0IV9soRub7odu/MyGQDceS2Y/xM4G4x8K7c5Y0jDNNuNUsB/qAt36P+p+nGabV/0h3RqPRc1ZVHQNx53fQl4MYLxQj03aoPXYKzoDPTZAaTnNvE3kr9pm4q/Ea0DjH4c1WZH59DkUrMuTIvERtDTjBT9Y0++5WXKmdcgBPhMxVZt3pf797p1x+J3p2sEdm6L4nwxu5CeKzTqxRXf7l+WRt39eqdd/cXsLuJrA1Xx7O7SkTycctR24vZ0fhJsGpVx/+gPZe88FvmfRo/+58dYhrXh6LgxCVYenP91n5bJOf6qK0RXERxuY61PDu/do4m1hf8o1jwMfYAiRBh5HtDNUIvA63DEHjmvUo7ILPeFoFWLILbUBfnlwI+WXvl9QqlPZNXsTP8Z+CtjqkCDY8wzMXx72fmOyEvZ8Y4QBn7PBkzVHOztLcpIv6uhkKvfaT/HTwp9uNHvo64w/qcXOH/JqoxpuoeFyy4DXGfF6Yki9Ryihx1T491/9Xv8l7DYu9r2+7JYLf6+vv5l+G669hX2vN6L9OIQ1gum4+Ud+r0fkl/9ej1AX/16v4lgJ1iIwc8HMBjMdzFQwk8HEYx3+W77XU2ooWOkGMI+D2YYh/z//Xm+eGvhe/7rtot/rrTbaJgi8JQ7cs8GU2i7zvR6hf9z3eor33/per+JuhDK0gjkCpg1MOxgCpguMYerM/6bv9YxGsfAbD2YqmIypIW3zX/5er3EYfD8qR2MxwF8cVmAcxx4MMI77HmSMo0rOpMwFZv0xsGQcRf4chElXYbLwruZGYCH21kqDlBnkJCrTgVEPfMcJjIcYdqpsxd3DxyLvMAHvaIYV3FBkHiUcOfqgxj0uwTxuC2MeFCLfN5VT35lRpuH7CIGXD/TKkZIxZGchztmQweR2doje+UnoIXq+7wmP6m/RlUJC37CI0GdrXPK3LZEYTnpgPdzjMOnwBpgX16Jy8xJU/hsCi5Lh35JBgIClOQ9C7LT66Xf0hb+hR3j0dQay/RfM88WBpp6I56EKujeehN+9iEKYLA6lQXjZoc8pvwOzLo/FKYTxU2xfA7vFaQhMlv4WkOTgJxIJClocD6sHlKCXhC7ynFGtkVblMm0dJSsLWnQNiO4dY7jyOag3+RjAtBq/03+hGuOnTe+gBWLjICf5/gN8FCFvbGNeSjgQ6VpLj1minGTX/Qre3jYpo16yqpMjbhWqcKmzowLWErOgaPRZhrJcxbnISV5T8PNKp2ySB0H/ci4gHxRiN8FXARShg2SsCLutAZuXNYBk/Brcs5xdjbkK19MdgpkG3bmGBg1VbxOwUiijnHg5OtI/Fl+JXbBIci6SF+RKzlx5gXGB5DSSw1B84tJIxnLKwo9ZthP4Lgp5oiowMG6swuWMv8pFfge5F0fr8ckiMuN5vMKQh+9bzSHLAZtSVuoiV6/BqkWL84yKlJYrO2Lz8qSaRfjN1eOwOmEouYodt+FtBvZcUwZbXsaqy8s2Fzm5iW5r8Zm4mZBvnq0R
*/