#ifndef BOOST_ARCHIVE_OSERIALIZER_HPP
#define BOOST_ARCHIVE_OSERIALIZER_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#pragma inline_depth(511)
#pragma inline_recursion(on)
#endif

#if defined(__MWERKS__)
#pragma inline_depth(511)
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// oserializer.hpp: interface for serialization system.

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/assert.hpp>
#include <cstddef> // NULL

#include <boost/config.hpp>

#include <boost/static_assert.hpp>
#include <boost/detail/workaround.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/greater_equal.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/bool_fwd.hpp>

#ifndef BOOST_SERIALIZATION_DEFAULT_TYPE_INFO
    #include <boost/serialization/extended_type_info_typeid.hpp>
#endif
#include <boost/serialization/throw_exception.hpp>
#include <boost/serialization/smart_cast.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/static_warning.hpp>

#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_enum.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_polymorphic.hpp>
#include <boost/type_traits/remove_extent.hpp>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/level.hpp>
#include <boost/serialization/tracking.hpp>
#include <boost/serialization/type_info_implementation.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/void_cast.hpp>
#include <boost/serialization/collection_size_type.hpp>
#include <boost/serialization/array_wrapper.hpp>

#include <boost/serialization/singleton.hpp>

#include <boost/archive/archive_exception.hpp>
#include <boost/archive/detail/basic_oarchive.hpp>
#include <boost/archive/detail/basic_oserializer.hpp>
#include <boost/archive/detail/basic_pointer_oserializer.hpp>
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
class save_access {
public:
    template<class Archive>
    static void end_preamble(Archive & ar){
        ar.end_preamble();
    }
    template<class Archive, class T>
    static void save_primitive(Archive & ar, const  T & t){
        ar.end_preamble();
        ar.save(t);
    }
};

namespace detail {

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

template<class Archive, class T>
class oserializer : public basic_oserializer
{
private:
    // private constructor to inhibit any existence other than the
    // static one
public:
    explicit BOOST_DLLEXPORT oserializer() :
        basic_oserializer(
            boost::serialization::singleton<
                typename
                boost::serialization::type_info_implementation< T >::type
            >::get_const_instance()
        )
    {}
    virtual BOOST_DLLEXPORT void save_object_data(
        basic_oarchive & ar,
        const void *x
    ) const BOOST_USED;
    virtual bool class_info() const {
        return boost::serialization::implementation_level< T >::value
            >= boost::serialization::object_class_info;
    }
    virtual bool tracking(const unsigned int /* flags */) const {
        return boost::serialization::tracking_level< T >::value == boost::serialization::track_always
            || (boost::serialization::tracking_level< T >::value == boost::serialization::track_selectively
                && serialized_as_pointer());
    }
    virtual version_type version() const {
        return version_type(::boost::serialization::version< T >::value);
    }
    virtual bool is_polymorphic() const {
        return boost::is_polymorphic< T >::value;
    }
    virtual ~oserializer(){}
};

#ifdef BOOST_MSVC
#  pragma warning(pop)
#endif

template<class Archive, class T>
BOOST_DLLEXPORT void oserializer<Archive, T>::save_object_data(
    basic_oarchive & ar,
    const void *x
) const {
    // make sure call is routed through the highest interface that might
    // be specialized by the user.
    BOOST_STATIC_ASSERT(boost::is_const< T >::value == false);
    boost::serialization::serialize_adl(
        boost::serialization::smart_cast_reference<Archive &>(ar),
        * static_cast<T *>(const_cast<void *>(x)),
        version()
    );
}

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

template<class Archive, class T>
class pointer_oserializer :
    public basic_pointer_oserializer
{
private:
    const basic_oserializer &
    get_basic_serializer() const {
        return boost::serialization::singleton<
            oserializer<Archive, T>
        >::get_const_instance();
    }
    virtual BOOST_DLLEXPORT void save_object_ptr(
        basic_oarchive & ar,
        const void * x
    ) const BOOST_USED;
public:
    pointer_oserializer();
    ~pointer_oserializer();
};

#ifdef BOOST_MSVC
#  pragma warning(pop)
#endif

template<class Archive, class T>
BOOST_DLLEXPORT void pointer_oserializer<Archive, T>::save_object_ptr(
    basic_oarchive & ar,
    const void * x
) const {
    BOOST_ASSERT(NULL != x);
    // make sure call is routed through the highest interface that might
    // be specialized by the user.
    T * t = static_cast<T *>(const_cast<void *>(x));
    const unsigned int file_version = boost::serialization::version< T >::value;
    Archive & ar_impl
        = boost::serialization::smart_cast_reference<Archive &>(ar);
    boost::serialization::save_construct_data_adl<Archive, T>(
        ar_impl,
        t,
        file_version
    );
    ar_impl << boost::serialization::make_nvp(NULL, * t);
}

template<class Archive, class T>
pointer_oserializer<Archive, T>::pointer_oserializer() :
    basic_pointer_oserializer(
        boost::serialization::singleton<
            typename
            boost::serialization::type_info_implementation< T >::type
        >::get_const_instance()
    )
{
    // make sure appropriate member function is instantiated
    boost::serialization::singleton<
        oserializer<Archive, T>
    >::get_mutable_instance().set_bpos(this);
    archive_serializer_map<Archive>::insert(this);
}

template<class Archive, class T>
pointer_oserializer<Archive, T>::~pointer_oserializer(){
    archive_serializer_map<Archive>::erase(this);
}

template<class Archive>
struct save_non_pointer_type {
    // note this bounces the call right back to the archive
    // with no runtime overhead
    struct save_primitive {
        template<class T>
        static void invoke(Archive & ar, const T & t){
            save_access::save_primitive(ar, t);
        }
    };
    // same as above but passes through serialization
    struct save_only {
        template<class T>
        static void invoke(Archive & ar, const T & t){
            // make sure call is routed through the highest interface that might
            // be specialized by the user.
            boost::serialization::serialize_adl(
                ar,
                const_cast<T &>(t),
                ::boost::serialization::version< T >::value
            );
        }
    };
    // adds class information to the archive. This includes
    // serialization level and class version
    struct save_standard {
        template<class T>
        static void invoke(Archive &ar, const T & t){
            ar.save_object(
                boost::addressof(t),
                boost::serialization::singleton<
                    oserializer<Archive, T>
                >::get_const_instance()
            );
        }
    };



