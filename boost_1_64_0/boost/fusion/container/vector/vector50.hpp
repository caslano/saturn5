/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_VECTOR50_11052014_2316
#define FUSION_VECTOR50_11052014_2316

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
#   include <boost/fusion/container/vector/detail/cpp03/vector50.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/vector/vector_fwd.hpp>
#include <boost/fusion/container/vector/vector.hpp>

#endif
#endif


/* vector50.hpp
JYTthGrCOcJVQvPlzSyRBCshm1BGqCScJlwgXCOErWA/EBIJTkI5YR/htRWB9maBKTAFpsD0VU83of6fepEbr/8Pof5/VFe1c01DC2vNI30+KvX+Vm1cgJp716ayfbdI/WbsGffz0YnkfcqUcT48n/Wo05T1xkg90wOEGNZr1dar66voQ72FPGuuNeZ0NF7S1zWZPUeXOrkyNW1LSVfP/prVUhd/QvJaLXmtNMsrXePs9nS/nucb8xzvJc9Wjzwbx0MmXZkXrn/fgWzbOW3b1M995Pndk6GGelKpa4+Qe8Nu8jy83N3OQ+tWWP86QCX9qte1ugePMbcTpa57uoxXnoBKWTtecy1fqz9sZh11tLu/6zlWucOkvIu9lHepl7qWDzpo41R7Hb/cihdcy+Xk5Tql/7JWd0iVjPT5jNPipmWmp82jqqGACkK1jOxq3i1LDWO6R0r9+BSpB51AGMoyyd9Tludk1nVl9uc4NNYRS12nVpdh1copRd7jKZ+lrjRZ+5wj43fXLitHTbnYmOux77fLdvWUY6+Huy7mjGyXdD32pf2EtzHM+0hajXT96JVkO0paZ7UyJCln3dc0r+1qJJ2kW+QZR0OWxRboOp9Ou9LRn0x1vk9FOZ57vup5PJcb0jYr904e4wxoSSoNHrRx1YsNx2uQ7KtCtX7T8D6KvHngrc5e2kKY1fE3bNmUco+/RX1Glvlt3dj8uvWwcu29CB9/WzsHAu+B/Qrqw/5b6r3mO5T5ey8+9sGw5z59eXvGg299//1Vb9S/fkt+3/C7h+X0z+Hkeb3iILwFB+vrKSRejEm8jvK8uRM+gJ0lXiahUuKdkHi3YpLE6yrxuuNA7IHD8E6Mx7twLkbgfLwbt2JP3Ie9sRrv0fIp3+cYYZLPdvK8sD12w1CtfkO+h+X7OdhQv/GI5HML9sBHsQ9uw/5YgRPwcczHJ3AB7sBluBPX4pO4CSuxAp/CZ3AXPo9Py/bswVdxL/4Sn8EreAD/gQdlrO9ncTw+hw/h8zgDD2MJHsFKrMY9+CL+DU9gZxlbuwu+jFH4LYzB0zgSX0ErvooJ+JpWzvKdjFNMyvl1qQd4Q8rl+1r/T/nOg54ST//c+5zsnx9iOP5Iyvt9Xfyzkm4nk/g/kOf7b2M7PIsd8R2Jf6aBfD/J95YSX9l/p2Q/D5X0h2EoDseuOBJ74SgchKNxFI7BiTgWE3A8puEEzMGJWIhWXISTcDlOxjKcgtvwIdyNU/E5nIbHMBFP4nR8GWfgDzAJL+IsbC/1VF0wGe/ENOyLdozFDJyBc9CGWbgY5+ISzMaTmIPvYS6exwL8CAvx11iEv8cF2IiyW4gzcBHacTFm4FJ04DJchstxC67AJ3AlPoWr8Du4Bs/jWvwI1+GfcD3+EzdgM/bXRmyBm7BM3jedWVb383x/+gwH3j3t27uneXZ+098/Hb7v5r6DupRjazvhFOEiwbKSZ9WEaIKVkLky8Hw6MAWmwBSYAlNgCkyBKTAFpsAUmALT/9Z0M+r/7Rk3Xv+v1POPlXp+/dj0x/F+rMQiZczdE+5637FxI22JD9qi7nPVUx033/zhrIw8DGhZiRMbNHDVWQ085VlndVqrg80rdEo90hnsZpF58m7oIOafxUbByvwZrrjnLfp3OKtxL/K5SUup07XlZbnrwS9rcQvn5Ug6V7X4zNO9g/oaVqt1l0SXOlz3ssxjUa1vZKH055I6XdkWXqGt1RHLPOrf3POicfwdrnVp7yaPM9TTh2h1ybI+JVGpN6vCUuUZIQV56CVDvVlbrZ+f9o7iAVL/2Fvq098nQhd8G4vZr5Evu+s51eMtKzcjj9EE0vLs6vsVKgw71ljnWYlz1Xc=
*/