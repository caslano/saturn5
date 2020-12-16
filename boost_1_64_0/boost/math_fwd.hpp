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
bAhFprqQpE4m8SCJR6/e5kAOyMrKZKonkUsRkhQxF2SBjOxcisxc+LZWXYdjdOpxNXgD1WjyHfWC4dU34G8l6qNCK9mjlRxDcGMa/2otVqGO0mquciWVITim0/1oLfIOGc3MPsCK2iYX3hp1QiwDIf5u66NIrBu+bqYVR3vJflPbBWsWvqxbB5mEocOGajwi8WKgROzpDDRyiaUWu7ANY3g4RX4ng6I3V0Kb+d8JuSdvCZY0V5XoRjQ8t043Gishku1/hVrDAc4bte2vBhibfRAT+6HhjXisbX8lZOw33tGjbd7Ac7Qr9D9QaPzmPnMlvyIr2gO6v37xICzpbRvOFbVRvQNBuFhqjzXSdWH3L7aH3L/AuvQNekmTvnrL4hKE7/IlVgWajFcb3ghB3zM6XLJdJtLiTaGSBiStQmeKFawHYW+0elE7ur9Fq4Fh4q6I6iUtIX/josFYpY3kgerXnVVnhUoaxb779TpyJQUUQ4v+BV9f8bZeBaZDIuR3+I6QIaQlFmBPZ9OaJaN/Z/c7/jfXD+rbjpquVKEJdgeMThxZWLm6doXbOh2K2w4jNFmq/ecpduoF0QEYRzRWTketbJ0b8SBsDK4EaFH8SqMJkt/IPdrdv1iPr/VYswupsYZqRvt0dwVUVoybtFJgeL5Tw/lBYWVr2L8VMq67EnskhP31Ws10irw5pCAg2RmKOHF4nytUc4MTZELuij0gQ2oDSyrgCvlx4YwsHhV4wql5QM0Dah5QKzrh1IpArQjUBCWS0avXQ3NFvdVv5Hc0SL31QZzlsxpVuko04UNme0P/cwoO53blVsPgi+x1x1oBWNsYqiknG1ijrneG/Lgieme4ZpYz7K5oqX7DuTjC3qhIp6VDCNqg7H+8/H/6kxavr3HSwA7aDxmnwlYIG+jFoBr3wIzQo696je2iq6zTIW0deinRInFnaxgXl577mzUkqSm4AHXQJOEBXfSyF2n2ajXLnNjyQfPv0SNn6Ma1DlTF0aABzam5KqGVQCRobNAEiShVX4j/kTE3APHXsraRsWZnLFQkCQvluNZiJ6w0h/3NYaMSmbZQZyKaV68ZP1H3H9ZqNGKxUfPHeYhs9Q50rXHN3xow4jr82uXuRxuCxlYijORBEJzUkQtcG2D82SizwV8z2ykbABnZg5U5QNnusH83udSx+Yr/iB65xwVmPNrvLQbBFjkGW+SOhLHlBehq/hhuHCBp0gMbySwkI7yU9FlC8tAL/Tbd3wZqoGT3H5wuAq1QzXj43Q+E/O3uR+ttiqJEn3T2RjULihYtbP2A/PHtOFh1kLIHlEkMPFFypAfeSHpgSXIGQYgyMt9j0S5K0E6lS5qkTXI27awEHMZ+Mv4jaQK2ilkzjgJGnULAFqKSqJF4giLJUfIECqj3iaorGUXHs0WRVrOEVIv6QDIVtx0pKPqDrRzYam92dke/LGPlSroWRVADKatysWHLwiJyLsqeReWWpVeuJwtg9VC5svVoXVpPGkVWaW6QklQTyqwr/SLsvk8WZMvqqqs2WGLmbklsZdBbkoGM4pbE9cidXiGd57sqrK5MZKmxRJ+cEWfUmD03qElFmr8zAB2dLb0saFlUoKV9AkwUmCxgJ3t/DSTZJaCUYEtCbGMm2jQXyrNg4LjuP67jUOYEwOs1sRNSZErZyfnG/+dPZvvsaEb77Nlu7DMMJqWJlsE8O7OreQbTzLbJQA550DSjqWZT4nGvtq02sHaaMNPY5aAx0kzLwUYL1SzJbKMtkTba2ixstBD6up41EDgYUHXvCglNq+7NxlTLVdUnmU00k0CCJJPEwC6mp66VfYvV2Um550RbhxOaREGs525GFj7UbTeTRDu3PjY=
*/