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
lkd1rLGwr8BuCBeM7GiR5jkaZK4GfGgqeQANuBvit4xoAnEnzFmDOadA7CB/KwR0tzfvzMMhkt4DdvjTheYwmGIZBlNgGPylfxj0zTC485X+YeC5NI7DANi+wsL2OncH/TgqrPxeAfxe8gAE49CoIC8oTUSJR4h1PLwP4+EJIOPDbBWIKPLbJRGHY/dy/6kAKddVqeS+eDmC0YsGNx+v738f+G/+ONpPyW1nTce4LvmrexnhOJb8dUljZE2TMYFd8rfcWqpSJzS75G+mUmVNkzGBXfK3nKzIr0Dn8t8HuwX6PFgutX7K9JknQUM2IQETFB/JEm+4xmeM1OfBciWl6VYaio9kiTdc47OXZiuUxiYaSgF2JbT/4mMHsOVzyR8H+B5z3e834aBb9bCy37CkPaqMbtQpj1q8/V9J2380JlGjXLbg1l93n8R7BmfXSrxncEljZE2TNQEVosKlEBWUP2MaI2uajAn0aaPSrlVXgQFoQrtWrdqVGXcFHB/JEm+4xrtFVjDxjPGRLPGGa7xbJH4nNdVOelG8w8875OP90vAKuz+7F61XcuvZ1BFJNDxLjVjGPnO84Rrvacv32ZcGfteIs9gaJVKv3nxg9xauHUlevVjmHn+JrPTTUVhf39mN2yM0dWqgw46EXrL3RKW9MSoskwWzfWZHWsz2meMN1/jMkcT2WeIjWeIN1/iMkdmVE5QRN4Sxb3838PYXsevQhsfNjwv7DU3/pYvU/9DHbpVvzP1iVbXIX9c6y1+Xq0SiX5POiSoy2cjPL1lxqD4GyX1h2J+6IF8yoTTDq65/mAvJB+EWn8/vGwZnGY/CTUyWHP5e58jh4rxiZEiKlTDASs050jxJKorBpq9skYm8CAYDmeiEXFOln4QJy1tX6DUtJ3n6Mm4wy71UeQ3SqGoN+uCCipNQvinwyjDIrwKPdgI7RoEdnRHsGB2sL4wifoIfu+mcMT/tyf8x50Ynq3m08bJcEUagLUScnD8rdCbHHPkiFXR4YYd7RgcKflcK/swU/F4pBFwpBDJTCHilkONKISczhRyvFIKuFIKZKQS9Ugi5UghlphDySiHXlUJuZgq5XinkuVLIy0whLyOFCP6K0i808objBJYAg5cAg2QDYPY0cktWGHCcbOHdKE03YWY3DgyWCcmNnfniaj+vsEPN4lAQvyIYFASZkzTEIEgGQGYICHrMHbSSDvaKdOhjkc79OKTzPhZpn0YaOykE/unO81wGJhfOkhCfoopDouk3PuqlHeP+T998zJWv6i6x8pGd5fDWoLCBmb6ONvdhv8+vNvdBiPNTcETu+cPXf7AAeO1RJR2khKtEMEocISeBwWaU0VlYCEwSQjzgsK5jkLWkSJOB4KZs0qCSe4JlLCgFPyEYWYewlkPCPuAYbesb/zGf4ibJKQ+91ZDZVnJK9lAIHrsHj6/4gjDOZBq+P6Nq8+qAsLH51NMDfA9FELDyO5q7i3JKN4LdBgANQz4U/fH5KHrsk8/LQ88+H91Ll1fS/9OPqC/HXQtAaHz2rxDaPG42PjWG0m9i74W+AU9IA3xEPRAmu3ojSvA7NBlidKPEdPPWTeJYVCP8xTbZqzavJWefzz41gDbLqXcfAfvk7eDCqnsH0CRXlD6ATXU2p7ubxzVQSVLDWvFphHxqXYlPb++QT9gfK4q+irnuaEx3p55bD/89sBD+u+4B+O/2BvjvzR/Cf4H74L/C++G/bT9Id28NrdsR7aXbLM8fu+nfwg2ypQeKUo9vHncj/pg3YmtoFfyQ46R0D/k+2/jkAHBuciIEbmlkN1EvrhY+qAaHsIve2I65j4O2vNXAJi36JQSk5t6bls6oOuHR5oyKvYw+H9Q=
*/