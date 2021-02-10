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
/4OIORrzLuKgcxwi+Om2Z7vAdWmviekCeDT5nNwUmGtCxy9StknNDR/kkUIwuEUtpTb7gPpFPsmRz5x1aWJws+vbnsjVntI/wsE4tryzw63S8UCRYAAFQUJMl6lfXE+DPnv/w97e7X0tTzOxcKr+VoRQZsj2CoOvqJh4oHYBZxgFCWC2O/nAtaXNlz0psOl7gxpjBWqKs1vFLEdotR6GEc3KYkIFOVnDQ8mgGtSWTFYsOdrww2QdHnDsX1p4/i8nGr5NO2o5z/DT5UzDz6/uL7kJ4IX9Qg4kDy55h6FBfx52dvBqC41sA/si5WqO82+lj8pvzN06OD199uZtevS+eaJcMEYUxduAacKUS1hKwme8HOr3Ar04Vr40IU9Rn5e3BIJQNcYaJvAFMfBcnoAO9fJyT6oqI1BHgY+jDQJBOYr/TBYloq+3W8GwcON7kiJJuDSxnFuJ854QIhAU3AylU0UmX10SLUgOTQXM8dQ9mu0JuJUsJBpvmynEwHB6I2SsAoFsOlak9szpd2ceQn9eHrwgOPtoyhC9rlPhel2xz1W1MX19LCoLPBG4GeIKnVXl9YpvEb47jPNqsgbsnHA44Von1qiuFoRSMlhMaM1xapO96cvrMavRJkmTKlY+TWsP7hf376uTgRsaoG7G
*/