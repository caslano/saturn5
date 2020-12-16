// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_DETAIL_GENERAL_DWA2006429_HPP
# define BOOST_CONCEPT_DETAIL_GENERAL_DWA2006429_HPP

# include <boost/config.hpp>
# include <boost/preprocessor/cat.hpp>
# include <boost/concept/detail/backward_compatibility.hpp>

# ifdef BOOST_OLD_CONCEPT_SUPPORT
#  include <boost/concept/detail/has_constraints.hpp>
#  include <boost/type_traits/conditional.hpp>
# endif

// This implementation works on Comeau and GCC, all the way back to
// 2.95
namespace boost { namespace concepts {

template <class ModelFn>
struct requirement_;

namespace detail
{
  template <void(*)()> struct instantiate {};
}

template <class Model>
struct requirement
{
    static void failed() { ((Model*)0)->~Model(); }
};

struct failed {};

template <class Model>
struct requirement<failed ************ Model::************>
{
    static void failed() { ((Model*)0)->~Model(); }
};

# ifdef BOOST_OLD_CONCEPT_SUPPORT

template <class Model>
struct constraint
{
    static void failed() { ((Model*)0)->constraints(); }
};
  
template <class Model>
struct requirement_<void(*)(Model)>
  : boost::conditional<
        concepts::not_satisfied<Model>::value
      , constraint<Model>
      , requirement<failed ************ Model::************>
    >::type
{};
  
# else

// For GCC-2.x, these can't have exactly the same name
template <class Model>
struct requirement_<void(*)(Model)>
    : requirement<failed ************ Model::************>
{};
  
# endif

#  define BOOST_CONCEPT_ASSERT_FN( ModelFnPtr )             \
    typedef ::boost::concepts::detail::instantiate<          \
    &::boost::concepts::requirement_<ModelFnPtr>::failed>    \
      BOOST_PP_CAT(boost_concept_check,__LINE__)             \
      BOOST_ATTRIBUTE_UNUSED

}}

#endif // BOOST_CONCEPT_DETAIL_GENERAL_DWA2006429_HPP

/* general.hpp
hrmbBVnFhGEEp/BSDbaVLT+27psEbiS57w55yyPFkVig20w+CHWdRZnnDbnKpmbZuAmTp2CRqpsg5XLIBFctrfpkJH8Bk2kQRCF3KibsGMr62LGg5wlvxCSPAx7GmMvSTvXBVC2q4BuraF9wPWHpRuRF4fkuH/L3u91ljNBK1gSnCS9nYZFHjscDkxf3P1U7wK1L00+CVfaEOz6PXSw7jTNLy372x/b5hScFzCmRF/dNMXUS7/OdtE0F0g0C1arY0Tll1rEfkmEG981M3oJ5UZIE4H9JZRLtcdfat/ibVVY/iEUI8UV1JNr1yjr+E+veRp5LL0g9tqRe2mmTWd5306FX7fuWE4TfZW4eCd/LQlZFsR74+eqD7yt7PhITXoelKU8cJ3BZfRBn5Jv+fIvweakb8bTIaNzWhyEfxgwn9eKxKHECnmWp4jOqZcXQ8JB3y7vGSDnhJCiKgkLxonq1ikbmDQd/Yt+bDKIkhPlhv6tjN9cOEHieZtWRXzhKUbnD+jMDcwrBd4wS2PuBzMy7ZHEu3SiIPYY9kLREw6b/xBrXMxkU0uHMHEza2obQgQnHpTUiI1U6j1MJsThhCIAWAqF3lKSFQ5YIoy+f+4l9jzAKM+4JlKF+rD0YnFf8zdJdnMZJzmUAvCTgem+JjA9ptS/wU3q+LoOk8N2MMzU7m+sdw2jGU3pz2nwdYq9PDryLtr/EgVaUBWxwVbcsRI/WxZ5qf5uZ+dgdqVoIczdmK4tl+HGofxrrXWo82qDI9wLPz9lxFTVYqQqSs3b99+CahPA6jOcBTwMvHvKSIcPBNYnJJ1iRcuHzCNiOLvUeuqSHG2rvTlGePBe5FDJFHkzIXNOS/HkszTMn5xlXTNiDyChqtIf3Ed6YqcYQBlHusYcu98BS6umvfSq0gP4ATf6cBQIupopYs5u5bR2D2J63VW9+GSvj+Hp2DF/w5XQ7RW/5SMcYwPj2p6VoRnxfD2P7Uv9Xlxkjh1K1b7/nL9OI6wMd495+jJ57p7kTxNxP2b7Ai/bsuM/+bB8qqqcWtqWd37GjXU7JlO6YGfeWyIqUvqUbChGVspqlVCPGlClr/ONUll94nlvkTpOs9nSzLGbJylWnzoQnmmTtmmiW1SeyMlb4QqRcus36QomoL9S9la8kDJ3Aj/ymfO1eR19nbVki9rzUadKX2khqlrXlE1YZYxnHQeAO/HjuuKBEovtPWLp30yRP86QpX1O71tG9la9cKo0Fsb9uviand9bq3i6jF6SZ74frylLbYLXt3pTluyxWRQyiNNOyDuzes3NXG2WO1qopa9sn6b0iN049Nw3YQMgFGwWNHW3J8oTrOUHQLKw9udsShrJOElk5jGdpUGQho6Vrrk82lPU+K18iFkK6cbOdmNQyZtXOwPIJUsZfWvkKpEiyLOLr98fJHZVEovtP0XyFaRokrpNhvkakNOdLfoq2CV5kmcgd0ocarYUqLzPidp+y8hVx2MkLG82XpS609WtETs5iL+F+JnSWLiiNlO9vVp5i7odenAeNtmudOrz1p6muZOHBRf9iA7pqT05SGzH/aavNZ17miqjAfI20+OZ8vYDIylkU5iLiPl/fDk5P1rWtM5as2PcL7l1A1s4JzB2xz5+x2rzqizzz1jddd95RW4+MyEqYF8rYTf1E9+sLNi9iny1ZsXA5l3nQLOvOu5pknbbzVRR5pPr2OoaQ9Eaieztfjl+khec128GJ6SZZrc9SWUkchU7mbMCklqKI7icsWSKP4Mp32Czszu2mfB20ZElPOKLIGkVNTuxszNcpS5brJzIQch1hU7ub8rVmyYqyPEj8KG2WtatR9+ftMsaCB4n0G2XtpBbatKnbPkc=
*/