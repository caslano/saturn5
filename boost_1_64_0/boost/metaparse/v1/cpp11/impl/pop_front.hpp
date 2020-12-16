#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_POP_FRONT_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_POP_FRONT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S>
        struct pop_front;

        template <char C, char... Cs>
        struct pop_front<string<C, Cs...>> : string<Cs...> {};
      }
    }
  }
}

#endif


/* pop_front.hpp
wFmxS6qEPberTfRwEs7D3XR5nZWdiulxteaHx9h8KE7vz+YbI2HyN3Di0kh4iK/Gw1HhE1r67MHsePAGOGU8y2qply5Xg+GQLew0Qj01qo/aKrC3a29opk9C773VQi/HNbK3D3KSLd8xlppsAq8aXE6b3sB3OLK2sX5g3K3l0rVw4bFjYGyF+JJrg8V3qn9flaCueVRu63k9X0Xf5ZTz0Bm3sfEby+TGa66Zpk/1IA5i+4cfcw4x9+wI9VsTurOgmkGfbdJYGFeNfsSdmRvgv+y+j0sKdLH+h4NLqOVmrITjq+gO60919Xx/qGacQS4tMMZ0sc0oRdngtHlcaV3irZX6kffoyY7l9264vSsN8Du1Pv2+j93e+Jw2+cq5e0bCc23gY89YuPe9aNhe1ryK6iPhrSF55GeOEFrBwY0wfIp4nplHPU6Dtb/GXGHEnDHWeNgztzjsQzO9JGar88mPfDjR+mClCWpPHPUOfKqEy9vLyavlVa1dOPigex3a0St98Jnr5xwAHz+Fw1siGWuRlduKHRj2rPkv/hkP4vFDn8kF8TpWz+orWLRGvi+Fs93ozCb6J2Ubyv1iYgSX91gJP/PBWJhaLjMs16d9oCGd8ZOS53J4rK5pJN4XLoPtacbTjC+nq63KiC/+60gPd2O7YsvhWT1rDQl6feXFzSVyL4d1G2M9LR9LTrOeg3e+hf+D1D63v8Z37HinWup9/jmRBD9usz6Eg+s21LODYS+pBa7cRlPdqWZ5Wn5G8A37ZB+jZywGyrwk3+nmpnx2mr7YakzTDqkP8jgO3x4sEcuoId5w7Slyo9NgMXEcZtCkDQrLh9I+uzcaclujaVpEnn8OB7K59mj885o6+km1G7v/8BBsUp9kogeOis+UF/DpaVwxwTXeE0fTxb4a9eHFcrAbe+yj7Xby973ytxZ8FvNxu9+sjvhdolzGkV1qwUCYniqXOsC46uqSS9r5uVm/dpKYoHNjX5pHEXXM1PjzkPzdOJr0lC+NYN92Nb08LqOO/r4gX/3GeFrBjgQa6mM8fqM5X6XP09b5N6rbntFjf0RdfT+/tBQf49T3Nfmf7VZaj2ksj1pNtS7Bjlvq6k0O1JNYDMeywF9x3VK/oiE+79OctlF3j75d/dQOXsuBxCzGfExcP6LHaOzfyqn+bDhmNKy9Et/nFYt18MlSuCsPKo8Xb6X0PdSmMb7dUQk/wMCU3rgPl+QeiDPkQ7yvs11dO1JsNx2vT3SJGrCsXspW12P7y7vqA/6OlvwD/TJAP1udmbOba/NluZJyrp7ev95E7VOObUQbiKXbzKdGkrFt0KPUPyv8kL60/LmlkXWtl/Bpe33wcfoi6oNOFWDtSrgMU5Pzs53jO+S2V+BxuH69WDlKQ/Fxzz248Xe+tyPeb9YLYfOC4v8beVM9Bx935Rt6drgYeHWNnsBSdhEH8Wf0vc3fv6GDR5eB77Ttt/Rp5hq45p1I+CPMT1enp8iTzhvhrfWdWx5lz4fE/Gl+onVLLoSlSfqnaTA3u1rrmHxK4B+9l6+vYrub1NL6qX3Oss/NbA9XOwyLryd4x6W1nJFit7wYfkT+zVB71FmhJsIBJ2ne2zbxDbyqXQzP6+E/9aqe7GxcJ6/TOvL3Utem6cr6fre+5ptg7QFW35lijvw4+S0+YNdwjvby3dN05mBjSemuR++Y+fR5B9w+e74crEDDDaIZ5PQhazItRtObNeXUKjhwl/VtNX0j2FQItheN4E018HdwdH0VvYdm1hXgRbCO26oVnQFbxuPu7dZqzj6r56NX+fSb+l16TZ1341CYtSQ3rZQAU7bheTHRNxM9jzOS28C2Wnqvjn9RzHf39zbDcccd8Co=
*/