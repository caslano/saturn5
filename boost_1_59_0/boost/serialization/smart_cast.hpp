#ifndef BOOST_SERIALIZATION_SMART_CAST_HPP
#define BOOST_SERIALIZATION_SMART_CAST_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// smart_cast.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/serialization for updates, documentation, and revision history.

// casting of pointers and references.

// In casting between different C++ classes, there are a number of
// rules that have to be kept in mind in deciding whether to use
// static_cast or dynamic_cast.

// a) dynamic casting can only be applied when one of the types is polymorphic
// Otherwise static_cast must be used.
// b) only dynamic casting can do runtime error checking
// use of static_cast is generally un checked even when compiled for debug
// c) static_cast would be considered faster than dynamic_cast.

// If casting is applied to a template parameter, there is no apriori way
// to know which of the two casting methods will be permitted or convenient.

// smart_cast uses C++ type_traits, and program debug mode to select the
// most convenient cast to use.

#include <exception>
#include <typeinfo>
#include <cstddef> // NULL

#include <boost/config.hpp>
#include <boost/static_assert.hpp>

#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/type_traits/is_polymorphic.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/identity.hpp>

#include <boost/serialization/throw_exception.hpp>

namespace boost {
namespace serialization {
namespace smart_cast_impl {

    template<class T>
    struct reference {

        struct polymorphic {

            struct linear {
                template<class U>
                 static T cast(U & u){
                    return static_cast< T >(u);
                }
            };

            struct cross {
                 template<class U>
                static T cast(U & u){
                    return dynamic_cast< T >(u);
                }
            };

            template<class U>
            static T cast(U & u){
                // if we're in debug mode
                #if ! defined(NDEBUG)                               \
                || defined(__MWERKS__)
                    // do a checked dynamic cast
                    return cross::cast(u);
                #else
                    // borland 5.51 chokes here so we can't use it
                    // note: if remove_reference isn't function for these types
                    // cross casting will be selected this will work but will
                    // not be the most efficient method. This will conflict with
                    // the original smart_cast motivation.
                    typedef typename mpl::eval_if<
                            typename mpl::and_<
                                mpl::not_<is_base_and_derived<
                                    typename remove_reference< T >::type,
                                    U
                                > >,
                                mpl::not_<is_base_and_derived<
                                    U,
                                    typename remove_reference< T >::type
                                > >
                            >,
                            // borland chokes w/o full qualification here
                            mpl::identity<cross>,
                            mpl::identity<linear>
                    >::type typex;
                    // typex works around gcc 2.95 issue
                    return typex::cast(u);
                #endif
            }
        };

        struct non_polymorphic {
            template<class U>
             static T cast(U & u){
                return static_cast< T >(u);
            }
        };
        template<class U>
        static T cast(U & u){
            typedef typename mpl::eval_if<
                boost::is_polymorphic<U>,
                mpl::identity<polymorphic>,
                mpl::identity<non_polymorphic>
            >::type typex;
            return typex::cast(u);
        }
    };

    template<class T>
    struct pointer {

        struct polymorphic {
            // unfortunately, this below fails to work for virtual base
            // classes.  need has_virtual_base to do this.
            // Subject for further study
            #if 0
            struct linear {
                template<class U>
                 static T cast(U * u){
                    return static_cast< T >(u);
                }
            };

            struct cross {
                template<class U>
                static T cast(U * u){
                    T tmp = dynamic_cast< T >(u);
                    #ifndef NDEBUG
                        if ( tmp == 0 ) throw_exception(std::bad_cast());
                    #endif
                    return tmp;
                }
            };

            template<class U>
            static T cast(U * u){
                typedef
                    typename mpl::eval_if<
                        typename mpl::and_<
                            mpl::not_<is_base_and_derived<
                                typename remove_pointer< T >::type,
                                U
                            > >,
                            mpl::not_<is_base_and_derived<
                                U,
                                typename remove_pointer< T >::type
                            > >
                        >,
                        // borland chokes w/o full qualification here
                        mpl::identity<cross>,
                        mpl::identity<linear>
                    >::type typex;
                return typex::cast(u);
            }
            #else
            template<class U>
            static T cast(U * u){
                T tmp = dynamic_cast< T >(u);
                #ifndef NDEBUG
                    if ( tmp == 0 ) throw_exception(std::bad_cast());
                #endif
                return tmp;
            }
            #endif
        };

        struct non_polymorphic {
            template<class U>
             static T cast(U * u){
                return static_cast< T >(u);
            }
        };

        template<class U>
        static T cast(U * u){
            typedef typename mpl::eval_if<
                boost::is_polymorphic<U>,
                mpl::identity<polymorphic>,
                mpl::identity<non_polymorphic>
            >::type typex;
            return typex::cast(u);
        }

    };

    template<class TPtr>
    struct void_pointer {
        template<class UPtr>
        static TPtr cast(UPtr uptr){
            return static_cast<TPtr>(uptr);
        }
    };

    template<class T>
    struct error {
        // if we get here, its because we are using one argument in the
        // cast on a system which doesn't support partial template
        // specialization
        template<class U>
        static T cast(U){
            BOOST_STATIC_ASSERT(sizeof(T)==0);
            return * static_cast<T *>(NULL);
        }
    };

} // smart_cast_impl

// this implements:
// smart_cast<Target *, Source *>(Source * s)
// smart_cast<Target &, Source &>(s)
// note that it will fail with
// smart_cast<Target &>(s)
template<class T, class U>
T smart_cast(U u) {
    typedef
        typename mpl::eval_if<
            typename mpl::or_<
                boost::is_same<void *, U>,
                boost::is_same<void *, T>,
                boost::is_same<const void *, U>,
                boost::is_same<const void *, T>
            >,
            mpl::identity<smart_cast_impl::void_pointer< T > >,
        // else
        typename mpl::eval_if<boost::is_pointer<U>,
            mpl::identity<smart_cast_impl::pointer< T > >,
        // else
        typename mpl::eval_if<boost::is_reference<U>,
            mpl::identity<smart_cast_impl::reference< T > >,
        // else
            mpl::identity<smart_cast_impl::error< T >
        >
        >
        >
        >::type typex;
    return typex::cast(u);
}

// this implements:
// smart_cast_reference<Target &>(Source & s)
template<class T, class U>
T smart_cast_reference(U & u) {
    return smart_cast_impl::reference< T >::cast(u);
}

} // namespace serialization
} // namespace boost

#endif // BOOST_SERIALIZATION_SMART_CAST_HPP

/* smart_cast.hpp
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
*/