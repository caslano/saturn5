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
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
*/