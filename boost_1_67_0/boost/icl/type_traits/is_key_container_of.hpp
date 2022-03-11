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