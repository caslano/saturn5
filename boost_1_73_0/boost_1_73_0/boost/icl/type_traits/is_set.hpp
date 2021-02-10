/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_SET_HPP_JOFA_081004
#define BOOST_ICL_TYPE_TRAITS_IS_SET_HPP_JOFA_081004

#include <boost/config.hpp>
#include <boost/icl/type_traits/is_container.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct is_set
    { 
        typedef is_set<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = is_std_set<Type>::value); 
    };

}} // namespace boost icl

#endif



/* is_set.hpp
EZ1nuxw6psDMigTa5jaOaEUB8Ra7riiLEnt2F4oL4AlMF7i1QPoOSALNPQibHDedC8sxiUKDrrK8PBTY1LGyYXc7Rv+IAy2+xUGx6IlBHf65CHU73fI6AdK+6fRdjb60XY0srrFMSZFtaGnPRPWQl3cMCxinZji77qsaX75la+6xzxm76H58uSGraje9AHvJmW1eDRqfsIzgaps2SyTtjkmO9D4Ouua0lgvTe/pzgBLQPDju17jrMlmICPxIhygucNPTQgwyQGtuvoyeWzAzlHr2puDV/p9vmypDnwpQW0Bm5s4JZ6QnopHvsvi/dKkteSa3dKPM4K1CXvUNy7k2bGseoop014ize57EGERl0nQs3/o3WunnmWnOCeiUP8YpbnNqPZYQrpdzyjPq3eRH1/NL8XstJLUFaubklbrjdImp8oCoUYI3qr+1wBNujNhRhHS7KcVDrG4KvE/ro0ykhbVNRT1JkXm0uGKjiBHwhg5eu3hvtzoECYsfVU3BpUS+NADRnlfA6DHrRSU5khjFTaOqKxTooih0xUF3/WaT1JQYtZRI6lcIKaneWzSPKD0MauwSc8u/RLO07W5ib2J5h0zhkXgm2LJt88KwITtOErFDRtJxP1o1me5clnJVt6suFax5p1tNJvOz5VML
*/