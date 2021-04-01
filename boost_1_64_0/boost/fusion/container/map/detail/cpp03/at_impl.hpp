/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Brandon Kohn

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_DETAIL_AT_IMPL_HPP)
#define BOOST_FUSION_MAP_DETAIL_AT_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template <typename Tag>
        struct at_impl;

        template <>
        struct at_impl<map_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename
                    mpl::at<typename Sequence::storage_type::types, N>::type
                element;
                typedef typename detail::ref_result<element>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& m)
                {
                    return m.get_data().at_impl(N());
                }
            };

            template <typename Sequence, typename N>
            struct apply<Sequence const, N>
            {
                typedef typename
                    mpl::at<typename Sequence::storage_type::types, N>::type
                element;
                typedef typename detail::cref_result<element>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence const& m)
                {
                    return m.get_data().at_impl(N());
                }
            };
        };
    }
}}

#endif //BOOST_FUSION_MAP_DETAIL_AT_IMPL_HPP

/* at_impl.hpp
rQyrTKcog74Juv6w22fannhHilzMMMSpYika92Gy+Hhc6j9hMWi+Bp0CnG/fTKNGUmLDpWSgesK4VD7h6kPRE/Ua2uof3cwG5n1q8AJZVb6TNkgcv/OiSKDVQH98INVtnITf+ygh7mk12sRIxzXj+bCjhvJwaW6QolKgXP9OJpOhdb0z+2/KYoGast6F79o/SftPhku3jmSb4LqgzlqA6CcfHi2fzv4GPKeaz04Nz4Cz12U5mx1coBv5JuW6e/BXyqAWs1SB+ee0PCt031XliwxiIsLvM1Rd6dEf0gFvutobQb5xeqqm3HhCGuZVPzeUNx+t6i+sO7dWfGKH2ULBqUbxasL565GoyWRQuEolRZLlKDZcO10qdplSYpSROB5M8d7KaUzyL+fd4zvcQRtwQynb/cBOz45qs9EYmS3QWOZPiGmJayav0AOUGZ0q7zlKCRIs60sU58SxUi1Mo88E8FWBCQ9ycYMiwwqIuWukSY/ElLf3AlviJLzw7ORz2yLfbv8xhXxN7lFNWneK2qZGNLGS2QWly/mk40d1Jxi4mL12fd1Lh9DU/acymg==
*/