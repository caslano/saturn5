//  Boost math_fwd.hpp header file  ------------------------------------------//

//  (C) Copyright Hubert Holin and Daryle Walker 2001-2002.  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/math for documentation.

#ifndef BOOST_MATH_FWD_HPP
#define BOOST_MATH_FWD_HPP

namespace boost
{
namespace math
{


//  From <boost/math/quaternion.hpp>  ----------------------------------------//

template < typename T >
    class quaternion;

// Also has many function templates (including operators)


//  From <boost/math/octonion.hpp>  ------------------------------------------//

template < typename T >
    class octonion;

template < >
    class octonion< float >;
template < >
    class octonion< double >;
template < >
    class octonion< long double >;

}  // namespace math
}  // namespace boost


#endif  // BOOST_MATH_FWD_HPP

/* math_fwd.hpp
34CUfw1MooRztkFA4lxNLNRsbwP+FG+BdR8mfJxbOlscr7PdB/Bxe1gOmCvxYoUJSqJzxaTmtahzBSfKjdiI+KH23TAKRWJapFQf4+ncf4P71vpC6Ms4d7GoA4jWo9h7Ruw73yFml8NMhGGS4g6t1JUs3hfnbuM+vhZJ7KUfDXQve3st9Csw0RXqhRe6oX4WWlufYsbhnCuvPISkJOaapIfmikOkh0rEDKM0JGEwO7N4MBrmW4oxIWRaAQaf+xGIJcMkJZWt09sH8o16MakMStLhuRjUlDAYTwY5oei4iZyvk5WDwKmAlN2nYYq5TXWSTgyVkoxiirF1t2qnArMwFI2XLMQQSkL1FqPVag3Bf/fEkkzcvB4VNT5zWpiJ3Bcbm5cJXDoqih5xmWaUzIB/hCwqWwT/TABBwojJBI4J/gszaeVXVi6vrKqECgzLK5cvqwwPCYEaBEEIISQ2tjKzshqgR90xPjOvEvJDJZmZeJwRNaqyuhLPO6CakpISkylsUVmZo6wsUH6/KyaugFK2mT8Vxd9/jNpfPG9vA7Gjpta/MMKy2ESCV0RuRSWa4HDzdbBYblcXqaDFia2Ku+jq1G1oBHqIH8q94k671aOuh/T4DFef9oFGop6WjOMrzGThnYo9QrGHs5mYW/LDDTqLfAeHZl4RMCzVBwCe9/WABjKQGVY/jMYVGIAiIV/wHH6NztfwAjRPf9mMkpN3
*/