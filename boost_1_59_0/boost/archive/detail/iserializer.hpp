#ifndef BOOST_ARCHIVE_DETAIL_ISERIALIZER_HPP
#define BOOST_ARCHIVE_DETAIL_ISERIALIZER_HPP

// MS compatible compilers support #pragma once
#if defined(BOOST_MSVC)
# pragma once
#if !defined(__clang__)
#pragma inline_depth(255)
#pragma inline_recursion(on)
#endif
#endif

#if defined(__MWERKS__)
#pragma inline_depth(255)
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// iserializer.hpp: interface for serialization system.

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <new>     // for placement new
#include <cstddef> // size_t, NULL

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::size_t;
} // namespace std
#endif

#include <boost/static_assert.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/greater_equal.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/core/no_exceptions_support.hpp>

#ifndef BOOST_SERIALIZATION_DEFAULT_TYPE_INFO
    #include <boost/serialization/extended_type_info_typeid.hpp>
#endif
#include <boost/serialization/throw_exception.hpp>
#include <boost/serialization/smart_cast.hpp>
#include <boost/serialization/static_warning.hpp>

#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_enum.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_extent.hpp>
#include <boost/type_traits/is_polymorphic.hpp>

#include <boost/serialization/assume_abstract.hpp>

#if !defined(BOOST_MSVC) && \
    (BOOST_WORKAROUND(__IBMCPP__, < 1210) || \
    defined(__SUNPRO_CC) && (__SUNPRO_CC < 0x590))
    #define BOOST_SERIALIZATION_DONT_USE_HAS_NEW_OPERATOR 1
#else
    #define BOOST_SERIALIZATION_DONT_USE_HAS_NEW_OPERATOR 0
#endif

#if ! BOOST_SERIALIZATION_DONT_USE_HAS_NEW_OPERATOR
#include <boost/type_traits/has_new_operator.hpp>
#endif

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/level.hpp>
#include <boost/serialization/tracking.hpp>
#include <boost/serialization/type_info_implementation.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/void_cast.hpp>
#include <boost/serialization/collection_size_type.hpp>
#include <boost/serialization/singleton.hpp>
#include <boost/serialization/wrapper.hpp>
#include <boost/serialization/array_wrapper.hpp>

// the following is need only for dynamic cast of polymorphic pointers
#include <boost/archive/archive_exception.hpp>
#include <boost/archive/detail/basic_iarchive.hpp>
#include <boost/archive/detail/basic_iserializer.hpp>
#include <boost/archive/detail/basic_pointer_iserializer.hpp>
#include <boost/archive/detail/archive_serializer_map.hpp>
#include <boost/archive/detail/check.hpp>

#include <boost/core/addressof.hpp>

