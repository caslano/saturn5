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
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
*/