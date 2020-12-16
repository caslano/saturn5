#ifndef BOOST_METAPARSE_V1_TRANSFORM_HPP
#define BOOST_METAPARSE_V1_TRANSFORM_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/unless_error.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class T>
      struct transform
      {
      private:
        template <class S, class Pos>
        struct no_error :
          accept<
            typename T::template apply<
              typename get_result<typename P::template apply<S, Pos> >::type
            >::type,
            get_remaining<typename P::template apply<S, Pos> >,
            get_position<typename P::template apply<S, Pos> >
          >
        {};
      public:
        typedef transform type;
        
        template <class S, class Pos>
        struct apply :
          unless_error<typename P::template apply<S, Pos>, no_error<S, Pos> >
        {};
      };
    }
  }
}

#endif


/* transform.hpp
hNMV7ixotw+VjTu0Ph632teqCucA/UOiXLV717O73+vyEacT7Dk2QRePyrlVWb87rzM41BnqIUrlX3/lxQ9jnMFe5BmOvujuGezNntn4A5WR+qb7rK9crezNziGtvjH2Gv2Vsv5Yx8Q/9Oe/x1eY88fVCafj/9F2JfBxFlX8a0lpkKJpSWkpUUMvWizt7mZzUAHbpilNjyQkaWnLseTYtEtzbLObtEVEFLzwAEErl4IICogKilARAVERLxQvROTyQEVQLjkqgm/m+3/73rx8u8m22N9vm29m3rw38+bNmzfXGyOq1r15VsZX+PHJfuD7g5FB8DaG9cGHBW+XTCarXTKLg3Z8QH9z+uejcm0P/Cp09uDxvHO1wrTtO1uirR5b5LfVHWXuu3KPTPCevW2v2oKuIyu4STauvxc8RXsk7W494iD3PuuD8HTRrh+bb2W+I5OsiQd5nsi1A9qKYF6bQLRMu0Dm/8rtQpXurIlL3nCwgJ+2wnnsG2aL3LOpM31dac+tcbjXROT8RP5jTGtNDa2t5Bw/1Z9NWO88GfKCCL+OwXrB5Bn+PB5/caYIZ0vEWDST399x3zVb5I73Jx2ez69bpiv3zon9xFnv8LW5bO/A5gAaAebX84v4Pu/zYt7x70XuuekXUbYXIKMvoa+8LMbN5wSu5wSu/yhcrwLXHuD6L3C9Bjjk4XOqEffs3LiI+blj/XgK2/OzEZfWHsXTCYDbH3C2roJWqaJ1QIR+itabgONAResFResgwL0ZcPJM1MW451rg7UMjcG3trY1Nx9vXeWz75UvMtefkEFpeib9GmPXcd4RnqnC6xA1PLuPw9ehP5YTfs/5d+Iz01AjB2Djq/z2sxw+h+LNtPPYzkP+uXByQAH6awT3O4qYXkRh+iY0z55PEnsg4ckXjibWhcZ0D2eyAnafWwC/e9IjYw7U4HCd3MqLAWeXR89lzDUoWDou4slARce8Fp9X4+zbAm3z6rvhMAZ8uwb3BiDtGLMF7rheKO/mzVZnmgMaXyv0yzRVlmhJR6URjXoTt2yx+4ToOe/6Mz01HHRdE3DpfW+7WoRJytyjihx97i6kTfGUqfkYjAjfqYupcJfsv6jxH9d9qwNYo2DiFawFL9CxsneIR8cbh0eJIvnkldVL/akHCPnxgRUfFBX4IUY7j9PvADU3HNzY1JFoa18gnjsMS+L7LNPEWBO6fv/Q2z3tXZOQ5pCXgw1LQl/c+X8fdx3qkrRqljuS7raN/KG09BIqq6qTc2n5DhOV0RYT17/GqTVZG6KfarxHlXiV0uLHPdL3XRMLrvRb5m5A/fNzs3oLJiK1OLoQ1uhZR/hOC9gvXH11mvVJNdXRkji9tAm+7qN8RFSPrtz5P/U5E/TaI/POnj8y/KU/+k5D/ZOR/DXcF/TOqfK5fzztvLjc252Cmw9bLj9tdbt9/deJaCW9ZwF/o8HUUV068knHfm2vnAbR16ceauGaCq8B8IQO4ZRRXibs9QdxGipvtpQMmZ3I+kCh+nh/fkemPItFPW0hlXSDns4iLeOYsg5cLxzGnCXAOUFydmCs3UvgYzx5eIINxmGhx/BLED3XymYtdFL/cjyfvZNRfUkmyMruSg6B5J6Wv9LrMJaRkT38mZ5OvwT0lvkdpjGHrObNH2vLtHl36Q7SJG6S230Bne8WdJisPJ9N9w+SwlwufBl9xpn8cSh3v1IjoHR56NwQaISPJo+rDdArq0I2Cjxrpv66r074piP3DDkG/ZC91jxxDFpRjLU/0k4fKWRcllS7qidBP6aLN6CtbBI4G8b1CjcFbkf/0iF+GXuTvU3AmXZZ1AHBpHiuYx3sxVgR8HrTl8DMEvvQyDp/Z5GQ=
*/