    // adds class information to the archive. This includes
    // serialization level and class version
    struct save_conditional {
        template<class T>
        static void invoke(Archive &ar, const T &t){
            //if(0 == (ar.get_flags() & no_tracking))
                save_standard::invoke(ar, t);
            //else
            //   save_only::invoke(ar, t);
        }
    };


    template<class T>
    static void invoke(Archive & ar, const T & t){
        typedef
            typename mpl::eval_if<
            // if its primitive
                mpl::equal_to<
                    boost::serialization::implementation_level< T >,
                    mpl::int_<boost::serialization::primitive_type>
                >,
                mpl::identity<save_primitive>,
            // else
            typename mpl::eval_if<
                // class info / version
                mpl::greater_equal<
                    boost::serialization::implementation_level< T >,
                    mpl::int_<boost::serialization::object_class_info>
                >,
                // do standard save
                mpl::identity<save_standard>,
            // else
            typename mpl::eval_if<
                    // no tracking
                mpl::equal_to<
                    boost::serialization::tracking_level< T >,
                    mpl::int_<boost::serialization::track_never>
                >,
                // do a fast save
                mpl::identity<save_only>,
            // else
                // do a fast save only tracking is turned off
                mpl::identity<save_conditional>
            > > >::type typex;
        check_object_versioning< T >();
        typex::invoke(ar, t);
    }
    template<class T>
    static void invoke(Archive & ar, T & t){
        check_object_level< T >();
        check_object_tracking< T >();
        invoke(ar, const_cast<const T &>(t));
    }
};

template<class Archive>
struct save_pointer_type {
    struct abstract
    {
        template<class T>
        static const basic_pointer_oserializer * register_type(Archive & /* ar */){
            // it has? to be polymorphic
            BOOST_STATIC_ASSERT(boost::is_polymorphic< T >::value);
            return NULL;
        }
    };

    struct non_abstract
    {
        template<class T>
        static const basic_pointer_oserializer * register_type(Archive & ar){
            return ar.register_type(static_cast<T *>(NULL));
        }
    };

    template<class T>
    static const basic_pointer_oserializer * register_type(Archive &ar, T* const /*t*/){
        // there should never be any need to save an abstract polymorphic
        // class pointer.  Inhibiting code generation for this
        // permits abstract base classes to be used - note: exception
        // virtual serialize functions used for plug-ins
        typedef
            typename mpl::eval_if<
                boost::serialization::is_abstract< T >,
                mpl::identity<abstract>,
                mpl::identity<non_abstract>
            >::type typex;
        return typex::template register_type< T >(ar);
    }

