/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_END_IMPL_31122005_1237)
#define BOOST_FUSION_END_IMPL_31122005_1237

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/mpl/mpl_iterator.hpp>
#include <boost/mpl/end.hpp>
#include <boost/type_traits/add_const.hpp>

namespace boost { namespace fusion
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<mpl_sequence_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename mpl::end<
                    typename remove_const<Sequence>::type
                >::type iterator;
                typedef mpl_iterator<iterator> type;
                
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence)
                {
                    return type();
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
6xX3Ys/ogn4Jh64pmye63v4DzTs6oyat/Sm1yo5YP+EDmkeT+Jf9i2s95nvWlxNLY9deQ8SrzNGraz7FUCeNsXUGZU5D56rapj1T+rrrlu0q2EPc7WVjNqyA2/V8ZcbBv53lzKlfOvXgc+oP0G7Wuq7kOdNu5jlDZ54z0e835Zl5LsSPvbXLObH7g9HF8n6u+3tCtfO4uNljzmmaaFl4Y74pC2utDVg3wZJfCW7CcDach531
*/