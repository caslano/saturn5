// Copyright 2005 Daniel Wallin. 
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler

#ifndef BOOST_PHOENIX_ALGORITHM_DETAIL_DECAY_ARRAY_HPP
#define BOOST_PHOENIX_ALGORITHM_DETAIL_DECAY_ARRAY_HPP

namespace boost { namespace phoenix {
namespace detail
{
  template<typename T>
  struct decay_array
  {
      typedef T type;
  };

  template<typename T, int N>
  struct decay_array<T[N]>
  {
      typedef T* type;
  };

  template<typename T, int N>
  struct decay_array<T (&)[N]>
  {
      typedef T* type;
  };
}
}}

#endif

/* decay_array.hpp
EtpRYtpQcraf7MG2k9ztJv/eNpPQXrL3tfe197X3tfe197X3tff1f//6137/nzgl+vX/z3//vzWxUFY/y1nh2YYTQ3+mvnwmuZCFrP7i/Y7t169Lr556Yo0cNzGzT1PVXfRp6m0wK7vWT3Jn/44vEpVPmuXQp2m5eKawZEw/65FheaPlR0J/kHKFipS+hzPs8Fy+nBie7Qj9NoaLdKgMhr582fqR1g7PLp4tJAiThefEu7hs3PzpFZ+Wkb/i+ejzs9J+hsXNT/x+dfLv/Mje73FNSF/VwtLHyoyUf++kPNI3OvWsMeOH56N/VLHSow7a/WMQ2xclfltQXt/ZC97mE7+NJa+2jj3X5lPQtpGCttXEb1PKuy0ofltKwftUFLTNpKBtPnm1Nb2e0Sdka7Ovmk+dUTrxtUs69Ot7wGdt8mobLHjfpIK2KRW0L1PGM2D7hLov1Im1Lffz70UMfQanJbAdy7I9y7MDG/BoNmVHduQxPI3HcjCP41h25gx25Z3sxnvZnfezJ19jL65nH77D45kscSewMk9iE/ZnS57MfjyF6TyVU3gaz+YAXsnTOY8DuYSD+AoH800O4XoO5VdM4XamspSyGMZGHM7mHMGW/2TvXuCiqPYAjotKgYDxElB8ID5TVATfT3y/FY3U1ESERVCElYePwsJ8ZGZF5c3HtbSyMvV6MV+U2kWzNDOzMrWyovKq18xrpmVKdn/L/nd2dmcWd1Hv68N+OnydaWfO/5w5Mzu7M+cMTsZBOAVjMQ0X4VR8CtNxDWbg6zgNv8dMPIM5+DtOx8pV2LbYBWdiD3wAh+BsTMOHcBrm8d9snIPP4CO4FOfjLlyAe/AxPISL8DNcjD/jE3gFn8Tr+BTWqco+jOH4NDbEZ7EvLsFBuAxH4XKcjivwQVyJj+Lz+Cq+gOtxNRbhi/guvoxf4Bo8ga9iddrda+iL67AfrscB+BeMxb/iCCxQ+uzIZxo+QGpqd89mc2m3rbAhRmIXbI0xGI1x2AYnYVvMwnY4Hduj+Tka8tkkn1lN7Z6jsV3yeQsDcAeG4E5shruwFe7F3vguDsB9OB73YyK+j3l4AFfjB/gSHsQ1+CG+iYdwB36Ex/EwXsGP8Sp+giX4KfoR7xEMwKNYC49jbfwcl1S58b2EhT0qfjv+f/nteBmpoOK34//K3449rlCvpMFXKlW8Kl7/E6/b+/2fQRtu0fX/V3wryfdP6RDIyzTGsY+4L5jjh5vy/TOB5bLjkwxZicSQydqcG1/NPGZEfhXWo5oOZNoyhkTlKpZxIKKjK8m8a5WVeVGWeZes85QxJH60zou0zDtVWTsmxTfWeR0s845b57W3zPu4snbsigPWeW0t896xzmtjmbfTOk8px1brPKUcGytrx8J4zTpPKcdqZV5rpRzLrfOUcjxjnaeU43HrPKUcc6zzlHLMsM5TyjHVOk8pR6J1nlKO+6zzlHIMs86jHObfH/oo8zqWTndWpjuUTrdWptuXTjdRptuVTtdRptuWTgco022UcVGySdMT0nIMqB7HySjjpLWVdo20a9pjVcftOj4tI32SC2178B22bfugO9OWNuGutE+lfre6a9v7Rndte3/NXdveV7tr2/tyd217f8Zd294fd9e293nu2vY+213b3qe7a9t7hru2vae4a9t7gru2vY9x17b3e9y17X2wu7a993HXtvfO7tr23tpd296buGvbex13bXsPcNe2d093bXv/o6q2vV+uatvef2Ba3d6/ZVrd3o8xrW7vHzKtbu/vVL1xe5fjOM/ts45p5EOigkrb+4Q77dp79iyjwYXj+I32s6Q79fMt0MvXxf3MUd4yfivPHOWPPHvfR9xP3nQ4k7w=
*/