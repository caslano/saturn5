
#ifndef BOOST_MPL_SET_AUX_ITEM_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_ITEM_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2007
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

#include <boost/mpl/long.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/prior.hpp>
#include <boost/mpl/set/aux_/set0.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>
#include <boost/mpl/aux_/config/arrays.hpp>

namespace boost { namespace mpl {

template< typename T, typename Base >
struct s_item
    : Base
{
    typedef s_item<T,Base> item_;
    typedef void_       last_masked_;
    typedef T           item_type_;
    typedef typename Base::item_ base;
    typedef s_item type;
    
    typedef typename next< typename Base::size >::type  size;
    typedef typename next< typename Base::order >::type order;

#if defined(BOOST_MPL_CFG_NO_DEPENDENT_ARRAY_TYPES)
    typedef typename aux::weighted_tag<BOOST_MPL_AUX_MSVC_VALUE_WKND(order)::value>::type order_tag_;
#else
    typedef char (&order_tag_)[BOOST_MPL_AUX_MSVC_VALUE_WKND(order)::value];
#endif

    BOOST_MPL_AUX_SET_OVERLOAD( order_tag_, ORDER_BY_KEY, s_item, aux::type_wrapper<T>* );
    BOOST_MPL_AUX_SET_OVERLOAD( aux::no_tag, IS_MASKED, s_item, aux::type_wrapper<T>* );
};


template< typename T, typename Base >
struct s_mask
    : Base
{
    typedef s_mask<T,Base> item_;
    typedef T       last_masked_;
    typedef void_   item_type_;
    typedef typename Base::item_ base;
    typedef typename prior< typename Base::size >::type  size;
    typedef s_mask type;

    BOOST_MPL_AUX_SET_OVERLOAD( aux::yes_tag, IS_MASKED, s_mask, aux::type_wrapper<T>* );
};


template< typename T, typename Base >
struct s_unmask
    : Base
{
    typedef s_unmask<T,Base> item_;
    typedef void_   last_masked_;
    typedef T       item_type_;
    typedef typename Base::item_ base;
    typedef typename next< typename Base::size >::type  size;

    BOOST_MPL_AUX_SET_OVERLOAD( aux::no_tag, IS_MASKED, s_unmask, aux::type_wrapper<T>* );
};

}}

#endif // BOOST_MPL_SET_AUX_ITEM_HPP_INCLUDED

/* item.hpp
SRw3GAu1k+9/GPNNKkKsuLG4dnmIlTYWlHmpCsYc8p5NFWP+i1yuhjHPYpn/Q3tyfeA2FljF87Z3wheZt7gHbDb3jQdgtzKPnS2MudrzefAx+CxrK1rDbkd5/xfsC67b3lim7CXaCXFMl+9/oJysUephzP0Gl0s2Fs5g1gdayVxGP/gscw+DjXnlnRA/NJB3WkcZi8r+UmONOduy3YnwrzazycYiPViXqfBF5iPehgYJPMa+ayzUifvBXPhcS97/hc/yrG0ZfGkp6/+Qy0vc3nrYOM/9byPiXSrv/0LTBzi2behD57i9MMr1kP3/jPnkWuUw9FvN499xaCD3MyfQnsxdnwaT/SjOom47LvcjdKnC/fkSfKki3/+ALhfYbt4KpsEdPOYUqmA2ZA65iLGArDe7BXXlfrUU6i6R93+NRb5l5jLmWMysOup2lfd/jXl+kPV/xnyyZraxMXcjrtvUWFhiu99Y3I18v/8QYpPxqiX8K8p2n4ANsdsGGrTjY6udsZDktyPqluF8xMM/yXl31JV38HsZc8m45oPdkOz/h3LS/wZVcBhkn4cb8xflY+FFY3fId2DGwGdZCzEBPsta7EnQVNZbvAFfZD3rW/BZrp9nGovIWs45yIfcIy405hgm83+wW4mPj5VgZ5itQ7zyLlkILFXm/2DXy/59Bp87Grl2/g91ZZ3qXsRxhrU/hP48lY+Zz435msn8n7HMe9nGKbDdnI/v0Z48WzxvzPkj2/3ZmKcHx3EZ/sVxvHkq4jqbj9+CYD9ze4WNeeT4cBrzS7lbjUXlWqUc6r7GPlc2FpH3FqsZ89WS/f+MZco9ez1jTtGgEezOYl/uNuaV94TvM+Y6wn3oQbSXwT4/Cp/zyvo/Y4598v0PaCVzLc8ai2vC7T0P9grHG4d4ZS+9RGPBelzuBWglaxxSwWQeJAM+T+P8DjQWkrncYbAxTvb/Q7kB7MtL8PlZHtfGg9Vg9ipyJOfG142F72EbbxpzLOP+PMOYX75HNftKn5Tvf4B5uG4QeXuB666ApvJe9Fr4V5XZh9DvG667Ge1t52PhU2MuWTP2d+j3APuyB/HKmtmDxrx3Grl2/g/6yXuVXyI2uUb6BrmUY+EMfG4i7/+ivWfYxk/GAif4vPUb8ivtOSqZ9pKjAsbitsn8nzFPL9bqZmNByVtJYy5hZY1FZT6xkjFHDbZ7mzG3PLOpZSwgfa0ufL5J5v9g9yXW4C5jmfI+STO0V5/z1txYpKB8/xdMxs6/GHPm5XOK15jvGZn/M+YdI/v/GXM0lO9/wBc59yTAxhb2OclYKJFtpCBHYznedNj4k8e1AbAh+8MNRTm5XxgJNoxtjEZ+2/M4NA7xvsx5ewU6p3POp6CczFFMR3syf5UJnWuxBrOMuQdye/ONRWV8XgKt5N5luTF/R87bGugnaxI2GPPI/dFHxhwtmG2FjcF8HO2Az3JPvBt287GNA8a8cr1xFOX28LHwBWxs4Jx/jbrb5fu/0Fn234iCyb3QRWgv9z2/GgtPkvV/YK/I+r/K1q9kzcmNxsLy3apixryyJ1YJY4Hdsv4P7cVxPioai8g3Vaoac+bje+eaxtyyxrAOysm3yhrAl1my/s+YYxhfm91rLDSYtfIYi8r+OQ/DvwPy/i80EF2eBOvEvrQ15pH5yefQnujXGf5JHN1QV8bOnvBvg6z/AxO7abAhrD+0n8I5HwL95NuAI6BLZZn/Q7nVzF5GfmWPhQDq1uMx5zVjDrnXnQatHuC67yC/sl/peyjXiMfnecb8YnexMZe8q/C+Md+fMv9nLNhR9v9DHMncJzehvWLcN7bArpwXtkPno2x3F+IYL9//MObYIPv/oZxoH4E=
*/