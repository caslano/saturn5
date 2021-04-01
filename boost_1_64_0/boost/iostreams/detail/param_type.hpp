// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_PARAM_TYPE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_PARAM_TYPE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/iostreams/traits.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace iostreams { namespace detail {

template<typename T>
struct param_type {
    typedef typename mpl::if_<is_std_io<T>, T&, const T&>::type type;
};

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_PARAM_TYPE_HPP_INCLUDED //-----------//

/* param_type.hpp
tJJjhOpFQqI1A7ERwJYcvggHgpvsDRw2clqEqsrCHSNrcHbQWK9O60TXeKZA6d9r33uosRgRUNhGjosAGXAzmlzuj1PfLl2Uy3Gybm6zMSmtRftTjqcRzUPnKyaongJbQM8XVShSLeKIIZW6NjradNXvdVeBlxN2SKzZTwR2SoJqI0xUnTqtrXr+TOGX77P+suDI+agdUNtuwUl8kHy0Ai0ClR6sXpkGWR3xmdphintf2AeNiK7pqf4gtG3pfoGiO+sLTjRNy9DVP2iH0zB5Z9stnx+A4L21guK+2lyN1a4eH98cv0T1ili+FjPmEexavKflY5vaE84AeXnK3zoD6REsemx9hSIFIEsUTwvOz/V3N6DAU0nmFTzVYymIvIijhPsN7ym5M5PJ/U4sQ+Cq/zgn9F//h2+Qhclrgww/SL6LZhvkgRchqMC0oOo5sZgO5ya1zsgKgBlvfGbMBtSoW07oTuyOqckI51Lb+mH10ueLTIH0iKOde4zPzyE+TS0gJF78A9cpy/wTvrozzEonLc/4+I4RRwaBmVJ3tRiezavJwbyAG5w9kzx/GA==
*/