namespace boost {

namespace serialization {
    class extended_type_info;
} // namespace serialization

namespace archive {

// an accessor to permit friend access to archives.  Needed because
// some compilers don't handle friend templates completely
class load_access {
public:
    template<class Archive, class T>
    static void load_primitive(Archive &ar, T &t){
        ar.load(t);
    }
};

namespace detail {

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

template<class Archive, class T>
class iserializer : public basic_iserializer
{
private:
    void destroy(/*const*/ void *address) const BOOST_OVERRIDE {
        boost::serialization::access::destroy(static_cast<T *>(address));
    }
public:
    explicit iserializer() :
        basic_iserializer(
            boost::serialization::singleton<
                typename
                boost::serialization::type_info_implementation< T >::type
            >::get_const_instance()
        )
    {}
    BOOST_DLLEXPORT void load_object_data(
        basic_iarchive & ar,
        void *x,
        const unsigned int file_version
    ) const BOOST_OVERRIDE BOOST_USED;
    bool class_info() const BOOST_OVERRIDE {
        return boost::serialization::implementation_level< T >::value
            >= boost::serialization::object_class_info;
    }
    bool tracking(const unsigned int /* flags */) const BOOST_OVERRIDE {
        return boost::serialization::tracking_level< T >::value
                == boost::serialization::track_always
            || ( boost::serialization::tracking_level< T >::value
                == boost::serialization::track_selectively
                && serialized_as_pointer());
    }
    version_type version() const BOOST_OVERRIDE {
        return version_type(::boost::serialization::version< T >::value);
    }
    bool is_polymorphic() const BOOST_OVERRIDE {
        return boost::is_polymorphic< T >::value;
    }
    ~iserializer() BOOST_OVERRIDE {}
};

#ifdef BOOST_MSVC
#  pragma warning(pop)
#endif

template<class Archive, class T>
BOOST_DLLEXPORT void iserializer<Archive, T>::load_object_data(
    basic_iarchive & ar,
    void *x,
    const unsigned int file_version
) const {
    // note: we now comment this out. Before we permited archive
    // version # to be very large.  Now we don't.  To permit
    // readers of these old archives, we have to suppress this
    // code.  Perhaps in the future we might re-enable it but
    // permit its suppression with a runtime switch.
    #if 0
    // trap case where the program cannot handle the current version
    if(file_version > static_cast<const unsigned int>(version()))
        boost::serialization::throw_exception(
            archive::archive_exception(
                boost::archive::archive_exception::unsupported_class_version,
                get_debug_info()
            )
        );
    #endif
    // make sure call is routed through the higest interface that might
    // be specialized by the user.
    boost::serialization::serialize_adl(
        boost::serialization::smart_cast_reference<Archive &>(ar),
        * static_cast<T *>(x),
        file_version
    );
}

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

// the purpose of this code is to allocate memory for an object
// without requiring the constructor to be called.  Presumably
// the allocated object will be subsequently initialized with
// "placement new".
// note: we have the boost type trait has_new_operator but we
// have no corresponding has_delete_operator.  So we presume
// that the former being true would imply that the a delete
// operator is also defined for the class T.

template<class T>
struct heap_allocation {
    // boost::has_new_operator< T > doesn't work on these compilers
    #if BOOST_SERIALIZATION_DONT_USE_HAS_NEW_OPERATOR
        // This doesn't handle operator new overload for class T
        static T * invoke_new(){
            return static_cast<T *>(operator new(sizeof(T)));
        }
        static void invoke_delete(T *t){
            (operator delete(t));
        }
    #else
        // note: we presume that a true value for has_new_operator
        // implies the existence of a class specific delete operator as well
        // as a class specific new operator.
        struct has_new_operator {
            static T * invoke_new() {
                return static_cast<T *>((T::operator new)(sizeof(T)));
            }
            static void invoke_delete(T * t) {
                // if compilation fails here, the likely cause that the class
                // T has a class specific new operator but no class specific
                // delete operator which matches the following signature.
                // note that this solution addresses the issue that two
                // possible signatures.  But it doesn't address the possibility
                // that the class might have class specific new with NO
                // class specific delete at all.  Patches (compatible with
                // C++03) welcome!
                (operator delete)(t);
            }
        };
        struct doesnt_have_new_operator {
            static T* invoke_new() {
                return static_cast<T *>(operator new(sizeof(T)));
            }
            static void invoke_delete(T * t) {
                // Note: I'm reliance upon automatic conversion from T * to void * here
                (operator delete)(t);
            }
        };
        static T * invoke_new() {
            typedef typename
                mpl::eval_if<
                    boost::has_new_operator< T >,
                    mpl::identity<has_new_operator >,
                    mpl::identity<doesnt_have_new_operator >
                >::type typex;
            return typex::invoke_new();
        }
        static void invoke_delete(T *t) {
            typedef typename
                mpl::eval_if<
                    boost::has_new_operator< T >,
                    mpl::identity<has_new_operator >,
                    mpl::identity<doesnt_have_new_operator >
                >::type typex;
            typex::invoke_delete(t);
        }
    #endif
    explicit heap_allocation(){
        m_p = invoke_new();
    }
    ~heap_allocation(){
        if (0 != m_p)
            invoke_delete(m_p);
    }
    T* get() const {
        return m_p;
    }

