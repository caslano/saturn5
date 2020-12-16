/*
 [auto_generated]
 boost/numeric/odeint/algebra/operations_dispatcher.hpp

 [begin_description]
 Operations dispatcher to automatically chose suitable operations.
 [end_description]

 Copyright 2013 Karsten Ahnert
 Copyright 2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_OPERATIONS_DISPATCHER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_OPERATIONS_DISPATCHER_HPP_INCLUDED

#include <boost/numeric/odeint/algebra/default_operations.hpp>

namespace boost {
namespace numeric {
namespace odeint {
    
template< class StateType , class Enabler = void >
struct operations_dispatcher_sfinae
{
    typedef default_operations operations_type;
};

template< class StateType >
struct operations_dispatcher : operations_dispatcher_sfinae< StateType > {};

// no further specializations required

}
}
}

#endif

/* operations_dispatcher.hpp
d8Xx/MVJfP+Kh0ceHnt4w8NbHp5M4vfrTvLYN0d77BsPr4pT/aG2+PIUHxO/A85H7RzD81dX/EGo39+dzPq7eqzid+Bftj28epzHfxCn96+Lnwbnj4fHl2xZmr/EF5g7flWd4okfTvHED8Upv8um8vuFUz36a6rHvprK7W/TPPphGss3p/Hzt6dx+3emefqn+IogX56u+CjWV/fEv6Z7/GfP9cOY378a8/vXYu4fHc/1bQa3X1mc3r8mTt+34+G1mR7/fiY/f3Mmt09bHPOrZ3L/6M7k71edxe3TmMXv15rF17fZnvE92zM/zfbYn7P5/ePZ/Hzt2fz+5RP4/SvidP26OH5/cfz+4qQfq3P4+jVxzA8Xp/dvi6P+muvRf+Jov4vj+D6R9VtTHNtPHMePOI4fcRw/J3nGjziOH3EcPyd7xo84jh9xHD/iOH7EcfyI4/g5xTN+xHH8iOP4EcfvL34FxXdOlf8PPBEfBfUbqv8l7C6DJKeiKADf7tlh0clLp3ELujjBHYIvHtwh+OLBHYI7BHcI7hDcIbhDcIfgDsFdDsMWM8C8c39QzNZXNx19Lvujfkvaz5IDeP2ngMdtkW9t+8Me1CeXkPWZ04NRf2HrO8AnZ/k7nI1/lEPQP0quL4c/yPzQPjlK7OuPR4f1yRFs/f3D++j+7QGcXX8EZ9efwtn1F8rxK+X4cgQ/fgA/vGW/fv8o1P/Z+ISj++Rh8n5Ux6B9g9WfFG/gV7D1GY/tk7VZ/ei4PrmO7d9z/N/tP+Pa2u8y3n+RZbz/ooDPRLyBL8zO/4Q+6bLyK5z9fgrfXcjzPbFPjmP5I5y1H8lJfbI8K5/Ch7ft46+aU3j7e3yqUr+D0/EhSnypeK24nIb2qRZJ/05X6mfwCRHvu0OvX+if2SfLsvZtOGs/yuFXjYH7aFu/80KM/4CvaPHmCrQPs/rplX1yeQ9ZP+naPjmZnX+B/nfi/nXoPyPri2Rwur4QfFwyfzy4Ee0vPfb9RZtb++QcuG9rX76rT+5h62Pc3Sf7sv6pe/j1pXC6vhL8bjI+OS375Gl2/+7tk9vZ79+H8yPtuw28IOujRQ+hf4mtrwBfmtWfH1buD5zeH/hUZH2Z8LE+8duk/e2JPlmKPH/zTJ+cycpv8N2IJ8/y66vhdPw4/MKW/D3Hdaj5LS8gfWHrG7w40P425mi/baVB81de6pPvEB9bjl+/0idbkePnr/XJDWOR8vGHKP+2SP3hY97/n8PZ+KkSTutfiteKN4rLJ9yN4j58JNs/G073b1C8VLxWXD7l7iseKh4rniqew88l81OTzzD+hc2Pht9A0r/88z6ZhtVv4HHbHl81fHyPfNXH56/An2X7C3yD8jHp/2zg07L371uUX1j9Hv4oa5/4DukXG5/6Q5/kLfv51T8h/yTzL9M/8PxY+gufuj99svQvtBx5jdyfuO3IEWT8uelxZA82fxF+CPF4GHfT68hBZP87Ge7Isyx+TEf2YvkvfPIx/n1/rt5gYP2V2DiyDnk+puPI4W1yf8d35Ely/8IJHFmMHL+a0JEP2Ps7EX6/h5z/5I58ROKzKRwJB+YX/S9/y6d25EMSX07jyNjk+qPp4az+pniieKp4pniueKF4qXileK14o7iM4G4U9xUPFA8VjxSPFU8UTxXPFM8VLxQvFa8UrxVvFJcZuBvFfcUDxUPFI8VjxRPFU8UzxXPFC/gtbdSPLemjP4sjR5L1k6PZHVmF9c/Ah7P3R/Fa8UZxTJCSgO2PC7+JeDCHI6+S/Dec05FjiDfwz4n7cyvvp+Kh4pHiMbxNyk/FPLz8VM3Ly0/pfLz85M/Py0cVd8yf4OWnZCFefkoXVr4vxXPFC8U=
*/