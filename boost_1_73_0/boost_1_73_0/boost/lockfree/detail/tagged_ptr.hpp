//  tagged pointer, for aba prevention
//
//  Copyright (C) 2008, 2016 Tim Blechmann
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LOCKFREE_TAGGED_PTR_HPP_INCLUDED
#define BOOST_LOCKFREE_TAGGED_PTR_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/lockfree/detail/prefix.hpp>

#ifndef BOOST_LOCKFREE_PTR_COMPRESSION
#include <boost/lockfree/detail/tagged_ptr_dcas.hpp>
#else
#include <boost/lockfree/detail/tagged_ptr_ptrcompression.hpp>
#endif

#endif /* BOOST_LOCKFREE_TAGGED_PTR_HPP_INCLUDED */

/* tagged_ptr.hpp
2QAV47N2BmZSwhevjzcGYwnsc6w3K9E8J5RV8e2qxWuo/a0ryysqTiQL7m99I+1v/YdNjGXEAJ1rf+tL5SRKvnLsb30xTHEvt/F8g+xvXdSYg2fbP3oAynM58MY28fe1cOTaP/qXUMAbIfWVS/n7IKaXYz/qzZDexH9k7JbTDV6u9F6H9JJnwFyvg78PD5JeHRzvwBPbwjP5e/cg6T0FRwo4J6wweIOltwQ4N5h4udJ7Fo7twPlh557TOwPO9zE=
*/