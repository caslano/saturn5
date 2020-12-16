 //////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2011-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTERPROCESS_WINDOWS_RECURSIVE_NAMED_MUTEX_HPP
#define BOOST_INTERPROCESS_WINDOWS_RECURSIVE_NAMED_MUTEX_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/sync/windows/named_mutex.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {


class windows_named_recursive_mutex
   //Windows mutexes based on CreateMutex are already recursive...
   : public windows_named_mutex
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //Non-copyable
   windows_named_recursive_mutex();
   windows_named_recursive_mutex(const windows_named_mutex &);
   windows_named_recursive_mutex &operator=(const windows_named_mutex &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   windows_named_recursive_mutex(create_only_t, const char *name, const permissions &perm = permissions())
      : windows_named_mutex(create_only_t(), name, perm)
   {}

   windows_named_recursive_mutex(open_or_create_t, const char *name, const permissions &perm = permissions())
      : windows_named_mutex(open_or_create_t(), name, perm)
   {}

   windows_named_recursive_mutex(open_only_t, const char *name)
      : windows_named_mutex(open_only_t(), name)
   {}
};

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_WINDOWS_RECURSIVE_NAMED_MUTEX_HPP

/* named_recursive_mutex.hpp
vRxyX8sheR+MtzthrJyOKWqeWvrS2qu4QA/XmXvJ7hY2fMxuQyxGW/tSvb0e066xG3a4Qv7eV2+/x9zzbUJW0/fp+0nI6vs+fV9Jeec+qrf8vY9RfkYaz+yj5HMnbTnoKn8bymfKKncAPSbqvyvOSVtd1+03cOb11NTrTE29VsvLmVE++bmLdW4V3EqxJ0NTXjAr7aq8BB5zX79U2QLNnYeflL8v9I3k+vBqlO+SUdGxdo59rE2ZmlEc/3Yt8zmNfx/B8+He5r7P1vcxd07/8mPK+FebZ/o6qrZz9VeT64yBXw63Vthc085xuy/3+7LuOdn9sHseXMqa9QdtcmXVUn3dtISdLtOxQCRRWzdV2XtyZTrQUejrJWWNPDqa1vqeHHW/LeuElv82W91vS/3UupIu/Us9jH5RpDeL6VV5W/U8rE58oheen9WJr/TuheL7x2v/eP8bA78+ufzZIzNnrjuZ3H58q9Nk+Lfc/sBP0r50029W/2XeuXX95zznnYe1vXhVvfLp6nlYnfhuvfOz6nlwnXhzvfO5tidv62mf/Mi9VlOAIaRxm/m33LfdQK59nP2Qf98MNyFD8ozKscVE5e8fUx5Nrxy3U17OEfJ7tNum/A7l7z3K37OUMA+Y38v3lhT8vVnwMyp/71T+3qX8vdv8m5yyPAfI8yMNFm65GxQOukbKZWjkRityzXHkRplyPL+mj3ekIhdmeD3jh8ezYvrwxptyPJ+lT98cRa4ojtzNCidtgHITKady0g7qFOG2GwK8GDgUmAscAcwDFgAHA4cBRwAvA14NvBw4FjgcOIHyht3i6DlbzQfK9XRKP8t7mHJ/pVxfuNcp93t/JP1/AvYWZQaYI8KnPmfxPAD4F+BVIgzgGP5+PfAcnm8E/gM4HtgJ31cLGwGDwB7Ae0QageuAOcCNwF7Ah0V6gQeB2cAG/n5IpBH4DLAf8AeM74fAPKBIe3/gH4EDgH/h7+SU5HkN1B/qq3JKvkZ93wCmA1uA2cC3gUOAvwReBvwV8EPAd4Ain34LnCTsCSwGvgmcwuf3ZX/Icwk8XyHiFXZL5tncVYz3s8A+wLuBlwOPAa8ErgWOAq4DzgTeC5wNXA+8hXKfAG4E3gbcDlwD3AlcD3wQ+HngbmCIz48C9wG/BnwY+DhwP/AI8ADwKPAg8DvAw8CXgV8FvgI8CvwD8CmgsPO3gOeB3wYKJZ8W+gBFOF2ATcDewGeB/YBIL8sp99+z3OnLKeutTU7fDhRRLruV8AKGnHN4tXB1lLuVcuSmlJ/jzLcfA7sBXwL24LOI42XgUGAzcALwp8DJ/P3DwBPAj/D5ZuCrwHnAn9M+BdE9rYDOjL8TXC7jX0NOz3uY3kLuHVXbrSS4QZS/l/LrgXKtRbFHoRLPFIs9QkmKfV3KlShyKf5Yuc1qPriUC7qUq3MpF3IpV6/ILbTITVX7R5dyTS7lml3KtbiUC7uU8z3RulwRvkyj3CG2Z4PhRrM9G8F6MJrt1rXAa8hZ/SE+F5OjegY512cBr2c7NhZYSU7qOuA44GYRL3AnOYgfAk4APkIu4m+Ta/hZcgz/hBzDp8gt/GvgDLZbJcB/A2cBwest4xkGnAu8DngL8EbgbcA5wABwHrACWAasAi4B3g6sBS4Gfg5YDfwCcClwO58x3pT67QMWAxuAk1m/YUCuh2LNlXbMgztLe58mp/AZYDa5h3OAfwbmSzmkmxzEI8k5PJmcw7OBfyeH/j+AleQcribX8BoRPbm/k4C76f8QsAuevwdMoR27A0+Qu/zP5EJPRnp7AXsA04DpwGxgFlBwGPfn9wOBGcARwEzgFGAWcKaUZzuHv5s5HnySdhgo+0rWR3I9b6E=
*/