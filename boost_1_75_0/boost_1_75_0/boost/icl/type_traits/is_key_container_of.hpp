/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_KEY_CONTAINER_OF_HPP_JOFA_100829
#define BOOST_ICL_TYPE_TRAITS_IS_KEY_CONTAINER_OF_HPP_JOFA_100829

#include <boost/mpl/has_xxx.hpp>
#include <boost/icl/type_traits/is_combinable.hpp>
#include <boost/icl/type_traits/is_container.hpp>

namespace boost{ namespace icl
{
    //--------------------------------------------------------------------------
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(key_object_type)
    }

    //--------------------------------------------------------------------------
    template <class Type>
    struct has_key_object_type 
      : mpl::bool_<detail::has_key_object_type<Type>::value>
    {};

    template <class Type, bool HasKeyContainerType, bool IsSet> 
    struct get_key_object_type;

    template <class Type>
    struct get_key_object_type<Type, false, false>
    {
        typedef Type no_type;
    };

    template <class Type>
    struct get_key_object_type<Type, false, true>
    {
        typedef Type type;
    };

    template <class Type, bool IsSet>
    struct get_key_object_type<Type, true, IsSet>
    {
        typedef typename Type::key_object_type type;
    };

    template <class Type>
    struct key_container_type_of
    {
        typedef typename 
            get_key_object_type
            < Type
            , has_key_object_type<Type>::value
            , mpl::or_<is_set<Type>, is_map<Type> >::value
            >::type type;
    };

    //--------------------------------------------------------------------------
    template<class KeyT, class ObjectT>
    struct is_strict_key_container_of // set is_strict_key_container_of map
    {
        typedef is_strict_key_container_of<KeyT, ObjectT> type;
        BOOST_STATIC_CONSTANT(bool, value =
            (mpl::and_< is_map<ObjectT>
                      , boost::is_same<KeyT, typename key_container_type_of<ObjectT>::type> >::value)
            );
    };

    template<class KeyT, class ObjectT>
    struct is_key_container_of // set is_key_container_of (set or map)
    {
        typedef is_key_container_of<KeyT, ObjectT> type;
        BOOST_STATIC_CONSTANT(bool, value =
            (mpl::or_< is_strict_key_container_of<KeyT, ObjectT> 
                     , mpl::and_< mpl::or_<is_set<ObjectT>, is_map<ObjectT> >
                                , boost::is_same<ObjectT, KeyT> > >::value)
            );
    };



}} // namespace boost icl

#endif



/* is_key_container_of.hpp
9TrPPA6Y3uorygHo+o30w7SrQSsm2HjwETM8L5CS1GA6TevyJL7ileJRLofWa5caNPv5yEv9faePRHylXWc3/xafL4QdnkxaZ3mSnjvV4XfR+PhmyJOTVlCIaqy92yiVfi//U08dvMiLcfy8a09d612M+Ce2yuGgXViw6yblrgMVs2DKZlcWpGkFVlO7doWSYe4wdmxbPpFdp23xbH9lE5lpDVajBpf+L462OcHEhT/Yj79CzgPalHRSRKD6fg/PYHxdTiyExhpKEAmIsjwxaj46MUJM3/6fJQo6KTaqUKx9vqX3on/+8n9dW6y9nhZpWgF1J5gKSihQL5OOxcLcHHT3xFcadGNg3T0kcWFgfY/UxkVqSJ9zgu2/ov5Je6Spf+wWAb4UHPY4LlkUncx8h7LcE9dMJ8zYD80+GMZXHWakepPEKxtHXPOB3+uveSVxxh+XbEbESu8HxMtObZpW1W3PUjNsjHMdfCPzZgpvRN4dZVYJ04Ne9H0kvDOk1dyu7bVfgafdq3CQoWQIDhb2vGNcdfkIV9pTV8IE12HGhdx/w1cj/DqlUkA/CvcMO3A/HoNGePqUrovIaxT0Zp+6CjBSS1x42OckFvcIoB98HScf223JhlVNFJeP6r7LlqF6f1U+plOC8dPFz1fkkzqfM5RdDAjI6XK6FmUFkMRWetvRBbxHMwwUAgI9cRwr1VGdyrbhGX1Hszq7ZAhD
*/