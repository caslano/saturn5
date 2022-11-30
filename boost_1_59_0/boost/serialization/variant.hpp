#ifndef BOOST_SERIALIZATION_VARIANT_HPP
#define BOOST_SERIALIZATION_VARIANT_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// variant.hpp - non-intrusive serialization of variant types
//
// copyright (c) 2005
// troy d. straszheim <troy@resophonic.com>
// http://www.resophonic.com
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org for updates, documentation, and revision history.
//
// thanks to Robert Ramey, Peter Dimov, and Richard Crossley.
//

#include <boost/mpl/front.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/empty.hpp>

#include <boost/serialization/throw_exception.hpp>

#include <boost/variant.hpp>

#include <boost/archive/archive_exception.hpp>

#include <boost/serialization/split_free.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/nvp.hpp>

namespace boost {
namespace serialization {

template<class Archive>
struct variant_save_visitor :
    boost::static_visitor<>
{
    variant_save_visitor(Archive& ar) :
        m_ar(ar)
    {}
    template<class T>
    void operator()(T const & value) const
    {
        m_ar << BOOST_SERIALIZATION_NVP(value);
    }
private:
    Archive & m_ar;
};

template<class Archive, BOOST_VARIANT_ENUM_PARAMS(/* typename */ class T)>
void save(
    Archive & ar,
    boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const & v,
    unsigned int /*version*/
){
    int which = v.which();
    ar << BOOST_SERIALIZATION_NVP(which);
    variant_save_visitor<Archive> visitor(ar);
    v.apply_visitor(visitor);
}

template<class S>
struct variant_impl {

    struct load_null {
        template<class Archive, class V>
        static void invoke(
            Archive & /*ar*/,
            int /*which*/,
            V & /*v*/,
            const unsigned int /*version*/
        ){}
    };

    struct load_impl {
        template<class Archive, class V>
        static void invoke(
            Archive & ar,
            int which,
            V & v,
            const unsigned int version
        ){
            if(which == 0){
                // note: A non-intrusive implementation (such as this one)
                // necessary has to copy the value.  This wouldn't be necessary
                // with an implementation that de-serialized to the address of the
                // aligned storage included in the variant.
                typedef typename mpl::front<S>::type head_type;
                head_type value;
                ar >> BOOST_SERIALIZATION_NVP(value);
                v = value;
                head_type * new_address = & boost::get<head_type>(v);
                ar.reset_object_address(new_address, & value);
                return;
            }
            typedef typename mpl::pop_front<S>::type type;
            variant_impl<type>::load(ar, which - 1, v, version);
        }
    };

    template<class Archive, class V>
    static void load(
        Archive & ar,
        int which,
        V & v,
        const unsigned int version
    ){
        typedef typename mpl::eval_if<mpl::empty<S>,
            mpl::identity<load_null>,
            mpl::identity<load_impl>
        >::type typex;
        typex::invoke(ar, which, v, version);
    }

};

template<class Archive, BOOST_VARIANT_ENUM_PARAMS(/* typename */ class T)>
void load(
    Archive & ar,
    boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>& v,
    const unsigned int version
){
    int which;
    typedef typename boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>::types types;
    ar >> BOOST_SERIALIZATION_NVP(which);
    if(which >=  mpl::size<types>::value)
        // this might happen if a type was removed from the list of variant types
        boost::serialization::throw_exception(
            boost::archive::archive_exception(
                boost::archive::archive_exception::unsupported_version
            )
        );
    variant_impl<types>::load(ar, which, v, version);
}

template<class Archive,BOOST_VARIANT_ENUM_PARAMS(/* typename */ class T)>
inline void serialize(
    Archive & ar,
    boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> & v,
    const unsigned int file_version
){
    split_free(ar,v,file_version);
}

} // namespace serialization
} // namespace boost

//template<typename T0_, BOOST_VARIANT_ENUM_SHIFTED_PARAMS(typename T)>

#include <boost/serialization/tracking.hpp>

namespace boost {
    namespace serialization {

template<BOOST_VARIANT_ENUM_PARAMS(/* typename */ class T)>
struct tracking_level<
    variant<BOOST_VARIANT_ENUM_PARAMS(T)>
>{
    typedef mpl::integral_c_tag tag;
    typedef mpl::int_< ::boost::serialization::track_always> type;
    BOOST_STATIC_CONSTANT(int, value = type::value);
};

} // namespace serialization
} // namespace boost

#endif //BOOST_SERIALIZATION_VARIANT_HPP

/* variant.hpp
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
*/