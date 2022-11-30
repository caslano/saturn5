/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_ARRAY_ITERATOR_26122005_2250)
#define BOOST_FUSION_ARRAY_ITERATOR_26122005_2250

#include <boost/fusion/support/config.hpp>
#include <cstddef>
#include <boost/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/fusion/iterator/iterator_facade.hpp>

namespace boost { namespace fusion
{
    struct random_access_traversal_tag;

    template <typename Array, int Pos>
    struct array_iterator
        : iterator_facade<array_iterator<Array, Pos>, random_access_traversal_tag>
    {
        BOOST_MPL_ASSERT_RELATION(Pos, >=, 0);
        BOOST_MPL_ASSERT_RELATION(Pos, <=, static_cast<int>(Array::static_size));

        typedef mpl::int_<Pos> index;
        typedef Array array_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        array_iterator(Array& a)
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

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
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
            typedef array_iterator<array_type, index::value + N::value> type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
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

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(I1 const&, I2 const&)
            {
                return type();
            }
        };

        BOOST_DELETED_FUNCTION(array_iterator& operator=(array_iterator const&))
    };
}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename Array, int Pos>
    struct iterator_traits< ::boost::fusion::array_iterator<Array, Pos> >
    { };
}
#endif

#endif

/* array_iterator.hpp
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
*/