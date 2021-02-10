/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_DEREF_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_DEREF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_impl;

    template <>
    struct deref_impl<set_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                result_of::at<
                    typename mpl::if_<
                        is_const<typename It::seq_type>
                      , typename It::seq_type::storage_type const
                      , typename It::seq_type::storage_type
                    >::type
                  , typename It::index
                >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(It const& it)
            {
                return ::boost::fusion::at<typename It::index>(it.seq->get_data());
            }
        };
    };
}}}

#endif

/* deref_impl.hpp
6aED8jMHdXp3KH7HcHmUOoqjs3mIWSCukKhEUzYx1LIHFqzy/NLZCxKuo407drDWknOzaLa+Nmf4SLWgXfZhvgnAhykLrrZD4VDgtewsiMA/RRseNhEnmjmrbLu3EhE5zhjZgGYbKZptijX4vUZFg4N811rsBO44U+OwwCHAHFpfIHF1dgXZ28JZRBt1bro9Nth6iSjOzqAPi7rb4WiY8QUG8ZpngZ9rWOmEthFwlSPg5v2Fh+cxPVwwncCHA9ETwGjGr+z9G9yl6zzLTKyL2SDVCxtQYcuKmnJ56sEvgv2BUVU5ngWP4IvUk4F6yYLKnBg0l8pDqk4X7wVSZ0TzYoviutiltXdZPS2iRbDMg6utCOdBpoab504UrCn4glPsB560KkOovIQncflPedxa0KfcKRpWR3e9K8OtzxX0GyG4kNxTy9NCTMV2AUWojjgGN5K/y6Fl4ol1kj2juL9CDiHBHS9ikCqMuHoFSZyu8aHcFtVw1fNbZUTnlqkX1KAIkpD7ykIGkTrJgOtQS4XaWgHdPdXg7+smwrhBLF4iQrX4sWU1B63xl9v5LYPKbCPQfqS0e2avXbVhl43+nsNtXW8I+C9Yl2AZ5Op07CsI/g9MUB7gVEamL2Y69v0Gteo2+7Gf0Pe98QAphCJq
*/