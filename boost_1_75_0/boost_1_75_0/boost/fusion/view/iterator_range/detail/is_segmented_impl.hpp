/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_ITERATOR_RANGE_IS_SEGMENTED_HPP_INCLUDED)
#define BOOST_FUSION_ITERATOR_RANGE_IS_SEGMENTED_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct iterator_range_tag;

    template <typename Context>
    struct segmented_iterator;

    namespace extension
    {
        template <typename Tag>
        struct is_segmented_impl;

        // An iterator_range of segmented_iterators is segmented
        template <>
        struct is_segmented_impl<iterator_range_tag>
        {
        private:
            template <typename Iterator>
            struct is_segmented_iterator
              : mpl::false_
            {};

            template <typename Iterator>
            struct is_segmented_iterator<Iterator &>
              : is_segmented_iterator<Iterator>
            {};

            template <typename Iterator>
            struct is_segmented_iterator<Iterator const>
              : is_segmented_iterator<Iterator>
            {};

            template <typename Context>
            struct is_segmented_iterator<segmented_iterator<Context> >
              : mpl::true_
            {};

        public:
            template <typename Sequence>
            struct apply
              : is_segmented_iterator<typename Sequence::begin_type>
            {
                BOOST_MPL_ASSERT_RELATION(
                    is_segmented_iterator<typename Sequence::begin_type>::value
                  , ==
                  , is_segmented_iterator<typename Sequence::end_type>::value);
            };
        };
    }
}}

#endif



/* is_segmented_impl.hpp
P+JkqHNeuzNLn3f++UHtxc7NNZZtjJsUe/rZUTV3Nny+Z26tIc93d265J/rNr/MHH9q6ZH3LG7s+kfhUWN9dLz376lbnprpxg0JT4xYVN33+/2ZG9vgl8fyM6HMg9rGR0063b3bk0qI/9jZd1ObtXuN3z+h416yfNzj31p8X/8z3iePHpM0/OCt251U3xp8Ka34oatzm4PgvWhzParog5K8avT6OWDyh46Svr/3X5L0Pf5Hx1dgmsY90DD3+9qRZbRuu/nZtq4/+jJ96w8sjv/n15mNbRrxxzZqHInuumP/ZU90mNfo+7vKdJU+s+qrnjMHPHR6/7rd+J5pnvb92Y0nCnI1zO7VY1fKDNZOOXX3kkx5hC/o1OnZ1/KHJT3Wa/G7DXwp7vbrvj2bXPHD2zXfzxv/855rMsA3ru77w8707W6ysdS7iydmO+OVRq/vndpr84SPztzb77c8ukc+Gu1+5rKThwXUHTn/z9i2bnOunfdp43KrQY/P3ZD+UvyMuatuheWtKbnhs5oi37p3Y4PHB0etyrkj77j/7/5F+edHGaZtDE6Ysu+b99F0ra/U/c/mGjBfnRDzc/q9TpVvO/jbydXDgzeX1EiZvqTstduI9Iz5fcouza//zsRvqO/ce/XfiTRmran7+yaC9kWtAves/f+K73Q9sLn1veovazvU9Zl7e6bmaxx545Ju7ttRfGjl1T8QjI18odi39
*/