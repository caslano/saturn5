// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/detail/comparison_adaptor.hpp
/// \brief Comparison adaptor.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_COMPARISON_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_COMPARISON_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/call_traits.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {
namespace detail {

/// \brief Comparison adaptor
/**

A simple comparison adaptor.
                                                                                    **/

template < class Compare, class NewType, class Converter >
struct comparison_adaptor
{
    typedef NewType first_argument_type;
    typedef NewType second_argument_type;
    typedef bool result_type;

    comparison_adaptor( const Compare & comp, const Converter & conv)
        : compare(comp), converter(conv) {}

    bool operator()( BOOST_DEDUCED_TYPENAME call_traits<NewType>::param_type x,
                     BOOST_DEDUCED_TYPENAME call_traits<NewType>::param_type y) const
    {
        return compare( converter(x), converter(y) );
    }

    private:
    Compare     compare;
    Converter   converter;
};

template < class Compare, class NewType, class Converter >
struct compatible_comparison_adaptor
{
    typedef NewType first_argument_type;
    typedef NewType second_argument_type;
    typedef bool result_type;

    compatible_comparison_adaptor( const Compare & comp, const Converter & conv)
        : compare(comp), converter(conv) {}

    template< class CompatibleTypeLeft, class CompatibleTypeRight >
    bool operator()( const CompatibleTypeLeft  & x,
                     const CompatibleTypeRight & y) const
    {
        return compare( converter(x), converter(y) );
    }

    private:
    Compare     compare;
    Converter   converter;
};


/// \brief Unary Check adaptor
/**

A simple unary check adaptor.
                                                                                    **/

template < class Compare, class NewType, class Converter >
struct unary_check_adaptor
{
    typedef BOOST_DEDUCED_TYPENAME call_traits<NewType>::param_type argument_type;
    typedef bool result_type;

    unary_check_adaptor( const Compare & comp, const Converter & conv ) :
        compare(comp), converter(conv) {}

    bool operator()( BOOST_DEDUCED_TYPENAME call_traits<NewType>::param_type x) const
    {
        return compare( converter(x) );
    }

    private:
    Compare   compare;
    Converter converter;
};

} // namespace detail
} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_COMPARISON_ADAPTOR_HPP



/* comparison_adaptor.hpp
XEDdeCx0Mm6F7k/SvsL/ovNW/PczHvw+O/99cwd/Z83B7n9MWxZSn9l90/LfN+vyyeqxc55KG3zLrkT7Ig/fPs2DPT/lcJ2HEv5uX2tx8ENEZdx3+520j/AoeCLMh1WwC1wFC+B1sBt8DfaE78GVSZp/1jpUyN2QvTrUHX3nPQD20zkdg+XOEJ2HMBzeqXMV7oej4CPwTJ2LMBY+q/MTXtf5CQH8GAaTYNfQ9/lwvM4nOQceDyfrHJLzYYnOQ6jQOQjz4XR4EZwB18CZcB0sg7fBcngvnAUf0nkJz8LZ8DdwHnSCxBN2h0vgMXApHA6PJlxFsDOcDLvAUlgAK+FyzC2AX4ar4EXwK3AV3AAvhrfBS+B3pX4PXA1fhFfBf8A1sC9pfQ0shyF5jeSr4Fp4GfwqvA3eAB+G6+CjcD38ObwFPg2/Dd+Ct8LP4F2wM/XiHjgUboaj4X1wIvwRLIVbYTn8MayQehV8EK6Hj8B74aPw1/BxuEfuvA9/AZunULZhF/g0HAKfhePh83AxfBF+Fe6Ed8Nd8CH4Knwdvgbfgq/DP8G34V/gH2EL6uY7sDf8ABbBj2Ad/AReCf8Kvw0d8mkHDMJXYTL8ROoZlPNU2BkGYHeYAQthM1gEj4TTYBacBbPhfJgDl8CW8DLYCn4NtoZ3wXbwPpgHfwjbw4dhB/g47AifhZ3g2zBX5w5UJmucqbk16qGdq1msQwf7YW6AzsW4Dp4Mb9C5GC/qXIzfwaFwLyyEH8Lh8FOdaxSqbyNhJjwdtoSjYB48A3aHY2F/eBacCM+Gk2ERLIUT4FI4CV4Gz4PfgVPgFlgMH4HT4EtwOnwHlsGUIPUQNoeVsDWcDfPhHNgXzoUj4Tx4HqyC1bAaLoG18Ha4CG6Ci+F2eESQcgObw5ah9xI8GmbDQbAlPAUuw/woeAGcAlfAa+FJcBO8BP4KXg6fhVfAt+DVMJu8uA72hl+D/eD18Cy4Dp4LvwGXwJvhd+Et8Hvw23Az3Ah/Am+D/2TvTOCjKu44/jYccpMEEgKByBEBIcUQAgZFCJcEgxgOMSI1AZKYSIAQEgmCbbQeqChU0OJNrSJVhKBY8caKgi0qUmytRUVFpS22eGOrbb87+9u3bzdvc3hga/d98s93Z+b/5s3Mm3nHvJn/PA7XwX1wWBT1HW7EfQRugs2b0V5hT/gAHAofgfnwcXghfApeCp+GK+ReC3fAGrgTPgCfgw/K/1n4PPwMvgQ70i5+B/vBl+FY+DTMh6/CRXAfXAVfh/fCt+A2eAC+B9+Fx1CfD8Lj4CGYBv8Gp8O/w3PhB7AA/gP+GH4JV8Kz4TrYNIryhx3hyzAOWi1oT7AFTILDYHd4NuwJq2AyXAN7wwdhX7gHpsCmLelbgHEwFY6BaTAHDoIFcDAsgSfCS+BJcCU8Bf4cDofr4Ah4PxwJt8FR8Bk4Gr4Ex8JX4anwPTgO/gtmw9ataF+wHTwdxsOJ8Hg4CA6AWTAd/svDfRz+G1bAHPyvhJPgzXAyrIFT4INwKnwcngmfgdPgHngWfBXmwtfg2bA0yrZLEn68fWScfWSc/dcYZ7+6EDsayIHCyFj7yBbZIltki2yR7bvYjtL4f7qHv/74/yT6WM/22temE6uJZcyrV7BIXuW82WYNERM+nfDdGc7wcpI1f95CrQ34RaJlj7Uu8KjzW/YDhluExfEe4Js/MHby5LzS+TML8hQTaVlo20n/NTE8baR+WwH+fuDunsb307r3H4bvJxxq+j/fv2HAoc2XrT1jYE239MErNp0Qvn/SvV8xfD+we/9t4/tpw/THap60zoHOTX7IPOnRmid9KuymfsX+MAsOhdlwOJwg+6hdS1taw5DgdxY=
*/