    struct non_polymorphic
    {
        template<class T>
        static void save(
            Archive &ar,
            T & t
        ){
            const basic_pointer_oserializer & bpos =
                boost::serialization::singleton<
                    pointer_oserializer<Archive, T>
                >::get_const_instance();
            // save the requested pointer type
            ar.save_pointer(& t, & bpos);
        }
    };

    struct polymorphic
    {
        template<class T>
        static void save(
            Archive &ar,
            T & t
        ){
            typename
            boost::serialization::type_info_implementation< T >::type const
            & i = boost::serialization::singleton<
                typename
                boost::serialization::type_info_implementation< T >::type
            >::get_const_instance();

            boost::serialization::extended_type_info const * const this_type = & i;

            // retrieve the true type of the object pointed to
            // if this assertion fails its an error in this library
            BOOST_ASSERT(NULL != this_type);

            const boost::serialization::extended_type_info * true_type =
                i.get_derived_extended_type_info(t);

            // note:if this exception is thrown, be sure that derived pointer
            // is either registered or exported.
            if(NULL == true_type){
                boost::serialization::throw_exception(
                    archive_exception(
                        archive_exception::unregistered_class,
                        "derived class not registered or exported"
                    )
                );
            }

            // if its not a pointer to a more derived type
            const void *vp = static_cast<const void *>(&t);
            if(*this_type == *true_type){
                const basic_pointer_oserializer * bpos = register_type(ar, &t);
                ar.save_pointer(vp, bpos);
                return;
            }
            // convert pointer to more derived type. if this is thrown
            // it means that the base/derived relationship hasn't be registered
            vp = serialization::void_downcast(
                *true_type,
                *this_type,
                static_cast<const void *>(&t)
            );
            if(NULL == vp){
                boost::serialization::throw_exception(
                    archive_exception(
                        archive_exception::unregistered_cast,
                        true_type->get_debug_info(),
                        this_type->get_debug_info()
                    )
                );
            }

            // since true_type is valid, and this only gets made if the
            // pointer oserializer object has been created, this should never
            // fail
            const basic_pointer_oserializer * bpos
                = static_cast<const basic_pointer_oserializer *>(
                    boost::serialization::singleton<
                        archive_serializer_map<Archive>
                    >::get_const_instance().find(*true_type)
                );
            BOOST_ASSERT(NULL != bpos);
            if(NULL == bpos)
                boost::serialization::throw_exception(
                    archive_exception(
                        archive_exception::unregistered_class,
                        "derived class not registered or exported"
                    )
                );
            ar.save_pointer(vp, bpos);
        }
    };

    template<class T>
    static void save(
        Archive & ar,
        const T & t
    ){
        check_pointer_level< T >();
        check_pointer_tracking< T >();
        typedef typename mpl::eval_if<
            is_polymorphic< T >,
            mpl::identity<polymorphic>,
            mpl::identity<non_polymorphic>
        >::type type;
        type::save(ar, const_cast<T &>(t));
    }

    template<class TPtr>
    static void invoke(Archive &ar, const TPtr t){
        register_type(ar, t);
        if(NULL == t){
            basic_oarchive & boa
                = boost::serialization::smart_cast_reference<basic_oarchive &>(ar);
            boa.save_null_pointer();
            save_access::end_preamble(ar);
            return;
        }
        save(ar, * t);
    }
};

template<class Archive>
struct save_enum_type
{
    template<class T>
    static void invoke(Archive &ar, const T &t){
        // convert enum to integers on save
        const int i = static_cast<int>(t);
        ar << boost::serialization::make_nvp(NULL, i);
    }
};

template<class Archive>
struct save_array_type
{
    template<class T>
    static void invoke(Archive &ar, const T &t){
        typedef typename boost::remove_extent< T >::type value_type;

        save_access::end_preamble(ar);
        // consider alignment
        std::size_t c = sizeof(t) / (
            static_cast<const char *>(static_cast<const void *>(&t[1]))
            - static_cast<const char *>(static_cast<const void *>(&t[0]))
        );
        boost::serialization::collection_size_type count(c);
        ar << BOOST_SERIALIZATION_NVP(count);
        // explict template arguments to pass intel C++ compiler
        ar << serialization::make_array<
            const value_type,
            boost::serialization::collection_size_type
        >(
            static_cast<const value_type *>(&t[0]),
            count
        );
    }
};

} // detail

