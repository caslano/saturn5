/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SIZE_IMPL_31122005_1508)
#define BOOST_FUSION_SIZE_IMPL_31122005_1508

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/size.hpp>

namespace boost { namespace fusion 
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template<typename Tag>
        struct size_impl;

        template <>
        struct size_impl<mpl_sequence_tag>
        {
            template <typename Sequence>
            struct apply : mpl::size<Sequence> {};
        };
    }
}}

#endif

/* size_impl.hpp
+m9SryxikRYXIKr1IGtss84xLia4LadcA+XGwVOZVJBxdOpq7Eo9CmL3SVTz56Sn1XwzNO8xYNU2BwAz3b6WpiLCuoosRmvC58jorOORnFw5vDRZUizzB5afc4l97ruYy1VuX8SDdfE82spwtvjMp7bJTxdgW45FmDtrKWatc4r45Xo6NERY2iSQBIilz9dvTfF6FkIeY04S57j2ekCW5F0VdmqJCG3zAGnJXsfWX8yrmweTSrfeF7Yop7ANUrVz3H+7VUeqnFZeKZkmgqiUWqcjLycfI9bjVi4YMMTUND6Lk7DKzlbhIYKZ8i2POE6feIvXIO8ha97vqxSCmcJRejfsJZ9pQoShvcrxLUOtS+M/TDkMIS5tpi5yAtJCmN0Y884vzdXPRhX8RzdPG1TGqSJMiYs3G+GiGGG5IOwaD/mpVN/w2NqSWAWqbr568uMplDk3JbvFCnAMStmvHTkTu5vnb5T7KnGrZp3ojbCmd85gdUp4UNE8sqRv+MQ3H0658NiLsrdK9wDsm3pa9gApH3YlL28bikOeqaAvizz7uWVexAgwLmmaGxLS/w==
*/