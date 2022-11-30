//  Boost compiler configuration selection header file

//  (C) Copyright John Maddock 2001 - 2003. 
//  (C) Copyright Jens Maurer 2001 - 2002. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


//  See http://www.boost.org for most recent version.

// locate which std lib we are using and define BOOST_STDLIB_CONFIG as needed:

// First, check if __has_include is available and <version> include can be located,
// otherwise include <cstddef> to determine if some version of STLport is in use as the std lib
// (do not rely on this header being included since users can short-circuit this header 
//  if they know whose std lib they are using.)
#if defined(__cplusplus) && defined(__has_include)
#  if __has_include(<version>)
// It should be safe to include `<version>` when it is present without checking
// the actual C++ language version as it consists solely of macro definitions.
// [version.syn] p1: The header <version> supplies implementation-dependent
// information about the C++ standard library (e.g., version number and release date).
#    include <version>
#  else
#    include <cstddef>
#  endif
#elif defined(__cplusplus)
#  include <cstddef>
#else
#  include <stddef.h>
#endif

#if defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)
// STLPort library; this _must_ come first, otherwise since
// STLport typically sits on top of some other library, we
// can end up detecting that first rather than STLport:
#  define BOOST_STDLIB_CONFIG "boost/config/stdlib/stlport.hpp"

#else

// If our std lib was not some version of STLport, and has not otherwise
// been detected, then include <utility> as it is about 
// the smallest of the std lib headers that includes real C++ stuff.
// Some std libs do not include their C++-related macros in <cstddef> 
// so this additional include makes sure we get those definitions.
// Note: do not rely on this header being included since users can short-circuit this 
// #include if they know whose std lib they are using.
#if !defined(__LIBCOMO__) && !defined(__STD_RWCOMPILER_H__) && !defined(_RWSTD_VER)\
   && !defined(_LIBCPP_VERSION) && !defined(__GLIBCPP__) && !defined(__GLIBCXX__)\
   && !defined(__STL_CONFIG_H) && !defined(__MSL_CPP__) && !defined(__IBMCPP__)\
   && !defined(MSIPL_COMPILE_H) && !defined(_YVALS) && !defined(_CPPLIB_VER)
#include <utility>
#endif

#if defined(__LIBCOMO__)
// Comeau STL:
#define BOOST_STDLIB_CONFIG "boost/config/stdlib/libcomo.hpp"

#elif defined(__STD_RWCOMPILER_H__) || defined(_RWSTD_VER)
// Rogue Wave library:
#  define BOOST_STDLIB_CONFIG "boost/config/stdlib/roguewave.hpp"

#elif defined(_LIBCPP_VERSION)
// libc++
#  define BOOST_STDLIB_CONFIG "boost/config/stdlib/libcpp.hpp"

#elif defined(__GLIBCPP__) || defined(__GLIBCXX__)
// GNU libstdc++ 3
#  define BOOST_STDLIB_CONFIG "boost/config/stdlib/libstdcpp3.hpp"

#elif defined(__STL_CONFIG_H)
// generic SGI STL
#  define BOOST_STDLIB_CONFIG "boost/config/stdlib/sgi.hpp"

#elif defined(__MSL_CPP__)
// MSL standard lib:
#  define BOOST_STDLIB_CONFIG "boost/config/stdlib/msl.hpp"

#elif defined(__IBMCPP__) && defined(__COMPILER_VER__) && defined(__MVS__)
// IBM z/OS XL C/C++
#  define BOOST_STDLIB_CONFIG "boost/config/stdlib/xlcpp_zos.hpp"

#elif defined(__IBMCPP__)
// take the default VACPP std lib
#  define BOOST_STDLIB_CONFIG "boost/config/stdlib/vacpp.hpp"

#elif defined(MSIPL_COMPILE_H)
// Modena C++ standard library
#  define BOOST_STDLIB_CONFIG "boost/config/stdlib/modena.hpp"

