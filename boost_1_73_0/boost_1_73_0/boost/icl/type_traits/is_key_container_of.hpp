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
X6Xai1tYkPIDy4uKVTmrpRgxohuxNN/EW3pHKHBY1OsklvtRbwoUZZtJXjIpkgSiwBYL2ZgsmK8jMyIqVsDauKI3mWeSND3s8/QJIUIIIdu6zKAGIQDNJkeAR6zONqJUtMrpVoOOpgrtC5D0tm5YnsES9trwmeW/ZmsuYzliN1awcFcBuzE8z3CCW+aeM8O5haxLy5kD7xiaSiYei1JIaC5ZnBZJLDZK4V/+tJc2X0jBrq98JsoSqqIcaaQA3olMlJy8WB9Yxe/ibMe4ShAKhAKZ0kklmQp3XVWKJkmaUK082wx/YiKrUyarertFXiLAKreIa0SVAaIr/2JM/xkzMjb253YjE1RRKZQB21LhpvnYAwIE3ivT940LcwIO8FJ+jhfPWGtJNqlqKIVQGJGGKs8pffiOx5lsPOo1k3yimhj2cmFMbMO5+HU2Q2jSFI42sN8QDbGJx0gUVCKUIo3P7uVIRUHnTAoU+U5HlVdgVnwq3FLcizKuDizBhwRufFcuWJam6YXnhmWb8/Da9KxzXdDkK6d6LtFBKFR5mb7AYc2MwHKdEYkH5mQNKZI8FSzDH0kdACcaFjNE+uIQzSTOoqTeiKay9zrYV41bbFXFCXmA2NQ8AdKIO1XVayJCzNYx2ZWIbAfPdEiQ2dv4
*/