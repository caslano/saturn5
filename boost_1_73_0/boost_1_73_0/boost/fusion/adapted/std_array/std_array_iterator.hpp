/*=============================================================================
    Copyright (c) 2013 Mateusz Loskot
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_ARRAY_ITERATOR_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_ARRAY_ITERATOR_01062013_1700

#include <cstddef>
#include <boost/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/fusion/iterator/iterator_facade.hpp>
#include <boost/fusion/adapted/std_array/detail/array_size.hpp>

namespace boost { namespace fusion
{
    struct random_access_traversal_tag;

    template <typename Array, int Pos>
    struct std_array_iterator
        : iterator_facade<std_array_iterator<Array, Pos>, random_access_traversal_tag>
    {
        BOOST_MPL_ASSERT_RELATION(Pos, >=, 0);
        BOOST_MPL_ASSERT_RELATION(Pos, <=, std::tuple_size<Array>::value);

        typedef mpl::int_<Pos> index;
        typedef Array array_type;

        std_array_iterator(Array& a)
            : array(a) {}

        Array& array;

        template <typename Iterator>
        struct value_of
        {
            typedef typename Iterator::array_type array_type;
            typedef typename array_type::value_type type;
        };

        template <typename Iterator>
        struct deref
        {
            typedef typename Iterator::array_type array_type;
            typedef typename 
                mpl::if_<
                    is_const<array_type>
                  , typename array_type::const_reference
                  , typename array_type::reference
                >::type 
            type;

            static type
            call(Iterator const & it)
            {
                return it.array[Iterator::index::value];
            }
        };

        template <typename Iterator, typename N>
        struct advance
        {
            typedef typename Iterator::index index;
            typedef typename Iterator::array_type array_type;
            typedef std_array_iterator<array_type, index::value + N::value> type;

            static type
            call(Iterator const& i)
            {
                return type(i.array);
            }
        };

        template <typename Iterator>
        struct next : advance<Iterator, mpl::int_<1> > {};

        template <typename Iterator>
        struct prior : advance<Iterator, mpl::int_<-1> > {};

        template <typename I1, typename I2>
        struct distance : mpl::minus<typename I2::index, typename I1::index>
        {
            typedef typename
                mpl::minus<
                    typename I2::index, typename I1::index
                >::type 
            type;

            static type
            call(I1 const&, I2 const&)
            {
                return type();
            }
        };

    private:

        std_array_iterator<Array, Pos>& operator=(std_array_iterator<Array, Pos> const&);
    };
}}

#endif

/* std_array_iterator.hpp
qawtUFarkuioLDQvlVR4H+oyReXmu0JsWNoqu5J/Z8u2uacgS8oKOv0ZhLMOLJjm2oerMDobX0Zw1Z9O+6PoGsZfoD+6bvHOw9EpaYMTqwK8rRRqykIBLyrBMX1E/kOd7gXRGZxcTofjSRRfTs4Hg0kcjqLB9Gt/GF/M4BA6h/swJktbhXegI/jCSgB+Do4Ogj0asN9iZHodazR2s+lDutIEPTuDUf9i4P0H/vwd7WxZUs+gGKirb4gVKZ22YcmEQ5hdj8aTWTjzfuJlIuoU4dhSNkLMP3sOPZE0/jSTHfsGdnOSiCClvJ6FD0KWNy17vGGPC9395FI4HcxOpuEkCscjbyYLhEpJIxMpdGO0zrMldEjcCRFzXWjnMI0PRsgMNRNi7Wkk9WqLaBTLMp5Y7eAtaYlTPltUbc0vlROpBFcjUkpBNiV/f3Km9hLSHOlmiaV5FJkpssICHaCQtqukNVoYuUT1FzIha5rEFa4oJRJqJpWHt4yER5r3bHMg6yooEVNnLVIn9SduxBoSioB5Fm4L36x+57A7zyYPc/bImwTceLLd5ZVU34jhpFaKciY4+06W9LApL6zIEMBeUMh9La33zqJo0jv4SKbH0rMgryvKTsfbhNZi2yIV/9XsPZpp14ep7TEtB0xcO1Cs
*/