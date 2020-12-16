/*-----------------------------------------------------------------------------+
Copyright (c) 2007-2011: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_SET_HPP_JOFA_070519
#define BOOST_ICL_SET_HPP_JOFA_070519

#include <boost/icl/impl_config.hpp>

#if defined(ICL_USE_BOOST_MOVE_IMPLEMENTATION)
#   include <boost/container/set.hpp>
#elif defined(ICL_USE_STD_IMPLEMENTATION)
#   include <set>
#else 
#   include <set>
#endif

#include <boost/icl/associative_element_container.hpp>
#include <boost/icl/functors.hpp>

#endif // BOOST_ICL_SET_HPP_JOFA_070519


/* set.hpp
jH+1RqS26MPr7dMy0uyjho2TeqjX138t/yKVOvnV5vulviRtuhf5ko1/2ebpiF1JdMZ/w4eo5OhJ5MsLPxsqpS49rg0dU8va5giM0XlBr1Tp4Eb2+ZZ/mlfjhtdtx7xRqYISHPkd+VNOhge4bVcXqZ1jVVuttOOklzZYLn49VfjtFxwm1bMu2E53jxJeBbnFdY+7+Lv4uWJHxZbuZ+wpqkzamUafC3z6JcCLN7BzjvCSf/XrJ4rllfHF4nwbnKWqyWmlma6/0P4cx0ivzBxaJBz45DOX1+cBbY51z5gIqX6GqhnPloXsSos5I9OltqeM++IzHxNMpJ+lvz+n4GIglryM/B4ND/6sc+3o05rtXjpzQWNRiddPKqfDZWNakhjCx2nwm7yz4sneidSdiJcl7be0Sqy+oo5SPydifujRcy+Ug+iTH5bST4Mnc4bW+96/Iv2S43Lv1PO66ETDuIMT0RtLL0Xrzw6cPBeL3ztgCVayO2gQp5J3vsPhvm3gnxXRaPpRhv7jNk7Jh7hn3j/VRMkQOxY6+hf88n7c2Tmvnzqz9TlVt++I5y63CPH34y4ecoXJ+E/+qNSwrlbVf+N1rpgBn+ElZTCxHf7RjzDOk+/ne25YvTSwZlF+N/FTe6Tkz8c8ff1PdDf2x271zlrqkyVGKl5XIiyormvwjzaQtxkIE04wuVLYhVY1bj2QU7oRckaq4eEIreUlz13vB9iXtVZUT3j7cn5p0tzfckpy0G6jUu1j5LXToZT2SEtyLqdhcL6O3BcnR1BEJ8nSi3FEIppoQtBj31FQtafYsD3UpSzvN5cGeyT0OyOd/dDX3zOwZMJOcs1lprDNgrg/jTta0SStT/Dm2HO/xIfn+ruXWoZ0zfWvMPS2dm6YPmB78bVV1L+n9iaT5ceAufI7Vz/XfGgk9hExOPNdQm6TqMPO3kTpiqaJ4hsOHbrwJW4Rispw1qZpRqKxJ6VsgfL35sQCUrzkf2GiFs/LeafiUgDjebpPWVF23Pz03OZIjy89dL7hVrjuKZqhjfq99DUZ6fMG/M/brwoEXFbYmMRqF8ym1RhYChAWWmfEqXg6sVTNsOHRlJ+c87B/3EP1uk5kibksjnrQx3PYByfunN5m1UTz2ULGBIxfV9xkn+IeldckmZsxmG9NXqdnNfYh5Xxfm6MqhWS7GJnbCPnODhypCue2fEI8dGQepKzU55XXLdXfEd2MOXlwbEzFY2yOS318TEL4Dp8GnwmLAhdhafgeG11d3N9OfYHFseBjvF7bbyoziReelvGabTnecfIk8ANW6IMdnBvDEmLsDjkocNB7fsVbM+umndzO8JbtZLES+87brJdvIgUvx3tLqpkyug5Mi1SfP3VOzfH1q3P7F9Wmiidco1b96JN0FCxVp5GmYFc0P6NVyms6/FycthNcSiHlGQMJnw6LzrzCHn3DZYfVsViHuExeZoVML4VY0cd2zbmqv5Q9jx2QKLuiwtRXG8CITUhZLUkfv085r0vOedVekf1++EjEm1lXJ88pvCq2Mzxb2BEEbn6vl2dZxH7iFCmZsCJ/50R2hyZkskaKlul7BnWuhzAp6gynxzkldZ6gf/Z245D2x5khl0VVqWexvBOLHlr5s8totXWOMO91pfJJo/bCCyvBXwmVUaxysOjglXWWpsS2dWrT+t21oTIlNXLuDrLHbjnd5Kol0Lq6LRnG09Wszya22ldD7VvDKmYXtWH2lvFHrkWbL6dIOq7AhzPhml1Fb0eyVwUOqHH07pDT/RyDZanp7py25zrIz1/GHjvu0HNZIeLsW0Xr+U9uenPaKzetsU+8ZW9VukTz5vp+/8XMe6fgFZyxNZymQorJbcqfn/o=
*/