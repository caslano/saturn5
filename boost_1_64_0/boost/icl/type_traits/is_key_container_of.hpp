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
ANsC7gckBcQRzRPtbK9SfTJgZAP9bD/p3TgCDiVgIx9UtiCLp8CHu/5FgMkeP1mO0YnSFWqzPZGgjmb8TBF/ZZBODpQFyUKOctBFOhfg9/qCVIRi7MJtCmnTPCUxay9hX6TCH40aEcWikfyXG3UKWrHwiOmNg9CGWj5OaWAcY/Ff6Hb2hBdwuDgowMefPFWQpmI4Yfrn+zgRNUKKAQwHMXNWXOMQkVO4+OFjM8z6BtfDk7q2cYs0DbkoP+SSojUH48U+lLYXfI0jLlRkdecsfhodGGOJeMphlSWAyL2VutkZrQafqoiZwJEfty4z9bTpTSsB0oJdRruJwlkSqPSCQRLkMEZjClVG6ZhOcQhJ1yx0h9enoaGHKb/wK54T8BtrpEP/DFPEPY5B+R7Hwtjg3UA4hczlMHlibs5tF+WvkxxiMJUk/Dn0gZfhdOgDtKPf4SfauRZWNcDxuGjAjLIVloKlhEvmhrk5cj7UyhT0idy+ZA4TtDEeL9etaArgClGZxqi9X/w08YhESY4aJ4Q+f80iZ1XbwrUYXsqbuxKtvDRQGarUFMNG5kkc4Z2/r/gTMogbhNpG1W+qeQW/ZoGP5KzG9Rfr0ePXUY/kgd4eyam1fkzv1yN5cMBbX56p3TeUGXJbfp+Mss0JiTF/hGS2sO8025DZAs8yezJENmNlPFporBOIrR+gF9WhKNYYPp2M3bFUJSmK0E5ZvvB8z+c1elQrTvTk4kOQbVT0ahQ2g0NFK693OzOGIHKh8dkyPgmcxBJMxwgBpOP5xma0IIEVGHhEr1+vNPAQKFptpiHefUPw4Dh9pEMYAYjvBy2M/dRnTFGNMXaxANLHscak+WgNTQvpJesrKQ9JTpvByIEiLBcQL/iKikOgeAQXxKGHI5jeRcXaiBIbHkqdjJmYJaYxwgIC49ioIt69mLfpkqjIMJwu40m8M9qKxxRTTqtKixOXqBwmcBjDECLEHaaIjJNNNpCbcl0CicN0GgabQTDhrUDFhWaSBUDqQUt8AQcW6NDPiEOvvEbg9VUrh6YFjg+k8pqTETddLFZqjI9EAiwHQIUnKULGmRGKttTdo5HwEmEFzgukipvlD80WGKX9YPEnFHBQXpFLCy0arUEZUqhgyFisOTq/VvrxZ4zzlfvObDb9hLYlzyZvGd2lFpMfdC8g4YxaNcoaXYlWLkLRzqRKn12OFoYPqHWEUgPWsD1HK2ziaHzQoZxDFOsJjko0WZARvtRTIg2JDMOV9NW+GFXIOBY+CUZ8sNjmgnU3N/5l24psk21ZcA2wpeJ9oq0QltyG2uQHdYChUnd+9wfxmpg4I3FzdfJ+ht26Le3W7KGxZzDcvv3s7Rf9fPUGhp98ctkn7UMv/MrwssvOuCz7tvZ7GG7Y8NaGe4or2jJs1Khpo5bNGp/AMC/v9LwxwVtbMxw8eP/gB74K3Mzwzjtvv3Nq0wm/M3zlldAr7z3zZCuG33//7fe/Nv/xJIY1NT/XfD3vm+sZhkK3hYpefC+Z4dVXX3T14a/PrmBYUDCx4N4Wa39iOGPGLTN6/n1zBsONG3dvXFLlG8Tw5psn3Xz/C2cOYXjVVY2varq00eUM16x5fM2sk895hWGrVsmtZoxIDDC88MJDF/5++Q8LGQ4a9Nqgxz44fx7DP/wh+odP/MO/Z3jgwF0H3BnvPsLwzTcvfPOH+x85neHWrf23nvfljasY9uu3oV/F9dPTGI4fnzK++ILrezP87bf3f1tz+gfnMpw82Tl5/ikPvs7w5JMLT77b2ecZhrNnb5n9p8e/+oThkCHvDLnj8+A1DP/yl0f+cuGkN29l+Kc/jf3T0j93a8/w4MG/HXy149+7MRw3btC48y8=
*/