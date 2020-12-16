/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_DEQUE_ITERATOR_26112006_2154)
#define BOOST_FUSION_DEQUE_ITERATOR_26112006_2154

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/iterator_facade.hpp>
#include <boost/fusion/container/deque/detail/keyed_element.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>

namespace boost { namespace fusion {

    struct bidirectional_traversal_tag;

    template <typename Seq, int Pos>
    struct deque_iterator
        : iterator_facade<deque_iterator<Seq, Pos>, bidirectional_traversal_tag>
    {
        typedef Seq sequence;
        typedef mpl::int_<Pos> index;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        deque_iterator(Seq& seq)
            : seq_(seq)
        {}

        template<typename Iterator>
        struct value_of
            : detail::keyed_element_value_at<
            typename Iterator::sequence, typename Iterator::index>
        {};

        template<typename Iterator>
        struct deref
        {
            typedef typename detail::keyed_element_value_at<
                typename Iterator::sequence, typename Iterator::index>::type element_type;

            typedef typename add_reference<
                typename mpl::eval_if<
                is_const<typename Iterator::sequence>,
                add_const<element_type>,
                mpl::identity<element_type> >::type>::type type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& it)
            {
                return it.seq_.get(typename Iterator::index());
            }
        };

        template <typename Iterator, typename N>
        struct advance
        {
            typedef typename Iterator::index index;
            typedef typename Iterator::sequence sequence;
            typedef deque_iterator<sequence, index::value + N::value> type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& i)
            {
                return type(i.seq_);
            }
        };

        template<typename Iterator>
        struct next
            : advance<Iterator, mpl::int_<1> >
        {};

        template<typename Iterator>
        struct prior
            : advance<Iterator, mpl::int_<-1> >
        {};

        template <typename I1, typename I2>
        struct distance : mpl::minus<typename I2::index, typename I1::index>
        {
            typedef typename
                mpl::minus<
                    typename I2::index, typename I1::index
                >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(I1 const&, I2 const&)
            {
                return type();
            }
        };

        template<typename I1, typename I2>
        struct equal_to
            : mpl::equal_to<typename I1::index, typename I2::index>
        {};

        Seq& seq_;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(deque_iterator& operator= (deque_iterator const&))
    };

}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename Seq, int Pos>
    struct iterator_traits< ::boost::fusion::deque_iterator<Seq, Pos> >
    { };
}
#endif

#endif

/* deque_iterator.hpp
bD422tVYdtdjl69QxyKvWL77zZu7vPLbz098+6lv6eNbXI9ZlzFy0n+S7Ql9HMbITVHGEmICzsWpWLtdVT3bRcl2Q2W7aH076Z+INpPtvpe5bX/AQvwJa7erke0KTbZ7VrZ7Dhfjn/S5aqVfHI6U7Yxz1f5G8nkNhuIaHILX4lC8zri/Eo/VJP33Jf0PsAD/IunXEKTPF33BtO06ylw/vNQxmAMwQ9LLwgmYjXm4CK/FHLwTc/F+XIwPYx4+gfn4DBbgUSzEGrTgP3EptiR9K/ZHG0ZgMY7AZZiEy7EAS3AFrsBbcCVWYim+jKvwNVwt5ZPjJX2wcLeUTytMkf0cJGPKw3EgDsGhGIGzMBLTMAqX41C8A4fhDhyBO3EkfonrCFpfK9KScvX1In+S3hkZC/419sFvMAG/xdn4HS7FH3Eb/hPvxp/wcRkD/wo0wTfQG79HH+xCei2xB7ZCrZ5J3yhMMqln42X/4zAMJ2A0TsRpOEniSSOUSTzPSDwtMUnimS71dYbsX5Ls3yyMw9myn3PQgsm4HOfjAVyAejqzXKczUtKJkXRGSzpjJJ1YSWespDNO0pko6cRLOoFN9L5H9EnS0lHia137vDcZ0+uN/bAZRmBzjMEWOAFbYiK2wkK8WNJrjXdgG6zAdrgH/fFlvAQPY3v8Bi/FH7AjkoZXEPbETjgAg3E6dsbZ2A3TsTuWYQ9ch6G4F3vig9gXf8IBeCn7OBDDcBCOx3Cch4MxFYfox0H6AeFRk+PwZzmvHMJ++CoOwddwKlbjbHwdV+JhXIVvYjW+jVo60s8Gj5uk84mkc1LS+UzS+VzSOSXp/E3S+QKvxi/xLfxan7tC+qvgMknHOIfBJNbzx3gMwskYjJfhYJyCCZiA8/ByXIpT9fO59FPBoSafs2flc/YchuLzOAhfwMH4EtaezysknrYm5/M/sl4zfAp98WnD57NKtqswKcdNyhh3vBE7YzmOxZukHt+Cc3EzXoVb8Gr8rdTjrajtp/QPwRiT/Twk+/kK9sNqjMLDOAyPoMRDfw/X5fWWxHNMyusdKa/jUl7v6+VFuMJFecmcGs1wPfriBtSPl2w3yCT9YJnTojN2wC7YA0Nkv7oZ0i+XeMJN0vdnvQC8BPtje8N21bKdr8l2++U4Py75eMKw3WmX26Fs11O266WXt/RXwNEm+3tKyvtvsn+nMRK/xOF4xhBPWj3xfCjx/EXi+Vji+UTi+dSwH5USTxuT/XhE9mMftsZHDelXyXadTNK/W7bbKft/DwbivRiE9xniOV1PPFsknlslnt9KPFslntsM8YSkuY5nrcSzTuK5XuJZL/FsQL0+1hPPXonnAYnnQYnn9xJPpSGesnri2SbxbJd47pR4dkg8FYZ4KuuJZ5PEc6PEUy7x3CTx3GyYs6JG4ukn8RjnrLCwXitcKvWmCEPQiqFYjH1xmSG+kHTX8S2Q+K6Q+FIlvjSJL0PiyzTEl1ZPfJdJfFMkvgSJ73KJb5rEl2iIr6Ke+FZJfKslvjKJ72qJ7xqJb42x/OqJb5HElyPx5Up8iyW+PIkv31h+Ga7jS5L4Zkl8syW+ORLfXIlvnuFznCbxdTT5HF/qpdWPAGyPHfBL3EUok+26y+9kJb1tsl2QfB93woHYGYdiF5yHXTEdu2Mh9sArMRR3YE98DHvhE9gXn8V++DqG4fs4EP+Jg7A9+QjHQByCnTFC8pvTRNpUpa2V/Krll9JExn3IXE/3YxDuwV74IE7G3+MsrMQF+BBm4D604qO4BvfjXnwCv8Cn8Ht8Gi8irSpsgc9iSzyIgfg8xuALGIcv4mR8GWfhn3EBHsIMfBUX42G8Gd/Au/AInsBjeArfxi/wXfw=
*/