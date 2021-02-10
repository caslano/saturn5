/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_AT_IMPL_SEP_24_2009_0225PM)
#define BOOST_FUSION_NVIEW_AT_IMPL_SEP_24_2009_0225PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>

namespace boost { namespace fusion
{
    struct nview_tag;

    namespace extension
    {
        template<typename Tag>
        struct at_impl;

        template<>
        struct at_impl<nview_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                typedef typename Sequence::sequence_type sequence_type;
                typedef typename Sequence::index_type index_type;

                typedef typename result_of::value_at<index_type, N>::type index;
                typedef typename result_of::at<sequence_type, index>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return fusion::at<index>(seq.seq);
                }
            };
        };
    }

}}

#endif

/* at_impl.hpp
26k/fudAy7oVeKkR2LG/u++7u/hoiVxlmMPVsDcYzlj/ZnbNLuPp9WgeT3uzOW1dBS0CCIV7MVHn/UYAHTg4WPNlNGhuLKZG/8TUvY1m7AnWH7K6o/kQSQRbkyd2DIdNnqDdmLANy4VfM3aI6M5r8z+Rt7xjfkk7ZOYt+7p6NGJZOGj3j+Hj2dkn+ACnJ6cnIQy4Eihh7lAlaJYhXGTNzteCPzx0LX4JAR1w2d24igthwerc3XODQGspUlQWM+AWMrSpEQk9CAWuQMiFROhPpovR+HsI94VIC+/kUddgC13LDAq+QjCYolitfVTcONA5mZPzTFhHDmsntOoSN4JDU1rvw9NzaTXwFReSJ0TEHRTOVfZzFKW1kaQ+ynRqo/Q5/G7hypdIFiSi5I+gKwdOQ20xBI8ModSZyP1MCaHNqk6ksEW4VUNUKou0AYtSel9kJ9CuZSPMN+kJPQwqUiycn6xW1lPdF7p8BaQ8ei95bRQRUR4IlGlKcwg1XSzTgJvInyk2OW0SvLM0W70ZaEVi4Kg3h9H8CBJuhQ3hdhRfTW5iuO3NZr1xvIDJJfTGC+/sx2g8oNILIjOAD5VBS+QGRFlJgdmG8/1GFLSESmWdIRz54jGLrq66xVFAB+vu0rSMwWje+3Y99K0joH4B
*/