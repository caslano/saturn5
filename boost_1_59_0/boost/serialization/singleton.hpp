#ifndef BOOST_SERIALIZATION_SINGLETON_HPP
#define BOOST_SERIALIZATION_SINGLETON_HPP

/////////1/////////2///////// 3/////////4/////////5/////////6/////////7/////////8
//  singleton.hpp
//
// Copyright David Abrahams 2006. Original version
//
// Copyright Robert Ramey 2007.  Changes made to permit
// application throughout the serialization library.
//
// Copyright Alexander Grund 2018. Corrections to singleton lifetime
//
// Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// The intention here is to define a template which will convert
// any class into a singleton with the following features:
//
// a) initialized before first use.
// b) thread-safe for const access to the class
// c) non-locking
//
// In order to do this,
// a) Initialize dynamically when used.
// b) Require that all singletons be initialized before main
// is called or any entry point into the shared library is invoked.
// This guarentees no race condition for initialization.
// In debug mode, we assert that no non-const functions are called
// after main is invoked.
//

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/noncopyable.hpp>
#include <boost/serialization/force_include.hpp>
#include <boost/serialization/config.hpp>

#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace serialization {

//////////////////////////////////////////////////////////////////////
// Provides a dynamically-initialized (singleton) instance of T in a
// way that avoids LNK1179 on vc6.  See http://tinyurl.com/ljdp8 or
// http://lists.boost.org/Archives/boost/2006/05/105286.php for
// details.
//

// Singletons created by this code are guaranteed to be unique
// within the executable or shared library which creates them.
// This is sufficient and in fact ideal for the serialization library.
// The singleton is created when the module is loaded and destroyed
// when the module is unloaded.

// This base class has two functions.

// First it provides a module handle for each singleton indicating
// the executable or shared library in which it was created. This
// turns out to be necessary and sufficient to implement the tables
// used by serialization library.

// Second, it provides a mechanism to detect when a non-const function
// is called after initialization.

// Make a singleton to lock/unlock all singletons for alteration.
// The intent is that all singletons created/used by this code
// are to be initialized before main is called. A test program
// can lock all the singletons when main is entered.  Thus any
// attempt to retrieve a mutable instance while locked will
// generate an assertion if compiled for debug.

// The singleton template can be used in 2 ways:
// 1 (Recommended): Publicly inherit your type T from singleton<T>,
// make its ctor protected and access it via T::get_const_instance()
// 2: Simply access singleton<T> without changing T. Note that this only
// provides a global instance accesible by singleton<T>::get_const_instance()
// or singleton<T>::get_mutable_instance() to prevent using multiple instances
// of T make its ctor protected

// Note on usage of BOOST_DLLEXPORT: These functions are in danger of
// being eliminated by the optimizer when building an application in
// release mode. Usage of the macro is meant to signal the compiler/linker
// to avoid dropping these functions which seem to be unreferenced.
// This usage is not related to autolinking.

class BOOST_SYMBOL_VISIBLE singleton_module :
    public boost::noncopyable
{
private:
    BOOST_DLLEXPORT bool & get_lock() BOOST_USED {
        static bool lock = false;
        return lock;
    }

public:
    BOOST_DLLEXPORT void lock(){
        get_lock() = true;
    }
    BOOST_DLLEXPORT void unlock(){
        get_lock() = false;
    }
    BOOST_DLLEXPORT bool is_locked(){
        return get_lock();
    }
};

static inline singleton_module & get_singleton_module(){
    static singleton_module m;
    return m;
}

namespace detail {

// This is the class actually instantiated and hence the real singleton.
// So there will only be one instance of this class. This does not hold
// for singleton<T> as a class derived from singleton<T> could be
// instantiated multiple times.
// It also provides a flag `is_destroyed` which returns true, when the
// class was destructed. It is static and hence accesible even after
// destruction. This can be used to check, if the singleton is still
// accesible e.g. in destructors of other singletons.
template<class T>
class singleton_wrapper : public T
{
    static bool & get_is_destroyed(){
        // Prefer a static function member to avoid LNK1179.
        // Note: As this is for a singleton (1 instance only) it must be set
        // never be reset (to false)!
        static bool is_destroyed_flag = false;
        return is_destroyed_flag;
    }
public:
    singleton_wrapper(){
        BOOST_ASSERT(! is_destroyed());
    }
    ~singleton_wrapper(){
        get_is_destroyed() = true;
    }
    static bool is_destroyed(){
        return get_is_destroyed();
    }
};

} // detail

template <class T>
class singleton {
private:
    static T * m_instance;
    // include this to provoke instantiation at pre-execution time
    static void use(T const &) {}
    static T & get_instance() {
        BOOST_ASSERT(! is_destroyed());

        // use a wrapper so that types T with protected constructors can be used
        // Using a static function member avoids LNK1179
        static detail::singleton_wrapper< T > t;

        // note that the following is absolutely essential.
        // commenting out this statement will cause compilers to fail to
        // construct the instance at pre-execution time.  This would prevent
        // our usage/implementation of "locking" and introduce uncertainty into
        // the sequence of object initialization.
        // Unfortunately, this triggers detectors of undefine behavior
        // and reports an error.  But I've been unable to find a different
        // of guarenteeing that the the singleton is created at pre-main time.
        if (m_instance) use(* m_instance);

        return static_cast<T &>(t);
    }
protected:
    // Do not allow instantiation of a singleton<T>. But we want to allow
    // `class T: public singleton<T>` so we can't delete this ctor
    BOOST_DLLEXPORT singleton(){}

public:
    BOOST_DLLEXPORT static T & get_mutable_instance(){
        BOOST_ASSERT(! get_singleton_module().is_locked());
        return get_instance();
    }
    BOOST_DLLEXPORT static const T & get_const_instance(){
        return get_instance();
    }
    BOOST_DLLEXPORT static bool is_destroyed(){
        return detail::singleton_wrapper< T >::is_destroyed();
    }
};

// Assigning the instance reference to a static member forces initialization
// at startup time as described in
// https://groups.google.com/forum/#!topic/microsoft.public.vc.language/kDVNLnIsfZk
template<class T>
T * singleton< T >::m_instance = & singleton< T >::get_instance();

} // namespace serialization
} // namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_SERIALIZATION_SINGLETON_HPP

/* singleton.hpp
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
*/