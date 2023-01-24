//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPE_TRAITS_TYPE_DEFINITION_HPP
#define BOOST_COMPUTE_TYPE_TRAITS_TYPE_DEFINITION_HPP

#include <string>

namespace boost {
namespace compute {
namespace detail {

template<class T>
struct type_definition_trait
{
    static std::string value() { return std::string(); }
};

} // end detail namespace

/// Returns the OpenCL type definition for \c T.
///
/// \return a string containing the type definition for \c T
///
/// \see type_name<T>()
template<class T>
inline std::string type_definition()
{
    return detail::type_definition_trait<T>::value();
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_TYPE_TRAITS_TYPE_DEFINITION_HPP

/* type_definition.hpp
l9dv1wP151YnE413JPfUb9WJdDQXSYSLznaso0hbNBaLJYr1a4RmdRDNWkw0q/UEmvUd+mpoNvXv+1RZMJ+QDJVmP826Er2YNr2AxvRFNH8DOjvl06JugJ8f75ogudtAlKuxafF8H+V6wO3nqSMe5eq2o9+fFbs8vjf5WOPNTT9OJupziTXxiRhhtkWxRdErInecQMJaoqtj9UliZBtjTbF4LLaa1lT9CbRr33zGvd+kyqPzgW8enB/E19+xDuqkmlHfND2f9U3/SpVQM2TCtyref8Gy54esJ3XR+o/pX7Nv/+bp5tPN2L9nNAf37zH//n0zuH8NT16jwnug993VzLKrSyduoZtvcDtv92CORG8Oq4u1c691IS2WDqthrnbHyNCnx5p5jJ6iyi+bWf/VHOzj5Xq80nb8vrw3+5SoOuUUvFd7SvC9hSHrKVfJVfFu7hR+d4gqn+F3z6x4t1pbj+tl7Ls0V9WNR1Ud9btuD3yXdp4S9fx/b6CbfQaOZd9ySpm2XkTdbrxH77VKNokLS+wtJDJkrSVEKkqW0eMkDK31+6+b9j3ntu9lurxJZVaLkRXgGG7UsUZWeN/7zJ/TZ2Lftt619SLrHXvcusuut6BfN7iWcOz4HYRrbydc+5UTcO1wC9sqzqLKFS2CazcIh+juLHjn5f00ecrg2qnWe9Vu/Za21ofHCNc+bHBth/Utre8OqbSHaz9kDB9r
*/