#elif (defined(_YVALS) && !defined(__IBMCPP__)) || defined(_CPPLIB_VER)
// Dinkumware Library (this has to appear after any possible replacement libraries):
#  define BOOST_STDLIB_CONFIG "boost/config/stdlib/dinkumware.hpp"

#elif defined (BOOST_ASSERT_CONFIG)
// this must come last - generate an error if we don't
// recognise the library:
#  error "Unknown standard library - please configure and report the results to boost.org"

#endif

#endif

#if 0
//
// This section allows dependency scanners to find all the files we *might* include:
//
#  include "boost/config/stdlib/stlport.hpp"
#  include "boost/config/stdlib/libcomo.hpp"
#  include "boost/config/stdlib/roguewave.hpp"
#  include "boost/config/stdlib/libcpp.hpp"
#  include "boost/config/stdlib/libstdcpp3.hpp"
#  include "boost/config/stdlib/sgi.hpp"
#  include "boost/config/stdlib/msl.hpp"
#  include "boost/config/stdlib/xlcpp_zos.hpp"
#  include "boost/config/stdlib/vacpp.hpp"
#  include "boost/config/stdlib/modena.hpp"
#  include "boost/config/stdlib/dinkumware.hpp"
#endif


/* select_stdlib_config.hpp
e1CcDAW77YyBX4U/MSIeMDaYe20UDOhwoCCi95o0nVGyHEngSpuyt87ITdfWIs8AHZDpDY+4e26ye5un+5aC+748no66e+HW65eCDCKI8zipO+WKt+Cxt6YhfH2Dd4Yh/M2Kt2WMd7v86r6NOYE0erBlj4wi6igPXE3i7PPTDYRDrlJgrg8k/LNn7r5krlEJfIMsPFwzPJg/TyzxS5MF8fK/FtkS3WCPrpRWuxJ0YwPSjM8Z40EfoRLdPRCoriZovBJPIdxww5zqfasxgiDeuo1V7Vk/1wjNpe7fICaLvYvYXBjYrhyVXJ8CxB3IHT/EHb4FPQ5/OgTa7UexAaamUvkNplg+T7sWHQthWWEL34HmvEtgn3yyBb55Qb75AVnCaj5G6VlF8dl6zFlIaef9ET5Jbb7Indlx9VnKpp6tPH2iVH2kHF9lIh9lZp/FCZ/FHPrGf3zEIFFT4uoEKJ1EzkV8pkTYKG3L0V0r/MSj+vmFJkDKwAnLABSIAacUueBVFZf4k//UpCVEZuLTwTjwy/nV+vdpTSJNmPaJDURSLI9GraeSLIe8yiHv4q13x2RpV151EpvC5EXupyLuwZ0VYZkq8NvNRnf95LudCPNXTvzhN35WYwXsogsM5zgKnaO5XH01RLHGibZ5G1JewzcJcFBLalERoJ+740DiE8ToBL5PkqeQMtK6A5+cd+zJuiuid34mW67nTJUQWRggQHebwtC6EyAO+A7h+WQRvu5/2P3NT/QfosdGLemnRdTPgIeaBc5f8WyfvEZGId5vS2XP75lS6e7fpK1/qyiNwqOSw6e2oVsCfLA9FFYCooX2nmZbMbXaGkGsmN7GBAiA0JKnWTX1KYIoeOcbBtz8ObrIkvJYtY8EaABbN9/vYY8liEJdmJKvaZc1qILdigbHaZ89yLjJfECVYvg0YMkBFQAAgP4A/wH5A/oH7A/4H4g/kH+g/kD/gfkD+wfuD/wfhD+If5D+IP9B+YP6B+0P+h+MP5h/sP5g/8H5g/sH7w/+H4I/hH+I/hD/IflD+ofsD/kfij+Uf6j+UP+h+UP7h+4P/R+GP4x/mP4w/2H5w/qH7Q/7H44/nH+4/nD/4fnD+4fvD/8fgT+Cf4T+CP8R+SP6R+yP+B+JP5J/pP5I/5H5I/tH7o/8H4U/in+U/ij/Ufmj+kftj/ofjT+af7T+aP/R+aP7R++P/h+DP4Z/jP4Y/zH5Y/rH7I/5H4s/ln+s/lj/sflj+8fuj/0fhz+Of5z+OP9x+eP6x+2P+x+PP55/vP54//H54/vH74//n8A/qKMjIikyE5BnPO+lmW/OBEr/ofnqmn54dOnUyNSM3AQa1mvVLl8XJiHXs2UlqzZnVwMAvCqjAHLSdayrFIbc9YopmcQDLcMVlW1GN5KvXOcagFxpgdGSbZNlgVKgoT7oytLDkFLu5v8wf+57sLV+Hr9Pbiv0vusfISbi/reD9sHBSMh1y/uZP+gdZNSk/m/yeXfHPY21A88g5SBDKEmKt5KwAaixgV0utSl6+4bpmavMvWfUuZpAC+1XfaHAc6LPrOiK3qxHlLs3M7uWD2Q39ztYoWn3azc0PFL8Ugm0j5BIyiGd/2sPwmcsKBHDRMmGrcGCLSR8sZyvPVivyX1J8WpjjDiiVxTp4/WT3zAsGfLGHtTro1VxiOHXj21RS96LJbGUuA08fNlYq7wj6COXElk00bNCZFx9UiXGQox2mpb0Ta9cSfXzLMqFEw1etShBptW5aLmnW8E8E0tT+NU1z8/iFrKTCHZMYlysd+6oI67bR2pzi1JZFrxQNh646z6BzTk44f3ML0zcEnNT65RN+7Sv+2wBlXz8fl3KUwt1LUKJWUPpBPoS5qqEsWtsTj3FJC/zQwNjvMKnhvPJtNwO47BRfevkCFG+8ebIuPrSy7SuxobXx9QGg0SgvkZzd7zFcY/ofXSJB7iY3CBqiLquNrP50sCOVt+0z1hInK7YdnfsZ+bBO3RD+3R1VTKxfyOZ0W/lXx1WygbCBKHvCv9t7Qv0rocbyV2Ko+ua3C8Bo1sHxdpt8T9o87W659fCi09fTCNdATLDcYB2wn4DTci6eKVNdv/9FwvosIivGZ/ghvjGf47lAca6wgBPCkyFtcpB/s5U1iutn4WiCIjwhWUmmLA53kQkthzpb5qgnOhggfIYTzpgRvP+rL29zmwUdLAULYjlOsb0m2oFjGAORh4xRIdDLk62HnLNZasGYY+Dg4m13c724JyMge2DI5GebkUIHr2VKnYUDtNik9DNoxH5CJJXzBXuj3i2RvV71ybe0Pc5BIkhoxFnXNgPOctri16yGif6d7pfXlo29YMfl2P+y8e4N7rGhlurHcuyGG9mmES2g87c/b+nizts9B2nPyl+BmliH0rVt1MP7hZpQr4gHXOTgsmjrcrdxOAF/ug7+XHWVYXQBa/gC3P+1msfdHMtr68wMPypo6I38WlcAAAs/9NjPR3zcIWy8Dj4l+zkKAe+PlzzztowG9U4TB4fiF2WgicISXJJqx8LdjFHXreXKbHs7U71w7imDbvW2mMnTD4ByuL4aypOLpdjPnOGviINny+8w47871aydx+9EYdjTpG7iq6ED35m2EbHvfgi2IXL7/5wGprwTItLIYYzx8Cb58UD5io+YAovd6cbawJXE45ywG97qPV0N5qqyhVyyAedU16ZsqEhAc9EuKgbPaGvYUOHPQPsS1GI5LtZDNjAVFTOspQYPCtHLvw8Qkq7iqIExEa+gXRrKqoKlJ5qg59bEXq+TaA1CZSVC/EdheniMuYtiJVInPYjVzebUo4BeJ+fsVxpIy36cGspllxqX6ShPSHiMqSuU7cMipRSA2LX1m6slUyWqsNDBDid/mdcsPF75A9hgDExuIFFBkHInvFiNvN8gM4/vJu7Q7SVnvF4GPqPlmA9ux3UHn9J81WkDglTLhuMWvzY4KEIYzqaqGHUIEZmkr7eYQh/NVaQfNCTRdJkRUdEQVmEaJI+/Dos5arNn6QofgPlYkRrcMefKByptnRjTceqUDLoWq1yi94Heehftpr9qkrbN1BCWNyiJMs53GDwptrP4NWU5s2kn0iTOK04kE+6xa5j+lx1cXGVMPXtUhBozY+bnKkYryr7rHy9ilV26e76bXA+P2S3RRWK5T2Y57OQ04tO9Q0305QPw9U+RusahNzZQcGZyf+pgjUFigkTqXjCfdSFVY67air95EKtz5sVM1dZI378X9k23mVROR0LH/LFjP+gZfXPMIVxV+m8avn8gL/idXpQVwdfpHpNz2w1V2AXn9YnArHcVbEFRiMf19HyjKqS8TOxuK3ujbKl+HRJJ3/vV/uC0uN+T7LvVMaUa5fY5w88+WsF6/KhRzNdU9LGrX6PLc+qlXt+Sl1U+DCGuKrXd3sUcBWA5wi6XruzcsalqJpRS/BHl/eu86UQw1UMdrHLQ67b+FQCjEyVYP5vqzTCGSHbJZNBegEI0/0vt2LTtf8XOQFcqpeAzLlKj8TYL5ro4Y/cBrJkAn3SJ+FrldN+r+i80yJLYbtPj93QA+0ytSybc2rYByyq8D2ctzH/kbY1O5cPRS8isZemvKuQgaIEysaFe1J2Lp9Qz/crEkgJj/RyY72j8IQ/vSCL5qiIoHvdgQyPitbjL3HUz/ddaxXHx7d95+eApoSnxOnFJ4aAzQ4CnEVN48OlmT2J6HYkgXmNU8vaFGTKySP32D/g2KKhM2f92REgdeyURvL9Cqo7/VN7/8sgwQJyNKgPn2P+7R/NmUp/aVzvdjBpQ098JAJoze8zPejPEymD/6bIOeU8UlemEjpmajeJ/P8tloXsP2qVMdz8g18N4dqXSX3jthNyw8xYjXczXgs7UwGO8Aifj0AUh4tthio/iRYJid3wI5kp0HziYIxPvSWndjmshYIni3omAJdwQhqHgx77Ouo/5OIcY6hY+iB84EfHQ1LuTQWPNHxzCf8WR5n+yRAYr6wrVEmVrsPdrTIWPuYvPLMAlu9n0a+ygZxWs60c7C/VM1QE6kxOkqGsbRiw13lVyf9M7I4VcKZBiJEfha4WtXSdPK+IbMBm+WTA69kHKWsbZGSuP0OZNlKCcBpzV2INMNev6UddDZLR/+ALnxbpm7QFyt0ZBqqPoXY1aNAoTY7e23c4y0sVTJC3JagrRFA4BlVctBx8RjhMpUIn0yRxAAXA+AlB5R6NgmUNhCH02xuGq7dqiuz48ownTw6tP6aAGH05L5j7XYC83bjsVLArE3K1W+whU4DMZadvp67pwTXW378A7weU8RJdLwf4HsjWFjEeWBh171YufrRnaPNEMzLiqMSyV4aJ/Wcq2WXuuUIFEYFWbuLveoG3iMx95RSj++GQhT9ggGerrQXjT4GW4Ugx7FHDsfx9p9VqVXm/4WCvSiLt9A0c++jEVOV9ujX3cXR0uA6wGjBVowWdYo6+3O6G/evlzhvah3rGRKDjzOsX/o4sROT+1bhmC7BvXggFEjBCQscmEb03oQc0+Qnc+64AhEEiA0Ng8IA1YE90dFltsbEzb6YjA4njE06e/NPTd+Vr31R2dosSFHv0y1GV1/dwhg+A6qEVwOTPcyOSD1lTTQXu9sstOwb/1sqZTfBkTzyq+Xb9YyP99lNpBc21sOHLFoXoAWDdAKNWJHiSAQeUYTOYdPAa5tAGcnhQ3f+9mh9CpoYf9G2mREyAHHKBiiYVDCWGNnw7KNgKsTmhKJIyOvvNpogPc0aCnQfK4qAjLw6xm2UkIGwCNgZpR7QnNhTxxRSc4dHTF2k+0FdvDDTM2hPAkjmNYL0JprmFZdQAJQTYyYsAipvsgB3Ki1AjhRAuKp8dsYtHyJnGkrHm2TXFQSoJZgTMWgeImgX1D0xE8YEzAwg+kT3kQBkNI9yaCrLWOTzp45Eid8HGaaOPjdX8P5qGRZuJ+DlbrfFZY437xgpSFd6nTE3jzF7sxQtOhAoaU9PngfWrw0a/ujUvdi2RgcOl4P0Mgqf6zD08G7+dWRciyfKReKaFMUWpG7Y2TtJM9yWXAyZ9XTHybLJfK8ScqWK1GeNHyPxDz7sYR1+7bBjh6/H2uGY7ijSVlfUdU9uPDJhXD+iaGYsfKVfXvBVEg8wzBjf1AA0md0NETEiQNsnH19SKJh81yBHpZ6FMijSmoRokiCR2g/uS1BDoMEFSbAoCleoEZr30xGyBkhHmrf8a/1N2D9sVpOgLpyBsC5X+edOkClKrELphC1ezU3Nj/SfHAJn7M/6qQHiTJ/NN28Gif1WgNFp3sApuNnMfAY30DxZEmMS7gBGbfZATIs4bzzPsbFQ4NpqEWJlcsHyb1rZmVkR10BYKPsW8Dcx6n7/QgqszI1RL+cGqUT6madvs0FVZMoos71h9xC9+6TUyl5rxWzcjG8cuYgSPsZRPO2Na7nSKRK6J6ael4007upsgZnxIw88WVUrocdJZeH3q/nbjhMpV2lDHNTnv68OOVsca1bxGWwz8piVXRTvKtEZcE2bmp0J98UukRn3o5gOmw32UDcu6z/BlQrNI7bS+sPHg8mvhpVht1RWnSobVf2ZkTfm1sTfmdTa7Jl7d/tp3Gku/vAvy7qICWi6Sdu+okw2H348daFoUwrYa8UtLDN+vQvksLxvX5b2k5zj8Yyw9Lufw7TSQqw1bf/l+e/ipRZCtNtPCGfSx4qaFMHfjUePV8bF/kPpjJDlMpPh2Sbicnrhn6oxBQBnDgOynPCpNVylxQBBZeKVcydbYKxLfHKHnVh/5bbEpu9W3BWebx7Wg1Ea2R7i0A/0sBParKTaaql/Grv6WhI3jdZzwFVqK2HVj/KRwVheICGm36T+fmfejvcSU+8BtjWPcdeE6hduJgDR/wo5TMyVHgvjYsw90090DpQOmWWNFBgA4FXs51wwPmrv/OFJJ6v2r2cn5l028suj5oFHeQ8u7cUArnwtdACo2LAT6IVgV1MMeD6WYhoJEUmy7xIJhx56AfoSWk88zFleB1wtZeHhRe7QaEpnsuBxTt2YiJ6tPvH1xOri1x9RjHvGkrBShbuPIf4mxFcVU22PbbcZw1sk0Z9CIrnfjZoObBix+HSSPNsHCsKkJdq899DoQo/fcGJPMKKTrGX22gykwg1+KPZoKdje51rB1j0mG1VpEP5lIUresjRJTjKG8o36djoPo4VrRZ+xE2fwLiXX6bpypeiu/ZlbUFykxVAtA60SigQKQdIvyncZDucjlU+TS40q73SJ2xYHwFtnDb3YLn8WYGShhbtGJNYQHkm3qkHCI1OY+dBzzRNbusZkwihP9QMhUA7KDIIngCGXHj8wqb1B5gNu6SH39Rqtk9SMUExtOHyVukCEQQeSpmCloyL8rEalOfiYO+UtAQjUt0kXKP/E6/AQeLK4QqNV6uABbbaESCY1Y1Rmm0TtfHqft2DjoEQ9rgIlO8JiTweQ8oVFTMZizoeJ75CTAt74tPTvJZn7c6XPBffHQyGYUFRoufE/4TSYj8OSZvcoTXn7NK5GmfH/QJYEbFN+Ge2nrxrpPDPPstkV5KwE9h3CSTCUZ3pPBQRPba9FtL/rjb6p+010SLMJ+y2QAdXD9hfD9D8byKSjpnERIC6cISOcNkLIMvhMMmET4ow4NSh8IwkxHam2JUmYFr/gIs2f7mRF/WfMKInCYI8WCRHMzhnz7klwKJs4LGpgKCicLmGYLFtgMQHMZOJYZPDsYdLMUvh8U9h8YDhMZVJysgK8daG8dqqYcssYcTO0rDJhIVJiKWw08VBmsCEDwqsJR9XBmCgJg7eJkAWFeR0nqtEHflE6ILUpDVAdAsZ9MMaNIrW4PK74ooUiQck+Qc+2QTVMxSS+E1uVrNmRD291qYVqDbV4DFKMwTLxwSkXQ9ZiRarxwtgMwigIx9MIxXqLpSnXJxDbJSimZSqt4St1JwFBQ1EIxuD1wFhExoa2xNq2Q2aTQuYmRuRXxNvmRoneIfrOi+JdlKRHR2iGQQ+jhEmpH+bbUJSD+KsM8A5RyoJLqZ7hhrwuQ2uqD98AYt6K+h+2xyxsBZdNAiccge3uQS7OI/53EyFgon4Xp2UbqVr/vq0lDQYQGQ67UD8p1qJpkgZ6lXQDNT+vUmIDMDVTDIxPLC1Y6IfWL5kIsaHKAoQiw6FwaO3UoP4uoK5gcCnVxiXV+SEXWoFWmWPjg4EA2tTeQlEbh9PRp5a2EsD4JayWA0iYobrVcgim98CjrZHGvEDXVLP/Tsj5hXBoKwRZImebA/CwrzibW1h0AMM9ivau4M1PoSi3iqGSBMZHJR8/G7DT9g6TZR5/JZYyZbJjJz9tUwIfZMJ7jW64JqJDpkNohyLMZnHDNkD7j/Nd1O2WdIzmjPok0KgPVKitxNKtbNfN8LVc1OzUnr+S5cbvngbTzH2HR1EqHHns4Khm3KHvRCltZ43Z5Ct5Vb9IieugyWZbqWBb3gPVWRAp2Vip3ZAirRiLyTxL37sxba46x0OvohfkU5nZ1cxr+9w6/V4GE56fmHuzuVnB1l4L7Sel89eILvvg1pzo9f4Paw43eg52HP8/9CV/MyX+tp/gmx8BHD+6Nfn09PwB+1Boa4/p+4+L/vgKftBg4terEf51/HuW7rrYCxL5me/0Jwo0mo4qTa76qq+oY
*/