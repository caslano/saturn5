/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SINGLE_VIEW_ITERATOR_05052005_0340)
#define BOOST_FUSION_SINGLE_VIEW_ITERATOR_05052005_0340

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/view/single_view/detail/deref_impl.hpp>
#include <boost/fusion/view/single_view/detail/next_impl.hpp>
#include <boost/fusion/view/single_view/detail/prior_impl.hpp>
#include <boost/fusion/view/single_view/detail/advance_impl.hpp>
#include <boost/fusion/view/single_view/detail/distance_impl.hpp>
#include <boost/fusion/view/single_view/detail/equal_to_impl.hpp>
#include <boost/fusion/view/single_view/detail/value_of_impl.hpp>
#include <boost/config.hpp>

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning (disable: 4512) // assignment operator could not be generated.
#endif

namespace boost { namespace fusion
{
    struct single_view_iterator_tag;
    struct random_access_traversal_tag;

    template <typename SingleView, typename Pos>
    struct single_view_iterator
        : iterator_base<single_view_iterator<SingleView, Pos> >
    {
        typedef single_view_iterator_tag fusion_tag;
        typedef random_access_traversal_tag category;
        typedef typename SingleView::value_type value_type;
        typedef Pos position;
        typedef SingleView single_view_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit single_view_iterator(single_view_type& in_view)
            : view(in_view) {}

        SingleView& view;

    private:
        single_view_iterator& operator=(single_view_iterator const&);
    };
}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename SingleView, typename Pos>
    struct iterator_traits< ::boost::fusion::single_view_iterator<SingleView, Pos> >
    { };
}
#endif

#if defined (BOOST_MSVC)
#  pragma warning(pop)
#endif

#endif



/* single_view_iterator.hpp
lyqd/TJ5JWOQHypTxMD9HZKOICuA/XC2YZL/Uqd4+Wn5nu+/YAmm5HPyrlZFiD5/xFuF3saUfJcm6cs9nT/s2NPyPd9/2WS51qQFi+RfPUpi/YKlm9NZX/T+yuTRF0kL1smzqS/y1em/XZARrtLf3Oeft8D7/+T86Xhkb7kVdfqe97fL5ye79Sh9G2Slp3R7t+QLzhd9hUas0idhcc7zPGkVYrEi6ftJfsaYLHudbEGeD2vkcT7KPaT1yH5i37q0yiRdckvWlqxknaTc0ycMF/mmlOXadd/wd0fpgyG9gznpdLyvNn36Fo6s7+sV6N5euuKmdzkc54/9aCRflfYff3VOv7emNU75uvSuh3D80Si78unyp1PKUFZBdrzW/aj0/lZFSoMikJuqCX7eLv3/9fz16fmw0vhXozJFaOxW8i36NNdf9iRzn/ZlyN4fGreKQmejUjSHfKtylk2Qb++TR0tc1CVNXiUr/bR89bPlW9N3bZCB3IL8xqydqeSDkE9k98nrbarZPH5Kc8mv5fI1z5ZvSbqCXOyY9MGefrrWfevltfSx6DbOWg+PcFet5pSPzOiaIhvyz1Xy0V/NP79JfaHXDV7T7WEHp6M+uKbzfguyPmOQv6rTPcMDHNO+rxf5pvSk5Ixdn6nu5HvT+kyTdDEVFFapkk+4yb9y/q8Kcr5d0gd1WpHYd7nLv5BRXZPWqtMbHyVVk94oz1ur
*/