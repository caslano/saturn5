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
yWfg4jAKnChskjc+Qha+7cbiiESaxLHl5J4Yckxlyv/WkPecwsmSqEB5kgesAvoNPMO/C26URFZipYJfY8E5Ofq0YHK+TNe1E3iPtOmqRCVM/EpS2Ryen0lKNw8EvcGr0lvBt21ZeolI3cBJvSiD9PCyNXPkwMfzDpMHnwh2UfhhzuW5zaxZV+fPGHt3UeDlaV4K88ppX7CH+x1njG+R50eO7zqi+arHgN/fy1R+JnATJ7adfnXRb8Zp9IlyxvCJkge2lxWCWYX2pVDmKm+T1PVyNyljlIlwO7iWGXk6kclgSpFGbhgJcpsZ86b1ZvLpht7EbhzAe49N16mNudMUk01E4XuxU4axGHrN2nhrkskHIg+CMHWzBnFMez/qD5OFjRXfDkrZCtcyCTX2z88bcQRJnHtSjRvj4Epo4fzaqIOsjOPCKgMx1E0JX1NcYfKO8OzCc8IsFwPXx3nd/Y3JuSLwvTSJrVwMHm0PvCE6ucn0JAiSIA/tqt7Ns7ijth5fNvl3MokDJ3OLfp8xHUoYlYV7aSyORJbVDtPCA10b4nqAyy8a8lGZJkXilIPyvBi2nuszeZlsBF8/v2iQ5xpP3wdjcYB9j+94rgd54A4b+LAnbP19MfKQlpYTu2kkhl8VGMjDbzeNb4xrW1nixKrtVRz02IjvmUw8w9zT81y/9D0tbx7e4Zqcyj3Yj93EL8pAoLMC01/3FEsnh/OI3Hc9cS3raV1Y3N9hcdgisTM/tPNYmKbxyn8v7u8wuVDknluGuZeJAXPs5jdazzF5V0RZlJauZ4nBa0ED66wPMdlMyEqKy9gPRKOJd3O5L7M4LBHIDAR5kAl2zRATX8P92meYfqyTwE/LVDSaq/D+MfFMYz7t2X5WqLPAZnMi1E18643F4YoyLhPfl40/aJYzsFchmGwisjgIArfJjqF5fDhpyIcZuEpPG8T5KOfr+SeTL0WUJIkbZJa4tpkk6g7u89J4HHiTOLes2LXMjJhmqSoi/D5dZvF4ovDs3MqwPEOtTyEO8Ck2uk9+X/aCby+Q4A/FAT4m8cn9iFOXZCN3Je/Ivb/2OQZEfEQO72K9BO86DfsQ4F2nyWtz8Q7eFNo1G4Nir/a7IJBjepECWp2/k8hr9DTE/UIAt9nDFvDw3RixyG0AfS8vvNS74ftV+BYY2HOODPuIAA/f0wPesA6BvF+MMp6p+Wjbd3mskWe6E0B+Zxz5ww2dCP/itmvwG+yYZyaQP9xwifD37xjOx45FbKvfvnM437ihjjaVB27KZUxDHWonvbyrkUtNsLGNyps1cvX9IOT9FnmDi2DKW7wV4ZkLTcL73m00DwrME++OkHsbtwXebLuL9zTlGQyUFd+xAXz4xIXer1m4veJey2CP8C/f8Vr89qrJ/92dhvB7LHrkj+wbyuf274q/767D+VWB6ds8d1NcPpnCuN5wd4KDZlSjNuwt4c1/tPu8dE+TixS059x/L8IxJ39kLL/vvRXPvNdM3xBEzqA/w3vjvSTJuc57WG+/r+Rex70q9IN9P+Q3+UhC3r77I6/5njDeTRrG00mT+wEPkNwbuJ/1oinJv677VsrPJX5bjPvD5K74hPFdcV07LrIbeEdffVeoPfh7R5oXOOb4cXwUuEO/zRjn78aG8bDrI3f/doM7OEZg/Uxi/dCFM7/XfPk0v1+R2JaTh9EN36+g3933XMv3qO4XWxjPXNQjLx1nPLO47D71BSirmsf3h2w4+a/b7mVbhnFac89o5ZFLxuKbjl2LW9gx4Z4bvxa3t0m/FXu2ca52ZA1s+t37k8mDIaYahTB9LLuYGOSqCDG+W+9o5mDRCfe+O4dxMWksj3uTYdx5aRrVq+dZyNs=
*/