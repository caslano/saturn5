/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_07172005_0831)
#define FUSION_DEREF_IMPL_07172005_0831

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>

namespace boost { namespace fusion
{
    struct cons_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        template <>
        struct deref_impl<cons_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::cons_type cons_type;
                typedef typename cons_type::car_type value_type;

                typedef typename mpl::eval_if<
                    is_const<cons_type>
                  , add_reference<typename add_const<value_type>::type>
                  , add_reference<value_type> >::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return i.cons.car;
                }
            };
        };
    }
}}

#endif



/* deref_impl.hpp
sg1f1qnjb1zrKp/DiF3Wf2p+F+Pnvk40a6ZTh0ItzYvVzzGa/mHqPHuYc32PrPtv0466hT8eyzwCdVveWq0fCjM7cWhgcPyszCxWIdiTJ6dOSZ2cmJOamdGws907GnRKzcickWN6/ncg/z+lnu2da7TRLuvoE1FqEDwbfoeelZ1UPR33XhilOX1caq7cg0sPoVu+6GY8Pz4s3lmGxS4/9XOJ270TqukaJ2scnNfbw5xx9NfVqeRXPk8zrANJk/X00fKMjYXfk7/CLrr8XXD+uNR6rV3nPoG+Ot1T3HS3u54L03s233XPqp8LXPeTtm7Q1y2vwa68upeHMg3mdo9PV9fwdqJeg8n7Rvwu8ZYzg3XndEg5ademcO2t+Ed0k/W+hnP+c3PSZb2icy1JSgvPNgfM1yY0fC2J+RoEz2tVzNeGNHwNyD9l06DlFYq/z8DFOz+PW1Rx64oem3d1O5kXzA9qecvvgvxexPCPP/9PcJ0fk98broID4EMwBa6HmfARWAAfhbfBJ+AKuAluhWXwHfgi/Aa+Cn+Hr8EA0ngdDoNb4UXwTZgCK2EmfBteB9+BN8MdcAV8D66DO+FG+AGsgLtgDdwNv4NV8Ff4CWxFee6BvrAa9oefwcHwcxgBv4CXwxo4A34FX4Bfw1fgN/Ab+C0MVZ55uAD+AG+FP8I74QG4Af4En4DOudq4FvKulnc45a3O30VLeXeW8vaGp8Nu8FLYHT4Oe8DjuNYHToU94QuwF+yBXieJ3r7wTdgbDiD9k+H1sA/8EPrBETxnfeHt8BT4NewHI1ujE7wPDoC/QH94Ie+GU+HDMAB6MSQ/ECbCQfBpOBh25jkKhJlwCHwVDoV9eO6GwathEHwPDodD2tJ2gfPhCPgZDIZn8dt2OlwGz4Ar4JnwSRgCq+FI+CMcpdkPl98Y+e2hfA32w0eLvfBIOBGOgdPhWLgMRsEn4dmwGp4Dv4XnwuHEFQ3PgOPg2fA8SbfKJu9+GC3PkTKnu13SvUDqNQ5mwkvhfHgZ3Agvhx/DCfAYwl4B28N4OAYmwEw4Cd4Hk+BmOAV+DafKWdMpcDBMhclwGsyD0+FcmA5LYQZ8GWbCT6Fdzpi+Ep4Ms2AYzIZjYQ4MbmGr1/nIelsQbUaJ/QfN3kNtWw+xYuOBeTnm4oy2HCqQEmX+TWw2LEbc7TNMQJw2GZJkTm0/op8/E/sK7rYVNHsKaYhmO8HcZoJmIyG6DrsIucVIFPExX7UAKUN2WnNXlrPcf84dVvt/Sv9fPfsvPi11UtPt//Viz/4CpY+v7tlPtNsd1uqUBDKTsm3q9wv9iXuK8n12Dpt+ErOStO/VMYSlur38+6U9Mg36wmR4G+Htn3fWxhDOjbw0Pjw2Tsz31X/fpP6Mqy6G/jAqK0eAiX+Czq6feLudgzY5PcnWsHPQXHsv2XEre0eXf6HmyXatv3Gv8nYZR/FpgcCuUDkDLbTGpAzkGLTGloOMC8iYSgZWIbXxA/05aGq/6iCJl7d07NmsUHTR5a20ozoWkiT7JtT8jf/ScU2h5M85TpQiYwkFfNkRXg9v55qSL2vnj+2JDcyXnYy5n/mWhZ/YNfjaodMit/26e0WnBUhH5CZkMWGLvq6lk7oxpj57MU3OnVN12CM63CE6hDnLRcYujkdaq9eiA9fE7K2tAxvoAuPtyclZ3Lr12Rco+zd1uhjvuSoPads9pk3CTUjXmecJrWunu4R0C83TjecNo26LbY48b/eQdol52k1O15nnGLFF0F7SPU7OEaz0kC5v9ix1KK0JaTvzHCpNwkVID+U65C7yvM8k7ZTk3KHK+6UhdlrNzhF0f2fGaO8WUhA/1zjRpNQMeQ/7qt+Jn84=
*/