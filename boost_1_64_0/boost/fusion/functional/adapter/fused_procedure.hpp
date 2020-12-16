/*=============================================================================
    Copyright (c) 2006-2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_FUNCTIONAL_ADAPTER_FUSED_PROCEDURE_HPP_INCLUDED)
#define BOOST_FUSION_FUNCTIONAL_ADAPTER_FUSED_PROCEDURE_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/config.hpp>

#include <boost/fusion/functional/adapter/detail/access.hpp>
#include <boost/fusion/functional/invocation/invoke_procedure.hpp>

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning (disable: 4512) // assignment operator could not be generated.
#endif

namespace boost { namespace fusion
{
    template <typename Function> class fused_procedure;

    //----- ---- --- -- - -  -   -

    template <typename Function>
    class fused_procedure
    {
        Function fnc_transformed;

        typedef typename detail::qf_c<Function>::type & func_const_fwd_t;
        typedef typename detail::qf<Function>::type & func_fwd_t;

    public:

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline explicit fused_procedure(func_const_fwd_t f = Function())
            : fnc_transformed(f)
        { }

        template <class Seq> 
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline void operator()(Seq const & s) const
        {
            fusion::invoke_procedure<
                func_const_fwd_t >(this->fnc_transformed,s);
        }

        template <class Seq> 
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline void operator()(Seq const & s) 
        {
            fusion::invoke_procedure<
                func_fwd_t >(this->fnc_transformed,s);
        }

        template <class Seq> 
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline void operator()(Seq & s) const
        {
            fusion::invoke_procedure<
                func_const_fwd_t >(this->fnc_transformed,s);
        }

        template <class Seq> 
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline void operator()(Seq & s) 
        {
            return fusion::invoke_procedure<
                func_fwd_t >(this->fnc_transformed,s);
        }

        typedef void result_type;
    };
}}

#if defined (BOOST_MSVC)
#  pragma warning(pop)
#endif

#endif


/* fused_procedure.hpp
TMV1OBZ34TjcgxPwJE7EMzgFf8A0JT58Gks6cRzARjgD2+BMbI+zMApn4xicgxNwLq7DebgLn8E9OB9P4gI8jxl4ERfhr7gYlfPWEnTG5VgeV+CpIur7E/d9B+L/5f2HP3Ms3L/0/Yd5vM9C2EU4RrhMcGEsMk9CEMH0jON9B8fkmByTY3JMjskxOSbH5Jjsmf6K/v+mmIfT/39yVYO5z7RJ2qtXYTVciunKuOr1pP8/wzr6smxh+h1Z9+kP4e/uuWM92nyLl3E9842pHDUWpZ+R8m+W/sqemu+javp9m78TpzwXr4nHcJqSh8fz8kAGfMPjC5OH4i5qmiUP5jTbfN/Z8i3eZto+htrvpkrfVG9LnqJYTtPXSb8PS0F9fx5eHyj9vksPr2+Ufl+ngvpGFX6MxsL2RSrsWJv/re+mlpmqzM/O7PPFwWkZvy1u37Z9hstztQvqG1VwXznaNunrIfuz7OculE0V/vwvqfjlSV41rIC1sSI+jlWwOVbFblgNg7A6pmANnIQ1cT664Vqsha9jbfwS3fEu1sFHiP9RdMe66IseOBDrYTg+hrPxcVyK9VGeuck+rezr/N3mmVsj+e5pY6yLXuiJ3tgUfXAg+uIwbIYHsAUexifwe/TDn7A13sI26CRtqOXRH6the6yFHbEedkIf7IxtsQt2xQDsj90wGgMxHrvjDOyB87EnrsBeuAaDcDP2wZ3YF9/B/ngMB+Crjra4v2Vb3Bna2m462tsck2NyTI7JMTmmv/X0V9z/J8Q/+Pf/lPv/pKoG8ztr3kUkA1gNbhO2uLLuKnn3zj179woO7RgcEhqRYBp333dg8+5zT9fMfb/eIPP8zPOiExPitO/NrZc0jJf74xTCC6TBpVq+NEQnRkUVMg1KsWnjc5H2ggUS3xyJb1f++GLiY5ILGZ8yVoE2vjSJrz+hLCGIsI34TNXzxRcflZrbRuF3n/jcJT4ZB0ETX6b0WWmBruiFO/jDmfzxJUUl2ze2w+81zWM5yLfQtOVb0Xo8B+ZFSjrX64zh0MxmDIeKmraSvrQ1yfuglnm531WjHNeTF6Wf4vxHLO/jhuHh3PpGxJZ3v6cxT74PlO993FgZz/gr+abJZ4TdlNFVV70y4kXriFFRkQb7to0/7nRV3wlUCsf83mExtR1MWZWkUae8QjTlpbette8PtpExD2ZLPtIJK5R9p1ZePpT9TT12DE+Ii0ocV4g8UPaacTYCbL4XFKSpA/rpl7Y8WVey5Mdq+8fL9xHlWzP+8t77WbaPK36OL/KHrILyo74WKd8wvE+esnTylG2Zp/4mRydPaeZ3HOO9wbYdM9bqXVBZV7zt945MhnzfKYw36bx7zrz831OStkRJwxg53mi/g2P5zpH2G2b+TtQRyvQ3pU20jmWfCbKkg0iJU/N+a5y67BL+3Y9lXVnI+VHLsiss74A2zcvDLMs8H5BjhHmeL8jxwDyvGch+qd03m8m4AdlSpw8R9irHL4+8OsD+orxLbV2t7ajXynFsaT2rMWm09dy2jtu0Z4dL/c5fP8L091ntMU67H8SZNO2/BbUzPrx23ofVnvt3f9f17/5Oaxu1Xfjg5hLjfrr149a1bgOaTE67cOne7b+zDHI9J9d59a3fnZDv6FfDKVgX07AxTsMe+DT2w3RMxOk4DmfgCpyJa3AWbsXZmINz8Beci7dxHl7DMINc2+F4+WZQaQyW9FwmCRXxCtbAH9AVr2Jj/AmfxGvYG6/jMLyBKVbfMAoh7JJ4Fkg8pbCHxPONxHMW3fAceuG32A6/wyA8j5PxAs7Bi7L+IINcw2F/WX9J7CTrP8nvyuKn6IOfYXM8Lev/ArvjlxLPV3hNLX+5VpM=
*/