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
wgO8nV6ztpTygcJVstwU/mYe68lZgUU560NBQmIuhgypaqv0OHP6djzOgumiYNqnmqc9nJG4LrjgrPFKAmERPz2R5h+gFzCz5D0j0LP7KEJWBMkTK51Z25cClRCDShC7WTgUjrM1n20QvXvCly3a2txV9bL1zzUWapIGph9uuHWihhtl336dX4RFRZoSVP4I5CRotNKEuEQ1IE7fCv/YBk5JunnYWmfvK5basB1/e5+/pXNKMCH+cIM6hfh0zhhHDCRN9/b2c+AhDV3WJzUWHCaG30A/RvI2It7TGZUcd1wBLXLX8NzDlCmq3d+9uup9PfFby1sljVuojNYt4ScwFJ3iLf1Bl4PUJdbklTad0GeVCtTRLvB4XFpDUJ/1c4d9qHiOAndwUzFh832XQri7FMlJqRohCndOS/EUshTSA3vgPvZpx8Uawc9WFjkDz5dfFy6tjNQS9IgKu2gJuG3HfZQcoCjaPtrWQoHov/0LhgvHHyb2pesvRPWtOMYgyvv/HOH3S8Yh7dGv0JQdOPCRQW4/tTip09POpPcWmUjfsMU6XEfaYkbCCM3H5w==
*/