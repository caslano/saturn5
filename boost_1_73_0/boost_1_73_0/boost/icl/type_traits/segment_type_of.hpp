/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_SEGMENT_TYPE_OF_HPP_JOFA_100902
#define BOOST_ICL_TYPE_TRAITS_SEGMENT_TYPE_OF_HPP_JOFA_100902

#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/icl/type_traits/no_type.hpp>

namespace boost{ namespace icl
{
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(segment_type)
    }

    template <class Type>
    struct has_segment_type 
      : mpl::bool_<detail::has_segment_type<Type>::value>
    {};

    template <class Type, bool has_segment_type> 
    struct get_segment_type;

    template <class Type>
    struct get_segment_type<Type, false>
    {
        typedef no_type type;
    };

    template <class Type>
    struct get_segment_type<Type, true>
    {
        typedef typename Type::segment_type type;
    };

    template <class Type>
    struct segment_type_of
    {
        typedef typename 
            get_segment_type<Type, has_segment_type<Type>::value>::type type;
    };

}} // namespace boost icl

#endif



/* segment_type_of.hpp
cmxtc2dfdm1zLmhVVAUAAbZIJGC1V21zm0YQ/lz/ih3nS5pRJUdJmqZNO8VwkhgjINwhW206DBYnQ4tAwyHHnqb/vXuHQICVejp18UjgfX95djk9S9ZZxNcwI5pBvED3PWtOp8FiToPZyTPkJBk/zhy9eLrrBF7Ao1egPgFeeFcabpH/zlflcekg+AzVH2p9xPtjTkZwUPkcfA2Pq3yG50ol2Ht5L5+D4DFHH2Vs8mskNT8G8hEpqCY19Xx7XyQ3cQnP9a/h5bt338E3MD4bnw3ACLOEp0BLnl3z4mYA7yNF+TkO7+6Ggv80AF5CmA73plicCBD5uvwUFhzwOU1WPBM8glBAxMWqSK7xnySDMuawTlIOuuMuTXs6gE9xsoqlkft8ByLOd2kEcXjLoeArntxWNrZhUUK+RnU0HiWiRIO7MsmzIfrmUPJiI6QN6T5MRQ7hbZik4TU6CkuIy3Irvh+NVrsixehHUb4So1Wd/jAuN00mSwxiE95Dvi2hzGEn+ACk5AA2eZSs5R0LgsTt7jpNRDw4RIOusmiUFyB4mkpbqJdwUYXNge7LM5BisMWIk1LeRJ4J6epTnG86glhHaWW9KzJ0hHVAoSjHMg9gh6NUKGGVee1iX1NV4C+25hBvBHmGwcCpRsGkp3Ad
*/