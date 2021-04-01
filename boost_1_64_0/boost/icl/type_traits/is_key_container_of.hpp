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
OAYnkChHB8Wyqe7LmWEDAHbc+VZs7SHSdM5/kdwLP3T0ObybH5G9G65g7/vPVEHjlBvOdA35GWEeqEXmpeWsakxtjRVTsTElxlVnpgbNI+aobqAADqb3cTW6sv3H+901d+1+HGQ0jROUgr/hfw2QGFGns8Vpi9XUEDdCqYV6/xDX6bRatID/dcN3ElWwhdSmx4veU8Mz6KCdMERj4gujkzos7RYp3KeaPfG/dnhiiQflcGx2IHz9QfH7nhkDIXDxuwcLe+ZhTSlyS/Bh6NnvbRa4vrN6RSSfItmxG9/0e3UoH+DW76I7twV8w6Um14n8moNfyOQyrKPQcKiF1ktJuFJ5radN4mKYw9G8hQSxejUnpAUnnrn3bKstzAeOeOwHQO4fz0MCe4m96gVA4/pLeegIM3mU6is1iUN16eDPQBh1VB4CsMtRGXDlunRDVDLKu+YFEUe1lssNRqheqsO7lBUN53apmHvrKbVKJVWqo1t9CyOf53dPKDRnVWfkBq4E8vY2xV2Icz6Zsb4eYsHXw4uCwQDUmQPVokA5bRM1LRRUn6PIDuutGLlsqA==
*/