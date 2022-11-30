#ifndef BOOST_SERIALIZATION_EXPORT_HPP
#define BOOST_SERIALIZATION_EXPORT_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// export.hpp: set traits of classes to be serialized

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// (C) Copyright 2006 David Abrahams - http://www.boost.org.
// implementation of class export functionality.  This is an alternative to
// "forward declaration" method to provoke instantiation of derived classes
// that are to be serialized through pointers.

#include <utility>
#include <cstddef> // NULL

#include <boost/config.hpp>
#include <boost/static_assert.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/type_traits/is_polymorphic.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/bool_fwd.hpp>

#include <boost/serialization/extended_type_info.hpp> // for guid_defined only
#include <boost/serialization/static_warning.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/force_include.hpp>
#include <boost/serialization/singleton.hpp>

#include <boost/archive/detail/register_archive.hpp>

namespace boost {
namespace archive {
namespace detail {

class basic_pointer_iserializer;
class basic_pointer_oserializer;

template<class Archive, class T>
class pointer_iserializer;
template<class Archive, class T>
class pointer_oserializer;

template <class Archive, class Serializable>
struct export_impl
{
    static const basic_pointer_iserializer &
    enable_load(mpl::true_){
        return boost::serialization::singleton<
            pointer_iserializer<Archive, Serializable>
        >::get_const_instance();
    }

    static const basic_pointer_oserializer &
    enable_save(mpl::true_){
        return boost::serialization::singleton<
            pointer_oserializer<Archive, Serializable>
        >::get_const_instance();
    }
    inline static void enable_load(mpl::false_) {}
    inline static void enable_save(mpl::false_) {}
};

// On many platforms, naming a specialization of this template is
// enough to cause its argument to be instantiated.
template <void(*)()>
struct instantiate_function {};

template <class Archive, class Serializable>
struct ptr_serialization_support
{
# if defined(BOOST_MSVC) || defined(__SUNPRO_CC)
    virtual BOOST_DLLEXPORT void instantiate() BOOST_USED;
# else
    static BOOST_DLLEXPORT void instantiate() BOOST_USED;
    typedef instantiate_function<
        &ptr_serialization_support::instantiate
    > x;
# endif
};

template <class Archive, class Serializable>
BOOST_DLLEXPORT void
ptr_serialization_support<Archive,Serializable>::instantiate()
{
    export_impl<Archive,Serializable>::enable_save(
        typename Archive::is_saving()
    );

    export_impl<Archive,Serializable>::enable_load(
        typename Archive::is_loading()
    );
}

// Note INTENTIONAL usage of anonymous namespace in header.
// This was made this way so that export.hpp could be included
// in other headers.  This is still under study.

namespace extra_detail {

template<class T>
struct guid_initializer
{
    void export_guid(mpl::false_) const {
        // generates the statically-initialized objects whose constructors
        // register the information allowing serialization of T objects
        // through pointers to their base classes.
        instantiate_ptr_serialization((T*)0, 0, adl_tag());
    }
    void export_guid(mpl::true_) const {
    }
    guid_initializer const & export_guid() const {
        BOOST_STATIC_WARNING(boost::is_polymorphic< T >::value);
        // note: exporting an abstract base class will have no effect
        // and cannot be used to instantitiate serialization code
        // (one might be using this in a DLL to instantiate code)
        //BOOST_STATIC_WARNING(! boost::serialization::is_abstract< T >::value);
        export_guid(boost::serialization::is_abstract< T >());
        return *this;
    }
};

template<typename T>
struct init_guid;

} // anonymous
} // namespace detail
} // namespace archive
} // namespace boost

#define BOOST_CLASS_EXPORT_IMPLEMENT(T)                      \
    namespace boost {                                        \
    namespace archive {                                      \
    namespace detail {                                       \
    namespace extra_detail {                                 \
    template<>                                               \
    struct init_guid< T > {                                  \
        static guid_initializer< T > const & g;              \
    };                                                       \
    guid_initializer< T > const & init_guid< T >::g =        \
        ::boost::serialization::singleton<                   \
            guid_initializer< T >                            \
        >::get_mutable_instance().export_guid();             \
    }}}}                                                     \
/**/

#define BOOST_CLASS_EXPORT_KEY2(T, K)          \
namespace boost {                              \
namespace serialization {                      \
template<>                                     \
struct guid_defined< T > : boost::mpl::true_ {}; \
template<>                                     \
inline const char * guid< T >(){                 \
    return K;                                  \
}                                              \
} /* serialization */                          \
} /* boost */                                  \
/**/

#define BOOST_CLASS_EXPORT_KEY(T)                                      \
    BOOST_CLASS_EXPORT_KEY2(T, BOOST_PP_STRINGIZE(T))                                                                  \
/**/

#define BOOST_CLASS_EXPORT_GUID(T, K)                                  \
BOOST_CLASS_EXPORT_KEY2(T, K)                                          \
BOOST_CLASS_EXPORT_IMPLEMENT(T)                                        \
/**/

#if BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3205))

// CodeWarrior fails to construct static members of class templates
// when they are instantiated from within templates, so on that
// compiler we ask users to specifically register base/derived class
// relationships for exported classes.  On all other compilers, use of
// this macro is entirely optional.
# define BOOST_SERIALIZATION_MWERKS_BASE_AND_DERIVED(Base,Derived)             \
namespace {                                                                    \
  static int BOOST_PP_CAT(boost_serialization_mwerks_init_, __LINE__) =        \
  (::boost::archive::detail::instantiate_ptr_serialization((Derived*)0,0), 3); \
  static int BOOST_PP_CAT(boost_serialization_mwerks_init2_, __LINE__) = (     \
      ::boost::serialization::void_cast_register((Derived*)0,(Base*)0)         \
    , 3);                                                                      \
}

#else

# define BOOST_SERIALIZATION_MWERKS_BASE_AND_DERIVED(Base,Derived)

#endif

// check for unnecessary export.  T isn't polymorphic so there is no
// need to export it.
#define BOOST_CLASS_EXPORT_CHECK(T)                              \
    BOOST_STATIC_WARNING(                                        \
        boost::is_polymorphic<U>::value                          \
    );                                                           \
    /**/

// the default exportable class identifier is the class name
// the default list of archives types for which code id generated
// are the originally included with this serialization system
#define BOOST_CLASS_EXPORT(T)                   \
    BOOST_CLASS_EXPORT_GUID(                    \
        T,                                      \
        BOOST_PP_STRINGIZE(T)                   \
    )                                           \
    /**/

#endif // BOOST_SERIALIZATION_EXPORT_HPP


/* export.hpp
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
*/