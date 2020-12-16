// Copyright Daniel Wallin 2006.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_TEMPLATE_KEYWORD_060203_HPP
#define BOOST_PARAMETER_TEMPLATE_KEYWORD_060203_HPP

namespace boost { namespace parameter { namespace aux {

    struct template_keyword_base
    {
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <type_traits>

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    using is_template_keyword = ::std::is_base_of<
        ::boost::parameter::aux::template_keyword_base
      , typename ::std::remove_const<
            typename ::std::remove_reference<T>::type
        >::type
    >;
}}} // namespace boost::parameter::aux

#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/remove_const.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/remove_reference.hpp>
#else
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_lvalue_reference.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

#if !defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
    template <typename T>
    struct is_template_keyword_aux
      : ::boost::mpl::if_<
            ::boost::is_convertible<
                T*
              , ::boost::parameter::aux::template_keyword_base const*
            >
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        >::type
    {
    };
#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING

    template <typename T>
    struct is_template_keyword
      : ::boost::mpl::if_<
#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)
            // Cannot use is_convertible<> to check if T is derived from
            // template_keyword_base. -- Cromwell D. Enage
            ::boost::is_base_of<
                ::boost::parameter::aux::template_keyword_base
              , typename ::boost::remove_const<
                    typename ::boost::remove_reference<T>::type
                >::type
            >
          , ::boost::mpl::true_
          , ::boost::mpl::false_
#else
            ::boost::is_lvalue_reference<T>
          , ::boost::mpl::false_
          , ::boost::parameter::aux::is_template_keyword_aux<T>
#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING
        >::type
    {
    };
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_CAN_USE_MP11
#endif  // include guard


/* template_keyword.hpp
ZCmyFdmPnEcSYriG5CNLkU3ILuQ44uIB+gbCTYPbDBLWYGQzshu5+yDtHRpKiEeKkGXIRmQncgiJ7UcekTFIObIUWYtsRXYhx5GI/oxdSAaSjyxGViO7kK3IIST9MtoJkonMRO5GtiC7kUPIeSRpAO6QkchcZCOy7SDhwOOIayDpRFoj3ZEcpAJZi2xDDiPnkJBBxIX0QkqQZcgWZA9yGAm5nHwhacgAJAdZjGxAtiL7kGOIazDjK5KBFKGnfFiOLEM2IceQkCtwg/RCMpFyZDMyF/c74SHkPBI/hHQjGcgyZB9yDDmNhAwlDKQLUo4sRTYje5DDSEAm15EMpAg5dJDw4UZkG3IecV2J/pB0JAspR9Yi25BDyAkkZBjhIL2QEqQCWYtsQp5F9iMnEdtV1EUkCUlHRiKlSAWyAtmEbEcOISeRiCzyhgxGxiDHFpI+uAHZiRxHAq4mbiQDKUGWIZuRbchu5BhiG065IKlIJlKKFFF3F8O1yDbkEHIeCRlBGSMZyEikFFmLbEUOIScR20jCQ9KQwUgFsvFf7J0JfBTVGcB3NweBLJCEEAJECBDuK4FwiAHCIbcQASEqmoQcJBKSmANBsYZDq5XaVFGxaqWVKrXYYqUVlSqtVFFRsaWKllpatVLFNiIqVqr9z9tv3szOzpKN9v4Z/fjvvPnefc28eQeyE9mHHEaOIf7z0UHmIJVIE7IbOYgcReIuwB1kLDIDWYLUIBuRXchB5Cgy5ELSHqlHNiHbkN3IIeQochJJX0KaIpuNugjLkQ3IJmQrshM5jJxE4i6i3CA5yEKkHtmAbEF2I4eRE0j0xcSNdNqG7EOakeRUnycHKUE2INuQ/cgJJJXBjBlIJXIHshs5jPh5uc9G8pA1yA7kIHICSe6Oe8gSpBHZhuxHTiJpadxDliBrkC3IHuQI4jmD+0gOUohsRHYhR5BoBk8GIAuRNcgO5BBiDKakI7lIPvLl35d//yt/0UiZxxs4K37ckmrm6tdVN9QWlwZ+1lUONU76LxmaNSxrWGbZ0JV1IzKzxuh7q8aOHlrHQqzSkqG1pZWlHO1kanDXEHWKyLDqpWrnwXGenERPuvEcY6ylfLTIo3lORXFtdV11WX36gPkD0+fV1FesqLi8ompZ+hR2UayoZAlPP49frbFrHm98nzJcXjUq80zWp1XXsl1h/aqC6qpivmcrvQVp9EMDw+ip6ea826NXD0+MD6dXVVFfUG3cMHbF5515TuKIZI9er5Ys1bw9YvJQV/rmnmq+vDqMd2F+QVEJS5YqK0qr6gumTDLP5PWr/cnxhGvXOf09rTVo2Wqe/SrXtWpaT+bIj4xgjry5DsDPRWcJg3keKn5htirozJjdEs/4APCL/oT0rQmOJ2vzrHjqPR0Jf0XCaeOKOy2uXwgKN+7pcNvDeTLKOmPAi/RBXutOPxMczrqQcEaYJ7ij93bsoHSrWJCiXHDLG61vrJ3Z4wvM785OJh1jWDqToI6siMVIrb8r5MdWZEUS+ZIQ449KDt3n022vz+gI8jZF8raDMtNhtp+jw5yb0LJ8LJVnUJ12znIc2brLHRGW4x1foBzrNZVhyvEsiePOtgHLG33UfeG7lI89wXEsqagNHHxU17D0Ek55qyuory4w9z3soPNemeg9HY8oNy7xpfiGu68/lfh10PuN4o1H1jp98tlnJ9T9fJ95Ns8xdV3o+wZ7OsT5stDDHJMTvQzz3u7rVm1pXZCmVlIqvRO4b9vrvRTqcH+o3FvEWp+Rei9UegPaW6Oc2Pb/TFfr0dl5PdH7npfwKHMJD7bbWe7rtVLzlZ1huMu11u1J2Wqr0qEwTfYTl7JzinBeQF04Ek16EqFPO+E=
*/