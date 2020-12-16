#ifndef BOOST_METAPARSE_V1_SWAP_HPP
#define BOOST_METAPARSE_V1_SWAP_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class F>
      struct swap
      {
        typedef swap type;

        template <class A, class B>
        struct apply : F::template apply<B, A> {};
      };
    }
  }
}

#endif



/* swap.hpp
zAfpePk82lKeubxlRcuSiAmZBbvD/X2ih3tgbhlJ+VFeImpT9yTLaxyb50hR1yiqq83WxBkqvhTZm5qf9sLu+pr0O6jwS/Bn/Ku2bxk35dljL4onWq+afpEx/GWb8uxRFKlfHwPL14E4gIhPuaFOxLwydW4UvovwEavEjkeJ4Fjo7rhId/I7NeI+uPTxTYgLIdrvBNl+iL+AXu4kkRlODhFDPj8/J4Kfz2+Gn5MEP03g5+QYfnoRCwIJ9daFk8nuL31BzA9OioF/0Yzfh9TSmlzt13V1r+X3o6yf42/8xq+U0j6f9ClublIWDLjNPZf2+2YVwVDu7cLZ0R6pkLnS+w2io30Gcni/+2N+foFxH/tyPbVhuzRgzLd3HL/C4xbhx49bZ6LtRor5S4C/o3asCffAunaFnC9PcT42sy41I8jZ1blCptscbruDOxm8SDIjf9yiIso5/r4qxrcWMQ9prdRxW9tixvYn7FvOTfj2reYV8e9Vf9PgLivPj3uxwtV+zeJeAvt8AjGej6oS8UErUY+N9U5lFhSxHzKvjTZ/wxAScYCcTi9v4r09mjN4e3+d7h8dob7nuYmLjfXi8vpMTEKMeJTN4yr6i8jbM4nvCmvD7/vRmcPvC1uq2Mz8SX4Lx5v0RFfP9a4QbZHVP+ByW1wpfMl36e8OM9+6WsxhU4B9F3Opa0zZfrP2vjYsS7oWsbWaTMysJm5rqtuXu0H0Y5fXOQyH5ifAkXsjtq/fIvjrBB0p221IV8NPTqgy39PqhB/FWIb5PdKgj3WJ9cN3sR9GmvHX1w1fF94D37QT/JGMxXJgHcu7qDw+lvp9QicL8+D8GnV8UtSRqgnr2FSt6zxqpzC91STeb3Dpw2s0vNuke0y6y6RTMg19uDqsPh5r0nCqV8EfN/BuA/+DgfcY+JMG3mXgTxn4JMPfMwaeMuWfa9JnUpIU74PtxdmAxv8z2maSGJuq8Df6s1j/xvvWv8PmCEftU+wAOvAfho72H/9qsnFWhtvRv4Xsn6fyf/mkifUOWV5tGh7L6jXKW1yh6b0OvsvxbszJY/T30RZ8k0caMfP5Hs1ySndI3421FPtt/S33nSas44atr3poFtTuCstzaBsG0p0UdZfWQvDZ/xE++3Dvs9v6Ot3pxlae1+hc/gZcjf715A6sw9Pr3U/r8H2zR3BGPX93ncjnvnHW3emku299wGm6dz6UXc9nNINm5vksdyaavgfOa22nrwSeXZnhxxp7R2p0EJ59Hi9+2UDfkRrRzN8SS2qYx9n4lphgHohfNzKvbGubn+OBM8DDYaD1uVqmFc3RRiXW0RmRIJfuSmRT3T2cviPR2yXPVFdtNZDa6E5ziu/6UXuOFHxVb+XYWNE6q91/UaaD0OBNZxZ457X48q6PjGpGH4mRNTpjsi3zR3KDFKuN0/ZMkt8v6OjO4r7waf6OBGhjLlsqaCdKQlozDe2ZoO39B8ag0djbs/tqnyB6Ed5ChxfE45UJW3HnW6ytjBZ8Pe51uu/8thZmTGTk7pJPjO5IlHAM3hZzF7OiOaqL72GMbXZlNn8Pw81nJorvOOPQdvDP5Cv5Lk0lwarNedJPUp4rN960+QTPE10owt2QEuKpqrm495mj9t5ByOV9hJcJsTVEe+8o9HpaibsQ0Ta/jd0Ap/ksorzfCD+AX6wf2Caobs63P1iwvnD8a1ZjBtUbf4dkCuFpH1UMb6OCWioHuQqXSwyXK9nMa1L4QFXOnk1qKJZHE/elkcrF2i98v7XfJtfWW2ArzXG2Egy3lenSVnwfpPbiLsjpfGfbCpVBe89Ee0OvseON1essKjP87q0uY8+VzVZlbB3xZ9F2Z18m2tviJYI5wi4=
*/