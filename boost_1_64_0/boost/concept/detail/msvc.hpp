// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_CHECK_MSVC_DWA2006429_HPP
# define BOOST_CONCEPT_CHECK_MSVC_DWA2006429_HPP

# include <boost/preprocessor/cat.hpp>
# include <boost/concept/detail/backward_compatibility.hpp>
# include <boost/config.hpp>

# ifdef BOOST_OLD_CONCEPT_SUPPORT
#  include <boost/concept/detail/has_constraints.hpp>
#  include <boost/type_traits/conditional.hpp>
# endif

# ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable:4100)
# endif

namespace boost { namespace concepts {


template <class Model>
struct check
{
    virtual void failed(Model* x)
    {
        x->~Model();
    }
};

# ifndef BOOST_NO_PARTIAL_SPECIALIZATION
struct failed {};
template <class Model>
struct check<failed ************ Model::************>
{
    virtual void failed(Model* x)
    {
        x->~Model();
    }
};
# endif

# ifdef BOOST_OLD_CONCEPT_SUPPORT
  
namespace detail
{
  // No need for a virtual function here, since evaluating
  // not_satisfied below will have already instantiated the
  // constraints() member.
  struct constraint {};
}

template <class Model>
struct require
  : boost::conditional<
        not_satisfied<Model>::value
      , detail::constraint
# ifndef BOOST_NO_PARTIAL_SPECIALIZATION
      , check<Model>
# else
      , check<failed ************ Model::************>
# endif 
        >::type
{};
      
# else
  
template <class Model>
struct require
# ifndef BOOST_NO_PARTIAL_SPECIALIZATION
    : check<Model>
# else
    : check<failed ************ Model::************>
# endif 
{};
  
# endif
    
# if BOOST_WORKAROUND(BOOST_MSVC, == 1310)

//
// The iterator library sees some really strange errors unless we
// do things this way.
//
template <class Model>
struct require<void(*)(Model)>
{
    virtual void failed(Model*)
    {
        require<Model>();
    }
};

# define BOOST_CONCEPT_ASSERT_FN( ModelFnPtr )      \
enum                                                \
{                                                   \
    BOOST_PP_CAT(boost_concept_check,__LINE__) =    \
    sizeof(::boost::concepts::require<ModelFnPtr>)    \
}
  
# else // Not vc-7.1
  
template <class Model>
require<Model>
require_(void(*)(Model));
  
# define BOOST_CONCEPT_ASSERT_FN( ModelFnPtr )          \
enum                                                    \
{                                                       \
    BOOST_PP_CAT(boost_concept_check,__LINE__) =        \
      sizeof(::boost::concepts::require_((ModelFnPtr)0)) \
}
  
# endif
}}

# ifdef BOOST_MSVC
#  pragma warning(pop)
# endif

#endif // BOOST_CONCEPT_CHECK_MSVC_DWA2006429_HPP

/* msvc.hpp
RJ44GfV7c6nJd2fpxkkeugHr79nZW50fXllJKvwa0QcXriuELEr8kotXrob4MwSfJZ7rBa4P+NV+Hf4cwft5lHlcpIDvE3yln9+a+B2RiEOZCM6q95oL6J+I6Cdlnif8TGSCDaedjrc/2Ks6UuJ19t9HaN9sVb7GH2TqyZdp4HuZC/kyr1C19uJdQhOfsSLLHR64GTAcUrdKOqsP7Y3odsLk2S0ckUWOyAc3XPfjLcfhO2Bm4gWTETiU4bEuUpgEmZ/4lr7kG1qGvnIvd7JYRKx6rIu4gwQnUlGIwAvZbIWr8iDNPOTMjX1ZSI/rPJRhJLGct61kE13maRoViecPyllluMIumtipOOGSS0UnvjJwH4lgC7/IPS+NmXn3A9v9k03stM9DpWk/YTq+A8JR1y8w8QX0fxmKAp6MSdVy8kA1nX2VbtD3kubB+zBBGkd+UbDBdbSdNAYVfcuyRnhdxpX60zStWO17MAzf6hI+n8UiSRyZVHwLxwZxshZPeA6miff1TV7JpOsmkQxTKCO3Sol63HKUtHPVu8Gdn2B9fG1D8VspPo6lCHPPZVaBEN86PGb0icQPitBLVTei71SM955H6V3jMM3jSMDTQJj/3NvZH4BT8JIJ4wrJn0EspxFDCYMQxpTZVo+pXPM6t9W48z9FXI1RKUUGFXZtfSyIxjxeWqaPzjKxNmB4rjD9PwEGH0oRTOVX/VSZJtFGmSnUxSi9KiPKkL/BvJg49N2+9lfMh0nHMXyajOEpSxPpSM/PLn4Mv/LV77JV2eZZkDf06LjSfXBnFWJ1KPqsop8E+mjdIQ7krF1LyTkEuMo8g9drRQaboeh3gPU70Jvra2ZudnV2EfA63XPr4jF5TL8/B3htBjH5wXzvjrB2KOnEumOiN6t00R3BYEI3q/ShMWihEaHnnzdWcg4DxrRuCEI5rSMaww3UoXlM62UKcwowtD2hIJij7lTlohIGMauY+m7ksMROA5a0qIGMe5TfDQn6e6y+E01A3tX3Ar+P1kq5xlEYFzFGizHmxKuqof/XaHO6jyB9+rKUDq6zW0ZsvYlNlL6wasRrpTTonyj39pejtBWUq/1jX35IX1l4GMnTpi1AI3UK2Ub6S0bpkC2kj1/BptP4OpdUdG6lYMq4ImJIKuiLGuk0FRK7vMQQhynlbX8dFgZxZ66EuDonMbgWevxVEVfvDMbw6dwfR2yj0xcjFgM0ZsTXO3cZyt50TcQ2OkNRMMS/6zq1eDvzqNs/X1fjqW0nMRufvnUEA9WD9de63ii9jMeg+ReBvq6NHOrmPGIbxz+U+9zrr4uFLKLca90AsU1jMJb3yYAltrAUhfR/IZ3YXKRfcsMROkjANvhbpNfOGzCe5pNvVIsDWVh/KtFaDBQIYyEBphyb0UYg/+JNkGbPD4aYbQRjtjtsA6+/mYFBxJC+dbtBx3mgYYduhXSzHaEuNt0a6DXOTQ19Pf52iLGdmKIu5J0AA/OQUV1snUBaoy5+iphmXTy+jZhaXRyYRHqtLv48hXRTF0hf2wV06yG6kf6Vp4GOj7eRju/FDtK3gz73k1BEkRknRx3OLx7plQ8+8G3Ejat9ipK/dLhcqlrHq4kKTX/BDN2PkUGQyeTiY6DjPf4PjZnrSS/lwksCj2nd7dk9nPMvVjy/NHkyFuZpHnDHYwN9GCyKB31gz1hvmnOfZ/FgX2fP7hEnA+jDdfytRlqCCSllkXk+U/ddwpVBEH4vgT/m9ENIL92jz6xV19x89c23BCnac4+q72J/VetK55o+ZtHv5WaJ1xrSL0PpZeMd1NlVrv7SazbVGY0h+5/WqFNrcx5xcgwwpkMjM94n0Cwn+kbs/nOXU3SVfhU=
*/