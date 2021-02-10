#ifndef BOOST_CORE_NO_EXCEPTIONS_SUPPORT_HPP
#define BOOST_CORE_NO_EXCEPTIONS_SUPPORT_HPP

#if defined(_MSC_VER)
#  pragma once
#endif

//----------------------------------------------------------------------
// (C) Copyright 2004 Pavel Vozenilek.
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//
// This file contains helper macros used when exception support may be
// disabled (as indicated by macro BOOST_NO_EXCEPTIONS).
//
// Before picking up these macros you may consider using RAII techniques
// to deal with exceptions - their syntax can be always the same with 
// or without exception support enabled.
//----------------------------------------------------------------------

#include <boost/config.hpp>
#include <boost/config/workaround.hpp>

#if !(defined BOOST_NO_EXCEPTIONS)
#    define BOOST_TRY { try
#    define BOOST_CATCH(x) catch(x)
#    define BOOST_RETHROW throw;
#    define BOOST_CATCH_END }
#else
#    if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#        define BOOST_TRY { if ("")
#        define BOOST_CATCH(x) else if (!"")
#    elif !defined(BOOST_MSVC) || BOOST_MSVC >= 1900
#        define BOOST_TRY { if (true)
#        define BOOST_CATCH(x) else if (false)
#    else
         // warning C4127: conditional expression is constant
#        define BOOST_TRY { \
             __pragma(warning(push)) \
             __pragma(warning(disable: 4127)) \
             if (true) \
             __pragma(warning(pop))
#        define BOOST_CATCH(x) else \
             __pragma(warning(push)) \
             __pragma(warning(disable: 4127)) \
             if (false) \
             __pragma(warning(pop))
#    endif
#    define BOOST_RETHROW
#    define BOOST_CATCH_END }
#endif


#endif 

/* no_exceptions_support.hpp
8U7dIqvicax1OtDHGI/hhcJyoGBMSnFiZZnUx+QLNmMDxyiNWBDctgydxn7m2SaK9YLtPVNFhRQN2XhX9WVL+dYjSgFWRa3zAaYc340s4dfsvi5wC7+ePMAoaHU/AgXxff0yNe/HQIln4GzaYhXktAMT7t0+P5THAP5EJI9BPBaIOTGGzy0dFgXh7pB2fVvfpjC2O3tvB/olE5GtR6d4u4EDOjsn+TczRuP7oa0Feh/rlKZqEQntGmRkOVouGOPB4E0Ljw3cmzNcIl2irepbXIijWRTnsyk2GC0k3OEoF5nBKR9jixJ+wn4u3YDDQckmToX4AsybeGzpkKTcF9iKzfCoYrKlOY6PxXspHpwglhKpthCkEfR59i9Gg8Hoy2B01rUJ2LrxhCJe8NgX/x0pOdyq5WSKe1XZooSnNB7a3TkpQj0LOb2N4IiGdROnm6OP20gAf+sYi7356JeiYz3gnocm6hDgHMt9oqPdtr0TG7I72SVj9dIOMHnH1vjKITmLsuRhMvMH22Dud4q6GQgzA3U/d/uD7sf+oD+7wsGIUM36pDe7nAzhc3dw2XMmRlFtQjUStWmvB93BdFRzmh8nuxUDNRzaMXh4MMwXT5z/A1BLAwQKAAAACAAtZ0pSbhgPlTgFAACYCwAAOAAJ
*/