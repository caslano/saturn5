//  (C) Copyright John Maddock 2003. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  for C++ Builder the following options effect the ABI:
//
//  -b (on or off - effect emum sizes)
//  -Vx  (on or off - empty members)
//  -Ve (on or off - empty base classes)
//  -aX (alignment - 5 options).
//  -pX (Calling convention - 4 options)
//  -VmX (member pointer size and layout - 5 options)
//  -VC (on or off, changes name mangling)
//  -Vl (on or off, changes struct layout).

//  In addition the following warnings are sufficiently annoying (and
//  unfixable) to have them turned off by default:
//
//  8027 - functions containing [for|while] loops are not expanded inline
//  8026 - functions taking class by value arguments are not expanded inline

#pragma nopushoptwarn
#  pragma option push -a8 -Vx- -Ve- -b- -pc -Vmv -VC- -Vl- -w-8027 -w-8026




/* borland_prefix.hpp
I7slLmRoO+Ok/bgk4ZKUJW41Pg4yPGI/njAOgXkulFmfHRnm0q9utSiyJvseCxvGByZ/kgb7vwVr8CSobluHDI2DoQGmPq2n3XPETQUfDDw+e3eKYJ/HO1rTjYZZlt1ELIo+vuuSDrJbdzP/4VY27/4ZjylTmMpksAZfFTaOwv/SsCmXnWMkWtnB8oMKX3t33I7xgaAomnWFuI1OkwYDRBs7Rl399k3spOAqGGcukvQXD/5xDdDvSrZSpuPEx2eIXh6/ozCtikAKDkMIr6/7fbg1VO9YhZJ0DrracYMpKuUNa7xyCTR7sZaifM8QXE8plCzB+mHvG9SfM3CZ0Sm848Fjo/68o7uIoRhUbbwzkVmUCRzxXvoL2N7LNK57XU5xuVoOjuqPE4mbHzN6vLGDWCW3QOfyS8O/iIjYkB/IeKhGBrlrrQ3LqPZ8rzO66E5ieAD05QY6S7LGljWCJ/FOpmHUzPt8hPtlv5a09KLEvvOQfmC4FVBeSTVsxk4bsRGxlN+2UgbHYHTIO5uhb6XSfum4aymk5gJL6Uk+KbdC6eE7y8hYG2w4TU5Lzg==
*/