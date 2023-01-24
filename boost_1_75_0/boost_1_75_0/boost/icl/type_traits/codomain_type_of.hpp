/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_CODOMAIN_TYPE_OF_HPP_JOFA_100829
#define BOOST_ICL_TYPE_TRAITS_CODOMAIN_TYPE_OF_HPP_JOFA_100829

#include <set>
#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/icl/type_traits/no_type.hpp>
#include <boost/icl/type_traits/is_container.hpp>

namespace boost{ namespace icl
{
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(codomain_type)
    }

    template <class Type>
    struct has_codomain_type 
      : mpl::bool_<detail::has_codomain_type<Type>::value>
    {};

    template <class Type, bool has_codomain_type, bool is_std_set> 
    struct get_codomain_type;

    template <class Type>
    struct get_codomain_type<Type, false, false>
    {
        typedef no_type type;
    };

    template <class Type, bool is_std_set>
    struct get_codomain_type<Type, true, is_std_set>
    {
        typedef typename Type::codomain_type type;
    };

    template <class Type>
    struct get_codomain_type<Type, false, true>
    {
        typedef typename Type::value_type type;
    };

    template <class Type>
    struct codomain_type_of
    {
        typedef typename 
            get_codomain_type< Type
                             , has_codomain_type<Type>::value
                             , is_std_set<Type>::value
                             >::type type;
    };

}} // namespace boost icl

#endif



/* codomain_type_of.hpp
C+9kw0J7M7oW955o/5iB+tsQgCyQgDsyG7i17aTPUN0CuaFJKFv9dkEu38ZqGBZ4dssE9Nc5GaGQEULG8+smow9lZ7O+Zu1DiafSNZB/uCPzwgS5sid8idQ2g7PQxzp9ViofP7Ogj54aRD9q9hOrBPFSgQcyds1Eva1fRvsFY6IFwHiur0Tbt1xpHpt4bmcp9OQPXmXjWubAsxtn49kRDQ2BFWEWrWRGOmJbnadCB/7Jz858sANwcMlAG3CAdsqZAk2Pf+Q4obPmvEkRKpNV50QdTH9ElhXtjXD69tmow7JHBTo9+YX9hHQeGIXu+t63gzqW6+lpsGkazg96euhGC8jaegq+6dt3iGWD8kQs70QCaI9fIEfoVBW5vA6SdhjtvP4O2e/SvESDGbxzZqK8n77M3qHxMI8V9D3TQZ99j0xnNQJ6wSmoj/6ZJjrV8Shn4hmg3xmwvp3Fd30zoHMXKWI8Enjk880kk6wYTqXx35ng/+brbBcS67vAl49EfahddO/vcn9Y2+uLHADK6VhbDo2xnI/gixzIG7D/dPiQa9+gdUaXjRgROc32TcZemz8g/iqSJL8LfJXjEQs+fxf2JRIaqcRunzfs05arKI+vEmvBR680eMJRjQH0ihTI6EridK2XSDLqx4Ln7U7OQ4ZbINLpl99zYiri77Ne0nhoSJNzgO46C/S1FZzO9IhAP3om9m59s4rT9e2eYlnp
*/