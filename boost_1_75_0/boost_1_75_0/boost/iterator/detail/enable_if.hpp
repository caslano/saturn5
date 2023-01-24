// (C) Copyright David Abrahams 2002.
// (C) Copyright Jeremy Siek    2002.
// (C) Copyright Thomas Witt    2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_ENABLE_IF_23022003THW_HPP
#define BOOST_ENABLE_IF_23022003THW_HPP

#include <boost/detail/workaround.hpp>
#include <boost/mpl/identity.hpp>

#include <boost/iterator/detail/config_def.hpp>

//
// Boost iterators uses its own enable_if cause we need
// special semantics for deficient compilers.
// 23/02/03 thw
//

namespace boost
{

  namespace iterators
  {
    //
    // Base machinery for all kinds of enable if
    //
    template<bool>
    struct enabled
    {
      template<typename T>
      struct base
      {
        typedef T type;
      };
    };

    //
    // For compilers that don't support "Substitution Failure Is Not An Error"
    // enable_if falls back to always enabled. See comments
    // on operator implementation for consequences.
    //
    template<>
    struct enabled<false>
    {
      template<typename T>
      struct base
      {
#ifdef BOOST_NO_SFINAE

        typedef T type;

        // This way to do it would give a nice error message containing
        // invalid overload, but has the big disadvantage that
        // there is no reference to user code in the error message.
        //
        // struct invalid_overload;
        // typedef invalid_overload type;
        //
#endif
      };
    };


    template <class Cond,
              class Return>
    struct enable_if
# if !defined(BOOST_NO_SFINAE) && !defined(BOOST_NO_IS_CONVERTIBLE)
      : enabled<(Cond::value)>::template base<Return>
# else
      : mpl::identity<Return>
# endif
    {
    };

  } // namespace iterators

} // namespace boost

#include <boost/iterator/detail/config_undef.hpp>

#endif // BOOST_ENABLE_IF_23022003THW_HPP

/* enable_if.hpp
JKfBU5ONiFRo1unBERsUYK+1SP3K7HwHN4PaH/HJQy6X0PJv/YPW+YgYLWhbI+HAjFuY9bZdhGeeP38Gb/l9UJOK4HjTNhOzQJ2oX57yOiFpYUBX8zyw3sWhFkV0JGpZydcCcxj2XuMmOGPsosUrT7tnTVqRi7wLWdd8Qf0wM5UIjOzTWFE8iX9G6+P3OdlXdL6v6olmGWNzUtXxZUIXy14XBZLBgpqdCXOSarShixc19ndEwLeoJ6+wLBfDVBEDi1DaazV0aAHEMJMXY9uIQOKUTpJC4QVSXqzb8Hu18XeQaw6GuKE94/P0UAPttMkYEcZbf2ssBuVYRguTs8kx9klWPs0mfwtgoY7jHOqn6wWbksc8+9ZcPC4mlhS1qEwABJUUDt3ui9UnL8rzX8vzvoFIK5X90XQVMti1LY8JevcveAfZwcnAy76uTnoPZcojtVjyRQLVF17JO2DfTCodKG0Q554u9dbqYKqpdTm7TEaGSlbWy2dnkLmp0P98ftU/dT9+cuD5ut826ObJOuXJuYot9q0mqivm30Nmd04FfdwqiRDnTZM/o7fPW+xtGrOq/ZTDaD+d6F3IKJ0Z3fNUmMMGqSJzQVgD0Qp2wl5MNfq60u8guGkKhZSa4Fqne+5ptoFGgceqImD7xcvGzCo1H2Kp6CIan5ED/ZMZU4it45J1VWQX8fVL0EtidcoGsoZkoTIm3UOn9oZTWFHk
*/