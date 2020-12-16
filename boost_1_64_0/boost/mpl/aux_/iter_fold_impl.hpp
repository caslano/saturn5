
#ifndef BOOST_MPL_AUX_ITER_FOLD_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_ITER_FOLD_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/next_prior.hpp>
#   include <boost/mpl/apply.hpp>
#   include <boost/mpl/aux_/config/ctps.hpp>
#   if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#       include <boost/mpl/if.hpp>
#       include <boost/type_traits/is_same.hpp>
#   endif
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER iter_fold_impl.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   define AUX778076_FOLD_IMPL_OP(iter) iter
#   define AUX778076_FOLD_IMPL_NAME_PREFIX iter_fold
#   include <boost/mpl/aux_/fold_impl_body.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_AUX_ITER_FOLD_IMPL_HPP_INCLUDED

/* iter_fold_impl.hpp
Bzf/VcAZavbW0a9yrI6awBUB9zbQueNoquhbz21IHGGA46rb9greurcGPxmnSyA8lRDvAEw8C93PglUWeC+Ct0A7G0+HHu1vB3t0RxHlS8amESjcs8HKxPaHA9DAYDjh0VB9zYkx0Nf5zHLIp5oXgbaJq7xZgDsj11s2g0pMZorgioC7VXDZ0PGe85zkzo+dg7dvAOctr48Rud+33miACwjszcPpSt6+pXi/bx5g1Q/tS5Ew/UXfW20dPG28bSYNqM0x0R3sfvv/6AdoG+DJoymK4+r/93nz6Az0Hto5oEEYMJg/BGj8Mpg7pF8ZcOL0fcCLkwAbiOVjQO0N2kpYUhxWSmh3IADsKYXLy6hHYMCHvVKg7SwMaK72jhh1YH0Yk2eyESrRgdW5fRVaNp5+5suHQ8uL44hc8lzAwWH+fJAJFaXia2RVf70/MuBdwLNnEwr8wYgimg/2rGICHrbuYiJno3MUDhuXTN16ZOWD9twAVFA+A5QTC/XzCUpQ/3Xu239hvIJy88ox9WHf8WrJQ0zeq7jkmAm4ocq9MmurwtroE3AR/46Hf11mTCg4jEUcGB2b2PCECE5ih7JQNKr/YRoAK0iTA2BQQrUtsHnpSBbybpmqyUJ1MA3ECKgLs9eYJLq2JssgVTMmVUdsYG2NHYAkzyNAurY7vsOsg/ohYhYSmzvoQTGCYD/Bx9PVxQww6Dqaq7vHFHcsHN0TW/cGFRu6Tc8SPTJTR3lxHr84dN+RHY9qF3AtlYv18sBqUAzShSAp9KHJiQNoPj1zZd4k8LBidNQIlDlUMK8yMk2ApfP4waA9RdBH0JwvoOkcEGekcZi4zZ99J4XWDfwGgPYHV+2MpvsirzjYuhw+zwXMwOa5aHwwcv3JHAQNE5YY+sdhQJeHKwxdgEHHlz+WBzORe13RwsbWB5aErZDWYdazOEZHlPd6m52Dt7eHtxlsFyKabbCC5K8ZMrNnQxBYUEOfI4b0q7mI3y8OFg8Y6MsppkijibL19D3oah6OEDsE4cJBf8BhC4dJnr7TrDA/0h+RXmRGx9bH6Vh+sfqD9TR0XdjbDxy0D6PceLgYZCc+CTKBaiOg/Rn73kZswLJiMVBZcRk5Ql+T/xwbq+QF0K7jtEECaE9wmrIA2nucNlhQN6zFaIoCaPI4bYgAmgFOUxFAc8ZpagJoITiNKoCWitOEBNCW4LRf8K0EP20jShPcxXOBRkXKbkns853ACZzmqU3oQ7uO04R0+tIeoun1/RagG0yLYBrqbxdMQ43IC4xG6UOAugEaN974BWeOhaapUgNh+ejcQ6sbH78bH79bf2mDmYHTSILmyThNTFB94TSyANpWnCYh6P30xcDeN/6dBtWF5d9g4qZxNpa4cNwbW2C4df374Dmbb4K/CeBJi28TjIMXsNHGocEmWh9+/ONBfv1i1G/jPo0Dc15/+OVAwPeJfDzdbKb5wvCP+2EHAbZMpnEliIbjWq/HZMZBYH5HPj+6KYNrWXO0tPnyhGaUB++LogTFgfPx62mjfr59AEE63iiud4PnD56ZSWzuZbbE0DAGLFly62ZhOrg2bk4ekCP+frm3Dp0Tc/qyYh1vfznN579eh70XE7mmXZWAg/GAM192ruN93xOp678PcrQ9WPx59eGlA8zkesHgH0MynYehadDr+44vR4BGBFcbpfUaWxcndOfaDgUG+P6WCmtEYfG9EheQlyeQHuJnN0B6fWkoLl0ArR0Pt6QfGlrOfuIkg7tRMA0t+w7BcaLh8gXT0HAnGv5s/ISmP8YIXD8cAGecMerHgOkoHlycAQzgcBrGNPB6AI123u+hYVcPc5NQF3yaAPGXbbjLMBo09fluL6FsfWk=
*/