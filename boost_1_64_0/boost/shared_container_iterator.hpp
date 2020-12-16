// (C) Copyright Ronald Garcia 2002. Permission to copy, use, modify, sell and
// distribute this software is granted provided this copyright notice appears
// in all copies. This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.

// See http://www.boost.org/libs/utility/shared_container_iterator.html for documentation.

#ifndef BOOST_SHARED_CONTAINER_ITERATOR_HPP
#define BOOST_SHARED_CONTAINER_ITERATOR_HPP

#include "boost/iterator_adaptors.hpp"
#include "boost/shared_ptr.hpp"
#include <utility>

namespace boost {
namespace iterators {

template <typename Container>
class shared_container_iterator : public iterator_adaptor<
                                    shared_container_iterator<Container>,
                                    typename Container::iterator> {

  typedef iterator_adaptor<
    shared_container_iterator<Container>,
    typename Container::iterator> super_t;

  typedef typename Container::iterator iterator_t;
  typedef boost::shared_ptr<Container> container_ref_t;

  container_ref_t container_ref;
public:
  shared_container_iterator() { }

  shared_container_iterator(iterator_t const& x,container_ref_t const& c) :
    super_t(x), container_ref(c) { }


};

template <typename Container>
inline shared_container_iterator<Container>
make_shared_container_iterator(typename Container::iterator iter,
                               boost::shared_ptr<Container> const& container) {
  typedef shared_container_iterator<Container> iterator;
  return iterator(iter,container);
}



template <typename Container>
inline std::pair<
  shared_container_iterator<Container>,
  shared_container_iterator<Container> >
make_shared_container_range(boost::shared_ptr<Container> const& container) {
  return
    std::make_pair(
      make_shared_container_iterator(container->begin(),container),
      make_shared_container_iterator(container->end(),container));
}

} // namespace iterators

using iterators::shared_container_iterator;
using iterators::make_shared_container_iterator;
using iterators::make_shared_container_range;

} // namespace boost

#endif

/* shared_container_iterator.hpp
X2Zt+HBtcgDey2pYHGlQ4ryV2pKBB/D1noJzKoPJ2sZbtSzSZ3zHO405OEs/jhw9G2fjtGLKYm2pgzP/1YDIy66ivIynVBsA4HyKvCzPqzLu0tJ+GCGkgDbSGqFvMmnjKIwohRMojIj6NkaoY6YxSuC2pFXmeLlovw1R2+CAiNruNZMufZehYtA5+JmqJwIa9c/X/y6fw9kX9J4ha5ZtfS+n+E4K+ycahclnC22t4m5i0dmlsRxBaVQsKz54vi70EguJncZGyhWiLpFb6glqFvKN7iL+HIn/dgPuEL7E4q+8U87S+hG15FIN4/qF8hf5/kK/h38s/AHRedMPxfTrgwRks/IeRodCm+cEGsepDZMFpx/Wt0hF2Rt+3kWh5lKw73rGC2d4fxezhPU1v/9ON5t2FS6/aRxq2iauQqZ6/1pnk+ZxJs6/U5AuSxzoOXcrbpGENH4v5TTJg5qb1H2hiiexYi2t3oaWf0SK1kF4WGWRXUVlDzPb2yo9nliNer8PDhe0759my0fK1leRj9zfZjf+gv/IJYYpvECetidNB7YZS+X16Df0w0IF+zKnMqTed1rxLvY/6TILamymNmJiU3CgqMAfI0UZQJEWry+cTvLoG7WM+ypmEUIq2Jgs5nDGtEov1z+afFdRkxfWUvWyUS7RvRxJTZdqVSmBH6nrNvSPRsar+oDsHSis1Qb7nd3kBC8fgDJivPaR5nIGowFi4odFJpLPzfpLijr4BzFnM5F/3HKZG3BJc0eDZizo3+jUrBm+popM/Hr7kEkVxn6dmjVP7lLY4KuwGuKyKU4L+EHsm+CjAK5tnajEqF4x2NuJi2xBnEuVxR0aN4snYadgHXUH5ry8RcEv3tl1VLN5+N6w4JckfD9jDr7HqRmDCFFCKuZIZEM0J27FE8xd4jh0ZEb/PTUkr3muTwT9tyu/w5AI+m9XvgKxqa4//WfQ0Z8+MSNcf7onnRXC4z/r0mo2ixr95Qir5vEngkE7GpvPuY+lzRA5GyskZzn3sVszju4+5sS/NT0cDv9Vo+zx2BFRRdpUX63IsaVN+V/qQC5/76lR5K5bnT3W0ui13r9QCHsLZfV0VIMfn4V1dweHg+H90ZrP2P0dna/7W897yP7GV+vvAhOr4J+F1frbxu7vFbOc/nb+DfpbbSmfmCIdN4u4C+66RtfqrbpiwnBjJcHPfJspJ8DpeE/CSoTZ9oXYVBykl4cpvdo8/YSI9UY2uJLXMoUrEdbnXe53ZGWZA7Zwkr4FRESS4keMSuJWrZJ4dCWFzLfivpKgokbKSV+6/rg+9votmWzLLlQFlGHu2O6mn8M8NYmM5uafB9ow96sXocO2tmLK6nIh778Bv1a7eOIj9y821L9h4f3DPg91UT3R4/AR3DJDZuvPXOcOP//ESG7f3QQc75g8i0szXe/IznIt9mR6k3WgjeLoWlpX8NcLHY1xF8bnKNFs+PVyd7lGi3yvUoOE/QKotBIHukR3pWUsGV3gBiycYtXJECcU03wdCTgCyrCvtH9+8U3G8H0vqLbwvhDpU3k5EbgWsGqLka0WHyeqb64k7T95dlZ++wLVJH86XdnjcC0q7yV0aYN0xe5I2egRbKQkUtY3A3TAm7N6NaKXTmrxNQYj79RqjxNeI0aWACO7qGuGVx+jrIUk/mfsyKudt8XXuladMog44FR5pnqCC8Rl3ikdJkuMk/OLCxg1o2C6Nzm/vtVQLJM2+JBUXzXqo2lXjyuEORTrz7+bKMLXwIIH0544z0ICpz6T/53BqAatHFuGEaJCup96bL6Dx33xfneAbs5vZdfhWyN+eykT3zz8tnC4phxNRaT7RpWTuawpZehgigaSF501i8Q=
*/