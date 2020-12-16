/*
 *          Copyright Andrey Semashev 2007 - 2014.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   null_deleter.hpp
 * \author Andrey Semashev
 * \date   22.04.2007
 *
 * This header contains a \c null_deleter implementation. This is an empty
 * function object that receives a pointer and does nothing with it.
 * Such empty deletion strategy may be convenient, for example, when
 * constructing <tt>shared_ptr</tt>s that point to some object that should not be
 * deleted (i.e. a variable on the stack or some global singleton, like <tt>std::cout</tt>).
 */

#ifndef BOOST_CORE_NULL_DELETER_HPP
#define BOOST_CORE_NULL_DELETER_HPP

#include <boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

//! A function object that does nothing and can be used as an empty deleter for \c shared_ptr
struct null_deleter
{
    //! Function object result type
    typedef void result_type;
    /*!
     * Does nothing
     */
    template< typename T >
    void operator() (T*) const BOOST_NOEXCEPT {}
};

} // namespace boost

#endif // BOOST_CORE_NULL_DELETER_HPP

/* null_deleter.hpp
TNTBdk8Hwz01vzGueGr2y701x5a9dY4txMf3ovdSXp+ju2Qbib9jUZ2xHSoV9SOMM58V9XHRBr0GH95HYQO9c6CDjKnDJpJZqmSPOHEODjFOHYhx917QwzVuLkHh2ciIxjgdX+eE/nSxgGdnbDsc4L0DHfD6MgIe8olGpRmXzcQ94fU9gaqcfI5n2ynPewwSw3dp+nr29di9ljmLWGLqqjOCuo6TDEPX+yNn7DhMuJOWajUDvqZLRFwru9XbS/HlC8s4VhmtzDfJ93ToD9aHU55Jyo+Sax7GUa8VWSe0P7X9uyry2L0l+kZUoLZ8dvjQsMqMWytqCvVDYfknUUGtoB/EUUHYlignPuEDZvSZXSLxoVAo27XLYl4+22Mzx+8BnOrg1cPKQc9sJi41t8nsjKPxGjbIG0ooyxHig29w6kLzOQycpxM9yUM+T0ccz9OXAx8xGXdMi0vngrl1XW7KwDwlnTecuxg65unLViMUlM7x286LenLPo0vEYyvIVz6nbR2mQjz2S9X9XlqPv2okF8bgP/r7c9QJXtB2qij2XZomsG+KPLQgqcmzZ9tDa/LQwVJNnoOb27capjQ5O3uHzzNM6XIu6jRMqXI6MgvzqGUElGe1xLNveGEZe3qHh2rJ2D+wsAyK45EwNGpD8rfXT2iW9okv53GmTDnxeOWM6T/aEOLKnxF/k1FhxHVf4utcZNP8VEpDb+PN2RLhGqMDR16z/JJoRwk9i/Cuet9tHSmPkITsWLf0ZvceYn2P0Z024s/mqKONjeYmk3dCyxN9LGHci93ymw16nd4/2Lunr1+d6cXOG5Puk0t1uqP0YAnPCZ/Ywuni90/b1DmVmft/twGx7c6Z3Su4HH7MrN8H5dAsp3np8HvWfwjTEGzLXmSd0Emac658GdPVcGz8r1CGvoIq98AMxha/3cH4EBDTYp3DtIxhWj7XIOyNbB+bG7QPensmxYxplta1f6V8tg3sgcsYTY7tkKwFbYdwYztoG0TXtgHj9zdXBOfE/IUi6vVgs3dsYL64PLGdZFWcGbQVSmhs5TSPrhob25Rouk1Zt6dspDNiQu9JeHeDup0W95EbU/vedN5VH5aX9Ee4JkMdiMY2DnUgGi1ZI49P27XLp6sKbUE0bgqu/72p/ouJd1T5shusf2lSqn+XaFtXLtG2NU5Fmiqq0wm3Dcf4KiLJE+il2SrY2h4q71RpZoK/g+zouDS5oI4JD3VMNNYx0gJ9Ek3rE/koOowqNdo78YGOPV6qSX1xUkjHObUiykk63tac9m6Npan9J3iM9ZoI7x2pPpUv0HQ2TqMcyfDvu1B6MwakpOugcqVhW7BdECvkC5xnKt7JDAviHTXSbwF7Qbw0TucRcroYS5VJYEp952hNkENsKfUptUQcpK8ScCxCsSyULLUshKWXhcA0mQVan4h0eOvsyzN2ChhdwSE5AY3uk0G7AP3w9GiOBsTNko6K+cKoKlgaxu0tYqD3AEO9I6ZCUEJ+IabsJ7OlScIgvxDj/EK9ZOLsVoZ0rpqcRmUl0NEukE66j6HbJIyWKgoL8hkbV0WjNAGdiwb1AYyKJsmS88/Rdn9znM3tMsZZyRhllZ6OsguxUbJbaj/QeYBB/wkxbv7bFsJJL+k4j28peeMYE6atVlKxidx0KlZaoK5z1Sg9P5LZImM0SY2qQA351LpsBbsOMdRxiKGOQxx1LOOo4xAHHQcY6DjAUMehzPS6gh4DrKYeKQYS6DHAUI8hhnoMcdSjjKMeQxz0GGCgxwBDPYYy0+sKthpgoOMQQx23pvd5PQ+p+5mwLvJk1cXny6N0TfXIU3wtwVg2XZiiRa8ZtKgOqTyccW0ebRg1eZpqy9k=
*/