
#ifndef BOOST_MPL_AUX_TYPE_WRAPPER_HPP_INCLUDED
#define BOOST_MPL_AUX_TYPE_WRAPPER_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Peter Dimov 2000-2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl { namespace aux {

template< typename T > struct type_wrapper
{
    typedef T type;
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
// agurt 08/may/03: a complicated way to extract the wrapped type; need it 
// mostly for the sake of GCC (3.2.x), which ICEs if you try to extract the 
// nested 'type' from 'type_wrapper<T>' when the latter was the result of a
// 'typeof' expression
template< typename T > struct wrapped_type;

template< typename T > struct wrapped_type< type_wrapper<T> >
{
    typedef T type;
};
#else
template< typename W > struct wrapped_type
{
    typedef typename W::type type;
};
#endif

}}}

#endif // BOOST_MPL_AUX_TYPE_WRAPPER_HPP_INCLUDED

/* type_wrapper.hpp
tlj6sIdOr70DYZwLyLbzb2FOYgCVZ9dEpZ3OkKWYDP4J9XRz0hyo2umA8xxaYEukC7nxZgOmhjzD9spNyLuxEx2138EbBQ/KIR0IfWGXiFX2KUw6wUUOqx2FZn1hMmo7AcpuBxM3n0d4jXctyKg5o0XaYhy27oLLD9nB7t5zeEJn0Ctvv8KcYGOYuEcEcrweUvMhDWzwOAGPw8Tg/ruZJFwyC87uiiXLrNNwnPZpahljBJ6PjlK5I+/xmN46eNVfB1FXH0HT3vuQo2dIDcrl0T/biQQZh8JJ31Yw4YmA5aOqcMqSFSr2RMLsqcMom/sIKsp2wPJ7zTTZ6AuqqqhhwTsPuPzanDh8HIAQvlJYIZwNA2L8NE0tE6NcY0h6wjF45lhJr3to47ym2bhw3C4cF9wPHN1PgCUlkvA/GcQrkhdpb+gjUPe6CWr9+yFk6Xo6Kj4Z+OyugJraJrRba0RTd4XgvGoj9BNhx6n50XQBOiDH6Twqc14IJjpIE8sJRfiuP5kobuUDDeFCcJb+CNcbHoNEvC1eiBCCuwfzcL4pG0bfUUKT9nVouUoLZtS/x4smDChbGQqJfHdBnn8VZJnehtGwNjQt5EeJZdX4Tvcz5OxZRPYpVQLnpzcQyuuCQTEHQb1+AdSYuRI3ZMH1bKXgwn0P3afwQcymaGg0vId5y8NQiWrTo7rRYGepjLa68WidX090/IVBEXfjeq5b8Hh0DilKCsFWsanUc00nNH6xob6nt+EJiXQozG/BGt5T8KzOGWQ236IBI3Ng9uoy4nPWHOKq+Wh+Qh0yCpSB1kjDVr1i6C3pw2iP0+RdQgK2mzwlq308oCj8NZEDUZwlXEhW+36AtLt5YPq2AY9eGCBv0xQhriuI3Ox/hOpRO8gci+kQInCRBhTXwi4BN5gbNh6Ebx1GZad23J1UhsENLzHz3FQUUD0EjXHPcJy4Eu7dFEpl/cxQ37wD0053okUuwVQOd9AViicLHQNRqikIB2/FwPjUV1TZ8Sz6LI8jOnN8wGMkk7x/Lg7TZp0mjLAN8KXwBOEuLMHXQWW4ftoUHFnaQ6dM5IGZdftpg408poaForGHFPDd3keEEgzh/vkvlN8zH6ukM+jui0tQ9EA32Z7Tg88fE7ShS6Cd0wwT4C286NkFXhkPoUbGiFbXGOFQ8Q5q924TXlrVD9MOOeDnz3l0D+th6DJrJy92jeH9Jl7MHOzCut53YD9Sglv1fMFihQwev36OHhCXRdcuBu3b2QiGF14QFpZ3aKplQHWWtcP41g66lP817pd3JdNOEEx5/B7ke2PxltNUnNCWClJiQBwdLyPbhrdYtWMA/Fo0yfB1edA4+JkeYJmImw+Woe8hUwztfUX2lWrj6961pLE8GU2KJFFyTyqaGaynrl038faCLjqjbS42jZVBpeg6vK93Dbwti8D+gwltX9wOLVWraTlXM1wWaIL96rIYfIEfknI1QPCNM42t6YLbzh5YP/Ek8q44RSoXymLnbFHoXpuFq+VDaTKPHr4lk7BcJh3lGgbplVoTKF63HOZrn4POkBUkT6MQbgWdoavVj2L8wzBMjywG346HNDHbD+I9RmnXXFVQe6QKs2cJwW5HY0INhlAsRR0qDkzEAlcZglt8cZ3uDFjbMg7mdruRLJEYWOfdRitwIYhEjYcY5Q04P/sIuL2KwBmVDUTkmj7sPB+K+45Ng3U25dhvWQjkzmkqsd0FJlS3QLHdV9znOY16b5VFP2Z+fjqfF48zatDtzFVwnMpHLuvMwf2fDkFn5gio2d2kj68egNe2F/HRpi6c2faW1ppuxk1q7HA8zxyuCiYgd4INKkyfSMzLs/CoymVyybsSrJKuALk=
*/