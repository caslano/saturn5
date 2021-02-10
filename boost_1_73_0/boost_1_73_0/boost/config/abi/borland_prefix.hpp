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
gqzDZd+4/wdQSwMECgAAAAgALWdKUo/Gl35qBAAAaQkAADUACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMSU5GT19DT05URU5UX1RZUEUuM1VUBQABtkgkYK1VbW/bNhD+rl9x07DODhS5WTNkadNijuMuQhzJsORmBgwItEhFLGRRICknxtL/viMl56UJ0HyoE1vS8e6eh3fPUf7Shb2f9nF8kw5++EntN8UPXndBUym+sky/HJCmd9D+YeASr6+AGsBD1F3ah1dF3UHPRqUd1om5T9NXwC0NSfMzMMHL1NyipY3s4kei3kp+XWjojfpwcHz8F+zDH28Pjjw4IxVnJcSaVSsmrz04odbyd0Fub33FPnnANJDSf5IwKbgCJXJ9QyQDvC95xirFKBAFlKlM8hU+8Ap0wSDnJYNRNF0E4T8e3BQ8K7o8W9GAKkRTUijIhoFkGeObNk1NpAaRYwbMT7nSmLPRXFQ+wjPQTK5Vl8aQIKUSQDaEl2SFcERDoXWt3g8GWSNL3MmAikwNsl0p/EKvv9vVAtmsyRZErUELaBTzwPh7sBaU5+aKJUJj3axKrgrvgRYCVnQgJChWll06DOVMtVtgEHfV8own1Miea3NRolIG7aYQ6yeOWNYuUd7I
*/