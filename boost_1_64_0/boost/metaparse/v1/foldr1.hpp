#ifndef BOOST_METAPARSE_V1_FOLDR1_HPP
#define BOOST_METAPARSE_V1_FOLDR1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldr.hpp>

#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class BackwardOp>
      struct foldr1
      {
        typedef foldr1 type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            is_error<typename P::template apply<S, Pos> >,
            P,
            foldr<P, State, BackwardOp>
          >::type::template apply<S, Pos>
        {};
      };
    }
  }
}

#endif


/* foldr1.hpp
ZuOTRfxfIsP4gtp/G99HzD/J4Gr+RcFz/CWe41fwaaL+tgG/SNTf3sQni/rbe/hEUX/LjdfjZwVcjZ8twdX42UO4Gj8LJvD9a2ocH9YJH4FvG7pZH6gzfqjxc/CW+HQ8bvxJPMzNYLyT43Z9oNIZ9F+3aRxf8RJ+fJvw+xTFd/4o7J/Ghxk/9wDOEfZP40cZfwrfKWz/4nsa7zHQ2V/8XN2+z3g85/GCx0v4uKBx/WA1PrZO/X+bMH4GP9lx+/y+hI8U9f/Uebr/IuPxnMcLHi/hM0X5uBq/1HG7fuDv8bMct+sH/gkfZ7yMh7//b/ipxpuHOPGXkzz9x7iMD/d42XP8iid9VafnY6zTx3BZv/ekT3rSp3BVf0vjzaJ8HInvI8rHPH6MmF+8Dt+uTvxumP5lvIPxIt7S/4G3Nx50j872e/wHIn43eaGnfxKX8Vu4XH8al/uD4PL5xOX8BXyeuL6tsvRv4jb+IDxba/xU4yPw8Gxt8JNxE38Q9b/hJ+GN4g/KU+LBYeL5eRUfKp6ff+L7iO9rcqpnfAyX42OhN/q+eNJnPelznvR5fHAtbb34gAreVe1v9pN48BPH7fepPX5mzWJ15sfn8Qki/QL8pLAsqrc+30U6/xlc5T+HLxLxO7PxhYH9vjj7o+K3G1+HB2F8On6Z8fXDo7u1CJ9h/JARTv/xxYzPit+Xx2er64dPddOb9b1S02hfqvoJfqtYP2kZnnfd1u8vIf5CpD8LP1GkL+Mp9f2ZHg8OUesj4QlV/8C3E17C+zrrF1qvetLHLtXnT+HHO277d4fgaREfPRQ/1nG7//Kh+Ajjuzrtv7PwfsZPGebE5+BtnfqPbd+vwr923k+7f+ev8S8dt/t3Po1/7rjdvzOYGQ+2biX2B8fbOm77j/rhf29qvD/4WHyZ43b85HT8buN7Dnf6f2dRvxD18wV4yllfypZfVVzO37vc0//q8YTHk/iF7vltfBxeZ35YFB+Hn+W4jV88H+9j/KujnfENvOC4Hf9ZjS9y3M5/+A1+p+N2/s3z+M1ifto6fL6Yn5a/Ihp/6lKn/bwA72jmB3foG+WvgLczPgIPx6eW4Fs5buMrl+JtHLf1GwLImb8ovr94Cm8Xupl/uCvey/gdeMv66vgOxj/Ew/u3J97N+DFHO+XHHJ6PVo3rh+/ge+JY6PQ/RPl7F9/dcdv/8B6+m+O2/+F9fFfHbf9D8Srd/ih5vOzxiserHg/mao/hcn0zvKNqX3nSZz3p8570RU/6sid91ZM+drXn9+Py9+PX1ym/O9X8JHyu6F8ZjedE/8o4fIboXwmu0e23hMdTHs94POfxAi77Zzxe8XhwrfaEx1P4oDrjZx1rPhzfE982dNO/OQLf3XG7/vkx+G6O2/XPj8V3cd3uH/XzePCgmL85En9AzN8chd8t5m+ejC8R8zdPwReL+ZvJG4gfEtdvEN4TN/0j0frxeHfH7fzhg/Ad8Ubzmw/Gt28t+kfm402N89eMd60TH9IhrJ/gMREfewDesU58yNZh/vCtVHzITYwP1snftmH9AH8bt89fUzi/GX/TePOR0d16Al9jfA4e/vU0/qzxd/CWr/Gtnv49XNYfPZ70HD/lSZ/2eAaX6/96zp/zHD/v8YLHi578lTz5K3uOX/F4Ff9nEDSs/23G33Dcfr++xP/guP1+bcF/J+YfxW6PBwe2avx+7oTvhTcqP7rje+CNyo8eeD+8UfnRE+/bSqzfe2c8WC7Kj434ZXij/G3CZ+CN8vcRPl2s3/AxPk30/wZ3Mf9M9D814QUxf6wVfofjdv7BjnjO+KeHR1ejFz7D+AlHOP2nuKzferyK9xf9b8lFOn3K42lc1l9xWX8=
*/