    ///////////////////////////////////////////////////////////////////////////////
    // template_arity_helper.hpp
    // Overloads of template_arity_helper, used by the template_arity\<\> class template
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    template<
        template<typename P0> class F
      , typename T0
    >
    sized_type<2>::type
    template_arity_helper(F<T0> **, mpl::int_<1> *);
    template<
        template<typename P0 , typename P1> class F
      , typename T0 , typename T1
    >
    sized_type<3>::type
    template_arity_helper(F<T0 , T1> **, mpl::int_<2> *);
    template<
        template<typename P0 , typename P1 , typename P2> class F
      , typename T0 , typename T1 , typename T2
    >
    sized_type<4>::type
    template_arity_helper(F<T0 , T1 , T2> **, mpl::int_<3> *);
    template<
        template<typename P0 , typename P1 , typename P2 , typename P3> class F
      , typename T0 , typename T1 , typename T2 , typename T3
    >
    sized_type<5>::type
    template_arity_helper(F<T0 , T1 , T2 , T3> **, mpl::int_<4> *);
    template<
        template<typename P0 , typename P1 , typename P2 , typename P3 , typename P4> class F
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4
    >
    sized_type<6>::type
    template_arity_helper(F<T0 , T1 , T2 , T3 , T4> **, mpl::int_<5> *);
    template<
        template<typename P0 , typename P1 , typename P2 , typename P3 , typename P4 , typename P5> class F
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5
    >
    sized_type<7>::type
    template_arity_helper(F<T0 , T1 , T2 , T3 , T4 , T5> **, mpl::int_<6> *);
    template<
        template<typename P0 , typename P1 , typename P2 , typename P3 , typename P4 , typename P5 , typename P6> class F
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6
    >
    sized_type<8>::type
    template_arity_helper(F<T0 , T1 , T2 , T3 , T4 , T5 , T6> **, mpl::int_<7> *);
    template<
        template<typename P0 , typename P1 , typename P2 , typename P3 , typename P4 , typename P5 , typename P6 , typename P7> class F
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7
    >
    sized_type<9>::type
    template_arity_helper(F<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7> **, mpl::int_<8> *);
    template<
        template<typename P0 , typename P1 , typename P2 , typename P3 , typename P4 , typename P5 , typename P6 , typename P7 , typename P8> class F
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8
    >
    sized_type<10>::type
    template_arity_helper(F<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8> **, mpl::int_<9> *);
    template<
        template<typename P0 , typename P1 , typename P2 , typename P3 , typename P4 , typename P5 , typename P6 , typename P7 , typename P8 , typename P9> class F
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9
    >
    sized_type<11>::type
    template_arity_helper(F<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9> **, mpl::int_<10> *);

/* template_arity_helper.hpp
2nIPj64uZY9Ehyole93KnCD2SFgVYc77x3H2R8LKyj04rvTmucNshV1c3SeMe4fJc3erm9qNe4fJPTS1a7WGfRDmJexUD5tI9kGYlbAvF4+3Zy+AyVjfb1OdfddsnnGsEwdELmO+wORzvu985wVzHibv57BkRz1lIbCKwgaY/zFZWQzMXNistinTGDOYPNuOLYJ6KkuCOQjLd/01V1k6zEnY6rxaz5TthZWR+/vUZK2yHJjM+VulmjkyX2Ay1psrTSv6tziw4sJutDrE98/P2v7iIuvwHMzmG/eXNS8smWeBMFnviSNL8D0yGFZd9t2h8/PZP2FyD5U75bPPx8Fk3S4/3pszPA0mz8+9/vPDjCdM5vydR4+Z8zkwub9rVrm3GDNtfyO39pvLvpRinGcX3iXwvdUKVknGZcnj8swzmJnM+eUZCYwLrI6woS9ft2IuafebkNmXvS4e5iLs+62l2JOTYTWFDVvXsrWy4zAfYc1KWzVSVgBzFvZDShX2LJMFxrn7fJj1S85bmOwh6auCPLh3WKA89wneRX+XESZrJS/mT74rjoc5y7hsv19SWQpMnlGH1o1acm7CPIWZX8uJYg/RrjnBptQ1zlRYgKyHg99VVeaRany215s3YN8Nh8n8dGyb8oV5DXMU9uNn6wfsnzAZzyVHa/P8UmAyLrEz8mI5O2ANhfX1sj6o7DlM7r1O+5msI9uFxu+RLntfmbFuYTIutbulbVUWBpN51tUkl88ZBZPnvrJ9bcZzPMxR5tKWpAXMT5irsNujIjjfN2vram/Le6/sCEzm7r6OUUnK8mFy79FufsHsWWnGMzypXNfxygJgshfcfXwpW1kQTD6nn3s+8zMC5i3M/1+drvPcYaVlXyrb0Ylx0WxKlbFdOB9gcoZnzp5tULYUJvNl/5RTrswJmJOwiEmDmBOnYTIuJs3K9We9w8rI/Fx6fTnrfZFxDm5oXvkT6wEmY5Y2J2CvMj9t3Zj8W6OUhcKshaVWun2F8YT5yX7dN/EP9kGYv8yz6S8ucgYs0t4jm++zUrYTZiHsyYk1nP1ZMFm33vExfAe7re2h+auRUxkXvN22/a+F/m8+THt6WlkHmKyj6S9vFH0jwGQu1W0TVkNZIkzmfPnqp0J47jD5LI+2fHmubK+2LqSGL99Ns2E2wo55VGEd5WnXvGB4OkLZe5jMF7fL/qbKXJYY1/vBGp96cI7B1Du7N+zFV3MP9hCYmbBNleYMYf/ULP7I1j3MCe2ad4Nu8juuC8xcWHbc+qLvVJiVMKdy792VxWj3O1DoxJwfDCsu7Pfq2SbMQe2aw0d3vMxZDLMUtiWjVGX2ee05HUIMr3ju2jqnPxux7yZr9xv5rUUKc15b1+loK/aedO1+DcOtLJVlaOY7I7MCe4hmc8qMack80+53vnkZ1vsRzWa/XXyHvQdmIaxVv6K/5ZWj2ZQx4/iucVV7ln3dHNeyNrWcsK06raGyQi1mbX1atuF81+7389Elqco+a3tYf3z6S86Opcb58lNFm33KrDR7nz/gsTIDTF7TtUMTnp8jzFrY2/MJRX+jXLNRjsdYY4HaNac2X8keUgtmJWPWdrCnshCYhTyjHYe5vzDNPjSyq6ssAlZcXvPRo87KIrX7NTj8cpeyLjB5fnvO7PVT1kuL2eXDe/k+GK1ZypzVXBejXfNV+R3s17GadbqXcV5ZvBazno/n8Ts1QbMuKx4PVpaoWaH1vqfKkjWr96+u85Slac+S/tKSvTVdW+cV4uKoLANWUtjkHJcxynZqdrF+pb+VHYEZ5B72NButLFuzlzvetFB2VbPjR67nKsvXbOjxgQ+VPdes6bN+FqwjzZ49/qs+awVf5HY=
*/