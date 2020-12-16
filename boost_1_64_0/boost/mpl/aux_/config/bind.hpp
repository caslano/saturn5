
#ifndef BOOST_MPL_AUX_CONFIG_BIND_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_BIND_HPP_INCLUDED

// Copyright David Abrahams 2002
// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if    !defined(BOOST_MPL_CFG_NO_BIND_TEMPLATE) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && (   BOOST_WORKAROUND(BOOST_MSVC, <= 1300) \
        || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610)) \
        )

#   define BOOST_MPL_CFG_NO_BIND_TEMPLATE

#endif

//#define BOOST_MPL_CFG_NO_UNNAMED_PLACEHOLDER_SUPPORT

#endif // BOOST_MPL_AUX_CONFIG_BIND_HPP_INCLUDED

/* bind.hpp
tP5wIpbayDhpPXSJ5devr/kxPwOXkECk/A41aQvZhOfz9U6fWdyr8Wv47grLGE4q6SvZTyxj5QZBvdFi5jDpITrS12ruidUPLhB23RzDukkk/S1HcxfumdvA75mxa6Fu7sEbOuc9z15JHsEIVDO2eBRnIi/zwTBgQxVpMNl4Ub0FOf9g7A+TEdMvFjH831dQAIGmJLZeTDnaMHTwkFzwLGEnvp0NR8shD/5E5K3g30OkHtKa4xMqnDLGDxqTHvIh47l/pQ5VqzQoSWUhU7nwbP7wYHc9S9KVh1ZKgzeZLMtqmS733IHzMtW55KWqy7pnk0Msvc370uIfD5tMahOnhv2G12Pjdaa3zV7lrCGroTKWhrXD4Wg7jK8r5HNfK80dEX3nqMGPjErZE/NO/5vKTpJKjlAoPzY5eueOgsVqW4zHV6z9GedsvHnbznS3KV90bE3GJG773KPFWntZ0eOs2pU+S7mFT94YvtU+Fpian5NWV7vua+XpygUHKP7S4REBrcP7Dz6e+eL2wT5ShydymqUsFB8XzglPLFd+/8T5dHq/Juk2cWrMsl4z88fKxVkqU2VGpDTuOySHr2fz9vGkm5T2b2nFkhAJzHxPZWS6l+6zObBIKWaepuLPngufypV76uZfO9byJeXs+Zmqm47k5YW8G2Z44FCg3bUGqdEupKfMHr1SvB3yi4fkn5HRzzGfmWC0/K8dui9MJzIaXpGfPqSyHBou+A3Iy9mWFBz6xu1+jV4UmN32C2qlzj14+xXFTvF84KwZt57WV0z1mDb3WI0G9RrWjszRGNplH9kxqeXu5kTNcT09PSq9HEI0e/2HYksCmjvPlr/b/Hqax/rYMcmuUbPvOhh++PQ43JX2Lftuvm75nq1rD/LmGLHuJAXm+fjuN0lWDqCSprvNvJ7x+JB7VO+Z9NiQmU6Dqyd8iB/iVTi0dar587XSj7SnLFjcN21ikPT+vTMTvQNOJK7ZDWgHru2Nev5p5Jndc4e/JUfGWR6/sPuU2jJScJ5PQMb1TKuJPkOfePjY3VRVt0w/Ry+W4pfJkn7tdl3e3V39PpnJnabuSBm7qYfR3HR65egH2/ry8e3UrdvjUXdIRhv8bxFJil2UO3nF+JNzVNeYfCWPf5afs20t6Hfn9szhaW6keYN3OHJXz1t5sMcL14fGXoevFi49caPY2t017vu6Ja4DvSoyyupW+c3dMngRT9r9UdpsnzOjfSa8qh5TsdrE687SN5uNkwLaLmr8ANGLR210TyzJd9q/2+f0iePNvP2PjlIKByXvLlA3lTEun6w27wup0rO/7Yey7d1ps8qqvrUf1oc+O7Q8t2r5bHuro8b3PZ7ftbbSWF59eFprfGZoCpmE9Q83tH+M2BLcbKNottctSokmQ75gM1tZi/w/VqckqSbF1GGaH1dX68cMLPp012ha5Nq2y0sbP1RG5V6dsF5137y2vaf++jbZbGT9vvCgXWz9CT9VpyS09cvzU/Sqty6u6D27tW22fiAvSVoaDDE/FqTPUim53WfsvViFlTdurqbmKuxsUiqvSh5x6tRza9+mkpsrK+/13T41/Hv/7P0zpRf0/2A94cz2w+W+D3Rr6+Ny/npjoCad/JHv8DB0Q/SVttaiccx7S1m6u0DOiQq1tK/+1povd81zsHUsLlw8KWR5QaaL+sHcQ/5DjGTml25Qqfswka31eOwgN90C9cWlU6Xb/kwvaFdV2wLX8eV7bFCN0JqvUfY4Z6vKkIZxEwV32XPnNJwweuntil/HYfuTm5331wFd1CtJTk7b5Yijn/mOYTUJa2KbTMtXWVT7OYBLE2fJ3hneZ2ybVZkH5WilF2fj7QdyBcx1q13I4xI=
*/