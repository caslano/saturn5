//  disable_warnings.hpp  --------------------------------------------------------------//

//  Copyright Beman Dawes 2011

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//--------------------------------------------------------------------------------------//

#ifdef  _MSC_VER

#ifndef _SCL_SECURE_NO_WARNINGS
# define _SCL_SECURE_NO_WARNINGS
#endif

#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif

# pragma warning(push)

// triggered by boost/detail/lightweight_test.hpp
# pragma warning( disable : 4640 )  // ... construction of local static object is not thread-safe

// triggered by Microsoft's own headers, so disable
# pragma warning( disable : 4820 )  // padding added after data member
# pragma warning( disable : 4548 )  // expression before comma has no effect
# pragma warning( disable : 4668 )  // ... is not defined as a preprocessor macro
# pragma warning( disable : 4514 )  // ... unreferenced inline function has been removed
# pragma warning( disable : 4710 )  // ... function not inlined
# pragma warning( disable : 4986 )  // ... exception specification does not match previous declaration
# pragma warning( disable : 4711 )  // ... selected for automatic inline expansion
#endif

/* disable_warnings.hpp
5ax+7xPhDaG7FB0QOaiForvxDj6TcTTb/w04swXNPS+GjWrtYkC8TvOyA4YOR/jXQN4BsZKcH8IRA+Y5CL+vqCluklGV7gh8AKlAYF3BfAZv5WH+x7aUcVdaQLZDqzTRqrijsqbFeC1nD8qzgTuaGhaJS0VHCvoygu69TypHNO2FVDbGPNxU7vY08Yqr4rsmpDukI6Z+3gQepLrKtzQxZASge8vxduxGDvsIT6HzabgE86uP2hg0DSafCTiJUp5Eu6ZM5ATkivFYRAKe1w66Wz5JyJ0gH1P2uAL9NDjOw7Dm0VCUdSNwGcGjL5GDK8FxpTNZ93OkEVWnLnBS/leZGbofl0KAfP9ezWyhLKZwA4XYB54gxgXhVuewXXifwN0zkmQ3ujfhCaKJEWI4cKzbskSgtCOQufOT5zRDHKlGAH2tnPGtgu6d1ZZevNapt3672sOS3xKnRvXp05QoShcHTUMfzZwnzmmkuLmauE/PLOA+Q6otGnidU2/XrVoy9oHOekYKSpUgGW2OZaKQA4l54pwWg72zaCCLM2Ega2ZZA/kuWm+3cJYcyPboekYCSuuhy7jLbOMoq9bGsZDHsYTHsRC/n8PjSMBx9NHGcU+03i5ejeMmfRwLeRyLeRySHS+0jePULG0cM3gc83gceILWveFfTMzp8lVxmXIAugMbmGLIMwwylVVzd5Ifz7B19/gsTQYH03ySr/JeJ25H
*/