template<class Archive, class T>
inline void save(Archive & ar, /*const*/ T &t){
    typedef
        typename mpl::eval_if<is_pointer< T >,
            mpl::identity<detail::save_pointer_type<Archive> >,
        //else
        typename mpl::eval_if<is_enum< T >,
            mpl::identity<detail::save_enum_type<Archive> >,
        //else
        typename mpl::eval_if<is_array< T >,
            mpl::identity<detail::save_array_type<Archive> >,
        //else
            mpl::identity<detail::save_non_pointer_type<Archive> >
        >
        >
        >::type typex;
    typex::invoke(ar, t);
}

} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_OSERIALIZER_HPP

/* oserializer.hpp
+tffYUqhuEsjW6eq+5uORcg7y8zH4SEJh6Xj2e8shmis5ARFOGPzlMMuwXwFpt2NXb4RI12uZ3TN5lFJKf+EEKS/Z4zpUrjJGyfcuTGbqEFZ8CzxOHpwq1RwyjTpLf/AhH/WbB01Qt6JXahwW97ziZrbVhHmNP/g8XTlqNmxWlGIxo8nkOW2eso3kxvVQt/V9aqa24fPw5BooM5QP2sV/3VZs9ifdkFR7Ifgd6/BAsjCmmAp6+pM5NtTnspM6epTC8k1U5bRpmoiz35XD3XcL5ci7qKlaq2xZ8/mySst4hfHPDc1D94NWolNvIZSq9FycSQuoSpSgguwGO5SFI68x8uCRW3iEx9Wgwh6F22eaMh2DPMrEpJ1p6Ez1rMMKR0PSNSASmvsC0jlsrgtdQ855IZHXmjxFuOfO92GRETxuo1n7w68LB5zDSb7mcZUO7M76ZRgMThNe6FOkt2/mZEH+cP79sVVItlxC98YYof/lDm3VrDTmPcLsTyE5jcUVgYab1dEJYkinwc7CDnvnxzN5EbU3VcuEdt2RaT8UUq2EK/JwD0Wl1Gvz+gexF2t73VRU7NpIWHVmCvtqb8jFD1jsQgOBkpY6ejq8FDgGOjwkCyOxGKCtKnG49TlJqI2UTMvJBld8uX4g/PZgqC+vmxXwclqqHKuNglRvZxVjoxNpdfAfnSwNafil8BW7i6Wo9eAbdzK6nuWn1HcYtGZmveTm8YzI8UaVKe1DXfCI2enLwhyyrXNOezNDXeT+BqLt36adZXsGbPfiZKYrZXnPWA3zJe859NnakpN+w/VVer1HLd/7loIh+VZznuO4JqNJtbpbOhR1uRZLhRnonFUz6XxTgVZmr4IKCjjLk+mJ9STXVVWrTq0WNtFE3vE2c1X7FaylHxzJAreqT/Y18s1GbvldjfFNJ1qcW02ztwd4c6kVh/7kTrL2G7OcuNsuRZ8ZEljlsRqpB73ID3LtNGahsyiJ+1U39xCbNkYIk1hsVSk82Qmy7lIg33KYSSNOqK+lbEZU8hF6vB4Q91s8ua06Nyefqt1S5vveTvsnA8E/Mg4+VZ99uhdX8JffgozOuolYzXurAYCbXRXC2kNxH1y5g2xKRMbP5dt79WB93FHQyULUqFQzD8bNXa5JTBd1r/Th5e33H+6xPQKNV4C9TaF//Wxpx7V26NzORgvFWHJdrioVPRWodGkuB9aJIlajelM7KlpsxAELGF7Z0JPFLfVbNdoL8rtvBODsYz3KGinuU9RB7V5fUF6r9V1JMYRyazZgvPouwKt7Dl0mMkdHoOjREt3tFUwyHWQQhkOk60GxvxXxHOz1O4ihrCftBbnmqgo63gKHxJMYqSPL7qARUBnBoo20lF2dx9EO6ByQ21nm7Llc05JCTtKM4dcvPmUrjUpxpVhWCaKZ7Umq55s4JcPPINfLlfOj9dkzladVW+dc73f2oKfRDCFv+T0IUTPH+QzQ26zxEEkbbfobvVlI74ODBGuwUCyLP8ce3vQ3ygHV9F2z72I8U9z4hZrz6ZdTefgw68ahvP0HB1UwLp9UTLNmeeZPslyqnOmy0LZ1bmY6w42MULqrWj3+Fa41vBJ6NTZkI18iMSb+3lu8zgHHOFcVpmvi2r4TbjA5CyGXADGFIxOzEoUNXRr8ENTuJS++aAa6rlT7mcXH0XBhdroSOBVfW7onX6gY9B9aDrcb8y7MCBkQOgGednHxkdqBQZtSlER5gNExMGKIVtxwb5rFBfCDEi6zOP10Fmx7nkQKeAHnBuNpcAEBMUfuaol1CXLgp/TNl4/DmjAuADnWoO4MXCp+NRQ6Eioq6Hz+T2XfR4jvm/LeJgiIpsm4g1yToFwhAVrgHAJ/5AOQAc2SgVEAlHl0MbuXPdun9jg0alBPSepPQBse0CyM6E3vLxdyghzk4BXMBcJgKwgoqHHA7n5PpWQuwLbWLu8KcifwZx/SrFsrb6SGfeymFojmOkjsAJkygJvV4pd2ncUFVumVDCBgNniqQG70PBh+cgdOzLIokuQDRyBXdh3UQNaq7drwNcNs+M/qpSA0CAwiCyLWdVMArotCsRxUa1IzO9piT7eoUoWr3NL8K9WfDJoj1k91phUOBQaBX0JFXzZAyoJ4mivusmODwd9bQU8BYxZ4jRB6BKfc0QnxhFjiWWBv3BguuBU9YFw8YLpAq6HEX2girk72uuJ7YvXDu4JEcieMOJTLIC26yuAVlcmxY8wjlwLipEON05E6RtxhjSh7FbAVQFfjGsJYOoyCTpa0b5lKgMQ+Th9tAFZIMuwdGjf4DrgfWg60gA6VkeU++F5aXVePlZfaf0+ZlvWjf5Y1atdySqkt8eaNboYTMDFt0ewK+UovdA/oKox0mqyMpdS44jrq/Maq715dT/ips6wowvn1uPF0K3txPX/pmFqEcH5pZoZV7nS1pB9HYs/Kkmdw7yWNoK6UbXJePhD34fNtjJn6op+CF0ZMdzDx0kmmeGuzurBjM97TKYc8/HMht8+Q5t3UQ46bIAj7mmJ01YCLtc9v1lwL8mKUFZoB7RhAx1gMZzfoA5wHmDbYrXsveCPZWyjRh8cdMnM8s+LC1+8bs99yqYNu6u2t3i0ZkPar5vmhtZYb7tr331rB7otc+Gd//kUt/aVM07cJau4hJ7gLB8UkMkU9HwDkAQ0ka8c3AxpNonjilYRC3gBFSBCieNVRgd0oBzSMoFwwhkAXfaH4MWVPsvbVVYwPgBpCSRWZGx/asQg93X0FAxDc0+iqu0owjv3SMLFybFPaYrvM/Uc6UkcEc0YAqLqvF+KPMfosga0++HCAGVYGI3AJHrW7YFXTADQ8q6ZH5JysmjjmgE6sbNjH7kz0rKzRH5oG+u7WwE9ZeLmj0eGTZ1ZL4gO96mxTFbZJ2aIJ431lO2pVNR+60/E8cqQ6rJdAdKjq7lAwn7SDc5ulxUnyRO6xDU1uNReZXMtNwR+4fFJbgFfffpoIpMRzeV3ZTp3rZk6ROrmhoviaYi7WM1p6X6F1NiXKdq/dKKQFzzYuMm/71zh6+Q+t47+wVWgeQ9qim+XNTbhHLf0ngE9KhqObiE2ZAUtoKZmF9RcZnvOL720cV++Kv4M2LvTbVYUc+FK2NsOqubFiBNuVxFaw3WTfNvJlJc+0FbXvD5Gvri85K5i0eCmVV60Kt5Yl9QJsdwGL95UhImsvi+Rn6Cxfxb6aKFx/bMv1TaGEFgGDqxRyaNVdRY5UYQcrvNiVUUWuE7PpJ4k6uf86fDwupeQl21lW2x20L5xy0tEuzQm2D5NRjvaaVs0LtZRM2iuucXM8nLi/K57ddg6U/Z5bP2jt9xtfi/eljEM3Tmge8ToiZfcvIYPhmxzXncN0VWVwyUX3XOxHpKiueadsBqvPbWGgeMZyJL2g3nRzuQlNk2ANUn8M2D0dlA6J9qgPftxK6R1T/ptjbHbeg+MYdGKvjBNsVQxSQten3nLimfk9bF2kvqLTkP2fVvFRtRtG4ID8WM8tlqvh0QXBd38MX7VFODUx97i6ajs3UsLu7qEMY9t6vVvSLE1u+MjXa65muiyUqeBlUtfr5FXAyofSRtDWIkUAlUGpLtIqiYloKXF0GApBdsQPCQpvcExTHeq6/E9uVOIrgP3kuIk9CgKN4747lYJUumQHjEzkWhBuA8gxt4+3Hwalx0k4sHtmxXme0vx6KAwuZpP5uoF1sM/MOXdA24uNR34wogFbM2M/oi8aD7RX4O2eFjDuNK3VTPmJVus7TJKQbgs9OiX7gTiILFBmDOft+3lw3wsKN8THCN8vZp7MzwQ8hF9XwYayA2Vj5aADxeEDW4f1ycL2IUtAWyNms8JSBPCkRfGxb+WpsKnV2y8K7oec93NR2Xqbln3gl27DauHZZC6PxfPtxHM5zV2WZ/f2DXaHv4eNDAuToMKoIVt4etAY0pBiy/tajJgDTdmlNvLQpeJS4DDLv76am35KAvwhtK0o3JoN2jiBbC+0erWQ7tThduDPPCarr1h+bxyo60zabStxRmT43yC2W8eXPHpn3IWZykHwfng4yArxio+zLgiG+1dm5E14f2NsifW1djLmKNa5416hCW60ErsyDcHTiXGCxXiJZuLz1jdNeW6ms8N95T77a7GZqy9g2gyYu1LLaRDxdXa1CTE5ALwLMLi4qIbWB+2T9wqEAtwB4U5b5YwmKpuhBb0vIhqORDbHUjuPHCSpn+i5kNE4dPBq/idpPEb3xNU4Ikh/LpHB0KHAQBOxuAueQS7PsXVVMOuhQHDIGc96/D5jdSn8gqqIwxA++ydikb8rRiwAJi0Ohd89MdrRHqOUxiUF4D1p2afxlq3qhA0AGoHd6VzxzuAigZ1IBxIA71HFYB9hXJg3j6T4o+FtBzAvKbU4F/NuS/xu4kQ5/Y+JxZ4fQRd35i+Ap8D/gn0KApIHoPz+nBv2jEn+GC93ggN4I1r8nahyEUDcAEdvESXAZIB1yg+aUCnQOMfvtFztQ8BD+M9LHFcv3HwvD5utfeuV//0cdpVpaftMDEqI3g1Tz8d8+5MMY9weHvDcur9yGAjAVth/Pjhuc3tbnGPt9R2Ev3x6itWgO1g97oCZiKe5UNV4pvFU9TXk5u0k35gHYHUH5U7nBqvxb8I5frScbLvl3qT9NrR+qXAq6ClukmdATMfCx+Wr3sCKbxqe9tOT3M3kCXgc12PYB2v7ZQQGFl+27DJzZhdmvUox6flPjrBDpwd7T/2amosX9IiXpLYT96cHr0zCN90fhaSdE1/vM9/ZgpAAFOLZkd7Kz+3tr97O2p8xtv9csf14p0qM3Zl+vkJYQq4ka6x10+q/draq6M9921k7EVnKsWr/y199Fxy8kDqfulFakXyibFU3BycoW/lDWp2UcBlu+Asy0pwl82pD+sHv0ivFYBzHHRvfKlT2+ctywJc98WaSoV/lX2IQJ8CDhFpMgrQ0eK6zdmRN8vdUT8pWXrvdEmXOxbsUHfepOUELHDQfmD/Y1X9tfEEz++nBadL4IzXJNY6kU8f4Aiwm/e0qC4IfAaH/rNplkMlOf5ZaR42egPklRI2egoIN8BBUIz1g8ayotkHp+boZYPeLSBzH+aKs5zIvvvY4Lxep5ROJ4vGxI8fOHXIj2v0dQb3jpNXESY/sxx7xufRBe/mbjlEWxn3BhlGodCKW3XdLzMdkCaDy/o+fK7dhV3nXF1FSqVUtV3OGmDWJLUNJ2CV7o8tvY9n1hFvXcegjNyIJPSWaOkyRATfj3pS3Cq5h35bXi1WM+5debC5/HBqPWNuPmh2I1ylTk4MuaPp3m6K0p5CFdiStjM8MCLv7O5tpOmmXbvbs9XzWqJqbE76I+Qs/QBp/iRNKkj9Ap117dpeAnh3MuuYTZEi8oG2DebnBSVAQuEJZXAtEu9Mqi3IdmyBrZ/WZvf5J9uLIUNoFshRm4PUrVXHWSx5lzCAbOtnXa6rrybsWxxt/K20D09v5E3erXsJuiLSHI9mV+LVnJM3TNWj1E8/+uXxw7dt4+WsMEgTPlcRdUhwgHxlv1GD9dxQKL96h3I3emlAJTAHmabl2YaWD8AoznlpTCn3diSXHvCSrcXoO6ZufkYGs92VE/0shS6qPK/bPxNbX/1jcMSneKH4FtdAcBnagrgkwCvTuD9vyt2POpDGabkpjA4V8Iini5DLuXgWOZ+oRMA1Bz/rOMupXtmofetNlHceRycSarTTLyZA88FzRlxgmY/jkuJcp8631BzakxX9sZZAbYiX4CSQLqUTK0Ye+sunxoxT8I+ZTaDHWANvgPOE6LpbrzVChckns8J7JvYv3ZTrlIB17TJQI9SKWia0O0jSTys0woLaAVxmgk2RtdtWaHyN26QA8AXmDk4RiQWS9UqwRWAPF5bw9o8+Jj8IHfh5QAIUdMNxoIVTAGPqDc4kfG2BnEbAu/WjHwbqbaiQ8Hmd0p2eFRq9zfp5d/ZMgLf33nS+9PPOpCVBRmfd4S2yEiHhew+8jUd6x9r3S/k8R75l43QzAl0Gm9SBHCOVGES1AMynwAHtUVcvcz7BwGAnnJfY4xVtYqM910+qpxwA1TcSa4BPrR1DEICF1rTUNwnoFRUwOzMoJ7oxMOyz9GNUL/eBqBxsH4yOp3fY7XZgi3yVBX+MEEt+DM8LfulIAs8U9lw4NGtkqapVA7AHtPx15yLtgPCmsA6v8fGL61HbTeSt/Y0owSCQSPcLdodBZFeMqHy0B+q5IEBZ81rYJynaKuqyYvWBvrgsx8n32egMRc2dk05l2Byycu+YcfDz0u4pm3GZxImat8Rp7UnGzVOGZwi5kS+eHXSImpe/UXcvQ/MzsT75T+kPz3EXt16rmnp4CIF74pQX9gxKBUS2r2T3vSAdq8Bw7jpgh3XHdTv252GDdAD38slVpKpbmVH84ZqIurdYGKNUKB0Bd2t8Db2RuuVF3urjxmXoSZWO5mWRUfgxorAEV8Pia5AaR9IUyCulSKYEoZ6rwY7rReVUUcUJQDugUmbwYy31toYJUhu+rSPGvaN1dAx+9efUekLwFKbA52aFiwRC/EbC8bvgJpCPtUsfT0B5pXxqHaeuG4EumKLFC1cyN24zpzyFfJg5EOA6lrm/OsQonbe6xe2YSVaJPMKsCgJrr2jtgZZ4PtYS6WQKt2wyxGZpN0tm+ab3I1JHlL40OHABPOqXAhbq2ufnV+e6XHz8pxxVnywlBySOSoR+6MTd5mBnARt8kPlJ8B75lj5MuXr30HgToijMg72aMk6uLPZXG3xKQV8yPNuyBNES8FZelQAbxj5fMfzhgIBBCAvSyERgsG0ibuAKMDV9MKmyeHK8KmFXf0bymKAnwnNoh+h/EgCYU8F00GtDP5wBcUVjRs3eV12eVEK6Blv3PLMDTIDi80817mL3fux3g8vfLN2NSiTwftyiMz3ppFcpMbaGOnb82n+Sv6lWFPYaFHW6ovEYd6/yrNM3XkJvkVHIMYrrTdKGeX7sgPnc0konUu5nwg2QX4wa7XHh2cFevlsLv6fpcX5/oHpwS2G7eh7izTB5gPOyMEvPu6jc0550gdr02NMcbde9Y0/JYUvpcfB/Y3EKpq+fNfVIvwIvTF6Wo3qxfNnuc8qCj/Qq2WmHq7t7KK1mfwNKZ9Tc84fFht6irhhFwoYjShaniqaMBL2+ekPIHd5gBxCTIsXyagAseWhBB9PgbwmXrYDqvbIh+RoY3u1LNs9XjrYHqOvQ366lfJ/toCze3ngBAz4DdH4JfSyJJY3nvMAuGKgD4PA04oIMpvzqp6bsP3aAz25BW+4s8kdMX1XP3kx5X7Nuh99K715lLZ1BMickDY6OMx2WnTTekipBefM7eCSrE5n4o/nKokCW4c6humZQO1RNLTOUNo2+yRrdugrvpbQfdOZVsNQCplxeRWI7quM0fvT5Ot6SghpuXmwTJuVdy56mx8Z5WpHuuHvCnsUEmliYfD85Kogkqt9gX8AerutoMY+4At4wZbhSzaJlJ6nNlFmFvcqF2MEKqSXq1JZeJaABSzsXvCS+0DwHBfjMgULQEpaIP3gNBl9g5xpmgWtLntqDlFguaegmAHkxA5yz2y0fKmfI2S6NKN6+NE/WJb0BndlG11SNJaEuHh3FCLCXHAyLU7bhnfq3656wXiAi1u5+xP2wNsRhbw+WmVSrD+cOyMeH3maIXTvCXJt9wDzShPHxJOk/zEfTha0YatflzdJec67ckrTvjDz7xH67gNdgknXgy1FSLZOo06MnTBAJaEUHNRIlXtueA8H9eg7OR1zjzEVughad6UFSErwG8M7H2M6C/QzqINkBA0QCvPyxwsfl5Nn/G6k3vyuAhu+RueNTyYnwwBOSnhFUydOt25OcPBSPLfl0EkX9lBcJKCJ53th8i4Trx0N/u4/KEthcUKsfTSFPdSDGLKVL10ob/JRW25JocnCpCb1EERelYqNTAZrpy59E4jT253LL6UKY/HhGgCH4dKz7b/x3RE8AAFNiFcHHhPYMaLGzOEJUPKKdzcHcfBf0Z/+Vb+BPYjoXrHZx81kOMSJdXLeASocDIoC5JesUh6xFFvFqynJmpGc+fypfauFYHNCsN8a3de9tyyzuNt6bbi+HdG68vDbS2pb6JwXcFE8vDuZZC16VyLg8ukgkAMjF8t3P6Vf0+290twHT7DM0XVq5WkNR1bOfRfnUxc25woGW1nu0qS0yTKsdoD35j7xhvH1ajUrN4wjMy/0iat7y7Y4WFBSOJnNRytvAOkLVVo8XvdWNOt/q7+oZ7rJfTdv310aNn5fUItrz3vq5E35WY705JW7pTGG407zV6YA1mT0MQCar1EmYx3ESvKB3JOjqnNXw4Q/m4uBJP5ij2eP0OVGX8IPHRKIj1W7mnnR61aIpL9K/hMnfxJDopukXzntcwnvt6fYrlM6n7yRdJt46w5deNAfR3Gt1dVw7I8mkz8r2qdXNVhXeputlnAQ5Ys6nyQ/XVSSFROFILOA3TYHpL3zipMHwZ+mzsJgqwVqMR5dLgVvdOUQ+DxpMskybxjeqZvN9ZFG7/bi7Ft9q1q+Rf4zmTmrkP49LFhekA2irvDU7vrlGKmTfG/C8Xb5WGZJZrBsPFQS29I6KVedlrun7doPzs/1Bcl9jNcsXT3bL+wr6IuXpIqU9qb8VK1kydd7+Miy3GCXNZlYr4P64ekJn/ijB12btkj/y8eHApXlFdly0sNUztZGm4ta+pE26/EDBtprwrOF8Gnn+qoa4n7aTdkp3FcfsCoBlcnY3TeTd6aR+FKf8LT+Jzbz9Wp2mdRZ/m0iPuTFuDFinoIMjznDsTrZhtt5ZXfcAw2t5+mTNl/mlHbAk0wHJBkS6/iHdB8kG+H+T0vHoulMCeAi5Jq6HT6GLlXbTaDej+Im6iDDx+lwD5x6qyttl+ZJioNP48sZn6jT0HcOUzyxm1xCKHc8UaOhYUJ3oZJBVTDIXSCk6cRB1Eds0EHmcNVp5ECpxN6F3tgpl9I0RBf5FTOFT6M7Bm0XogD7xZPo16lE06refGWJhudkueJOI8WsBNVIySPWfSqMT5TVyleSp8lyNJmwnPxWkQGG7YFw6pdURxVN7f5mKzXiLkF6KjfeuNu39jjL4Q0kySMI+lz9oCPEXgfpFbsT8PyasRYNhFH0wjc5exP1FQN7JI+gkviD1CLRhQWml6YiZyaxu2mxpnVE=
*/