    T* release() {
        T* p = m_p;
        m_p = 0;
        return p;
    }
private:
    T* m_p;
};

template<class Archive, class T>
class pointer_iserializer :
    public basic_pointer_iserializer
{
private:
    void * heap_allocation() const BOOST_OVERRIDE {
        detail::heap_allocation<T> h;
        T * t = h.get();
        h.release();
        return t;
    }
    const basic_iserializer & get_basic_serializer() const BOOST_OVERRIDE {
        return boost::serialization::singleton<
            iserializer<Archive, T>
        >::get_const_instance();
    }
    BOOST_DLLEXPORT void load_object_ptr(
        basic_iarchive & ar,
        void * x,
        const unsigned int file_version
    ) const BOOST_OVERRIDE BOOST_USED;
public:
    // this should alway be a singleton so make the constructor protected
    pointer_iserializer();
    ~pointer_iserializer() BOOST_OVERRIDE;
};

#ifdef BOOST_MSVC
#  pragma warning(pop)
#endif

// note: BOOST_DLLEXPORT is so that code for polymorphic class
// serialized only through base class won't get optimized out
template<class Archive, class T>
BOOST_DLLEXPORT void pointer_iserializer<Archive, T>::load_object_ptr(
    basic_iarchive & ar,
    void * t,
    const unsigned int file_version
) const
{
    Archive & ar_impl =
        boost::serialization::smart_cast_reference<Archive &>(ar);

    // note that the above will throw std::bad_alloc if the allocation
    // fails so we don't have to address this contingency here.

    // catch exception during load_construct_data so that we don't
    // automatically delete the t which is most likely not fully
    // constructed
    BOOST_TRY {
        // this addresses an obscure situation that occurs when
        // load_constructor de-serializes something through a pointer.
        ar.next_object_pointer(t);
        boost::serialization::load_construct_data_adl<Archive, T>(
            ar_impl,
            static_cast<T *>(t),
            file_version
        );
    }
    BOOST_CATCH(...){
        // if we get here the load_construct failed.  The heap_allocation
        // will be automatically deleted so we don't have to do anything
        // special here.
        BOOST_RETHROW;
    }
    BOOST_CATCH_END

    ar_impl >> boost::serialization::make_nvp(NULL, * static_cast<T *>(t));
}

template<class Archive, class T>
pointer_iserializer<Archive, T>::pointer_iserializer() :
    basic_pointer_iserializer(
        boost::serialization::singleton<
            typename
            boost::serialization::type_info_implementation< T >::type
        >::get_const_instance()
    )
{
    boost::serialization::singleton<
        iserializer<Archive, T>
    >::get_mutable_instance().set_bpis(this);
    archive_serializer_map<Archive>::insert(this);
}

template<class Archive, class T>
pointer_iserializer<Archive, T>::~pointer_iserializer(){
    archive_serializer_map<Archive>::erase(this);
}

template<class Archive>
struct load_non_pointer_type {
    // note this bounces the call right back to the archive
    // with no runtime overhead
    struct load_primitive {
        template<class T>
        static void invoke(Archive & ar, T & t){
            load_access::load_primitive(ar, t);
        }
    };
    // note this bounces the call right back to the archive
    // with no runtime overhead
    struct load_only {
        template<class T>
        static void invoke(Archive & ar, const T & t){
            // short cut to user's serializer
            // make sure call is routed through the higest interface that might
            // be specialized by the user.
            boost::serialization::serialize_adl(
                ar,
                const_cast<T &>(t),
                boost::serialization::version< T >::value
            );
        }
    };

    // note this save class information including version
    // and serialization level to the archive
    struct load_standard {
        template<class T>
        static void invoke(Archive &ar, const T & t){
            void * x = boost::addressof(const_cast<T &>(t));
            ar.load_object(
                x,
                boost::serialization::singleton<
                    iserializer<Archive, T>
                >::get_const_instance()
            );
        }
    };

    struct load_conditional {
        template<class T>
        static void invoke(Archive &ar, T &t){
            //if(0 == (ar.get_flags() & no_tracking))
                load_standard::invoke(ar, t);
            //else
            //    load_only::invoke(ar, t);
        }
    };

    template<class T>
    static void invoke(Archive & ar, T &t){
        typedef typename mpl::eval_if<
                // if its primitive
                mpl::equal_to<
                    boost::serialization::implementation_level< T >,
                    mpl::int_<boost::serialization::primitive_type>
                >,
                mpl::identity<load_primitive>,
            // else
            typename mpl::eval_if<
            // class info / version
            mpl::greater_equal<
                        boost::serialization::implementation_level< T >,
                        mpl::int_<boost::serialization::object_class_info>
                    >,
            // do standard load
            mpl::identity<load_standard>,
        // else
        typename mpl::eval_if<
            // no tracking
                    mpl::equal_to<
                        boost::serialization::tracking_level< T >,
                        mpl::int_<boost::serialization::track_never>
                >,
                // do a fast load
                mpl::identity<load_only>,
            // else
            // do a fast load only tracking is turned off
            mpl::identity<load_conditional>
        > > >::type typex;
        check_object_versioning< T >();
        check_object_level< T >();
        typex::invoke(ar, t);
    }
};

template<class Archive>
struct load_pointer_type {
    struct abstract
    {
        template<class T>
        static const basic_pointer_iserializer * register_type(Archive & /* ar */){
            // it has? to be polymorphic
            BOOST_STATIC_ASSERT(boost::is_polymorphic< T >::value);
            return static_cast<basic_pointer_iserializer *>(NULL);
         }
    };

