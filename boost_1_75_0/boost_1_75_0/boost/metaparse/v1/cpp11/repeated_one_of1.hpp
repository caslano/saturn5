#ifndef BOOST_METAPARSE_V1_CPP11_REPEATED_ONE_OF1_HPP
#define BOOST_METAPARSE_V1_CPP11_REPEATED_ONE_OF1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/one_of.hpp>
#include <boost/metaparse/v1/repeated1.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class... Ps>
      using repeated_one_of1 = repeated1<one_of<Ps...>>;
    }
  }
}

#endif


/* repeated_one_of1.hpp
gK0hmPsJDn64X1qVOrDcD1/7AzuVIustcmQDdNFmDWMqbxjSMVnyb5CP7C6PZlLbdyJzGz+gHQlnMbGcGmrRODSxktUt2oCvLZZkNjNJT3c409QPRtaXai3n4NPTS4SysqzElFRd87+24U4KDYRNOhu/u3eE0uQl9uvxuzq9VFt2ondVe8ZQOsNw15mbo+0DeN5zKSuqARPtOQ8mhDEIKbmLdPUBPP8PaoeHCvH8DEOcZvH8pgoQz1FcRm99a1B5L4h+Dx+TON5T8I4ni6GYhqe/JIJWAIRMxJ870K+Fa2HbH3rAVNGVsnfSSZgdGS0Eb/WjvHCNuuudR9COGh6vu1zlGBTS8hYK2X23kJhdt2l+HxZgG26yAtL9OBtOnhZpVUPfxrpN0sXr2zB7urtxrvDm+jM8tBpF/rZewk1RhGKRAlJ3PXgTpTq6lhUBnJvbyva5iaREV7yDfErACTKg9yRp1SWZqPjRXR/cJEw4CBF4KahYqRz3p/PTlMa2Pwv1TZ6x2Cdnf2sjQ9YZsVP1S6GLvmQS3aGdufco0t5bYaiXOuDLjXAYAe1wW8KtaOektxpgO+6Ae7ADT/6pzUbyb8Zh+BIDwdqNhG20fiV0JYk2W/dQm0OhzSsdRNiVjI1tKBVjmO/uuZtR80PQh+U6vIc1P5jyQl68EZfJjOkleiVUrJUUBm3/YHl8/ejK2uzVVF6yNX+/dx2mDC/3
*/