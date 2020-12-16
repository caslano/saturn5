/*=============================================================================
    Copyright (c) 2006 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTS_04052005_1141)
#define BOOST_FUSION_SEGMENTS_04052005_1141

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct sequence_facade_tag;
    struct iterator_range_tag;

    // segments: returns a sequence of sequences
    namespace extension
    {
        template <typename Tag>
        struct segments_impl
        {
            template <typename Sequence>
            struct apply {};
        };

        template <>
        struct segments_impl<sequence_facade_tag>
        {
            template <typename Sequence>
            struct apply : Sequence::template segments<Sequence> {};
        }; 

        template <>
        struct segments_impl<iterator_range_tag>;
    }

    namespace result_of
    {
        template <typename Sequence>
        struct segments
        {
            typedef typename traits::tag_of<Sequence>::type tag_type;

            typedef typename
                extension::segments_impl<tag_type>::template apply<Sequence>::type
            type;
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_disable_if<
            is_const<Sequence>
          , result_of::segments<Sequence>
        >::type
    segments(Sequence& seq)
    {
        typedef typename traits::tag_of<Sequence>::type tag_type;
        return extension::segments_impl<tag_type>::template apply<Sequence>::call(seq);
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::segments<Sequence const>::type
    segments(Sequence const& seq)
    {
        typedef typename traits::tag_of<Sequence const>::type tag_type;
        return extension::segments_impl<tag_type>::template apply<Sequence const>::call(seq);
    }
}}

#endif

/* segments.hpp
L9ExOH8JH71aDD1/jL1Ux+DnUOtWi6P1n3iZjqnmU75KMPgxkL5vAum1/j6fpHRQQPIeOMxo60Dgmwl+WY3fWaOzPe38cp+cZ0DeIHa64g6K3Y7ByVrmA91EMOilgbk8Bgldemmo53mCQU8NHM+jmymdempI3JVGHLS/Gr9vSMNpHhu4V6rF4nUN1nNxuBYHyVakrH1bOAad0kiboqwf1eJom/S3ahjStpiTQsdh+2Ks0ZEqRmtj4utCsXo7Y94wDVvf1ujntF3Dk/YmezgNS9tc5hIVONLWeDd9eifSsY1x74400rbIu7gL6dimeG+ONL0t8Z5qN2K0NsRY33sIRms7fDNAnNZmWJ8XjyKGtBW+L/+IvpnbphXGnmnw4xGgO+KBGXl8lScxEgusBQMnNpRIAYIFeU5XyvG9IAl90yhuQpbaxY1E1Qdk8UfUZibzXBsufXyj3qVcsP9XlPlhWmaYJ2AdErUMdYvImTovFXb1Ks+Ul4axm7qOIRywMSe1wH+O4HPPBCtesFCFViNVMl8p/JBInVwjdaIsaoFtE57b5OGVMxuiPb5NeEOwB28lvhtHRlM6lFLAfwX/3Qp/lKdJkCepUZ8mBfnR7uHHKr9leGDaaIFhQZGdc64vHyxKvgW0e1D5ciPy07yVu4lBvfyoHaVBykoN33VyJ3KySiZQ6mpZikAZixUZXuZ5Ye64zTJgHFZkXKzIsCy3FcZR3iyjL6qC/fjqj2m7h07LshKtKux0X5wJOLsp+G9W+APLdJ04C6gAfjxDAZL/PuH3WZ+DKjhOwa8/9WCfFd9v7CfERiZ3vTwDU37GLqO7lVyzx8Q3V3ksm9ntm7HjxZKpuPqEhEKV7074oGuaLctNWmHBR91mm797RUYemXEWtpwaGc3fnciA++YU3KfA0sdoDtvCJcjvfoXICAxmvpTkdjle4OA0t4An5WISFOP9lWK8E37XcLLUChzXrPIjrzLP3CG8jhFAM4V+y1d5abGSd+B/pF13bB5LEXdLMBDA9NADBAhFkOTZIUiI7PV+t8QOhCbj2F9igxv+7GCKUOgRNRRBEB1RQg89dBD8ESSEkOhNhCbRCb2X2bvd2Z3b+yDAi+yX3Pxmdm9v+7Tv0nJdlztVFIYNL00Zo8p1VV8hvBX01TKPq1S226DUQa0+0JJRBZlXcse3ZdiDDvsAkZGz3PWqgoclyrDT8+D3O6TWDyLDY16RBGnKUQRqQxrOxyi+1xE+RyQ9CbzUzTRj0/kbNs13qcUXZZXLqyxgrTNOm++LwEfn5SL3nELOD6IosfDjUHsM9hHC57OyyIKqKFO2rdONypUE/eBUmUNXaJnwhqVf+LJvyhxnYkZrOJni232l/Y4ld6s4Jnz9Hq596nvuJ3w59EknyItA8nWqrK3vyYkMj5UJrJ9hlaEMbCtq77fY4nM9WETcPEc+nMso35lWG/lxVvhemSo+VBnKmqrvcp7wBSxJ87wsCpfhtYS+vpasRxTvRcLrM+7lsQuTn8Wr9yZHXOUHYrVxUVXQWzWvdX2PbYx9qlX3wIsdP00qLQPD2ll1H/peqz86TpbzJG/z6iGgfXx2E17OsjTJkypPCK8VBs8e84zIcVmZc99L/YK1Vc9yvcP9rcnHmeeU3E9g6FIrR2p7uk55UrfgJS8jkwdHAs5JrfoFXgVdKvZZ26S2Vb/XmXwVi6B+RV4mTEQ30nbjtH4XTZ6SZX4RhEFVshNzwAL+qjBnouUy+hyS+nks8UqvikrJtC06+5RYdEDbhj7b6If0smHSdzK3hJU7CYG3D/Gslf85MZlWvF9vlZtWgeM5Tsjm54QrSj05gIDFxqac+ttcJbw5426Z+rmfCkc=
*/