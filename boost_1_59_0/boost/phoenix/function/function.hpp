/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Eric Niebler
    Copyright (c) 2015 John Fletcher

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_FUNCTION_FUNCTION_HPP
#define BOOST_PHOENIX_FUNCTION_FUNCTION_HPP

#include <boost/phoenix/config.hpp>
#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/detail/function_eval.hpp>
#include <boost/utility/result_of.hpp>

namespace boost { namespace phoenix
{
    /////////////////////////////////////////////////////////////////////////////
    // Functions
    /////////////////////////////////////////////////////////////////////////////

    namespace expression
    {
#if defined(BOOST_PHOENIX_NO_VARIADIC_FUNCTION)
        template <typename F, BOOST_PHOENIX_typename_A_void(BOOST_PHOENIX_ACTOR_LIMIT)>
        struct function
            : detail::expression::function_eval<F, BOOST_PHOENIX_A(BOOST_PHOENIX_ACTOR_LIMIT)>
        {};
#else
      // TODO:
#endif
    }

    // functor which returns our lazy function call extension
    template<typename F>
    struct function
    {
        BOOST_CONSTEXPR function()
          : f()
        {}

        BOOST_CONSTEXPR function(F f_)
          : f(f_)
        {}

        template <typename Sig>
        struct result;

#if defined(BOOST_PHOENIX_NO_VARIADIC_FUNCTION)
        typename detail::expression::function_eval<F>::type const
        operator()() const
        {
            return detail::expression::function_eval<F>::make(f);
        }

        // Bring in the rest
        #include <boost/phoenix/function/detail/cpp03/function_operator.hpp>

      // Solves the result problem for F(X)
        template <typename This, typename A0>
        struct result<This(A0)>
          : detail::expression::function_eval<F,
            typename boost::remove_reference<A0>::type>
        {};
      // Solves the result problem for F(X,Y)
        template <typename This, typename A0, typename A1>
        struct result<This(A0,A1)>
          : detail::expression::function_eval<F,
            typename boost::remove_reference<A0>::type,
            typename boost::remove_reference<A1>::type>
        {};
      // Solves the result problem for F(X,Y,Z)
        template <typename This, typename A0, typename A1, typename A2>
        struct result<This(A0,A1,A2)>
          : detail::expression::function_eval<F,
            typename boost::remove_reference<A0>::type,
            typename boost::remove_reference<A1>::type,
            typename boost::remove_reference<A2>::type>
        {};

      // Solves the result problem for F(W,X,Y,Z)
      template <typename This, typename A0, typename A1,
                               typename A2, typename A3>
      struct result<This(A0,A1,A2,A3)>
          : detail::expression::function_eval<F,
            typename boost::remove_reference<A0>::type,
            typename boost::remove_reference<A1>::type,
            typename boost::remove_reference<A2>::type,
            typename boost::remove_reference<A3>::type>
         {};

      // Solves the result problem for F(V,W,X,Y,Z)
      template <typename This, typename A0, typename A1,
                typename A2, typename A3,typename A4>
      struct result<This(A0,A1,A2,A3,A4)>
          : detail::expression::function_eval<F,
            typename boost::remove_reference<A0>::type,
            typename boost::remove_reference<A1>::type,
            typename boost::remove_reference<A2>::type,
            typename boost::remove_reference<A3>::type,
            typename boost::remove_reference<A4>::type>
       {};

      // Solves the result problem for F(U,V,W,X,Y,Z)
      template <typename This, typename A0, typename A1,
                typename A2, typename A3,typename A4,
                typename A5>
      struct result<This(A0,A1,A2,A3,A4,A5)>
          : detail::expression::function_eval<F,
            typename boost::remove_reference<A0>::type,
            typename boost::remove_reference<A1>::type,
            typename boost::remove_reference<A2>::type,
            typename boost::remove_reference<A3>::type,
            typename boost::remove_reference<A4>::type,
            typename boost::remove_reference<A5>::type>
       {};

      // Solves the result problem for F(T,U,V,W,X,Y,Z)
      template <typename This, typename A0, typename A1,
                typename A2, typename A3,typename A4,
                typename A5, typename A6>
      struct result<This(A0,A1,A2,A3,A4,A5,A6)>
          : detail::expression::function_eval<F,
            typename boost::remove_reference<A0>::type,
            typename boost::remove_reference<A1>::type,
            typename boost::remove_reference<A2>::type,
            typename boost::remove_reference<A3>::type,
            typename boost::remove_reference<A4>::type,
            typename boost::remove_reference<A5>::type,
            typename boost::remove_reference<A6>::type>
       {};
#else
      // TODO:
#endif

