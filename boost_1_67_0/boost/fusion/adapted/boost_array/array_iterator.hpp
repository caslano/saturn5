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

    private:

        array_iterator<Array, Pos>& operator=(array_iterator<Array, Pos> const&);
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