    struct non_abstract
    {
        template<class T>
        static const basic_pointer_iserializer * register_type(Archive & ar){
            return ar.register_type(static_cast<T *>(NULL));
        }
    };

    template<class T>
    static const basic_pointer_iserializer * register_type(Archive &ar, const T* const /*t*/){
        // there should never be any need to load an abstract polymorphic
        // class pointer.  Inhibiting code generation for this
        // permits abstract base classes to be used - note: exception
        // virtual serialize functions used for plug-ins
        typedef typename
            mpl::eval_if<
                boost::serialization::is_abstract<const T>,
                boost::mpl::identity<abstract>,
                boost::mpl::identity<non_abstract>
            >::type typex;
        return typex::template register_type< T >(ar);
    }

    template<class T>
    static T * pointer_tweak(
        const boost::serialization::extended_type_info & eti,
        void const * const t,
        const T &
    ) {
        // tweak the pointer back to the base class
        void * upcast = const_cast<void *>(
            boost::serialization::void_upcast(
                eti,
                boost::serialization::singleton<
                    typename
                    boost::serialization::type_info_implementation< T >::type
                >::get_const_instance(),
                t
            )
        );
        if(NULL == upcast)
            boost::serialization::throw_exception(
                archive_exception(archive_exception::unregistered_class)
            );
        return static_cast<T *>(upcast);
    }

    template<class T>
    static void check_load(T * const /* t */){
        check_pointer_level< T >();
        check_pointer_tracking< T >();
    }

    static const basic_pointer_iserializer *
    find(const boost::serialization::extended_type_info & type){
        return static_cast<const basic_pointer_iserializer *>(
            archive_serializer_map<Archive>::find(type)
        );
    }

    template<class Tptr>
    static void invoke(Archive & ar, Tptr & t){
        check_load(t);
        const basic_pointer_iserializer * bpis_ptr = register_type(ar, t);
        const basic_pointer_iserializer * newbpis_ptr = ar.load_pointer(
            // note major hack here !!!
            // I tried every way to convert Tptr &t (where Tptr might
            // include const) to void * &.  This is the only way
            // I could make it work. RR
            (void * & )t,
            bpis_ptr,
            find
        );
        // if the pointer isn't that of the base class
        if(newbpis_ptr != bpis_ptr){
            t = pointer_tweak(newbpis_ptr->get_eti(), t, *t);
        }
    }
};

template<class Archive>
struct load_enum_type {
    template<class T>
    static void invoke(Archive &ar, T &t){
        // convert integers to correct enum to load
        int i;
        ar >> boost::serialization::make_nvp(NULL, i);
        t = static_cast< T >(i);
    }
};

template<class Archive>
struct load_array_type {
    template<class T>
    static void invoke(Archive &ar, T &t){
        typedef typename remove_extent< T >::type value_type;

        // convert integers to correct enum to load
        // determine number of elements in the array. Consider the
        // fact that some machines will align elements on boundaries
        // other than characters.
        std::size_t current_count = sizeof(t) / (
            static_cast<char *>(static_cast<void *>(&t[1]))
            - static_cast<char *>(static_cast<void *>(&t[0]))
        );
        boost::serialization::collection_size_type count;
        ar >> BOOST_SERIALIZATION_NVP(count);
        if(static_cast<std::size_t>(count) > current_count)
            boost::serialization::throw_exception(
                archive::archive_exception(
                    boost::archive::archive_exception::array_size_too_short
                )
            );
        // explict template arguments to pass intel C++ compiler
        ar >> serialization::make_array<
            value_type,
            boost::serialization::collection_size_type
        >(
            static_cast<value_type *>(&t[0]),
            count
        );
    }
};

} // detail

template<class Archive, class T>
inline void load(Archive & ar, T &t){
    // if this assertion trips. It means we're trying to load a
    // const object with a compiler that doesn't have correct
    // function template ordering.  On other compilers, this is
    // handled below.
    detail::check_const_loading< T >();
    typedef
        typename mpl::eval_if<is_pointer< T >,
            mpl::identity<detail::load_pointer_type<Archive> >
        ,//else
        typename mpl::eval_if<is_array< T >,
            mpl::identity<detail::load_array_type<Archive> >
        ,//else
        typename mpl::eval_if<is_enum< T >,
            mpl::identity<detail::load_enum_type<Archive> >
        ,//else
            mpl::identity<detail::load_non_pointer_type<Archive> >
        >
        >
        >::type typex;
    typex::invoke(ar, t);
}

} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_DETAIL_ISERIALIZER_HPP

/* iserializer.hpp
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
*/