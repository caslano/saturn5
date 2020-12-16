// Copyright (C) 2000 Stephen Cleary
// Copyright (C) 2008 Ion Gaztanaga
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org for updates, documentation, and revision history.
//
// This file is a modified file from Boost.Pool

//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2007-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_SINGLETON_DETAIL_HPP
#define BOOST_CONTAINER_DETAIL_SINGLETON_DETAIL_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

//
// The following helper classes are placeholders for a generic "singleton"
//  class.  The classes below support usage of singletons, including use in
//  program startup/shutdown code, AS LONG AS there is only one thread
//  running before main() begins, and only one thread running after main()
//  exits.
//
// This class is also limited in that it can only provide singleton usage for
//  classes with default constructors.
//

// The design of this class is somewhat twisted, but can be followed by the
//  calling inheritance.  Let us assume that there is some user code that
//  calls "singleton_default<T>::instance()".  The following (convoluted)
//  sequence ensures that the same function will be called before main():
//    instance() contains a call to create_object.do_nothing()
//    Thus, object_creator is implicitly instantiated, and create_object
//      must exist.
//    Since create_object is a static member, its constructor must be
//      called before main().
//    The constructor contains a call to instance(), thus ensuring that
//      instance() will be called before main().
//    The first time instance() is called (i.e., before main()) is the
//      latest point in program execution where the object of type T
//      can be created.
//    Thus, any call to instance() will auto-magically result in a call to
//      instance() before main(), unless already present.
//  Furthermore, since the instance() function contains the object, instead
//  of the singleton_default class containing a static instance of the
//  object, that object is guaranteed to be constructed (at the latest) in
//  the first call to instance().  This permits calls to instance() from
//  static code, even if that code is called before the file-scope objects
//  in this file have been initialized.

namespace boost {
namespace container {
namespace dtl {

// T must be: no-throw default constructible and no-throw destructible
template <typename T>
struct singleton_default
{
  private:
    struct object_creator
    {
      // This constructor does nothing more than ensure that instance()
      //  is called before main() begins, thus creating the static
      //  T object before multithreading race issues can come up.
      object_creator() { singleton_default<T>::instance(); }
      inline void do_nothing() const { }
    };
    static object_creator create_object;

    singleton_default();

  public:
    typedef T object_type;

    // If, at any point (in user code), singleton_default<T>::instance()
    //  is called, then the following function is instantiated.
    static object_type & instance()
    {
      // This is the object that we return a reference to.
      // It is guaranteed to be created before main() begins because of
      //  the next line.
      static object_type obj;

      // The following line does nothing else than force the instantiation
      //  of singleton_default<T>::create_object, whose constructor is
      //  called before main() begins.
      create_object.do_nothing();

      return obj;
    }
};
template <typename T>
typename singleton_default<T>::object_creator
singleton_default<T>::create_object;

} // namespace dtl
} // namespace container
} // namespace boost

#include <boost/container/detail/config_end.hpp>

#endif   //BOOST_CONTAINER_DETAIL_SINGLETON_DETAIL_HPP

/* singleton.hpp
iczH7Ny1D42DZQi7ZN7492F5ZBYz8757WLHo5fqPHrgUVins7TsvPQpWL3Ka38jDWhKd50ubGJ/5vi+sS9R7/NxLk2Cuc6Pt4PkPxMB8ZLyXu1/cmAiLF3F3rVhZA0sWdu+le5fDMnhOcT8km8wDE/uXPGHmbyiwAmZynhUpVsJ7EcfGShFn/s4Fq1Zy1ipWr1ijYs2KtSrWrlinYt2K9SrWL5bn5f8YvgpmnRe9j5zVc84GWJDMac4nCzu7/fV4WLrIuax46SewPBG31Tp5OKyYDPNzH/3ffGMMVims+Mnl+2D1ZBazbws/jsBayLBcXO7oc6k2MpvZk4NOHALrEXboZW/cCPOcT/WYmb99wvxkvN6RB/3xGSyWzM9sxKBvvt1vGQuTybA/c7tzcsy9UVimo7lc+azeQe7o9+wVMhsgrJjMy4y/965cxJm/QcMqRVzivdNiYbVkNrNHjl7fCmsms5iZZwBgHUovPcoY+pQ4T5Kz+RSLS3KuF1QspFiSMP6tqRTFUsksZo/fuGw9LExmM7tj2jlhWD6Zj5kre/VtsDJhG+OTOmC1qAf7/pvHYU3C5gwb3gZrV8bQKfrk3xjrV+JiLnA2LxnvZVrkoo9hATJeb+ghHcfCQsLumj56OiyVmewzIuqZ+xqwfDIvs0smn1IOKybzMfvihAt3wKpEvffufvw0WIOod8m8K7ywVmHme8mwLmWZ9Yh65m/XMM+F0Zb4x7OfwAJkvN72u77sgiWQsXr8WdI5iWRYLjHuRYvNNgabJMyc88EyyCxm4y5+KgWWTeZhxuvlCTuw/Y2YVcDsYPeooLlegRWR2czu9b8yF1Yh7OxJx46A1SnWIuqZ/SesTcTtKmjYCushs5iZ95TCYiY45/SSOeWMJXPKGSLzMjPnprAUkbP33YNugmUKS9/03hhYnmIlYgzmt0awMhFnfmsEq5Hj23PwHbAmYWa7hXWIema+wLoU61GsTyxPc24K8yZHx5ntD2Yr5lcsVrF4xRIUSySzmE3avnMoLJXMz+zN7xuSYdnCajd2HgMrSXbexsrIbGbHHv/U07AaYdsm3r4X1qRYh6hnrjtgXYr1KMulj5mcn66JzvPTx0zOzyCZU72QYkmKpZA5bbfpope7vvggFZYtbOizLhtWpNQrUepViJyv/ZL/f6sTNu+xpyfAWpR6bYp1KNalWI9ifYq5LnI2j2KWMHPNDPMJM9ewsIBiccL4MS6oWEixJMVSmMn9YCqZ034w7Jgz4/osZoe4Z80zOWG5wv7R2DIblk9mM9sTjrsOVkpmMTPPb8KqyPzMLvjm4UpYk8h50pVPrYZ1CCu9ee0bsD5Rz3fE77/CvBdHj8HsB2E2Gc/Z+lXRb7B4YXl/v3YbLNnRFmZnsHqHuueEzRyEhRXLUixXsXwym5nnrs8/hJUKW1Ay4lhYNZnFzDxviOvbBlbPQ9e3Zk7AmkwcMzPPYO1KXCeZzczcS4D1CzPnDDA7JbqeOdeHxZHxuPKbbhwGSxL2rz/v/hqWLnLmLzn0eFiWiLvpqQu3wAqVuDKlz2rFGsi8zMz1O6xF9PLJjFW/wrqE3XLklS/DXJc4m0/Y3o5xG1y4nibD+jvMHf3d45CJY2bmGSxV2NqXp++DRcgsZsNPuKkblq/UKxQ5N+ZMWAorFzZ2SMl4WK2od2BZ03sHyLDvOZzs2AuOeR/WRWYzW3ffisUw16WUk9mHkd1hmE3Gc047buQQWIJj3IKcFDKM/Qj3ov9+RwWWSuZldlv41cNhmWQ+Zr/+c/gNsHxhP8af0QkrI7OZffyHdyushsxilpDyVAqsUVjHb+cth7UJe6locNL/bGY3G5/XPWeBGR+sl8w=
*/