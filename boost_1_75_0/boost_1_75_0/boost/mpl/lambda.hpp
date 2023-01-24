
#ifndef BOOST_MPL_LAMBDA_HPP_INCLUDED
#define BOOST_MPL_LAMBDA_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/lambda_fwd.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/aux_/config/lambda.hpp>

#if !defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)
#   include <boost/mpl/aux_/full_lambda.hpp>
#else
#   include <boost/mpl/aux_/lambda_no_ctps.hpp>
#   include <boost/mpl/aux_/lambda_support.hpp>
#   define BOOST_MPL_CFG_NO_IMPLICIT_METAFUNCTIONS
#endif

#endif // BOOST_MPL_LAMBDA_HPP_INCLUDED

/* lambda.hpp
/ba8WKjwjLy3JdUlG2ebcpTI9m29AiwFEvdioVu3XnXqK5/xUHot1WexN9U64kb5tqfznXIwDwGDE31GwwE2h9D5WiV9HM5QC9PJE2fjEeO1g+/RxmPpNaQO9Ibj6fW9cIANTQWeBnqOcwnsc7lZvVX3aUh5CGfwOcq7c5S15Eglzw+2FaHzkkWNDjT25lRLqsFfm4COESrzJYDsrMEHARTwYagxfYcXjSQmvzGqIPuPbNDi/crIiEfK8IMjeYue5As6l5coVU28MftVwR1Uy2QHGO/rdQ++CPY5i/zIdLTu7UKxSaMldVaBbKLYflld0p3CS/lG2L2O3evzHRz8Ci094pFC5PV96I/P1+QDSoe6rFYgnPuFkdDnovNF1zf3Qz/D1Z9xbPjeBSHvkyISssqLOKkk7nUQndukzCC/q0v6yzcw1T3C5E1JWiYY5z7fG1Cxf+aeYJocM6iwgRd2/qZ/D5oSphIo2Bozcskx9OOp6+bPlKd33DCxA4aUTUtam5v2cf6UTS5KWuO5q58A8b7oU/s0Di+DpNwjb6PLuP4k0XDVz0r+XtubOviG1wWEC49EI/TsZYy6ePIs3thVY4kGl1TUPPJ4ipOgxRJrIC2t4E4RV92caFrB7ibk3lDhw840MdY6XVycrNVK6Ybbs7kLo8NgnBDrI25p++1zVLRlx+KIkKH34HIvH5gM6NJEYpNlU0ADfIQ8+84W
*/