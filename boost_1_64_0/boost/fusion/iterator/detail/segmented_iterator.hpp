/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_ITERATOR_SEGMENTED_ITERATOR_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_ITERATOR_SEGMENTED_ITERATOR_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/iterator/iterator_facade.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/deref_data.hpp>
#include <boost/fusion/iterator/key_of.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/value_of_data.hpp>
#include <boost/fusion/iterator/detail/segmented_equal_to.hpp>

namespace boost { namespace fusion
{
    struct nil_;

    namespace detail
    {
        template <typename Stack>
        struct segmented_next_impl;
    }

    // A segmented iterator wraps a "context", which is a cons list
    // of ranges, the frontmost is range over values and the rest
    // are ranges over internal segments.
    template <typename Context>
    struct segmented_iterator
      : iterator_facade<segmented_iterator<Context>, forward_traversal_tag>
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED explicit segmented_iterator(Context const& ctx)
          : context(ctx)
        {}

        //auto deref(it)
        //{
        //  return deref(begin(car(it.context)))
        //}
        template <typename It>
        struct deref
        {
            typedef
                typename result_of::deref<
                    typename It::context_type::car_type::begin_type
                >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(It const& it)
            {
                return *it.context.car.first;
            }
        };

        //auto deref_data(it)
        //{
        //  return deref_data(begin(car(it.context)))
        //}
        template <typename It>
        struct deref_data
        {
            typedef
                typename result_of::deref_data<
                    typename It::context_type::car_type::begin_type
                >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(It const& it)
            {
                return fusion::deref_data(it.context.car.first);
            }
        };

        //auto key_of(it)
        //{
        //  return key_of(begin(car(it.context)))
        //}
        template <typename It>
        struct key_of
          : result_of::key_of<typename It::context_type::car_type::begin_type>
        {};

        //auto value_of(it)
        //{
        //  return value_of(begin(car(it.context)))
        //}
        template <typename It>
        struct value_of
          : result_of::value_of<typename It::context_type::car_type::begin_type>
        {};

        //auto value_of_data(it)
        //{
        //  return value_of_data(begin(car(it.context)))
        //}
        template <typename It>
        struct value_of_data
          : result_of::value_of_data<typename It::context_type::car_type::begin_type>
        {};

        // Compare all the segment iterators in each stack, starting with
        // the bottom-most.
        template <
            typename It1
          , typename It2
          , int Size1 = It1::context_type::size::value
          , int Size2 = It2::context_type::size::value
        >
        struct equal_to
          : mpl::false_
        {};

        template <typename It1, typename It2, int Size>
        struct equal_to<It1, It2, Size, Size>
          : detail::segmented_equal_to<
                typename It1::context_type
              , typename It2::context_type
            >
        {};

        template <typename It>
        struct next
        {
            typedef detail::segmented_next_impl<typename It::context_type> impl;
            typedef segmented_iterator<typename impl::type> type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(It const& it)
            {
                return type(impl::call(it.context));
            }
        };

        typedef Context context_type;
        context_type context;
    };

}}

#endif

/* segmented_iterator.hpp
91YLHz6e77FTGz9LndGNtd4mhuCPYjX4xM3URcSARBLaZ6Bb5eh0V+yRXCXFKMh/E5yJWsjFv5X5kH/6+hJyHPToO3z0tegH/itOXErhy61/kTfHiW3kyL7p/D0c34Q/tuYX8x1v4uwCbHcIvblPkD3f84+Su8Sp52Jr0Ps9yOD1EmpBdPICzpOWsNZGcqf7kOf7/ZA5a2y00AX8RjH1J32/FH7eZ8c3znliLxMrxsAz+pXpx3szN38/0J/8nj3+nnx/P3Kf7cz9IP2lE8hB6+DdNexhHXPdj64PHk1MwJ8SwzKcnYR4Z4ugh+UtgW7yL95Hjp5S5+0hjmyBfmqEODEwPo46iM/RX3TH39t6jFyiPYgh3DOuPz6F73mcPwx7we+yz/QA7L6UPHvFAM42mP88dGx/9hVEHrxX2Et9Lohbvqn0ULCr+NfY1kBqve7j6GVgp9TTAlXuJPbuFT/9/PTz089PPz/9/PTz08///cf7O2q4W4WgxSy68rkTv864l59hPQ75rGo+udyRQkyeIrjOeFin9nEM769kFP3uLGLkFRp8/4FRfNADOONQib/tdPAYe08Bj/GTvt3ax5EvA2c8ZytwxvkzuI/xwWOBC+Y/CnzGb/hfO9767ozMe7Oc93PwGZ/br5iRVxg8x3XGi57nfsbH+PcOGcWR25if8Y5PBCPzbeA+xrZnwWOc6eEz42eDujCyTorPjGU39mofDz6UzwI8P/czvv42nxnv2QG+AD6dUTDv5eALrkclHyU/Du4OnLHcz32M0+5iXcYVb/dkhA/9oY9x0DzuYzyZ//Gf2DyB+xkDA4ELPl/A/hnXbOrKCN+nMI9g/w8JRva5ErhgH09ynfGqz/gsWLc/dAnWPYLrjH+rh6+Muw5jFPDrYa4L1lnHKJDTB8wvkOct0CfAO1DKO8N1AZ9HQQ9jYz3zCvj4iKTjafAE8r8Xehgv+X0RI/ua2J0RPmwCT7CP9YIRej4QjPBBdGFk3rvAE8j1B4mX4bNAH0qZV3D/sYwCPXmZUTDvZ5LeLfBJcP9J0CvA/4x5Gav3k3rXKvkp9fZP49AXxr8ML2KEzoHsi3HJROCMO9qYR4C3gv0J6PmM64L9vgA+41sPS3kNhW6BnMcKRuiaK9e/jc+ME4Z0k3QKRvh4M/cJ+NVXfpZ07f9vRsYb6GG3y0PqV7+uUj8EdAg+X851gZ7J+doekPw4HPoF+/1ZESP6KeHlHimHbsAF865ifsF+hgpG6Hqd+wV6I/XpsBXYi8A+I1wX6Mle6BfMI+31y1ZGwb4egd+MGx7is4CuF4sYsY/OzCPQo1e7M7KfCvAYL/uG6wI6HuQz4/ebGQV6Sh+tXd8T4Av28SajQE77sj7jCScCF9D3e8GIfhVLfXmN6wL5HVzMiF5cCX8EdB4OvwTy2Cvt9DVGRl6Nxwh9m5hXoA/X8JnxBal3W/cTjOynP58Ze6yUfuQI+CGwgyLoFeCfyz4Zb7mN9RjHOOs8yGfBfp/pKvWEz4L1zpR8P5N1BXozAboFfJV+7rE5rCfAHyP93SWMAjlsBy5YbwejgP5LpL97TzCinz2hSzDP0O6M6G0n5mU87Qapn8XFjPivgwQj/rKHtNdRUm/eYj8Cuc2V+7yfdQX2eAb0CvbzO/gogF3MfQK96gadgnX3gx7BPo+U/nAro4DfXwlG5u8l48PhzC9Yvyf3Ce4/FzyBXhwE3QK8qVwX4JayDuMHD0n9HwrfBPunfm/fdyP3CfThKugT6McQGQ/qoEswXib1+wAZNyZBv+C+B6UdLwZPIK9LpR7tZl2B/9xH+v+vixjRx258FoyPQ7dgnsMFI3pyBSPjyC9kfNjFKNCzjZI=
*/