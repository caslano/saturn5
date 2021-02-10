/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_IMPL_07162005_1031)
#define FUSION_BEGIN_IMPL_07162005_1031

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/transform_view/transform_view_fwd.hpp>

namespace boost { namespace fusion
{
    template <typename First, typename F>
    struct transform_view_iterator;

    template <typename First1, typename First2, typename F>
    struct transform_view_iterator2;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        // Unary Version
        template <>
        struct begin_impl<transform_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::first_type first_type;
                typedef typename Sequence::transform_type transform_type;
                typedef transform_view_iterator<first_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return type(s.first(), s.f);
                }
            };
        };

        // Binary Version
        template <>
        struct begin_impl<transform_view2_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::first1_type first1_type;
                typedef typename Sequence::first2_type first2_type;
                typedef typename Sequence::transform_type transform_type;
                typedef transform_view_iterator2<first1_type, first2_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return type(s.first1(), s.first2(), s.f);
                }
            };
        };
    }
}}

#endif



/* begin_impl.hpp
IUaT52AZ9knbAOGybQppcMwhMZV2zDWLHq2MVBC6oZGUxZSU9c1m1bKl5VfvT79dXMhND4LU4ZblNBVHTGro3mbQvFLS77t3O9QtE7zXoW/9zIUYzZUSRcPeDYhPDYKbvMe1EvQwupRTHRsyPGw9D/fOQTWLsQr/hop+Dvzysu5oLTXf4F8GpOvaousgOHEXv1HVQ/u8wjqIjCh1Gb6XdyGG4PBvXCyUke4pBk3+Yu8BkcLUDVacv2ERxqA43kOvV6SJSSpFC0KjhNPICyrjospYqILfGG7i8g6txdR49s+PJiwD6r+AyBuF8ujEvj2hr/hX5rMiShBy0ygtq6UF6HSWOs1Hd2wp0jI1Bae0TfH22fdbdO9Px1ZMPVwQWoduVrotncRp3nybaVm9JMwwxwxZ5opFSdfNpjZRnnupxjuCFyh0I/rZ38MruKbw0gPuL7JmpTozQBhhdMjeNHLa0AX0XbHWX3MyT+cuQqoX0PUZ1j+qgLxzbxi6niU6j559//3b/9p+t/0o6XiJhJSf4eYRecbwAapD6FwBqq7k3LUzKkUEwpGZ6dqjam0Vs+sbJOJu3Cbg+Ht37j5/1Y1CGvnrbxWSXnV/Sax/VYoO10/SpVY5OKzs9iSl85EfiKC+Vemlh+/ufp7Bh0sQ
*/