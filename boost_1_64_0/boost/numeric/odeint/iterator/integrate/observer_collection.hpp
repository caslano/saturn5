/*
 [auto_generated]
 boost/numeric/odeint/integrate/observer_collection.hpp

 [begin_description]
 Collection of observers, which are all called during the evolution of the ODE.
 [end_description]

 Copyright 2009-2011 Karsten Ahnert
 Copyright 2009-2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_OBSERVER_COLLECTION_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_OBSERVER_COLLECTION_HPP_INCLUDED

#include <vector>

#include <boost/function.hpp>

namespace boost {
namespace numeric {
namespace odeint {

template< class State , class Time >
class observer_collection
{
public:

    typedef boost::function< void( const State& , const Time& ) > observer_type;
    typedef std::vector< observer_type > collection_type;

    void operator()( const State& x , Time t )
    {
        for( size_t i=0 ; i<m_observers.size() ; ++i )
            m_observers[i]( x , t );
    }

    collection_type& observers( void ) { return m_observers; }
    const collection_type& observers( void ) const { return m_observers; }

private:

    collection_type m_observers;
};

} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_INTEGRATE_OBSERVER_COLLECTION_HPP_INCLUDED

/* observer_collection.hpp
O772HXFstkDGtP09Rcw+hX25En/IP8MbwxMzqLFgP41nwd+xSW2tWTf8uBZ1glN3qJsUJw8dwnhOG+KgJ/WCadTI5qFL4tYB+pjalj4ji8o9iVcK8QG7ExfIgYKowU4ErzeRi3KuMD4fAGZc/5CccwRYAz+us57YswScwO5aLABfu4OpRcAKbV8ZcPvsHrCGfixhrMSvK3EFWZQpSd0IHLoVgp7BntSmxMr5ivg8HUwLo/aBbS34CgwpSO6ykdpGZXwEvpYGBxiikl9jM5+gw4LYZMduPOOBKkpHEON64KtgdC3GIt+hTmYlBheFcwXCBV7uAO9nvCglHd99Ai8Di9rCLTeNQy5bsB9qqMUY/3AZDD5+A7a3A5OwtYf0KyMc+06lT+Dw7Qz4H/bb4UtixEqu/QW8HY3PDEd/N+CFNbEhuPg44uHfesJV4DLxY8hZ8iPv1/hdFM6CzobvIJYVRj60t14y7wYzviSniXsZ/KFe0SeFsZYQ2lMbbuALd6Y/cdTSajRR9NxsPXbVfCSckppaC/yl9lf4cgVVhFGn90KXqcjX/224Smn88oSNq1+jjxZqfm9RV+5NzG3CcQs5Qz4wIoBx2w2TqVlmoh/w/porbSI+3z9Gvk88jwbjTwQS94gdT8hf8pWmf97wNjBj9UJynPKMw8EDtjwkbmMnFdaBU/nx7QRiNbnFnFHsE0Tdr/c6fIkYUqgHeAN/23OUd8LLjlJDCaNPl+BA5SoRJweDL8UZI6GG0BZsuAgeKYyp1B0pyC+IbR74f17s4h740JjcNY18pz92RDyo0Q5fx94CIqlZEw+UvYxNYOP36HscbfX5GLsljqykXR/uo15SAnsvRN1qDPj9gL7DD16BE6/7jDgChk4ric39RKxpgCzgIRexwd/gRV2uwmPAy4NVif/w/aQq6A9O8GN3hVyLHAdsrQ3WeyO3siOIF/DiIvhWTWq1gchvDklY8mx8hry201nweTfXNsW+4GZegxk3GAo3OkMMRDe+LnDUEsgwjn4SL/siJ//FyHcnvv8qe8d0xk+wtWnO8CMv4uxV4lJZnoV8C9dBx8SdHjwzD1ifdIR7FXKRd/DjOGIf712LrZ0ZDL4eB5fGUxOFexWFL1bZTzxbTvzogO12IA8jxrrzngfpyIB3V34X/kxcyl8R++1DXX0T740m1vOcTUlgZwvqbNhDe+p1qZuJBdheKO+e9BF5EFyyvx+66EvNrgfxkLj2Ixi3ED+td5kaERylEfgxph/3wJ8aEEe8aZsT/tiI2qnrBq69CyZ+D5cgTn4wAf1/TM3MSv2Etoa1hFuAse+DL929OD6H93QHm8fgu/Xg61/wjC3wW3y8qBZb0acntpkXHhraFu4GPjjjN+1qk+/T7p38Lwk9NMKOMsGp6rzrLlwu3JW2ksPcfR3c9QXDC5N/wXNHNIRzUUePjaTe+xPxgFrDB+BaZQ3zFsHPpxNX4S2r4T17L1IHQAaZr6K7lxhrygdubSev60fs9GZcNQA+VBDMG8I33RiXizlOzD4B5/Ig71pKXRvMGIyuh8AHBzbGdyzkCcTcZQnUh67R1qLUCCowvgZ/jU0mD4Gv1Yfbrq5Cf5i7sMSP3I+ccmkx9BmCP0bAucHB7+aAheQbYZXx/2twRfKCrxtjrweZx7GJnCPGwr5ZvAM+sZxYnV4SjI5j7L8u3KA5fSQGvUN+U6k8/DcJ32hA3NfjE/sjkm94FyW3QeZh1Dff1/biGsn/HcW3uKbmaXAdX9xNHI/7mvuJ1W2po72Mv3jgX/mpw9Quw7yNWK1+Qp2xDrnWG/g7Naf0leDhGjgxegxtRa1vNfMAGjDfADtseAbO1xde9j7/GwE=
*/