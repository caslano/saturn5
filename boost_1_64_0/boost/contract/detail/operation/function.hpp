
#ifndef BOOST_CONTRACT_DETAIL_FUNCTION_HPP_
#define BOOST_CONTRACT_DETAIL_FUNCTION_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/core/exception.hpp>
#include <boost/contract/core/config.hpp>
#include <boost/contract/detail/condition/cond_post.hpp>
#include <boost/contract/detail/exception.hpp>
#if     !defined(BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION) && ( \
        !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_EXCEPTS))
    #include <boost/contract/detail/checking.hpp>
#endif
#if     !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_EXCEPTS)
    #include <boost/config.hpp>
    #include <exception>
#endif

namespace boost { namespace contract { namespace detail {

// Used for free function, private and protected member functions.
class function : public cond_post</* VR = */ none> { // Non-copyable base.
public:
    explicit function() : cond_post</* VR = */ none>(
            boost::contract::from_function) {}

private:
    #if     !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_OLDS)
        void init() /* override */ {
            #ifndef  BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
                if(checking::already()) return;
            #endif
            #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
                {
                    #if !defined(BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION) && \
                        !defined( \
                            BOOST_CONTRACT_PRECONDITIONS_DISABLE_NO_ASSERTION)
                        checking k;
                    #endif
                    this->check_pre();
                }
            #endif
            #ifndef BOOST_CONTRACT_NO_OLDS
                this->copy_old();
            #endif
        }
    #endif

public:
    #if     !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
            !defined(BOOST_CONTRACT_NO_EXCEPTS)
        ~function() BOOST_NOEXCEPT_IF(false) {
            this->assert_initialized();
            #ifndef  BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
                if(checking::already()) return;
                checking k;
            #endif
            
            if(uncaught_exception()) {
                #ifndef BOOST_CONTRACT_NO_EXCEPTS
                    this->check_except();
                #endif
            } else {
                #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                    this->check_post(none());
                #endif
            }
        }
    #endif
};

} } } // namespace

#endif // #include guard


/* function.hpp
4RNwf09w8LfY0bJfidlhL8cwR5+hdzPQEQs92LV52D/0z/Kt8H4YcgkW3bUXXJxOXIR1ofnU+Riy3wwcMLk1NhQ/qmIx/R9oqRjwRavAwsOheS64G/v9YUf85eHwdkN4/Dn03wTimEOIneZjA5mTb5Dl7GnMCzhjegf0bRr4Dv/j6DTmH12YdxfxZeL/vejzMxnIWzE+4TJsYDIY8j7ihwnEdMAKE5G1cDBk5ijoRAwoBxpsR+ZXzsaffwDsjh2X9x2+ncQ8RaHPwLA1EsAlQu5NxKcCLxb8k6T7jtex/OMA/jzPsbP3yv6hki0jm2NlZYc6OI7tODl2doWMMpMZKqQiiqwyioqsjEiyhZKZrPi97+OPXuI8z31f1/f6fj/je133fQrpA3wvp9TPnVo0Bg2fD+flaS/P68ODOrR3NWsfw79Ns58oDpnyhJzhgx88WnaaZHZbWE3fNKXnvrjJp7lu9ix8BJ0aF8930xE77aO2tn/f3J7KmsXysButO8J/arHjAOe3s5oXDLmpv9CsXyjpfPLGR7Tvq8Geoz4jPk//g/GLd7rP3eeStVdvixL03jfj71h6xr5Zwj4xfQgH3uFraZSgd72+oLXWE37YXF82Fe+Np4umxxEf8rk/84a39ZBH4GTjiMblKTrLqaL2fNTH6zzGit/lSA//DiMnisW6NPTmSf3cI3oHc3GfvlEZmmcRXdclGeyMMbaO9oefp2kWwY5ZaiIO9t4VG7U7py+8oJ3aGn8d89glTtu3h2luOPwLzT0Xp/FrrfiRVLl43GF4+TO8dBeGz+Y/16gz9z67hK56g3cq67OZ8IGYL+CNOsGumG3m2tv6ZxGTJvqiyYJzWLRII3neDx/ikbpb4etDdZRM3ts/HyZOoXG07Rp9zMNy61n6cZ5/h0/fnoMbesY7jqvXWWrxGA+ijziEHvtbLaRwOKApnXVwtJ93ppf30I+jjb0ZXqO9P4JXc7/U07wRleTnB8mR9a4V+wdd3cX+Sm91XVWtmP+7FfRMtsDL6TAEXzcXu/BNdTAfTlXmyR7q84zkf/eE+CZevF9Ib1LewopaMODiBJzh78Ni9EM2B+dV+M6QfH9JDvPUm3/HlXobLcW0nfl+sIJfUUsdv/X3RsZSxFq2g51l6b+xrqFGU671GWNqOUat9XftDTQVH3VgIW5uRQ+qtfiPeIi2tJk9htIXaWzX+uOaMeWnO06Fk3hnKVzLsBvn/EDXi3kePfFyUbxjcC62Is6DC4d420Vh6zNEzvn7fl6mfCvaaBFMou1mLZabeOJrHrFNReOPocFgzHtZebw7xgcvy+ttXT+FExfAkQL2P3vwkkRjm+FiVzVKrejRlHQWpqyY58WD3eGFnsaAp3n8WNw0hBe4hUfftE9wRUx513X67T+XoHngRfB+sb3qaJt7vGqcu2HSd+p5pHFO05NqGqv+UqiT/NZJLJvLo+m8/eDAM8vJ+no8iybCJlr8r+J4oqh1oQkaGtMW90ufTp3AlWy36IwV8Nr6Z5KHU2Bc1e6wRJ6Eeb5bH/PK8O78Ub3D/TyAZ5LqwZCa6qC3ekrUaxnwKi8hXtefgB//iRHtVwTfTKdNOnVzns1Yzpj7IT7/aTlyp6vnC/Q7xo+luX1/unjNsMa1+abNuP2fz9RoX+dW9L4ybjDHLep3Mg6KDtPpsFucx9G1yUuK03qcPTQ4g4r3BtCAMGLgJf2BTPzrSrlcTY7AqsGz1KSYfiIWb+ErYQ2Vg5Ulz4oDrVsCz+2Tf6sGqhNafFMOuNvbPX6Ti/K21X90Px77fRGN/bueyqfyyt5BVKyxWqcdjcX0Kc9VLFMLj0LO5fqZHFxzVOwbGBO9nnAQ1+I=
*/