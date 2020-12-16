//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPE_TRAITS_IS_VECTOR_TYPE_HPP
#define BOOST_COMPUTE_TYPE_TRAITS_IS_VECTOR_TYPE_HPP

#include <boost/mpl/bool.hpp>

#include <boost/compute/type_traits/vector_size.hpp>

namespace boost {
namespace compute {

/// Meta-function returning \c true if \p T is a vector type.
///
/// For example,
/// \code
/// is_vector_type<int>::value == false
/// is_vector_type<float4_>::value == true
/// \endcode
///
/// \see make_vector_type, vector_size
template<class T>
struct is_vector_type : boost::mpl::bool_<vector_size<T>::value != 1>
{
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_TYPE_TRAITS_IS_VECTOR_TYPE_HPP

/* is_vector_type.hpp
7q/D2Czay8Zfe+tdYmAO+xOdrfTsaZPVw/2Dna2Y5z4t+p4xz9O0dKSkYEinibLPd7KkEYRdH8dG2VcuwNx2EoC9u3Zz3quRAlW3fuXhhVm/MLaVF0L7THdb9Osow/f+qqUcsgTj4bVrZJiODW0ojVNBlqZFU/l3ZdwdVp/NY19rhutTmtLYr8tnMrCerTleL5PvT2302YR03Pb6CHNkOq52gwzXN6TUFg6Tz5JnJ413OuHSWPbBd5k+e/L60yf7q/EirMPN9cFH3/MmU9lq77lv3T9bjdYOJpmkx78prv21gi+kgXI+t/KJ+POC451EbcRo7c7fw3sOsnQbLnAuXQWeP2p3OoEHvmztakm2tba6MLlyZ+3p0fbMzvMTJ35UbxDTc60uPYspOYD5eLdvMj49BvN9sYKvH+f74q6rflyQFnMncYvP+l60mfGem3jTLMDzk1cZnnfJh/R/Bp6f24uvVjqnetZOrjrIIGvQDt599SSbn5aUpxd3eTo9ytNzor7TWZ7e/fppnk7/hzw9O/FGeeqfl3mC5/Py1Mvm5inJ5qfFDf7mSfl4qSaKBuq5/q/HS5uxB036fsSX7ovWw5wXsnv+FfScnjXHUP8i7rvNWNPlGpDf86pYPiwQwPj16vPkk5W9CzMb5JoY0y/RzHxEIcd+KMWFYTleosm+FQVuWKKBdFwPy/vlGcjLs65fymF5BjAnboAxsDyTpfeuJzCmWJ4BXX8a4Q72+rV8eOevd+OEiZ4nXViUjelve5P0fFrYcUt6WsMDzuWbJdn6pd14kUzno4Z1/Vum57Hw9raPPXqIUbxwVRTXL5Q3QdSUQN7PLB75712FS392wUTTqHbQexnpbYlxgnurdad3Ow7y/yu9oPbYI4fYwotYL2+Ya51knd7O5U+1/2eNx+iQ1pMXcRlI4Sqjjet0Totx/8x/XQKzd/uxhV6vrK8Ms5ne4ZO4/2/0PXDI+/MKfXXNeaDSdPqGJrL/36WyGuabC52MM61ry5FOSOVcXVA3Xyl02eC0UGFajt1IP/Vl9v+b5IHOP5U6G1WrWvfJ29r9H1RC27zjRpFnKm3rvE9Ke5/xn5smKJ7pNYVeyZx3jsukNxbh7ubK6vr/oBb07hZ6fWutq1ST9Pb++n9K71C2byv0KuoNl6Lp39Fe9X+ndEjrZwqdujXd3tOkE3zlf53S2bv0o0JvUzvpOQtI72RrYx/awr9vqyeehPUZ3VAtaw1ttWtd/1XDgjs8lpBORtqWOlHxmiSPNGU98DD+fzlq8dPfT2V55cM7GZCemtS1VkbXnvR2F3sPd9htYt45PIh/nC/cG9w1lutqiGKGtVwoUDV18ZCGw6Een5fzuCAiKKaM8SR9wqa21qaBpCcX0u+L00HvmcU5cpK+sVlf9ZnoG5tW4dJm1H34fl4+fiRmcuXGDsxDnL7qGJdGmSsXenSKhR3mIa52NBY0Q78o7XfD+EEhrK1es5SDElgLPHk+lWE6mnISI6wnu2mssbU+jYt0A+YCni9veUM1rf7rdc8nr8VfyOwcmrVc3wODa1kttUvnwe4N9+acgfjxHLvMrdKs4oHERe4cfmx90P3Qjx3P44mlqwWvZXcYBXxT4YyWXPeDVM0b6QTtdAMc1gyKPggzlBvHFFnZT764O2/n/MrGZuTFw2lWLx5uP7l7E/30bexPMEjlfv0bXeemR5d7P68I/d5nHO9EAOzXnHpMGi+NMMP0A8Sn3PWq8zGpL5fb+8bVxrg4EIgXo2XxKdcYY2AOf+gPXjNhQByG4M9bD/m6LpKvbMZ+OOx7Xs/L2RDmfFDaaDI/+UOx/hP2MyO+Itq2TAtFybxsFXePHot1gu5LDVY=
*/