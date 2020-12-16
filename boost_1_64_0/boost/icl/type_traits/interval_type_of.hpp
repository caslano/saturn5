/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_INTERVAL_TYPE_OF_HPP_JOFA_100910
#define BOOST_ICL_TYPE_TRAITS_INTERVAL_TYPE_OF_HPP_JOFA_100910

#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/icl/type_traits/no_type.hpp>

namespace boost{ namespace icl
{
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(interval_type)
    }

    template <class Type>
    struct has_interval_type 
      : mpl::bool_<detail::has_interval_type<Type>::value>
    {};

    template <class Type, bool has_interval_type> 
    struct get_interval_type;

    template <class Type>
    struct get_interval_type<Type, false>
    {
        typedef no_type type;
    };

    template <class Type>
    struct get_interval_type<Type, true>
    {
        typedef typename Type::interval_type type;
    };

    template <class Type>
    struct interval_type_of
    {
        typedef typename 
            get_interval_type<Type, has_interval_type<Type>::value>::type type;
    };

}} // namespace boost icl

#endif



/* interval_type_of.hpp
2wez3tPzyzLfPtgG2qPXUTfLN2HWH8PJz39XyLdj1vvyr8jbMOsDPU+tlhcdxHGP9srv8+2AWR/q+nxLPh6zPpI/KP9rp2ouW0OhSPL9xQZdvglbSuFIcj3fk6/E1lJE/ojfXsyKypvlLZgVyB+Xt2JtlCN/0m/vIG4v5cqfkpdiVh4e8PUW+UDMype3yEdjVoF8q3wSZhXKt8mnYFYH+XZ5PWYVyVt9P8GsjvId8uWY1Um+U74GszrLd/l2w6yYvM23D2Z1ke+W78WsrvI98uLBvL6ibvK9vp9gVrE8dI22D2Z1TzjJqzGrhzxfXodZJfIi+XzMKpXH5Mswq6e8WL4Gs3rJS+XNmNVb3ke+DbP6yMvluzGrTF4hL6rkvqK+8oHygZjVT14pH4tZ5fIq+WTM2k8+XF6PWfvLR8kXYlZ/+Wj5csyqkI+Vr8WsAfLx8k2YdYB8om8HzDpQPknehlkD5dXy/CE8Jugg+WR5OWYNktf4/oBZg+VT5DWYVSmvlTdg1hB5nXwJZh0sr5evxqxD5DP9fsesKnmDfDtmDZU3yvdg1jD5fHnsYB5DdKh8od/vmDVc3uS3F7MOky/y+x2zRsiXyGdi1kj5UnkTZo2SL5OvxKzD5cvl6zHrCPkK+WbM+oR8pW8HzBotX+X7P2aNka/2/f8Q9n86Ur5GXoFZR8nX+nbArLHydX6/Y9bR8vV+v2PWOPkGv98x6xj5Rr/fMWu8vFm+AbOOlW+Sb8Gs4+Sb5a2YNcGP/74/YNZEP/77/lDF/kDH+/Hf9wfMOsGP/74dMOtEP/77/oBZk/z478cBzDrJj/++P2DWyX789/0Bsz7px3/fHzCr2o//8hbMOsWP//JdmHWqH//lwVCeY+k0P/7LSzFrsjy0SK8nMSuecJKPx6zT5fnyOsz6lLxIvgSzauQx+RpsI31aXizfiu2gM+Sl8tAwXoPQmfI+8mLMmiIvl1dg1lnyCvlwbCx9Rj5QPgWzzpZXyhswq1Ze5bcLs86RD5evxKxz5aPk6zFrqny0vAWz6uRj5Tsxa5p8vHwvZp0nnyiPHcr+TNPlk/x+xKx6ebV8EmbNkE/2+xGzzpfXyBdi1gXyKX57MWumvFa+FmumWfI6+Q7Mmi2v99tl13848//ymfKBmNWA5/B1g3w0Zl0ov8hvF2bNlV/mtwuz5smvlDdhVqN8kXwFZl0k/6x8HWZdLP+8fDPWSpfguXx9s3wPln8Yr4Hkt8rLsVF0qfwOeTVWT5fJ75YvwlbSAvl98g2YtVDb7QHfrzDrcvmDvv0x6wr5d+XBCI4PdKX8EX98YVaT/Ad+v2DWVfIn/PiAWVdr+zwlr8Hq6Bo8n6+f8ccXZi2KaJ5QvhRbTtfimaeV2DpanOWbsJ10HR7m6xe1nqKRvJ6hJXghX7fKx2IT6bPy38kbsUX0uaz1L8dW0/VZvh7bREuzfCu2g27I8t1YMIr5/ywvxiroxiwfjo2lZVk+CauhL2R5HdZIN2X5Imw53Zzlq7G19j08atdP22EjZn1R/p58C2Z9KaJ/f+XHbWwH3aL7N3ytXmcezvanFfICeRU2kW6Vd5HXYDPpNv3envIl2Cq6XZfvI1+HNdNK7T8V8u3YLvqyfIhfnyN4vqOvyEfIh2Pj6Q75UfJarJ5WySfKG7D5dKf8FHkTtoS+Kj9DvgxbQXfJp8pXYdZq7bcz5Rsx625th1nyLZj1tYj+uz95C2bdo8vP9e2AWWu03S6Shz7B8yndq+tzubwIs74uXywvxaz75DfKKzBrrda/wrcnZt0vXyUfj1nfkK+RT8asb8rXyeswa518g7wRsx6QN8sXYda35JvlyzHr2/IW+WrMWi/fJl8=
*/