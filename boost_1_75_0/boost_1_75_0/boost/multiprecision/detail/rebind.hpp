///////////////////////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock.
//  Copyright Christopher Kormanyos 2013. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_MP_DETAIL_REBIND_HPP
#define BOOST_MP_DETAIL_REBIND_HPP

namespace boost { namespace multiprecision { namespace backends { namespace detail {
template <class value_type, class my_allocator>
struct rebind
{
#ifndef BOOST_NO_CXX11_ALLOCATOR
   typedef typename std::allocator_traits<my_allocator>::template rebind_alloc<value_type> type;
#else
   typedef typename my_allocator::template rebind<value_type>::other type;
#endif
};
}}}} // namespace boost::multiprecision::backends::detail

#endif // BOOST_MP_DETAIL_REBIND_HPP

/* rebind.hpp
uo4TQThc94eoz2ijE9PE29miVU5PlNzMFi08M5mrBtxpNexUbBw5NsnK2bMxPQvVXywmGNHwhJeGvkB9iE6FQeMSq/712CHdMIrAt6V7jgnLnaZJ/yH6ZvWen2A9JE6Mjc/nb7MaxgLaaRXXg4/W2+523mZsnS6YQta5m2qApt1L8sg6l1Vjl0yts+/gzw2Z4ex1PzdXW45sxUrVJAszjW5YkW+2S1zhUe+vzRQhiE3JpC6iVjqkhGkNnm4pns4xgL8nX5hldD4/mCfE8KqQqNV511jV5RmruryQABaJeYSMCFvbkQTD/b8tLIBRxtVf212SyWJx4DCSlqnD+DSJTy/nn4v5pzv/dOKfaP5pwT9W/jmdTT9/8s+v2dzbT+L3G778uTjdlW3kbDFs/PB1jqv6GTb+XLLKzBlnsspEL2WrDPqKxH7FkreDgyTvFbTr7L7qV7bKyOqbj7NVRoZ5eZxYQctq9mS2yoSKzo6YEF50lu02uEdNbuRJ+9KDA4H6o3AbS737ZZup1nGa0D+x3KzX7jBqHZsN/2UaakxLeXbFpoGF8UI2yNWupH2U/2W8MA4R8Zgqw6KZ4GMWBYt1TRK51Chl+jZddfy5RMAmXWFD8KCWDgGKFzEmTNlkvF/JqeUbI25DA20kspey26PnCS/0f6Tx/cTbURUqzjcK2PYZb0DSfovVvKsYXrU2F+lv8GabUTHRRHy71Re9
*/