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
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
*/