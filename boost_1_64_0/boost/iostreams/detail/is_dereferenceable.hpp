// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2005-2007 Jonathan Turkanis
// (C) Copyright David Abrahams 2004.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_IS_DEREFERENCEABLE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_IS_DEREFERENCEABLE_HPP_INCLUDED

# include <boost/type_traits/remove_cv.hpp>
# include <boost/mpl/aux_/lambda_support.hpp>
# include <boost/mpl/bool.hpp>
# include <boost/detail/workaround.hpp>

namespace boost { namespace iostreams { namespace detail { 

// is_dereferenceable<T> metafunction
//
// Requires: Given x of type T&, if the expression *x is well-formed
// it must have complete type; otherwise, it must neither be ambiguous
// nor violate access.

// This namespace ensures that ADL doesn't mess things up.
namespace is_dereferenceable_
{
  // a type returned from operator* when no increment is found in the
  // type's own namespace
  struct tag {};
  
  // any soaks up implicit conversions and makes the following
  // operator* less-preferred than any other such operator that
  // might be found via ADL.
  struct any { template <class T> any(T const&); };

  // This is a last-resort operator* for when none other is found
  tag operator*(any const&);

# if BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3202))
#  define BOOST_comma(a,b) (a)
# else 
  // In case an operator++ is found that returns void, we'll use ++x,0
  tag operator,(tag,int);  
#  define BOOST_comma(a,b) (a,b)
# endif 
  
  // two check overloads help us identify which operator++ was picked
  char (& check_increment(tag) )[2];
  
  template <class T>
  char check_increment(T const&);
  
  template <class T>
  struct impl
  {
      static typename boost::remove_cv<T>::type& x;

      BOOST_STATIC_CONSTANT(
          bool
        , value = sizeof(is_dereferenceable_::check_increment(BOOST_comma(*x,0))) == 1
      );
  };
}

# undef BOOST_comma

template<typename T> 
struct is_dereferenceable 
    : public ::boost::integral_constant<bool, is_dereferenceable_::impl<T>::value >
{ 
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_dereferenceable,(T))
};

} } 


} // End namespaces detail, iostreams, boost.

#endif // BOOST_IOSTREAMS_DETAIL_IS_DEREFERENCEABLE_HPP_INCLUDED

/* is_dereferenceable.hpp
e1SQFPscjzL6v2kbw0VP0hB2X7S5niXHcqQSsgxJdN6LRZSfWk2LWv/vif4Qq7P3OEB83ntwuONo293R6S7jpOc7MVeZvi2pz+XNeuk7sUYSfqDkrzv/R9rZd4J8KnGch0Zvawax6nhcuodLamzvpqLa3fXYn8L9e3U0zZLjPO13+cjZzvNJ94jy1t8svKM+F94oYeZap/L/aO9yJ15T7iaO6TK1yrvdqr5n2d0ifsPpY5V5xm5wQtmdWo7fske7x2bDWN1Mmt1tN15t/a3Rsvw5MoW22yQzvCzVAlvUcmwp+qusPvKUHe9VjsTpYS/buwyNbiPKp5Kl94fy3jP0HvTHP/8ae80RZZLeyJLjNl0rB+V+qCSyTGR4iP47H9dDbMfavflNHEvK1jFS/QWpZyd49+9Mz7GRcx0fxL+KZ3m5w2ZILoIfG9tqu/tY/NfZzfh9ySHEBdZg1h5msj43nTWkjawlWPEdQ1kn6di5IDV4D78Q9of5eo6I/3mpob8R19+Fzt8xvpuoYSUAnhN6kjaYRJtuFfy7xegxnTItdfuoh3HrGnK7vdSts6X9YaJx6yHnA815dzm3zXmGnM/p+ePuBfc2dr1TVc503qlKvEvds61l7DgnOKd34flY7CxY7HnPrGHtqP3sS/G/3lpEHS7zfIeqcUTYDwy1y9owqRf+jNw+2lIybbMp7MJZfyjfovAtFJ24sLmq/R2J4X4jVK/FEofup9UrvG66cO6um2Rz3lXOa5rzDLOvgVN+dUz5ec3HjLA/52EjcKhzX9PL2NyL/ExsbFi9e3IbVsQR8a4wug0rdH+4Dat3PWxY6bdWrhduY3Cbh7298eR3Vy9vG4MmwzqG7Tx5nokn8vk1ep53/Yg87/TIM9cLy3NPzXO2h82/08jz3l4eNv9cdu9GtT5pXgn/w+2oEbemPzytoz3s9I1Ft8QjrVIxMdomLHHVS7cy6qXkR9SLl93XblHqJdPDft7pztjolVexqhZbvRzuFbtNtcO9frhNtVGty7apFsrrbR55reuMPb3D8jpo3Ogfbi8wZKdulYctvvpcK/HEa5mx7OGTtx8Nq9/sTt5+0P3h7edhj/azPoo9vqMtve0vNun909pf3N/K27Zheu8fZtswvXfstg3Tf0RZxmLb8N9t829NpszXz7plyMG75mWsbr/3hU+/vbb1T2fDr/Urjvuw1pdd+u7rX99y6pqzBj/Qb2Hf/7z1Cf9pNvzWzXbc37xs5nW31/3igYN1znn76RWPtv3nr0PwXpdycpt/+QiHfMdYDYuRc0N/qy3AlT5jC9D8zbwA+fsdi/bp+ntuaVj5PpGptv1y9O+eaucvMzR/Ud8J7kfcdmN+zeDg8DcwHt4Ga8FNMGR/Ll/Dfyrh3fbn8EfPhq/AFPg1TIWvwm7wdTgAvgHPhn+Fs2EJXAzfhyvgB/AqeBBeBz+Cq+EheAP8BN4Hj8EH9ToPwSNwF/wCPg6/hM+q/3PwbfihhvtE3Y/AyWYuGmWh+YpHRmu+1mq5rIMJcL2Wy82wHtwAG8FbYCv4S9gO/krj32XmUck8M4m/DrJN4++s5dYNpsFMmAn7w0FwAMyGQ+F8OAzmw1HwZ3AM3AhPh3fDLHgPHKvlM03LZxzcCcdreUyGb8Cp8K+q95a6f6vuto275mOrmU9EmWg5ydxCzcdhtXN2FCbCL2Ea/BZ2ht/BrrA68fWANuwHfXAY9MNRMABzYBycpfpzYGVYAOPhclgFXgOrwp+p3s9hAvyFnofSffgk6U7U8k+GibCO1kND2Bk2gl1hB013U013M013c013C013S013B013G033KZrutprudpruDpruUzXdHTTd2aG5LbA=
*/