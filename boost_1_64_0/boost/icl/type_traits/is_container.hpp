/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_CONTAINER_HPP_JOFA_100828
#define BOOST_ICL_TYPE_TRAITS_IS_CONTAINER_HPP_JOFA_100828

#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/and.hpp> 
#include <boost/mpl/not.hpp> 
#include <boost/type_traits/is_same.hpp>
#include <boost/icl/type_traits/element_type_of.hpp> 
#include <boost/icl/type_traits/segment_type_of.hpp> 
#include <boost/icl/type_traits/size_type_of.hpp> 
#include <boost/icl/type_traits/is_map.hpp> 

namespace boost{ namespace icl
{
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(iterator)
        BOOST_MPL_HAS_XXX_TRAIT_DEF(reference)
    }

    template <class Type>
    struct is_container 
      : mpl::bool_<
            detail::has_value_type<Type>::value &&
            detail::has_iterator<Type>::value &&
            detail::has_size_type<Type>::value &&
            detail::has_reference<Type>::value>
    {};

    template <class Type>
    struct is_std_set
    {
        typedef is_std_set type;
        BOOST_STATIC_CONSTANT(bool, 
            value = (mpl::and_< is_container<Type> 
                              , detail::has_key_type<Type>
                              , boost::is_same< typename key_type_of<Type>::type
                                              , typename value_type_of<Type>::type >
                              , mpl::not_<detail::has_segment_type<Type> >
                              >::value )
        ); 
    };

}} // namespace boost icl

#endif



/* is_container.hpp
qZM9b6jDlYKJBSZ1mPWQZ4v82Cot3L3OjIVhDItW9nrxBpwxuyJePDeJd2x6FJ25qjGJzCi7M+pcBP7sakNgMWIuZK0C2pXBAnfmKrKCFZidf7EvKi03z0QRKqLhGvYOLCaDGhxPmgrpMJrQjamw5KbHPyGXrWUxu0f5MB3T5NimQJuiuji7ojjDOg8XToU73oGYmprgaeVja5sa57zxGmMvTaONcTTrnuxewzfPzKenL3Ckj8R5DmznRRPDbUmNCEdbuoCVjMDQ/o5fUU8nlBjcBhh+GrynPQkfmn8eQrFtg77wdAQwHziGDIYzfBN3kHHe8eU5u6l3EqaHYKzUEXc36AxbzQ2kp9HZXt+G6I4TQ+v50HNZ+2MxjFsMR8So1o0GVYEBsCySVB70wLg5KUUC3FlD5E3y8WtM7lw91B9NR0MIAQ0eL6LkFsMYFkVXQg+twHPPa9pm/OPgrVPj24oW67AHG8SKnbSVFtQ6bqg6ycvVOPx1sfhgL73n4avL5ctjvL8xHE0kPQd5KpEOSB2lt4YoUmxMhKiaHzfcP5QO9aeGQ4zB76lVOK5DRasaYir8ADHrFV4yh9QVNPIislUaY9iXpmylymjUHIo2UMVOXbP/1sWVGMc8W5NDTXRYvU6i4pEK9LyC7WK8eX4FzVcb1ny1Yc23GtZ8q2HNFxrWfKFhTX6XJr9Lk9+lye/S5Hdp8ru4bTltbltOl+FdAlfpE/FEhzARzsybHcIoeGEWvAiwyOvQkKfnj6nZ/hl26PIebq0EOG20kNHk/dkkxQ0CyMpX3+sQ3lC2AtdeZXzCXV1iBDRKDFHoipUCelIjWiqJfjkAI8uQClpc32mRfRKg9F0YT27erMExBJPOclUA7zdhowHNwX2vkMW7/7YT03Z0dbq0eJ+Vdm044tLifVbaSMSTi3d/Wskr0dBT8oO4/ZQ0EbefLJdlol5kiM03dWzPl5GrlkPY2KX4HgxiCKE91rjUqc8WEu1ce32+Wulx442a915T3nORWmU0vK6D93y8eESLd6jx9es8+gbiG8J6XPgl7vFXnXinFl+ryI+0d+1R5dEelR6PaHFVPuIiX+LN8tdHIN+Ld7R3KukhvpbTE/y65vx0doTriPM4VguHI4h67xF+h10iuLx78HXtuwCX97r6LjSwWS4NlEV9d+mhdC4cCufC10bC8t4Ihzua3iPyzkWQd4GjqSFT3pmX312aDQznd4FHOohX3j0aVL8H7+pQ3j2aznbQeO8ufO36MMHlneDSD3Awqow9N/SEPY2SRYiZcB2z4Dpnwa2dBbduFtz6WXBds+A2zIILt8+CC8+MY6MH4y9zWbHVZP4Fhp/ssQ9mazVxNOv76804DBTFUQwUIlqh73dQ09MYzu4qmXuxdRoZCnUE+AwpXlR4p8DxksOAUioVs+qGscBoYNdh6sZrDNsjAwP9UW8zWpPHG7YeHeTpdIDpdLL5q6er03mb1no5xqanq9MBptPJxEVPV6dTJ2B+aQtcT1/geh4ErudD4HpeBK7np2uG/Ahcz4/A9fwIXM+PTk9wf/l82EDPS9WnXXQ6glV92kWnA0zotg7FE73euRj3OJJs/clqdgJTobEinIFeP5IjMy6PoTPhhwl53io661v0TtXLkqQlhdBhBmPQyt2QLeLV6Ke5NQG13zoiDFWGoQqp7cpRwupei7PEnz0NI7mZD9p5aamT1iYZg/FIYHO/syddzkcCu3illkok4tzvMB6YeelvI7HOQB3GgmDS91En3myNeaWNaI5HaYgcaSek5T/RE/6Yyr+WXjlN4V87I3/fYDQmTMmeBKUfwtrAxtknh8FM77VRk2QAHa3k7UVHT0yVwSc=
*/