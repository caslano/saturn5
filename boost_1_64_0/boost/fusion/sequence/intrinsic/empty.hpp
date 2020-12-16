/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EMPTY_09162005_0335)
#define FUSION_EMPTY_09162005_0335

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct sequence_facade_tag;
    struct mpl_sequence_tag; // mpl sequence tag

    namespace extension
    {
        template <typename Tag>
        struct empty_impl
        {
            template <typename Sequence>
            struct apply 
                : mpl::bool_<(result_of::size<Sequence>::value == 0)>
            {};
        };

        template <>
        struct empty_impl<sequence_facade_tag>
        {
            template <typename Sequence>
            struct apply : Sequence::template empty<Sequence> {};
        };

        template <>
        struct empty_impl<mpl_sequence_tag>;
    }

    namespace result_of
    {
        template <typename Sequence>
        struct empty 
            : extension::empty_impl<typename detail::tag_of<Sequence>::type>::
                template apply<Sequence>
        {};
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::empty<Sequence>::type
    empty(Sequence const&)
    {
        typedef typename result_of::empty<Sequence>::type result;
        return result();
    }
}}

#endif

/* empty.hpp
YDNWFIx9tBl7eHZxBS4wJXZpcy22dIefPbc09/Yezh8DQ/VYjPMj7t3qccKFH8seGm7G8SkJx+mFB2G77fYqxUOMjkZ8ERaNB9BBXS404/lOSmL/1YyFrUa3v6hg17c2YnnrSp3vNWNZhGiBR9n9kWY87C3IN7lbj8Wo2rjn3FaLE6/jqGt3ez2OJYZTvweuKTtq8SSmxcfqMSK0A9Y739mM4xnUEHu/GYtj4XkyBngzttNFmc7uB+IgRe88YnfuacZW+/gnH4TFeEwSvzTaiKd9HO+4m/B6v73UhNX6LeD2NmNZE1fx1xrx9f08f3Izvru22l3pyTn1TjMWxwSOn32N2DLoh9QZckLWYsupt5gtl2F4yLuILsOTuwge57b4HWzaSh/xYuHAWCoix+9+HYON2ZNlXHoqw5VksB5A/tEx+L05jgjq0q/F0bPNHYZ5hFgj60/TcFo8OVg0EdMUR/DDApPlYPkxHYMt+Ul4ioX+2e4WL7GKbkefXosVqskcB/U4tUlQx30HdGw15t1HajH1Me/Gn9GAhaYhOgqc3sUwGCvamT/eiGUGMPL8SnDatIs455nNOKg26nitEYdVR5kz481YqDrKvN2IEz1D9vf+sxgWhlTZEfD3m/g7U0H+/upns9+LEUrGx1fo77PWtGuetP1ZO8lnvVSJP/kchluX77R8KL63vcrv3bmdruJ/WEwyx47KWNBPfhY/85cBiNltrZiJMD/Qn+l+NUyDVh4G/kb3q68Xe3dVnhOAIU9gZ1FaH1IFvrAaU+Uw+w+7VfydnO+DWCn3CtEzM6y45becwHqw4AySKKlCO+WvhsxndKdaf9OP/MCM6+XCS3qZOggKgNCvMFGDqNZJ4U9wj8py4ji2Qj98pMorokGmw/b4P30FzKeFfpDrgXlQ8802swHeNQp3SQUtPZUUuQXLMNTT3H9+jPjGMa/1cju5CmFgl7n/3K9APpsWHDN1BzjfTo1PLDDAxzF/AD4YNQtzy+3+Um92Fa7gVxfQhKbEPF2Tw/sg1+CFtCyKkSdggJby/lxfJno5MvuYvwCGAkre+3W8aH7TVG8x7pgGMC4B85QGfcubjAVAMlxzvfi5qsDtBtw4yF2DpXZqtl/wPUvj41vfYuD2UP5zGnHQuAzG9d2r4+RdFMDEN9/TWPf5swLzuI4BpbBDSX88+Pv8QcUe6Nw5eRc7iDStd6n3U/frcOgXhWdHHcMOZIVaEne7GbcISWNwj3VmqBG3trraLv0AlBimtx6Kxys/+eY0rPMo4RxQl1sPwJWq9NcBJnXf0ojHUKnqPdKtRvzaMg84hzqf2VqPPVy2H8r8UQMOe4lS/umReqycIWTdvteAJSNPtgXEd6jHkxGI3xHkN+PpTKTqv72JB/uy1L8Ji90K2kfpIzM7GvDFdbmUe+OBODxSoc7xTh1PI3DJNvlRM7bLDoJ9bEYp/8yueh6x6qjYHzVicXbCer5ldz2WzIzY3iC7GY8zJMCk/D0NeFie5XCQ3+dHDXg+Y8o+MtqIw5kV39BqsGVke8Vu4Uk6hu2kyTywV8eIQypetqhz6JN1fBHWhbcS5kRrxLElVXkz2FeH0+e3fU9pwvHmhqPr3PwT2JaXG/HyAx1B268GbNnwHRBeTFxqO9ys58Gxie371DqcNpZR77v1ePTqUXX42FgjFkayxI0/rQ6nzw+Xa3HN84PxWB2ezg+4ptZi8XIGZXafXo8TfVKVOXRAx+LFiXpPVo/DSxN8H3xGHU4fp9cbcfo4nXkcsXB0w6/ONMT9zw2KYTQs6+o40tDUhJ/r2v3S9Uja/jxLYs8zKXCD/o4BJY7as5EuqMh7WafBZ5Sy+88RdKwldFw=
*/