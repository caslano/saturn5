
#ifndef BOOST_MPL_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/joint_view.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/iter_push_front.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>

#include <boost/type_traits/same_traits.hpp>

namespace boost { namespace mpl {

// default implementation; conrete sequences might override it by 
// specializing either the 'insert_range_impl' or the primary 
// 'insert_range' template


template< typename Tag >
struct insert_range_impl
{
    template<
          typename Sequence
        , typename Pos
        , typename Range
        >
    struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : reverse_fold<
              joint_view<
                  iterator_range<typename begin<Sequence>::type,Pos>
                , joint_view<
                      Range
                    , iterator_range<Pos,typename end<Sequence>::type>
                    >
                >
            , typename clear<Sequence>::type
            , insert<_1, begin<_1>, _2>
            >
    {
#else
    {
        typedef typename reverse_fold<
                joint_view<
                    iterator_range<typename begin<Sequence>::type,Pos>
                  , joint_view<
                        Range
                      , iterator_range<Pos,typename end<Sequence>::type>
                      >
                  >
              , typename clear<Sequence>::type
              , insert<_1, begin<_1>, _2>
              >::type type;
#endif
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(3,insert_range_impl)

}}

#endif // BOOST_MPL_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED

/* insert_range_impl.hpp
c7Bj2/G7T9a/+Gnh4Ul185yZdTz+5S8Vrw1dUv7bjZcW71zZ9M68hlXtv4vznnPEf0Bgq5G+ewpMfmXYdGFq39cNqr/8de+YHaP7/Dz8+xPaZdXORv6Wv9zxRrNXJP9lhLNjRNBcw7CtjS7niit/9IVzjwiLjT8+WvpjpwRNxIx7I++lLbc9vq30PUPBJxfn3N9yrG5kuzO5fn54bvjqSr+uXVyzZtmmlV2nLzmwK2RhnXrbOup+OTzmw+oTU28UvPAXt3azrJ++vvSoeV7vo6NqvJpWePK5DrEdVj9p6dth+ZHr1j/cub3+5E/FJgzw2lSq6u5RnTWtrB/2ndenziSLGN34d9Wb53nfs0T/37qcuvydW1fHBwVanwufFHD+x6F2C+p96/SmR2LjAil/VFh2rM6hgI2P7xa/2XhN66E9rp+a2zTmmd+QY07OO+sdjHl49LVPr+Uf/Z0i3a9/c9kjLv75r4eb7AvdXLW2S33/Zov2RO8tUciu3K1tSW0bV2w+wz5tkMXSBtd+s7Ode2fdham7uwYHjP19WNSGWmd1vcPatOi26QT8veHvA/+98P8B/r/D/yn8/wr/7+HvB/9X8J8G/3Lw/wD/8/AfDf8p8G8L//7wnwX/m/C3hH9++C+C/wH434f/DPinwP8S/KvB/zT8K8HfA/4D4B8H/4Hwvwr/DfAvDP8Q+K+DvzP8x8C/H/w94X8D/mPhXxz+0+HfHf5F4D8e/hvhXxb+t+DfDf6V4Z8T/lbw/xH+S+D/DP5r4b8F/r3hXwX+38E/Ff4L4H8U/mfhXwr+E+E/D/7z4V8L/nr4N4D/cvjngH9n+L+Fvzv8V8G/FfzXw98G/pHwT4O/C/xnwv8I/AfDfzv8J8C/Pvwvw781/B/A/5DkH/4J8G8D/xXw7wj/9/DvCv+S8K8A/2D4l4b/Sfg3hP8a+DvA/xT8f4J/J/gvhL8W/oXgnxv+d+HfEv4l4J8H/ivhvxn+yfAfB38v+G+F/0f4/wz/bfDfD//a8I+F/xX4h8I/CP6H4e8I/2bwV8N/BPzfwD8f/MPh3x7+z+H/CP4n4B8G/9nwfwf/MvDfB/+i8L8A/yfwPwj/3fD/BP+68D8O/4rwLw//xfC/A397+M+BfyD898DfAP++8H8J/x3wHw7/ZfD/Df6N4P8X+EfAfxj8c8H/Bfwt4L8U/hr4j4S/Lfzvwf8i/I/B/wz8z8H/V/jXhL8r/HfBvx78f4H/avgXhH87+L+Gf17414D/ZPh3gL8v/K/D/zb8i8F/E/xHwd8a/n3gHwP/6vDvCf8u8HeDfwH4T4L/UPh/C/9E+P8B/zrwfwz/xvDvAf+m8B8C/53wfwj/XvB3gv838I+HfxP4V4W/P/yj4W8H/yT4N4f/IPhfg/9c+E+FfwD8o+Cvg38L+P8F/hr4L4Z/X/gPhL8n/LvD3wr+7+AfDv9Y+HvB/zz8f4e/B/wXwb8n/IvBPy/8d8FfD/9U+M+E/1v4+8N/LvyHwr8H/BPgXxr+Wvgnwz8R/kPg3wT+g+DfCf4r4b8C/g3h3w7+NeHvBv9R8B8M/1Xwnw//KvAPhf9H+IfB/w38T8PfEv5T4P9X+FeE/x74D4O/LfzHw38J/AfAfwz8i8N/Hfyfwf8W/F/Afwf8A+H/Cf4+8PeD/034p8D/EfyfwP9n+DvCfyL8c8DfBv7b4T8Z/n3gfwb+BeH/Hv4P4N8S/j/BvwX8k+DfC/5/wD83/B3gX1LyD/9v4P8Y/lHwj4Z/Gvzrw/8s/BvA/yL8f4G/L/yrw78//O/D/wf4T4P/fvir4d8e/kXhvwX+leF/A/6F4W8P/4PwXwr/ZfAvAv+c8L8K/37wLw//l/A=
*/