        F f;
    };
}

    template<typename F>
    struct result_of<phoenix::function<F>()>
      : phoenix::detail::expression::function_eval<F>
    {};

}

#endif


/* function.hpp
x4zqSgWHwAeflZ867X6zG04/aseEe077LkKIm2WKKnO5eRrsjZUaA40Ung5MZdJ2eF/LJtK2hPnz9VmyS7igGSRIjT9tQv0o4bWbYiIi28mCiBJ3ZRZtZfjy/2tDrGiQ/yyjWfg3dLCxvF1GEwlBAop1/5Xu9/f/fYJvEuhErED+eqnCIBnfSafCkUSMgkV8fR3NTvmdJDwimh5DIRT5HZdcqEdzKdeB9nF4BmlRU3qzpCrXZ61/lATEGISozHF9yioM5IRWERFZ5sTSPSu5UveJHZvOkICWpXye7MmpTUCHQGPHFqjFV6BnRoRl2fLX1uH7Y1IyHFGWZTGXJ8tOC/w6prPUNvM+ycLEJKkFQUXx0bU6f42wrD2uVdere/Sm7vCUEa1bd0j7TPm15zoPno+UsHTh086Wy/qVuLTrz9DyefOC1NW8ds8p9QGHb03zgRG9ITOAniGJ/CFOmRY68LAebAMQvvWquFQvuG8MUHhC/rVTUe6rPrBXs13Xj/Lq7Vcu4PAE/ulaHH1GN7rlfvdN6Q1XeifCcccJUhKJVbDxd+v+MmhEfNqpzetnsqdmcRxCi/4ITMePOgzP9c18XHlY1srtJGS0x3qtggYNcrqVveTdPXl6ogfHLL6fxlpddY5H9+VIKV5blxZax70FiR96xvnbgaA2h9kvCu+2HygKzPYeLuonO3a4ysr5ALN+HWVoc3P4hpT9EU2P5DjOkQ+bajapsNjsO/jMO/DMRbdt42yjU+K9nUC3vdQh+IuH70VTW3RO08J0dYMPrQ9vYDuq5Jd/cxDDpK3ZzJYvMkiGVOVC3X5HdULd2ULCvSU16IKboYau5kmkvyie/+p2fV/M6IgwdKY5kgo4wxvLMfJuXEwUcLzwbXyzyFwtxrIZhuQopymfxWvRD7MNMk3IeI3InV1NXnL7dyEqbc+VSEqpY2k2Iq90tov6O0kI2IVzc3/m4OzW07LVLFxisaRAXDZh+2e93lHrxKlmEcH4aShUv1iHxxHFU+MQEnC80723RG/uGY80FSm6hbcsOv1eKjDuTEY6+Xb7gG8dbWQTLRzorCrUzp3N2wO/h6AIcn70YKrFu8D39C57ZbRooPPLMuVbMoOUmIaE/FjihujInF1ClIbyqknzl1Zm20engtAn9m6h2CPhUIksTcGPkfYBeM68rSybu2UvoNudJ5/eTUjXPtrRw+1xI/kJ/p7XS+3EmeH02SlW/lfrQjT1hFtUGd1JTZH9DtKjHNma1NM7Y3IyOqeepa1dK+aEB7OUC1rR7eqOohj3KPIl+rMjD7Vc+0HykcJoK8UlGyIWtaz699kQD8rv9hdZXiibHyTHRDbcUyXI9fp63Toqo9Ttww8oYiBWTnFU0x83lxj0slRpErA6cafhnSJabCFyIpx+64hl1YvvjwEgFwTQrPwlR76P5JscuEMpE1b969os4U0KobBmMUcphtaxfRYxmXJROV/AnR25iP2bwek8VKKj6egTEIvcxyhUHzL9nSFIPL1wMJXa6LtI9hU6WQ9TghKSzP6E9XcxHOvIty2X0dBZQ/1PpugTHHjh3hBt5ara6NjAkDB7OrOwFe9Mi50CV4aGQ0FmGihudXR39ILS9AAMCAgfMhN8P9ugWF/QintSDoiunlVZ1jfAcXToCat+jK+/XgYmv07xaHmd6i0D7t+kFTp+87Z1lZtuk/l5tVtYfzFrpuXzIHze6Udzb9KO+EXvsrd7uGen/8FzF5GYZdIzAWCXq/7c95U/shmTL1etWtKHk0NJRsghJhYVW7eMM2B+tOAHOg8eHcmCvAGA8V1lxx9JTocPItb+dvPvoz32Y2JqcQ9CCSzGb6wIdkyoJ5DF3008Dzx5JY9frDZbV7lAqP51dP2xCH668/ATo5X87clagUc72J+6ssm6P8Y3ragcTbs0DFmKsxT888F9hWFszeBX63finpRd0U+SLa62LzMzM6OEt0VQtrf3BpvThENaJdBYYp0Uy/rgjj+00y/jIDZcpiHzktaECERuIdzcm3Iod36upQRh4u971oTkaXXotwiFymdM2xJPomH6nWyHkP53J+sR1spZv1cLrzTERXYYCGsr71kn06bVs+IipuBJM0s9ibiZdjrgSX3gSS+UjWWbZK6RT9YHKZKhUaqvFxQZVTddQGmOHqZEhvxcP3RCW+0aZBVJBXERdzLmzeLVwlYswmjZXSVlSUwaqxqePbW5oMQCg5hsIjyebmHEXdLBAdV4XTknuTdq+hm4nhl1SPFDSLe6pf1hadjKKiphNFSZfdNBHOfsKtHsYwa8UtbIkyrASOhdU3JWOg6omutbKZWHxVAZkn6yCfZ125r52CGehTWAj5nk4ts819vkF1kKZtcqj+3gWtHNnB9v9M26qRY/L6gYu+qALdhqpVGMTrsjiMDRJjcS2Us0re56bhIW/Z+vxFyc5dbTn6JlVutcCws2aE9Wa51/Z/utZfEVKyko4lJI2m3vEXym5fPBdo7961zkMS+gKbMsd8AajUclbv7+dbMrwAu03Dddv5pLDSxn89Ul5/ClsBepoL6v3hDvWDX7o6Ex0pJpQLYOrC9Vmxv4+HL5IcbqR8tTPFDIuk4tJyDd0rfRu7oLbJZilkDcmGIJb3yluDPlaxr2TaahEGbq9/3IzOvv+/GYqWX7SZ7c2aNUg+LdWYYDyX0tYOHuGMPI5BkCkjZZ47zZO5WzhZY9g2QUR7f3oioh/djMasmiVS0j2o9HF5VdQ7y5VxiYmcm82JgTbiRgLAsawkOGHTpCXEaLt4Q2jDvlI4C3MKnLydyFLMqQfpfPqXnPmJAUt6Wq/fFC0fB8oL9KLaxpcUv9dcH+PCTppfu7QMHD+m2dZgQZi2ZkZjnwm95WHPJZmIh5/5qnxR9rBrV4zW/ZsRP03OwUNnXjydCN9X3i+pIS+cSF3V7QMsj/uqqxZOuWcPHrwCxYjNf1mVT/rz0H8356b2Ckdb2lI2pntg7m4g+TZN1mMssqwN3omcOE546WAm5QewtK4uL5t8k4Sv2WM3qndV8MYZAMtr+Q0s8rcykn6H7r4K1wCICyOeRZPjVI002qcPlV9K/m5lfa/yYl5yaYn3WOmjfNud79YvsVxlbMZDjoj3BU+YWYRDYegy3uN0YYMts7+ndhCfwYlgqfPxMTu/cjhoXhFX36i7vAXRPcvbrUvVnrUxP4VNC1tBYMeWVlZd6JQCkx2VyCOV6QvATfgPLyUoO2Ml2PUEy+h9hKlduWWP6rmAy8571YH6uXf/JBm2xAJudzOc8KRX6CWHlMlVH1spW7cwp8w2q9RChmFVUVeD6RDkagjpYQFxfVNwBfOru4LGrf7lVMd2BnJMk6ufBrSyv+8V9KueGLWPMevr8pUng2TosiH36zBvVBPsC/mZrx5O9RvSHtvNY9w4xP4aXALEypp8IcSOGlwVxL4aXFPEvhpcN8TfFDiMVL9pOd1omomZq1jDhTkUa38Gj8S15VfDyHXyCiGt8gPiiAk2SmFTZIoGwcOkilDAsdZFKmjhhUUO6MGNRUlowc1FPujBz0hdbm9bSYAO9wrst1ZYOedA0TTtpaZsIGr78vprL0ZW2/laGJMWaYYdks3dtqFy02AH6nlTJc8lzA2fj34Dl7DTDKZrV9H+4SleR1zpqfRDl0lCjfwTGNLjH+WPenrStcXmTogT6aofq1sg54+Pj4iEzjpH4HPvDsQmwWNrkDU15q3k7HnT0t67+bClzT9/mcZ6SfQ/Fu+uB5yQcNDftlcirtqS74QpxiTFqkOMc0uuxllG7FdcHm973RAriDWN4916Gnqe35zyvwWVdJaeTVqqjddLRR66LljT8q17+vPUZNW6vrAEhh0dbqfIDzY4062DEEBHA820mwkSo/nrrQ79CfzyWSbOutIXAz9435wTMiKXY4wpUUF/3vtx3GFhP4UHjwbV9ixKDiy/rkPqF+1pd3kOOgW2ZKqXaTJ4F9aZOTMey3dYlgK9SeRPDXVA2SCamOux9U7ZvVLsdRLFLls2lfbwuk1Np99u/Xn0BNMyJhFkQsot/pBO0QRI4fs/pHPxKxCSjnNJzjWpWpuYwuZ/WNNlgpJlIf2jkvrPX3d+Z2DY84SoLW/5nRTOJ0VNzwJU59Hxkb0RJ+NY/hFW9aMKZ7ZcARo30XUf890oHuw+hrQUCiu9hJ6OiivqZoAtf1Ud5hu4rhKsfbhJEK2nhmrot0QpltJ1e6j6qBpYPsx4d0vUtEdPTX7xthYrv8xoTEj7oADcf8nkXDLeMkbg4H6/01P6/Ks9yzmYpaVhofDSpXbpe9WbISK96vKzDfXehe3Sz+ULYZ1S85TbGIoManmunpXy95/+Sfi2FiZQvEUuJlA17S+S7Hw3TnQPDZ2scKATGPu6sXGJ4EpZN0UNZkIRXvtwcLOmzftAdPq+H6B3ylEZe4275EXJY4z0Alo9IHevQzbhVPI0erIX86xxUwwU3bNvDjEalumAxr/gRMTEpKeGluzuqFuqd74KeJxCEe/6u2mdlLG0XuNY31EHAe9ENmKU3m59S/4ULHyvLSGhnWq6bLAIwNMH5Imkz5d5nKUyD7Y3HJxCbGWXaZNcOtbQih3H4Ac4He3ZEhuq3gWRsBk2LvodBmfXAXnRPedbSJUZg5pFlLOWblzcm1BIPEW1Lc8iFZH0PGfRsWOQ3FN/tHJf0peWqijx9JiWmnonRGPIrYXonYRmWQjqbzIuIVWH+2XhEbc4ghL/EURHKQxe2MD926XXhgKqsA5R/AVfRt7iSV47W9NTdnWjoGaC0crnLeC1y/a2rDgJeAN76gzcgnsPfV8Y48DeIAACz/01mUC4w2QENTU/PB51vBzJPz2t9SI4atjb/x2koWEuQG96f2q6WpDaHVPxpqvvC0R8eGVn/Qay8K9HJVwi+2nS8KNmpvOF1o1As0HR9cjnE5rw4wakLnbThTx7QKD0V2CmgcYqlOi20IrWkqpQiE0SKf6//Krw85DPeT25QQohskvBHbsP5Z8/cH9uGdk3P1FBilOtU52TXkOQep5FpRk5L0TWF+8XvSHeKU2W+xs8cC1xd3eb1kEV3L8z7eW002/v1K3VIeA+8wLYQJfZh2RAkTi3d91MGYdSluVJgTKfU0mEfac3uePaxcuPBznxsN5lm6A74IvbtyavsPURRM0IEQMSQc+qHbdKMbH8R2weqeECSjz7XL8xBw/4Ms8QvUkO7jcZwC4Y4o5lpM6j4wckFliyzcciTugioQUDkSC42XIdsVNVXVB6K5M21Nn75bxE8kuqYmPGJwZzCre8yLBAfRfXGoB+tN56flyWRziOX7vvfglDD4FfASm+Qf3EDZ7+5wClaiThwc+CVEXFjezlCtV1M0FTAUbDESexe6ulfi0uWWOJSYWq+eO+J6+fQX7F5mL9Uy6SxebSCOJ6fLGVbfJF0vNU/n4/QmIuvqfe3ZfXJtfNIqSuxMroWZGgrzxSoSe8Mag5QLOopT/GEBTUetkKQwqZwlET2jNCLS3mxrUovQAYKT8kTkaIL8dnbySGC1abTrN9dTTP3UDPQq3LworpUR85EdpCtuABJg5J25syxJREEXshHPfF+lKpAe+oiFUeWHORZYzJD+1/qxm21ULSYqfKyDgUkM10PZ0aZ0eGAnASVGRS0069kePzcb53olmp5VABXXNuVyUu3bnpi9264W5VLhQ9uK2+GyLJt4AXJ54pHcZJ/kY1AgoQ8NR1gJjHGzUZ27HSk7kozhuR9ntF0fzVZD2fv0IUyy1e+QLY04P4xjCNWtYp/afhGJrcsNt9aUJT+glNzFuAubZIm7tybOozW4EfsPj957rxOpGI4QDPZ0Tfqqe4r9xZ5vv09dLUAbIAbwbc/7ezKZgbHord4VnlcqlYJXPOrgFz3R55uQnX7fkOgzmRciB9B6VIdQyw7tyRo65HT7ek9JXPsXVc02kIKSonlPRovxTMun4IJ/xX9S6wli3buzLV7IujrxdU5UBK+Al59SymEfQ4eINWlIkm/5d2BPt08XF0sI9SjRAFruAy6laK+Py7Z4AfmZXVfC2/WwMP9+/7wpjww3o33pkOmv5Ra4GnMw/bCalHbvOb3rDwOS75Xvdm8NqiI/0ElDjJmYS1YdMl7HSaSlVbsy7lr2b7PpAKLecf5A2o12lY0ekXcM4pwLI2uPnrESIkw77ITdjEtWRS/K5AkRQ8pZCRFTx8LerasFdBa8hNwf/R/8aj+rWpfR7zASmjLuiAZM09b5SFmwESYyWGTZfd9YE/4JCqtwWDqiUX7fL8XcSVQjGxRaRTr1AxqpoBwkHPFRMnxRVRJpUeXw4UHV5gmqogH4EfXjLDPF7dNftB0ptEfOZPxCenckQvg4RCGMvgJw7ojAC2RRbIezi7q+3aMvRx0R0aQsGTbIqtwZNiiiLJoYUeGXZI+SQjlI0yr0T0mOOjJi7rsD/iWTBR8hafwifUGf3WzSoKsy+dZvtGtUQk16dzTCTHp3LEIeBncSwsKU6dj+5RhzzGtCQhnByqLHoPkHy+ot9SBGQ/lc8GCksnFJA5p753HArhYz7Zx+uFcoPKrJjDuvH34X0Vrn24Adq5PSShJrldJKFhue0koem5rSSvHRld6e8Poo5GZdkzjLrxP/Iyv9CSqzeniJayuZRnu02ZpagLJX8Nmu2lyAS+SImr5qgEs+SE6/Z51GGM2vD0byMguaRo1UDmlk5kVgDNPrbf9nfoW1hUbV4hIVw1WET0OK0ZCSyyDtwfThg/ORIY+YMOGnjyDrQSW590Fo1RqTOz16/V40c15qE+ynrd/9yczPYjmMgZEFNW9p9OpK9j5BLsKQPwbSc9iLfGUBRcpXNLjZvZpekgB+FCBE45UgnDiNstYMw/qJCr+6dfk8jiKyjUpglCfSRDWy4g486LThm/jRvNHcdzfRDXoUNeacjJ71ZN3pX0Fq/fSJDUL4Vm+67wBr6BPP9bh/snEXxsGS6s4hWHVds9MAgFPpuvlNQqS02/L84U1M2z3C7jgtu73gociirp5csPrb+Y2adP/veNsrjbZX4CWzsw+RLp1Yz4u09xsdlFTNC2T4lqPnFETDiW7Hs2i9McG+LsuWBbxvu2ylf4bIrM2o+lnWM7zn8VVJMBsnSkQRy6BNyzqfIipuJ0Ti+jXoRVfgJkxjsbVSojOCC5ryzJa2P1eOZsAtpkHP9eFbNDpeXJrOo/XjDFkPddbXxir7XiIxm0FyoX5LUStpMRrHjypi1M40jJXnVL0io+2WfqmstxPbFhAs6XtIbKtjcSnmeukVsD/TDxMx+BwT8TeYg3AZv2bG9W3eh/+eU37o116nII2B91zRhIgJZeh6ia+sX0yEup/BZQt1RqBSxJRyK7eZ5vJUiHy4W36IbaIbLaaEtenHPcqIgyCZCPC5r8pnIYQdTsLm2EX6zkOggj5PWRVGZgqv9l80CwkZ2v4APhMF6PeI8k7FcBBTTd8dsUTZ/6zTT4oY+iUUw9G6aZPzzmMuJ2BXkrlAfleGmfvDrgLz9IddRGaX94eyBOX0t7Mx0VdahtQsF9iBspJDkEgpOh+1ZXfrI5Z3nDGFZrs4zC/06tqa7U2ksQLp0/59M9Qzt6rro8A6FhMF4/J7of7p/2Lr
*/