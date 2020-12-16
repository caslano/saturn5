/*=============================================================================
    Copyright (c) 2006-2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_FUNCTIONAL_ADAPTER_FUSED_FUNCTION_OBJECT_HPP_INCLUDED)
#define BOOST_FUSION_FUNCTIONAL_ADAPTER_FUSED_FUNCTION_OBJECT_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/config.hpp>

#include <boost/fusion/functional/adapter/detail/access.hpp>
#include <boost/fusion/functional/invocation/invoke_function_object.hpp>

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning (disable: 4512) // assignment operator could not be generated.
#endif

namespace boost { namespace fusion
{
    template <class Function> class fused_function_object;

    //----- ---- --- -- - -  -   -

    template <class Function>
    class fused_function_object
    {
        Function fnc_transformed;

        typedef typename detail::qf_c<Function>::type & func_const_fwd_t;
        typedef typename detail::qf<Function>::type & func_fwd_t;

    public:

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline explicit fused_function_object(func_const_fwd_t f = Function())
            : fnc_transformed(f)
        { }

        template <class Seq> 
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename result_of::invoke_function_object<func_const_fwd_t,
            Seq const>::type operator()(Seq const & s) const
        {
          return fusion::invoke_function_object<
              func_const_fwd_t >(this->fnc_transformed,s);
        }

        template <class Seq> 
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename result_of::invoke_function_object<func_fwd_t,
            Seq const>::type 
        operator()(Seq const & s) 
        {
          return fusion::invoke_function_object<
              func_fwd_t >(this->fnc_transformed,s);
        }

        template <class Seq> 
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename result_of::invoke_function_object<func_const_fwd_t,
            Seq>::type
        operator()(Seq & s) const
        {
          return fusion::invoke_function_object<
              func_const_fwd_t >(this->fnc_transformed,s);
        }

        template <class Seq> 
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename result_of::invoke_function_object<func_fwd_t,Seq>::type
        operator()(Seq & s) 
        {
          return fusion::invoke_function_object<
              func_fwd_t >(this->fnc_transformed,s);
        }

        template <typename Sig>
        struct result;

        template <class Self, class Seq>
        struct result< Self const (Seq) >
            : result_of::invoke_function_object<func_const_fwd_t, 
                typename boost::remove_reference<Seq>::type >
        { };

        template <class Self, class Seq>
        struct result< Self(Seq) >
            : result_of::invoke_function_object<func_fwd_t,
                typename boost::remove_reference<Seq>::type >
        { };
    };

}}

#if defined (BOOST_MSVC)
#  pragma warning(pop)
#endif

#endif


/* fused_function_object.hpp
PbE9NsbB6IVDsQnORG98Fn1wIzbFl7AZHsXmmIN++DG2RLYh/YClXUjaifz5u3IvcRmVaaXS3xjXoQ9uwPa4EcdjJr6Im/AHfB6DbPqd78YX8ABuw9dxB7oTx06ciLswHXfjbNyLC3EfLsP9eBMPSD/yl3EIvoJGfA1j8HWMxyzMwTfQU+k/is3wCLbDd3ENHsXjeAxP4gcYqvQPxYP4Gb6Ln+NlPI1NqKdfoA9+iT3xawzGb3A5nsOP8Fs8jRfwPF7EIOnn3R8vYSpexsV4BXfjD3gKiyj9nLEo3sFiGFiK+o890AnjsQSOwVJ4EEvjYXTGFtSnMpiJ5bAq2788pqMLzsUKeBsrYcw/qO+YjFVxIlbDp7E6PoM1cDPWxGx0xavohjexFv6OtdFZuddHd3wUu2NdnIgemI6P4wKsj8uxAW7AhrgNPfEdbIzn0Qurl6X+ozt6Yz30QV9sigHYDJOwOWZiC9yGLfGaen6Sti5pA6P+q++6riEw0W9V+tNhVyyBIVgSh2IpXISlcSM642b8B36BZfAHLIvXsRzWL0L5Y0t0wdZYAU1YESdjJZyHlXEhVsHcMRyl7UvaxPxtvmufJvvrVPTBp3EKpuMcnI6/4wzsV4R14GGcha7K9QvWwTmoXr/ghzgP2SaGZ3AKLsBr6nW3tGNJ+5Y/obZBOT5LG7RcP36OjfArbIpnsDV+jR3xG+yJZ3EgnkMjnsdkvIAT8CIuwu9xOV7ClXgZj+OP+A1exfP4E3qRlmvYDq9jJ7yBc/FnXIO/4LP4K17Am3gLb+Ft/A07kLfbGIR3cBj+jrF4F0fjv/Ga3LdJm5YhTN4PUu5Ve6AyfSNj/J1FLzyPfngB0/AiTscr+C7+gGXkPa3KeBV74zVcidexaFHyhSXxJvbBW/gy/oZv4m18B7m2Va9viuJ4LIbTsDjOxFJ4HEtjq+Ls9xiAj+AkrIGrsCYqYx+7Yh90wwFYCxOwNh5Gd3RS7u2xCtbDevgYtsL62BMbYAg2xBvoiT4l2e+xDXrhKfTGuqW4N8P62Ax7YAsMwyfwGPrhcWyFX2I7vIP+uILjYUfcgJ0wCzvjEGe2FQ7DQIzA/rgUB+IaDMGvcBB+jYPRg+NdJM7DKFyO0XgAh+NhHIGfYwxewAS8gaOxKPUkEctjErpiMjbAFPTBsbLfUQelPY2ylev0rgY1H+rUW+pXEPpgHxyIYZiCRlyE4bgco3ETDscrOAKLyZizvXAU9sN4nIcJ+Caa8ASOxrLyHmh3TMZNmIJbMRX34Fh8CcfjzzgBe8t7oANxEg7BqRiJ0zAG0/F5nI5F5H3P0jgTy+FsrIpzsCbOw0H4DL6Ii/AzXIJf41Ks7sR9FbbBlTgIV+EeXI2f4lo8g+uwGvXxWWyNGzEEM3EbbsLduBnfwy34EW7FhtTXbRiM2zEDd6DSfvMSdsYD2ANfxhX4Cq7C1/A7PIy9qJ/v4CDMxgl4BGfhu/hPPIpb8Tjuww/xLfwIj+PH+CWexEv4CV7Hz1B9b7mYtLlJW5xSr8L5s6vc/9WS+7862AkfxXD0wBish0n4OM7A+rgSG+A2bIQvYWN8H73wMjbBG+iNv6MPliMRvlgJm2FDbI4B2AKD8AkchH44EltiArbGGdgGM7EtbsMncS+2w8Poj9nYAb/Cjvg7dpL7yc5YDrtgbeyKdbAbNsFAbIvdsQP2wK7YE3tjLxyMvTERg3AJ9sE12Bc3YT/ch8H4Cg7AEzgQb2AI3sFB6MS2eAqr4mCsiUPRF4dhMIbiEAzDKDTiGAzHCRiJizAK/4XR+CoOx7dxBJ7EGDyFo/AMxuIPGId3MB6V/TEBy6AJa+Bo7IRJOAKTcRym4AQ=
*/