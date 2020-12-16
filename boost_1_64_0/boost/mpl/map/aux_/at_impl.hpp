
#ifndef BOOST_MPL_MAP_AUX_AT_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_AT_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/at_fwd.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/map/aux_/tag.hpp>
#include <boost/mpl/aux_/order_impl.hpp>
#include <boost/mpl/aux_/overload_names.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>
#include <boost/mpl/aux_/ptr_to_ref.hpp>
#include <boost/mpl/aux_/static_cast.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

#if !defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
#   include <boost/mpl/eval_if.hpp>
#   include <boost/mpl/pair.hpp>
#   include <boost/mpl/void.hpp>
#   include <boost/mpl/aux_/config/static_constant.hpp>
#endif

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template< typename Map, typename Key >
struct m_at
{
    typedef aux::type_wrapper<Key> key_;
    typedef __typeof__( BOOST_MPL_AUX_OVERLOAD_CALL_VALUE_BY_KEY(
          Map
        , BOOST_MPL_AUX_STATIC_CAST(key_*, 0)
        ) ) type;
};

template<>
struct at_impl< aux::map_tag >
{
    template< typename Map, typename Key > struct apply
        : aux::wrapped_type< typename m_at<
              Map
            , Key
            >::type >
    {
    };
};

// agurt 31/jan/04: two-step implementation for the sake of GCC 3.x
template< typename Map, long order > 
struct item_by_order_impl
{
    typedef __typeof__( BOOST_MPL_AUX_OVERLOAD_CALL_ITEM_BY_ORDER(
          Map 
        , BOOST_MPL_AUX_STATIC_CAST(long_<order>*, 0)
        ) ) type;
};

template< typename Map, long order >
struct item_by_order
    : aux::wrapped_type<
          typename item_by_order_impl<Map,order>::type
        >
{
};

#else // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#   if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< typename Map, long n > struct m_at
{
    typedef void_ type;
};

#   else

template< long n > struct m_at_impl
{
    template< typename Map > struct result_
    {
        typedef void_ type;
    };
};

template< typename Map, long n > struct m_at
{
    typedef typename m_at_impl<n>::result_<Map>::type type;
};

#   endif


template<>
struct at_impl< aux::map_tag >
{
    template< typename Map, typename Key > struct apply
    {
        typedef typename m_at< Map, (x_order_impl<Map,Key>::value - 2) >::type item_;       
        typedef typename eval_if<
              is_void_<item_>
            , void_
            , second<item_>
            >::type type;
    };
};

template< typename Map, long order > struct is_item_masked
{
    BOOST_STATIC_CONSTANT(bool, value = 
          sizeof( BOOST_MPL_AUX_OVERLOAD_CALL_IS_MASKED(
              Map
            , BOOST_MPL_AUX_STATIC_CAST(long_<order>*, 0)
            ) ) == sizeof(aux::yes_tag)
        );
};

template< typename Map, long order > struct item_by_order
{    
    typedef typename eval_if_c< 
          is_item_masked<Map,order>::value
        , void_
        , m_at<Map,(order - 2)>
        >::type type;
};

#endif

}}

#endif // BOOST_MPL_SET_AUX_AT_IMPL_HPP_INCLUDED

/* at_impl.hpp
VpUNtHdQNvCa8k7HIutzVvgNlA341LF/jt3moGxgP3F5LlbHJc+xcQlp8rDudJxN6ts/q/ton9UlTl91nDdYNkB89uUfFR3vY6Cj+FImmqIsQ7o6itPN1XGcoY7iTE2Kvxn7makTZ7ijONMz0v5MnOa8ek7i7CdlEr0IrxNnjDrOMpRJmMsfyKt25Q/JbvblD/mdCNq40m8srxKnTflDE4Ikke27L7Id1WQ73GU7Cu22o+z5V3cbtMe6kuO0KLbbhhvL085uB3863A7PJdrtuLF87ux2zNPZjkC77bixvK+7HZrzIUL6wI+V/DGa8KZyDqq2Qyl+5FclKSXDufNBiX8iW8k7OJb4+/KfSWOT411kmzwxg5CUEp/Aeo3LeanG6lfm8ZZz2PSrwzQ515SF01NiJyZY8vkdpn5kpC/4RW7si3iQfSkw7Qu/jep9iWatpv0JKHV/PEz92T3GOozbUKnGrGXGv/36D2zdykWmFeWYpwW1NU+rZ5nWqoN52jdLLdPamae9aJ0W7GKfhpb3moo5piRhmdJPmXGspJUyzQcl/SzTfGVdKamJ8WkyzU+d9qrrnDFO+V7M94Wkb+zkTOMy5/iubGPGRAObaVrPcaa9yjyG2LRx5vWcZ9o7TEsYa5qnhO8/s5zxAEmZ7mWm+dZmXURY28W1RiT5NL6KaVz1xOVyLJivSOZLT5jErMb8wPIdakzNMc1ziHiU7zVlGeIxfr/tMfN3dR6SE5FPH1fykPge68haYclDZB9ulzKSpiTISaHkIT8n8tC21axD9X3Ramue+nmVJf+0N+eLY9Zplrzy6ir7fPakdVob87T51mnB5mmTrNNam6d1t05r5Uzek34ebPKZlzov3kDes8lnckyPKHlmrDXfKe/4cRm05A2iUX5vjesolmuCQdZrzlNK2k9mNCzztEJZLiUhIT55rClfrSNP7eMHsYdyrFda89Vp5jW+VyvLk0cs859n/uZMk7Qz5X1Z95jU1OQpscmWfFiywjTP0U62+WyF5LNRct0dTlCuErlrLPlMLlPKGhNiU+S3sPINXHvV21VdfQ0lPdXblF1N2nGywa7YGAvYbt/Htds0VjmEZerbVbtN2vzi6SC/eGnzi/Y3Qfor/JBtTBynpG+6ITYuId08fWptzlvj9BTLf6j310/6wh8nxyCOsIsC1pwntPtLSBiXkHYDx8B8/vyok3/Nx8PAb5V2+/bI9s2Ue4QZhDAKgj3XarcvdQzr5vmt7MdDs30OflvkfkG2KV762M+WdxGmEPaSZvn225QUL+kV6Xh7ZrM9PFN1NO5/bWLR27bexMzajN+3SN5NTjHlh218/4jjzAPvmMlj5R5LtrVyDWnPW9F0fBvgMeW6ss6yrZaqTu09ge8NpKEzv8/ym6Z7f1NkPjc117IM1f2b9rf4TslTlvNHdU3qywZnyH2Xcv1K5PgdZ76HObe/NaaDXBtl3vQJyh0S0+R3en19JV/Exk2Q+Yolr2ZIPObr3GpZ1z72T/n+2Xrb71M2mL/b5vHMGvb9+D5JnL6mOuL0CfJafLf+Q+lsefLE0q85vjbHZ2N9ZX9s47ss8dWS+IxDmzBfqKP4uGBOTih7fNXV17j4THNdMBH+/9UFO64z/d+tI15bw7g94et7Fj2XHJwTUHD0wm+Lm/376ohnG+uIgx57r8XKUU9Wrdzoqbnjpw75+N9fR0zZoKWO2FBKHWptDLLUcUo5H7o7WK6vLNcPq+B9quV8ZbmqspxeHXFlmzpigjq+MtRJh5ay3BBZLkKWG6paLryU5UbLcg/IctGyXDghRpbrJ8vdjmGq93eqSZ17Y/SXuuW7pW65OfbAAOylqevOl/VWd7A=
*/