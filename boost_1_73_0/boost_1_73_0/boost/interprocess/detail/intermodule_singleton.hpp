//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2009-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_INTERMODULE_SINGLETON_HPP
#define BOOST_INTERPROCESS_INTERMODULE_SINGLETON_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#ifdef BOOST_INTERPROCESS_WINDOWS
   #include <boost/interprocess/detail/windows_intermodule_singleton.hpp>
#else
   #include <boost/interprocess/detail/portable_intermodule_singleton.hpp>
#endif

namespace boost{
namespace interprocess{
namespace ipcdetail{

//Now this class is a singleton, initializing the singleton in
//the first get() function call if LazyInit is false. If true
//then the singleton will be initialized when loading the module.
template<typename C, bool LazyInit = true, bool Phoenix = false>
class intermodule_singleton
   #ifdef BOOST_INTERPROCESS_WINDOWS
   : public windows_intermodule_singleton<C, LazyInit, Phoenix>
   #else
   : public portable_intermodule_singleton<C, LazyInit, Phoenix>
   #endif
{};

}  //namespace ipcdetail{
}  //namespace interprocess{
}  //namespace boost{

#include <boost/interprocess/detail/config_end.hpp>

#endif

/* intermodule_singleton.hpp
XCvGYblQTsZape6AEV/kuV8OylRWAFVTVhAmshkD+YFDwjYjNhhG8xRW6iH8JEqS9LyISMrlq7wmRGSJObVPsYLoml759SCPdCSi6O6TMu7XzGWQ54VgnuCg05C1iUHfyDHBmFfb+CXDYA86vaOXbglR8Xx5mc/2P+Wf0kmwuZC0MjdX50gaslfs5d5eadveEXYLcbGfnLNXEh60qkWXb94Yfl7FhUPk+JaAH4ZyAJMewFgLMuFPo7xN7BYOO5VJORQCljCDs+CpjOvKxM4TT27t6zkjDYjGRN8BUV/uguAr3sOJ+Pn8sX04a4F1HN8aeFXt3MEBstfLtSPMAsIuKknVIXC7N6TAiOd2SCCZ7XsdMNqb1iGpD8oJpEiLtTrFZLAnH/b+OGy3hJ/Z2o5DacumzmPrRgjcKIFpt4D+b1BeW/BK8neUUifhHSFrJ+eNmPnReUfA8py9EW190N4RsHYw34yZn8x3RSzP8Zv3pX6Q33Vzmof/jdit0/+O6G++GdTLRW3se5Pfm74mNDUMk4A3vyO0kLZ/cuiE2gXDOOlUxShUfTo0zjY7qDXy5F8k3ikiXSV0t3pS9MlaGdkqoD3dfKiAjrr94TIa4XdoLD5cwLaQ+j+E/Wop669pv1pM9UXuv0paN8R/AVBL
*/