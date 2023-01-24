/*==============================================================================
    Copyright (c) 2013 Jamboree

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_FUSION_ALGORITHM_FLATTEN_HPP_INCLUDED
#define BOOST_FUSION_ALGORITHM_FLATTEN_HPP_INCLUDED


#include <boost/fusion/view/flatten_view.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>


namespace boost { namespace fusion { namespace result_of
{
    template<typename Sequence>
    struct flatten
    {
        typedef flatten_view<Sequence> type;
    };
}}}

namespace boost { namespace fusion
{
    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::flatten<Sequence>::type
    flatten(Sequence& view)
    {
        return flatten_view<Sequence>(view);
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::flatten<Sequence const>::type
    flatten(Sequence const& view)
    {
        return flatten_view<Sequence const>(view);
    }
}}


#endif


/* flatten.hpp
35h8rtQnhWSKN3CaM8OoGDL3L26rBS5eD1xdrFWUWnQbEn2NK0VlTV7Ij8ylq7hDcy5qbCAoZlUXUK8EZrLNXC53N1bc4Mq4vzI4sluk7zECYQ8O2kyNLX+My3Fk2mRrxOprsYwP1DNm9QDev8Nl/n5mtE5E7I4T7Rl+9YxBKyLuLcYwUBR5RL4N8jSIpFeS6FnFJ5roXADP0/6S05SoI/o73zyU61CuiV8X5qT9bIfDtlQ+qCG99LSpbIkRNtkTOmVbXF9DorPsLFjRMRFAfVGD6nFC6vqxiEtdqqsy29RJNONMJTVXIAcLQ90XrF/tN1dIyqZJtK6Iiz007z4oapi4UutgYVJZkSJLHNO2HdO3eZWQ1EURZJA28Ni60DSJmIMF/DxewAUYpJBV/UgKCW4ghZSBXBBxEy33M96idX4SX+8ff5uUw+PfouOYt3D9HwKXLdJueSDv35f3TyHBojuMee9K/B1PlzrQ4Xq68zu56dvueYCKTtHiGtzxcqyQH4CjZYH+9UymtC89kRJOjYKJDZrX0RjoIIz5AcL3IEP6hhO+NZBqvceRuqzHYkooEycSyghfBZ5Upou+FK1wGGBC8MYZ0QY0jtZuCqBnArWaYoKjHWQRhvR5UU0drdTseeuvkPsWcEi5y/so/jdXnIh5Ij10Hx2cDepl1TGUPW8ge16p69khSvQ9pojQFzEGgljPHXA5QXiB3qhA
*/