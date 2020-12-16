/*

@Copyright Barrett Adair 2015-2017

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_REMOVE_VARARGS_HPP
#define BOOST_CLBL_TRTS_REMOVE_VARARGS_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ remove_varargs_hpp
/*`
[section:ref_remove_varargs remove_varargs]
[heading Header]
``#include <boost/callable_traits/remove_varargs.hpp>``
[heading Definition]
*/

template<typename T>
using remove_varargs_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::remove_varargs,
        varargs_are_illegal_for_this_type>;

namespace detail {

    template<typename T, typename = std::false_type>
    struct remove_varargs_impl {};

    template<typename T>
    struct remove_varargs_impl <T, typename std::is_same<
        remove_varargs_t<T>, detail::dummy>::type>
    {
        using type = remove_varargs_t<T>;
    };
}

//->

template<typename T>
struct remove_varargs : detail::remove_varargs_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be one of the following:
  * function type
  * function pointer type
  * function reference type
  * member function pointer type
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Removes C-style variadics (`...`) from the signature of `T`, if present.

[heading Input/Output Examples]
[table
    [[`T`]                                 [`remove_varargs_t<T>`]]
    [[`int(...)`]                          [`int()`]]
    [[`int(int, ...)`]                     [`int(int)`]]
    [[`int (&)(...)`]                      [`int(&)()`]]
    [[`int (*)()`]                         [`int(*)()`]]
    [[`int(foo::*)(...)`]                  [`int(foo::*)()`]]
    [[`int(foo::*)(...) &`]                [`int(foo::*)() &`]]
    [[`int(foo::*)(...) &&`]               [`int(foo::*)() &&`]]
    [[`int(foo::*)(...) const`]            [`int(foo::*)() const`]]
    [[`int(foo::*)(...) transaction_safe`] [`int(foo::*)() transaction_safe`]]
    [[`int`]                               [(substitution failure)]]
    [[`int foo::*`]                        [(substitution failure)]]
    [[`int (* const)()`]                   [(substitution failure)]]
]

[heading Example Program]
[import ../example/remove_varargs.cpp]
[remove_varargs]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_REMOVE_VARARGS_HPP

/* remove_varargs.hpp
2imzQ1L2lm2NVh7o5t7QOLqa96d0PWeJ9zPVmaPF3+nQ9zMN38WsqZYm57udt55r/PWjuf/6SZid9nc04vHb39M8J6doerUNV+TGlnweU/zZcKT43+Xwe4cz9+h08f9Y71Fveufx/MymTMw5zXN7gchn2+63PCpBcX7Mk/DXBLt+DTOFMMV6f5HINDbP8HFiz0PvJ1v9uQciA+zL+fuS74ji1glzHKPPcn1nvMT3xkMln+nUG/+5ZXqv5Om7oP99Yt+PU+qYuM3weWcMuienWReuU6wlx/uYOOUx3PKelHKanlM4ibVU7ffPdPPdfEBktqBNKuk95Q13TaBx5up3lWm7vl/suym9CPv3TEt7+/g2kXmY8UJlzD1EPLquoAljvun1PlGZ+kYXblB7cV8N7Qbatvup+GXzZR7l04ZPHOYeoTyC7qG7WeQOWvv5b9rw/cJTfqZ9xqHtM17Z9n6ylKvZl/PX1KmH9Zt/mPf3RdSz8j7rbk73H4fut54geW7W2zRutjy17+84IdDejqY+Pilunuv731pvrPkKj/u3Mwf/YXnV9gNmJtz25cn4YU1K1xv7T1pvzNM2dRgOwuh+etoPK/3I+Pnup5csY2eRhzVgCmwAM2AjOAY2hzfAdmrvqPar4VDYGw6HKXAEHG5bD2ur6VeU/lU5f0sM40DlGKdjM3NgYzgeNoUT9LwT4UdwMvwMToEVdYxxJDwMa8ECeCWcCpvBabAFnAn7wFkwBc6Fo+CNMAvO03Wb5sO5UNbLgovhE3AJPAZvga/DZfBNuBx+DlfCL+Aq+CNcB2s6KXNYH26EHeEm2ANuhn3hnXA4vAfmwnthIbwPLoc74Wp4P9wKd8MDcA88BPfBw/BBeFzDvw8fg9/BgzCS/H4CRsNDsBZ8EjaAT8FG8LBZB0r7eWCtAOudPafrlj0PY+ALGu6o6UOQfhgJ19a2xsJvtV69ChPga7AHfB32gvV5wA6Ex7XevAFHE/YEHA/fhHnQIzdL7UvgW3AzfFvL689aXu/A5+FJ+Ir6/xG+B91O7i1YFn4MY+AnsDH8FLaCn8HO8HOYDM9oOZ2DE+E/4AL4NVwFv4Fr4LdwA3wPPgr/Cp+AP8Fjur7du9ABv4Yh0El+hcJwGAZjYTisCyNgK1gedoeRcDysDCfDqnA6rA5v0XC3wppwO4yDu2AtuB/GwydgbfgsrAtfhldC6TfTMar7vW2X2vZ7WNtCdmg9OIVcA/gR7AY/hkPgaTgZfgFXwC/hFvgPuBd+DffDb+AxaDHc8YQH8D3ogh/DEPi5+v8dhMIyjiJ7WRgOK8DyMBpWgmelvmo7Glyl6S5aX49Dx/pGwd6wDrwOJsG+sDfsB0fBAXAqHASXwSHwMBwOX4Uj4bswFZLnVhaMg+NgI5gNW8DxsI36d4NDYDqcCKfBPHgjzIfzYYHm/1LT/sN7j15XeR2HbOmY4sqwOewJW8N+sA2Ub3U4GraHmeo/XuXnwyS4FnaFd6n9HtgJ7lD7fep/FlYzbRnUDYfmsyX1U441yF0J12t+btR83Azz4J1wDrwLLoZ363nvhXfDPXr+XXCH2vfDvfBBuA8ehb/W/H8YnoCP6tjuA/Az+Bws40A/QeqF2OPhC7AePKLl8yJsDl+GfeHrMFPsqm/gTPg2XAb/Am+Fb8E1cBNcB09q/oSZ71F0luZPHOZ779wUZ1H+xMBrYQ04ENaEo2AsHA/jYAGsDRfDenA7bAgPw8bwD7ApfAs2gx/AFvAjmAC/g61gJdLRDtaDV8Ek2Bn2hd3gUNgdZsEecArsBWer3Hx4DVwHr4X3wj5wJ+wP98GB8AC8Hj4BU/Q+3Oh9j4fva/2tiFmh+TFDx84=
*/