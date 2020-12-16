
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

// no include guards, this file is intended for multiple inclusion

#if   BOOST_FT_ARITY_LOOP_PREFIX

#   ifndef BOOST_FT_DETAIL_SYNTHESIZE_IMPL_MASTER_HPP_INCLUDED
#   define BOOST_FT_DETAIL_SYNTHESIZE_IMPL_MASTER_HPP_INCLUDED
#     include <boost/preprocessor/cat.hpp>
#     include <boost/preprocessor/arithmetic/dec.hpp>
#     include <boost/preprocessor/iteration/local.hpp>
#     include <boost/preprocessor/facilities/empty.hpp>
#     include <boost/preprocessor/facilities/identity.hpp>
#   endif

#   define BOOST_FT_type_name type

#   ifdef BOOST_FT_flags
#     define BOOST_FT_make_type(flags,cc,arity) BOOST_FT_make_type_impl(flags,cc,arity)
#     define BOOST_FT_make_type_impl(flags,cc,arity) make_type_ ## flags ## _ ## cc ## _ ## arity
#   else
BOOST_PP_EXPAND(#) define BOOST_FT_make_type(flags,cc,arity) BOOST_FT_make_type_impl(flags,cc,arity)
BOOST_PP_EXPAND(#) define BOOST_FT_make_type_impl(flags,cc,arity) make_type_ ## flags ## _ ## cc ## _ ## arity
#   endif

#   define BOOST_FT_iter(i) BOOST_PP_CAT(iter_,i)

#elif BOOST_FT_ARITY_LOOP_IS_ITERATING

template< BOOST_FT_tplargs(BOOST_PP_IDENTITY(typename)) >
struct BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,BOOST_FT_arity)
{
  typedef BOOST_FT_type ;
};

template<> 
struct synthesize_impl_o< BOOST_FT_flags, BOOST_FT_cc_id, BOOST_FT_n > 
{ 
  template<typename S> struct synthesize_impl_i
  {
  private:
    typedef typename mpl::begin<S>::type BOOST_FT_iter(0);
#   if BOOST_FT_n > 1
#     define BOOST_PP_LOCAL_MACRO(i) typedef typename mpl::next< \
          BOOST_FT_iter(BOOST_PP_DEC(i)) >::type BOOST_FT_iter(i);
#     define BOOST_PP_LOCAL_LIMITS (1,BOOST_FT_n-1)
#     include BOOST_PP_LOCAL_ITERATE()
#   endif
  public:
    typedef typename detail::BOOST_FT_make_type(BOOST_FT_flags,BOOST_FT_cc_id,BOOST_FT_arity) 
    < typename mpl::deref< BOOST_FT_iter(0) >::type 
#   if BOOST_FT_mfp
    , typename detail::cv_traits< 
          typename mpl::deref< BOOST_FT_iter(1) >::type >::type
#   endif
#   if BOOST_FT_n > (BOOST_FT_mfp+1)
#     define BOOST_PP_LOCAL_LIMITS (BOOST_FT_mfp+1,BOOST_FT_n-1)
#     define BOOST_PP_LOCAL_MACRO(i) \
        , typename mpl::deref< BOOST_FT_iter(i) >::type
#     include BOOST_PP_LOCAL_ITERATE()
#   endif
    >::type type;
  };
};

#elif BOOST_FT_ARITY_LOOP_SUFFIX

#   ifdef BOOST_FT_flags
#     undef BOOST_FT_make_type
#     undef BOOST_FT_make_type_impl
#   else
BOOST_PP_EXPAND(#) undef BOOST_FT_make_type
BOOST_PP_EXPAND(#) undef BOOST_FT_make_type_impl
#   endif
#   undef BOOST_FT_iter
#   undef BOOST_FT_type_name

#else
#   error "attempt to use arity loop master file without loop"
#endif


/* master.hpp
TuKHegckocFjUAiFDxULR4pyY0iXPoXL6hEFFzPBfie8cCTDbaXhP0bEf1wgYJpa2uzwQv+InInrPXzoYMQ7fLAgZ/xiNCp07OBAoTwyJLoXm4No/qaNWId3689MCaWKP12W3FB2tcb41VPgz7CLQtPfEL9JLCEIRKrS0dMiDguJKCcY483xK2HKzhurytIJND5h7WT9wPvUcmxfmO+LkrydiYpVJhGX5VeRfWSFinhdwEmu5SUBeKlghE6tt4E/nFkhtSLR+krhjB45lR3g2GKLGs+GN1xYFJyqdPrMBBhS95vNUhLD2klB0hFVbqk2RpNPFVfGJyty19kZ4k3LqRQvve634jnNFvxUh/lK2KgOF5gKalUYrpy/opPv3U4KrzThfjc/fv93YqzqwNftcCF4+yeezx+b2HWXREHMrInmY7RVIJM3LBx5sFARBAe/KOOxQXxw8kl1GUI8Mm0/RDFtPNsvUlWwe6kEEEn5+/J47bzaeOwPI7/h4qKCNwwLJwZQctscxTOj0fg8+yF2kjZOqpWl2umXNUuYGTEvJ1KHsZIjfMSlRaiqRRE+UV6EcuGlnJ70z4bcwlnE/SPENjW8GT/Qgt98/IIgGsP773RB5J+5IBgdEwmpd/wMAdn40qcydCLyLXOgbGb6VlvjrhQJcuTggARFOEtso3CGUS+LNkHD6oexuX/kofSrEq86qVloGY+L3AL0fNXa/iGK1hynkTbUkK2I1bZy1v7aSP5wU0Jqpibw3vv+sq0ZNbCJyPGiwd4k8Kl0e88TidmIyJEAmLgvZnxmh1DTDMUnGMyTqD8TNF8iNnMP96cBdLCQSbHFjcMbmpEI05+SUKIcJYBUIm6H7ezgTFesIGSrNmVWTxl3+4iMaQp1/uTU2aNTRkvA9Wj6w1CumylCCpOhoogwCQwHZenQtlC8hEAL2gPloSlsDBuJ24njaR01osSLctEo3F8RdYk6+3TTKFSOg7AWRomF+c0b+eVTeDGvSYc5gPD9oxNbToeRhj1JrA6gfEpW3YRt8uVDnEGH/wgwXENYUVvlRm10GjeG5Jon8ltDsfyIUULjXwjJdtFoao56zAjfFIjnqcnftu/0BbIjWqvZp/eFjFA+Bt9IzbUM6ZtGtRZPvjpsXlo+GBK5sSC70CX5d3hQDo4WiXI8GBOZ82x5U2lz8W0n/+8U7CInTLYO9glCvn9DQo4F50SxauLWxD8NafX0CHua+MeCSfmV+MQ3KSHONPKu4EMjySLn0+R3awzDQospVbm3Xpd2O5vS4Vr0mtS0Hq35En5EcqxE5Y+/+2d3tPZAl2e/93K9/baVUWhluob8PXb9tsFj522bwq0of2uY8XzDtkF4vuA0v+Dv+X4p+sq/cwRfxbhZLnTtft2v+3W/7tf9ul/3637dr/t1v+7X/bpf9+t+3a/7db/u1/26X/frfv/Zb7g0UNpp/7MfW2PTl4946cUHPrr6sBtXygl8YJ/IkMPer9q06ajMjI1XYdmx/XmNXXbaec8m7oI9dtu+ceao3K26fWRwoXi518yeiT1ioLpDvQrzn3N77J/51gi6X/frft2v+/0dX26TXLBJBe6sw10/F6w/B9f4N8gFG3ytLsL1BcG6uy8pd7ZsHqxVX/PU2w8RewHYBay7a0+wSW7NQGC4O5/yqKiLNPsSea6VC9bKJ+Br54K1tQxziKd+47J/7Z5g7dzaFs7h55Gega+WC1bLw9V8+tJlvysqOXBx2khD8yR3jtx5yqOieflctEEf4v2V4VGudXeybWPqeGCAPtvW1MHCdkr2WR7unLpaX6SbpzauuNLKgIvbEX2j6XrGU5gLwoqOF7jqZzi7Br9qLlg16Wo=
*/