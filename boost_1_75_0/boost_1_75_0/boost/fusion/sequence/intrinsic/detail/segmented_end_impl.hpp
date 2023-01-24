/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_END_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_END_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/container/list/cons_fwd.hpp>
#include <boost/fusion/support/is_segmented.hpp>

namespace boost { namespace fusion
{
    template <typename First, typename Last>
    struct iterator_range;
}}

namespace boost { namespace fusion { namespace detail
{
    //auto segmented_end_impl( seq, stack )
    //{
    //    assert(is_segmented(seq));
    //    auto it = end(segments(seq));
    //    return cons(iterator_range(it, it), stack);
    //}

    template <typename Sequence, typename Stack>
    struct segmented_end_impl
    {
        BOOST_MPL_ASSERT((traits::is_segmented<Sequence>));

        typedef
            typename result_of::end<
                typename remove_reference<
                    typename add_const<
                        typename result_of::segments<Sequence>::type
                    >::type
                >::type
            >::type
        end_type;

        typedef iterator_range<end_type, end_type>  pair_type;
        typedef cons<pair_type, Stack>              type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static pair_type make_pair(end_type end)
        {
            return pair_type(end, end);
        }

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call(Sequence & seq, Stack stack)
        {
            return type(
                make_pair(fusion::end(fusion::segments(seq))),
                stack);
        }
    };

}}}

#endif

/* segmented_end_impl.hpp
ucoTU0CvZ6aN3NulRsTTh/XKR28eUdGaobx7gEK58U6d+aIBcVQGppMMzDmPDPzWeh4ZaFSby6vNpWql81Qrn73aXK0TCPKr7u8A8pwLkt4Dzge5JrH33h0Vgdvujkrsbduj5L/499Eynfj1LLx+8e5Y8LQekAi8kvOAx+LP0wNtq+VYF5yn2sHnq1abcQd3V84GeeF5mthtOW8T1FG70xSjMx+b2JaZZe9UZf1k4mFQcks4C88i3m3ci7zbFrhiAm7K+fA/D3CGkPPIKWu/PaPyKKzcKwyjg42vMyRexwTIPQ8Af407b+/QDHvPXdHZtjcAcpbmzjeQnOdvjuSn7zlqjpSB/ZOj+spdz0Vl78D7YoiUzolUolyMT7V4IBLRp/BLnT5GQVjBEHy8wDVftiJgVoxk0OLJnBOnqebzjlwalatXdSAcsi6Ih1PO10THMud81X5s+p+k5fmE8D1nr1YnMp6SDifdEdW8AivpGre7wr/c3oGYovFU/sL5yXEIjzpckKTK+m8k1bKzV5sVK6meu/esk9f5xmL/8zXRcbXng7z+zP9UbdZ5qp19vmo1LfTo12eMhdN3/JomowP8mnSXnV+faas8eDEKkc+qfFWlchUhuPvsYnbqeWDdefo8PKHB9HCMynf06bbipZXyM7GDjsu9oJm+4OzAZMXIfPkBqMjsqF2QC+XRs5eFtHaNSaECV/tS0+QcNOZX
*/