/* Boost interval/detail/interval_prototype.hpp file
 *
 * Copyright 2002 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_DETAIL_INTERVAL_PROTOTYPE_HPP
#define BOOST_NUMERIC_INTERVAL_DETAIL_INTERVAL_PROTOTYPE_HPP

namespace boost {
namespace numeric {

namespace interval_lib {

template<class T> struct rounded_math;
template<class T> struct checking_strict;
class comparison_error;
template<class Rounding, class Checking> struct policies;

/*
 * default policies class
 */

template<class T>
struct default_policies
{
  typedef policies<rounded_math<T>, checking_strict<T> > type;
};
    
} // namespace interval_lib

template<class T, class Policies = typename interval_lib::default_policies<T>::type >
class interval;  

} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_DETAIL_INTERVAL_PROTOTYPE_HPP

/* interval_prototype.hpp
yyrH+QjQuMZj2mtxSJXFn+xP+l9e5b83ALJAPmeffq3Kfe4OvGS9CTYfA18cMCdTWp3Dm1Et7VBgXGR6uu576KqW8Z+w/WNFGLh9A3CLY+cPDOyso+uMav/4OGpsvq7QSfYho8XdaSnhHmuIq+tXOtj3MGzWDgFDb/8Tn0MCnpDl87HU5wMOtSmKT5I8PEaTLKQH2/vF2xXoDbsITJJ1dA3kYXUBeVxOPr8G3kIejFXyZQK2kGeHGuAwW+O6ug8O+Pl736Yp+h1aI+sdjUuc2i+9vIHrenrx2qnMb4BcSh8W8d97T+G7oPmzxGxv4Sq1ajsVPsZWKoZMLhjgwe8nLMLg7S+3d3dtFvOaWpWnwo/1V/prvct0zDi6H3wFDZVzL+tTcP/YmdGofst5Hz3OO/8On/zPffKrViN5maysrJA/cNxAe0BhY0ebUHw5ejWuJy+L4H5/x2rU72ayhcf/Mw3+bN4DMUmvT+CEVbl68bB20sAqxG5HafIvJObdurr/+kVuzUdvXc1u+/rLc9gfre7Sp1lDxc/JPBN5iu6QiWghG42tuDyQn8kk4+PiNTi+3j7xP0v0Yu3DayixVtEBeeBVuA4/5OkQnp+tuaaTn+nZSMc++65JvLmNQEP0pA/H4DYDbxofn7pm9t7dZF1Wywu05It83K/afQnygUu2R1+K8B5aU+CR/qxMlDkHyZN0IX8mbHXs/92aeeN+yO0/TsU9Amu1OoHDy0WVh+z6l6Y8s+qystQo8ijzK8y2nnYlm3KeJ9Vxe+b6mhvnxx2qK9wP7qtT47cdl/THj05+/1WdMpcndPePgYhlPA4izvnHwr4yb1lq1nKPw7yfw+2yJ2jUvsA1tc7+w/100VpqXQxWzy15H1pLre/h8f7egffq42OxvZFORnoA6Zvx4cUpa56vdm2zvrkJf8t/Zjnw53/3UmzndZ/Kl+pb7yCK+Yq/k6zkX6CHTNz33NYOyWflPJ5ZnON7G3l8WbQ2i3cac3IW1gOgAQ7FBF4Xkc/9iscL3p6Qvt+tTWMZ1p7oj1dWX8dfZtiNYvTsdUh2KXc0a99nrqO35hJkL6+63vLkOpZ8/n3qvrLgeiGOkjx/ruO/pphG3gsaz26BlmNBVuAp80W0drquo03532RPYPMxHn8Ohdq25LpubQnJDbpg68qWHEsGyos86ju57dGk5wVfXNd/LsumHbRebrw0fT3v9ctB64Xj423r6a1hhoV3RZHxXi8yXtn6Kh7NV/AYRr4MXB5bic+M9S2+/vsiVbknaD7zBFkGyL5w/eLa6qYi431cZLzK+uLi7VpkvBOKjHdfkfG+qzebu/GYs4FMes+G1k0oro6zCc9tDTXYmp7aNz9zgiWv0jcPYS+Rk06PTNDfQ1Io1k9FxFproj7WoPX08TAOQd/QFVf0OfePCNsNc7EBXqFYDxOWa1+f+sLqexNABwyah4DuAgs2A39ZF4Ch9o2FDt9PpD4/yiBaHVef5Kaj3hqr3W/Ze5Lsl4awJ95JzkWT/MsdOGyu3P9Zu7qRes9o3DdJjYWCls7ZOi7FRLaeRDLzvThfT6LylvL6261uZDDbjZss5Ccct7V10ACPMPj8F3gTHo/xkJlkg9yCJ82tv4Q8yADZ5LPkk+11cj0/MdE3Wao8P+6ts1qHiT8fG/K2C7whj+DDfUYdsxPepsh/cLL/HuC6kfr7J/zK+bvJhe2dsPlDJhpvrjHFrtd6e91BK59FMpub33cKn6vKm6/Br/n7KHhZnTolyw/yg5bWEkjvh5Fv18/bpK/+RfNq5ONsvYfN+U0Jd11w/Ya8MkR7oTd3Z8fhBOiBxfxblcl/DmpJw8B5qJcalHkoKduFy7k=
*/