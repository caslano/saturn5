//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// The aim of this header is just to include <utility> but to do
// so in a way that does not result in recursive inclusion of
// the Boost TR1 components if boost/tr1/tr1/utility is in the
// include search path.  We have to do this to avoid circular
// dependencies:
//

#ifndef BOOST_CONFIG_UTILITY
#  define BOOST_CONFIG_UTILITY

#  ifndef BOOST_TR1_NO_RECURSION
#     define BOOST_TR1_NO_RECURSION
#     define BOOST_CONFIG_NO_UTILITY_RECURSION
#  endif

#  include <utility>

#  ifdef BOOST_CONFIG_NO_UTILITY_RECURSION
#     undef BOOST_TR1_NO_RECURSION
#     undef BOOST_CONFIG_NO_UTILITY_RECURSION
#  endif

#endif

/* utility.hpp
vFWqTJbPl0Cf8d5+16oxTK9zMU1z63/ZpkjBb15J7L/+539ZM/OsIczwMWHk/FQwoTO2I1X7hdv6DF1nS2DLZiu0pnftwVOQfmvSOP60c0SoVij31C3F8x5J3xzJVaTjy/ilDt7+m22Zyad/Pdk6rnLL+0Jzkla/zq/UXxJbQVuiW67IEGEiPzJvO9WyjHguNCuvezHIjX9FWqtPpQAdazKuquMWF5fCm6LVl9vn7c8O1rNJgrrpPpLhN+nl2wrduqNyM7q/5lfQr2+DY3WQiHzZxEd4eg/1u9muBuXKikRwanDyj/7cPhV/ndZXeXoJVcbmvcmO62tHnmDb+49SroRmdTTdpzG+Q8vW7D/5psG/0OhOAW0MrGxiEdoBlRCsXOD6K5IqcqPWNmUDLrP09lcYakHr1q6g8L7j1uFZn8I8cwpYxWyOfrtAPfT0lOHIuZjUWqUyAgSzveYSTrSC/ICu7HvPb3r7i7Sm/wxOqVOdkUwraUMVM/TFILdGpOUezFX+VrputpKeIGIaCH8dnjJOXreyouF6tlDJT6QFk8cMxcFGy0niDREa+mLgnIICDjbXgkonz/dyf1/ORxtZyi2t1KznW51iSL81xh7WUht6bPetVvuV6eh6isV7bhcy1cgS3PRO5TLhud/jK9Jn1VSRK6IKDgqDIraCTocnR+ekI3NbW97KaqBai0o+RGzkTNZmPBJpe+6S/Kx+
*/