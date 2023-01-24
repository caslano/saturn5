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
9Qd95wJBXzy41dfuvZBGdl0U2RXnbuXIrsi73+N1b9JOxmoLtxYZ8XiRkRgqri4aKbsHl09W+Mp/Uekrj1aNlneULsFpPXLv8pLq4tqS6p11sWR1nV4dL91f4i3qLbwDF/kajKJ4o1E0WFxRVFpS0nSw8FxKFd38RsvHrb42o7W03Wgt7zBa2zt7Wld2P29vbegqaX2jp7e7urdq1dDq/asqVo726t0FrXrL8eaRko7CbVxtfB0+4jtqHCmAFIfU9+z4kUFAUxvWrDahxdHRu/CGyY2+DSc3+TZEx9ZtaFl/fotvq7GldJuxpWt7yZbiHYktG3fm71q2U99StH7/Ou/QmjVl4817jL3xPca+dfsr9pQeSBwsOXR2PAen2n549aG6g5vGr8LEfzC9tUZbz1vVVniW5zaWrC58g+d715zkT/Yd3DF+D37OOB6DFIdU9VwP7jtRhXU0dILiSpFhS2euK2gYhjvg0MqI5ttZ7aoyyowiH1ENdWurfavC3c4erTnQpJUA9oxpo9oObZdzi2vMGDWGfIe1Q9pB7YC2RxvXntVOpHnW2c94Cf/Bz4bMg8yrkAqZTjwdmoM5xzadahvjHJcpBOthSgtPUlq4/zinCCjNZDoHx52HMo35+QbmNJQLv77LtKF28+yvZ8YX7UxfKdxg1poL3802vdDPjorZH51rvrllGJcLLeIyySsXKyWqW4PkWK+XqoXO
*/