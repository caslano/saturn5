//  (C) Copyright John Maddock 2003. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//
// Boost binaries are built with the compiler's default ABI settings,
// if the user changes their default alignment in the VS IDE then their
// code will no longer be binary compatible with the bjam built binaries
// unless this header is included to force Boost code into a consistent ABI.
//
// Note that inclusion of this header is only necessary for libraries with 
// separate source, header only libraries DO NOT need this as long as all
// translation units are built with the same options.
//
#if defined(_M_X64)
#  pragma pack(push,16)
#else
#  pragma pack(push,8)
#endif



/* msvc_prefix.hpp
iDV5DxovDuO9PSUi0DlDwrdARjYYvW/5NTtHVV2QynCL6S7n0QtSxLvXLrQ5UAU7m+R0ArX6jtQIbQO0SkilNJgBcrg+EaHWR4c+oxerzCwGdDWLbcLK4DI01FACwVaJFZFzkYgShYVrw8NLCFlvLKYwyzrDfjNi1iPuAErQ6Nq//2DU1DMnwKHyjmhAo7boOIjXNoVPczFE9lgxAgY81lchguy88pAx/dDPUW3e24iF/i3t44RnMrmu6jyxt9bo35mLBI5kl5NbMF4ybha4Q0psMyUY4fjylER5as9RhyLJ0f/oSWW9yQPNB9WanS9Soa70HEqzIS2jVLEPmUPfvfCq3/zGORUoGUm0hIbEhEU98o9e28ftgPx5GJXV+L+6OcdeAWcwPjTSRSH8pl2XRlqrFkq8veueVeYb2KALS4fVI5qrvZFqCTK8/+MOIYOS+9cH96acovhwzKCCa123eOnuGI0rc3cxsJX/PiDox0wIPZu6VICuu2ipoulXaEJhDXl+S5RNKwDXEShLhlQOZTTw9AH3qX5sZlOh5tyRgR/h/86GXbNAAjsUjw==
*/